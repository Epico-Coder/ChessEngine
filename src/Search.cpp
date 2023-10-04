#include "Search.h"

#include <limits>
#include <iostream>

Search::Search(int maxDepth)
    : maxDepth(maxDepth)
{
}

int Search::Evaluate(Board& board)
{
    auto tempBoard = board;
    return Minimax(tempBoard, 0, board.GetTurnInt());
}

Move Search::FindBestMove(Board& board)
{
    int bestVal = (board.GetTurnInt() == 1) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    Move bestMove;

    if (!board.IsOver())
    {
        for (Move& move : board.PossibleMoves())
        {
            Board tempBoard = board;
            tempBoard.MakeMove(move);

            int moveVal = Minimax(tempBoard, 0, -board.GetTurnInt());

            if (board.GetTurnInt() == 1 && moveVal > bestVal)
            {
                bestVal = moveVal;
                bestMove = move;
            }
            else if (board.GetTurnInt() == -1 && moveVal < bestVal)
            {
                bestVal = moveVal;
                bestMove = move;
            }
        }
    }

    return bestMove;
}

int Search::Minimax(Board& board, int depth, int maximizingPlayer, int alpha, int beta)
{
    if (board.IsOver())
    {
        return (board.GetResultInt() * 100);
    }
    else if (depth >= maxDepth)
    {
        // for now, just finds the material difference
        return board.Evaluate();
    }

    if (maximizingPlayer == 1)
    {
        int maxEval = std::numeric_limits<int>::min();
        auto possibleMoves = board.PossibleMoves();

        for (Move& move : possibleMoves)
        {
            //auto tempBoard = board;
            //tempBoard.MakeMove(move);

            board.MakeMove(move);

            int eval = Minimax(board, depth + 1, -1, alpha, beta);

            board.UndoMove(move);

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);

            if (beta <= alpha)
                break;
        }

        return maxEval;
    }
    else if (maximizingPlayer == -1)
    {
        int minEval = std::numeric_limits<int>::max();
        auto possibleMoves = board.PossibleMoves();

        for (Move& move : possibleMoves)
        {
            //auto tempBoard = board;
            //tempBoard.MakeMove(move);

            board.MakeMove(move);

            int eval = Minimax(board, depth + 1, 1, alpha, beta);

            board.UndoMove(move);

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);

            if (beta <= alpha)
                break;
        }

        return minEval;
    }
    else
    {
        throw std::runtime_error("Invalid maximizing player");
    }
}
