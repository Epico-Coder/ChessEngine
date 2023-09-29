#include "Board.h"
#include <math.h>

Board::Board(Theme& theme) 
    : theme(theme)
{
    turn = 'W';

    InitalizeBoard();
}

void Board::InitalizeBoard() {
    // Initialize all to nullptr
    for (auto& row : board)
    {
        for (auto& cell : row)
        {
            cell = nullptr;
        }
    }

    // Black pieces
    {
        board[0][0] = new Rook("B", sf::Vector2f(0, 0), "b_rook.png");
        board[0][1] = new Knight("B", sf::Vector2f(0, 1), "b_knight.png");
        board[0][2] = new Bishop("B", sf::Vector2f(0, 2), "b_bishop.png");
        board[0][3] = new Queen("B", sf::Vector2f(0, 3), "b_queen.png");
        board[0][4] = new King("B", sf::Vector2f(0, 4), "b_king.png");
        board[0][5] = new Bishop("B", sf::Vector2f(0, 5), "b_bishop.png");
        board[0][6] = new Knight("B", sf::Vector2f(0, 6), "b_knight.png");
        board[0][7] = new Rook("B", sf::Vector2f(0, 7), "b_rook.png");
        for (int i = 0; i < 8; i++)
        {
            board[1][i] = new Pawn("B", sf::Vector2f(1, i), "b_pawn.png");
        }
    }

    // White pieces
    {
        board[7][0] = new Rook("W", sf::Vector2f(7, 0), "w_rook.png");
        board[7][1] = new Knight("W", sf::Vector2f(7, 1), "w_knight.png");
        board[7][2] = new Bishop("W", sf::Vector2f(7, 2), "w_bishop.png");
        board[7][3] = new Queen("W", sf::Vector2f(7, 3), "w_queen.png");
        board[7][4] = new King("W", sf::Vector2f(7, 4), "w_king.png");
        board[7][5] = new Bishop("W", sf::Vector2f(7, 5), "w_bishop.png");
        board[7][6] = new Knight("W", sf::Vector2f(7, 6), "w_knight.png");
        board[7][7] = new Rook("W", sf::Vector2f(7, 7), "w_rook.png");
        for (int i = 0; i < 8; i++)
        {
            board[6][i] = new Pawn("W", sf::Vector2f(6, i), "w_pawn.png");
        }
    }
}

void Board::Draw(sf::RenderWindow& win)
{
    const int squareSize = 100;
    
    // Draw board
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            float border = 0.5f;

            sf::RectangleShape square(sf::Vector2f(squareSize - (8 * border), squareSize - (8 * border)));
            square.setPosition(border + (col * (squareSize + (1 * border))), border + (row * (squareSize + (1 * border))));

            if ((row + col) % 2 == 0)
                square.setFillColor(theme.color1);
            else
                square.setFillColor(theme.color2);

            win.draw(square);
        }
    }

    // Draw pieces
    for (const auto& row : board)
    {
        for (const auto& piece : row)
        {
            // If not nullptr
            if (piece)
            {
                piece->Draw(win, squareSize);
            }
        }
    }
}

void Board::MakeMove(Move move)
{

}

void Board::Update()
{
    if (turn == 'W')
    {
        turn = 'B';
    }
    else if (turn == 'B')
    {
        turn = 'W';
    }
}

int Board::Evaluate()
{
    int score = 0;

    // white's material - black's material

    return score;
}

std::vector<Move> Board::PossibleMoves()
{
    std::vector<Move> moves;

    // append pieces' moves

    return moves;
}

bool Board::IsOver() const
{
    return false;
}

bool Board::IsChecked() const
{
    return false;
}