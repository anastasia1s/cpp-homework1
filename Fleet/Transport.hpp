#pragma once
#include <string>

#include "Errors.hpp"
#include "Inventory.hpp"
class Transport : public InventoryItem {
 private:
  static const int cNoviceMax = 6;

 protected:
  int score_;

 public:
  Transport(const std::string& id, const std::string& name, int score)
      : InventoryItem(id, name), score_(score) {
    if (score_ < 1 || score_ > 10) {
      throw InvalidArgumentError("score out of range");
    }
  }
  int noviceScore() const override { return score_; }
  bool suitableForNovice() const override { return score_ >= cNoviceMax; }
};
class Scooter : public Transport, public EnergyConsumer {
 public:
  Scooter(const std::string& id, const std::string& name, double energy,
          int score)
      : Transport(id, name, score), EnergyConsumer(energy) {}
  const std::string& inventoryId() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override { return id_ + " " + name_; }
  double dailyEnergy() const override { return energy_; }
  const EnergyConsumer* energyConsumer() const override { return this; }
};
class Bike : public Transport {
 public:
  Bike(const std::string& id, const std::string& name, int score)
      : Transport(id, name, score) {}
  const std::string& inventoryId() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override { return id_ + " " + name_; }
};
class EBike : public Transport, public EnergyConsumer {
 public:
  EBike(const std::string& id, const std::string& name, double energy,
        int score)
      : Transport(id, name, score), EnergyConsumer(energy) {}
  const std::string& inventoryId() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override { return id_ + " " + name_; }
  double dailyEnergy() const override { return energy_; }
  const EnergyConsumer* energyConsumer() const override { return this; }
};
class HoverBoard : public Transport, public EnergyConsumer {
 public:
  HoverBoard(const std::string& id, const std::string& name, double energy,
             int score)
      : Transport(id, name, score), EnergyConsumer(energy) {}
  const std::string& inventoryId() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override { return id_ + " " + name_; }
  double dailyEnergy() const override { return energy_; }
  const EnergyConsumer* energyConsumer() const override { return this; }
};