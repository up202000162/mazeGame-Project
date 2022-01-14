

#ifndef PROJETO_NOVO_2_ROBOT_H
#define PROJETO_NOVO_2_ROBOT_H
typedef unsigned int Uint;

class Robot {
public:
    Robot(Uint row, Uint col);
    char getSymbol() const; // retorna 'R'(vivo) ou 'r'(morto)
    Uint getRow() const;
    Uint getCol() const;
    bool isAlive() const;
    void setRow(Uint x);
    void setCol(Uint y);
    void setAsDead();

private:
    static Uint robotCounter; // atribui automaticamente id aos robôs
    Uint row, col;
    char symbol;
};


#endif //PROJETO_NOVO_2_ROBOT_H
