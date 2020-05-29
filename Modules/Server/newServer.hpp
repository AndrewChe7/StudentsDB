
#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <DB.h>

using boost::asio::ip::tcp;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;
    static pointer create(boost::asio::io_service& io_service);
    tcp::socket& socket();
    void start(DB::DB* db);
    void getRequest();

private:
    explicit tcp_connection(boost::asio::io_service& io_service);
    void handle_nothing(const boost::system::error_code &, size_t);
    void handle_write(const boost::system::error_code&, size_t);
    void handle_size(const boost::system::error_code&, size_t);
    void handle_read(const boost::system::error_code&, size_t);
    tcp::socket socket_;
    std::string answer_;
    int size_;
    std::string request_;
    boost::asio::streambuf buffer_;
    DB::DB* db_;
    std::stringstream ss_;

};

class tcp_server
{
public:
    explicit tcp_server(boost::asio::io_service& io_service, DB::DB* db, int port);

private:
    void start_accept();
    void handle_accept(const tcp_connection::pointer& new_connection,
            const boost::system::error_code& error);
    tcp::acceptor acceptor_;
    DB::DB* db_;
    int port_;
    bool running_;
};