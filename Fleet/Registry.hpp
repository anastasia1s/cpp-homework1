#pragma once
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Errors.hpp"
#include "Inventory.hpp"
template <typename T, int Cap>
class Registry {
  static_assert(Cap > 0, "Park capacity must be positive");

 private:
  std::vector<std::shared_ptr<T>> items_;
  std::weak_ptr<T> display_;

 public:
  void add(std::shared_ptr<T>&& item) {
    if (item == nullptr) {
      throw InvalidArgumentError("item is empty");
    }
    if (items_.size() >= static_cast<std::size_t>(Cap)) {
      throw CapacityExceededError("registry is full");
    }
    for (const auto& existing_item : items_) {
      if (*existing_item == *item) {
        throw InventoryIdError("inventory id already exists");
      }
    }
    items_.push_back(std::move(item));
  }
  std::size_t size() const { return items_.size(); }
  T& operator[](std::size_t index) { return *items_.at(index); }
  friend std::ostream& operator<<(std::ostream& print,
                                  const Registry& registry) {
    for (const auto& item : registry.items_) {
      print << *item << "\n";
    }
    return print;
  }
  void list() {
    std::sort(items_.begin(), items_.end(),
              [](const std::shared_ptr<T>& a, const std::shared_ptr<T>& b) {
                return *a < *b;
              });
    std::cout << *this;
  }
  void remove(const std::string& id) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
      if ((*it)->inventoryId() == id) {
        items_.erase(it);
        return;
      }
    }
    throw InvalidArgumentError("item not found");
  }
  void focus(const std::string& id) {
    for (const auto& item : items_) {
      if (item->inventoryId() == id) {
        display_ = item;
        return;
      }
    }
    throw InvalidArgumentError("item not found");
  }
  void show_focus() const {
    auto item = display_.lock();
    if (item == nullptr) {
      std::cout << "removed\n";
      return;
    }
    std::cout << *item << "\n";
  }
  void novice() const {
    for (const auto& item : items_) {
      if (item->suitableForNovice()) {
        std::cout << *item << "\n";
      }
    }
  }
  void energy() const {
    double energy = 0;
    for (const auto& item : items_) {
      const EnergyConsumer* consumer = item->energyConsumer();
      if (consumer != nullptr) {
        energy += consumer->dailyEnergy();
      }
    }
    std::cout << std::fixed;
    std::cout.precision(1);
    std::cout << energy << "\n";
  }
  void theBestForNovice() {
    int max_score = -1;
    for (const auto& item : items_) {
      if (item->noviceScore() > max_score) {
        max_score = item->noviceScore();
      }
    }
    if (max_score < 6) {
      std::cout << "There isn't anything for novice\n";
      return;
    }
    for (const auto& item : items_) {
      if (item->noviceScore() == max_score) {
        std::cout << *item << "\n";
      }
    }
  }
  void parkInfo() {
    std::cout << "Park size: " << size() << "\n";
    energy();
    std::cout << "All items:\n";
    list();
  }
};
template <>
class Registry<InventoryItem, 100> {
 private:
  std::vector<std::shared_ptr<InventoryItem>> items_;
  std::weak_ptr<InventoryItem> display_;
  const int Cap = 100;

 public:
  void add(std::shared_ptr<InventoryItem>&& item) {
    if (item == nullptr) {
      throw InvalidArgumentError("item is empty");
    }
    if (items_.size() >= static_cast<std::size_t>(Cap)) {
      throw CapacityExceededError("registry is full");
    }
    for (const auto& existing_item : items_) {
      if (*item == *existing_item) {
        throw InventoryIdError("inventory id already exists");
      }
    }
    items_.push_back(std::move(item));
  }
  std::size_t size() const { return items_.size(); }
  InventoryItem& operator[](std::size_t index) { return *items_.at(index); }
  friend std::ostream& operator<<(std::ostream& print,
                                  const Registry& registry) {
    for (const auto& item : registry.items_) {
      print << *item << "\n";
    }
    return print;
  }
  void list() {
    std::sort(items_.begin(), items_.end(),
              [](const std::shared_ptr<InventoryItem>& a,
                 const std::shared_ptr<InventoryItem>& b) { return *a < *b; });
    std::cout << *this;
  }
  void remove(const std::string& id) {
    for (auto it = items_.begin(); it != items_.end(); ++it) {
      if ((*it)->inventoryId() == id) {
        items_.erase(it);
        return;
      }
    }
    throw InvalidArgumentError("item not found");
  }
  void focus(const std::string& id) {
    for (const auto& item : items_) {
      if (item->inventoryId() == id) {
        display_ = item;
        return;
      }
    }
    throw InvalidArgumentError("item not found");
  }
  void show_focus() const {
    auto item = display_.lock();
    if (item == nullptr) {
      std::cout << "removed\n";
      return;
    }
    std::cout << *item << "\n";
  }
  void novice() const {
    for (const auto& item : items_) {
      if (item->suitableForNovice()) {
        std::cout << *item << "\n";
      }
    }
  }
  void energy() const {
    double energy = 0;
    for (const auto& item : items_) {
      const EnergyConsumer* consumer = item->energyConsumer();
      if (consumer != nullptr) {
        energy += consumer->dailyEnergy();
      }
    }
    std::cout << std::fixed;
    std::cout.precision(1);
    std::cout << energy << "\n";
  }
  void theBestForNovice() {
    int max_score = -1;
    for (const auto& item : items_) {
      if (item->noviceScore() > max_score) {
        max_score = item->noviceScore();
      }
    }
    if (max_score < 6) {
      std::cout << "There isn't anything for novice\n";
      return;
    }
    for (const auto& item : items_) {
      if (item->noviceScore() == max_score) {
        std::cout << *item << "\n";
      }
    }
  }
  void parkInfo() {
    std::cout << "Park size: " << size() << "\n";
    energy();
    std::cout << "All items:\n";
    list();
  }
};