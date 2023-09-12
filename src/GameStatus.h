#pragma once
#include "Board.h"
#include <vector>

enum PlayerType {
    MIN,
    MAX
};

class GameStatus {
public:
    GameStatus(PlayerType t) : board(new Board()), team(t), minScore(0), maxScore(0) {}
    GameStatus(Board* b, PlayerType t) : board(b), team(t), minScore(0), maxScore(0) {}
    virtual ~GameStatus();
    
    Board* board;
    PlayerType team;
    int minScore, maxScore;
    Edge* previousMove;
    std::vector<GameStatus*> childNodes;

    bool isTerminal();
    Edge* getNextMove();
    void update(Edge* e);
    GameStatus* copy();
    int evaluate();
    std::vector<GameStatus*> generateChildren(bool isContinue);
    void printChildren();
    void addToScore();
    bool isInitialState();
};