//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_EVENTCONNECTIONCLOSED_H
#define POKERGAME_EVENTCONNECTIONCLOSED_H

#include "Event.h"

class EventConnectionClosed : public Event {

public:
    explicit EventConnectionClosed(const void *const clientHandler);
};


#endif //POKERGAME_EVENTCONNECTIONCLOSED_H
