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
    bool sendData(unsigned char *const data, size_t size);
    bool sendMessage(google::protobuf::Message &message);
    void sendError(Error error);
    void setLoggedIn(bool loggedIn);
};


#endif //POKERGAME_CLIENTHANDLER_H
