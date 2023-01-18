#include <iostream>
#include <string>

using namespace std;

string getNumberString()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;
    return to_string(n);
}

int main()
{
    string numberString = getNumberString();
    int strLength = strlen(numberString.c_str());
    bool numberIsPalindrome = true;
    for (int i = 0; i < strLength / 2; i++) {
        if (numberString[i] != numberString[strLength - (i + 1)]) {
            numberIsPalindrome = false;
        }
    };
    cout << numberString << " is " << (numberIsPalindrome ? "" : "NOT ") << "a palindrome.\n";
    return 0;
}