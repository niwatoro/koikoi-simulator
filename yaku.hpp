#ifndef YAKU_HPP
#define YAKU_HPP

#include <string>
#include <vector>

#include "card.hpp"

struct Yaku {
  std::string name;
  int points;
  std::vector<Card*> cards;
};

class YakuCalculator {
 public:
  static std::vector<Yaku> calculateYaku(const std::vector<Card*>& cards);

 private:
  // 五光 (10点) - 光札5枚
  static Yaku checkFiveBrights(const std::vector<Card*>& cards);

  // 四光 (8点) - 光札4枚（雨札を除く）
  // 雨四光 (7点) - 光札4枚（雨札を含む）
  static Yaku checkFourBrights(const std::vector<Card*>& cards);

  // 三光 (5点) - 光札3枚（雨札を除く）
  static Yaku checkThreeBrights(const std::vector<Card*>& cards);

  // 月見で一杯 (5点) - 芒に月・菊に盃の2枚
  static Yaku checkMoonViewing(const std::vector<Card*>& cards);

  // 花見で一杯 (5点) - 桜に幕・菊に盃の2枚
  static Yaku checkCherryBlossomViewing(const std::vector<Card*>& cards);

  // 猪鹿蝶 (5点) - 萩に猪・紅葉に鹿・牡丹に蝶の3枚
  static Yaku checkBoarDeerButterfly(const std::vector<Card*>& cards);

  // 青短 (5点) - 牡丹・菊・紅葉の短冊3枚
  static Yaku checkBlueRibbons(const std::vector<Card*>& cards);

  // 赤短 (5点) - 松・梅・桜の短冊3枚
  static Yaku checkRedRibbons(const std::vector<Card*>& cards);

  // たん (1点) - 短冊札5枚以上
  static Yaku checkRibbons(const std::vector<Card*>& cards);

  // たね (1点) - 種札5枚以上
  static Yaku checkAnimals(const std::vector<Card*>& cards);

  // かす (1点) - カス札10枚以上
  static Yaku checkPlainCards(const std::vector<Card*>& cards);

  // Helper methods
  static bool isBlueRibbon(const Card* card);
  static bool isRedRibbon(const Card* card);
};

#endif  // YAKU_HPP
