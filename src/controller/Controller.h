//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_CONTROLLER_H
#define POKERGAME_CONTROLLER_H

#include "model/Model.h"
#include "utils/BlockingQueue.h"
#include "event/Event.h"

class Controller;
typedef void (Controller::*EventHandler)(Event *event);

class Controller {

private:
    BlockingQueue<Event *> *const blockingQueue;
    Model *const model;
    bool workerFlag;
    std::map<std::string, EventHandler> eventStrategyMap;
    void eventRecvRequestHandler(Event *event);
    void eventConnectionClosedHandler(Event *event);

public:
    Controller(BlockingQueue<Event *> *const blockingQueue, Model *const model);
    void run();
    void setWorkerFlag(bool workerFlag);
};


#endif //POKERGAME_CONTROLLER_H
