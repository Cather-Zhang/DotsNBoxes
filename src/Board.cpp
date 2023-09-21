#include "Board.h"
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

Board::Board() {
	//cout << "Making a new board" << endl;
}

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

void Board::put(Edge* e) {
    int key = e->startX * (MAX_COL + 1) + e->startY;
    if (e->isHorizontal()) {
        horizontalEdges[key] = e;
    }
    else {
        verticalEdges[key] = e;
    }
}

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
