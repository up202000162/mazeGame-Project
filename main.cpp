#include <iostream>
#include "Game.h"
#include "ChooseMaze.h"

int main() {

    ChooseMaze chooseMaze;
    int createdFile;
    enum {GO_TO_MENU = 0, CTRL_Z = -1, END = 0};

    while (true)
    {

        Uint menuChoice = Game::menu();

        switch (menuChoice)
        {
            case 1:

                if(Game::rules() == GO_TO_MENU) continue;

                else //Jogador pressionou 2 para jogar após ver as regras
                {

                    while (true)
                    {
                        /*Escolha do número do maze e armazenamento do nome do ficheiro
                        no atributo 'maze_name' da classe ChoseMaze */
                        createdFile = chooseMaze.choiceMaze();

                        if (createdFile == CTRL_Z)
                            return END;

                        if (!createdFile) // Jogador deseja voltar ao menu inicial
                            break;

                        /*Caso jogador não pressione '0' ou 'Ctrl-Z' cria nome do maze normalmente
                        a partir do número que ele inseriu e o armazena na classe ChoseMaze*/

                        Game game(chooseMaze.getMazeName());  // cria jogo

                        if (game.isValid())  // verifica se o jogo 'MAZE_XX.TXT' existe e, caso exista, chama método 'play'
                        {
                            game.play();
                            return END;
                        }
                    }
                    continue;  // Retorna ao menu inicial caso pressione '0' na escolha do número do maze
                }

            case 2:

                while (true)
                {
                    /*Escolha do número do maze e armazenamento do nome do ficheiro
                    no atributo 'maze_name' da classe ChoseMaze */
                    createdFile = chooseMaze.choiceMaze();

                    if (createdFile == CTRL_Z)
                        return END;

                    if (!createdFile)
                        break;  // Jogador deseja voltar ao menu inicial


                    /*Caso jogador não pressione '0' ou 'Ctrl-Z' cria nome do maze normalmente
                    a partir do número que ele inseriu e o armazena na classe ChoseMaze*/

                    Game game(chooseMaze.getMazeName());  // cria jogo
                    if (game.isValid())  // verifica se o jogo 'MAZE_XX.TXT' existe e, caso exista, chama método 'play'
                    {
                        game.play();
                        return END;
                    }
                }
                continue;  // Retorna ao menu inicial caso pressione '0' na escolha do número do maze

            case 3:
            {

                bool goToMenu = Game::showWinners(); // Imprime leaderboard

                if (goToMenu) continue;

                return END;
            }

            default:
                //Exit (0)
                cout << "YOU LEFT THE GAME!\n\n";
                return END;
        }
    }
}