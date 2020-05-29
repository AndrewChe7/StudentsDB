//
// Created by godknows on 20.05.2020.
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdio>

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("%s [host] [port]\n", argv[0]);
        return -1;
    }

    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1], argv[2]);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    std::string line;
    int size;
    boost::asio::streambuf read_buf;
    std::stringstream ss;

    while (std::getline(std::cin, line, '\0') && (line != "stop"))
    {
        size = line.size();
        ss.str("");
        ss << std::setw(10) << std::setfill('0') << size;
        std::string str = ss.str();
        boost::asio::write(socket, boost::asio::buffer(str));
        std::cout << "Sent size: " << str << std::endl;

        boost::asio::write(socket, boost::asio::buffer(line));
        std::cout << "Sent request: " << line << std::endl;

        boost::asio::read(socket, read_buf, boost::asio::transfer_exactly(10));
        std::istream(&read_buf) >> size;
        std::cout << "Answer size: " << size << std::endl;

        boost::asio::read(socket, read_buf, boost::asio::transfer_exactly(size));
        std::string answer((std::istreambuf_iterator<char>(&read_buf)), std::istreambuf_iterator<char>());
        std::cout << answer;
    }
    socket.close();

    return 0;
}