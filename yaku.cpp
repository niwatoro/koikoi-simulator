#include "yaku.hpp"

#include <algorithm>

std::vector<Yaku> YakuCalculator::calculateYaku(
    const std::vector<Card*>& cards) {
  std::vector<Yaku> yakus;

  // Check each yaku type
  auto fiveBrights = checkFiveBrights(cards);
  if (!fiveBrights.cards.empty()) {
    yakus.push_back(fiveBrights);
  } else {
    auto fourBrights = checkFourBrights(cards);
    if (!fourBrights.cards.empty()) {
      yakus.push_back(fourBrights);
    } else {
      auto threeBrights = checkThreeBrights(cards);
      if (!threeBrights.cards.empty()) {
        yakus.push_back(threeBrights);
      }
    }
  }

  auto redRibbons = checkRedRibbons(cards);
  if (!redRibbons.cards.empty()) {
    yakus.push_back(redRibbons);
  }
  auto blueRibbons = checkBlueRibbons(cards);
  if (!blueRibbons.cards.empty()) {
    yakus.push_back(blueRibbons);
  }

  auto boarDeerButterfly = checkBoarDeerButterfly(cards);
  if (!boarDeerButterfly.cards.empty()) {
    yakus.push_back(boarDeerButterfly);
  }

  auto animals = checkAnimals(cards);
  if (!animals.cards.empty()) {
    yakus.push_back(animals);
  }

  auto ribbons = checkRibbons(cards);
  if (!ribbons.cards.empty()) {
    yakus.push_back(ribbons);
  }

  auto plains = checkPlainCards(cards);
  if (!plains.cards.empty()) {
    yakus.push_back(plains);
  }

  return yakus;
}

Yaku YakuCalculator::checkFiveBrights(const std::vector<Card*>& cards) {
  std::vector<Card*> brights;
  for (Card* card : cards) {
    if (card->getType() == CardType::BRIGHT) {
      brights.push_back(card);
    }
  }

  if (brights.size() == 5) {
    return {"五光", 10, brights};
  }
  return {"", 0, {}};
}

Yaku YakuCalculator::checkFourBrights(const std::vector<Card*>& cards) {
  std::vector<Card*> brights;
  for (Card* card : cards) {
    if (card->getType() == CardType::BRIGHT) {
      brights.push_back(card);
    }
  }

  if (brights.size() == 4) {
    bool hasRainman = false;
    for (Card* card : brights) {
      if (card->getIdentifier() == CardIdentifier::RAINMAN) {
        hasRainman = true;
        break;
      }
    }
    return {hasRainman ? "雨四光" : "四光", hasRainman ? 7 : 8, brights};
  }
  return {"", 0, {}};
}

Yaku YakuCalculator::checkThreeBrights(const std::vector<Card*>& cards) {
  std::vector<Card*> brights;
  for (Card* card : cards) {
    if (card->getType() == CardType::BRIGHT) {
      brights.push_back(card);
    }
  }

  if (brights.size() == 3) {
    return {"三光", 5, brights};
  }
  return {"", 0, {}};
}

Yaku YakuCalculator::checkMoonViewing(const std::vector<Card*>& cards) {
  bool hasMoon = false, hasCup = false;
  std::vector<Card*> moonViewing;

  for (Card* card : cards) {
    if (card->getType() == CardType::PLAIN) {
      auto id = card->getIdentifier();
      if (id == CardIdentifier::MOON) {
        hasMoon = true;
        moonViewing.push_back(card);
      } else if (id == CardIdentifier::SAKE_CUP) {
        hasCup = true;
        moonViewing.push_back(card);
      }
    }
  }

  if (hasMoon && hasCup) {
    return {"月見で一杯", 5, moonViewing};
  }
  return {"", 0, {}};
}

Yaku YakuCalculator::checkCherryBlossomViewing(
    const std::vector<Card*>& cards) {
  bool hasCurtain = false, hasCup = false;
  std::vector<Card*> cherryBlossomViewing;

  for (Card* card : cards) {
    if (card->getType() == CardType::PLAIN) {
      auto id = card->getIdentifier();
      if (id == CardIdentifier::CHERRY_RIBBON) {
        hasCurtain = true;
        cherryBlossomViewing.push_back(card);
      } else if (id == CardIdentifier::SAKE_CUP) {
        hasCup = true;
        cherryBlossomViewing.push_back(card);
      }
    }
  }

  if (hasCurtain && hasCup) {
    return {"花見で一杯", 5, cherryBlossomViewing};
  }
  return {"", 0, {}};
}

Yaku YakuCalculator::checkBoarDeerButterfly(const std::vector<Card*>& cards) {
  bool hasBoar = false, hasDeer = false, hasButterfly = false;
  std::vector<Card*> animals;

  for (Card* card : cards) {
    if (card->getType() == CardType::ANIMAL) {
      auto id = card->getIdentifier();
      if (id == CardIdentifier::BOAR) {
        hasBoar = true;
        animals.push_back(card);
      } else if (id == CardIdentifier::DEER) {
        hasDeer = true;
        animals.push_back(card);
      } else if (id == CardIdentifier::BUTTERFLIES) {
        hasButterfly = true;
        animals.push_back(card);
      }
    }
  }

  if (hasBoar && hasDeer && hasButterfly) {
    return {"猪鹿蝶", 5, animals};
  }
  return {"", 0, {}};
}

bool YakuCalculator::isRedRibbon(const Card* card) {
  if (card->getType() != CardType::RIBBON) return false;
  auto id = card->getIdentifier();
  return id == CardIdentifier::WISTERIA_RIBBON ||
         id == CardIdentifier::IRIS_RIBBON ||
         id == CardIdentifier::BUSH_CLOVER_RIBBON ||
         id == CardIdentifier::WILLOW_RIBBON;
}

Yaku YakuCalculator::checkRedRibbons(const std::vector<Card*>& cards) {
  std::vector<Card*> redRibbons;
  for (Card* card : cards) {
    if (isRedRibbon(card)) {
      redRibbons.push_back(card);
    }
  }

  if (redRibbons.size() == 3) {
    return {"Red Ribbons", 5, redRibbons};
  }
  return {"", 0, {}};
}

bool YakuCalculator::isBlueRibbon(const Card* card) {
  if (card->getType() != CardType::RIBBON) return false;
  auto id = card->getIdentifier();
  return id == CardIdentifier::PEONY_RIBBON ||
         id == CardIdentifier::CHRYSANTHEMUM_RIBBON ||
         id == CardIdentifier::MAPLE_RIBBON;
}

Yaku YakuCalculator::checkBlueRibbons(const std::vector<Card*>& cards) {
  std::vector<Card*> blueRibbons;
  for (Card* card : cards) {
    if (isBlueRibbon(card)) {
      blueRibbons.push_back(card);
    }
  }

  if (blueRibbons.size() == 3) {
    return {"青短", 5, blueRibbons};
  }
  return {"", 0, {}};
}

Yaku YakuCalculator::checkAnimals(const std::vector<Card*>& cards) {
  std::vector<Card*> animals;
  for (Card* card : cards) {
    if (card->getType() == CardType::ANIMAL) {
      animals.push_back(card);
    }
  }

  if (animals.size() >= 5) {
    return {"たね", (int)animals.size() - 4, animals};
  }
  return {"", 0, {}};
}

Yaku YakuCalculator::checkRibbons(const std::vector<Card*>& cards) {
  std::vector<Card*> ribbons;
  for (Card* card : cards) {
    if (card->getType() == CardType::RIBBON) {
      ribbons.push_back(card);
    }
  }

  if (ribbons.size() >= 5) {
    return {"たん", (int)ribbons.size() - 4, ribbons};
  }
  return {"", 0, {}};
}

Yaku YakuCalculator::checkPlainCards(const std::vector<Card*>& cards) {
  std::vector<Card*> plains;
  for (Card* card : cards) {
    if (card->getType() == CardType::PLAIN) {
      plains.push_back(card);
    }
  }

  if (plains.size() >= 10) {
    return {"かす", 1, plains};
  }
  return {"", 0, {}};
}
