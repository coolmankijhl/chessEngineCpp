// https://www.chessprogramming.org/Direction
// Note: north and south are swapped here.

#include "movegen.h"

#include "board.h"
#include "pieceData.h"

void pawnMoves(Index square, Color color, Bitboard *board) {

    Bitboard pawnMoves = EMPTY_BITBOARD;

    if (color == WHITE) {

        // HANDLES JUMP/DOUBLE JUMP
        if (getBit(board[OCCUPIED_SPACES], square - 8) == 0) {
            setBit(pawnMoves, square - 8); // single jump
            if (square < 56 && square > 47 && getBit(board[OCCUPIED_SPACES], square - 16) == 0)
                setBit(pawnMoves, square - 16); // double jump
        }

        // HANDLES CAPTURE
        if (square % 8 != 0 && getBit(board[BLACK_PIECES], square - 9) != 0) {
            setBit(pawnMoves, square - 9); // forward right
        }
        if (square % 8 != 7 && getBit(board[BLACK_PIECES], square - 7) != 0) {
            setBit(pawnMoves, square - 7); // forward left
        }

    } else {

        // HANDLES JUMP/DOUBLE JUMP
        if (getBit(board[OCCUPIED_SPACES], square + 8) == 0) {
            setBit(pawnMoves, square + 8); // single jump
            if (square < 17 && square > 8 && getBit(board[OCCUPIED_SPACES], square + 16) == 0)
                setBit(pawnMoves, square + 16); // double jump
        }

        // HANDLES CAPTURE
        if (square % 8 != 0 && getBit(board[WHITE_PIECES], square + 7) != 0) {
            setBit(pawnMoves, square + 7); // forward right
        }
        if (square % 8 != 7 && getBit(board[WHITE_PIECES], square + 9) != 0) {
            setBit(pawnMoves, square + 9); // forward left
        }
    }
}

void knightMoves(Index square, Color color, Bitboard *board) {

    Bitboard knightMoves = EMPTY_BITBOARD;

    // Possible movements for a knight
    int posChange[] = {15, 17, 10, -6, -15, -17, -10, 6};

    for (int i = 0; i < 8; i++) {

        int targetSquare = square + posChange[i];
        int currRank = square / 8;
        int targetRank = targetSquare / 8;
        int currFile = square % 8;
        int targetFile = targetSquare % 8;

        // Check if the knight's move doesn't wrap around horizontally and vertically
        if (abs(currRank - targetRank) <= 2 && abs(currFile - targetFile) <= 2) {
            // Check if the target square is empty or occupied by an opponent's piece
            if ((color == WHITE && getBit(board[WHITE_PIECES], targetSquare) == 0) || (color == BLACK && getBit(board[BLACK_PIECES], targetSquare) == 0)) {
                setBit(knightMoves, targetSquare);
            }
        }
    }

    printBitboard(knightMoves);
}

