#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>

#include "card.hpp"

class Player {
 public:
  Player(const std::string& name, bool isAI = false);
  virtual ~Player();

  // Basic operations
  void addToHand(Card* card);
  void addToCollected(Card* card);
  void clearHand();
  void clearCollected();

  // Getters
  const std::vector<Card*>& getHand() const { return hand; }
  const std::vector<Card*>& getCollected() const { return collected; }
  std::vector<Card*>& getHandRef() { return hand; }
  std::vector<Card*>& getCollectedRef() { return collected; }
  const std::string& getName() const { return name; }
  bool isAIPlayer() const { return isAI; }
  int getScore() const { return score; }

  // Display collected cards by type
  void displayCollectedCards() const;
  std::vector<Card*> getCollectedCardsByType(CardType type) const;

  // Game actions
  virtual std::pair<Card*, Card*> selectMatch(
      const std::vector<Card*>& tableCards);
  virtual Card* selectDiscard();
  virtual bool decideKoiKoi();
  virtual Card* selectMatchingTableCard(const std::vector<Card*>& matchingCards,
                                        Card* drawnCard);

  // Scoring
  void addScore(int points) { score += points; }
  void resetScore() { score = 0; }

 protected:
  std::string name;
  bool isAI;
  std::vector<Card*> hand;
  std::vector<Card*> collected;
  int score;

  // Helper methods for AI
  std::vector<std::pair<Card*, Card*>> findPossibleMatches(
      const std::vector<Card*>& tableCards);
  int evaluateHand(const std::vector<Card*>& cards);
};

class AIPlayer : public Player {
 public:
  AIPlayer(const std::string& name);

  // Override virtual methods with AI logic
  std::pair<Card*, Card*> selectMatch(
      const std::vector<Card*>& tableCards) override;
  Card* selectDiscard() override;
  bool decideKoiKoi() override;
  Card* selectMatchingTableCard(const std::vector<Card*>& matchingCards,
                                Card* drawnCard) override;

 private:
  // AI specific helper methods
  double evaluateMatchValue(Card* handCard, Card* tableCard);
  double evaluateCardValue(Card* card);
};

#endif  // PLAYER_HPP
