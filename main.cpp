#include <iostream>

// clang-format off
#include "pieceData.h"
#include "movegen.h"
#include "board.h"
// clang-format on

void printBitboards(Bitboard *board) {
    for (int i = 0; i < 20; i++) {
        printBitboard(board[i]);
    }
}

int main() {
    Color currentPlayerColor = WHITE;
    Bitboard board[20];
    std::string startingPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR kqKQ";
    fenToBitboards(startingPosition, board, &currentPlayerColor);

    // printBitboard(board[BLACK_PIECES]);
    knightMoves(a1, WHITE, board);
    // printBoard(board);
    // printBitboards(board);
}
