#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map>

#include "libs/json.hpp"

#include "Player.hpp"

#include "AbstractField.hpp"
#include "SupermarketField.hpp"
#include "ElectronicsField.hpp"

template <class FieldDerived>
AbstractField::ptr createInstance() {
  return std::make_unique<FieldDerived>();
}

int main() {
  std::unordered_map<std::string, AbstractField::ptr (*)()> map = {
    {"SupermarketField", &createInstance<SupermarketField>},
    {"ElectronicsField", &createInstance<ElectronicsField>},
  };

  std::vector<AbstractField::ptr> vec;

  std::ifstream fin("fields.config.json");
  json data = json::parse(fin);
  fin.close();

  for (const json& fieldData : data) {
    AbstractField::ptr tmp = map[fieldData.at("class")]();
    tmp->deserialize(fieldData.at("properties"));
    vec.push_back(std::move(tmp));
  }


  std::unique_ptr<AbstractPlayer> player = std::make_unique<Player>("Olesya");

  for (const auto& field : vec) {
    field->action(player);
  }

  return 0;
}
