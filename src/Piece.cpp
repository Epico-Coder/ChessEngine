#include "Piece.h"

Piece::Piece(const std::string& color, const sf::Vector2f& pos, const std::string& filename)
    : color(color), pos(pos) 
{
    texture.loadFromFile("resources/images/" + filename);
    image.setTexture(texture);
}

void Piece::Draw(sf::RenderWindow& win, const int& squareSize) 
{
    float x = (pos.y * squareSize) + (squareSize - image.getGlobalBounds().width) / 2.0f;
    float y = (pos.x * squareSize) + (squareSize - image.getGlobalBounds().height) / 2.0f;

    image.setPosition(x, y);
    win.draw(image);
}

void King::PossibleMoves() 
{
}

void Queen::PossibleMoves() 
{
}

void Rook::PossibleMoves() 
{
}

void Bishop::PossibleMoves() 
{
}

void Knight::PossibleMoves() 
{
}

void Pawn::PossibleMoves() 
{
}

