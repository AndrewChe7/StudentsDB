
#include <interpreter.h>
#include "newServer.hpp"

//TCP connection

tcp_connection::tcp_connection(boost::asio::io_service &io_service)
        : socket_(io_service), db_(nullptr)
{
}

void tcp_connection::handle_write(const boost::system::error_code &, size_t)
{

}
void tcp_connection::handle_nothing(const boost::system::error_code &, size_t) {}
void tcp_connection::handle_size(const boost::system::error_code &, size_t) {
    std::istream(&buffer_) >> size_;
    std::cout << "Got size of request: " << size_ << std::endl;

    boost::asio::async_read(socket_, buffer_, boost::asio::transfer_exactly(size_),
                            boost::bind(&tcp_connection::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}


void tcp_connection::handle_read(const boost::system::error_code &, size_t size)
{
    request_ = std::string((std::istreambuf_iterator<char>(&buffer_)), std::istreambuf_iterator<char>());
    std::cout << "Got request: " << request_ << std::endl;
    auto* core = new ParserModule::Interpreter (db_);
    std::cout << "Core created. " << core << std::endl;

    std::istringstream req(request_);
    core->switchInputStream(&req);
    answer_ = core->parse();
    ss_.str("");
    ss_ << std::setw(10) << std::setfill('0') << answer_.size();

    boost::asio::async_write(socket_, boost::asio::buffer(ss_.str()),
                             boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));

    boost::asio::async_write(socket_, boost::asio::buffer(answer_),
                             boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));

}

void tcp_connection::getRequest() {
    boost::asio::async_read(socket_, buffer_, boost::asio::transfer_exactly(10),
                            boost::bind(&tcp_connection::handle_size, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::start(DB::DB* db) {
    std::cout << "Somebody connected." << std::endl;
    db_ = db;
    getRequest();
}

tcp::socket &tcp_connection::socket() {
    return socket_;
}

tcp_connection::pointer tcp_connection::create(boost::asio::io_service &io_service) {
    return pointer(new tcp_connection(io_service));
}


//TCP server

tcp_server::tcp_server(boost::asio::io_service &io_service, DB::DB* db, int port)
        : acceptor_(io_service, tcp::endpoint(tcp::v4(), port)), db_(db), port_(port), running_(true)
{
    std::cout << "Server acceptor started." << std::endl;
    start_accept();
}




void tcp_server::start_accept() {
    tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());
    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&tcp_server::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void tcp_server::handle_accept(const tcp_connection::pointer& new_connection, const boost::system::error_code &error) {
    if (!error)
    {
        new_connection->start(db_);
    }
    start_accept();
}
