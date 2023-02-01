/* Michael Dougherty
 * Prof. Edwin Whitfield 
 * CIS 242
 * 23 Jan 2023
 * 
 * Assignment 1 - Computes Roman numerals between 0 and 4000
*/
#include <iostream>
#include <string>
#include <map>
using namespace std;

map<char, int> DIGITS = {
  { 'I', 1 },
  { 'V', 5 },
  { 'X', 10 },
  { 'L', 50 },
  { 'C', 100 },
  { 'D', 500 },
  { 'M', 1000 },
};

int readRomanNumeral(string num) {
  int n = num.length();
  char firstChar = num[n-1];
  int sum = DIGITS[firstChar];
  for (int i = n - 2; i >= 0; i--) {
    char prevChar = num[i+1];
    char thisChar = num[i];
    int previous = DIGITS[prevChar];
    int current = DIGITS[thisChar];
    if (current >= previous) {
      sum += current;
    } else {
      sum -= current;
    }
  }
  return sum;
}

int main() {
  string num;
  cout << "Please enter a Roman numeral: ";
  cin >> num;

  int answer = readRomanNumeral(num);
  printf("Answer: %d\n", answer);
  return 0;
}
