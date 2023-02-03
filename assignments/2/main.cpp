#include <iostream>
#include <iomanip>
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

typedef map<int, MOVE_TYPE> Moveset;

Moveset hare_moves = {
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

Moveset tortoise_moves = {
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
    Racer(string name, Moveset moveset, string winMessage) {
      this->name = name;
      this->initial = name[0];
      this->moveset = moveset;
      this->winMessage = winMessage;
    }
    int position = 0;
    string name;
    char initial;
    Moveset moveset;
    string winMessage;
};

class Race {
  static const int TRACK_LENGTH = 70;
  static const int FINISH_LINE = 69;
  public:
    Race(Racer *racer1, Racer *racer2) {
      this->racer1 = racer1;
      this->racer2 = racer2;
    }
    bool hasWinner = false;
    Racer *winner;
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

    void fireGun() {
      cout << "BANG!!!!!" << endl;
      cout << "AND THEY'RE OFF!!!!!" << endl;
    }

    void run() {
      fireGun();
      do {
        this->printTrack();
        Racer *racers[] = { this->racer1, this->racer2 };
        for (int i = 0; i < 2; i++) {
          Racer *racer = racers[i];
          MOVE_TYPE selection = racer->moveset[rand() % 10 + 1];
          racer->position += MOVES[selection];
          if (racer->position > Race::FINISH_LINE) {
            racer->position = Race::FINISH_LINE;
            if (!this->hasWinner) {
              this->hasWinner = true;
              this->winner = racer;
            }
          }
        }
      } while (!this->hasWinner);
      cout << "FLASH!!!\n";
      this->printTrack();
      cout << this->winner->winMessage << endl;
    }
};

int main() {
  srand(static_cast<unsigned int>(time(NULL)));
  Racer tortoise = Racer("TORTOISE", tortoise_moves, "TORTOISE WINS!!! YAY!!");
  Racer hare = Racer("HARE", hare_moves, "Hare wins. Yuck.");
  Race race = Race(&tortoise, &hare);
  race.run();
}