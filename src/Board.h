#pragma once
#include <unordered_map>
#include "Edge.h"

#define MAX_ROW 3
#define MAX_COL 3

class Board {
public:
	Board();
	virtual ~Board();

    std::unordered_map<int, Edge*> verticalEdges;
	std::unordered_map<int, Edge*> horizontalEdges;

	void printBoard();
	bool existEdge(EdgeType edgeType, int startX, int startY);
	bool doesCompleteSquare(EdgeType type, int startX, int startY);
	void put(Edge* e);
};

