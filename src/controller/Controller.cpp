//
// Created by kuba on 18.03.18.
//

#include "Controller.h"
#include "event/EventRecvRequest.h"
#include "event/EventConnectionClosed.h"


Controller::Controller(BlockingQueue<Event *> *const blockingQueue, Model *const model)
        : blockingQueue(blockingQueue),
          model(model),
          workerFlag(false)
{
    /* Fill event strategy map */
    this->eventStrategyMap[typeid(EventRecvRequest).name()] = &Controller::eventRecvRequestHandler;
    this->eventStrategyMap[typeid(EventConnectionClosed).name()] = &Controller::eventConnectionClosedHandler;
}

void Controller::run()
{
    Event *event;
    EventHandler handler;

    this->workerFlag = true;
    while (this->workerFlag) {
        event = this->blockingQueue->pop();

        handler = this->eventStrategyMap[typeid(*event).name()];
        assert(handler != nullptr);
        (this->*handler)(event);

        delete event;
    }
}

void Controller::setWorkerFlag(bool workerFlag) {
    this->workerFlag = workerFlag;
}

void Controller::eventRecvRequestHandler(Event *event)
{
    std::cout << "eventRecvRequestHandler" << std::endl;
}

void Controller::eventConnectionClosedHandler(Event *event)
{
    std::cout << "eventConnectionClosedHandler" << std::endl;
}