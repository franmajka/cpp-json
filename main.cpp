#include <iostream>
#include <tuple>

#include "Player.hpp"
#include "StringToClassesMap.hpp"
#include "JsonDeserializer.hpp"

int main() {
  JsonDeserializer deserializer {
    "/home/franmag/workspace/cpp-json/fields.config.json",
    stringToFieldClassMap
  };

  std::unique_ptr<AbstractPlayer> player = std::make_unique<Player>("Olesya");

  for (const auto& field : deserializer.deserialize()) {
    field->action(player);
  }

  return 0;
}
