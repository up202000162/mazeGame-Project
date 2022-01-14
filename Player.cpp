
#include "Player.h"

Player::Player(Uint row, Uint col, char symbol) {
    //construtor
    this->row = row;
    this->col = col;
    this->symbol = symbol;

}

char Player::getSymbol() const {
    // retorna 'h' ou 'H'
    return symbol;
}

Uint Player::getRow() const {
    // retorna posição da linha onde o jogador se encontra
    return row;
}

Uint Player::getCol() const {
    // retorna posição da linha onde o jogador se encontra
    return col;
}


bool Player::isAlive() const {
    // verifica se o jogador está vivo
    if (symbol == 'H')
        return true;
    return false;
}

void Player::setRow(const Uint x) {
    // atuliza posição da linha do jogador
    row = x;
}

void Player::setCol(const Uint y) {
    // atuliza posição da coluna do jogador
    col = y;
}

void Player::setAsDead() {
    // coloca jogador como morto
    symbol = 'h';
}


