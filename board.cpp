#include "board.h"

// prints bitboard
void printBoard(Bitboard bitboard) {
    printf("\n");
    // print colors turn?
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (col == 0) printf("  %d  ", 8 - row);

            int square = row * 8 + col;
            printf(" %d", getBit(bitboard, (row * 8) + col) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n      a b c d e f g h\n\n");
    printf("      Bitboard: %lu \n\n", bitboard);
}
