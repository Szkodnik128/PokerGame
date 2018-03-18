//
// Created by kuba on 17.03.18.
//

#ifndef POKERGAME_CLIENTHANDLER_H
#define POKERGAME_CLIENTHANDLER_H

#include "utils/BlockingQueue.h"
#include "event/Event.h"

#include <cstddef>

class ClientHandler {

private:
    BlockingQueue<Event *> *const blockingQueue;
    const int client_sock;
    bool logged_in;
    bool handleMessage(unsigned char *const data, size_t size);

public:
    ClientHandler(BlockingQueue<Event *> *const blockingQueue, const int client_sock);
    void listen();
    bool sendMessage(unsigned char *const data, size_t size);
};


#endif //POKERGAME_CLIENTHANDLER_H
