//
// Created by kuba on 18.03.18.
//

#include "Model.h"

#include <iostream>

void Model::login(const Login &login, ClientHandler *const clientHandler)
{
    Player *player;
    DummyLobbyView *dummyLobbyView;
    DummyTableView *dummyTableView;

    std::cout << "login" << std::endl;

    player = getUserWithName(login.username());
    if (player == nullptr) {
        /* Create a new user */
        player = new Player(login.username());
        /* Add user to model */
        this->players.push_front(player);
        this->clientHandlersMap[clientHandler] = player;
        /* Set as logged in */
        clientHandler->setLoggedIn(true);
        /* Mark as connected */
        player->setConnected(true);

    } else {
        if (player->isConnected()) {
            /* Player is connected. Send error */
            clientHandler->sendError(Error::ErrorInvalidValue);
            return;
        } else {
            /* Player was disconnected. Add to map again */
            this->clientHandlersMap[clientHandler] = player;
            /* Set as logged in */
            clientHandler->setLoggedIn(true);
            /* Mark as connected */
            player->setConnected(true);
        }
    }

    if (player->isPlaying()) {
        /* Player was reconnected */
        /* TODO: Send table view */
        //dummyTableView = player->getTable()->getTableView(player);
    } else {
        /* Send lobby view */
        dummyLobbyView = this->lobby.getLobbyView();
        clientHandler->sendResponseMessage(dummyLobbyView, Response::PayloadCase::kLobbyView);
    }
}

void Model::createTable(const CreateTable &createTable, ClientHandler *const clientHandler)
{
    Player *player;
    DummyLobbyView *dummyLobbyView;

    std::cout << "createTable" << std::endl;

    /* Get player */
    player = clientHandlersMap[clientHandler];

    /* Create table */
    this->lobby.createTable(createTable.name(), createTable.maxplayers());

    /* Add player to table */
    this->lobby.joinTable(createTable.name(), player);

    /* TODO: Send tableView to players in table */

    /* Send lobby view to all players in lobby */
    for (auto const& node : this->clientHandlersMap) {
        if (!node.second->isInTable()) {
            dummyLobbyView = this->lobby.getLobbyView();
            node.first->sendResponseMessage(dummyLobbyView, Response::PayloadCase::kLobbyView);
        }
    }
}

void Model::joinTable(const JoinTable &joinTable, ClientHandler *const clientHandler)
{
    Player *player;
    DummyLobbyView *dummyLobbyView;

    std::cout << "joinTable" << std::endl;

    /* Get player */
    player = clientHandlersMap[clientHandler];

    /* Join table */
    this->lobby.joinTable(joinTable.name(), player);

    /* TODO: Send tableView to players in table */

    /* Send lobby view to all players in lobby */
    for (auto const& node : this->clientHandlersMap) {
        if (!node.second->isInTable()) {
            dummyLobbyView = this->lobby.getLobbyView();
            node.first->sendResponseMessage(dummyLobbyView, Response::PayloadCase::kLobbyView);
        }
    }
}

void Model::leaveTable(const LeaveTable &leaveTable, ClientHandler *const clientHandler)
{
    Player *player;
    DummyLobbyView *dummyLobbyView;

    std::cout << "leaveTable" << std::endl;

    /* Get player */
    player = clientHandlersMap[clientHandler];

    /* Join table */
    this->lobby.leaveTable(leaveTable.name(), player);

    /* Send lobby view to all players in lobby */
    for (auto const& node : this->clientHandlersMap) {
        if (!node.second->isInTable()) {
            dummyLobbyView = this->lobby.getLobbyView();
            node.first->sendResponseMessage(dummyLobbyView, Response::PayloadCase::kLobbyView);
        }
    }
}

void Model::raise(const Raise &raise, ClientHandler *const clientHandler)
{
    std::cout << "raise" << std::endl;
}

void Model::fold(const Fold &fold, ClientHandler *const clientHandler)
{
    std::cout << "fold" << std::endl;
}

void Model::call(const Call &call, ClientHandler *const clientHandler)
{
    std::cout << "call" << std::endl;
}

void Model::disconnect(ClientHandler *const clientHandler)
{
    Player *player;

    std::cout << "disconnect" << std::endl;

    /* Get player */
    player = clientHandlersMap[clientHandler];
    /* If player didn't login then will be nullptr */
    if (player != nullptr) {
        /* Mark as disconnected */
        player->setConnected(false);

        /* Remove player from model if player is not playing */
        if (!player->isPlaying()) {
            this->players.remove(player);
        }

        /* Remove from map */
        auto iterator = this->clientHandlersMap.find(clientHandler);
        this->clientHandlersMap.erase(iterator);
    }
}

Player *Model::getUserWithName(std::string name)
{
    for (auto iterator = this->players.begin(); iterator != this->players.end(); ++iterator) {
        if ((*iterator)->getName() == name) {
            return *iterator;
        }
    }

    return nullptr;
}