#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <array>

#include "Move.h"

bool WithinBounds(int row, int col);

class Piece
{
public:
    Piece(char color, const sf::Vector2i& pos, const std::string& filename);
    virtual ~Piece() = default;

    char GetColor() const;

    void Draw(sf::RenderWindow& win, const int& squareSize);
    virtual std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) = 0;

protected:
    char color;
    sf::Vector2i pos;
    sf::Texture texture;
    sf::Sprite image;
};

class King : public Piece 
{
public:
    using Piece::Piece;
    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Queen : public Piece
{
public:
    using Piece::Piece;
    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Rook : public Piece 
{
public:
    using Piece::Piece;
    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Bishop : public Piece 
{
public:
    using Piece::Piece;
    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Knight : public Piece 
{
public:
    using Piece::Piece;
    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

class Pawn : public Piece 
{
public:
    using Piece::Piece;
    std::vector<Move> PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board) override;
};

