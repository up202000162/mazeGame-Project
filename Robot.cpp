
#include "Robot.h"

Uint Robot::robotCounter = 0; // inicializa contador

Robot::Robot(Uint row, Uint col) {
    //construtor
    this->row = row;
    this->col = col;
    robotCounter += 1;
    symbol = 'R';
}

char Robot::getSymbol() const {
    // retorna símbolo do robô
    return symbol;
}

Uint Robot::getRow() const {
    // retorna linha da posição onde o robô se encontra
    return row;
}

Uint Robot::getCol() const {
    // retorna coluna da posição onde o robô se encontra
    return col;
}

bool Robot::isAlive() const {
    // verifica se o robô está vivo
    if (symbol == 'R')
        return true;
    return false;
}

void Robot::setRow(const Uint x) {
    // atualiza posição da linha do robô
    row = x;
}

void Robot::setCol(const Uint y) {
    // atualiza posição da coluna do robô
    col = y;
}

void Robot::setAsDead() {
    // coloca robô como morto
    symbol = 'r';
}



