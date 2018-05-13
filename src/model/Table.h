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

/**
 * Round statuses
 */
enum RoundStatus {
    RoundStatusUnknown = 0,
    RoundStatusBegining = 1,
    RoundStatusPreFlop = 2,
    RoundStatusFlop = 3,
    RoundStatusTurn = 4,
    RoundStatusRiver = 5,
    RoundStatusEnd = 6,
};

class Table {

    typedef void (Table::*RoundHandler)();

private:
    std::string name;
    std::list<Player *>players;
    int maxPlayers;
    int currentPlayers;
    enum TableStatus tableStatus;

    /* Valid only when table is in game */
    enum RoundStatus roundStatus;
    Deck deck;
    Pot pot;
    std::string currentPlayerName;
    std::list<Card *>cards;
    Player *dealer;
    int toCheck;

    void dealGame();
    void handleBegining();
    void handlePreFlop();
    void handleFlop();
    void handleTurn();
    void handleRiver();
    void handleEnd();

    void setInGameAllPlayers();
    void dealCardsForPlayers();
    void setDealer();
    void payBlinds();
    void setFirstTurn();

    Player *getNextPlayer(Player *player);

    std::map<RoundStatus, RoundHandler> roundHandlerMap;

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

    bool raise(Player *player, int chips);
    bool fold(Player *player);
    bool call(Player *player);

    DummyTableView *getTableView(Player *player) const;
};


#endif //POKERGAME_TABLE_H
