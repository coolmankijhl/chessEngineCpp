#include <iostream>

#include "board.h"

#ifndef movegen_h
#define movegen_h

enum Color { WHITE, BLACK };

void pawnMoves(Index square, Color color);

#endif
