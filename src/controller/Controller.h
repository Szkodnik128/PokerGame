//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_CONTROLLER_H
#define POKERGAME_CONTROLLER_H

#include "model/Model.h"
#include "utils/BlockingQueue.h"
#include "event/Event.h"

class Controller {

private:
    BlockingQueue<Event *> *const blockingQueue;
    Model *const model;
    bool workerFlag;
public:
    void setWorkerFlag(bool workerFlag);

public:
    Controller(BlockingQueue<Event *> *const blockingQueue, Model *const model);
    void run();
};


#endif //POKERGAME_CONTROLLER_H
