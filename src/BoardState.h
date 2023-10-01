#pragma once

#include <array>
#include <optional>

class Piece;

struct BoardState
{
    std::array<std::array<Piece*, 8>, 8> board;
    std::optional<std::pair<int, int>> enPassantSquare;
};