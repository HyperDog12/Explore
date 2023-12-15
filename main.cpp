#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <fstream>
using std::cin;
using std::cout;
using std::ifstream;
using std::rand;
using std::stoi;
using std::to_string;
using std::endl;
using std::string;
int random(int low, int high) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(low, high);
  return distr(gen);
};
class world {
private:
  int size = -1;
  int map[100][100];
  int playerloc[2];
  int enemies[6][500];
  int em;
  string enemyNames[500];
  string name;
  //first loc up/down, second left right
public:
  string getName() { return name; };
  void move(int direction) {
    if (direction == 1) {
      playerloc[0]--;
      cout << "Sucessfuly moved North\n";
    } else if (direction == 2) {
      playerloc[0]++;
      cout << "Sucessfuly moved South\n";
    } else if (direction == 3) {
      playerloc[1]--;
      cout << "Sucessfuly moved West\n";
    } else if (direction == 4) {
      playerloc[1]++;
      cout << "Sucessfuly moved East\n";
    }
  };
  void setNames(int x){
    ifstream namesList("files/names/names.txt");
    string names;
    int rand = random(2, 501);
    int i = 1;
    while (getline (namesList, names) && i<rand) {
       i++;
    }
    enemyNames[x]=names;
  };
  void setEnemy() {
    for (int i = 0; i < em+1; i++) {
      //y
      enemies[0][i] = random(0,size);
      //x
      enemies[1][i] = random(0,size);
      //attack power
      enemies[2][i] = random(10, 50);
      //health
      enemies[3][i] = random(75, 200);
      //live?
      enemies[4][i] = 1;
      //discovered
      enemies[5][i] = 0;
      //names
      setNames(i);
    }
  };
  void drawRiver() {
    int start = random(0, size - 1);
    int move;
    int j = start;
    int i = 0;
    if (random(1, 2) == 1) {
      map[start][0] = 0;
      while (i < size) {
        move = random(-3, 3);
        j = j + move;
        i++;
        map[j][i] = 0;
        if (move == -2) {
          map[j + 1][i] = 0;
        } else if (move == -3) {
          map[j + 2][i] = 0;
          map[j + 1][i] = 0;
        } else if (move == 2) {
          map[j - 1][i] = 0;
        } else if (move == 3) {
          map[j - 1][i] = 0;
          map[j - 2][i] = 0;
        }
      }
    } else {
      map[0][start] = 0;
      while (i < size) {
        move = random(-3, 3);
        j = j + move;
        i++;
        map[i][j] = 0;
        if (move == -2) {
          map[i][j + 1] = 0;
        } else if (move == -3) {
          map[i][j + 2] = 0;
          map[i][j + 1] = 0;
        } else if (move == 2) {
          map[i][j - 1] = 0;
        } else if (move == 3) {
          map[i][j - 2] = 0;
          map[i][j - 1] = 0;
        }
      }
    }
  };
  void makeWorld() {
    cout << "What would you like to name your world?\n";
    cin >> name;
    cout << "How large would you like the world to be(Enter an integer under "
            "100 and greater than 20, larger maps might be harder to print "
            "out)?\n";
    cin >> size;
    while (size<20 || size>100){
      cout << "Please enter the world size, it should be between 20 and 100.\n";
      cin >> size;
    }
    cout << "How many enimies would you like to have, it should be between 5 and " << round(size*size*0.05) << ".\n";
    cin >> em;
    while (em < 5 || em > round(size*size*0.05)){
    cout << "How many enimies would you like to have, it should be between 5 and " << round(size*size*0.05) << ".\n";
      cin >> em;
    }
    cout << "Making world...\n";
    /*  for (int i = size; i < 100; i++){
                    for (int j = 0; j < 100; j++){
                            map[i][j]=-1;
                    }
            }*/
    int x;
    int y = 0;
    while (y <= size) {
      x = 0;
      while (x <= size) {
        map[x][y] = 7;
        x++;
      }
      y++;
    }
    playerloc[0] = round(size / 2);
    playerloc[1] = round(size / 2);
    drawRiver();
    drawRiver();
    setEnemy();
  };
  void printMap() {
    int y = 0;
    while (y < size) {
      int x = 0;
      while (x < size) {
        if (x != playerloc[1] || y != playerloc[0]) {
          cout << map[y][x];
        } else {
          cout << "8";
        }
        if (x != size - 1) {
          cout << ",";
        } else {
          cout << "\n";
        }
        x++;
      }
      y++;
    }
    cout << "Key: 0=River, 1=Player, 7=Forest\n";
  };
  string coords() {
    string code = to_string(playerloc[0]);
    code+=", ";
    code+=to_string(playerloc[1]);
    return code;
  };
};
void clear() { cout << "\033[2J\033[1;1H"; }
int main() {
  world map;
  clear();
  map.makeWorld();
  map.printMap();
  string input;
  cout << "Welcome to the world of " + map.getName() +
              ". Your task is to explore the world. If you are ever in need of "
              "help then you can use the 'help' command.\n";
  while (true) {
    cin >> input;
    if (input == "help" || input == "Help") {
      cout << "Help: You know what this does.\n";
      cout << "North: Moves the player North\n";
      cout << "South: Moves the player South\n";
      cout << "East: Moves the player East\n";
      cout << "West: Moves the player West\n";
      cout << "Pos: Shows coords\n";
      cout << "Clear: Clears the console\n";
      cout << "";
    } else if (input == "clear" || input == "Clear") {
      clear();
    } else if (input == "N" || input == "n" || input == "North" || input == "north") {
      map.move(1);
    } else if (input == "S" || input == "s" || input == "South" ||
               input == "south") {
      map.move(2);
    } else if (input == "W" || input == "w" || input == "West" ||
               input == "west") {
      map.move(3);
    } else if (input == "E" || input == "e" || input == "East" ||
               input == "east") {
      map.move(4);
    } else if (input == "Map" || input == "map") {
      map.printMap();
    } else if (input == "pos" || input == "Pos"){
      cout << map.coords() << endl;
    } else {cout << "Invaild command, use help to see command list\n";}
  }
}