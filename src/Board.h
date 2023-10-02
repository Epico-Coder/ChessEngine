#pragma once

#include <array>
#include <optional>

#include "Piece.h"
#include "Move.h"
#include "Theme.h"
#include "BoardState.h"

class Board
{
public:
    Board(Theme& theme);

    void InitalizeBoard();
    void Draw(sf::RenderWindow& win);

    void MakeMove(Move move);
    void Update();

    int Evaluate();
    std::vector<Move> PossibleMoves(char color='\0');

    void Test(int row, int col)
    {
        std::cout << "Debug" << std::endl;

        lastClickedPiece;

        turn;

        std::cout << "Debug" << std::endl;

    }

    void RightClick(int row, int col);
    void LeftClick(int row, int col);
    bool isHighlighted(int row, int col) const;

    bool IsChecked(char color) const;
    bool IsOver() const;

    std::string GetGameOverMsg() const;
private:
    char turn;
    int depth;

    Theme theme;

    BoardState boardState;

    std::vector<std::pair<int, int>> piecehighlightedSquares;
    std::vector<std::pair<int, int>> userhighlightedSquares;

    Piece* lastClickedPiece = nullptr;

    int movesSincePawnOrCapture;

    int result;
    bool gameOver;
    std::string gameOverMsg;
};
