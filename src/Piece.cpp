#include "Piece.h"

bool WithinBounds(int row, int col)
{
    return (row >= 0 && row < 8) && (col >= 0 && col < 8);
}

Piece::Piece(char color, const sf::Vector2i& pos, const std::string& filename)
    : color(color), pos(pos) 
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

void Piece::Draw(sf::RenderWindow& win, const int& squareSize)
{
    float x = (pos.y * squareSize) + (squareSize - image.getGlobalBounds().width) / 2.0f;
    float y = (pos.x * squareSize) + (squareSize - image.getGlobalBounds().height) / 2.0f;

    image.setPosition(x, y);
    win.draw(image);
}

std::vector<Move> King::PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board)
{
    std::vector<Move> allMoves;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            // Skip the current position
            if (i == 0 && j == 0) continue;

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

std::vector<Move> Queen::PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board)
{
    std::vector<Move> allMoves;

    Rook tempRook(color, pos, "...");
    Bishop tempBishop(color, pos, "...");

    std::vector<Move> rookMoves = tempRook.PossibleMoves(board);
    std::vector<Move> bishopMoves = tempBishop.PossibleMoves(board);

    allMoves.insert(allMoves.end(), rookMoves.begin(), rookMoves.end());
    allMoves.insert(allMoves.end(), bishopMoves.begin(), bishopMoves.end());

    return allMoves;
}

std::vector<Move> Rook::PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board)
{
    std::vector<Move> allMoves;

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

    return allMoves;
}

std::vector<Move> Bishop::PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board)
{
    std::vector<Move> allMoves;

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

    return allMoves;
}

std::vector<Move> Knight::PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board)
{
    std::vector<Move> allMoves;

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

    return allMoves;
}

std::vector<Move> Pawn::PossibleMoves(std::array<std::array<Piece*, 8>, 8>& board)
{
    std::vector<Move> allMoves;

    int forward = (this->color == 'W') ? -1 : 1;

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

    // Captures diagonally forward
    for (int side : {-1, 1})
    {
        int newRow = pos.x + forward;
        int newCol = pos.y + side;
        if (WithinBounds(newRow, newCol) && board[newRow][newCol] != nullptr
            && board[newRow][newCol]->GetColor() != this->color)
        {
            allMoves.push_back(Move(pos.x, pos.y, newRow, newCol));
        }
    }

    return allMoves;
}
