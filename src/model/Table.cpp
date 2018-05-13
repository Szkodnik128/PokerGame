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

    /* TODO: If all players took a seat the game begins */

    return true;
}

bool Table::raise(Player *player, int chips)
{
    return false;
}

bool Table::fold(Player *player)
{
    return false;
}

bool Table::call(Player *player)
{
    return false;
}

DummyTableView *Table::getTableView(Player *player) const
{
    auto *dummyTableView = new DummyTableView();

    dummyTableView->set_tablestatus(static_cast<DummyTableStatus>(this->tableStatus));
    dummyTableView->set_currentplayername(this->currentPlayerName);
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

        if (tablePlayer == player && this->tableStatus == TableStatus::TableStatusGameInProgress) {
            DummyCard *dummyCard;

            /* First */
            dummyCard = dummyPlayer->add_hand();
            dummyCard->set_cardsuit(static_cast<DummyCardSuit>(std::get<0>(tablePlayer->getHand())->getCardSuit()));
            dummyCard->set_cardvalue(static_cast<DummyCardValue >(std::get<0>(tablePlayer->getHand())->getCardValue()));

            /* Second */
            dummyCard = dummyPlayer->add_hand();
            dummyCard->set_cardsuit(static_cast<DummyCardSuit>(std::get<0>(tablePlayer->getHand())->getCardSuit()));
            dummyCard->set_cardvalue(static_cast<DummyCardValue >(std::get<0>(tablePlayer->getHand())->getCardValue()));
        } else {
            /* TODO: Show cards if roundStatus is End and player didn't fold */
        }

    }

    return dummyTableView;
}


