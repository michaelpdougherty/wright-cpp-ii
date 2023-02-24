#include <iostream>
#include <string>
#include <map>
using namespace std;

// directional values
enum NSEW { NORTH, SOUTH, EAST, WEST };
map<NSEW, string> directions = {
  { NORTH, "NORTH" },
  { SOUTH, "SOUTH" },
  { EAST, "EAST" },
  { WEST, "WEST" },
};

// spaces on the map
class WorldObject {
  public:
    virtual char getSymbol() = 0;
};

class Wall : public WorldObject {
  public:
    char getSymbol() {
      return 'W'; 
    }
};

class Space : public WorldObject {
  bool hasItem = false;
  public:
    Space() {}
    Space(bool hasItem) {
      this->hasItem = hasItem;
    }
    char getSymbol() {
      if (hasItem) {
        return 'I';
      } else {
        return ' ';
      }
    }
};

class Shakey : public WorldObject {
  NSEW facingDirection = NORTH;
  public:
    string getFacingDirection() {
      return directions[facingDirection];
    }
    char getSymbol() {
      string facingDirection = getFacingDirection();
      if (facingDirection == "NORTH") {
          return '^';
      } else if (facingDirection == "SOUTH") {
        return 'v';
      } else if (facingDirection == "EAST") {
        return '>';
      } else {
        return '<';
      }
    }
};

typedef WorldObject * WorldMap[10][10];

int main() {
  cout << "Starting...\n";
  system("clear");

  // declare map scheme
  char mapScheme[10][10] = {
    { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
    { 'W', 'S', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W' },
    { 'W', ' ', ' ', ' ', ' ', 'W', ' ', ' ', ' ', 'W' },
    { 'W', ' ', ' ', 'I', ' ', ' ', ' ', ' ', ' ', 'W' },
    { 'W', ' ', 'W', ' ', ' ', ' ', ' ', ' ', ' ', 'W' },
    { 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W' },
    { 'W', ' ', ' ', ' ', 'W', ' ', ' ', ' ', ' ', 'W' },
    { 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W' },
    { 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W' },
    { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
  };

  // declare world map
  WorldMap worldMap;

  Shakey myShakey;

  // fill map according to map scheme
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      switch (mapScheme[x][y]) {
        case 'W':
          worldMap[x][y] = new Wall;
          break;
        case ' ':
          worldMap[x][y] = new Space;
          break;
        case 'I':
          worldMap[x][y] = new Space(true);
          break;
        case 'S':
          worldMap[x][y] = &myShakey;
          break;
      }
    }
  }

  // print map
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 10; y++) {
      cout << ' ' << (worldMap[x][y])->getSymbol() << ' ';
    }
    cout << endl;
  }

  cout << "\n\n";

  cout << "Shakey is facing: " << myShakey.getFacingDirection() << endl;
  cout << "Please enter a command: ";
  string cmd;
  cin >> cmd;

  cout << "You entered: " << cmd << endl;

  cout << "Done.\n";
  return 0;
}
