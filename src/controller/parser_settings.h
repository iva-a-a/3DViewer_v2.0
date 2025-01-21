#pragma once

#include <string>

#include "../view/paint_model.h"
#include "controller.h"

namespace s21 {

class ParserSettings {
 private:
  inline static const std::string filename = "settings.txt";

 public:
  ParserSettings() = default;

  static void saveSettingsToFile(Parameters *p, RenderSetting *s);
  static Parameters getSettingsFromFile(RenderSetting *s);
  static bool checkExistFile();
};
}  // namespace s21