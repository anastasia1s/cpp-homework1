#pragma once
#include <ostream>
#include <string>

#include "Errors.hpp"
class EnergyConsumer;
class InventoryItem {
 protected:
  std::string id_;
  std::string name_;

 public:
  InventoryItem(const std::string& id, const std::string& name)
      : id_(id), name_(name) {}
  virtual const std::string& inventoryId() const = 0;
  virtual const std::string& name() const = 0;
  virtual std::string describe() const = 0;
  virtual bool suitableForNovice() const { return false; }
  virtual int noviceScore() const { return -1; }
  bool operator<(const InventoryItem& other) const {
    return inventoryId() < other.inventoryId();
  }
  virtual const EnergyConsumer* energyConsumer() const { return nullptr; }
  virtual ~InventoryItem() = default;
  bool operator==(const InventoryItem& other) const {
    return inventoryId() == other.inventoryId();
  }
  friend std::ostream& operator<<(std::ostream& print,
                                  const InventoryItem& item) {
    print << item.describe();
    return print;
  }
};
class EnergyConsumer {
 protected:
  double energy_;

 public:
  EnergyConsumer(const double energy) : energy_(energy) {
    if (energy_ < 0) {
      throw InvalidArgumentError("negative energy");
    }
  }
  virtual double dailyEnergy() const = 0;
  virtual ~EnergyConsumer() = default;
};