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

bool Board::doesCompleteSquare(EdgeType type, int startX, int startY) {
    if (type == VERTICAL) {
        return (((existEdge(VERTICAL, startX, startY - 1)) && existEdge(HORIZONTAL, startX, startY - 1) && existEdge(HORIZONTAL, startX + 1, startY - 1)) ||  //left square
                ((existEdge(VERTICAL, startX, startY + 1) && existEdge(HORIZONTAL, startX, startY) && existEdge(HORIZONTAL, startX + 1, startY)))); //right square
    }
    else {
        return (((existEdge(VERTICAL, startX - 1, startY)) && existEdge(VERTICAL, startX - 1, startY + 1) && existEdge(HORIZONTAL, startX - 1, startY)) ||  //top square
                ((existEdge(VERTICAL, startX, startY + 1) && existEdge(VERTICAL, startX, startY) && existEdge(HORIZONTAL, startX + 1, startY)))); //bottom square
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

