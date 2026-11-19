#pragma once
#include <string>

#include "Inventory.hpp"
class Helmet : public InventoryItem {
 public:
  Helmet(const std::string& id, const std::string& name)
      : InventoryItem(id, name) {}
  const std::string& inventoryId() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override { return id_ + " " + name_; }
};
class Dock : public InventoryItem, public EnergyConsumer {
 public:
  Dock(const std::string& id, const std::string& name, double energy)
      : InventoryItem(id, name), EnergyConsumer(energy) {}
  const std::string& inventoryId() const override { return id_; }
  const std::string& name() const override { return name_; }
  std::string describe() const override { return id_ + " " + name_; }
  const EnergyConsumer* energyConsumer() const override { return this; }
  double dailyEnergy() const override { return energy_; }
};