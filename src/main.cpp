#include <iostream>
#include <string>
#include <sstream>

#include "main.h"
using namespace std;

int main(int argc, char *argv[]) {
    bool myTurn = true;

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
        if (myTurn) 
        {
            
            cout << "Generating move" << endl;
            Edge* nextMove = minimax->getNextMove(gs);
            nextMove->print();

            if (gs->update(nextMove)) myTurn = true;
            else myTurn = false;
            cout << "Board after my move" << endl;
            gs->board->printBoard();
        }

        else
        {
            cout << "input opponent's move" << endl;
            string move;
            getline(cin, move);
            Edge* newMove = new Edge(move);
            if (gs->update(newMove)) myTurn = false;
            else myTurn = true;

            cout << "Board after opponent's move" << endl;
            gs->board->printBoard();

        }
        
    }
    


    return 0;
}

