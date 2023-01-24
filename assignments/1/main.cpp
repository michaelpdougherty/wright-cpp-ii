#include <iostream>
#include <string>
#include <map>

std::map<std::string, int> TESTS = {
  { "I", 1 },
  { "II", 2 },
  { "III", 3 },
};

std::map<char, int> DIGITS = {
  { 'I', 1 },
  { 'V', 5 },
  { 'X', 10 },
  { 'L', 50 },
  { 'C', 100 },
  { 'D', 500 },
  { 'M', 1000 },
};

void log(std::string name, std::string value) {
  printf("%s: %s\n", name.c_str(), value.c_str());
}

void log(std::string name, int value) {
  printf("%s: %d\n", name.c_str(), value);
}

int readRomanNumeral(std::string num)
{
  int n = num.length();
  int sum = DIGITS[num[n - 1]];
  for (int i = n - 2; i >= 0; i--) {
    int previous = DIGITS[num[i+1]];
    int current = DIGITS[num[i]];
    if (current >= previous) {
      sum += current;
    } else {
      sum -= current;
    }
  }
  return sum;
}

int main() {
  std::cout << "Looping through TESTS...\n";
  for (auto const& [input, expected] : TESTS) {
    printf("%s: %d\n", input.c_str(), expected);
  }
  return 0;
}