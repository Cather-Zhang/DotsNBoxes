#pragma once
#include "Board.h"
#include <vector>

enum PlayerType {
    MIN,
    MAX
};

class GameStatus {
public:
    GameStatus(PlayerType t) : board(new Board()), team(t), minScore(0), maxScore(0), doesPrevMoveScore(false), previousMove(new Edge(VERTICAL, 0, 0, "")) {}
    GameStatus(Board* b, PlayerType t) : board(b), team(t), minScore(0), maxScore(0), doesPrevMoveScore(false) {}
    GameStatus(Board* b, PlayerType t, int max, int min, Edge* prev) : board(b), team(t), maxScore(max), minScore(min), doesPrevMoveScore(false), previousMove(prev) {}
    virtual ~GameStatus();
    
    Board* board;
    PlayerType team;
    int minScore, maxScore;
    Edge* previousMove;
    bool doesPrevMoveScore;
    //std::vector<GameStatus*> children;

    bool isTerminal();
    Edge* getNextMove();
    bool update(Edge* e);
    GameStatus* copy();
    int evaluate();
    std::vector<GameStatus*> generateChildren();
    //void printChildren();
    void addToScore(PlayerType t, int score);
};