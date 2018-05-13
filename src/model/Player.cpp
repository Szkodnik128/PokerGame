//
// Created by Jakub Dębski on 18.02.18.
//

#include "Player.h"

Player::Player(const std::string &name)
        : name(name), connected(false), playing(false), inTable(false), inGame(false), turn(false), chips(0), bet(0)
{
}

void Player::setChips(unsigned int chips)
{
    this->chips = chips;
}

unsigned int Player::getChips()
{
    return this->chips;
}

const std::string &Player::getName() const {
    return this->name;
}

bool Player::isConnected() const {
    return this->connected;
}

void Player::setConnected(bool connected) {
    this->connected = connected;
}

bool Player::isPlaying() const {
    return this->playing;
}

void Player::setPlaying(bool playing) {
    this->playing = playing;
}

bool Player::isInTable() const {
    return this->inTable;
}

void Player::setInTable(bool inTable) {
    this->inTable = inTable;
}

const std::tuple<Card *, Card *> &Player::getHand() const {
    return this->hand;
}

void Player::setHand(const std::tuple<Card *, Card *> &hand) {
    this->hand = hand;
}

bool Player::isInGame() const {
    return inGame;
}

void Player::setInGame(bool inGame) {
    Player::inGame = inGame;
}

bool Player::isTurn() const {
    return turn;
}

void Player::setTurn(bool turn) {
    Player::turn = turn;
}

unsigned int Player::getBet() const {
    return bet;
}

void Player::setBet(unsigned int bet) {
    Player::bet = bet;
}
