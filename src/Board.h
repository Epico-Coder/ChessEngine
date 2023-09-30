#pragma once

#include <array>

#include "Piece.h"
#include "Move.h"

struct Theme
{
    sf::Color color1;
    sf::Color color2;
};

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

    bool IsChecked() const;
    bool IsOver() const;

private:
    char turn;
    Theme theme;
    std::array<std::array<Piece*, 8>, 8> board;
};
