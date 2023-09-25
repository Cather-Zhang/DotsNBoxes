#include "GameStatus.h"
#include "main.h"
#include <iostream>
using namespace std;

/**
 * Completely free memory of a GameStatus
*/
GameStatus::~GameStatus() {
    delete board;
    /*
    if (!children.empty()) {
        for (GameStatus* child: children) 
            delete child;
        children.clear();
    }
    */
}

/**
 * @brief Return boolean indicate if a gamestatus is terminal status (game is over)
 * 
 * @return true if game is over
 * @return false if game is still going
 */
bool GameStatus::isTerminal() {
    return minScore + maxScore == MAX_ROW * MAX_COL;
}


/**
 * @brief Update game status
 * 
 * @param e: Edge that is the new move
 * 
 * @return true if the new move scored, else false
 */
bool GameStatus::update(Edge* e) {
    this->previousMove = e;
    int key = e->toKey();

    // Add edge to board edges
    if (e->isVertical())
        this->board->verticalEdges[key] = e;
    else
        this->board->horizontalEdges[key] = e;
    
    // Update Player Type for game state
    if (e->playerName == MY_TEAM)
        this->team = MAX;
    else 
        this->team = MIN;
    
    // Check if the new move scored, and add to player's score
    int score = this->board->doesCompleteSquare(e);
    if(score != 0) {
        this->doesPrevMoveScore = true;
        score > 0 ? this->addToScore(MAX, score) : this->addToScore(MIN, abs(score));
        return true;
    }
    else this->doesPrevMoveScore = false;
    return false;
}


/**
 * @brief make a complete copy the current game status
 * 
 * @return GameStatus*: 
 *         The address of copied GameStatus
 */
GameStatus* GameStatus::copy() {
    return new GameStatus(this->board->copy(), this->team, this->maxScore, this->minScore, this->previousMove->copy(), this->easyEdge);
}


/**
 * @brief Evaluate the game status
 * 
 * @return int: 
 *         The static evaluation of this game status
 */
int GameStatus::evaluate() {
    int score = 0;
    score += (maxScore - minScore) * 100;
    Edge* e = previousMove;
    int chainsCreated = this->board->totalChainsCreated(e);
    if (e->playerName == MY_TEAM) {
        score += doesPrevMoveScore ? (chainsCreated * 80) : (chainsCreated * -80);
    }
    else {
        score += doesPrevMoveScore ? (chainsCreated * -80) : (chainsCreated * 80);
    }
    return score;
}

/**
 * @brief generate child nodes of current Game State
 * 
 * @return vector<GameStatus*>:
 *         A list of all child nodes with possible moves.
 *         The most promising child is put in front of the list to be evaulated first
*/
vector<GameStatus*> GameStatus::generateChildren() {
    vector<GameStatus*> children;


    // all child nodes with possible vertical edges
    for (int col = 0; col <= MAX_COL; col++) {
        for (int row = 0; row < MAX_ROW; row++) {
            if (!this->board->existEdge(VERTICAL, row, col)) {
                // Create a copy of the current state
                GameStatus* childState = this->copy();
                if (!doesPrevMoveScore) this->team == MAX ? childState->team = MIN : childState->team = MAX;
                string teamName;
                childState->team == MAX ? teamName = MY_TEAM : teamName = "opp";
                // alternate team if it is not a continued generation (second move)

                // Add the new vertical edge to the child state's board, update previousMove
                int key = row * (MAX_COL + 1) + col;
                Edge* newEdge = new Edge(VERTICAL, row, col, teamName);
                childState->board->verticalEdges[key] = newEdge;
                childState->previousMove = newEdge;

                int pointScored = childState->board->doesCompleteSquare(newEdge);
                if (pointScored != 0) {
                    childState->doesPrevMoveScore = true;
                    (pointScored > 0) ? childState->addToScore(MAX, pointScored) : childState->addToScore(MIN, abs(pointScored));
                    // add to front of the array so we can check this first
                    children.insert(children.begin(), childState);
                }
                else {
                    children.push_back(childState);
                }
            }
        }
    }





    // all child nodes with possible horizontal edges
    for (int col = 0; col < MAX_COL; col++) {
        for (int row = 0; row <= MAX_ROW; row++) {
            if (!this->board->existEdge(HORIZONTAL, row, col)) {
                // Create a copy of the current state
                GameStatus* childState = this->copy();

                // alternate team if it is not a continued generation (second move)
                if (!doesPrevMoveScore) this->team == MAX ? childState->team = MIN : childState->team = MAX;
                string teamName;
                childState->team == MAX ? teamName = MY_TEAM : teamName = "opp";
                // Add the new horizontal edge to the child state's board, update previousMove
                int key = row * (MAX_COL + 1) + col;
                Edge* newEdge = new Edge(HORIZONTAL, row, col, teamName);
                childState->board->horizontalEdges[key] = newEdge;
                childState->previousMove = newEdge;

                // Check if the new edge scores
                int pointScored = childState->board->doesCompleteSquare(newEdge);
                if (pointScored != 0) {
                    childState->doesPrevMoveScore = true;
                    (pointScored > 0) ? childState->addToScore(MAX, pointScored) : childState->addToScore(MIN, abs(pointScored));
                    // add to front of the array so we can check this first
                    children.insert(children.begin(), childState);
                }
                else {
                    children.push_back(childState);
                }
            }
        }
    }

/*
    // For internal testing
    // all child nodes with possible vertical edges
    for (int col = 0; col <= MAX_COL; col++) {
        for (int row = 0; row < MAX_ROW; row++) {
            if (!this->board->existEdge(VERTICAL, row, col)) {
                // Create a copy of the current state
                GameStatus* childState = this->copy();
                if (!doesPrevMoveScore) this->team == MAX ? childState->team = MIN : childState->team = MAX;
                string teamName;
                childState->team == MAX ? teamName = MY_TEAM : teamName = "opp";
                // alternate team if it is not a continued generation (second move)

                // Add the new vertical edge to the child state's board, update previousMove
                int key = row * (MAX_COL + 1) + col;
                Edge* newEdge = new Edge(VERTICAL, row, col, teamName);
                childState->board->verticalEdges[key] = newEdge;
                childState->previousMove = newEdge;

                int pointScored = childState->board->doesCompleteSquare(newEdge);
                if (pointScored != 0) {
                    childState->doesPrevMoveScore = true;
                    (pointScored > 0) ? childState->addToScore(MAX, pointScored) : childState->addToScore(MIN, abs(pointScored));
                    // add to front of the array so we can check this first
                    children.insert(children.begin(), childState);
                }
                else {
                    children.push_back(childState);
                }
            }
        }
    }

*/


    //this->children = children;
    return children;
}


/*
// For debugging purpose
void GameStatus::printChildren() {
    int a = 0;
    for (GameStatus* child: this->childNodes) {
        cout << "Child " << a << endl;
        child->board->printBoard();
        a++;
    } 
}
*/


/**
 * @brief Check if there is an edge that is easy to put on (not third or fourth edge)
 * @return true if there is, else false       
*/
bool GameStatus::existEasyEdge() {
    if (!easyEdge) return false;
    for (int col = 0; col <= MAX_COL; col++) {
        for (int row = 0; row < MAX_ROW; row++) {
            if (!this->board->existEdge(VERTICAL, row, col)) {
                if (!this->board->isThirdOrFourthEdge(row, col, VERTICAL)) {
                    return true;
                }
            }
        }
    }

    for (int col = 0; col < MAX_COL; col++) {
        for (int row = 0; row <= MAX_ROW; row++) {
            if (!this->board->existEdge(HORIZONTAL, row, col)) {
                if (!this->board->isThirdOrFourthEdge(row, col, HORIZONTAL)) {
                    return true;
                }
            }
        }
    }
    this->easyEdge = false;
    return false;
}

/**
 * @brief Add score to corresponding player type
 * 
 * @param type: the player type points are added to
 * @param score: the score to be added
*/
void GameStatus::addToScore(PlayerType type, int score) {
    if (type == MAX) maxScore+=score;
    else minScore+=score;
}
