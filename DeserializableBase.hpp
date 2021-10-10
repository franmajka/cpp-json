#pragma once

#include <string>
#include <fstream>

#include "libs/json.hpp"

class DeserializableBase {
public:
  virtual void deserializeFile(const std::string& fName) {
    std::ifstream fin(fName);
    json data = json::parse(fin);
    fin.close();

    deserialize(data);
  }

  virtual void deserialize(const json& data) = 0;
};
