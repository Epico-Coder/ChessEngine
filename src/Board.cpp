#include <iostream>
#include <math.h>
#include <algorithm>

#include "Board.h"

Board::Board(Theme& theme) 
    : theme(theme), depth(0)
{
    turn = 'W';

    InitalizeBoard();
}

void Board::InitalizeBoard()
{
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
        board[0][0] = new Rook('B', sf::Vector2i(0, 0), "b_rook.png");
        board[0][1] = new Knight('B', sf::Vector2i(0, 1), "b_knight.png");
        board[0][2] = new Bishop('B', sf::Vector2i(0, 2), "b_bishop.png");
        board[0][3] = new Queen('B', sf::Vector2i(0, 3), "b_queen.png");
        board[0][4] = new King('B', sf::Vector2i(0, 4), "b_king.png");
        board[0][5] = new Bishop('B', sf::Vector2i(0, 5), "b_bishop.png");
        board[0][6] = new Knight('B', sf::Vector2i(0, 6), "b_knight.png");
        board[0][7] = new Rook('B', sf::Vector2i(0, 7), "b_rook.png");
        for (int i = 0; i < 8; i++)
        {
            board[1][i] = new Pawn('B', sf::Vector2i(1, i), "b_pawn.png");
        }
    }

    // White pieces
    {
        board[7][0] = new Rook('W', sf::Vector2i(7, 0), "w_rook.png");
        board[7][1] = new Knight('W', sf::Vector2i(7, 1), "w_knight.png");
        board[7][2] = new Bishop('W', sf::Vector2i(7, 2), "w_bishop.png");
        board[7][3] = new Queen('W', sf::Vector2i(7, 3), "w_queen.png");
        board[7][4] = new King('W', sf::Vector2i(7, 4), "w_king.png");
        board[7][5] = new Bishop('W', sf::Vector2i(7, 5), "w_bishop.png");
        board[7][6] = new Knight('W', sf::Vector2i(7, 6), "w_knight.png");
        board[7][7] = new Rook('W', sf::Vector2i(7, 7), "w_rook.png");
        for (int i = 0; i < 8; i++)
        {
            board[6][i] = new Pawn('W', sf::Vector2i(6, i), "w_pawn.png");
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

            if (isHighlighted(row, col))
            {
                square.setFillColor(theme.color3);
            }
            else
            {
                if ((row + col) % 2 == 0)
                    square.setFillColor(theme.color1);
                else
                    square.setFillColor(theme.color2);
            }

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
    depth++;
    std::cout << "MADE MOVE " << depth << ": (" << move.startX << ", " << move.startY << ")--> (" << move.endX << ", " << move.endY << ")" << std::endl;

    // handle captures
    Piece* capturedPiece = board[move.endX][move.endY];
    if (capturedPiece != nullptr) 
    {
        delete capturedPiece;
    }

    // handle castling
    if (board[move.startX][move.startY]->GetType() == 'K')
    {
        // kingside
        if (move.endY - move.startY == 2)
        {
            Piece* rook = board[move.endX][7];
            rook->SetPos(move.endX, 5);
            rook->SetMoved(true);

            board[move.endX][5] = rook;
            board[move.endX][7] = nullptr;
        }
        // queenside
        else if (move.startY - move.endY == 2)
        {
            Piece* rook = board[move.endX][0];
            rook->SetPos(move.endX, 3);
            rook->SetMoved(true);

            board[move.endX][3] = rook;
            board[move.endX][0] = nullptr;
        }
    }

    // move piece from start to end
    Piece* piece = board[move.startX][move.startY];
    piece->SetPos(move.endX, move.endY);
    piece->SetMoved(true);

    board[move.endX][move.endY] = piece;
    board[move.startX][move.startY] = nullptr;
    

    // handle promotion
    Piece* end = board[move.endX][move.endY];
    if (end)
    {
        if (end->GetType() == 'P')
        {
            if (move.endX == 0 || move.endX == 7)
            {
                if (board[move.endX][move.endY] != nullptr)
                {
                    delete board[move.endX][move.endY];
                }

                std::string filename = "_queen.png";
                filename.insert(filename.begin(), std::tolower(turn));
                std::cout << filename << std::endl;

                Piece* piece = new Queen(turn, sf::Vector2i(move.endX, move.endY), filename);
                board[move.endX][move.endY] = piece;
            }
        }
    }

    // update turn
    Update();
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
    std::vector<Move> allMoves;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            auto piece = board[row][col];
            if (piece != nullptr)
            {
                if (piece->GetColor() == turn)
                {
                    std::vector<Move> pieceMoves = piece->PossibleMoves(board);
                    allMoves.insert(allMoves.end(), pieceMoves.begin(), pieceMoves.end());
                }
            }
        }
    }

    return allMoves;
}

bool Board::IsOver() const
{
    return false;
}

void Board::RightClick(int row, int col)
{
    // clear the piece highlights
    piecehighlightedSquares.clear();

    auto iter = std::find(userhighlightedSquares.begin(), userhighlightedSquares.end(), std::make_pair(row, col));

    // highlight
    if (iter != userhighlightedSquares.end())
    {
        userhighlightedSquares.erase(iter);
    }
    else
    {
        userhighlightedSquares.push_back(std::make_pair(row, col));
    }

    // reset left click
    lastClickedPiece = nullptr;
}

void Board::LeftClick(int row, int col)
{
    Piece* clickedPiece = board[row][col];

    // clicked on a piece before
    if (lastClickedPiece != nullptr)
    {
        // clicked on same piece now
        if (lastClickedPiece == clickedPiece)
        {
            userhighlightedSquares.clear();
            piecehighlightedSquares.clear();

            lastClickedPiece = nullptr;

            return;
        }
        // clicked on a highlight (possible move)
        if (isHighlighted(row, col))
        {
            piecehighlightedSquares.clear();
            userhighlightedSquares.clear();

            Move move(lastClickedPiece->GetPos().x, lastClickedPiece->GetPos().y, row, col);
            MakeMove(move);

            return;
        }
    }

    // clear all highlights
    piecehighlightedSquares.clear();
    userhighlightedSquares.clear();

    // clicked on a piece now
    if (clickedPiece != nullptr)
    {
        if (clickedPiece->GetColor() == turn)
        {
            auto moves = clickedPiece->PossibleMoves(board);
            for (const auto& move : moves)
            {
                // highlight all the possible moves
                piecehighlightedSquares.emplace_back(std::make_pair(move.endX, move.endY));
            }
        }
    }

    lastClickedPiece = clickedPiece;
}

bool Board::isHighlighted(int row, int col) const
{
    auto predicate = [row, col](const auto& pair) { return (pair.first == row) && (pair.second == col); };

    bool isHighlighted = (std::find_if(userhighlightedSquares.begin(), userhighlightedSquares.end(), predicate) != userhighlightedSquares.end() || 
                          std::find_if(piecehighlightedSquares.begin(), piecehighlightedSquares.end(), predicate) != piecehighlightedSquares.end());

    return isHighlighted;
}

bool Board::IsChecked() const
{
    return false;
}