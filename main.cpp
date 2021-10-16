#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map>

#include "libs/json.hpp"

#include "Player.hpp"

#include "FieldFactory.hpp"

int main() {
  std::vector<AbstractField::ptr> vec;

  std::ifstream fin("fields.config.json");
  json data = json::parse(fin);
  fin.close();

  for (const json& fieldData : data) {
    vec.push_back(FieldFactory::getInstance().create(fieldData));
  }

  std::unique_ptr<AbstractPlayer> player = std::make_unique<Player>("Olesya");

  for (const auto& field : vec) {
    field->action(player);
  }

  return 0;
}
