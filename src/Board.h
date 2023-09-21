#pragma once
#include <unordered_map>
#include "Edge.h"



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
	Board* copy();
	std::pair<bool, int> isThirdEdge(Edge* e);
};

