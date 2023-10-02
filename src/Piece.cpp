#include "Piece.h"

#include <iostream>

bool WithinBounds(int row, int col)
{
    return (row >= 0 && row < 8) && (col >= 0 && col < 8);
}

bool SquareUnderAttack(std::array<std::array<Piece*, 8>, 8>& board, int checkRow, int checkCol, char opponentColor)
{
    // get all opponent's pieces
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece* piece = board[row][col];

            if (piece)
            {
                if (piece->GetColor() == opponentColor)
                {
                    if (piece->IsAttackingSquare(board, checkRow, checkCol)) 
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

std::vector<Move> FindLegalMoves(std::vector<Move> allMoves, std::array<std::array<Piece*, 8>, 8>& board, char color)
{
    std::vector<Move> legalMoves;

    // find king
    int kingRow;
    int kingCol;

    bool kingFound = false;

    for (int row = 0; row < 8 && !kingFound; row++)
    {
        for (int col = 0; col < 8 && !kingFound; col++)
        {
            Piece* piece = board[row][col];
            if (piece)
            {
                if (piece->GetType() == 'K' && piece->GetColor() == color)
                {
                    kingRow = row;
                    kingCol = col;

                    kingFound = true;
                }
            }
        }
    }

    for (const Move& move : allMoves)
    {
        // create copy
        auto tempBoard = board;
        
        // make move
        tempBoard[move.endX][move.endY] = tempBoard[move.startX][move.startY];
        tempBoard[move.startX][move.startY] = nullptr;

        if (tempBoard[move.endX][move.endY]->GetType() == 'K')
        {
            kingRow = move.endX;
            kingCol = move.endY;
        }

        // check if king under attack
        char opponentColor = (color == 'W') ? 'B' : 'W';
        if (!SquareUnderAttack(tempBoard, kingRow, kingCol, opponentColor))
        {
            legalMoves.push_back(move);
        }
    }

    return legalMoves;
}

Piece::Piece(char color, const sf::Vector2i& pos, const std::string& filename)
    : color(color), pos(pos), moved(false)
{
    texture.loadFromFile("resources/images/" + filename);
    image.setTexture(texture);
}

char Piece::GetColor() const
{
    return color;
}

sf::Vector2i Piece::GetPos() const
{
    return pos;
}

void Piece::SetPos(int row, int col)
{
    pos = sf::Vector2i(row, col);
}

bool Piece::GetMoved() const
{
    return moved;
}

void Piece::SetMoved(bool hasMoved)
{
    moved = hasMoved;
}

void Piece::Draw(sf::RenderWindow& win, const int& squareSize)
{
    float x = (pos.y * squareSize) + (squareSize - image.getGlobalBounds().width) / 2.0f;
    float y = (pos.x * squareSize) + (squareSize - image.getGlobalBounds().height) / 2.0f;

    image.setPosition(x, y);
    win.draw(image);
}

bool King::IsAttackingSquare(std::array<std::array<Piece*, 8>, 8>& board, int row, int col)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            int newRow = pos.x + i;
            int newCol = pos.y + j;

            if (WithinBounds(newRow, newCol))
            {
                if (newRow == row && newCol == col)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<Move> King::NonCastlingMoves(std::array<std::array<Piece*, 8>, 8>& board)
{
    std::vector<Move> allMoves;

    // checking in all directions
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // skip the current position
            if (i == 0 && j == 0)
            {
                continue;
            }

            int newRow = pos.x + i;
            int newCol = pos.y + j;

            if (WithinBounds(newRow, newCol))
            {
                Piece* destination = board[newRow][newCol];

                // If the square is empty or enemy piece
                if (destination == nullptr || destination->GetColor() != this->color)
                {
                    allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
                }
            }
        }
    }



    return allMoves;
}

std::vector<Move> King::PossibleMoves(const BoardState& boardState)
{
    std::vector<Move> allMoves;
    
    auto board = boardState.board;

    std::vector<Move> nonCastlingMoves = NonCastlingMoves(board);
    allMoves.insert(allMoves.end(), nonCastlingMoves.begin(), nonCastlingMoves.end());

    // checking for castle
    if (!moved)
    {
        std::cout << "Not Moved!" << std::endl;

        int kingRow = pos.x;
        char opponentColor = (color == 'W') ? 'B' : 'W';

        // kingside
        Piece* rightRook = board[kingRow][7];
        if (rightRook && !(rightRook->GetMoved()))
        {
            if (board[kingRow][5] == nullptr && board[kingRow][6] == nullptr)
            {
                if (!SquareUnderAttack(board, kingRow, 4, opponentColor) &&
                    !SquareUnderAttack(board, kingRow, 5, opponentColor) &&
                    !SquareUnderAttack(board, kingRow, 6, opponentColor))
                {
                    allMoves.push_back(Move(pos.x, pos.y, pos.x, pos.y + 2));
                }
            }
        }

        // queenside
        Piece* leftRook = board[kingRow][0];
        if (leftRook && !(leftRook->GetMoved()))
        {
            if (board[kingRow][1] == nullptr && board[kingRow][2] == nullptr && board[kingRow][3] == nullptr)
            {
                if (!SquareUnderAttack(board, kingRow, 4, opponentColor) &&
                    !SquareUnderAttack(board, kingRow, 3, opponentColor) &&
                    !SquareUnderAttack(board, kingRow, 2, opponentColor))
                {
                    {
                        allMoves.push_back(Move(pos.x, pos.y, pos.x, pos.y - 2));
                    }
                }
            }
        }
    }

    allMoves = FindLegalMoves(allMoves, board, color);

    return allMoves;
}

bool Queen::IsAttackingSquare(std::array<std::array<Piece*, 8>, 8>& board, int row, int col)
{
    int dirs[8][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };
    
    for (auto& dir : dirs)
    {
        for (int dist = 1; dist < 8; dist++)
        {
            int newRow = pos.x + (dist * dir[0]);
            int newCol = pos.y + (dist * dir[1]);

            if (!WithinBounds(newRow, newCol))
            {
                break;
            }

            if (newRow == row && newCol == col)
            {
                return true;
            }

            if (board[newRow][newCol] != nullptr)
            {
                break;
            }
        }
    }

    return false;
}

std::vector<Move> Queen::PossibleMoves(const BoardState& boardState)
{
    std::vector<Move> allMoves;

    auto board = boardState.board;

    int dirs[8][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1} };

    // Checking in horizontal, vertical, and diagnol direction
    for (auto& dir : dirs)
    {
        for (int dist = 1; dist < 8; dist++)
        {
            int newRow = pos.x + (dist * dir[0]);
            int newCol = pos.y + (dist * dir[1]);

            // Out of board
            if (!WithinBounds(newRow, newCol))
            {
                break;
            }

            // Empty square
            if (board[newRow][newCol] == nullptr)
            {
                allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
            }

            // Hits a piece
            else
            {
                // Enemy piece
                if (board[newRow][newCol]->GetColor() != this->color)
                {
                    allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
                }
                break;
            }
        }
    }

    allMoves = FindLegalMoves(allMoves, board, color);

    return allMoves;
}

bool Rook::IsAttackingSquare(std::array<std::array<Piece*, 8>, 8>& board, int row, int col)
{
    int dirs[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
    
    for (auto& dir : dirs)
    {
        for (int dist = 1; dist < 8; dist++)
        {
            int newRow = pos.x + (dist * dir[0]);
            int newCol = pos.y + (dist * dir[1]);

            if (!WithinBounds(newRow, newCol))
            {
                break;
            }

            if (newRow == row && newCol == col)
            {
                return true;
            }

            if (board[newRow][newCol] != nullptr)
            {
                break;
            }
        }
    }

    return false;
}

std::vector<Move> Rook::PossibleMoves(const BoardState& boardState)
{
    std::vector<Move> allMoves;

    auto board = boardState.board;

    int dirs[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

    // Checking in horizontal and vertical direction
    for (auto& dir : dirs)
    {
        for (int dist = 1; dist < 8; dist++)
        {
            int newRow = pos.x + (dist * dir[0]);
            int newCol = pos.y + (dist * dir[1]);

            // Out of board
            if (!WithinBounds(newRow, newCol))
            {
                break;
            }

            // Empty square
            if (board[newRow][newCol] == nullptr)
            {
                allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
            }

            // Hits a piece
            else
            {
                // Enemy piece
                if (board[newRow][newCol]->GetColor() != this->color)
                {
                    allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
                }
                break;
            }
        }
    }

    allMoves = FindLegalMoves(allMoves, board, color);

    return allMoves;
}

bool Bishop::IsAttackingSquare(std::array<std::array<Piece*, 8>, 8>& board, int row, int col)
{
    int dirs[4][2] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };
    
    for (auto& dir : dirs)
    {
        for (int dist = 1; dist < 8; dist++)
        {
            int newRow = pos.x + (dist * dir[0]);
            int newCol = pos.y + (dist * dir[1]);

            if (!WithinBounds(newRow, newCol))
            {
                break;
            }

            if (newRow == row && newCol == col)
            {
                return true;
            }

            if (board[newRow][newCol] != nullptr)
            {
                break;
            }
        }
    }

    return false;
}

std::vector<Move> Bishop::PossibleMoves(const BoardState& boardState)
{
    std::vector<Move> allMoves;

    auto board = boardState.board;

    int dirs[4][2] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };

    // Checking in diagnol direction
    for (auto& dir : dirs)
    {
        for (int dist = 1; dist < 8; dist++)
        {
            int newRow = pos.x + dist * dir[0];
            int newCol = pos.y + dist * dir[1];

            // Out of board
            if (!WithinBounds(newRow, newCol))
            {
                break;
            }

            // Empty square
            if (board[newRow][newCol] == nullptr)
            {
                allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
            }

            // Hits a piece
            else
            {
                // Enemy piece
                if (board[newRow][newCol]->GetColor() != this->color)
                {
                    allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
                }
                break;
            }
        }
    }

    allMoves = FindLegalMoves(allMoves, board, color);

    return allMoves;
}

bool Knight::IsAttackingSquare(std::array<std::array<Piece*, 8>, 8>& board, int row, int col)
{
    int moves[8][2] = { {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1} };
    
    for (int x = 0; x < 8; x++)
    {
        int newRow = pos.x + moves[x][0];
        int newCol = pos.y + moves[x][1];

        if (WithinBounds(newRow, newCol))
        {
            if (newRow == row && newCol == col)
            {
                return true;
            }
        }
    }

    return false;
}

std::vector<Move> Knight::PossibleMoves(const BoardState& boardState)
{
    std::vector<Move> allMoves;

    auto board = boardState.board;
    
    // Relative directions
    int moves[8][2] = { {2,1}, {1,2}, {-1,2}, {-2,1}, {-2,-1}, {-1,-2}, {1,-2}, {2,-1} };

    for (int x = 0; x < 8; x++)
    {
        int newRow = pos.x + moves[x][0];
        int newCol = pos.y + moves[x][1];

        // Inside board
        if (WithinBounds(newRow, newCol))
        {
            Piece* destination = board[newRow][newCol];

            // Square is either empty or enemy piece
            if (destination == nullptr || destination->GetColor() != this->color)
            {
                allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
            }
        }
    }

    allMoves = FindLegalMoves(allMoves, board, color);

    return allMoves;
}

bool Pawn::IsAttackingSquare(std::array<std::array<Piece*, 8>, 8>& board, int row, int col)
{
    int forward = (this->color == 'W') ? -1 : 1;
    
    for (int side : {-1, 1})
    {
        int newRow = pos.x + forward;
        int newCol = pos.y + side;
        if (WithinBounds(newRow, newCol))
        {
            if (newRow == row && newCol == col)
            {
                return true;
            }
        }
    }

    return false;
}

std::vector<Move> Pawn::PossibleMoves(const BoardState& boardState)
{
    std::vector<Move> allMoves;

    auto board = boardState.board;

    int forward = (this->color == 'W') ? -1 : 1;

    // moves forward
    if (WithinBounds(pos.x + forward, pos.y) && board[pos.x + forward][pos.y] == nullptr)
    {
        allMoves.push_back(Move(pos.x, pos.y, pos.x + forward, pos.y));

        if ((this->color == 'W' && pos.x == 6) || (this->color == 'B' && pos.x == 1))
        {
            if (board[pos.x + 2 * forward][pos.y] == nullptr)
            {
                allMoves.push_back(Move(pos.x, pos.y, pos.x + 2 * forward, pos.y));
            }
        }
    }

    for (int side : {-1, 1})
    {
        int newRow = pos.x + forward;
        int newCol = pos.y + side;
        if (WithinBounds(newRow, newCol))
        {
            // captures diagonally forward
            if (board[newRow][newCol] != nullptr && board[newRow][newCol]->GetColor() != this->color)
            {
                allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
            }

            // en passant
            if (boardState.enPassantSquare && boardState.enPassantSquare->first == newRow && boardState.enPassantSquare->second == newCol)
            {
                allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
            }
        }
    }

    allMoves = FindLegalMoves(allMoves, board, color);

    return allMoves;
}
