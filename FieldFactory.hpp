#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <type_traits>

#include "libs/json.hpp"

#include "AbstractField.hpp"
#include "SupermarketField.hpp"
#include "ElectronicsField.hpp"

class FieldFactory {
public:
  using type = AbstractField;
  using ptr = std::unique_ptr<type>;
  using create_func_t = ptr (*)(const json&);
  using map = std::unordered_map<std::string, create_func_t>;

  template <class Derived>
  void registerType(const std::string& name) {
    static_assert(
      std::is_base_of<type, Derived>::value,
      "FieldFactory::registerType doesn't accept this type because doesn't derive from base class"
    );

    m_map[name] = &createFunc<Derived>;
  }

  ptr create(const json& data) {
    std::string className = data["class"];
    auto it = m_map.find(className);
    if (it == m_map.end()) return nullptr;

    return it->second(data["properties"]);
  }

  static FieldFactory& getInstance() {
    static FieldFactory instance;

    return instance;
  }

private:
  template <class Derived>
  static ptr createFunc(const json& data) {
    std::unique_ptr<Derived> tmp = std::make_unique<Derived>();
    tmp->deserialize(data);
    return tmp;
  }

  FieldFactory() {
    registerType<SupermarketField>("SupermarketField");
    registerType<ElectronicsField>("ElectronicsField");
  }

  FieldFactory(const FieldFactory &) { }
  FieldFactory &operator=(const FieldFactory &) { return *this; }

  map m_map;
};
