#pragma once

#include <limits>

#include "Move.h"
#include "Board.h"
#include "BoardState.h"

class Search
{
public:
    Search(int maxDepth = 10);

    int Evaluate(Board& board);
    Move FindBestMove(Board& board);

private:
    int Minimax(Board& board, int depth, int maximizingPlayer, int alpha=std::numeric_limits<int>::min(), int beta= std::numeric_limits<int>::max());

private:
    int maxDepth;
};

