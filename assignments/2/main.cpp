#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void printTrack(int, int);
void printSingleTrack(char, int);

const int TRACK_LENGTH = 70;

int main() {
  srand(static_cast<unsigned int>(time(NULL)));
  cout << "BANG!!!!!" << endl;
  cout << "AND THEY'RE OFF!!!!!" << endl;
  
  int harePosition = 0, tortoisePosition = 0;
  bool isWinner = false;
  string winner;
  do {
    printTrack(harePosition, tortoisePosition);
    if (harePosition < TRACK_LENGTH - 1) {
      harePosition += rand() % 10 + 1;
    }
    if (harePosition > TRACK_LENGTH - 1) {
      harePosition = TRACK_LENGTH - 1;
      isWinner = true;
      winner = "HARE";
    }
    if (tortoisePosition < TRACK_LENGTH - 1) {
      tortoisePosition += rand() % 10 + 1;
    }
    if (tortoisePosition > TRACK_LENGTH - 1) {
      tortoisePosition = TRACK_LENGTH - 1;
      isWinner = true;
      winner = "TORTOISE";
    }
  } while (!isWinner);
  cout << winner << " WINS!!!" << endl;
  return(0);
}

void printTrack(int harePosition, int tortoisePosition) {
  printSingleTrack('H', harePosition);
  printSingleTrack('T', tortoisePosition);
}

void printSingleTrack(char signifier, int position) {
  for (int i = 0; i < TRACK_LENGTH; i++) {
    cout << '[';
    if (i == position) {
      cout << signifier;
    }
    cout << ']';
  }
  cout << endl;
}
