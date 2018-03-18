//
// Created by kuba on 18.03.18.
//

#include "Event.h"

Event::Event(const void *const clientHandler)
        : clientHandler(clientHandler)
{
}

const void *const Event::getClientHandler() const {
    return clientHandler;
}
