#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "main.h"
using namespace std;

int main(int argc, char *argv[]) {
    // bool myTurn = true;

    // Use the constants defined in main.h
    cout << "Welcome to game: " << PROGRAM_NAME << endl;
    cout << "The grid is " << MAX_ROW << " x " << MAX_COL << endl;

    cout << "Constructing a new game" << endl;

/*
    Edge* my1 = new Edge(VERTICAL, 0, 0, MY_TEAM);
    Edge* opp1 = new Edge(HORIZONTAL, 0, 0, "opp");

    Edge* my2 = new Edge(HORIZONTAL, 0, 1, MY_TEAM);
    Edge* opp2 = new Edge(VERTICAL, 0, 1, "opp");

    Board* b = new Board();
    b->put(my1);
    b->put(opp1);
    b->put(my2);
    b->put(opp2);

    GameStatus* gs = new GameStatus(b, MIN);

    Minimax* minimax = new Minimax();

    pair<int, vector<GameStatus*>> paths = minimax->minimaxAlphaBeta(gs, 3, INT_MIN, INT_MAX, true);
    Edge* nextMove = paths.second[1]->previousMove;
    cout << "Best path" << endl;
    nextMove->print();
    cout << nextMove->toString() << endl;
    cout << "final evaluation: " << paths.first << endl;
    
*/

    GameStatus* gs = new GameStatus(MIN);
    Minimax* minimax = new Minimax;
    while (!gs->isTerminal())
    {
        // check if go file exists for our player
        std::string filename = MY_TEAM".go"; 
        std::ifstream file(filename);
        if (file.good()) 
        {        
            cout << "Generating move" << endl;
            Edge* nextMove = minimax->getNextMove(gs);
            nextMove->print();

            // Write to new line in move file
            std::ofstream outputFile("move_file", std::ios::app);
            if (outputFile.is_open()) {
                outputFile << nextMove->toString();
                outputFile.close();
                std::cout << "Wrote to move file" << std::endl;
            } 
            else {
                std::cout << "Failed to open momve file" << std::endl;
            }

            cout << "Board after my move" << endl;
            gs->board->printBoard();
        }

        else
        {
            cout << "Getting opponent's move" << endl;
            string move;

            // get last line from move file
            std::ifstream inputFile("move_file", std::ios::in);

            if (inputFile.is_open()) {
                std::string line;

                while (std::getline(inputFile, line)) {
                    move = line;
                }
                inputFile.close();
                std::cout << "Read from move file" << std::endl;
            }     
            else {
                std::cerr << "Failed to open the file." << std::endl;
            }

            // put opponent's move on board
            Edge* newMove = new Edge(move);
            gs->board->put(newMove);
        
            cout << "Board after opponent's move" << endl;
            gs->board->printBoard();
        }      
    }
    return 0;
}

