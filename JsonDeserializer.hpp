#pragma once

#include <memory>
#include <fstream>
#include <vector>
#include <string>

#include "libs/json.hpp"

#include "AbstractField.hpp"
#include "StringToClassesMap.hpp"

template <class Class, template<typename, class> class Map = std::unordered_map>
class JsonDeserializer {
public:
  using class_t = Class;
  using class_ptr = std::unique_ptr<class_t>;
  using ptr_vec = std::vector<class_ptr>;

  using class_name_t = std::string;
  using constructor_func = class_ptr (*)(json);
  using map_t = Map<class_name_t, constructor_func>;

  JsonDeserializer(const std::string& finName, map_t& map) : m_map(map) {
    std::ifstream fin(finName);

    m_json = json::parse(fin);
  }

  ptr_vec deserialize() {
    ptr_vec vec;
    for (const auto& fieldJson : m_json) {
      vec.push_back(deserializeClass(fieldJson));
    }

    return vec;
  }

private:
  json m_json;
  map_t m_map;

  inline class_ptr deserializeClass(json fieldJson) {
    return m_map[fieldJson.at("class").get<std::string>()](fieldJson.at("properties"));
  }
};
