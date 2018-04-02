//
// Created by kuba on 18.03.18.
//

#ifndef POKERGAME_CONTROLLER_H
#define POKERGAME_CONTROLLER_H

#include "model/Model.h"
#include "utils/BlockingQueue.h"
#include "server/ClientHandler.h"
#include "event/Event.h"
#include "protocol/Protocol.pb.h"

class Controller;
typedef void (Controller::*EventHandler)(Event *event);
typedef void (Controller::*MessageHandler)(const Request *const request, ClientHandler *const clientHandler);

class Controller {

private:
    BlockingQueue<Event *> *const blockingQueue;
    Model *const model;
    bool workerFlag;
    std::map<std::string, EventHandler> eventStrategyMap;
    std::map<Request::PayloadCase, MessageHandler> messageStrategyMap;
    void eventRecvRequestHandler(Event *event);
    void eventConnectionClosedHandler(Event *event);
    void messageLoginHandler(const Request *const request, ClientHandler *const clientHandler);
    void messageCreateTableHandler(const Request *const request, ClientHandler *const clientHandler);
    void messageJoinTableHandler(const Request *const request, ClientHandler *const clientHandler);
    void messageLeaveTableHandler(const Request *const request, ClientHandler *const clientHandler);
    void messageRaiseHandler(const Request *const request, ClientHandler *const clientHandler);
    void messageFoldHandler(const Request *const request, ClientHandler *const clientHandler);
    void messageCallHandler(const Request *const request, ClientHandler *const clientHandler);


public:
    Controller(BlockingQueue<Event *> *const blockingQueue, Model *const model);
    void run();
    void setWorkerFlag(bool workerFlag);
};


#endif //POKERGAME_CONTROLLER_H
