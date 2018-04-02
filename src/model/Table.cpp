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


