#pragma once

#include <string>
#include <memory>
#include <tuple>

#include "libs/json.hpp"

#include "AbstractPlayer.hpp"

#include "Property.hpp"

class AbstractField {
public:
  virtual void action(std::unique_ptr<AbstractPlayer>& player) const = 0;

public:
  unsigned m_id;
  std::string m_name;

  constexpr static std::tuple properties{
    property("id", &AbstractField::m_id),
    property("name", &AbstractField::m_name),
  };
};

using field_ptr = std::unique_ptr<AbstractField>;

template <class Class>
constexpr field_ptr createInstance(json jProperties) {
  auto ptr = std::make_unique<Class>();

  std::apply([&](auto&&... args) {
    ((jProperties.at(args.name).get_to((*ptr).*args.member)), ...);
  }, Class::properties);

  return ptr;
}
