#pragma once

#include <memory>
#include <fstream>
#include <vector>

#include "libs/json.hpp"

#include "AbstractField.hpp"
#include "StringToClassesMap.hpp"

class JsonFieldsDeserializer {
public:
  using fields_vec = std::vector<field_ptr>;

  JsonFieldsDeserializer(const std::string& finName) {
    std::ifstream fin(finName);
    m_json = json::parse(fin);
  }

  fields_vec deserialize() {
    fields_vec vec;
    for (const auto& fieldJson : m_json) {
      vec.push_back(deserializeField(fieldJson));
    }

    return vec;
  }

private:
  json m_json;

  inline field_ptr deserializeField(json fieldJson) {
    return stringToFieldClassMap[fieldJson.at("class").get<std::string>()](fieldJson.at("properties"));
  }
};
