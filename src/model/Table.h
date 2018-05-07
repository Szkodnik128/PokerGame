//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_TABLE_H
#define POKERGAME_TABLE_H

#include "Deck.h"
#include "Pot.h"
#include "Player.h"

#include <protocol/Protocol.pb.h>

#include <list>

/**
 * Table statuses
 */
enum TableStatus {
    TableStatusUnknown = 0,
    TableStatusWaitingForPlayers = 1,
    TableStatusGameInProgress = 2,
    TableStatusGameEnded = 3,
};

class Table {

private:
    std::string name;
    std::list<Player *>players;
    Deck deck;
    Pot pot;
    int maxPlayers;
    int currentPlayers;
    enum TableStatus tableStatus;

public:
    Table(const std::string &name, int maxPlayers);

    const std::string &getName() const;
    const std::list<Player *> &getPlayers() const;
    const Deck &getDeck() const;
    const Pot &getPot() const;
    int getMaxPlayers() const;
    int getCurrentPlayers() const;
    TableStatus getTableStatus() const;
    bool addPlayer(Player *player);

    DummyTableView *getTableView(Player *player);
};


#endif //POKERGAME_TABLE_H
