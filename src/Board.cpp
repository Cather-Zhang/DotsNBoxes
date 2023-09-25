#include "Board.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

Board::Board() {
	//cout << "Making a new board" << endl;
}

/**
 * Completely free memory of a board
*/
Board::~Board() {
    // Clear the map and delete the objects
    for (auto& pair : verticalEdges) {
        delete pair.second; // Delete the Object pointed to by the pointer
    }
    verticalEdges.clear();
    // Clear the map and delete the objects
    for (auto& pair : horizontalEdges) {
        delete pair.second; // Delete the Object pointed to by the pointer
    }
    horizontalEdges.clear();
}

/**
 * @brief print the all existing edges on the board
*/
void Board::printBoard() {
    //cout << "Vertical Edges on the board:" << endl;
    for (auto& pair : verticalEdges) {
        Edge* edge = pair.second;
        edge->print();
    }
    //cout << "Horizontal Edges on the board:" << endl;
    for (auto& pair : horizontalEdges) {
        Edge* edge = pair.second;
        edge->print();
    }

}


/**
 * @brief Check if the edge already exists on board
 * 
 * @param edgeType: the type of the edge (VERTICAL/HORIZONTAL)
 * @param startX: row
 * @param startY: column
 * 
 * @return true if the edge exist on board, else false
 * 
*/
bool Board::existEdge(EdgeType edgeType, int startX, int startY) {
    int key = startX * (MAX_COL + 1) + startY;
    if (edgeType == VERTICAL) {
        auto edge = verticalEdges.find(key);
        return (edge != verticalEdges.end());
    }
    else {
        auto edge = horizontalEdges.find(key);
        return (edge != horizontalEdges.end());  
    }
}


/**
 * @brief check if an edge will complete a square on board
 * 
 * @param e: the Edge to be checked
 * 
 * @return int:
 *         The points that the edge will score.
 *         Positive if maximizing player socres;
 *         Negative if opponent player scores;
 *         0 if it does not score
*/
int Board::doesCompleteSquare(Edge* e) {
    int startX = e->startX;
    int startY = e->startY;
    int score = 0;
    if (e->type == VERTICAL) 
    {
        // left square
        if ((existEdge(VERTICAL, startX, startY - 1)) && existEdge(HORIZONTAL, startX, startY - 1) && existEdge(HORIZONTAL, startX + 1, startY - 1)) {
            e->playerName == MY_TEAM ? score++ : score--;
        } 
        // right square
        if ((existEdge(VERTICAL, startX, startY + 1) && existEdge(HORIZONTAL, startX, startY) && existEdge(HORIZONTAL, startX + 1, startY)))
            e->playerName == MY_TEAM ? score++ : score--;
        }
    else 
    {
        //top square
        if ((existEdge(VERTICAL, startX - 1, startY)) && existEdge(VERTICAL, startX - 1, startY + 1) && existEdge(HORIZONTAL, startX - 1, startY)) {
            e->playerName == MY_TEAM ? score++ : score--;
        }

        //bottom square
        if ((existEdge(VERTICAL, startX, startY + 1) && existEdge(VERTICAL, startX, startY) && existEdge(HORIZONTAL, startX + 1, startY))) {
            e->playerName == MY_TEAM ? score++ : score--;
        }
    }
    return score; 
}


/**
 * @brief check if the edge creates a third edge
 * 
 * @param e: the edge to be checked
 * 
 * @return pair<bool, int>
 *         bool: true if the edge creates a third edge, else false
 *         int: the number of third edges created;
 *              positive if opponent creates third edges; else negative.
*/
pair<bool, int> Board::isThirdEdge(Edge* e) {
    int startX = e->startX;
    int startY = e->startY;
    int score = 0;
    if (e->type == VERTICAL) 
    {
        int neighborNumLeft = 0;
        int neighborNumRight = 0;
        // left square
        if (existEdge(VERTICAL, startX, startY - 1)) neighborNumLeft++;
        if (existEdge(HORIZONTAL, startX, startY - 1)) neighborNumLeft++;
        if (existEdge(HORIZONTAL, startX + 1, startY - 1)) neighborNumLeft++;
        if (neighborNumLeft == 2) {
            e->playerName == MY_TEAM ? score-- : score++;
        }
        
        // right square
        if (existEdge(VERTICAL, startX, startY + 1)) neighborNumRight++;
        if (existEdge(HORIZONTAL, startX, startY)) neighborNumRight++;
        if (existEdge(HORIZONTAL, startX + 1, startY)) neighborNumRight++;
        if (neighborNumRight == 2) {
            e->playerName == MY_TEAM ? score-- : score++;
        }
        return (score != 0) ? make_pair(true, score) : make_pair(false, score);
    }
    else {

        int neighborNumUp = 0;
        int neighborNumDown = 0;
        // up square
        if (existEdge(VERTICAL, startX - 1, startY)) neighborNumUp++;
        if (existEdge(VERTICAL, startX - 1, startY + 1)) neighborNumUp++;
        if (existEdge(HORIZONTAL, startX - 1, startY)) neighborNumUp++;
        if (neighborNumUp == 2) {
            e->playerName == MY_TEAM ? score-- : score++;
        }
        
        // down square
        if (existEdge(VERTICAL, startX, startY + 1)) neighborNumDown++;
        if (existEdge(VERTICAL, startX, startY)) neighborNumDown++;
        if (existEdge(HORIZONTAL, startX + 1, startY)) neighborNumDown++;
        if (neighborNumDown == 2) {
            e->playerName == MY_TEAM ? score-- : score++;
        }
        return (score != 0) ? make_pair(true, score) : make_pair(false, score);
    
    }
}

/**
 * @brief Add the new edge to board
 * 
 * @param e: The new edge to be added
 * 
*/
void Board::put(Edge* e) {
    int key = e->toKey();
    if (e->isHorizontal()) {
        horizontalEdges[key] = e;
    }
    else {
        verticalEdges[key] = e;
    }
}

/**
 * @brief Make a complete copy of board
 * 
 * @return Board*:
 *         the address of copied board 
*/
Board* Board::copy() {
    
    std::unordered_map<int, Edge*> newVerticalEdges;
    std::unordered_map<int, Edge*> newHorizontalEdges;

    // Iterate through the original map and create new Edge objects
    for (const auto& pair : verticalEdges) {
        Edge* copiedEdge = pair.second->copy();
        newVerticalEdges[pair.first] = copiedEdge;
    }
    for (const auto& pair : horizontalEdges) {  
        Edge* copiedEdge = pair.second->copy();
        newHorizontalEdges[pair.first] = copiedEdge;
    }

    Board* newBoard = new Board();
    newBoard->verticalEdges = newVerticalEdges;
    newBoard->horizontalEdges = newHorizontalEdges;
    //newBoard->printBoard();
    return newBoard;
}

/**
 * @brief check if the edge is third or fourth in a square
 * 
 * @param startX: row
 * @param startY: column
 * @param type: Edge Type
 * 
 * @return true if the edge is third or fourth edge, else false
*/
bool Board::isThirdOrFourthEdge(int startX, int startY, EdgeType type) {
    if (type == VERTICAL) 
    {
        int neighborNumLeft = 0;
        int neighborNumRight = 0;
        // left square
        if (existEdge(VERTICAL, startX, startY - 1)) neighborNumLeft++;
        if (existEdge(HORIZONTAL, startX, startY - 1)) neighborNumLeft++;
        if (existEdge(HORIZONTAL, startX + 1, startY - 1)) neighborNumLeft++;
        if (neighborNumLeft >= 2) {
            return true;
        }
        
        // right square
        if (existEdge(VERTICAL, startX, startY + 1)) neighborNumRight++;
        if (existEdge(HORIZONTAL, startX, startY)) neighborNumRight++;
        if (existEdge(HORIZONTAL, startX + 1, startY)) neighborNumRight++;
        if (neighborNumRight >= 2) {
            return true;
        }
        return false;
    }
    else {

        int neighborNumUp = 0;
        int neighborNumDown = 0;
        // up square
        if (existEdge(VERTICAL, startX - 1, startY)) neighborNumUp++;
        if (existEdge(VERTICAL, startX - 1, startY + 1)) neighborNumUp++;
        if (existEdge(HORIZONTAL, startX - 1, startY)) neighborNumUp++;
        if (neighborNumUp >= 2) {
            return true;
        }
        
        // down square
        if (existEdge(VERTICAL, startX, startY + 1)) neighborNumDown++;
        if (existEdge(VERTICAL, startX, startY)) neighborNumDown++;
        if (existEdge(HORIZONTAL, startX + 1, startY)) neighborNumDown++;
        if (neighborNumDown >= 2) {
            return true;
        }
        return false;
    }
}


pair<int, Edge*> Board::chainsCreated(Edge* e, Direction dir) {
    int startX = e->startX;
    int startY = e->startY;
    Edge* lastEdge;

    int count = 0;
    if (e->type == VERTICAL) {
        Edge* newEdge;
        if (dir == LEFT) {
            int neighborNum = 0;
            Direction newDir;
            if (existEdge(VERTICAL, startX, startY - 1)) neighborNum++;
            else {
                newEdge = new Edge(VERTICAL, startX, startY - 1, "");
                newDir = LEFT;
            }

            if (existEdge(HORIZONTAL, startX, startY - 1)) neighborNum++;
            else {
                newEdge = new Edge(HORIZONTAL, startX, startY - 1, "");
                newDir = UP;
            }

            if (existEdge(HORIZONTAL, startX + 1, startY - 1)) neighborNum++;
            else {
                newEdge = new Edge(HORIZONTAL, startX + 1, startY - 1, "");
                newDir = DOWN;
            }

            if (neighborNum == 2) {
                if (newEdge->isAtBoarder()) {
                    count++;
                    lastEdge = newEdge;
                }
                else {
                    pair<int, Edge*> result = chainsCreated(newEdge, newDir);
                    count += 1 + result.first;
                    lastEdge = result.second;
                }
            }
            else if (neighborNum == 3 && !existEdge(e->type, e->startX, e->startY)) {
                count++;
                lastEdge = e;
            }
            else return make_pair(0, e);
        }
        else if (dir == RIGHT) {
            int neighborNum = 0;
            Direction newDir;

            if (existEdge(VERTICAL, startX, startY + 1)) neighborNum++;
            else {
                newEdge = new Edge(VERTICAL, startX, startY + 1, "");
                newDir = RIGHT;
            }

            if (existEdge(HORIZONTAL, startX, startY)) neighborNum++;
            else {
                newEdge = new Edge(HORIZONTAL, startX, startY, "");
                newDir = UP;
            }

            if (existEdge(HORIZONTAL, startX + 1, startY)) neighborNum++;
            else {
                newEdge = new Edge(HORIZONTAL, startX + 1, startY, "");
                newDir = DOWN;
            }

            if (neighborNum == 2) {
                if (newEdge->isAtBoarder()) {
                    count++;
                    lastEdge = newEdge;
                }
                else {
                    pair<int, Edge*> result = chainsCreated(newEdge, newDir);
                    count += 1 + result.first;
                    lastEdge = result.second;
                }
            }
            else if (neighborNum == 3 && !existEdge(e->type, e->startX, e->startY)) {
                count++;
                lastEdge = e;
            }
            else return make_pair(0, e);
        }
    }
    else {
        Edge* newEdge;
        if (dir == UP) {
            int neighborNum = 0;
            Direction newDir;
            if (existEdge(VERTICAL, startX - 1, startY)) neighborNum++;
            else {
                newEdge = new Edge(VERTICAL, startX - 1, startY, "");
                newDir = LEFT;
            }

            if (existEdge(HORIZONTAL, startX - 1, startY)) neighborNum++;
            else {
                newEdge = new Edge(HORIZONTAL, startX - 1, startY, "");
                newDir = UP;
            }

            if (existEdge(VERTICAL, startX - 1, startY + 1)) neighborNum++;
            else {
                newEdge = new Edge(VERTICAL, startX - 1, startY + 1, "");
                newDir = RIGHT;
            }


            if (neighborNum == 2) {
                if (newEdge->isAtBoarder()) {
                    count++;
                    lastEdge = newEdge;
                }
                else {
                    pair<int, Edge*> result = chainsCreated(newEdge, newDir);
                    count += 1 + result.first;
                    lastEdge = result.second;
                }
            }
            else if (neighborNum == 3 && !existEdge(e->type, e->startX, e->startY)) {
                count++;
                lastEdge = e;
            }
            else return make_pair(0, e);
        }
        else if (dir == DOWN) {
            int neighborNum = 0;
            Direction newDir;

            if (existEdge(VERTICAL, startX, startY)) neighborNum++;
            else {
                newEdge = new Edge(VERTICAL, startX, startY, "");
                newDir = LEFT;
            }

            if (existEdge(HORIZONTAL, startX + 1, startY)) neighborNum++;
            else {
                newEdge = new Edge(HORIZONTAL, startX + 1, startY, "");
                newDir = DOWN;
            }

            if (existEdge(VERTICAL, startX, startY + 1)) neighborNum++;
            else {
                newEdge = new Edge(VERTICAL, startX, startY + 1, "");
                newDir = RIGHT;
            }


            if (neighborNum == 2) {
                if (newEdge->isAtBoarder()) {
                    count++;
                    lastEdge = newEdge;
                }
                else {
                    pair<int, Edge*> result = chainsCreated(newEdge, newDir);
                    count += 1 + result.first;
                    lastEdge = result.second;
                }
            }
            else if (neighborNum == 3 && !existEdge(e->type, e->startX, e->startY)) {
                count++;
                lastEdge = e;
            }
            else return make_pair(0, e);
        }
    }
    return make_pair(count, lastEdge);
}

/*
bool Board::isThirdEdgeInSquare(Edge* e) {
    int startX = e->startX;
    int startY = e->startY;
    if (e->type == VERTICAL) {
        if (existEdge(HORIZONTAL, startX - 1, startY - 1) &&
            existEdge(HORIZONTAL, startX - 1, startY) &&
            existEdge(HORIZONTAL, startX + 1, startY - 1) &&
            existEdge(HORIZONTAL, startX + 1, startY) &&

            existEdge(VERTICAL, startX - 1, startY - 1) &&
            existEdge(VERTICAL, startX, startY - 1) &&
            existEdge(VERTICAL, startX - 1, startY + 1) &&
            existEdge(VERTICAL, startX, startY + 1)) 
            {
                return (!existEdge(VERTICAL, startX - 1, startY) && !existEdge(HORIZONTAL, startX, startY - 1) && !existEdge(HORIZONTAL, startX, startY));
            }


        if (existEdge(HORIZONTAL, startX, startY - 1) &&
            existEdge(HORIZONTAL, startX, startY) &&
            existEdge(HORIZONTAL, startX + 2, startY - 1) &&
            existEdge(HORIZONTAL, startX + 2, startY) &&

            existEdge(VERTICAL, startX, startY - 1) &&
            existEdge(VERTICAL, startX + 1, startY - 1) &&
            existEdge(VERTICAL, startX, startY + 1) &&
            existEdge(VERTICAL, startX + 1, startY + 1)) 
            {
                return (!existEdge(VERTICAL, startX + 1, startY) && !existEdge(HORIZONTAL, startX + 1, startY - 1) && !existEdge(HORIZONTAL, startX + 1, startY));
            }
    }
    else {
        if (existEdge(HORIZONTAL, startX - 1, startY - 1) &&
            existEdge(HORIZONTAL, startX - 1, startY) &&
            existEdge(HORIZONTAL, startX + 1, startY - 1) &&
            existEdge(HORIZONTAL, startX + 1, startY) &&

            existEdge(VERTICAL, startX - 1, startY - 1) &&
            existEdge(VERTICAL, startX, startY - 1) &&
            existEdge(VERTICAL, startX - 1, startY + 1) &&
            existEdge(VERTICAL, startX, startY + 1)) 
            {
                return (!existEdge(VERTICAL, startX - 1, startY) && !existEdge(HORIZONTAL, startX, startY - 1) && !existEdge(VERTICAL, startX, startY));
            }


        if (existEdge(HORIZONTAL, startX - 1, startY) &&
            existEdge(HORIZONTAL, startX - 1, startY + 1) &&
            existEdge(HORIZONTAL, startX + 1, startY) &&
            existEdge(HORIZONTAL, startX + 1, startY + 1) &&

            existEdge(VERTICAL, startX - 1 , startY) &&
            existEdge(VERTICAL, startX, startY) &&
            existEdge(VERTICAL, startX - 1, startY + 2) &&
            existEdge(VERTICAL, startX, startY + 2)) 
            {
                return (!existEdge(VERTICAL, startX - 1, startY + 1) && !existEdge(HORIZONTAL, startX, startY + 1) && !existEdge(VERTICAL, startX, startY + 1));
            }
    }
    return false;
}
*/


int Board::totalChainsCreated(Edge* e) {
    int count = 0;
    if (e->type == VERTICAL) {
        pair<int, Edge*> resultLeft = chainsCreated(e, LEFT);
        count = resultLeft.first;
        if (doesCompleteSquare(resultLeft.second) == 0 || count == 0) 
            count += chainsCreated(e, RIGHT).first;
    }
    else {
        pair<int, Edge*> resultUp = chainsCreated(e, UP);
        count = resultUp.first;
        if (doesCompleteSquare(resultUp.second) == 0 || count == 0) 
            count += chainsCreated(e, DOWN).first;
    }
    return count;
}