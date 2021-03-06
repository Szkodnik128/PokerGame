//
// Created by kuba on 12.03.18.
//

#include "Server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <thread>
#include <iostream>
#include <cstring>

static void handle_connection(BlockingQueue<Event *> *const blockingQueue, const int client_sock);

Server::Server(BlockingQueue<Event *> *const blockingQueue, std::string const &address, std::string const &service,
               size_t max_connections)
        : blockingQueue(blockingQueue),
          address(address),
          service(service),
          max_connections(max_connections),
          workerFlag(false)
{
}

void Server::run()
{
    struct addrinfo hints;
    struct addrinfo *res = nullptr;
    int sock, ret, client_sock;
    int reuse_addr = 1;
    socklen_t sock_len;
    struct sockaddr_in client_addr;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    ret = getaddrinfo(this->address.c_str(), this->service.c_str(), &hints, &res);
    if (ret != 0) {
        std::cerr << "getaddrinfo failed" << ret << std::endl;
        return;
    }

    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    ret = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(int));
    if (ret == -1) {
        std::cerr << "setsockopt failed" << std::endl;
        return;
    }

    ret = bind(sock, res->ai_addr, res->ai_addrlen);
    if (ret == -1) {
        std::cerr << "bind failed" << std::endl;
        return;
    }

    ret = listen(sock, (int)this->max_connections);
    if (ret == -1) {
        std::cerr << "listen failed" << std::endl;
        return;
    }

    this->workerFlag = true;
    sock_len = sizeof(struct sockaddr_in);

    while (this->workerFlag) {
        client_sock = accept(sock, (struct sockaddr*)&client_addr, &sock_len);
        if (client_sock == -1) {
            std::cerr << "accept failed" << std::endl;
        } else {
            std::cout << "Accepted new connection: " << client_sock << std::endl;
            std::thread client_thread(handle_connection, this->blockingQueue, client_sock);
            client_thread.detach();
        }
    }

    close(sock);
}

void Server::setWorkerFlag(bool workerFlag) {
    this->workerFlag = workerFlag;
}

static void handle_connection(BlockingQueue<Event *> *const blockingQueue, const int client_sock)
{
    ClientHandler *clientHandler;

    /* Create new client handler */
    clientHandler = new ClientHandler(blockingQueue, client_sock);

    /* Run client handler */
    clientHandler->listen();

    /* Destroy client handler */
    delete clientHandler;

    /* Close socket */
    close(client_sock);
}
