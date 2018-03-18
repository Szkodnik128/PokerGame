//
// Created by kuba on 18.03.18.
//

#include "EventRecvRequest.h"

EventRecvRequest::EventRecvRequest(const void *const clientHandler, const Request request)
        : Event(clientHandler), request(request)
{
}

const Request &EventRecvRequest::getRequest() const {
    return request;
}
