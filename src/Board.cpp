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
    if (e->type == VERTICAL) {
        if (((existEdge(VERTICAL, startX, startY - 1)) && existEdge(HORIZONTAL, startX, startY - 1) && existEdge(HORIZONTAL, startX + 1, startY - 1)) ||  //left square
            ((existEdge(VERTICAL, startX, startY + 1) && existEdge(HORIZONTAL, startX, startY) && existEdge(HORIZONTAL, startX + 1, startY)))) //right square
        {
            return (e->playerName == MY_TEAM) ? 1 : -1;
        }
        else return 0;
    }
    else {
        if (((existEdge(VERTICAL, startX - 1, startY)) && existEdge(VERTICAL, startX - 1, startY + 1) && existEdge(HORIZONTAL, startX - 1, startY)) ||  //top square
            ((existEdge(VERTICAL, startX, startY + 1) && existEdge(VERTICAL, startX, startY) && existEdge(HORIZONTAL, startX + 1, startY)))) //bottom square
        {
            return (e->playerName == MY_TEAM) ? 1 : -1;
        }
        else return 0;
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

