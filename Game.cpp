
#include <iostream>
#include <limits>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <sstream>
#include "Game.h"
#include "ChooseMaze.h"

const Uint MAX_NAME_LENGTH = 15; // número máximo de caracteres do nome do ganhador que pode ser escrito no ficheiro
const Uint TIME_LENGTH = 3; // quantidade de caracteres do tempo
const Uint MAZE_XX = 7;



// Construtor
//---------------------------------------------------------------------------------------------
Game::Game(const string& fileName) {
    ifstream mazeStream;
    string strRow, strCol, line, copyMazeName = fileName;
    Uint row, col;

    copyMazeName.resize(MAZE_XX); // Armazena valor "MAZE_XX" do nome do ficheiro MAZE_XX.TXT
    winnersFile = copyMazeName + "_WINNERS.TXT"; // Cria nome do ficheiro dos winners a partir do nome do ficheiro do maze

    mazeName = fileName;

    mazeStream.open(mazeName);
    if (mazeStream.is_open()) // Verifica se o jogo existe
    {
        fileOpened = true;

        getline(mazeStream, strRow, 'x');
        getline(mazeStream, strCol);
        row = stringToInt(strRow);
        col = stringToInt(strCol);

        maze = Maze(row, col); // constrói labirinto

        // Leitura do ficheiro
        char* symbol;
        for (Uint l = 0; l < row; l++)
        {

            getline(mazeStream, line);

            for (size_t c = 0; c < line.size(); c++)
            {
                symbol = &line[c];

                switch (*symbol)
                {
                    case 'R':
                    {
                        Robot robot(l, c);
                        robots.push_back(robot);
                        continue;
                    }

                    case 'H':
                    {
                        player = Player(l, c, *symbol);
                        continue;
                    }

                    case '*': case '+':
                    {
                        Post post(l, c, *symbol);
                        maze.addPost(post);
                        continue;
                    }

                    case 'O':
                    {
                        Gate gate;
                        gate.setCol(c);
                        gate.setRow(l);
                        gates.push_back(gate);
                        continue;
                    }
                }
            }
        }
        mazeStream.close();
    }

    else
        fileOpened = false;
}
//---------------------------------------------------------------------------------------------



// Métodos privados
//---------------------------------------------------------------------------------------------
Uint Game::stringToInt(string &str) {
    /*
    converte um string para inteiro.
    */
    Uint number;
    stringstream convertString(str);
    convertString >> number;
    return number;
}

bool Game::isValidMovement(char moveTo) {
    switch (toupper(moveTo))
    {
        case 'Q': case 'W': case 'E':
        case 'A': case 'S': case 'D':
        case 'Z': case 'X': case 'C':
            return true;

    }
    return false;
}

bool Game::playerLose() const {
    /*
    Verifica se o jogador perdeu
    */
    if (!player.isAlive())
        return true;
    return false;
}

bool Game::playerWon() const {
    /*
    Verifica se o jogador ganhou
    */
    if (enteredGate)
        return true;

    return false;
}

template<typename T1, typename T2>
bool Game::collide(const T1& class1, const T2& class2) {
    // verifica colisões entre quaisquer classes

    if (class1.getRow() == class2.getRow() && class1.getCol() == class2.getCol())
        return true;
    return false;
}

Position Game::distanceRobotPlayer(Position player, Position robot) {
    /*
    retorna uma struct com diferença (linha, coluna) entre um robô e o jogador.
    se  'distance.row' > 0  -> robô está encima.
    se  'distance.row' < 0  -> robô está embaixo.
    se  'distance.col' > 0  -> robô está à esquerda.
    se  'distance.col' < 0  -> robô está à direita.
    */
    Position distance{};

    distance.row = player.row - robot.row;
    distance.col = player.col - robot.col;
    return distance;
}

void Game::moveRobot(Robot& robot)
{
    /*
    se  'diffPositions.row' > 0  -> robô está em cima e deve descer ( robot.setRow += 1 ).
    se  'diffPositions.row' < 0  -> robô está em baixo e deve subir ( robot.setRow -= 1 ).
    se  'diffPositions.row' == 0 -> mantém a posição da linha, ou seja, basta não atualizar a posição.
    se  'diffPositions.col' > 0  -> robô está à esquerda e deve ir à direita ( robot.setCol += 1 ).
    se  'diffPositions.col' < 0  -> robô está à direita e deve ir à esquerda ( robot.setCol += 1 ).
    se  'diffPositions.col' == 0 -> mantém a posição da coluna, ou seja, basta não atualizar a posição.
    */

    Position robotPosition, playerPosition, diffPositions;
    robotPosition.row = int(robot.getRow()); robotPosition.col = int(robot.getCol());
    playerPosition.row = int(player.getRow()); playerPosition.col = int(player.getCol());

    diffPositions = distanceRobotPlayer(playerPosition, robotPosition);

    Uint oldRow = robot.getRow(), oldCol = robot.getCol();

    if (diffPositions.row > 0) robot.setRow(oldRow + 1);
    else if (diffPositions.row < 0) robot.setRow(oldRow - 1);

    if (diffPositions.col > 0) robot.setCol(oldCol + 1);
    else if (diffPositions.col < 0) robot.setCol(oldCol - 1);

    if (collide(robot, player))
    {
        player.setAsDead();
        return;
    }

    for (const auto& post : maze.getPosts())
    {
        if (collide(robot, post))
        {
            if (post.getSymbol() == '*')
            {
                robot.setCol(oldCol);
                robot.setRow(oldRow);
                robot.setAsDead();
                return;
            }
            else if (post.getSymbol() == '+')
            {
                robot.setAsDead();
                return;
            }
        }
    }

    for (auto& robot_i : robots)
    {
        if (&robot_i == &robot)
            continue;

        if (collide(robot, robot_i))
        {
            robot.setAsDead();
            robot_i.setAsDead();
        }
    }

    for (const auto& gate : gates)
    {
        if (collide(robot, gate))
            robot.setAsDead();
    }
}

bool Game::movePlayer(char moveTo, Movement playerMovement) {
    /*Atualiza posição do jogador e verifica se houve colisões.
      A ordem de verificação de colisões aqui estabelecida é importante,
      pois exitem prioridades de 'cout' caso exista coincidênncia de posições.*/

    switch (toupper(moveTo))
    {
        case 'W': playerMovement.row -= 1; break;
        case 'X': playerMovement.row += 1; break;
        case 'D': playerMovement.col += 1; break;
        case 'A': playerMovement.col -= 1; break;
        case 'Q': playerMovement.row -= 1; playerMovement.col -= 1; break;
        case 'Z': playerMovement.row += 1; playerMovement.col -= 1; break;
        case 'C': playerMovement.row += 1; playerMovement.col += 1; break;
        case 'E': playerMovement.row -= 1; playerMovement.col += 1; break;
    }

    Uint oldRow = player.getRow();
    Uint oldCol = player.getCol();
    player.setRow(playerMovement.row);
    player.setCol(playerMovement.col);

    for (auto& gate : gates) // verifica se colide com alguma saída
    {
        if (entryGate(gate))
        {
            player.setRow(oldRow);
            player.setCol(oldCol);
            enteredGate = true;
            return true;
        }
    }

    for (const auto& robot : robots) // verifica se colide com algum robô
    {
        if (collide(robot, player))
        {
            if (!robot.isAlive())
            {
                player.setRow(oldRow);
                player.setCol(oldCol);
                return false;  // jogador não pode se movimentar para essa posição
            }
            else
            {
                player.setAsDead();
                return true;
            }
        }
    }

    for (const auto& post : maze.getPosts()) // verifica se colide com algum poste
    {
        if (collide(player, post))
        {
            if (!post.isElectrified())
            {
                player.setRow(oldRow);
                player.setCol(oldCol);
                return false;  // jogador não pode se movimentar para essa posição
            }
            else
            {
                player.setRow(oldRow);
                player.setCol(oldCol);
                player.setAsDead();
                return true;
            }
        }
    }
    return true; // movimento válido e sem colisões
}

bool Game::entryGate(const Gate& gate) {
    // verifica se jogar entrou em um portão

    if (gate.getRow() == player.getRow() && gate.getCol() == player.getCol())
        return true;
    return false;
}

void Game::showGameDisplay() const {
    /*
    Imprime labirinto com posições atualizadas.
    A ordem estabelecida aqui é importante pois existem prioridades
    de 'cout' quando ocorrem colisões. 'Gates' são a maior prioridades
    enquanto 'Posts' são a menor.
    */
    bool foundPosition;
    for (Uint row = 0; row < maze.getNumRows(); row++)
    {
        cout << endl;

        for (Uint col = 0; col < maze.getNumCols(); col++)
        {
            foundPosition = false;

            for (const auto& gate : gates)  // verifica se a linha e coluna é ocupada por um portão
            {
                if (gate.getRow() == row && gate.getCol() == col)
                {
                    foundPosition = true;
                    cout << gate.getSymbol();
                    break;
                }
            }
            if (foundPosition) continue;

            if (player.getRow() == row && player.getCol() == col)  // verifica se a linha e coluna é ocupada pelo jogador
            {
                cout << player.getSymbol();
                continue;
            }

            for (const auto& robot : robots)  // verifica se a linha e coluna é ocupada por um robô
            {
                if (robot.getRow() == row && robot.getCol() == col)
                {
                    foundPosition = true;
                    cout << robot.getSymbol();
                    break;
                }
            }
            if (foundPosition) continue;

            for (const auto& post : maze.getPosts())  // verifica se a linha e coluna é ocupada por um poste
            {
                if (post.getRow() == row && post.getCol() == col)
                {
                    foundPosition = true;
                    cout << post.getSymbol();
                    break;
                }
            }
            if (foundPosition) continue;

            cout << ' '; // caso não encotre nenhuma das classes acima
        }
    }
    cout << endl;
}

bool ascendingTimeOrder(const Player& p1, const Player& p2) {
    if (p1.getTime() == p2.getTime())
        return (p1.getName() < p2.getName());
    else // 'else' não necessário, mas torna o programa mais legível
        return (p1.getTime() < p2.getTime());
}

void Game::sortAndShowWinners(fstream& winnersStream, string& lastWinnerName, const time_t& lastWinnerTime){
    vector<Player> winners;
    string title, division;

    //reajusta nome para 15 caracteres
    if (lastWinnerName.length() >= MAX_NAME_LENGTH)
    {
        lastWinnerName.resize(MAX_NAME_LENGTH); //reajusta nome para os 15 primeiros caracteres
        winnersStream << lastWinnerName << " -  " << setw(TIME_LENGTH) << setfill('0') << lastWinnerTime << endl;
    }
    else
    {
        winnersStream << lastWinnerName;
        for (unsigned int i = lastWinnerName.length(); i < MAX_NAME_LENGTH; i++)
            winnersStream << " "; //completa nome até atingir 15 caracteres

        winnersStream << " -  " << setw(TIME_LENGTH) << setfill('0') << lastWinnerTime << endl;
    }

    winnersStream.seekg(SEEK_SET); // apontador retorna ao início do ficheiro para realizar leitura
    getline(winnersStream, title); getline(winnersStream, division);

    string winnerName, winnerTime;
    Player winner;
    while (!winnersStream.eof())
    {
        getline(winnersStream, winnerName, '-');
        getline(winnersStream, winnerTime);
        winner.setName(winnerName);
        winner.setTime(winnerTime);
        winners.push_back(winner);
    }
    winners.pop_back(); // necessário devido à tentativa de leitura duplicada da ultima linha ao final do ficheiro pelo ciclo while acima
    winnersStream.close();

    sort(winners.begin(), winners.end(), ascendingTimeOrder); // ordena vetor de winners por ordem crescente de tempo


    // imprime Leaderboard
    cout << endl << title << endl << division << endl;
    for (const auto& w : winners)
        cout << w.getName() << "-" << w.getTime() << endl;
}
//---------------------------------------------------------------------------------------------



// Métodos públicos
//---------------------------------------------------------------------------------------------
Uint Game::rules() {
    /*
    lê ficheiro que contêm as regras do jogo e retorna na forma
    de um inteiro próximo passo após jogador ler as regras
    */
    cout << "RULES" << endl << "-------------------------------------------------------" << endl;

    ifstream rulesStream;
    string line;
    rulesStream.open("RULES.txt");
    while (!rulesStream.eof())
    {
        getline(rulesStream, line);
        cout << line << endl;
    }
    rulesStream.close();

    Uint choose;
    while (true)
    {
        cout << endl << "Press 0 to come back to Menu or 2 to play: "; cin >> choose;

        //verifica se o jogador entrou com Ctrl-(Z ou D)
        if (cin.eof())
        {
            cin.clear();
            cout << endl << endl << "Invalid command!"; continue;
        }

        //verificação de entrada inválida
        if (cin.fail() || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << endl << "Invalid command!"; continue;
        }

        //verificação de entrada não disponível para execução
        if (!(choose == 0 || choose == 2))
        {
            cout << endl << endl << "Invalid number!"; continue;
        }
        cout << endl << endl;
        return choose;
    }
}

Uint Game::menu() {
    /*
      imprime o menu com as opções para ver regras, jogar e sair.
      retorna 0 caso o jogador queira sair do jogo, 1 quando ele
      quer ver as regras, 2 quando ele quer jogar ou 3 quando quer
      ver alguma leaderboard
      */

    cout << "MENU" << endl << "-------------------------------------------------------" << endl;
    Uint numberChoose;
    while (true)
    {
        cout << "Choose an option:\n\n";
        cout << "1) Rules" << endl << "2) Play" << endl << "3) Winners" << endl << "0) Exit" << endl;
        cout << "Go to: ";
        cin >> numberChoose;

        //verifica se o jogador entrou com Ctrl-Z
        if (cin.eof())
        {
            cin.clear();
            cin.get();
            cout << endl << endl << "Invalid command!\n";
            continue;
        }

        //verificação de entrada inválida
        if (cin.fail() || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << endl << "Invalid command!\n"; continue;
        }
        //verificação de entrada não disponível para execução
        if (!(numberChoose == 0 || numberChoose == 1 || numberChoose == 2 || numberChoose == 3))
        {
            cout << endl << endl << "Invalid number!\n";continue;
        }
        cout << endl << endl;
        return numberChoose;
    }
}

bool Game::showWinners() {
    string choose, title, division;
    ifstream winnersStream;
    ChooseMaze chooseMaze;
    vector<Player> winners;
    int createdFile, afterWinners;

    while (true)
    {
        createdFile = chooseMaze.choiceWinners();

        if (createdFile == -1) return false;  // Jogador sai do jogo com Ctrl-Z
        if (!createdFile) return true; // Jogador pressionou 0 para voltar ao menu inicial na escolha do maze

        winnersStream.open(chooseMaze.getWinnersStreamName());
        if (!winnersStream.is_open())
        {
            cout << "File empty!" << endl;
            continue;
        }

        winnersStream.seekg(SEEK_SET); // apontador retorna ao início do ficheiro para realizar leitura
        getline(winnersStream, title); getline(winnersStream, division);

        string winnerName, winnerTime;
        Player winner;
        while (!winnersStream.eof())
        {
            getline(winnersStream, winnerName, '-');
            getline(winnersStream, winnerTime);
            winner.setName(winnerName);
            winner.setTime(winnerTime);
            winners.push_back(winner);
        }
        winners.pop_back(); // necessário devido à tentativa de leitura duplicada da ultima linha ao final do ficheiro pelo ciclo while acima
        winnersStream.close();

        sort(winners.begin(), winners.end(), ascendingTimeOrder); // ordena vetor de winners pelo tempo

        cout << title << endl << division << endl;

        for (const auto& w : winners)
            cout << w.getName() << "-" << w.getTime() << endl;
        // imprime leaderboard ordenada pelo tempo


        // próximo passo no jogo
        cout << endl << "Press 0 to come back to Menu or Ctrl-(Z or D) to Exit: ";
        cin >> afterWinners;

        //verifica se o jogador entrou com Ctrl-(Z ou D)
        if (cin.eof())
        {
            cout << endl << endl;
            cout << "YOU LEFT THE GAME!" << endl;
            return false;
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

        if (afterWinners != 0)
        {
            cout << endl << endl << "Invalid number!\n";
            continue;
        }

        cout << endl << endl;
        return true;  // retorna ao menu principal
    }
}

bool Game::isValid() const {
    //verifica se o maze que foi escolhido para jogar existe

    if (fileOpened)
        return true;
    cout << "Maze not found! Try Again!" << endl;
    return false;
}

void Game::play() {
    cout << "PLAY" << endl << "-------------------------------------------------------" << endl;
    fstream winnersStream;

    showGameDisplay();
    static chrono::steady_clock::time_point begin = chrono::steady_clock::now(); // Início da contagem do tempo

    char moveTo;
    Movement playerMovement{};

    while (true)
    {
        playerMovement.row = player.getRow();
        playerMovement.col = player.getCol();
        cout << "Next movement: "; cin >> moveTo;

        //verifica se o jogador saiu do jogo com Ctrl-(Z ou D)
        if (cin.eof())
        {
            cout << endl << endl;
            cout << "YOU LEFT THE GAME!" << endl;
            return; //Jogo acaba com Ctrl-Z
        }

        // verifica se a entrada é um movimento válido
        if (!(isValidMovement(moveTo) && cin.peek() == '\n'))
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << endl;
            cout << "Invalid Movement. Try again!" << endl; continue;
        }

        // move jogador e verifica se movimento é válido
        if (!movePlayer(moveTo, playerMovement))
        {
            cout << endl << "YOU CAN'T MOVE TO THIS POSITION!" << endl;
            continue;
        }

        if (playerWon())
        {
            chrono::steady_clock::time_point end = chrono::steady_clock::now(); // fim da contagem do tempo
            time_t diffTime = chrono::duration_cast<chrono::seconds>(end - begin).count(); // tempo que o jogador demorou à ganhar

            cout << endl << endl;
            showGameDisplay();

            string  winnerName;
            cout << endl << "CONGRATULATIONS. YOU WON!" << endl;
            cin.get(); // necessário porque o '\n' fica no buffer e o comando getline abaixo o leria automaticamente


            while (winnerName.empty())
            {
                cout << "ENTER YOUR NAME: ";

                getline(cin, winnerName);

                if (winnerName.empty())
                {
                    cout << endl << endl << "Empty name! Please insert some characters. " << endl;
                    continue;
                }
            }

            player.setName(winnerName);
            player.setTime(to_string(diffTime));

            winnersStream.open(winnersFile, ios::in); // verifica se ficheiro dos ganhadores já existe
            if (winnersStream.is_open())  // se o ficheiro já existe, fecha-o e o abre para leitura e para escrita
            {
                winnersStream.close();
                winnersStream.open(winnersFile, ios::app | ios::in);
            }
            else
                // se o ficheiro não existe, cria-se um novo ficheiro para escrita e para leitura e escreve-se as duas primeiras linhas dele
            {
                winnersStream.open(winnersFile, ios::app | ios::in);
                winnersStream << "Player          - Time" << endl << "----------------------" << endl;
            }

            sortAndShowWinners(winnersStream, winnerName, diffTime);
            winnersStream.close();
            return;
        }

        if (playerLose())
        {
            cout << endl << endl;
            showGameDisplay();
            cout << endl << "GAME OVER!" << endl; return;
        }

        // move um robô de cada vez
        for (auto& robot : robots)
        {
            if (!robot.isAlive())
                continue;  // impede que robôs mortos se movam

            moveRobot(robot); // atualiza posição do robô

            if (playerLose())
            {
                cout << endl << endl;
                showGameDisplay();
                cout << endl << "GAME OVER!" << endl;
                return;
            }
        }

        cout << endl << endl;
        showGameDisplay();  // imprime labirinto atualizado
    }
}
//--------------------------------------------------------------------------------------------
