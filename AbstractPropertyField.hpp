#pragma once

#include <iostream>
#include <memory>
#include <tuple>

#include "AbstractField.hpp"
#include "AbstractPlayer.hpp"

// ������ �� ������� ������ ��� �� ����������� ����� �� ������
// �� ������� ���������� ��� ��� ���� ����������� ������ �������
// ������ ���� � ���� �������������
class AbstractPropertyField : public AbstractField {
public:
  virtual void action(std::unique_ptr<AbstractPlayer>& player) const {
    std::cout << "Player " << player->getName() << " steps on "
      << m_name << " field and has to pay $" << m_cost << std::endl;
  }

  virtual void deserialize(const json& data) {
    AbstractField::deserialize(data);

    data.at("cost").get_to(m_cost);
  }

protected:
  std::unique_ptr<AbstractPlayer> m_owner = nullptr;
  unsigned m_cost;
};
