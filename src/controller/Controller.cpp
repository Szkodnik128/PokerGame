//
// Created by kuba on 18.03.18.
//

#include "Controller.h"

Controller::Controller(BlockingQueue<Event *> *const blockingQueue, Model *const model)
        : blockingQueue(blockingQueue),
          model(model),
          workerFlag(false)
{
}

void Controller::run()
{
    Event *event;

    this->workerFlag = true;
    while (this->workerFlag) {
        event = this->blockingQueue->pop();
        std::cout << event->getClientHandler() << std::endl;
        delete event;
    }
}

void Controller::setWorkerFlag(bool workerFlag) {
    this->workerFlag = workerFlag;
}
