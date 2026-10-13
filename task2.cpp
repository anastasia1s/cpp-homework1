#include <iostream>
#include <string>
using BankOp = void (*)(int&, int);
void Deposit(int& bank, int k) {
  if (k <= 0) {
    std::cout << "error\n";
    return;
  }
  bank += k;
}
void Withdraw(int& bank, int k) {
  if (bank < k || k <= 0) {
    std::cout << "error\n";
    return;
  }
  bank -= k;
}
void Balance(int& bank, int k) { std::cout << bank << "\n"; }
void Reset(int& bank, int k) { bank = 0; }
void Multiply(int& bank, int k) {
  if (k <= 0) {
    std::cout << "error\n";
    return;
  }
  bank *= k;
}
int main() {
  const int c_size{5};
  int bank = 0;
  std::string function_name[c_size]{"deposit", "withdraw", "balance", "reset",
                                    "multiply"};
  BankOp function_pointer[c_size]{Deposit, Withdraw, Balance, Reset, Multiply};
  bool need_k[c_size]{true, true, false, false, true};
  std::string command;
  while (true) {
    int k = 0;
    std::cin >> command;
    if (command == "stop") {
      break;
    }
    bool found = false;
    for (int i = 0; i < c_size; ++i) {
      if (command == function_name[i]) {
        if (need_k[i]) {
          std::cin >> k;
        }
        function_pointer[i](bank, k);
        found = true;
        break;
      }
    }
    if (!found) {
      std::cout << "error\n";
    }
  }
  return 0;
}
