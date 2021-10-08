#pragma once

#include <string>

#include "AbstractPlayer.hpp"

class Player : public AbstractPlayer {
public:
  Player(std::string_view name) : AbstractPlayer(name) {}
  void makeTurn() const {}
};
