//
// Created by kuba on 12.03.18.
//

#ifndef POKERGAME_SERVER_H
#define POKERGAME_SERVER_H

#include "ClientHandler.h"

#include <list>
#include <string>
#include <netdb.h>

class Server {

private:
    std::string address;
    std::string service;
    size_t max_connections;
    bool work_flag;

public:
    Server(std::string const &address, std::string const &service, size_t max_connections);
    void run();
};


#endif //POKERGAME_SERVER_H
