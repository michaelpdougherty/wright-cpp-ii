#include <iostream>
#include <string>
#include <map>
using namespace std;

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
  public:
    char getSymbol() {
      return 'S';
    }
};

typedef WorldObject * WorldMap[10][10];

int main() {
  cout << "Starting...\n";

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
          worldMap[x][y] = new Shakey;
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

  cout << "Done.\n";
  return 0;
}