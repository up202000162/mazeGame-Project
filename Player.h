
#ifndef PROJETO_NOVO_2_PLAYER_H
#define PROJETO_NOVO_2_PLAYER_H
#include <string>
typedef unsigned int Uint;

struct Movement
{
    Uint row, col; // deslocamento
};

class Player {
public:
    explicit Player(Uint row = 0, Uint col = 0, char symbol = 'H');
    char getSymbol() const;
    bool isAlive() const;
    void setAsDead();
    void setCol(Uint y);
    void setRow(Uint x);
    Uint getRow() const;
    Uint getCol() const;
    inline std::string getName() const { return name; };
    inline std::string getTime() const { return time; };
    inline void setName(const std::string &playerName) { name = playerName; };
    inline void setTime(const std::string &playerTime) { time = playerTime; };

private:
    Uint row, col;
    std::string name, time;
    char symbol;
};

#endif //PROJETO_NOVO_2_PLAYER_H
