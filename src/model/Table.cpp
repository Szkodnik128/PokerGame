//
// Created by Jakub Dębski on 18.02.18.
//

#include "Table.h"

Table::Table(const std::string &name, int maxPlayers)
        : name(name),
          maxPlayers(maxPlayers),
          currentPlayers(0),
          tableStatus(TableStatus::TableStatusWaitingForPlayers)
{
}

DummyTableView *Table::getTableView(Player *player)
{
    return nullptr;
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


