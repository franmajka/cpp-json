#include <iostream>
#include <tuple>

#include "Player.hpp"
#include "JsonFieldsDeserializer.hpp"

int main() {
  JsonFieldsDeserializer deserializer("/home/franmag/workspace/cpp-json/fields.config.json");
  std::unique_ptr<AbstractPlayer> player = std::make_unique<Player>("Olesya");

  for (const auto& field : deserializer.deserialize()) {
    field->action(player);
  }

  return 0;
}
