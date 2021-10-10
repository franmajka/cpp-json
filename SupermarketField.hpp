#pragma once

#include "AbstractPropertyField.hpp"

class SupermarketField : public AbstractPropertyField {
public:
  SET_SERIALIZABLE

  void action(std::unique_ptr<AbstractPlayer>& player) const {
    std::cout << "Player " << player->getName() << " steps on "
      << m_name << " field and has to pay $" << m_cost  << ". It's " << (m_isBusiness ? "" : "not ") << "a business" << std::endl;
  }

protected:
  bool m_isBusiness = false;
  constexpr static auto properties = std::tuple_cat(AbstractPropertyField::properties, std::make_tuple(
    property("isBusiness", &SupermarketField::m_isBusiness)
  ));
};
