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

    vector<Edge*> moves;
    GameStatus* bestState = minimax->minimaxAlphaBeta(gs, 1, INT_MIN, INT_MAX, true, moves);
    
    cout << "Best state" << endl;
    bestState->board->printBoard();

    cout << "moves" << endl;
    for (Edge* move: moves) {
        move->print();
    } 

    /*
    while (!gs->isTerminal())
    {
        if (myTurn) 
        {
            cout << "all children of this state" << endl;
            gs->generateChildren(false);
            gs->printChildren();
            myTurn = false;

            cout << "My turn input move: " << endl;
            //Edge* nextMove = gs->getNextMove();
            //nextMove->print();
            string move;
            getline(cin, move);
            Edge* newEdge = new Edge(move);
            //newEdge->print();
            gs->update(newEdge);
            gs->board->printBoard();

        }
        else
        {
            myTurn = true;
            cout << "input opponent's move" << endl;
            string move;
            getline(cin, move);
            gs->update(new Edge(move));
            gs->board->printBoard();
            
        }
        
    }
    */


    return 0;
}

