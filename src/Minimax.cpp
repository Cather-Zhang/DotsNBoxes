#include "Minimax.h"
#include <limits>


using namespace std;
#define MAX_DEPTH 30


Minimax::Minimax() {
}

Minimax::~Minimax() {
}

/**
 * @brief Minimax algorithm with alpha-beta pruning and exit with a endtime limit
 * 
 * @param currentState: the current state of the game
 * @param depth: the max depth we are searching
 * @param alpha: alpha value
 * @param beta: beta value
 * @param maximizingPlayer: if we are maximizing value or not
 * @param endtime: the time when the program needs to exit by
 * 
 * @return pair<int, vector<GameStatus*>>:
 *         int: The evaulation score that is maximized or minimized
 *         vector<GameStatus*>: The best game states along the best path
 * 
 * if time limit reached, return pair(-1, empty list)
 * 
*/

pair<int, vector<GameStatus*>> Minimax::minimaxAlphaBeta(GameStatus* currentState, int depth, int alpha, int beta, bool maximizingPlayer, chrono::_V2::system_clock::time_point endtime) {
    // we have reached terminal state or max depth
    //cout << "Start minimax at depth " << depth << endl;
    //currentState->board->printBoard();
    auto currentTime = chrono::high_resolution_clock::now();

    if (currentTime >= endtime) {
        return make_pair(-1, vector<GameStatus*>{});
    }

    if (depth == 0 || currentState->isTerminal()) {
        //cout << "reached terminal" << endl;
        return make_pair(currentState->evaluate(), vector<GameStatus*>{currentState->copy()});
    }

    // Keep track of best States along the paths
    vector<GameStatus*> bestPath;

    //cout << "not terminal yet" << endl;
    if (maximizingPlayer) {
        int max_eval = INT_MIN;
        pair<int, vector<GameStatus*>> childResult;
        bool exceedTime = false;

        vector<GameStatus*> children = currentState->generateChildren();
        for (GameStatus* child: children) {

            
            // Debug Purpose
            /*

            cout<<"Child state board"<<endl;
            child->board->printBoard();
            cout<<"Child new move: ";
            child->previousMove->print();
            */
    
            childResult = child->doesPrevMoveScore ? 
                minimaxAlphaBeta(child, depth - 1, alpha, beta, true, endtime) :
                minimaxAlphaBeta(child, depth - 1, alpha, beta, false, endtime);
            
            if (childResult.second.empty()) {
                exceedTime = true; 
                break;
            }
            int eval = childResult.first;
            
            if (eval > max_eval) {
                max_eval = eval;
                bestPath = childResult.second;
                bestPath.insert(bestPath.begin(), currentState->copy());
            }

            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }

        //Free memory
        for (GameStatus* child: children) 
            delete child;
        children.clear();

        return exceedTime ? make_pair(-1, vector<GameStatus*>{}) : make_pair(max_eval, bestPath);
    }
    else {
        int min_eval = INT_MAX;
        pair<int, vector<GameStatus*>> childResult;
        bool exceedTime = false;

        vector<GameStatus*> children = currentState->generateChildren();
        for (GameStatus* child: children) {
            
            
            // Debug Purpose
            /*
            cout<<"Child state board"<<endl;
            child->board->printBoard();
            cout<<"Child new move: ";
            child->previousMove->print();
            */
            
            
            
            childResult = child->doesPrevMoveScore ? 
                minimaxAlphaBeta(child, depth - 1, alpha, beta, false, endtime) :
                minimaxAlphaBeta(child, depth - 1, alpha, beta, true, endtime);
            
            if (childResult.second.empty()) {
                exceedTime = true;
                break;
            }

            int eval = childResult.first;

            if (eval < min_eval) {
                min_eval = eval;
                bestPath = childResult.second;
                bestPath.insert(bestPath.begin(), currentState->copy());
            }

            beta = min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        for (GameStatus* child: children) 
            delete child;
        children.clear();
        return exceedTime ? make_pair(-1, vector<GameStatus*>{}) : make_pair(min_eval, bestPath);
    }
}


/**
 * @brief Minimax algorithm with alpha-beta pruning
 * 
 * @param currentState: the current state of the game
 * @param depth: the max depth we are searching
 * @param alpha: alpha value
 * @param beta: beta value
 * @param maximizingPlayer: if we are maximizing value or not
 * 
 * @return pair<int, vector<GameStatus*>>:
 *         int: The evaulation score that is maximized or minimized
 *         vector<GameStatus*>: The best game states along the best path
 * 
*/
pair<int, vector<GameStatus*>> Minimax::minimaxAlphaBeta(GameStatus* currentState, int depth, int alpha, int beta, bool maximizingPlayer) {
    // we have reached terminal state or max depth
    //cout << "Start minimax at depth " << depth << endl;
    //currentState->board->printBoard();

    if (depth == 0 || currentState->isTerminal()) {
        //cout << "reached terminal" << endl;
        return make_pair(currentState->evaluate(), vector<GameStatus*>{currentState->copy()});
    }

    // Keep track of best States along the paths
    vector<GameStatus*> bestPath;

    //cout << "not terminal yet" << endl;
    if (maximizingPlayer) {
        int max_eval = INT_MIN;
        pair<int, vector<GameStatus*>> childResult;
        
        vector<GameStatus*> children  =  currentState->generateChildren();
        for (GameStatus* child: children) {
        
        /*
        if (currentState->children.empty())
            currentState->generateChildren();
        for (GameStatus* child: currentState->children) {
        */   
            /*
            // Debug Purpose
            cout<<"Child state board"<<endl;
            child->board->printBoard();
            cout<<"Child new move: ";
            child->previousMove->print();
            */
    
            childResult = child->doesPrevMoveScore ? 
                minimaxAlphaBeta(child, depth - 1, alpha, beta, true) :
                minimaxAlphaBeta(child, depth - 1, alpha, beta, false);
            
 
            int eval = childResult.first;
            
            if (eval > max_eval) {
                max_eval = eval;
                bestPath = childResult.second;
                bestPath.insert(bestPath.begin(), currentState->copy());
            }

            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break;
            }
        }

        //Free memory
        
        for (GameStatus* child: children) 
            delete child;
        children.clear();
        

        return make_pair(max_eval, bestPath);
    }
    else {
        int min_eval = INT_MAX;
        pair<int, vector<GameStatus*>> childResult;
    
        
        vector<GameStatus*> children  =  currentState->generateChildren();
        for (GameStatus* child: children) {
        
        /*
        if (currentState->children.empty())
            currentState->generateChildren();
        for (GameStatus* child: currentState->children) {
        */    
            
            /*
            // Debug Purpose
            cout<<"Child state board"<<endl;
            child->board->printBoard();
            cout<<"Child new move: ";
            child->previousMove->print();
            */
            
            
            childResult = child->doesPrevMoveScore ? 
                minimaxAlphaBeta(child, depth - 1, alpha, beta, false) :
                minimaxAlphaBeta(child, depth - 1, alpha, beta, true);

            int eval = childResult.first;

            if (eval < min_eval) {
                min_eval = eval;
                bestPath = childResult.second;
                bestPath.insert(bestPath.begin(), currentState->copy());
            }

            beta = min(beta, eval);
            if (beta <= alpha) {
                break;
            }
        }
        
        for (GameStatus* child: children) 
            delete child;
        children.clear();
        

        return make_pair(min_eval, bestPath);
    }
}



/**
 * @brief Iterative deepening minimax algorithm within a time limit
 * 
 * @param: currentState: The current game state
 * @param: timeLimit: the time limit for searching
 * 
 * @return pair<int, vector<GameStatus*>>:
 *         int: The evaulation score that is maximized or minimized
 *         vector<GameStatus*>: The best game states along the best path
*/
pair<int, vector<GameStatus*>> Minimax::iterativeDeepeningMinimax(GameStatus* currentState, int timeLimit) {
    pair<int, vector<GameStatus*>> bestPath;
    int maxDepth = 1;

    auto startTime = chrono::high_resolution_clock::now();
    auto endTime = startTime + chrono::seconds(timeLimit);
    
    while (maxDepth < MAX_DEPTH) {
        //auto currentTime = chrono::high_resolution_clock::now();

        pair<int, vector<GameStatus*>> currentPath = minimaxAlphaBeta(currentState, maxDepth, INT_MIN, INT_MAX, true, endTime);
        if (currentPath.second.empty()) break;
        //currentPath.second[1]->previousMove->print();
        bestPath = currentPath;
        cout<<"depth "<<maxDepth<< " completed"<< endl;
        maxDepth++;

        /*
        chrono::_V2::system_clock::time_point currentTime = chrono::high_resolution_clock::now();
        if (currentTime >= endTime) {
            break; // Time limit exceeded, exit the loop
        }
        */
    }

    return bestPath;
}

/**
 * @brief Generate the next move based on current game state
 * 
 * @param gs: Current game state
 * 
 * @return Edge*: 
 *         The best edge for next move
*/
Edge* Minimax::getNextMove(GameStatus* gs) {
    pair<int, vector<GameStatus*>> paths;
    //auto startTime = chrono::high_resolution_clock::now();
    //auto endTime = startTime + chrono::seconds(10);

    // If there exist an edge does not complete square or make a third edge,
    // we only go depth 1 for searching (since there is no chain scoring)
    if (gs->existEasyEdge()) 
        paths = minimaxAlphaBeta(gs, 1, INT_MIN, INT_MAX, true);
    //else paths = minimaxAlphaBeta(gs, 3, INT_MIN, INT_MAX, true);
    // If there is no easy move, iterative deepening minimax is used
    else paths = iterativeDeepeningMinimax(gs, 9);

    Edge* nextMove = paths.second[1]->previousMove->copy();
    /*
    cout << "deleting" << endl;
    for (GameStatus* child: gs->children) 
        delete child;
    */
    for (GameStatus* path: paths.second) 
        delete path;
    return nextMove;
}
