//
// Created by Jakub Dębski on 18.02.18.
//

#ifndef POKERGAME_TABLE_H
#define POKERGAME_TABLE_H

#include "Deck.h"
#include "Pot.h"
#include "Player.h"
#include "CardAnalyzer.h"

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
    std::list<Card *>cards;
    Player *dealer;
    Player *bigBlindPlayer;
    Player *currentPlayer;
    unsigned int toCall;
    bool roundCouldFinish;

    CardAnalyzer cardAnalyzer;

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
    bool isEverybodyFolded();
    bool isRoundCouldFinish();
    void setNextTurn();
    void addBetsToPot();
    void dealCardsToTable();
    Player *selectWinner();
    void checkPlayersHand();
    void payPrize(Player *player);
    Player *getNextPlayer(Player *player);
    void removeCards();
    bool isGameCouldFinish();

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
    bool removePlayer(Player *player);
    RoundStatus getRoundStatus() const;

    bool raise(Player *player, int chips);
    bool fold(Player *player);
    bool call(Player *player);

    void startNextRound();

    DummyTableView *getTableView(Player *player) const;
};


#endif //POKERGAME_TABLE_H
