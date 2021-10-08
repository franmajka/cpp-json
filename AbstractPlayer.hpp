#pragma once

#include <string>

class AbstractPlayer {
public:
  AbstractPlayer(std::string_view name) : m_name(name) {}

  virtual void makeTurn() const = 0;

  std::string getName() { return m_name; }

private:
  std::string m_name;
};
