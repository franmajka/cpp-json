#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "libs/json.hpp"

#include "AbstractField.hpp"
#include "SupermarketField.hpp"
#include "ElectronicsField.hpp"

using fields_map = std::unordered_map<std::string, field_ptr (*)(json)>;

fields_map stringToFieldClassMap{
  {"SupermarketField", &createInstance<SupermarketField>},
  {"ElectronicsField", &createInstance<ElectronicsField>},
};
