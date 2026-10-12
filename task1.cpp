#include <iostream>
double Average(const int* arr, int n) {
  double sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += arr[i];
  }
  double res = sum / n;
  return res;
}
int Minimum(const int* arr, int n) {
  int min_el = arr[0];
  for (int i = 1; i < n; ++i) {
    if (arr[i] < min_el) {
      min_el = arr[i];
    }
  }
  return min_el;
}
int Maximum(const int* arr, int n) {
  int max_el = arr[0];
  for (int i = 1; i < n; ++i) {
    if (arr[i] > max_el) {
      max_el = arr[i];
    }
  }
  return max_el;
}
int Counter(const int* arr, int n) {
  int cnt = 0;
  for (int i = 0; i < n; ++i) {
    if (arr[i] < 0) {
      ++cnt;
    }
  }
  return cnt;
}
int main() {
  int n;
  std::cin >> n;
  if (n <= 0) {
    return 0;
  }
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  double average_temp = Average(arr, n);
  std::cout << std::fixed;
  std::cout.precision(1);
  std::cout << average_temp << "\n";
  int min_temp = Minimum(arr, n);
  std::cout << min_temp << " ";
  int max_temp = Maximum(arr, n);
  std::cout << max_temp << "\n";
  int cnt = Counter(arr, n);
  std::cout << cnt;
  delete[] arr;
  arr = nullptr;
  return 0;
}

