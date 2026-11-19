#pragma once
#include <string>

#include "Errors.hpp"
#include "Transport.hpp"
class ServiceCenter {
 public:
  void inspect(const Transport& transport) const {
    std::string check = transport.name();
    for (char& c : check) {
      if (c >= 'A' && c <= 'Z') {
        c = static_cast<char>(c - 'A' + 'a');
      }
    }
    if (check.find("broken") != std::string::npos) {
      throw InspectionRejectedError("inspection rejected");
    }
  }
};