//
// Created by Jakub Dębski on 27.05.18.
//

#include "CardSet.h"

bool cardSortDescending(const Card *first, const Card *second)
{
    return first >= second;
}

CardSetCategory CardSet::getCardSetCategory() const
{
    return cardSetCategory;
}

const std::list<Card *> &CardSet::getCards() const
{
    return cards;
}

void CardSet::setCardSetCategory(CardSetCategory cardSetCategory)
{
    CardSet::cardSetCategory = cardSetCategory;
}

void CardSet::sortCards()
{
    this->cards.sort(cardSortDescending);
}

void CardSet::addCard(Card *card)
{
    this->cards.push_front(card);
}

void CardSet::removeCard(Card *card)
{
    for (auto iterator = this->cards.begin(); iterator != this->cards.end(); ++iterator) {
        if (*iterator == card) {
            this->cards.erase(iterator);
            break;
        }
    }
}

void CardSet::removeLastCard()
{
    this->cards.pop_back();
}
