//
// Created by Jakub Dębski on 18.02.18.
//

#include "Deck.h"

#include <vector>
#include <chrono>
#include <random>
#include <algorithm>


Deck::Deck()
{
    Card *card;
    CardSuit suit;
    CardValue value;

    for (int s=1; s<=4; s++) {
        suit = static_cast<CardSuit>(s);

        for (int v=2; v<=14; v++) {
            value = static_cast<CardValue>(v);

            card = new Card(value, suit);
            this->cards.push_front(card);
        }
    }

    this->shuffle();
}

void Deck::shuffle()
{
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<Card *> temp(this->cards.begin(), this->cards.end());

    std::shuffle(temp.begin(), temp.end(), std::default_random_engine(seed));
    std::copy(temp.begin(), temp.end(), this->cards.begin());
}

Card *Deck::getCardFromTop()
{
    Card *card;

    /* Check if deck is not empty */
    if (this->cards.empty()) {
        // TODO: Throw exception
        return nullptr;
    }

    /* Take card's pointer from list */
    card = this->cards.front();
    /* Remove card's from list */
    this->cards.pop_front();
    /* Add card to taken list */
    this->taken.push_front(card);

    return card;
}

size_t Deck::getDeckSize()
{
    return this->cards.size();
}

void Deck::restartDeck()
{
    while (!this->taken.empty()) {
        this->cards.push_front(this->taken.front());
        this->taken.pop_front();
    }
};