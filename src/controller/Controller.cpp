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

    /* Fill message strategy map */
    this->messageStrategyMap[Request::PayloadCase::kLogin] = &Controller::messageLoginHandler;
    this->messageStrategyMap[Request::PayloadCase::kCreateTable] = &Controller::messageCreateTableHandler;
    this->messageStrategyMap[Request::PayloadCase::kJoinTable] = &Controller::messageJoinTableHandler;
    this->messageStrategyMap[Request::PayloadCase::kLeaveTable] = &Controller::messageLeaveTableHandler;
    this->messageStrategyMap[Request::PayloadCase::kRaiseBet] = &Controller::messageRaiseHandler;
    this->messageStrategyMap[Request::PayloadCase::kFold] = &Controller::messageFoldHandler;
    this->messageStrategyMap[Request::PayloadCase::kCall] = &Controller::messageCallHandler;
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
    MessageHandler handler;
    auto *eventRecvRequest = (EventRecvRequest *)event;
    const Request &request = eventRecvRequest->getRequest();

    handler = this->messageStrategyMap[request.payload_case()];
    assert(handler != nullptr);
    (this->*handler)(&request, (ClientHandler *const)eventRecvRequest->getClientHandler());
}

void Controller::eventConnectionClosedHandler(Event *event)
{
    auto *eventConnectionClosed = (EventConnectionClosed *)event;

    this->model->disconnect((ClientHandler *const)eventConnectionClosed->getClientHandler());
}

void Controller::messageLoginHandler(const Request *const request, ClientHandler *const clientHandler)
{
    const Login &login = request->login();

    this->model->login(login, clientHandler);
}

void Controller::messageCreateTableHandler(const Request *const request, ClientHandler *const clientHandler)
{
    const CreateTable &createTable = request->createtable();

    this->model->createTable(createTable, clientHandler);
}

void Controller::messageJoinTableHandler(const Request *const request, ClientHandler *const clientHandler)
{
    const JoinTable &joinTable = request->jointable();

    this->model->joinTable(joinTable, clientHandler);
}

void Controller::messageLeaveTableHandler(const Request *const request, ClientHandler *const clientHandler)
{
    const LeaveTable &leaveTable = request->leavetable();

    this->model->leaveTable(leaveTable, clientHandler);
}

void Controller::messageRaiseHandler(const Request *const request, ClientHandler *const clientHandler)
{
    const Raise &raise = request->raise_bet();

    this->model->raise(raise, clientHandler);
}

void Controller::messageFoldHandler(const Request *const request, ClientHandler *const clientHandler)
{
    const Fold &fold = request->fold();

    this->model->fold(fold, clientHandler);
}

void Controller::messageCallHandler(const Request *const request, ClientHandler *const clientHandler)
{
    const Call &call = request->call();

    this->model->call(call, clientHandler);
}