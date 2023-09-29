#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class Piece
{
public:
    Piece(const std::string& color, const sf::Vector2f& pos, const std::string& filename);
    virtual ~Piece() = default;

    void Draw(sf::RenderWindow& win, const int& squareSize);
    virtual void PossibleMoves() = 0;

private:
    std::string color;
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite image;
};

class King : public Piece 
{
public:
    using Piece::Piece;
    void PossibleMoves() override;
};

class Queen : public Piece
{
public:
    using Piece::Piece;
    void PossibleMoves() override;
};

class Rook : public Piece 
{
public:
    using Piece::Piece;
    void PossibleMoves() override;
};

class Bishop : public Piece 
{
public:
    using Piece::Piece;
    void PossibleMoves() override;
};

class Knight : public Piece 
{
public:
    using Piece::Piece;
    void PossibleMoves() override;
};

class Pawn : public Piece 
{
public:
    using Piece::Piece;
    void PossibleMoves() override;
};

