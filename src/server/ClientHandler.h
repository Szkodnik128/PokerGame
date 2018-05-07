//
// Created by kuba on 17.03.18.
//

#ifndef POKERGAME_CLIENTHANDLER_H
#define POKERGAME_CLIENTHANDLER_H

#include "utils/BlockingQueue.h"
#include "event/Event.h"
#include "protocol/Protocol.pb.h"

#include <cstddef>

class ClientHandler {

private:
    BlockingQueue<Event *> *const blockingQueue;
    const int clientSock;
    bool loggedIn;
    bool handleMessage(unsigned char *const data, size_t size);

public:
    ClientHandler(BlockingQueue<Event *> *const blockingQueue, const int clientSock);
    void listen();
    void setLoggedIn(bool loggedIn);
    bool sendData(unsigned char *const data, size_t size) const;
    bool sendMessage(google::protobuf::Message *message) const;
    bool sendResponseMessage(google::protobuf::Message *message, Response::PayloadCase payloadCase) const;
    void sendError(Error error) const;
};


#endif //POKERGAME_CLIENTHANDLER_H
