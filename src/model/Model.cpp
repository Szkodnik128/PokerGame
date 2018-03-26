//
// Created by kuba on 18.03.18.
//

#include "Model.h"

#include <iostream>

void Model::login(const MsgLogin &login, ClientHandler *const clientHandler)
{
    bool found;
    User *user;

    std::cout << "login" << std::endl;

    found = isUserWithName(login.username());
    if (found) {
        /* Send error */
        clientHandler->sendError(MsgError::MsgErrorInvalidValue);
    } else {
        /* Create a new user */
        user = new User(login.username());
        /* Add user to model */
        this->users.push_front(user);
        this->clientHandlersMap[clientHandler] = user;
        /* Set as logged in */
        clientHandler->setLoggedIn(true);

        /* TODO: Send lobby view */
    }
}

void Model::joinTable(const MsgJoinTable &joinTable, ClientHandler *const clientHandler)
{
    std::cout << "joinTable" << std::endl;
}

void Model::leaveTable(const MsgLeaveTable &leaveTable, ClientHandler *const clientHandler)
{
    std::cout << "leaveTable" << std::endl;
}

void Model::raise(const MsgRaise &raise, ClientHandler *const clientHandler)
{
    std::cout << "raise" << std::endl;
}

void Model::fold(const MsgFold &fold, ClientHandler *const clientHandler)
{
    std::cout << "fold" << std::endl;
}

void Model::call(const MsgCall &call, ClientHandler *const clientHandler)
{
    std::cout << "call" << std::endl;
}

void Model::disconnect(ClientHandler *const clientHandler)
{
    User *user;

    std::cout << "disconnect" << std::endl;

    /* Get user */
    user = clientHandlersMap[clientHandler];
    /* Remove user from model */
    this->users.remove(user);
    auto iterator = this->clientHandlersMap.find(clientHandler);
    this->clientHandlersMap.erase(iterator);
}

bool Model::isUserWithName(std::string name)
{
    for (auto iterator = this->users.begin(); iterator != this->users.end(); ++iterator) {
        if ((*iterator)->getName() == name) {
            return true;
        }
    }

    return false;
}