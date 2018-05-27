//
// Created by Jakub Dębski on 27.05.18.
//

#ifndef POKERGAME_CARDANALYZER_H
#define POKERGAME_CARDANALYZER_H

#include "CardSet.h"

#include <tuple>
#include <list>

class CardAnalyzer {
private:
    bool isStraightFlush(CardSet *cardSet);
    bool isFourOfAKind(CardSet *cardSet);
    bool isFullHouse(CardSet *cardSet);
    bool isFlush(CardSet *cardSet);
    bool isStraight(CardSet *cardSet);
    bool isThreeOfAKind(CardSet *cardSet);
    bool isTwoPairs(CardSet *cardSet);
    bool isPair(CardSet *cardSet);
    bool isHighCard(CardSet *cardSet);
    Card *checkFlush(const std::list <Card *> cards);
    Card *checkStraight(const std::list<Card *> cards);
    Card *checkFourOfAKind(const std::list <Card *> cards);
    Card *checkThreeOfAKind(const std::list <Card *> cards);
    Card *checkPair(const std::list <Card *> cards);

public:
    CardSet *analyzeCardSet(std::list<Card *> tableCards, std::tuple<Card *, Card *> playerCard);
};


#endif //POKERGAME_CARDANALYZER_H
