#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <array>

#include "Move.h"

class Piece
{
public:
    Piece(char color, const sf::Vector2i& pos, const std::string& filename);
    virtual ~Piece() = default;

    virtual char GetType() const = 0;

    char GetColor() const;

    sf::Vector2i GetPos() const;
    void SetPos(int row, int col);

    bool GetMoved() const;
    void SetMoved(bool hasMoved);

    void Draw(sf::RenderWindow& win, const int& squareSize);
    virtual std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) = 0;

protected:
    char color;
    bool moved;
    sf::Vector2i pos;
    sf::Texture texture;
    sf::Sprite image;
};

class King : public Piece 
{
public:
    using Piece::Piece;
    char GetType() const override { return 'K'; };

    std::vector<Move> NonCastlingMoves(std::array<std::array<Piece*, 8>, 8>& board);
    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Queen : public Piece
{
public:
    using Piece::Piece;
    char GetType() const override { return 'Q'; };

    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Rook : public Piece 
{
public:
    using Piece::Piece;
    char GetType() const override { return 'R'; };

    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Bishop : public Piece 
{
public:
    using Piece::Piece;
    char GetType() const override { return 'B'; };

    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Knight : public Piece 
{
public:
    using Piece::Piece;
    char GetType() const override { return 'N'; };
    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Pawn : public Piece 
{
public:
    using Piece::Piece;
    char GetType() const override { return 'P'; };

    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

bool WithinBounds(int row, int col);
bool SquareUnderAttack(std::array<std::array<Piece*, 8>, 8>& board, int checkRow, int checkCol, char opponentColor);

