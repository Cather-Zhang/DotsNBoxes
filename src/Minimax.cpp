#include "Minimax.h"

using namespace std;


Minimax::Minimax() {
}

Minimax::~Minimax() {
}


GameStatus* Minimax::minimaxAlphaBeta(GameStatus* currentState, int depth, int alpha, int beta, bool maximizingPlayer, vector<Edge*> bestMoves) {
    // we have reached terminal state or max depth
    cout << "Start minimax at depth " << depth << endl;
    currentState->board->printBoard();
    if (depth == 0 || currentState->isTerminal()) {
        cout << "reached terminal" << endl;
        return currentState;
    }
    cout << "not terminal yet" << endl;
    if (maximizingPlayer) {
        cout << "maximizing player" << endl;
        int max_eval = INT_MIN;
        GameStatus* bestState;
        GameStatus* childState;
        currentState->generateChildren(false);
        for (GameStatus* child: currentState->childNodes) {
            if (!child->childNodes.empty()) {
                childState = minimaxAlphaBeta(child, depth, alpha, beta, true, bestMoves);
            }
            else {
                childState = minimaxAlphaBeta(child, depth - 1, alpha, beta, false, bestMoves);
            }
            int eval = bestState->evaluate();
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
            if (eval == max_eval) 
                bestState = childState;
                bestMoves.push_back(bestState->previousMove);
        }
        return  bestState;    
    }
    else {
        int min_eval = INT_MAX;
        GameStatus* bestState;
        GameStatus* childState;
        currentState->generateChildren(false);
        for (GameStatus* child: currentState->childNodes) {
            if (!child->childNodes.empty()) {
                childState = minimaxAlphaBeta(child, depth, alpha, beta, true, bestMoves);
            }
            else {
                childState = minimaxAlphaBeta(child, depth - 1, alpha, beta, false, bestMoves);
            }
            int eval = bestState->evaluate();
            min_eval = min(min_eval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) {
                break;
            }
            if (eval == min_eval) 
                bestState = childState;
                bestMoves.push_back(bestState->previousMove);
        }
        return  bestState;       
    }
}

