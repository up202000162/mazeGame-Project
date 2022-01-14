
#ifndef PROJETO_NOVO_2_POST_H
#define PROJETO_NOVO_2_POST_H
typedef unsigned int Uint;

class Post {
public:
    Post(Uint row, Uint col, char type);
    Uint getRow() const;
    Uint getCol() const;
    char getSymbol() const; // retorna '*' ou '+'
    bool isElectrified() const;
private:
    Uint row, col;
    char symbol; // '*' - electrified; '+'- non-electrified
};

#endif //PROJETO_NOVO_2_POST_H
