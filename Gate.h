#ifndef PROJETO_NOVO_2_GATE_H
#define PROJETO_NOVO_2_GATE_H
typedef unsigned int Uint;

class Gate {
public:
    explicit Gate(Uint col = 0, Uint row = 0);
    Uint getRow() const;
    Uint getCol() const;
    char getSymbol() const;  // retorna 'O'
    void setCol(Uint y);
    void setRow(Uint x);

private:
    Uint col, row;
    char symbol;
};

#endif //PROJETO_NOVO_2_GATE_H