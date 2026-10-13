#include <iostream>
#include <string>
void Clear(char announcement[][10]) {
  const int cline = 5;
  const int column = 10;
  for (int i = 0; i < cline; ++i) {
    for (int j = 0; j < column; ++j) {
      announcement[i][j] = ' ';
    }
  }
}
bool Put(char announcement[][10], int x_column, int y_line, char ch) {
  const int cline = 5;
  const int column = 10;
  if (x_column >= column || x_column < 0 || y_line >= cline || y_line < 0) {
    return false;
  }
  announcement[y_line][x_column] = ch;
  return true;
}
bool Text(char announcement[][10], int x_column, int y_line, std::string word) {
  const int cline = 5;
  const int column = 10;
  int word_size = word.size();
  if (x_column < 0 || x_column >= column ||
      word_size + x_column - 1 >= column || y_line < 0 || y_line >= cline) {
    return false;
  }
  for (int i = x_column; i < x_column + word_size; ++i) {
    announcement[y_line][i] = word[i - x_column];
  }
  return true;
}
void Print(char announcement[][10]) {
  const int cline = 5;
  const int column = 10;
  for (int i = 0; i < cline; ++i) {
    for (int j = 0; j < column; ++j) {
      std::cout << announcement[i][j];
    }
    std::cout << "\n";
  }
}
int main() {
  const int cline = 5;
  const int column = 10;
  char announcement[cline][column];
  Clear(announcement);
  std::string now;
  int x_column;
  int y_line;
  std::string word;
  char ch;
  while (std::cin >> now && now != "quit") {
    if (now == "clear") {
      Clear(announcement);
    } else if (now == "put") {
      std::cin >> x_column;
      std::cin >> y_line;
      std::cin >> ch;
      if (!Put(announcement, x_column, y_line, ch)) {
        std::cout << "error\n";
      }
    } else if (now == "text") {
      std::cin >> x_column;
      std::cin >> y_line;
      std::cin >> word;
      if (!Text(announcement, x_column, y_line, word)) {
        std::cout << "error\n";
      }
    } else if (now == "print") {
      Print(announcement);
    } else {
      std::cout << "error\n";
    }
  }
  return 0;
}
