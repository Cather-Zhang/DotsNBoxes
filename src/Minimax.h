#include "GameStatus.h"
#include <iostream>
#include <vector>

#define MY_TEAM "BOTSNDOXES"

class Minimax {
public:
    Minimax();
    ~Minimax();

    std::pair<int, std::vector<GameStatus*>> minimaxAlphaBeta(GameStatus* currentState, int depth, int alpha, int beta, bool maximizingPlaye);
    std::pair<int, std::vector<GameStatus*>> iterativeDeepeningMinimax(GameStatus* currentState, int timeLimit);
    Edge* getNextMove(GameStatus* gs);
};