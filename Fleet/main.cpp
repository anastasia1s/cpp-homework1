#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <utility>

#include "Errors.hpp"
#include "Inventory.hpp"
#include "Registry.hpp"
#include "ServiceCenter.hpp"
#include "Things.hpp"
#include "Transport.hpp"
void toLower(std::string& str) {
  for (char& c : str) {
    if (c >= 'A' && c <= 'Z') {
      c = static_cast<char>(c - 'A' + 'a');
    }
  }
}
int main() {
  const int park_size = 100;
  Registry<InventoryItem, park_size> park;
  ServiceCenter service;
  std::string request;
  while (std::cin >> request) {
    toLower(request);
    try {
      if (request == "quit") {
        break;
      } else if (request == "list") {
        park.list();
      } else if (request == "add") {
        std::string type;
        std::string id;
        std::string name;
        if (!(std::cin >> type >> id >> name)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw InvalidArgumentError("invalid input");
        }
        toLower(type);
        if (type == "scooter") {
          double energy;

          int score;
          if (!(std::cin >> energy >> score)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw InvalidArgumentError("invalid input");
          }
          std::unique_ptr<Scooter> scooter =
              std::make_unique<Scooter>(id, name, energy, score);
          service.inspect(*scooter);
          park.add(std::move(scooter));
        } else if (type == "bike") {
          int score;
          if (!(std::cin >> score)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw InvalidArgumentError("invalid input");
          }
          std::unique_ptr<Bike> bike = std::make_unique<Bike>(id, name, score);
          service.inspect(*bike);
          park.add(std::move(bike));
        } else if (type == "ebike") {
          double energy;
          int score;
          if (!(std::cin >> energy >> score)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw InvalidArgumentError("invalid input");
          }
          std::unique_ptr<EBike> ebike =
              std::make_unique<EBike>(id, name, energy, score);
          service.inspect(*ebike);
          park.add(std::move(ebike));
        } else if (type == "helmet") {
          std::unique_ptr<Helmet> helmet = std::make_unique<Helmet>(id, name);
          park.add(std::move(helmet));
        } else if (type == "dock") {
          double energy;
          if (!(std::cin >> energy)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw InvalidArgumentError("invalid input");
          }
          std::unique_ptr<Dock> dock = std::make_unique<Dock>(id, name, energy);
          park.add(std::move(dock));
        } else if (type == "hoverboard") {
          double energy;
          int score;
          if (!(std::cin >> energy >> score)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw InvalidArgumentError("invalid input");
          }
          std::unique_ptr<HoverBoard> hoverboard =
              std::make_unique<HoverBoard>(id, name, energy, score);
          service.inspect(*hoverboard);
          park.add(std::move(hoverboard));
        } else {
          throw InvalidArgumentError("unknown item");
        }
      } else if (request == "novice") {
        park.novice();
      } else if (request == "energy") {
        park.energy();
      } else if (request == "focus") {
        std::string id;
        if (!(std::cin >> id)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw InvalidArgumentError("invalid input");
        }
        park.focus(id);
      } else if (request == "show_focus") {
        park.show_focus();
      } else if (request == "remove") {
        std::string id;
        if (!(std::cin >> id)) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw InvalidArgumentError("invalid input");
        }
        park.remove(id);
      } else if (request == "easy") {
        park.theBestForNovice();
      } else if (request == "information") {
        park.parkInfo();
      } else {
        throw InvalidArgumentError("unknown request");
      }
    } catch (const FleetError& e) {
      std::cout << "error: " << e.what() << "\n";
    }
  }
  return 0;
}