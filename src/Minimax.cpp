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
        return make_pair(currentState->evaluate(), vector<GameStatus*>{currentState});
    }

    vector<GameStatus*> bestPath;

    //cout << "not terminal yet" << endl;
    if (maximizingPlayer) {
        int max_eval = INT_MIN;
        //GameStatus* bestState;
        pair<int, vector<GameStatus*>> childResult;

        if (currentState->childNodes.empty())
            currentState->generateChildren(false);

        for (GameStatus* child: currentState->childNodes) {
            //cout<<"Child state board"<<endl;
            //child->board->printBoard();
            if (!child->childNodes.empty()) {
                childResult = minimaxAlphaBeta(child, depth - 1, alpha, beta, true);
            }
            else {
                childResult = minimaxAlphaBeta(child, depth - 1, alpha, beta, false);
            }
            int eval = childResult.first;
            
            if (eval > max_eval) {
                max_eval = eval;
                bestPath = childResult.second;
                bestPath.insert(bestPath.begin(), currentState);
            }

            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return make_pair(max_eval, bestPath);
    }
    else {
        int min_eval = INT_MAX;
        //GameStatus* bestState;
        //GameStatus* childState;
        pair<int, vector<GameStatus*>> childResult;

        if (currentState->childNodes.empty())
            currentState->generateChildren(false);
        for (GameStatus* child: currentState->childNodes) {
            if (!child->childNodes.empty()) {
                childResult = minimaxAlphaBeta(child, depth - 1, alpha, beta, true);
            }
            else {
                childResult = minimaxAlphaBeta(child, depth - 1, alpha, beta, false);
            }
            int eval = childResult.first;

            if (eval < min_eval) {
                min_eval = eval;
                bestPath = childResult.second;
                bestPath.insert(bestPath.begin(), currentState);
            }

            beta = min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        return  make_pair(min_eval, bestPath);
    }
}

pair<int, vector<GameStatus*>> Minimax::iterativeDeepeningMinimax(GameStatus* currentState, int timeLimit) {
    pair<int, vector<GameStatus*>> bestPath;
    int maxDepth = 1;

    auto startTime = chrono::high_resolution_clock::now();
    auto endTime = startTime + chrono::seconds(timeLimit);
    
    while (true) {
        auto currentTime = chrono::high_resolution_clock::now();
        if (currentTime >= endTime) {
            break; // Time limit exceeded, exit the loop
        }

        pair<int, vector<GameStatus*>> currentPath = minimaxAlphaBeta(currentState, maxDepth, INT_MIN, INT_MAX, true);
        currentPath.second[1]->previousMove->print();
        bestPath = currentPath;
        maxDepth++;
    }

    return bestPath;
}

Edge* Minimax::getNextMove(GameStatus* gs) {
    pair<int, vector<GameStatus*>> paths = iterativeDeepeningMinimax(gs, 1000000);
    Edge* nextMove = paths.second[1]->previousMove;
    return nextMove;
}
