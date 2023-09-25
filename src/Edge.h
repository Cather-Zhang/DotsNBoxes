#pragma once

#include <string>

#define MAX_ROW 9
#define MAX_COL 9
#define MY_TEAM "BotsNDoxes"
//#define MY_TEAM "boo"

enum EdgeType {
    VERTICAL,
    HORIZONTAL
};

enum Direction {
    UP, 
    DOWN,
    LEFT,
    RIGHT
};

class Edge {
public:
    int startX;
    int startY;
    EdgeType type;

    std::string playerName;

    Edge(EdgeType t, int x, int y, const std::string player) : startX(x), startY(y), type(t), playerName(player) {}
    Edge(std::string move);

    bool isVertical();
    bool isHorizontal();
    void print();
    std::string toString();
    int toKey();
    //bool isPassedMove();
    Edge* copy();
    bool isAtBoarder();

private:
    bool isValid(int x1, int y1, int x2, int y2);
};