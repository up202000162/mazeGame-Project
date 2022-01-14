#ifndef PROJETO_NOVO_2_CHOOSEMAZE_H
#define PROJETO_NOVO_2_CHOOSEMAZE_H
#include <string>
using namespace std;

class ChooseMaze
{
public:
    ChooseMaze();
    inline string getMazeName() const { return mazeName; } // retorna nome do ficheiro do labirinto
    inline string getWinnersStreamName() const { return winnersStreamName; } // retorna nome do ficheiro dos winners
    int choiceMaze(); // escolhe número do labirinto
    int choiceWinners(); // esolhe número do labirinto para ver os winnners
private:
    string mazeName, winnersStreamName;
};
#endif //PROJETO_NOVO_2_CHOOSEMAZE_H
