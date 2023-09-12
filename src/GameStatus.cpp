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
void GameStatus::update(Edge* e) {
    this->previousMove = e;
    int key = e->startX * MAX_COL + e->startY;
    if (e->isVertical())
        this->board->verticalEdges[key] = e;
    else
        this->board->horizontalEdges[key] = e;
    if(this->board->doesCompleteSquare(e->type, e->startX, e->startY))
            this->team == MAX ? this->maxScore++ : this->minScore++;
}

/**
 * @brief copy the current game status
 * 
 * @return GameStatus* the address of copied GameStatus
 */
GameStatus* GameStatus::copy() {
    Board* newBoard = new Board(*this->board);
    return new GameStatus(newBoard, this->team);
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

                // alternate team if it is not a continued generation (second move)
                if (!isContinue) this->team == MAX ? this->team = MIN : this->team = MAX;

                // Add the new vertical edge to the child state's board, update previousMove
                int key = row * MAX_COL + col;
                Edge* newEdge = new Edge(VERTICAL, row, col, MY_TEAM);
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

    // all child nodes with possible vertical edges
    for (int col = 0; col < MAX_COL; col++) {
        for (int row = 0; row <= MAX_ROW; row++) {
            if (!this->board->existEdge(HORIZONTAL, row, col)) {
                // Create a copy of the current state
                GameStatus* childState = this->copy();

                // alternate team if it is not a continued generation (second move)
                if (!isContinue) this->team == MAX ? this->team = MIN : this->team = MAX;

                // Add the new horizontal edge to the child state's board, update previousMove
                int key = row * MAX_COL + col;
                Edge* newEdge = new Edge(HORIZONTAL, row, col, MY_TEAM);
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