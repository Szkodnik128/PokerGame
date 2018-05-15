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
        this->playersMap[player] = clientHandler;
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
            this->playersMap[player] = clientHandler;
            /* Set as logged in */
            clientHandler->setLoggedIn(true);
            /* Mark as connected */
            player->setConnected(true);
        }
    }

    if (player->isPlaying()) {
        /* Player was reconnected, send tableView */
        dummyTableView = this->lobby.getTableByPlayer(player)->getTableView(player);
        this->playersMap[player]->sendResponseMessage(dummyTableView, Response::PayloadCase::kTableView);
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
    DummyTableView *dummyTableView;

    std::cout << "createTable" << std::endl;

    /* Get player */
    player = clientHandlersMap[clientHandler];

    /* Create table */
    this->lobby.createTable(createTable.name(), createTable.maxplayers());

    /* Add player to table */
    this->lobby.joinTable(createTable.name(), player);

    /* Send tableView to players in table */
    auto table = this->lobby.getTableByName(createTable.name());
    auto players = table->getPlayers();
    for (auto const&tablePlayer : players) {
        dummyTableView = table->getTableView(tablePlayer);
        this->playersMap[tablePlayer]->sendResponseMessage(dummyTableView, Response::PayloadCase::kTableView);
    }

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
    DummyTableView *dummyTableView;

    std::cout << "joinTable" << std::endl;

    /* Get player */
    player = clientHandlersMap[clientHandler];

    /* Join table */
    this->lobby.joinTable(joinTable.name(), player);

    /* Send tableView to players in table */
    auto table = this->lobby.getTableByName(joinTable.name());
    auto players = table->getPlayers();
    for (auto const&tablePlayer : players) {
        dummyTableView = table->getTableView(tablePlayer);
        this->playersMap[tablePlayer]->sendResponseMessage(dummyTableView, Response::PayloadCase::kTableView);
    }

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
    DummyTableView *dummyTableView;

    std::cout << "leaveTable" << std::endl;

    /* Get player */
    player = clientHandlersMap[clientHandler];

    /* Leave table */
    this->lobby.leaveTable(leaveTable.name(), player);

    /* Send tableView to players in table */
    auto table = this->lobby.getTableByName(leaveTable.name());
    auto players = table->getPlayers();
    for (auto const&tablePlayer : players) {
        dummyTableView = table->getTableView(tablePlayer);
        this->playersMap[tablePlayer]->sendResponseMessage(dummyTableView, Response::PayloadCase::kTableView);
    }

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
    Player *player;
    Table *table;
    DummyTableView *dummyTableView;

    std::cout << "raise" << std::endl;

    player = clientHandlersMap[clientHandler];
    table = this->lobby.getTableByPlayer(player);

    if (table == nullptr) {
        /* Wrong action. Send error */
        clientHandler->sendError(Error::ErrorWrongMessage);
        return;
    } else if (!table->raise(player, raise.chips())) {
        /* Wrong action. Send error */
        clientHandler->sendError(Error::ErrorWrongMessage);
        return;
    }

    /* Send tableView to players in table */
    auto players = table->getPlayers();
    for (auto const&tablePlayer : players) {
        dummyTableView = table->getTableView(tablePlayer);
        this->playersMap[tablePlayer]->sendResponseMessage(dummyTableView, Response::PayloadCase::kTableView);
    }
}

void Model::fold(const Fold &fold, ClientHandler *const clientHandler)
{
    Player *player;
    Table *table;
    DummyTableView *dummyTableView;

    std::cout << "fold" << std::endl;

    player = clientHandlersMap[clientHandler];
    table = this->lobby.getTableByPlayer(player);

    if (table == nullptr) {
        /* Wrong action. Send error */
        clientHandler->sendError(Error::ErrorWrongMessage);
        return;
    } else if (!table->fold(player)) {
        /* Wrong action. Send error */
        clientHandler->sendError(Error::ErrorWrongMessage);
        return;
    }

    /* Send tableView to players in table */
    auto players = table->getPlayers();
    for (auto const&tablePlayer : players) {
        dummyTableView = table->getTableView(tablePlayer);
        this->playersMap[tablePlayer]->sendResponseMessage(dummyTableView, Response::PayloadCase::kTableView);
    }
}

void Model::call(const Call &call, ClientHandler *const clientHandler)
{
    Player *player;
    Table *table;
    DummyTableView *dummyTableView;

    std::cout << "call" << std::endl;

    player = clientHandlersMap[clientHandler];
    table = this->lobby.getTableByPlayer(player);

    if (table == nullptr) {
        /* Wrong action. Send error */
        clientHandler->sendError(Error::ErrorWrongMessage);
        return;
    } else if (!table->call(player)) {
        /* Wrong action. Send error */
        clientHandler->sendError(Error::ErrorWrongMessage);
        return;
    }

    /* Send tableView to players in table */
    auto players = table->getPlayers();
    for (auto const&tablePlayer : players) {
        dummyTableView = table->getTableView(tablePlayer);
        this->playersMap[tablePlayer]->sendResponseMessage(dummyTableView, Response::PayloadCase::kTableView);
    }
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

        /* Remove from maps */
        auto handlersIterator = this->clientHandlersMap.find(clientHandler);
        this->clientHandlersMap.erase(handlersIterator);
        auto playersIterator = this->playersMap.find(player);
        this->playersMap.erase(playersIterator);
    }

    /* TODO: Remove player from table etc. */
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