//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_EVENTRECVREQUEST_H
#define POKERGAME_EVENTRECVREQUEST_H

#include "Event.h"

class EventRecvRequest : public Event {

private:
    const Request request;
public:
    const Request &getRequest() const;

public:
    explicit EventRecvRequest(const void *const clientHandler, const Request request);
};


#endif //POKERGAME_EVENTRECVREQUEST_H
