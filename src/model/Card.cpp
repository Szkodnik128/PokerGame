//
// Created by Jakub Dębski on 18.02.18.
//

#include "Card.h"

Card::Card(const CardValue cardValue, const CardSuit cardSuit)
: cardValue(cardValue), cardSuit(cardSuit)
{}

CardValue Card::getCardValue()
{
    return this->cardValue;
}

CardSuit Card::getCardSuit()
{
    return this->cardSuit;
}

bool Card::operator==(const Card& card) const
{
    return this->cardValue == card.cardValue;
}

bool Card::operator<(const Card& card) const
{
    return this->cardValue < card.cardValue;
}

bool Card::operator>(const Card &card) const
{
    return this->cardValue > card.cardValue;
}

bool Card::operator<=(const Card &card) const
{
    return this->cardValue <= card.cardValue;
}

bool Card::operator>=(const Card &card) const
{
    return this->cardValue >= card.cardValue;
}

bool Card::operator!=(const Card &card) const
{
    return this->cardValue != card.cardValue;
}