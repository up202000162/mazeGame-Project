
#include "Post.h"

Post::Post(Uint row, Uint col, char type) {
    // construtor
    this->row = row;
    this->col = col;
    this->symbol = type;
}

Uint Post::getRow() const {
    // retorna posição da linha do poste
    return row;
}

Uint Post::getCol() const {
    // retorna posição da coluna do poste
    return col;
}

char Post::getSymbol() const {
    // retorna símbolo ('*' or '+')
    return symbol;
}

bool Post::isElectrified() const {
    // verifica se o poste é eletrificado ('*')
    if (symbol == '*')
        return true;
    return false;
}
