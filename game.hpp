#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <vector>

#include "card.hpp"
#include "player.hpp"
#include "yaku.hpp"

class Game {
 public:
  Game(int numRounds = 12);
  ~Game();

  // Game modes
  void playerVsAI();
  void AIvsAI();

 private:
  // Game state
  Deck deck;
  std::vector<Card*> tableCards;
  std::unique_ptr<Player> player1;
  std::unique_ptr<Player> player2;
  Player* currentPlayer;
  Player* oya;  // Dealer
  int roundsToPlay;
  int currentRound;
  bool koiKoiCalled;

  // Game flow methods
  void initializeRound();
  void dealCards();
  void playRound();
  bool playTurn(Player* player);
  bool handleMatch(Player* player, const std::pair<Card*, Card*>& match);
  void handleDiscard(Player* player, Card* discarded);
  bool checkAndHandleYaku(Player* player);
  void switchCurrentPlayer();
  void cleanupRound();
  void displayGameState() const;

  // Helper methods
  void moveCardToTable(Card* card);
  void removeCardFromTable(Card* card);
  void moveCardToPlayer(Card* card, Player* player);
  std::vector<Card*> findMatchingCards(Card* card) const;
  int calculateFinalScore(Player* player, const std::vector<Yaku>& yakus);
  void displayYaku(const std::vector<Yaku>& yakus) const;
};

#endif  // GAME_HPP
