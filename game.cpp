#include "game.hpp"

#include <algorithm>
#include <iostream>

Game::Game(int numRounds)
    : roundsToPlay(numRounds), currentRound(0), koiKoiCalled(false) {
  deck.shuffle();
}

Game::~Game() { cleanupRound(); }

void Game::playerVsAI() {
  player1 = std::make_unique<Player>("Player", false);
  player2 = std::make_unique<AIPlayer>("AI");
  oya = player1.get();
  currentPlayer = oya;

  while (currentRound < roundsToPlay) {
    currentRound++;
    std::cout << "\n=== Round " << currentRound << " ===\n";
    initializeRound();
    playRound();
    cleanupRound();
  }

  // Display final scores
  std::cout << "\nGame Over!\n";
  std::cout << player1->getName() << "'s final score: " << player1->getScore()
            << "\n";
  std::cout << player2->getName() << "'s final score: " << player2->getScore()
            << "\n";
}

void Game::AIvsAI() {
  player1 = std::make_unique<AIPlayer>("AI 1");
  player2 = std::make_unique<AIPlayer>("AI 2");
  oya = player1.get();
  currentPlayer = oya;

  while (currentRound < roundsToPlay) {
    currentRound++;
    std::cout << "\n=== Round " << currentRound << " ===\n";
    initializeRound();
    playRound();
    cleanupRound();
  }

  // Display final scores
  std::cout << "\nGame Over!\n";
  std::cout << player1->getName() << "'s final score: " << player1->getScore()
            << "\n";
  std::cout << player2->getName() << "'s final score: " << player2->getScore()
            << "\n";
}

void Game::initializeRound() {
  deck.reset();
  deck.shuffle();
  tableCards.clear();
  player1->clearHand();
  player2->clearHand();
  player1->clearCollected();
  player2->clearCollected();
  koiKoiCalled = false;
  dealCards();
}

void Game::dealCards() {
  // Deal 8 cards to each player
  for (int i = 0; i < 8; ++i) {
    player1->addToHand(deck.drawCard());
    player2->addToHand(deck.drawCard());
  }

  // Deal 8 cards to the table
  for (int i = 0; i < 8; ++i) {
    tableCards.push_back(deck.drawCard());
  }

  // Sort all cards by month
  Card::sortByMonth(tableCards);
  Card::sortByMonth(player1->getHandRef());
  Card::sortByMonth(player2->getHandRef());
}

void Game::playRound() {
  while (!deck.isEmpty() || !player1->getHand().empty()) {
    displayGameState();
    bool roundEnded = playTurn(currentPlayer);

    if (roundEnded || (deck.isEmpty() && player1->getHand().empty())) {
      if (!roundEnded) {
        // If round ended naturally with no yaku, oya gets 1 point
        oya->addScore(1);
        std::cout << "No yaku formed. Oya (" << oya->getName()
                  << ") gets 1 point.\n";
      }
      break;
    }

    switchCurrentPlayer();
  }
}

bool Game::playTurn(Player* player) {
  std::cout << "\n" << player->getName() << "'s turn\n";

  // Try to match
  auto match = player->selectMatch(tableCards);
  if (match.first && match.second) {
    if (handleMatch(player, match)) {
      return true;  // Round ends if yaku was formed and player chose not to
                    // koi-koi
    }
  } else {
    // If no match possible or chosen, must discard
    Card* discarded = player->selectDiscard();
    handleDiscard(player, discarded);
  }

  // Draw and play a card if deck is not empty
  if (!deck.isEmpty()) {
    Card* drawn = deck.drawCard();
    std::cout << player->getName() << " drew: " << drawn->getName() << "\n";

    // Check for matches with the drawn card
    auto matchingCards = findMatchingCards(drawn);
    if (!matchingCards.empty()) {
      if (matchingCards.size() == 3) {
        // Collect all four cards of the same month
        std::cout << player->getName() << " matched drawn card "
                  << drawn->getName() << " (Month " << drawn->getMonth()
                  << ") with all three table cards of the same month!\n";
        for (Card* card : matchingCards) {
          removeCardFromTable(card);
          moveCardToPlayer(card, player);
        }
        moveCardToPlayer(drawn, player);
        std::cout << "Collected all cards of month " << drawn->getMonth()
                  << "!\n";

        // Check for yaku after collecting all four cards
        if (checkAndHandleYaku(player)) {
          return true;  // Round ends if yaku was formed and player chose not to
                        // koi-koi
        }
      } else {
        // Let player choose which card to match with
        Card* selectedMatch =
            player->selectMatchingTableCard(matchingCards, drawn);
        if (selectedMatch) {
          std::cout << player->getName() << " matched drawn card "
                    << drawn->getName() << " (Month " << drawn->getMonth()
                    << ") with " << selectedMatch->getName() << " (Month "
                    << selectedMatch->getMonth() << ")\n";

          moveCardToPlayer(drawn, player);
          moveCardToPlayer(selectedMatch, player);
          removeCardFromTable(selectedMatch);

          // Check for yaku after matching cards
          if (checkAndHandleYaku(player)) {
            return true;  // Round ends if yaku was formed and player chose not
                          // to koi-koi
          }
        } else {
          // If no match was selected, put the drawn card on the table
          moveCardToTable(drawn);
        }
      }
    } else {
      moveCardToTable(drawn);
    }
  }

  return false;  // Round continues
}

bool Game::handleMatch(Player* player, const std::pair<Card*, Card*>& match) {
  auto& hand = player->getHandRef();
  auto it = std::find(hand.begin(), hand.end(), match.first);
  if (it != hand.end()) {
    hand.erase(it);
  }

  auto tableIt = std::find(tableCards.begin(), tableCards.end(), match.second);
  if (tableIt != tableCards.end()) {
    tableCards.erase(tableIt);
  }

  // Output matched cards if AI player
  if (player->isAIPlayer()) {
    std::cout << player->getName() << " matched: " << match.first->getName()
              << " (Month " << match.first->getMonth() << ") with "
              << match.second->getName() << " (Month "
              << match.second->getMonth() << ")\n";
  }

  moveCardToPlayer(match.first, player);
  moveCardToPlayer(match.second, player);

  return checkAndHandleYaku(player);
}

void Game::handleDiscard(Player* /* player */, Card* discarded) {
  if (discarded) {
    moveCardToTable(discarded);
  }
}

bool Game::checkAndHandleYaku(Player* player) {
  auto yakus = YakuCalculator::calculateYaku(player->getCollected());
  if (!yakus.empty()) {
    displayYaku(yakus);

    if (!koiKoiCalled) {
      bool callKoiKoi = player->decideKoiKoi();
      if (callKoiKoi) {
        koiKoiCalled = true;
        std::cout << player->getName() << " called Koi-Koi!\n";
        return false;
      }
    }

    int score = calculateFinalScore(player, yakus);
    player->addScore(score);
    std::cout << player->getName() << " scored " << score << " points!\n";
    std::cout << "\nCurrent scores:\n";
    std::cout << player1->getName() << ": " << player1->getScore()
              << " points\n";
    std::cout << player2->getName() << ": " << player2->getScore()
              << " points\n";

    return true;
  }
  return false;
}

void Game::switchCurrentPlayer() {
  currentPlayer =
      (currentPlayer == player1.get()) ? player2.get() : player1.get();
}

void Game::cleanupRound() {
  // Switch oya for next round
  oya = (oya == player1.get()) ? player2.get() : player1.get();
  currentPlayer = oya;
}

void Game::displayGameState() const {
  // Create temporary copies for sorting
  std::vector<Card*> sortedTableCards = tableCards;
  std::vector<Card*> sortedP1Cards = player1->getCollected();
  std::vector<Card*> sortedP2Cards = player2->getCollected();

  Card::sortByMonth(sortedTableCards);
  Card::sortByMonth(sortedP1Cards);
  Card::sortByMonth(sortedP2Cards);

  std::cout << "\nTable cards:\n";
  for (size_t i = 0; i < sortedTableCards.size(); ++i) {
    std::cout << i + 1 << ". " << sortedTableCards[i]->getName() << " (Month "
              << sortedTableCards[i]->getMonth() << ")\n";
  }

  // Display collected cards for both players
  player1->displayCollectedCards();
  player2->displayCollectedCards();
}

void Game::moveCardToTable(Card* card) {
  if (card) {
    tableCards.push_back(card);
    Card::sortByMonth(tableCards);
  }
}

void Game::removeCardFromTable(Card* card) {
  auto it = std::find(tableCards.begin(), tableCards.end(), card);
  if (it != tableCards.end()) {
    tableCards.erase(it);
  }
}

void Game::moveCardToPlayer(Card* card, Player* player) {
  if (card && player) {
    player->addToCollected(card);
    Card::sortByMonth(player->getCollectedRef());
  }
}

std::vector<Card*> Game::findMatchingCards(Card* card) const {
  std::vector<Card*> matches;
  if (card) {
    for (Card* tableCard : tableCards) {
      if (tableCard->getMonth() == card->getMonth()) {
        matches.push_back(tableCard);
      }
    }
  }
  return matches;
}

int Game::calculateFinalScore(Player* player, const std::vector<Yaku>& yakus) {
  int baseScore = 0;
  for (const auto& yaku : yakus) {
    baseScore += yaku.points;
  }

  // Apply multipliers
  int finalScore = baseScore;
  if (baseScore >= 7) {
    finalScore *= 2;  // Double score for 7+ points
  }
  if (koiKoiCalled) {
    if (player == currentPlayer) {
      finalScore *= 2;  // Double score for winning after calling koi-koi
    } else {
      finalScore *= 4;  // Quadruple score for opponent winning after koi-koi
    }
  }

  return finalScore;
}

void Game::displayYaku(const std::vector<Yaku>& yakus) const {
  std::cout << "\nYaku formed:\n";
  for (const auto& yaku : yakus) {
    std::cout << "- " << yaku.name << " (" << yaku.points << " points)\n";
  }
}
