#include "board.h"
#include "pieceData.h"

#ifndef movegen_h
#define movegen_h

#include <iostream>

void pawnMoves(Index square, Color color, Bitboard *board);
void knightMoves(Index square, Color color, Bitboard *board);

#endif
