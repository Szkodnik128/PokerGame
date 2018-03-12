//
// Created by kuba on 12.03.18.
//

#include "Server.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


Server::Server(std::string const &address, std::string const &service, size_t max_connections)
{
    this->address = address;
    this->service = service;
    this->max_connections = max_connections;
    this->work_flag = false;
}

void Server::run()
{
    int ret, client_sock;
    int reuse_addr = 1;
    socklen_t sock_len;
    struct sockaddr_in client_addr;

    this->hints.ai_family = AF_INET;
    this->hints.ai_socktype = SOCK_STREAM;

    ret = getaddrinfo(this->address.c_str(), this->service.c_str(), &this->hints, &this->res);
    if (ret != 0) {
        // TODO: Throw exception
    }

    this->sock = socket(this->res->ai_family, this->res->ai_socktype, this->res->ai_protocol);

    ret = setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int));
    if (ret == -1) {
        // TODO: Throw exception
    }

    ret = bind(this->sock, this->res->ai_addr, this->res->ai_addrlen);
    if (ret == -1) {
        // TODO: Throw exception
    }

    ret = listen(this->sock, (int)this->max_connections);
    if (ret == -1) {
        // TODO: Throw exception
    }

    this->work_flag = true;
    sock_len = sizeof(struct sockaddr_in);

    while (this->work_flag == true) {
        client_sock = accept(this->sock, (struct sockaddr*)&client_addr, &sock_len);
        if (client_sock == -1) {
            // TODO: Log error
        } else {
            std::cout << "New connection" << std::endl;
        }
    }

    close(this->sock);
}
