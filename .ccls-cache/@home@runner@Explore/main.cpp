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
  string enemyNames[500][2];
  string name;
  bool customEm;
  string CuEmFiPath;
  //first loc up/down, second left right
public:
  int checkForEm(int x, int y, int type){
  int isEm = -1;
    if (type == 1){
  for (int i=0; i<em; i++){
    if (enemies[0][i]==x && enemies[1][i]==y && enemies[5][i]){
      isEm = i;
      break;
    }
  }
  } else if (type==2){
      for (int i=0; i<em; i++){
        if (enemies[0][i]==x && enemies[1][i]==y){
          isEm = i;
          break;
        }
      }
  }
  return isEm;
};
  string getName() { return name; };
  void move(int direction) {
    if (direction == 1) {
      if (playerloc[0]-1>=0){
      playerloc[0]--;
        cout << "Sucessfuly moved North\n";
      } else {
        cout << "Failed to move North, end of map\n"; 
      }
    } else if (direction == 2) {
      if (playerloc[0]+1<size){
      playerloc[0]++;
      cout << "Sucessfuly moved South\n";
      } else {
        cout << "Failed to move South, end of map\n"; 
      }
    } else if (direction == 3) {
      if (playerloc[1]-1>=0){
      playerloc[1]--;
      cout << "Sucessfuly moved West\n";
      } else {
        cout << "Failed to move West, end of map\n"; 
      }
    } else if (direction == 4) {
      if (playerloc[1]+1<size){
      playerloc[1]++;
      cout << "Sucessfuly moved East\n";
    } else {
        cout << "Failed to move East, end of map\n"; 
      }
    }
  };
  void setNames(int x){
    int mf = random(1,2);
    string names;
    int i;
    string filepaths[3]={"files/names/male/", "files/names/female/", "files/names/last/"};
    int rand;
    string ln;
    if (!customEm){
    if (mf == 1){
    ifstream namesList("files/names/male/main.txt");
    rand = random(2, 501);
    i = 1;
    while (getline (namesList, names) && i<rand) {
       i++;
    }
      namesList.close();
      enemyNames[x][1] = "m";
    } else if (mf == 2){
    ifstream namesList("files/names/female/main.txt");
    rand = random(2, 501);
    i = 1;
    while (getline (namesList, names) && i<rand) {
       i++;
    }
      namesList.close();
      enemyNames[x][1] = "f";
    }
    ifstream namesList("files/names/last/main.txt");
    rand = random(2, 501);
    i = 1;
    while (getline (namesList, ln) && i<rand) {
       i++;
    }
    namesList.close();
    } else {
      filepaths[0]+=CuEmFiPath;
      filepaths[1]+=CuEmFiPath;
      filepaths[2]+=CuEmFiPath;

      filepaths[0]+=".txt";
      filepaths[1]+=".txt";
      filepaths[2]+=".txt";
      if (mf == 1){
        ifstream namesList(filepaths[0]);
        rand = random(2, 501);
        i = 1;
        while (getline (namesList, names) && i<rand) {
           i++;
        }
          namesList.close();
          enemyNames[x][1] = "m";
        } else if (mf == 2){
        ifstream namesList(filepaths[1]);
        rand = random(2, 501);
        i = 1;
        while (getline (namesList, names) && i<rand) {
           i++;
        }
          namesList.close();
          enemyNames[x][1] = "f";
        }
        ifstream namesList(filepaths[2]);
        rand = random(2, 501);
        i = 1;
        while (getline (namesList, ln) && i<rand) {
           i++;
        }
        namesList.close();
    }
    names += " ";
    names += ln;
    enemyNames[x][0]=names;
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
    string i;
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
    cout << "Would you like to use custom names for enemies?(Y/N)\n";
    cin >> i;
    if (i=="y" || i=="Y" || i=="Yes" || i=="yes"){
      cout << "Please enter the file name (if the file is names.txt the enter names ect.)\n";
      cin >> CuEmFiPath;
      customEm=true;
    }
    cout << "How many enemies would you like to have, it should be between 5 and " << round(size*size*0.05) << ".\n";
    cin >> em;
    while (em < 5 || em > round(size*size*0.05)){
    cout << "How many enemies would you like to have, it should be between 5 and " << round(size*size*0.05) << ".\n";
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
          if (checkForEm(y,x,1) != -1){
            cout << "E"; 
          } else {
            cout << map[y][x];
          }
        } else {
          cout << "U";
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
    cout << "Key: 0=River,  7=Forest\n";
    cout << "     U=Player, E=Enemy\n"; 
  };
  string coords() {
    string code = to_string(playerloc[0]);
    code+=", ";
    code+=to_string(playerloc[1]);
    return code;
  };
  void UpDiscEms() {
     if (checkForEm(playerloc[0], playerloc[1], 2) > -1){
       enemies[5][checkForEm(playerloc[0], playerloc[1], 2)]=1;
       cout << "You happen to stumble across an enemy, ";
       if (enemyNames[checkForEm(playerloc[0], playerloc[1], 2)][1]=="m"){
         cout << "his name is ";
       } else if (enemyNames[checkForEm(playerloc[0], playerloc[1], 2)][1]=="f"){
         cout << "her name is "; 
       }
         cout << enemyNames[checkForEm(playerloc[0], playerloc[1], 2)][0] << endl; 
     }
  }; 
};
void clear() { cout << "\033[2J\033[1;1H"; }
int main() {
  clear();
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
    map.UpDiscEms();
  }
}