//
// Created by kuba on 17.03.18.
//

#include "ClientHandler.h"
#include "protocol/Protocol.pb.h"
#include "event/EventRecvRequest.h"
#include "event/EventConnectionClosed.h"
#include "utils/BlockingQueue.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#define BUFFER_SIZE 1024

ClientHandler::ClientHandler(BlockingQueue<Event *> *const blockingQueue, const int clientSock)
        : blockingQueue(blockingQueue),
          clientSock(clientSock),
          loggedIn(false)
{
}

void ClientHandler::listen()
{
    unsigned char buffer[BUFFER_SIZE];
    Event *event;
    ssize_t sent;
    bool ret;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        sent = recv(this->clientSock, buffer, BUFFER_SIZE, 0);
        if (sent < 0) {
            std::cerr << "recv failed. client socket = " << this->clientSock << std::endl;
            event = new EventConnectionClosed(this);
            blockingQueue->push(event);
            return;
        } else if (sent == 0) {
            std::cerr << "connection closed. client socket = " << this->clientSock << std::endl;
            event = new EventConnectionClosed(this);
            blockingQueue->push(event);
            return;
        }

        ret = this->handleMessage(buffer, (size_t)sent);
        if (ret != true) {
            std::cerr << "received illegal message. closing connection. client socket = " << this->clientSock << std::endl;
            event = new EventConnectionClosed(this);
            blockingQueue->push(event);
            return;
        }
    }
}

bool ClientHandler::sendData(unsigned char *const data, size_t size) const
{
    ssize_t ret;

    ret = send(this->clientSock, data, size, 0);
    if (ret < 0) {
        return false;
    }

    return true;
}

bool ClientHandler::sendMessage(google::protobuf::Message *message) const
{
    size_t response_size;
    void *response_buffer;

    response_size = message->ByteSizeLong();
    response_buffer = malloc(response_size);
    message->SerializeToArray(response_buffer, (int)response_size);
    this->sendData((unsigned char *)response_buffer, response_size);
    free(response_buffer);

    return true;
}

bool ClientHandler::sendResponseMessage(google::protobuf::Message *message, Response::PayloadCase payloadCase) const
{
    size_t response_size;
    void *response_buffer;
    Response response;

    switch (payloadCase) {
        case Response::PayloadCase::kLobbyView:
            response.set_allocated_lobbyview((DummyLobbyView *)message);
            break;
        case Response::PayloadCase::kTableView:
            response.set_allocated_tableview((DummyTableView *)message);
            break;
        default:
            response.set_error(Error::ErrorInternalError);
            break;
    }

    response_size = response.ByteSizeLong();
    response_buffer = malloc(response_size);
    response.SerializeToArray(response_buffer, (int)response_size);
    this->sendData((unsigned char *)response_buffer, response_size);
    free(response_buffer);

    return true;
}

void ClientHandler::sendError(Error error) const
{
    Response response;
    size_t response_size;
    void *response_buffer;

    response.set_error(error);
    response_size = response.ByteSizeLong();
    response_buffer = malloc(response_size);
    response.SerializeToArray(response_buffer, (int)response_size);
    this->sendData((unsigned char *)response_buffer, response_size);
    free(response_buffer);
}

bool ClientHandler::handleMessage(unsigned char *const data, size_t size)
{
    Request request;
    Event *event;

    request.ParseFromArray(data, (int)size);

    if (this->loggedIn == false) {
        if (request.has_login()) {
            event = new EventRecvRequest(this, request);
            blockingQueue->push(event);
        } else {
            return false;
        }
    } else {
        event = new EventRecvRequest(this, request);
        blockingQueue->push(event);
    }

    return true;
}

void ClientHandler::setLoggedIn(bool loggedIn) {
    this->loggedIn = loggedIn;
}
