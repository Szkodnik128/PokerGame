//
// Created by Jakub Dębski on 18.02.18.
//

#include "Player.h"

Player::Player(const std::string &name)
        : name(name), connected(false), playing(false)
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

const std::tuple<Card *, Card *> &Player::getHand() const {
    return this->hand;
}

void Player::setHand(const std::tuple<Card *, Card *> &hand) {
    this->hand = hand;
}
