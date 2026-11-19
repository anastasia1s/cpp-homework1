#pragma once
#include <exception>
#include <string>
class FleetError : public std::exception {
 private:
  std::string message_;

 public:
  explicit FleetError(const std::string& message) : message_(message) {}
  const char* what() const noexcept override { return message_.c_str(); }
};
class InvalidArgumentError : public FleetError {
 public:
  explicit InvalidArgumentError(const std::string& message)
      : FleetError(message) {}
};
class InspectionRejectedError : public FleetError {
 public:
  explicit InspectionRejectedError(const std::string& message)
      : FleetError(message) {}
};
class CapacityExceededError : public FleetError {
 public:
  explicit CapacityExceededError(const std::string& message)
      : FleetError(message) {}
};
class InventoryIdError : public FleetError {
 public:
  explicit InventoryIdError(const std::string& message) : FleetError(message) {}
};