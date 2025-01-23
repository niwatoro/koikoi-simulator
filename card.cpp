#include "card.hpp"

#include <algorithm>
#include <chrono>
#include <random>

Card::Card(int month, CardType type, const std::string& name,
           CardIdentifier identifier)
    : month(month), type(type), name(name), identifier(identifier) {}

Deck::Deck() { initializeDeck(); }

void Deck::initializeDeck() {
  // Clear existing cards
  for (auto card : cards) {
    delete card;
  }
  cards.clear();

  // Create all 48 cards (4 cards for each of the 12 months)
  // Month 1 (松, Pine)
  cards.push_back(
      new Card(1, CardType::BRIGHT, "松に鶴", CardIdentifier::CRANE_AND_PINE));
  cards.push_back(
      new Card(1, CardType::RIBBON, "松に赤短", CardIdentifier::PINE_RIBBON));
  cards.push_back(
      new Card(1, CardType::PLAIN, "松のカス1", CardIdentifier::PINE_PLAIN_1));
  cards.push_back(
      new Card(1, CardType::PLAIN, "松のカス2", CardIdentifier::PINE_PLAIN_2));

  // Month 2 (梅, Plum Blossom)
  cards.push_back(new Card(2, CardType::ANIMAL, "梅に鴬",
                           CardIdentifier::PLUM_AND_BUSH_WARBLER));
  cards.push_back(
      new Card(2, CardType::RIBBON, "梅に赤短", CardIdentifier::PLUM_RIBBON));
  cards.push_back(
      new Card(2, CardType::PLAIN, "梅のカス1", CardIdentifier::PLUM_PLAIN_1));
  cards.push_back(
      new Card(2, CardType::PLAIN, "梅のカス2", CardIdentifier::PLUM_PLAIN_2));

  // Month 3 (桜, Cherry Blossom)
  cards.push_back(new Card(3, CardType::BRIGHT, "満開の桜に幔幕",
                           CardIdentifier::CURTAIN_AND_CHERRY));
  cards.push_back(
      new Card(3, CardType::RIBBON, "桜に赤短", CardIdentifier::CHERRY_RIBBON));
  cards.push_back(new Card(3, CardType::PLAIN, "桜のカス1",
                           CardIdentifier::CHERRY_PLAIN_1));
  cards.push_back(new Card(3, CardType::PLAIN, "桜のカス2",
                           CardIdentifier::CHERRY_PLAIN_2));

  // Month 4 (藤, Wisteria)
  cards.push_back(new Card(4, CardType::ANIMAL, "藤に時鳥",
                           CardIdentifier::CUCKOO_AND_WISTERIA));
  cards.push_back(new Card(4, CardType::RIBBON, "藤に短冊",
                           CardIdentifier::WISTERIA_RIBBON));
  cards.push_back(new Card(4, CardType::PLAIN, "藤のカス1",
                           CardIdentifier::WISTERIA_PLAIN_1));
  cards.push_back(new Card(4, CardType::PLAIN, "藤のカス2",
                           CardIdentifier::WISTERIA_PLAIN_2));

  // Month 5 (杜若, Iris)
  cards.push_back(new Card(5, CardType::ANIMAL, "杜若に八橋",
                           CardIdentifier::BRIDGE_AND_IRIS));
  cards.push_back(
      new Card(5, CardType::RIBBON, "杜若に短冊", CardIdentifier::IRIS_RIBBON));
  cards.push_back(new Card(5, CardType::PLAIN, "杜若のカス1",
                           CardIdentifier::IRIS_PLAIN_1));
  cards.push_back(new Card(5, CardType::PLAIN, "杜若のカス2",
                           CardIdentifier::IRIS_PLAIN_2));

  // Month 6 (牡丹, Peony)
  cards.push_back(
      new Card(6, CardType::ANIMAL, "花王に蝶", CardIdentifier::BUTTERFLIES));
  cards.push_back(new Card(6, CardType::RIBBON, "牡丹に青短",
                           CardIdentifier::PEONY_RIBBON));
  cards.push_back(new Card(6, CardType::PLAIN, "牡丹のカス1",
                           CardIdentifier::PEONY_PLAIN_1));
  cards.push_back(new Card(6, CardType::PLAIN, "牡丹のカス2",
                           CardIdentifier::PEONY_PLAIN_2));

  // Month 7 (萩, Bush Clover)
  cards.push_back(
      new Card(7, CardType::ANIMAL, "山萩に山猪", CardIdentifier::BOAR));
  cards.push_back(new Card(7, CardType::RIBBON, "萩に短冊",
                           CardIdentifier::BUSH_CLOVER_RIBBON));
  cards.push_back(new Card(7, CardType::PLAIN, "萩のカス1",
                           CardIdentifier::BUSH_CLOVER_PLAIN_1));
  cards.push_back(new Card(7, CardType::PLAIN, "萩のカス2",
                           CardIdentifier::BUSH_CLOVER_PLAIN_2));

  // Month 8 (芒, Susuki Grass)
  cards.push_back(
      new Card(8, CardType::BRIGHT, "芒に望月", CardIdentifier::MOON));
  cards.push_back(
      new Card(8, CardType::ANIMAL, "芒に雁", CardIdentifier::GEESE));
  cards.push_back(new Card(8, CardType::PLAIN, "芒のカス1",
                           CardIdentifier::SUSUKI_PLAIN_1));
  cards.push_back(new Card(8, CardType::PLAIN, "芒のカス2",
                           CardIdentifier::SUSUKI_PLAIN_2));

  // Month 9 (菊, Chrysanthemum)
  cards.push_back(
      new Card(9, CardType::ANIMAL, "菊に盃", CardIdentifier::SAKE_CUP));
  cards.push_back(new Card(9, CardType::RIBBON, "菊に青短",
                           CardIdentifier::CHRYSANTHEMUM_RIBBON));
  cards.push_back(new Card(9, CardType::PLAIN, "菊のカス1",
                           CardIdentifier::CHRYSANTHEMUM_PLAIN_1));
  cards.push_back(new Card(9, CardType::PLAIN, "菊のカス2",
                           CardIdentifier::CHRYSANTHEMUM_PLAIN_2));

  // Month 10 (紅葉, Maple)
  cards.push_back(
      new Card(10, CardType::ANIMAL, "楓に鹿", CardIdentifier::DEER));
  cards.push_back(new Card(10, CardType::RIBBON, "紅葉に青短",
                           CardIdentifier::MAPLE_RIBBON));
  cards.push_back(new Card(10, CardType::PLAIN, "紅葉のカス1",
                           CardIdentifier::MAPLE_PLAIN_1));
  cards.push_back(new Card(10, CardType::PLAIN, "紅葉のカス2",
                           CardIdentifier::MAPLE_PLAIN_2));

  // Month 11 (柳, Willow)
  cards.push_back(
      new Card(11, CardType::BRIGHT, "柳に小野道風", CardIdentifier::RAINMAN));
  cards.push_back(
      new Card(11, CardType::ANIMAL, "柳に燕", CardIdentifier::SWALLOW));
  cards.push_back(new Card(11, CardType::RIBBON, "柳に短冊",
                           CardIdentifier::WILLOW_RIBBON));
  cards.push_back(
      new Card(11, CardType::PLAIN, "柳のカス", CardIdentifier::WILLOW_PLAIN));

  // Month 12 (桐, Paulownia)
  cards.push_back(
      new Card(12, CardType::BRIGHT, "梧桐に鳳凰", CardIdentifier::PHOENIX));
  cards.push_back(new Card(12, CardType::PLAIN, "桐のカス1",
                           CardIdentifier::PAULOWNIA_PLAIN_1));
  cards.push_back(new Card(12, CardType::PLAIN, "桐のカス2",
                           CardIdentifier::PAULOWNIA_PLAIN_2));
  cards.push_back(new Card(12, CardType::PLAIN, "桐のカス3",
                           CardIdentifier::PAULOWNIA_PLAIN_3));
}

void Deck::shuffle() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

Card* Deck::drawCard() {
  if (cards.empty()) {
    return nullptr;
  }
  Card* card = cards.back();
  cards.pop_back();
  return card;
}

void Deck::reset() {
  initializeDeck();
  shuffle();
}
