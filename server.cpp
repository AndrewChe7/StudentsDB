//
// Created by godknows on 20.05.2020.
//

#include <thread>
#include "Modules/Server/newServer.hpp"

int main(int argc, char **argv) {
    std::string f;
    FILE* q1;
    int port;

    if (argc != 3) {
        printf("Usage: %s [DBfile] [port]\n", argv[0]);
        return -1;
    }
    if ((q1 = fopen(argv[1], "r")) == nullptr) {
        printf("Can't open file %s\n", argv[1]);
        return -2;
    }
    fclose(q1);
    try {
        std::string s = argv[2];
        port = std::stoi(s);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -3;
    }

    f = argv[1];
    auto* db = new DB::DB();
    db->loadDB(f);
    //Server server(db, port);
    bool isRunning = true;

    try
    {
        boost::asio::io_service io_service;
        tcp_server server(io_service, db, port);

        std::thread thr = std::thread([&]{ io_service.run(); });

        std::cout << "Server started." << std::endl;

        std::string command;
        while (isRunning) {
            std::cin >> command;
            if (command == "stop") {
                isRunning = false;
            }
        }
        io_service.stop();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    db->unloadDB();
    delete db;
    return 0;
}

