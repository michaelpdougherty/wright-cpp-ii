#include <iostream>
#include <string>
#include <map>
using namespace std;
/**
  * Michael Dougherty
  * CIS 242 - C++ 2
  * Final Project - Shakey the Robot
  * Tue Mar 7 2023
  */

enum NSEW { NORTH, SOUTH, EAST, WEST };
map<NSEW, string> directions = {
    { NORTH, "NORTH" },
    { SOUTH, "SOUTH" },
    { EAST, "EAST" },
    { WEST, "WEST" },
};

class WorldObject
{
    public:
        virtual char getSymbol() = 0;
};

class Wall : public WorldObject
{
    public:
        char getSymbol() {
            return 'W';
        }
};

class Space : public WorldObject
{
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

class Position
{
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
    int itemCount = 0;
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

        int getItemCount() {
            return this->itemCount;
        }

        void setPosition(int x, int y) {
            this->position = Position(x, y);
        }

        void setPosition(Position position) {
            this->position = position;
        }

        void turnRight(string &userMessage) {
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

            if (this->standingOnItem) {
                userMessage = this->getUserItemMessage();
            }
        }

        void turnLeft(string &userMessage) {
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
            if (this->standingOnItem) {
                userMessage = this->getUserItemMessage();
            }
        }

        void pickup(WorldMap worldMap, string &userMessage) {
            if (this->standingOnItem) {
                this->standingOnItem = false;
                this->itemCount++;
                userMessage = "Shakey picked up the item!\nNow Shakey has " + to_string(this->itemCount) +  " item(s) in his little pouch!";
            } else {
                userMessage = "Oops, Shakey is not standing on an item.";
            }
        }

        void drop(WorldMap worldMap, string &userMessage) {
            if (this->itemCount > 0) {
                if (this->standingOnItem) {
                    userMessage = "There is already an item here.";
                } else {
                    this->standingOnItem = true;
                    this->itemCount--;
                    userMessage = "Shakey dropped an item!\nNow Shakey has " + to_string(this->itemCount) +  " item(s) in his little pouch!";
                }
            } else {
                userMessage = "Shakey has no items!";
            }
        }

        string getUserItemMessage() {
            return "Shakey is standing on an item. Enter `pickup` to pick it up!";
        }

        void moveTo(Position newPosition, WorldMap worldMap, string &userMessage) {
            WorldObject * thingAtPosition = worldMap[newPosition.getX()][newPosition.getY()];
            char symbolAtNewPosition = thingAtPosition->getSymbol();
            bool wasStandingOnItem = this->standingOnItem;
            if (symbolAtNewPosition != 'W') {
                this->standingOnItem = symbolAtNewPosition == 'I';
                if (this->standingOnItem) {
                    userMessage = this->getUserItemMessage();
                }
                worldMap[this->position.getX()][this->position.getY()] = !wasStandingOnItem ? new Space : new Space(true);
                worldMap[newPosition.getX()][newPosition.getY()] = this;
                this->position = newPosition;
            } else {
                userMessage = "Shakey cannot walk through walls, dummy!";
            }
        }

        void step(WorldMap worldMap, string &userMessage) {
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
            this->moveTo(Position(newX, newY), worldMap, userMessage);
        }

        void home(WorldMap worldMap, string &userMessage) {
            userMessage = "Shakey, I'm coming home!";
            this->facingDirection = NORTH;
            this->moveTo(Position(1, 1), worldMap, userMessage);
        }
};

int main() {
    int mapRowCount = 10;
    int mapColumnCount = 10;
    char mapScheme[10][10] = {
        { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
        { 'W', 'S', ' ', 'I', ' ', 'I', ' ', ' ', ' ', 'W' },
        { 'W', ' ', ' ', 'I', ' ', 'I', ' ', ' ', ' ', 'W' },
        { 'W', 'I', 'I', 'I', ' ', 'I', ' ', ' ', ' ', 'W' },
        { 'W', ' ', 'W', ' ', ' ', 'I', ' ', ' ', ' ', 'W' },
        { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
        { 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W' },
        { 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W' },
        { 'W', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'W' },
        { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' },
    };

    WorldMap worldMap;
    Shakey myShakey;

    for (int x = 0; x < mapRowCount; x++) {
        for (int y = 0; y < mapColumnCount; y++) {
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

    string cmd;
    string userMessage = "";
    do {
        system("clear");
        cout << "Shakey is facing: " << myShakey.getFacingDirection() << "\t(Items: " + to_string(myShakey.getItemCount()) + ")" << endl;
        for (int x = 0; x < mapRowCount; x++) {
            for (int y = 0; y < mapColumnCount; y++) {
                cout << ' ' << (worldMap[x][y])->getSymbol() << ' ';
            }
            cout << endl;
        }
        cout << endl << endl;

        if (userMessage != "") {
            cout << endl;
            cout << "----------------------------------------------------" << endl;
            cout << userMessage << endl;
            cout << "----------------------------------------------------" << endl << endl;
        }
        userMessage = "";

        cout << "Options: [right, left, step, pickup, drop, home]\n\n";
        cout << "Please enter a command: ";
        cin >> cmd;
        if (cmd == "right") {
            myShakey.turnRight(userMessage);
        } else if (cmd == "left") {
            myShakey.turnLeft(userMessage);
        } else if (cmd == "step") {
            myShakey.step(worldMap, userMessage);
        } else if (cmd == "pickup") {
            myShakey.pickup(worldMap, userMessage);
        } else if (cmd == "drop") {
            myShakey.drop(worldMap, userMessage);
        } else if (cmd == "home") {
            myShakey.home(worldMap, userMessage);
        }
    } while (cmd != "exit");
}