#include <iostream>

#include "board.h"

int main() {
    Bitboard bitboard = 0ULL;

    setBit(bitboard, a8);

    printBoard(bitboard);
}
