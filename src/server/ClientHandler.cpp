//
// Created by kuba on 17.03.18.
//

#include "ClientHandler.h"
#include "protocol/protocol.pb.h"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#define BUFFER_SIZE 256

ClientHandler::ClientHandler(const int client_sock) : client_sock(client_sock)
{
    this->logged_in = false;
}

void ClientHandler::listen()
{
    unsigned char buffer[BUFFER_SIZE];
    ssize_t sent;
    bool ret;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        sent = recv(this->client_sock, buffer, BUFFER_SIZE, 0);
        if (sent < 0) {
            std::cerr << "recv failed. client socket = " << this->client_sock << std::endl;
            /* TODO: Add to queue connection closed event */
            return;
        } else if (sent == 0) {
            std::cerr << "connection closed. client socket = " << this->client_sock << std::endl;
            /* TODO: Add to queue connection closed event */
            return;
        }

        ret = this->handle_msg(buffer, (size_t)sent);
        if (ret != true) {
            return;
        }
    }
}

bool ClientHandler::send_msg(unsigned char *const data, size_t size)
{
    ssize_t ret;

    ret = send(this->client_sock, data, size, 0);
    if (ret < 0) {
        return false;
    }

    return true;
}

bool ClientHandler::handle_msg(unsigned char *const data, size_t size)
{
    Request request;

    request.ParseFromArray(data, (int)size);

    if (this->logged_in == false) {
        if (request.has_login()) {
            // TODO: Login
            this->logged_in = true;
        } else {
            return false;
        }
    } else {
        // TODO: Handle request
    }
}
