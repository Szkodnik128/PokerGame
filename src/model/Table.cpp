//
// Created by Jakub Dębski on 18.02.18.
//

#include "Table.h"

Table::Table(const std::string &name, int maxPlayers)
        : name(name),
          maxPlayers(maxPlayers),
          currentPlayers(0),
          tableStatus(TableStatus::TableStatusWaitingForPlayers),
          roundStatus(RoundStatus::RoundStatusUnknown)
{
    this->roundHandlerMap[RoundStatusBegining] = &Table::handleBegining;
    this->roundHandlerMap[RoundStatusPreFlop] = &Table::handlePreFlop;
    this->roundHandlerMap[RoundStatusFlop] = &Table::handleFlop;
    this->roundHandlerMap[RoundStatusTurn] = &Table::handleTurn;
    this->roundHandlerMap[RoundStatusRiver] = &Table::handleRiver;
}

const std::string &Table::getName() const {
    return name;
}

const std::list<Player *> &Table::getPlayers() const {
    return players;
}

const Deck &Table::getDeck() const {
    return deck;
}

const Pot &Table::getPot() const {
    return pot;
}

int Table::getMaxPlayers() const {
    return maxPlayers;
}

int Table::getCurrentPlayers() const {
    return currentPlayers;
}

TableStatus Table::getTableStatus() const {
    return tableStatus;
}

bool Table::addPlayer(Player *player) {
    if (this->currentPlayers == this->maxPlayers) {
        return false;
    }

    this->players.push_front(player);
    this->currentPlayers++;
    player->setInTable(true);
    player->setChips(200);

    if (this->currentPlayers == this->maxPlayers) {
        this->tableStatus = TableStatusGameInProgress;
        this->roundStatus = RoundStatusBegining;
        this->dealGame();
    }

    return true;
}

bool Table::raise(Player *player, int chips)
{
    if (this->tableStatus != TableStatusGameInProgress) {
        return false;
    }

    if (player != this->currentPlayer) {
        return false;
    }

    if (player->getChips() < chips) {
        return false;
    } else {
        player->setBet(player->getBet() + chips);
        player->setChips(player->getChips() - chips);
        this->toCall = player->getBet();
    }

    this->dealGame();

    return true;
}

bool Table::fold(Player *player)
{
    if (this->tableStatus != TableStatusGameInProgress) {
        return false;
    }

    if (player != this->currentPlayer) {
        return false;
    }

    player->setInGame(false);

    this->dealGame();

    return true;
}

bool Table::call(Player *player)
{
    unsigned int toCall;

    if (this->tableStatus != TableStatusGameInProgress) {
        return false;
    }

    if (player != this->currentPlayer) {
        return false;
    }

    toCall = this->toCall - player->getBet();

    if (player->getChips() >= toCall) {
        player->setBet(this->toCall);
        player->setChips(player->getChips() - toCall);
    } else {
        player->setBet(player->getBet() + player->getChips());
        player->setChips(0);

    }

    this->dealGame();

    return true;
}

DummyTableView *Table::getTableView(Player *player) const
{
    auto *dummyTableView = new DummyTableView();

    dummyTableView->set_tablestatus(static_cast<DummyTableStatus>(this->tableStatus));
    dummyTableView->set_roundstatus(static_cast<DummyRoundStatus>(this->roundStatus));
    dummyTableView->set_pot(this->pot.getChips()); /* TODO: Add many pots */

    /* cards */
    for (auto &card : this->cards) {
        DummyCard *dummyCard;

        dummyCard = dummyTableView->add_cards();
        dummyCard->set_cardsuit(static_cast<DummyCardSuit>(card->getCardSuit()));
        dummyCard->set_cardvalue(static_cast<DummyCardValue>(card->getCardValue()));
    }

    /* players */
    for (auto &tablePlayer : this->players) {
        DummyPlayer *dummyPlayer;

        dummyPlayer = dummyTableView->add_players();
        dummyPlayer->set_name(tablePlayer->getName());
        dummyPlayer->set_chips(tablePlayer->getChips());
        dummyPlayer->set_dealer(tablePlayer == this->dealer);
        dummyPlayer->set_ingame(tablePlayer->isInGame());
        dummyPlayer->set_turn(tablePlayer->isTurn());
        dummyPlayer->set_bet(tablePlayer->getBet());

        if (tablePlayer == player && this->tableStatus == TableStatus::TableStatusGameInProgress) {
            DummyCard *dummyCard;

            /* First */
            dummyCard = dummyPlayer->add_hand();
            dummyCard->set_cardsuit(static_cast<DummyCardSuit>(std::get<0>(tablePlayer->getHand())->getCardSuit()));
            dummyCard->set_cardvalue(static_cast<DummyCardValue >(std::get<0>(tablePlayer->getHand())->getCardValue()));

            /* Second */
            dummyCard = dummyPlayer->add_hand();
            dummyCard->set_cardsuit(static_cast<DummyCardSuit>(std::get<1>(tablePlayer->getHand())->getCardSuit()));
            dummyCard->set_cardvalue(static_cast<DummyCardValue >(std::get<1>(tablePlayer->getHand())->getCardValue()));
        } else {
            /* TODO: Show cards if roundStatus is End and player didn't fold */
        }

    }

    return dummyTableView;
}

void Table::dealGame()
{
    RoundHandler handler;

    handler = this->roundHandlerMap[this->roundStatus];
    assert(handler != nullptr);
    (this->*handler)();
}

/* Private */

void Table::handleBegining()
{
    std::cout << "handle begining" << std::endl;

    this->deck.shuffle();
    this->pot.zeroChips(); /* It should be already zeroed */

    this->setInGameAllPlayers();
    this->dealCardsForPlayers();
    this->setDealer();
    this->payBlinds();
    this->setFirstTurn();
    this->toCall = 20; /* Big blind */
    this->roundCouldFinish = false;

    /* Change to preflop */
    this->roundStatus = RoundStatusPreFlop;
}

void Table::handlePreFlop()
{
    std::cout << "handle preflop" << std::endl;

    if (isEverybodyFolded()) {
        this->roundStatus = RoundStatusEnd;
        return;
    }

    if (this->currentPlayer == this->bigBlindPlayer) {
        this->roundCouldFinish = true;
    }

    if (this->isRoundCouldFinish()) {
        this->addBetsToPot();
        this->toCall = 0;
        this->setFirstTurn();
        this->roundCouldFinish = false;
        this->roundStatus = RoundStatusFlop;
        this->dealCardsToTable();
    } else {
        this->setNextTurn();
    }
}

void Table::handleFlop()
{
    std::cout << "handle flop" << std::endl;

    if (isEverybodyFolded()) {
        this->roundStatus = RoundStatusEnd;
        return;
    }

    if (this->currentPlayer == this->dealer) {
        this->roundCouldFinish = true;
    }

    if (this->isRoundCouldFinish()) {
        this->addBetsToPot();
        this->toCall = 0;
        this->setFirstTurn();
        this->roundCouldFinish = false;
        this->roundStatus = RoundStatusTurn;
        this->dealCardsToTable();
    } else {
        this->setNextTurn();
    }
}

void Table::handleTurn()
{
    std::cout << "handle turn" << std::endl;

    if (isEverybodyFolded()) {
        this->roundStatus = RoundStatusEnd;
        return;
    }

    if (this->currentPlayer == this->dealer) {
        this->roundCouldFinish = true;
    }

    if (this->isRoundCouldFinish()) {
        this->addBetsToPot();
        this->toCall = 0;
        this->setFirstTurn();
        this->roundCouldFinish = false;
        this->roundStatus = RoundStatusRiver;
        this->dealCardsToTable();
    } else {
        this->setNextTurn();
    }
}

void Table::handleRiver()
{
    std::cout << "handle river" << std::endl;

    if (isEverybodyFolded()) {
        this->roundStatus = RoundStatusEnd;
        return;
    }

    if (this->currentPlayer == this->dealer) {
        this->roundCouldFinish = true;
    }

    if (this->isRoundCouldFinish()) {
        this->addBetsToPot();
        this->toCall = 0;
        this->setFirstTurn();
        this->roundCouldFinish = false;
        this->roundStatus = RoundStatusEnd;
        /* Handle end */
        this->handleEnd();
    } else {
        this->setNextTurn();
    }
}

void Table::handleEnd()
{
    std::cout << "handle end" << std::endl;

    /* TODO: select winner, prize winner, check if whole game ended, call handleBegining */
}

void Table::setInGameAllPlayers()
{
    for (auto &player : this->players) {
        player->setInGame(true);
        player->setPlaying(true); /* Set also playing if it is first round */
    }
}

void Table::dealCardsForPlayers()
{
    for (auto &player : this->players) {
        player->setHand(std::make_tuple(this->deck.getCardFromTop(), this->deck.getCardFromTop()));
    }
}

void Table::setDealer()
{
    if (this->dealer == nullptr) {
        this->dealer = this->players.front();
    } else {
        this->dealer = this->getNextPlayer(this->dealer);
    }
}

void Table::payBlinds()
{
    Player *player;

    /* Small blind */
    player = this->getNextPlayer(this->dealer);
    if (player->getChips() < 10) {
        player->setBet(player->getChips());
        player->setChips(0);
    } else {
        player->setBet(10);
        player->setChips(player->getChips() - 10);
    }

    /* Big blind */
    player = this->getNextPlayer(player);
    this->bigBlindPlayer = player;
    if (player->getChips() < 20) {
        player->setBet(player->getChips());
        player->setChips(0);
    } else {
        player->setBet(20);
        player->setChips(player->getChips() - 20);
    }
}

void Table::setFirstTurn()
{
    Player *player;

    /* Zero turn */
    for (auto &tablePlayer : this->players) {
        tablePlayer->setTurn(false);
    }

    /* Set first player turn */
    if (this->roundStatus == RoundStatusBegining) {
        player = getNextPlayer(this->dealer); /* Small blind */
        player = getNextPlayer(player); /* Big blind */
        player = getNextPlayer(player); /* Turn player */
        player->setTurn(true);
        this->currentPlayer = player;
    } else {
        player = getNextPlayer(this->dealer);
        player->setTurn(true);
        this->currentPlayer = player;
    }
}

Player *Table::getNextPlayer(Player *player)
{
    for (auto iterator = this->players.begin(); iterator != this->players.end(); ++iterator) {

        if (player == *iterator) {
            if (std::next(iterator) == this->players.end()) {
                return *(this->players.begin());
            } else {
                return *(std::next(iterator));
            }
        }
    }

    assert(false);
    return nullptr;
}

bool Table::isEverybodyFolded()
{
    int notFolded = 0;

    for (auto &player : this->players) {
        if (player->isInGame()) {
            notFolded++;
        }
    }

    if (notFolded == 1) {
        return true;
    } else {
        return false;
    }
}

bool Table::isRoundCouldFinish()
{
    if (this->roundCouldFinish == false) {
        return false;
    }

    for (auto &player : this->players) {
        if (player->getBet() != this->toCall && player->getChips() != 0) {
            return false;
        }
    }

    return true;
}

void Table::setNextTurn()
{
    Player *player;

    /* Zero turn */
    this->currentPlayer->setTurn(false);

    this->currentPlayer = this->getNextPlayer(this->currentPlayer);
    this->currentPlayer->setTurn(true);
}

void Table::addBetsToPot()
{
    for (auto &player : this->players) {
        this->pot.addChips(player->getBet());
        player->setBet(0);
    }
}

void Table::dealCardsToTable()
{
    switch (this->roundStatus) {
        case RoundStatusFlop:
            this->cards.insert(this->cards.end(), this->deck.getCardFromTop());
            this->cards.insert(this->cards.end(), this->deck.getCardFromTop());
            this->cards.insert(this->cards.end(), this->deck.getCardFromTop());
            break;
        case RoundStatusTurn:
            this->cards.insert(this->cards.end(), this->deck.getCardFromTop());
            break;
        case RoundStatusRiver:
            this->cards.insert(this->cards.end(), this->deck.getCardFromTop());
            break;
        default:
            break;
    }
}
