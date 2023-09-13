#include "GameStatus.h"
#include "main.h"
#include <iostream>
using namespace std;

GameStatus::~GameStatus() {
    delete board;
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
 * @brief Get the next best move using minimax alpha-beta pruning
 * 
 * @return Edge* the ptr to the edge
 */
Edge* GameStatus::getNextMove() {
    //TODO
    return new Edge(VERTICAL, 1, 3, MY_TEAM);
}

/**
 * @brief Update game status
 * 
 * @param e 
 */
bool GameStatus::update(Edge* e) {
    this->previousMove = e;
    this->childNodes.clear();
    int key = e->startX * (MAX_COL + 1) + e->startY;
    if (e->isVertical())
        this->board->verticalEdges[key] = e;
    else
        this->board->horizontalEdges[key] = e;
    if (e->playerName == MY_TEAM)
        this->team = MAX;
    else 
        this->team = MIN;
    if(this->board->doesCompleteSquare(e->type, e->startX, e->startY)) {
        if (this->team == MAX) {
            this->maxScore++;
            this->team = MIN;
        }
        else {
            this->minScore++;
            this->team = MAX;
        }
        return true;
    }
    return false;
}

/**
 * @brief copy the current game status
 * 
 * @return GameStatus* the address of copied GameStatus
 */
GameStatus* GameStatus::copy() {
    Board* newBoard = new Board(*this->board);
    return new GameStatus(newBoard, this->team, this->maxScore, this->minScore);
}

/**
 * @brief Evaluate the game status
 * 
 * @return int the static evaluation of this game status
 */
int GameStatus::evaluate() {
    //TODO
    return maxScore - minScore;
}

vector<GameStatus*> GameStatus::generateChildren(bool isContinue) {
    //TODO
    vector<GameStatus*> children;

    // all child nodes with possible vertical edges
    for (int col = 0; col <= MAX_COL; col++) {
        for (int row = 0; row < MAX_ROW; row++) {
            if (!this->board->existEdge(VERTICAL, row, col)) {
                // Create a copy of the current state
                GameStatus* childState = this->copy();
                if (!isContinue) this->team == MAX ? childState->team = MIN : childState->team = MAX;
                string teamName;
                childState->team == MAX ? teamName = MY_TEAM : teamName = "opp";
                // alternate team if it is not a continued generation (second move)

                // Add the new vertical edge to the child state's board, update previousMove
                int key = row * (MAX_COL + 1) + col;
                Edge* newEdge = new Edge(VERTICAL, row, col, teamName);
                childState->board->verticalEdges[key] = newEdge;
                childState->previousMove = newEdge;

                if (childState->board->doesCompleteSquare(VERTICAL, row, col)) {
                    childState->addToScore();
                    // generate possible second moves
                    childState->generateChildren(true);
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
                if (!isContinue) this->team == MAX ? childState->team = MIN : childState->team = MAX;
                string teamName;
                childState->team == MAX ? teamName = MY_TEAM : teamName = "opp";
                // Add the new horizontal edge to the child state's board, update previousMove
                int key = row * (MAX_COL + 1) + col;
                Edge* newEdge = new Edge(HORIZONTAL, row, col, teamName);
                childState->board->horizontalEdges[key] = newEdge;
                childState->previousMove = newEdge;

                if (childState->board->doesCompleteSquare(HORIZONTAL, row, col)) {
                    childState->addToScore();
                    // generate possible second moves
                    childState->generateChildren(true);
                    // add to front of the array so we can check this first
                    children.insert(children.begin(), childState);
                }
                else {
                    children.push_back(childState);
                }
            }
        }
    }
    this->childNodes = children;
    
    return children;
}

void GameStatus::printChildren() {
    int a = 0;
    for (GameStatus* child: this->childNodes) {
        cout << "Child " << a << endl;
        child->board->printBoard();
        a++;
    } 
}

void GameStatus::addToScore() {
    if (team == MAX) maxScore++;
    else minScore++;
}

bool GameStatus::isInitialState() {
    return (minScore == 0 && maxScore == 0 && board->verticalEdges.empty() && board->horizontalEdges.empty());
}
