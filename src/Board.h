#pragma once
#include <unordered_map>
#include "Edge.h"

#define MAX_ROW 9
#define MAX_COL 9

class Board {
public:
	Board();
	virtual ~Board();

    std::unordered_map<int, Edge*> verticalEdges;
	std::unordered_map<int, Edge*> horizontalEdges;

	void printBoard();
	bool existEdge(EdgeType edgeType, int startX, int startY);
	int doesCompleteSquare(Edge* e);
	void put(Edge* e);
};

