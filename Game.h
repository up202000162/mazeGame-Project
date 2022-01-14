
#ifndef PROJETO_NOVO_2_GAME_H
#define PROJETO_NOVO_2_GAME_H
#include <string>
#include <vector>
#include "Maze.h"
#include "Robot.h"
#include "Player.h"
#include "Gate.h"
using namespace std;
typedef unsigned int Uint;

struct Position {
    int row = 0, col = 0;
};


class Game {
public:
    explicit Game(const string& fileName);
    void play();
    bool isValid() const;
    static Uint menu();
    static bool showWinners();
    static Uint rules();

private:
    bool playerWon() const;
    bool playerLose() const;
    static bool isValidMovement(char moveTo) ;
    void showGameDisplay() const;
    template<typename T1, typename T2>                  //permite verificar colisões
    bool collide(const T1 & class1, const T2 & class2); //entre diferentes classes
    bool entryGate(const Gate & gate);
    static Position distanceRobotPlayer(Position player, Position robot);
    void moveRobot(Robot & robot);
    bool movePlayer(char moveTo, Movement playerMovement);
    static void sortAndShowWinners(fstream& winnersStream, string &lastWinnerName, const time_t &lastWinnerTime);
    static Uint stringToInt(string &str);

private:
    Maze maze;
    Player player;
    vector<Robot> robots;
    vector<Gate> gates;
    string mazeName, winnersFile;
    bool fileOpened, enteredGate = false;
};


#endif //PROJETO_NOVO_2_GAME_H
