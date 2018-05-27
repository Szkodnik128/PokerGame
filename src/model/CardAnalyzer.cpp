//
// Created by Jakub Dębski on 27.05.18.
//

#include <iostream>

#include "CardAnalyzer.h"

CardSet *CardAnalyzer::analyzeCardSet(std::list<Card *> tableCards, std::tuple<Card *, Card *> playerCard)
{
    auto *cardSet = new CardSet();

    /* Add cards from table */
    for (auto &card : tableCards) {
        cardSet->addCard(card);
    }

    /* Add cards from player */
    cardSet->addCard(std::get<0>(playerCard));
    cardSet->addCard(std::get<1>(playerCard));

    /* Sort cards */
    cardSet->sortCards();

    if (isStraightFlush(cardSet)) {
    } else if (isFourOfAKind(cardSet)) {
    } else if (isFullHouse(cardSet)) {
    } else if (isFlush(cardSet)) {
    } else if (isStraight(cardSet)) {
    } else if (isThreeOfAKind(cardSet)) {
    } else if (isTwoPairs(cardSet)) {
    } else if (isPair(cardSet)) {
    } else if (isHighCard(cardSet)) {
    } else {
        return nullptr;
    }

    return cardSet;
}

bool CardAnalyzer::isStraightFlush(CardSet *cardSet)
{
    Card *flushCard, *straightCard;
    std::list<Card *> cards = cardSet->getCards();

    /* Check flush */
    flushCard = checkFlush(cards);
    if (flushCard == nullptr) {
        return false;
    }

    /* Remove cards with different suit */
    for (auto iterator = cards.begin(); iterator != cards.end(); ++iterator) {
        if ((*iterator)->getCardSuit() == flushCard->getCardSuit()) {
            iterator = cards.erase(iterator);
        }
    }

    /* Check straight */
    straightCard = checkStraight(cards);
    if (straightCard == nullptr) {
        return false;
    }

    cardSet->setCardSetCategory(STRAIGHT_FLUSH);

    cards = cardSet->getCards();
    for (auto &card : cards) {
        if (card->getCardSuit() == flushCard->getCardSuit()) {
            continue;
        }

        cardSet->removeCard(card);
    }

    cards = cardSet->getCards();
    for (auto &card : cards) {
        if (card->getCardValue() == straightCard->getCardValue() ||
            card->getCardValue() == straightCard->getCardValue() - 1 ||
            card->getCardValue() == straightCard->getCardValue() - 2 ||
            card->getCardValue() == straightCard->getCardValue() - 3 ||
            card->getCardValue() == straightCard->getCardValue() - 4 ||
            (straightCard->getCardValue() == 5 && card->getCardValue() == 14)) {
            continue;
        }

        cardSet->removeCard(card);
    }

    /* TODO: Check if size == 5 or remove doubles */

    return true;
}

bool CardAnalyzer::isFourOfAKind(CardSet *cardSet)
{
    Card *fourOfAKindCard;
    std::list<Card *> cards = cardSet->getCards();

    fourOfAKindCard = checkFourOfAKind(cards);
    if (fourOfAKindCard == nullptr) {
        return false;
    }

    cardSet->setCardSetCategory(FOUR_OF_A_KIND);

    int skipped_cards = 0;
    for (auto &card : cards) {
        if (card->getCardValue() == fourOfAKindCard->getCardValue()) {
            continue;
        }

        if (skipped_cards == 1) {
            cardSet->removeCard(card);
        } else {
            skipped_cards += 1;
            continue;
        }
    }


    return true;
}

bool CardAnalyzer::isFullHouse(CardSet *cardSet)
{
    Card *pairCard, *threeOfAKindCard;
    std::list<Card *> cards = cardSet->getCards();

    threeOfAKindCard = checkThreeOfAKind(cards);
    if (threeOfAKindCard == nullptr) {
        return false;
    }

    /* Remove from cards first pair */
    for (auto iterator = cards.begin(); iterator != cards.end(); ++iterator) {
        if ((*iterator)->getCardValue() == threeOfAKindCard->getCardValue()) {
            iterator = cards.erase(iterator);
        }
    }

    pairCard = checkPair(cards);
    if (pairCard == nullptr) {
        return false;
    }

    cardSet->setCardSetCategory(FULL_HOUSE);

    cards = cardSet->getCards();
    for (auto &card : cards) {
        if (card->getCardValue() == threeOfAKindCard->getCardValue() || card->getCardValue() == pairCard->getCardValue()) {
            continue;
        }

        cardSet->removeCard(card);
    }

    return true;
}

bool CardAnalyzer::isFlush(CardSet *cardSet)
{
    Card *flushCard;
    std::list<Card *> cards = cardSet->getCards();

    flushCard = checkFlush(cards);
    if (flushCard == nullptr) {
        return false;
    }

    cardSet->setCardSetCategory(FLUSH);

    for (auto &card : cards) {
        if (card->getCardSuit() == flushCard->getCardSuit()) {
            continue;
        }

        cardSet->removeCard(card);
    }

    while (cardSet->getCards().size() > 5) {
        cardSet->removeLastCard();
    }

    return true;
}

bool CardAnalyzer::isStraight(CardSet *cardSet)
{
    Card *straightCard;
    std::list<Card *> cards = cardSet->getCards();

    straightCard = checkStraight(cards);
    if (straightCard == nullptr) {
        return false;
    }

    cardSet->setCardSetCategory(STRAIGHT);

    cards = cardSet->getCards();
    for (auto &card : cards) {
        if (card->getCardValue() == straightCard->getCardValue() ||
            card->getCardValue() == straightCard->getCardValue() - 1 ||
            card->getCardValue() == straightCard->getCardValue() - 2 ||
            card->getCardValue() == straightCard->getCardValue() - 3 ||
            card->getCardValue() == straightCard->getCardValue() - 4 ||
            (straightCard->getCardValue() == 5 && card->getCardValue() == 14)) {
            continue;
        }

        cardSet->removeCard(card);
    }

    /* TODO: Check if size == 5 or remove doubles */

    return true;
}

bool CardAnalyzer::isThreeOfAKind(CardSet *cardSet)
{
    Card *threeOfAKindCard;
    std::list<Card *> cards = cardSet->getCards();

    threeOfAKindCard = checkThreeOfAKind(cardSet->getCards());
    if (threeOfAKindCard == nullptr) {
        return false;
    }

    cardSet->setCardSetCategory(THREE_OF_A_KIND);

    int skipped_cards = 0;
    for (auto &card : cards) {
        if (card->getCardValue() == threeOfAKindCard->getCardValue()) {
            continue;
        }

        if (skipped_cards == 2) {
            cardSet->removeCard(card);
        } else {
            skipped_cards += 1;
            continue;
        }
    }

    return true;
}

bool CardAnalyzer::isTwoPairs(CardSet *cardSet)
{
    Card *firstPairCard, *secondPairCard;
    std::list<Card *> cards = cardSet->getCards();

    firstPairCard = checkPair(cards);
    if (firstPairCard == nullptr) {
        return false;
    }

    /* Remove from cards first pair */
    for (auto iterator = cards.begin(); iterator != cards.end(); ++iterator) {
        if ((*iterator)->getCardValue() == firstPairCard->getCardValue()) {
            iterator = cards.erase(iterator);
        }
    }

    secondPairCard = checkPair(cards);
    if (secondPairCard == nullptr) {
        return false;
    }

    cardSet->setCardSetCategory(TWO_PAIRS);

    cards = cardSet->getCards();
    int skipped_cards = 0;
    for (auto &card : cards) {
        if (card->getCardValue() == firstPairCard->getCardValue() || card->getCardValue() == secondPairCard->getCardValue()) {
            continue;
        }

        if (skipped_cards == 1) {
            cardSet->removeCard(card);
        } else {
            skipped_cards += 1;
            continue;
        }
    }

    return true;
}

bool CardAnalyzer::isPair(CardSet *cardSet)
{
    Card *pairCard;
    std::list<Card *> cards = cardSet->getCards();

    pairCard = checkPair(cards);
    if (pairCard == nullptr) {
        return false;
    }

    cardSet->setCardSetCategory(PAIR);

    int skipped_cards = 0;
    for (auto &card : cards) {
        if (card->getCardValue() == pairCard->getCardValue()) {
            continue;
        }

        if (skipped_cards == 3) {
            cardSet->removeCard(card);
        } else {
            skipped_cards += 1;
            continue;
        }
    }

    return true;
}

bool CardAnalyzer::isHighCard(CardSet *cardSet)
{
    std::list<Card *> cards = cardSet->getCards();

    cardSet->setCardSetCategory(HIGH_CARD);

    int skipped_cards = 0;
    for (auto &card : cards) {
        if (skipped_cards == 5) {
            cardSet->removeCard(card);
        } else {
            skipped_cards += 1;
            continue;
        }
    }

    return true;
}

Card *CardAnalyzer::checkFlush(const std::list <Card *>cards)
{
    int counter;

    for (int suit = 0; suit < 3; suit++) {
        counter = 0;
        for (auto &card : cards) {
            if (card->getCardSuit() == suit) {
                counter++;
            }

            if (counter == 5) {
                return card;
            }
        }
    }

    return nullptr;
}

Card *CardAnalyzer::checkStraight(const std::list<Card *> cards)
{
    Card *cards_array[cards.size()];
    int i = 0;

    for (auto &card : cards) {
        cards_array[i] = card;
        i++;
    }

    for (i = 0; i < cards.size() - 4; i++) {
        if (cards_array[i]->getCardValue() == cards_array[i + 1]->getCardValue() + 1 &&
            cards_array[i + 1]->getCardValue() == cards_array[i + 2]->getCardValue() + 1 &&
            cards_array[i + 2]->getCardValue() == cards_array[i + 3]->getCardValue() + 1 &&
            cards_array[i + 3]->getCardValue() == cards_array[i + 4]->getCardValue() + 1) {
            return cards_array[i];
        }

        if (cards_array[0]->getCardValue() == 14 &&
            cards_array[i + 1]->getCardValue() == cards_array[i + 2]->getCardValue() + 1 &&
            cards_array[i + 2]->getCardValue() == cards_array[i + 3]->getCardValue() + 1 &&
            cards_array[i + 3]->getCardValue() == cards_array[i + 4]->getCardValue() + 1 &&
            cards_array[i + 4]->getCardValue() == 2) {
            return cards_array[i + 1];
        }
    }

    return nullptr;
}

Card *CardAnalyzer::checkFourOfAKind(const std::list <Card *>cards)
{
    int counter;

    for (int value = 14; value > 1; value--) {
        counter = 0;
        for (auto &card : cards) {
            if (card->getCardValue() == value) {
                counter++;
            }

            if (counter == 4) {
                return card;
            }
        }

    }

    return nullptr;
}

Card *CardAnalyzer::checkThreeOfAKind(const std::list <Card *>cards)
{
    int counter;

    for (int value = 14; value > 1; value--) {
        counter = 0;
        for (auto &card : cards) {
            if (card->getCardValue() == value) {
                counter++;
            }

            if (counter == 3) {
                return card;
            }
        }
    }

    return nullptr;
}

Card *CardAnalyzer::checkPair(const std::list <Card *>cards)
{
    int counter;

    for (int value = 14; value > 1; value--) {
        counter = 0;
        for (auto &card : cards) {
            if (card->getCardValue() == value) {
                counter++;
            }

            if (counter == 2) {
                return card;
            }
        }
    }

    return nullptr;
}