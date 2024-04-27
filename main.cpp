#include <iostream>

#include "board.h"
#include "movegen.h"

/*    // INIT STARTING POSITIONS

    // White pieces
    Bitboard whitePawns = 71776119061217280ULL;
    Bitboard whiteKnights = 4755801206503243776ULL;
    Bitboard whiteBishops = 2594073385365405696ULL;
    Bitboard whiteRooks = 9295429630892703744ULL;
    Bitboard whiteQueens = 576460752303423488ULL;
    Bitboard whiteKing = 1152921504606846976ULL;
    Bitboard whitePieces = whitePawns | whiteKnights | whiteBishops |
                           whiteRooks | whiteQueens | whiteKing;
    // Black pieces
    Bitboard blackPawns = 65280ULL;
    Bitboard blackKnights = 66ULL;
    Bitboard blackBishops = 36ULL;
    Bitboard blackRooks = 129ULL;
    Bitboard blackQueens = 8ULL;
    Bitboard blackKing = 16ULL;
    Bitboard blackPieces = blackPawns | blackKnights | blackRooks |
                           blackBishops | blackQueens | blackKing;

    // All pieces
    Bitboard occupiedSpaces = whitePieces | blackPieces;
    Bitboard emptySpaces = ~occupiedSpaces;     */

int main() {
    Bitboard board[18];
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR kqKQ";
    fenToBitboards(fen, board);
    for (int i = 0; i < 18; ++i) {
        printBoard(board[i]);
    }
}
