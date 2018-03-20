//
// Created by kuba on 18.03.18.
//

#include "Model.h"

#include <iostream>

void Model::login(const MsgLogin &login, ClientHandler *const clientHandler)
{
    bool found;
    Response response;
    Player *player;
    size_t response_size;
    void *response_buffer;

    std::cout << "login" << std::endl;

    found = isPlayerWithName(login.username());
    if (found) {
        response.set_error(MsgError::MsgErrorInvalidValue);
        response_size = response.ByteSizeLong();
        response_buffer = malloc(response_size);
        response.SerializeToArray(response_buffer, (int)response_size);
        clientHandler->sendMessage((unsigned char *)response_buffer, response_size);
        free(response_buffer);
    } else {
        player = new Player(login.username());

        this->players.push_front(player);
        this->clientHandlersMap[clientHandler] = player;

        /* TODO: Add player to lobby */

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
    std::cout << "disconnect" << std::endl;
}

bool Model::isPlayerWithName(std::string name)
{

}