#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class Racer {
  public:
    Racer(string name) {
      this->name = name;
      this->initial = name[0];
    }
    string name;
    char initial;
    int position = 0;
};

class Race {
  public:
    bool hasWinner = false;
    static const int TRACK_LENGTH = 70;
    string winner;
    Racer *racer1;
    Racer *racer2;
    void printTrack() {
      for (int i = 0; i < Race::TRACK_LENGTH; i++) {
        cout << '[';
        if (i == racer1->position) {
          cout << racer1->initial;
        }
        if (i == racer2->position) {
          cout << racer2->initial;
        }
        cout << ']';
      }
      cout << endl;
    }
};

void init() {
  srand(static_cast<unsigned int>(time(NULL)));
  cout << "BANG!!!!!" << endl;
  cout << "AND THEY'RE OFF!!!!!" << endl;
}

int main() {
  init();
  Racer hare = Racer("HARE");
  Racer tortoise = Racer("TORTOISE");

  Race race;
  race.racer1 = &hare;
  race.racer2 = &tortoise;
  do {
    race.printTrack();
    if (hare.position < Race::TRACK_LENGTH - 1) {
      hare.position += rand() % 10 + 1;
    }
    if (hare.position > Race::TRACK_LENGTH - 1) {
      hare.position = Race::TRACK_LENGTH - 1;
      race.hasWinner = true;
      race.winner = "HARE";
    }
    if (tortoise.position < Race::TRACK_LENGTH - 1) {
      tortoise.position += rand() % 10 + 1;
    }
    if (tortoise.position > Race::TRACK_LENGTH - 1) {
      tortoise.position = Race::TRACK_LENGTH - 1;
      race.hasWinner = true;
      race.winner = "TORTOISE";
    }
  } while (!race.hasWinner);
  race.printTrack();
  cout << race.winner << " WINS!!!" << endl;
  return(0);
}