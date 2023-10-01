#pragma once

#include <array>

#include "Piece.h"
#include "Move.h"
#include "Theme.h"

class Board
{
public:
    Board(Theme& theme);

    void InitalizeBoard();
    void Draw(sf::RenderWindow& win);

    void MakeMove(Move move);
    void Update();

    int Evaluate();
    std::vector<Move> PossibleMoves();

    void RightClick(int row, int col);
    void LeftClick(int row, int col);
    bool isHighlighted(int row, int col) const;

    bool IsChecked() const;
    bool IsOver() const;

private:
    char turn;
    Theme theme;
    std::array<std::array<Piece*, 8>, 8> board;
    std::vector<std::pair<int, int>> piecehighlightedSquares;
    std::vector<std::pair<int, int>> userhighlightedSquares;
};
