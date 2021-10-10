#pragma once

#include "AbstractPropertyField.hpp"

class SupermarketField : public AbstractPropertyField {
public:
  void action(std::unique_ptr<AbstractPlayer>& player) const {
    std::cout << "Player " << player->getName() << " steps on "
      << m_name << " field and has to pay $" << m_cost  << ". It's " << (m_isBusiness ? "" : "not ") << "a business" << std::endl;
  }

  void deserialize(const json& data) {
    AbstractPropertyField::deserialize(data);

    data.at("isBusiness").get_to(m_isBusiness);
  }

protected:
  bool m_isBusiness = false;
};
