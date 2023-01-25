#include <iostream>
#include <numeric>   
using namespace std;

int arraySum(int a[], int n)
{
    int previous = a[0];
    return accumulate(a+1, a+n, a[0], [&](int rollingTotal, int current){
      int newSum = (current >= previous
        ? rollingTotal + current
        : rollingTotal - current);
      previous = current;
      return newSum;
    });
}

 
int main()
{
  cout << "CDXLIV (444)" << endl;
  int n = 6;
  int a[] = {5, 1, 50, 10, 500, 100}; // CDXLIV => 444
  int result = arraySum(a, n);
  cout << "Total result: " << result << endl;
}
