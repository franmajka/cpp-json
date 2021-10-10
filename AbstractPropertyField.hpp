#pragma once

#include <iostream>
#include <memory>
#include <tuple>

#include "AbstractField.hpp"
#include "AbstractPlayer.hpp"

#include "Property.hpp"

// Говоря на чистоту сейчас это не абстрактный класс но просто
// на секунду представим что тут есть виртуальные методы которые
// должны быть у поля собственности
class AbstractPropertyField : public AbstractField {
public:
  SET_SERIALIZABLE

  virtual void action(std::unique_ptr<AbstractPlayer>& player) const {
    std::cout << "Player " << player->getName() << " steps on "
      << m_name << " field and has to pay $" << m_cost << std::endl;
  }

protected:
  std::unique_ptr<AbstractPlayer> m_owner = nullptr;
  unsigned m_cost;

  constexpr static auto properties = std::tuple_cat(AbstractField::properties, std::make_tuple(
    property("cost", &AbstractPropertyField::m_cost)
  ));
};
