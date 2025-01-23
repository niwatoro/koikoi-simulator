#ifndef CARD_HPP
#define CARD_HPP

#include <algorithm>
#include <string>
#include <vector>

enum class CardType {
  PLAIN,   // Kasu
  RIBBON,  // Tanzaku
  ANIMAL,  // Tane
  BRIGHT   // Light
};

enum class CardIdentifier {
  // Month 1 (松)
  CRANE_AND_PINE,  // Bright
  PINE_RIBBON,     // Ribbon
  PINE_PLAIN_1,    // Plain
  PINE_PLAIN_2,    // Plain

  // Month 2 (梅)
  PLUM_AND_BUSH_WARBLER,  // Animal
  PLUM_RIBBON,            // Ribbon
  PLUM_PLAIN_1,           // Plain
  PLUM_PLAIN_2,           // Plain

  // Month 3 (桜)
  CURTAIN_AND_CHERRY,  // Bright
  CHERRY_RIBBON,       // Ribbon
  CHERRY_PLAIN_1,      // Plain
  CHERRY_PLAIN_2,      // Plain

  // Month 4 (藤)
  CUCKOO_AND_WISTERIA,  // Animal
  WISTERIA_RIBBON,      // Ribbon
  WISTERIA_PLAIN_1,     // Plain
  WISTERIA_PLAIN_2,     // Plain

  // Month 5 (杜若)
  BRIDGE_AND_IRIS,  // Animal
  IRIS_RIBBON,      // Ribbon
  IRIS_PLAIN_1,     // Plain
  IRIS_PLAIN_2,     // Plain

  // Month 6 (牡丹)
  BUTTERFLIES,    // Animal
  PEONY_RIBBON,   // Ribbon
  PEONY_PLAIN_1,  // Plain
  PEONY_PLAIN_2,  // Plain

  // Month 7 (萩)
  BOAR,                 // Animal
  BUSH_CLOVER_RIBBON,   // Ribbon
  BUSH_CLOVER_PLAIN_1,  // Plain
  BUSH_CLOVER_PLAIN_2,  // Plain

  // Month 8 (芒)
  MOON,            // Bright
  GEESE,           // Animal
  SUSUKI_PLAIN_1,  // Plain
  SUSUKI_PLAIN_2,  // Plain

  // Month 9 (菊)
  SAKE_CUP,               // Animal
  CHRYSANTHEMUM_RIBBON,   // Ribbon
  CHRYSANTHEMUM_PLAIN_1,  // Plain
  CHRYSANTHEMUM_PLAIN_2,  // Plain

  // Month 10 (紅葉)
  DEER,           // Animal
  MAPLE_RIBBON,   // Ribbon
  MAPLE_PLAIN_1,  // Plain
  MAPLE_PLAIN_2,  // Plain

  // Month 11 (柳)
  RAINMAN,        // Bright
  SWALLOW,        // Animal
  WILLOW_RIBBON,  // Ribbon
  WILLOW_PLAIN,   // Plain

  // Month 12 (桐)
  PHOENIX,            // Bright
  PAULOWNIA_PLAIN_1,  // Plain
  PAULOWNIA_PLAIN_2,  // Plain
  PAULOWNIA_PLAIN_3   // Plain
};

class Card {
 public:
  Card(int month, CardType type, const std::string& name,
       CardIdentifier identifier);
  int getMonth() const { return month; }
  CardType getType() const { return type; }
  std::string getName() const { return name; }
  CardIdentifier getIdentifier() const { return identifier; }

  // Static utility function for sorting cards by month
  static void sortByMonth(std::vector<Card*>& cards) {
    std::sort(cards.begin(), cards.end(), [](const Card* a, const Card* b) {
      return a->getMonth() < b->getMonth();
    });
  }

 private:
  int month;                  // 1-12
  CardType type;              // Card category
  std::string name;           // Card name/description
  CardIdentifier identifier;  // Unique card identifier
};

class Deck {
 public:
  Deck();
  void shuffle();
  Card* drawCard();
  void reset();
  bool isEmpty() const { return cards.empty(); }

 private:
  std::vector<Card*> cards;
  void initializeDeck();
};

#endif  // CARD_HPP
