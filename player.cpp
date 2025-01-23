#include "player.hpp"

#include <algorithm>
#include <iostream>

Player::Player(const std::string& name, bool isAI)
    : name(name), isAI(isAI), score(0) {}

Player::~Player() {
  clearHand();
  clearCollected();
}

void Player::addToHand(Card* card) {
  if (card) {
    hand.push_back(card);
  }
}

void Player::addToCollected(Card* card) {
  if (card) {
    collected.push_back(card);
  }
}

void Player::clearHand() {
  hand.clear();  // Cards are owned by the Deck, so we don't delete them
}

void Player::clearCollected() {
  collected.clear();  // Cards are owned by the Deck, so we don't delete them
}

std::vector<Card*> Player::getCollectedCardsByType(CardType type) const {
  std::vector<Card*> result;
  for (Card* card : collected) {
    if (card->getType() == type) {
      result.push_back(card);
    }
  }
  return result;
}

void Player::displayCollectedCards() const {
  std::cout << "\n" << name << "'s collected cards:\n";

  // Display 光札 (Bright cards)
  std::cout << "光札:\n";
  for (Card* card : getCollectedCardsByType(CardType::BRIGHT)) {
    std::cout << "  " << card->getName() << " (Month " << card->getMonth()
              << ")\n";
  }

  // Display 種札 (Animal cards)
  std::cout << "種札:\n";
  for (Card* card : getCollectedCardsByType(CardType::ANIMAL)) {
    std::cout << "  " << card->getName() << " (Month " << card->getMonth()
              << ")\n";
  }

  // Display 短冊札 (Ribbon cards)
  std::cout << "短冊札:\n";
  for (Card* card : getCollectedCardsByType(CardType::RIBBON)) {
    std::cout << "  " << card->getName() << " (Month " << card->getMonth()
              << ")\n";
  }

  // Display カス札 (Plain cards)
  std::cout << "カス札:\n";
  for (Card* card : getCollectedCardsByType(CardType::PLAIN)) {
    std::cout << "  " << card->getName() << " (Month " << card->getMonth()
              << ")\n";
  }
}

std::vector<std::pair<Card*, Card*>> Player::findPossibleMatches(
    const std::vector<Card*>& tableCards) {
  std::vector<std::pair<Card*, Card*>> matches;
  for (Card* handCard : hand) {
    for (Card* tableCard : tableCards) {
      if (handCard->getMonth() == tableCard->getMonth()) {
        matches.push_back({handCard, tableCard});
      }
    }
  }
  return matches;
}

int Player::evaluateHand(const std::vector<Card*>& cards) {
  int value = 0;
  // Basic evaluation: higher value for Bright and Animal cards
  for (Card* card : cards) {
    switch (card->getType()) {
      case CardType::BRIGHT:
        value += 5;
        break;
      case CardType::ANIMAL:
        value += 3;
        break;
      case CardType::RIBBON:
        value += 2;
        break;
      case CardType::PLAIN:
        value += 1;
        break;
    }
  }
  return value;
}

std::pair<Card*, Card*> Player::selectMatch(
    const std::vector<Card*>& tableCards) {
  // show hand
  std::cout << "\nYour hand:\n";
  for (size_t i = 0; i < hand.size(); ++i) {
    std::cout << "- " << hand[i]->getName() << " (Month " << hand[i]->getMonth()
              << ")\n";
  }

  // Base class implementation for human player
  auto matches = findPossibleMatches(tableCards);
  if (matches.empty()) {
    return {nullptr, nullptr};
  }

  std::cout << "\nPossible matches for " << name << ":\n";
  for (size_t i = 0; i < matches.size(); ++i) {
    std::cout << i + 1 << ". Hand: " << matches[i].first->getName()
              << " (Month " << matches[i].first->getMonth()
              << ") with Table: " << matches[i].second->getName() << " (Month "
              << matches[i].second->getMonth() << ")\n";
  }

  std::cout << "Select match (1-" << matches.size() << ") or 0 to skip: ";
  int choice;
  std::cin >> choice;

  if (choice <= 0 || choice > static_cast<int>(matches.size())) {
    return {nullptr, nullptr};
  }

  std::cout << name << " matched: " << matches[choice - 1].first->getName()
            << " (Month " << matches[choice - 1].first->getMonth() << ") with "
            << matches[choice - 1].second->getName() << " (Month "
            << matches[choice - 1].second->getMonth() << ")\n";

  return matches[choice - 1];
}

Card* Player::selectDiscard() {
  // Base class implementation for human player
  if (hand.empty()) {
    return nullptr;
  }

  std::cout << "\nYour hand:\n";
  for (size_t i = 0; i < hand.size(); ++i) {
    std::cout << i + 1 << ". " << hand[i]->getName() << " (Month "
              << hand[i]->getMonth() << ")\n";
  }

  std::cout << "Select card to discard (1-" << hand.size() << "): ";
  int choice;
  std::cin >> choice;

  if (choice <= 0 || choice > static_cast<int>(hand.size())) {
    return nullptr;
  }

  Card* selected = hand[choice - 1];
  hand.erase(hand.begin() + choice - 1);
  return selected;
}

bool Player::decideKoiKoi() {
  // Base class implementation for human player
  std::cout << "\n"
            << name << ", do you want to call Koi-Koi? (1 for yes, 0 for no): ";
  int choice;
  std::cin >> choice;
  return choice == 1;
}

// AI Player Implementation
AIPlayer::AIPlayer(const std::string& name) : Player(name, true) {}

double AIPlayer::evaluateCardValue(Card* card) {
  double value = 0;
  switch (card->getType()) {
    case CardType::BRIGHT:
      value = 5.0;
      break;
    case CardType::ANIMAL:
      value = 3.0;
      break;
    case CardType::RIBBON:
      value = 2.0;
      break;
    case CardType::PLAIN:
      value = 1.0;
      break;
  }
  return value;
}

double AIPlayer::evaluateMatchValue(Card* handCard, Card* tableCard) {
  return evaluateCardValue(handCard) + evaluateCardValue(tableCard);
}

std::pair<Card*, Card*> AIPlayer::selectMatch(
    const std::vector<Card*>& tableCards) {
  auto matches = findPossibleMatches(tableCards);
  if (matches.empty()) {
    return {nullptr, nullptr};
  }

  // Find the match with the highest combined value
  auto bestMatch = std::max_element(
      matches.begin(), matches.end(), [this](const auto& a, const auto& b) {
        return evaluateMatchValue(a.first, a.second) <
               evaluateMatchValue(b.first, b.second);
      });

  return *bestMatch;
}

Card* AIPlayer::selectDiscard() {
  if (hand.empty()) {
    return nullptr;
  }

  // Find the card with the lowest value to discard
  auto worstCard =
      std::min_element(hand.begin(), hand.end(), [this](Card* a, Card* b) {
        return evaluateCardValue(a) < evaluateCardValue(b);
      });

  Card* selected = *worstCard;
  hand.erase(worstCard);
  return selected;
}

bool AIPlayer::decideKoiKoi() {
  // Simple AI strategy: call Koi-Koi if we have good cards in hand
  int handValue = evaluateHand(hand);
  return handValue >= 8;  // Threshold can be adjusted
}

Card* Player::selectMatchingTableCard(const std::vector<Card*>& matchingCards,
                                      Card* drawnCard) {
  if (matchingCards.empty()) {
    return nullptr;
  }

  std::cout << "\nDrawn card: " << drawnCard->getName() << " (Month "
            << drawnCard->getMonth() << ")\n";
  std::cout << "Select a matching card from the table:\n";
  for (size_t i = 0; i < matchingCards.size(); ++i) {
    std::cout << i + 1 << ". " << matchingCards[i]->getName() << " (Month "
              << matchingCards[i]->getMonth() << ")\n";
  }

  std::cout << "Enter your choice (1-" << matchingCards.size() << "): ";
  int choice;
  std::cin >> choice;

  if (choice <= 0 || choice > static_cast<int>(matchingCards.size())) {
    return nullptr;
  }

  return matchingCards[choice - 1];
}

Card* AIPlayer::selectMatchingTableCard(const std::vector<Card*>& matchingCards,
                                        Card* drawnCard) {
  if (matchingCards.empty()) {
    return nullptr;
  }

  // Select the card with the highest value
  auto bestCard = std::max_element(
      matchingCards.begin(), matchingCards.end(), [this](Card* a, Card* b) {
        return evaluateCardValue(a) < evaluateCardValue(b);
      });

  return *bestCard;
}
