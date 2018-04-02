//
// Created by kuba on 20.03.18.
//

#include "Lobby.h"

void Lobby::createTable(const std::string &name, int maxPlayers)
{

}

void Lobby::joinTable(const std::string &name, Player *player)
{

}

void Lobby::leaveTable(const std::string &name, Player *player)
{

}

const std::list<Table *> &Lobby::getTables() const {
    return this->tables;
}

DummyLobbyView *Lobby::getLobbyView()
{
    DummyLobbyView *dummyLobbyView = new DummyLobbyView();


    return dummyLobbyView;
}
