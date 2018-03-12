//
// Created by Jakub Dębski on 18.02.18.
//

#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
}

void Player::setHand(std::tuple<Card, Card> hand)
{
    this->hand = hand;
}

std::tuple<Card, Card> Player::getHand()
{
    return hand;
}

void Player::setChips(unsigned int chips)
{
    this->chips = chips;
}

unsigned int Player::getChips()
{
    return this->chips;
}

void Player::setTable(Table *table)
{
    this->table = table;
}

Table *Player::getTable()
{
    return table;
}
