#include "GameStatus.h"
#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
#include <ctime>

class Minimax {
public:
    Minimax();
    ~Minimax();

    std::pair<int, std::vector<GameStatus*>> minimaxAlphaBeta(GameStatus* currentState, int depth, int alpha, int beta, bool maximizingPlayer, std::chrono::_V2::system_clock::time_point endtime);
    std::pair<int, std::vector<GameStatus*>> minimaxAlphaBeta(GameStatus* currentState, int depth, int alpha, int beta, bool maximizingPlayer);

    std::pair<int, std::vector<GameStatus*>> iterativeDeepeningMinimax(GameStatus* currentState, int timeLimit);
    Edge* getNextMove(GameStatus* gs);
};