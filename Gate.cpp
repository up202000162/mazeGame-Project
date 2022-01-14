#include "Gate.h"

Gate::Gate(Uint col, Uint row) {
    //construtor
    this->row = row;
    this->col = col;
    symbol = 'O';
}

Uint Gate::getRow() const {
    // retorna posição da linha onde o gate se encontra
    return row;
}

Uint Gate::getCol() const {
    // reotna posição da coluna onde o gate se encontra
    return col;
}

void Gate::setRow(const Uint x) {
    // atualiza posição da linha do gate
    row = x;
}

void Gate::setCol(const Uint y) {
    // atualiza posição da coluna do gate
    col = y;
}

char Gate::getSymbol() const {
    /*Não era necessário criar, mas foi criado para facilitar 
    a implementação do template foundPosition da classe Game que 
    utiliza getSymbol*/

    return symbol; // retona 'O'
}