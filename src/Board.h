#pragma once

#include <array>
#include <optional>
#include <iostream>

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

    void MakeMove(Move& move);
    void UndoMove(Move& move);

    void Update();

    int Evaluate() const;
    std::vector<Move> PossibleMoves(char color='\0') const;

    void DisplayBoard() const;
    void Test(int row, int col)
    {
        std::cout << "Debug" << std::endl;

        lastClickedPiece;

        turn;

        std::cout << "Debug" << std::endl;

    }

    void RightClick(int row, int col);
    void LeftClick(int row, int col);
    bool IsHighlighted(int row, int col) const;

    bool IsChecked(char color) const;
    bool IsOver() const;

    bool IsInsufficientMaterial() const;

    int GetTurnInt() const;
    int GetResultInt() const;

    std::string GetGameOverMsg() const;
private:
    char turn;
    int depth;

    Theme theme;

    BoardState boardState;
    std::vector<std::array<std::array<Piece*, 8>, 8>> boardHistory;

    std::vector<std::pair<int, int>> piecehighlightedSquares;
    std::vector<std::pair<int, int>> userhighlightedSquares;

    Piece* lastClickedPiece = nullptr;

    int movesSincePawnOrCapture;

    int result;
    bool gameOver;
    std::string gameOverMsg;
};
