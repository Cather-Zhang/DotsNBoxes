#include "Minimax.h"
#include <limits>
#include <chrono>

using namespace std;


Minimax::Minimax() {
}

Minimax::~Minimax() {
}


pair<int, vector<GameStatus*>> Minimax::minimaxAlphaBeta(GameStatus* currentState, int depth, int alpha, int beta, bool maximizingPlayer) {
    // we have reached terminal state or max depth
    //cout << "Start minimax at depth " << depth << endl;
    //currentState->board->printBoard();
    if (depth == 0 || currentState->isTerminal()) {
        //cout << "reached terminal" << endl;
        return make_pair(currentState->evaluate(), vector<GameStatus*>{currentState->copy()});
    }

    vector<GameStatus*> bestPath;
    //vector<GameStatus*> children;

    //cout << "not terminal yet" << endl;
    if (maximizingPlayer) {
        int max_eval = INT_MIN;
        pair<int, vector<GameStatus*>> childResult;
        vector<GameStatus*> children = currentState->generateChildren();
        for (GameStatus* child: children) {
            /*
            cout<<"Child state board"<<endl;
            child->board->printBoard();
            cout<<"Child new move: ";
            child->previousMove->print();
            */
            
               
    
            childResult = child->doesPrevMoveScore ? 
                minimaxAlphaBeta(child, depth, alpha, beta, true) :
                minimaxAlphaBeta(child, depth - 1, alpha, beta, false);
            
            int eval = childResult.first;
            
            if (eval > max_eval) {
                max_eval = eval;
                bestPath = childResult.second;
                bestPath.insert(bestPath.begin(), currentState->copy());
            }

            alpha = max(alpha, eval);
            //delete child;
            if (beta <= alpha) {
                break;
            }
        }
        children.clear();

        return make_pair(max_eval, bestPath);
    }
    else {
        int min_eval = INT_MAX;
        //GameStatus* bestState;
        //GameStatus* childState;
        pair<int, vector<GameStatus*>> childResult;

        vector<GameStatus*> children = currentState->generateChildren();
        for (GameStatus* child: children) {
            
            /*
            cout<<"Child state board"<<endl;
            child->board->printBoard();
            cout<<"Child new move: ";
            child->previousMove->print();
            */
            
            
            childResult = child->doesPrevMoveScore ? 
                minimaxAlphaBeta(child, depth, alpha, beta, false) :
                minimaxAlphaBeta(child, depth - 1, alpha, beta, true);
            int eval = childResult.first;

            if (eval < min_eval) {
                min_eval = eval;
                bestPath = childResult.second;
                bestPath.insert(bestPath.begin(), currentState->copy());
            }

            beta = min(beta, eval);
            //delete child;
            if (beta <= alpha) {
                break;
            }
        }
        children.clear();

        return make_pair(min_eval, bestPath);
    }
}

pair<int, vector<GameStatus*>> Minimax::iterativeDeepeningMinimax(GameStatus* currentState, int timeLimit) {
    pair<int, vector<GameStatus*>> bestPath;
    int maxDepth = 1;

    auto startTime = chrono::high_resolution_clock::now();
    auto endTime = startTime + chrono::seconds(timeLimit-2);
    
    while (true) {
        auto currentTime = chrono::high_resolution_clock::now();
        if (currentTime >= endTime) {
            break; // Time limit exceeded, exit the loop
        }

        pair<int, vector<GameStatus*>> currentPath = minimaxAlphaBeta(currentState, maxDepth, INT_MIN, INT_MAX, true);
        //currentPath.second[1]->previousMove->print();
        bestPath = currentPath;
        currentTime = chrono::high_resolution_clock::now();
        if (currentTime >= endTime) {
            break; // Time limit exceeded, exit the loop
        }
        //cout<<"depth "<<maxDepth<< " completed"<< endl;
        maxDepth++;
    }

    return bestPath;
}

Edge* Minimax::getNextMove(GameStatus* gs) {
    pair<int, vector<GameStatus*>> paths;
    //if (gs->board->verticalEdges.size()+gs->board->horizontalEdges.size() <= (MAX_COL+1)*MAX_ROW)
    paths = minimaxAlphaBeta(gs, 1, INT_MIN, INT_MAX, true);
    //else paths = iterativeDeepeningMinimax(gs, 10);
    Edge* nextMove = paths.second[1]->previousMove->copy();
    /*
    for (GameStatus* gs: paths.second) {
        delete gs;
    }
    */
    return nextMove;
}
