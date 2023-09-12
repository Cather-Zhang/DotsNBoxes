#include "GameStatus.h"
#include <iostream>
#include <vector>

#define MY_TEAM "BOTSNDOXES"

class Minimax {
public:
    Minimax();
    ~Minimax();

    GameStatus* minimaxAlphaBeta(GameStatus* currentState, int depth, int alpha, int beta, bool maximixingPlayer, std::vector<Edge*> bestMoves);
};