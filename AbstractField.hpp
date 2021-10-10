#pragma once

#include <string>
#include <memory>
#include <tuple>

#include "libs/json.hpp"

#include "AbstractPlayer.hpp"

#include "DeserializableBase.hpp"

class AbstractField : public DeserializableBase {
public:
  using ptr = std::unique_ptr<AbstractField>;

  virtual void action(std::unique_ptr<AbstractPlayer>& player) const = 0;

  virtual void deserialize(const json& data) {
    data.at("id").get_to(m_id);
    data.at("name").get_to(m_name);
  }

public:
  unsigned m_id;
  std::string m_name;
};
