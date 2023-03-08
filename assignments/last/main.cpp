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

class Position {
  int x = 0;
  int y = 0;
  public:
    Position() {}
    Position(int x, int y) {
      this->x = x;
      this->y = y;
    }
    void print() {
      cout << "[" << x << ", " << y << "]\n";
    }
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
};

typedef WorldObject * WorldMap[10][10];

class Shakey : public WorldObject {
  NSEW facingDirection = NORTH;
  Position position;
  bool standingOnItem = false;
  public:
    string getFacingDirection() {
      return directions[facingDirection];
    }

    char getSymbol() {
      string strFacingDirection = getFacingDirection();
      if (strFacingDirection == "NORTH") {
          return '^';
      } else if (strFacingDirection == "SOUTH") {
        return 'v';
      } else if (strFacingDirection == "EAST") {
        return '>';
      } else {
        return '<';
      }
    }

    void setPosition(int x, int y) {
      this->position = Position(x, y);
    }

    void setPosition(Position position) {
        this->position = position;
    }

    void turnRight() {
      string strFacingDirection = getFacingDirection();
      if (strFacingDirection == "NORTH") {
        facingDirection = EAST;
      } else if (strFacingDirection == "EAST") {
        facingDirection = SOUTH;
      } else if (strFacingDirection == "SOUTH") {
        facingDirection = WEST;
      } else {
        facingDirection = NORTH;
      }
    }

    void turnLeft() {
      string strFacingDirection = getFacingDirection();
      if (strFacingDirection == "NORTH") {
        facingDirection = WEST;
      } else if (strFacingDirection == "WEST") {
        facingDirection = SOUTH;
      } else if (strFacingDirection == "SOUTH") {
        facingDirection = EAST;
      } else {
        facingDirection = NORTH;
      }
    }

    void giveInfo() {
      cout << "Here's what Shakey knows:\n";
      cout << "Current position:\n";
      position.print();
      cout << "Facing object: ???\n";
    }

    void step(WorldMap worldMap) {
        int x = this->position.getX();
        int y = this->position.getY();
        int newX = x, newY = y;
        string facingDirection = this->getFacingDirection();
        if (facingDirection == "NORTH") {
            newX = x - 1;
            newY = y;
        } else if (facingDirection == "SOUTH") {
            newX = x + 1;
            newY = y;
        } else if (facingDirection == "EAST") {
            newX = x;
            newY = y + 1;
        } else {
            newX = x;
            newY = y - 1;
        }
        Position newPosition = Position(newX, newY);
        WorldObject * thingAtPosition = worldMap[newX][newY];
        char symbolAtNewPosition = thingAtPosition->getSymbol();
        bool wasStandingOnItem = this->standingOnItem;
        if (symbolAtNewPosition != 'W') {
            this->standingOnItem = symbolAtNewPosition == 'I';
            if (!wasStandingOnItem) {
                worldMap[x][y] = new Space;
            } else {
                worldMap[x][y] = new Space(true);
            }
            worldMap[newX][newY] = this;
            this->position = newPosition;
        }
    }
};

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

  // initialize shakey in global scope
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
          myShakey.setPosition(x, y);
          break;
      }
    }
  }

  // run loop
  string cmd;
  string errorMessage = "show error";
  do {
    system("clear");
    // print map
    for (int x = 0; x < 10; x++) {
      for (int y = 0; y < 10; y++) {
        cout << ' ' << (worldMap[x][y])->getSymbol() << ' ';
      }
      cout << endl;
    }

    cout << "\n\n";

    cout << "Shakey is facing: " << myShakey.getFacingDirection() << endl;
    if (errorMessage != "") {
        cout << endl;
        cout << "--------------------------" << endl;
        cout << "Error: " << errorMessage << endl;
        cout << "--------------------------" << endl << endl;
    }
    errorMessage = "";

    cout << "Please enter a command: ";
    cin >> cmd;

    cout << "You entered: " << cmd << endl;

    if (cmd == "right") {
      myShakey.turnRight();
    } else if (cmd == "left") {
      myShakey.turnLeft();
    } else if (cmd == "info") {
      myShakey.giveInfo();
      return 0;
    } else if (cmd == "step") {
      myShakey.step(worldMap);
    }
  } while (cmd != "exit");

  cout << "Done.\n";
  return 0;
}
