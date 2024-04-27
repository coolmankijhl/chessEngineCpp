// https://www.chessprogramming.org/Direction
// Note: north and south are swapped here.

#include "movegen.h"

#include "board.h"
#include "pieceData.h"

void pawnMoves(Index square, Color color) {
    Bitboard temp = 0ULL;

    if (color == WHITE) {
        // push
        setBit(temp, square - 8);

        // double jump
        if (square < 17 && square > 8) setBit(temp, square - 16);

        // HANDLES CAPTURE
        // take up right
        if (square % 8 != 0) {
            setBit(temp, square - 9);
        }
        // take up left
        if (square % 8 != 7) {
            setBit(temp, square - 7);
        }
    } else {
        // push
        setBit(temp, square + 8);

        // double jump
        if (square < 17 && square > 8) setBit(temp, square + 16);

        // HANDLES CAPTURE
        // take up right
        if (square % 8 != 0) {
            setBit(temp, square + 7);
        }
        // take up left
        if (square % 8 != 7) {
            setBit(temp, square + 9);
        }
    }
}
