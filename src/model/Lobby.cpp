//
// Created by kuba on 20.03.18.
//

#include "Lobby.h"

void Lobby::createTable(const std::string &name, int maxPlayers)
{
    Table *table = new Table(name, maxPlayers);
    this->tables.push_front(table);
}

void Lobby::joinTable(const std::string &name, Player *player)
{
    for (auto const& table : this->tables) {
        if (table->getName() == name) {
            table->addPlayer(player);
            this->playersMap[player] = table;
        }
    }
}

void Lobby::leaveTable(const std::string &name, Player *player)
{
    /* TODO: Remove from table */
    /* TODO: Remove from playersMap */
}

void Lobby::deleteTable(const std::string &name)
{
    /* TODO: Delete table */
}

const std::list<Table *> &Lobby::getTables() const {
    return this->tables;
}

DummyLobbyView *Lobby::getLobbyView() const
{
    auto *dummyLobbyView = new DummyLobbyView();

    for (auto &table : this->tables) {
        DummyTableInfo *dummyTableInfo;

        dummyTableInfo = dummyLobbyView->add_tables();
        dummyTableInfo->set_name(table->getName());
        dummyTableInfo->set_maxplayers((uint32_t)table->getMaxPlayers());
        dummyTableInfo->set_players((uint32_t)table->getCurrentPlayers());
    }

    return dummyLobbyView;
}

Table *Lobby::getTableByName(const std::string &name) const
{
    for (auto &table : this->tables) {
        if (table->getName() == name) {
            return table;
        }
    }

    return nullptr;
}

Table *Lobby::getTableByPlayer(Player *player) const
{
    return this->playersMap.at(player);
}
