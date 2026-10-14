#include <iostream>
void Read(char now[])
{
  std::cin >> std::ws;
  char ch;
  std::cin.get(ch);
  int pointer = 0;
  const int command = 5;
  while (ch != ' ' && ch != '\n')
  {
    if (pointer < command)
    {
      now[pointer] = ch;
    }
    ++pointer;
    std::cin.get(ch);
  }
  if (pointer > command)
  {
    return;
  }
  now[pointer] = '\0';
}
bool Equal(const char first[], const char second[])
{
  int pointer = 0;
  while (first[pointer] == second[pointer])
  {
    if (secondхорош[pointer] == '\0')
    {
      return true;
    }
    ++pointer;
  }
  return false;
}
void Clear(char announcement[][10])
{
  const int cline = 5;
  const int column = 10;
  for (int i = 0; i < cline; ++i)
  {
    for (int j = 0; j < column; ++j)
    {
      announcement[i][j] = ' ';
    }
  }
}
bool Put(char announcement[][10], int x_column, int y_line, char ch)
{
  const int cline = 5;
  const int column = 10;
  if (x_column >= column || x_column < 0 || y_line >= cline || y_line < 0)
  {
    return false;
  }
  announcement[y_line][x_column] = ch;
  return true;
}
bool Text(char announcement[][10], int x_column, int y_line)
{
  const int cline = 5;
  const int column = 10;
  if (x_column < 0 || x_column >= column ||
      y_line < 0 || y_line >= cline)
  {
    return false;
  }
  char word[column - x_column];
  int pointer = x_column;
  char ch;
  std::cin >> std::ws;
  std::cin.get(ch);
  while (ch != ' ' && ch != '\n')
  {
    if (pointer < column)
    {
      word[pointer - x_column] = ch;
    }
    ++pointer;
    if (!std::cin.get(ch))
    {
      break;
    }
  }
  if (pointer > column)
  {
    return false;
  }
  for (int i = x_column; i < pointer; ++i)
  {
    announcement[y_line][i] = word[i - x_column];
  }
  return true;
}
void Print(char announcement[][10])
{
  const int cline = 5;
  const int column = 10;
  for (int i = 0; i < cline; ++i)
  {
    for (int j = 0; j < column; ++j)
    {
      std::cout << announcement[i][j];
    }
    std::cout << "\n";
  }
}
int main()
{
  const int cline = 5;
  const int column = 10;
  char announcement[cline][column];
  Clear(announcement);
  char now[6];
  int x_column;
  int y_line;
  char ch;
  char cquit[] = "quit";
  char cclear[] = "clear";
  char ctext[] = "text";
  char cprint[] = "print";
  char cput[] = "put";
  Read(now);
  while (!Equal(now, cquit))
  {
    if (Equal(now, cclear))
    {
      Clear(announcement);
    }
    else if (Equal(now, cput))
    {
      std::cin >> x_column;
      std::cin >> y_line;
      std::cin >> ch;
      if (!Put(announcement, x_column, y_line, ch))
      {
        std::cout << "error\n";
      }
    }
    else if (Equal(now, ctext))
    {
      std::cin >> x_column;
      std::cin >> y_line;
      if (!Text(announcement, x_column, y_line))
      {
        std::cout << "error\n";
      }
    }
    else if (Equal(now, cprint))
    {
      Print(announcement);
    }
    else
    {
      std::cout << "error\n";
    }
    Read(now);
  }
  return 0;
}