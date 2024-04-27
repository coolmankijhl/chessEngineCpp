#include <iostream>

// clang-format off
#include "pieceData.h"
#include "movegen.h"
#include "board.h"
// clang-format on

int main() {
    Color currentPlayerColor = WHITE;
    Bitboard board[20];
    std::string startingPosition =
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR kqKQ";
    fenToBitboards(startingPosition, board, &currentPlayerColor);

    printBoard(board);
}
