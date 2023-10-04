#pragma once

class Piece;

struct Move
{
    // initial
    int startX;
    int startY;
    int endX;
    int endY;

    // for promotion choice
    char promotionPiece = '\0';

    // for undo moves
    Piece* movedPiece = nullptr;
    Piece* capturedPiece = nullptr;
};
