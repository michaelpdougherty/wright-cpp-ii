#include <iostream>
#include <cmath>
#include <string>
#include <map>
using namespace std;

enum MOVE_TYPE {
  FAST_PLOD,
  SLIP,
  SLOW_PLOD,
  SLEEP,
  BIG_HOP,
  BIG_SLIP,
  SMALL_HOP,
  SMALL_SLIP,
};

map<MOVE_TYPE, int> MOVES = {
  { FAST_PLOD, 3 },
  { SLIP, -6 },
  { SLOW_PLOD, 1 },
  { SLEEP, 0 },
  { BIG_HOP, 9 },
  { BIG_SLIP, -12 },
  { SMALL_HOP, 1 },
  { SMALL_SLIP, -2 },
};

map<int, int> hare_moves = {
  {1, SLEEP},
  {2, SLEEP},
  {3, BIG_HOP},
  {4, BIG_HOP},
  {5, BIG_SLIP},
  {6, SMALL_HOP},
  {7, SMALL_HOP},
  {8, SMALL_HOP},
  {9, SMALL_SLIP},
  {10, SMALL_SLIP},
};

map<int, int> tortoise_moves = {
  {1, FAST_PLOD},
  {2, FAST_PLOD},
  {3, FAST_PLOD},
  {4, FAST_PLOD},
  {5, FAST_PLOD},
  {6, SLIP},
  {7, SLIP},
  {8, SLOW_PLOD},
  {9, SLOW_PLOD},
  {10, SLOW_PLOD},
};

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
        if (i == racer1->position && i == racer2->position) {
          cout << "OUCH!!";
        } else if (i == racer1->position) {
          cout << racer1->initial;
        } else if (i == racer2->position) {
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