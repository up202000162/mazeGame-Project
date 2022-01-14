#include "ChooseMaze.h"
#include <iostream>
#include<limits>

ChooseMaze::ChooseMaze() {
    mazeName = "UNKNOWN";
    winnersStreamName = "UNKNOWN";
}

int ChooseMaze::choiceMaze() {
    /*Cria nome do do ficheirio que contém o labirinto*/

    int choose;
    string number;

    while (true)
    {
        cout << "Choose the maze number (Press 0 to return to Menu or Ctrl-(Z or D) to Exit): ";
        cin >> choose;

        //verifica se o jogador entrou com Ctrl-(Z or D)
        if (cin.eof())
        {
            cout << endl << endl;
            cout << "YOU LEFT THE GAME!" << endl;
            return -1;
        }

        //verifica se houve uma entrada inválida
        if (cin.fail() || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << endl;
            cout << "Invalid command. Try again!" << endl;
            continue;
        }

        // verifica se o jogador pressionou 0 para voltar ao menu inicial
        if (!choose)
        {
            cout << endl << endl;
            return 0; // volta ao menu inicial
        }

        //cria labirinto com número < 10
        if (choose > 0 && choose < 10)
        {
            number = "0" + to_string(choose); // numero do labirinto deve ter 2 digitos
            mazeName = "MAZE_" + number + ".TXT";
            cout << endl << endl;
            return 1;
        }

        else
        {
            // cria labirinto com número > 10
            number = to_string(choose);
            mazeName = "MAZE_" + number + ".TXT";
            cout << endl << endl;
            return 1;
        }
    }
}

int ChooseMaze::choiceWinners() {
    /*
    Cria nome do do ficheirio que contém o a leaderboard do labirinto específico
    */
    int choose;
    string number;

    while (true)
    {
        cout << "Choose maze's leaderboard (Press 0 to return to Menu or Ctrl-(Z or D) to Exit): ";
        cin >> choose;

        //verifica se o jogador entrou com Ctrl-(Z or D)
        if (cin.eof())
        {
            cout << endl << endl;
            cout << "YOU LEFT THE GAME!" << endl;
            return -1;
        }

        //verifica se houve uma entrada inválida
        if (cin.fail() || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << endl;
            cout << "Invalid command. Try again!" << endl;
            continue;
        }

        // verifica se o jogador pressionou 0 para voltar ao menu inicial
        if (!choose)
        {
            cout << endl << endl;
            return 0;
        }

        if (choose > 0 && choose < 10)
        {
            number = "0" + to_string(choose); // numero do labirinto deve ter 2 digitos
            winnersStreamName = "MAZE_" + number + "_WINNERS.TXT";
            cout << endl << endl;
            return 1;
        }

        else
        {
            number = to_string(choose);
            winnersStreamName = "MAZE_" + number + "_WINNERS.TXT";
            cout << endl << endl;
            return 1;
        }
    }
}

