#include "pieceData.h"

#ifndef board_h
#define board_h

#include <iostream>
#include <map>
#include <string>

// Bitboard data type
#define Bitboard uint64_t
#define EMPTY_BITBOARD 0ULL

// BIT MACROS for board manipulation
#define getBit(bitboard, square) (bitboard & (1ULL << square))
#define setBit(bitboard, square) (bitboard |= (1ULL << square))
#define popBit(bitboard, square) (getBit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

void printBoard(Bitboard *bitboard);
void printBitboard(Bitboard bitboard);
int getPieceType(char piece);
void fenToBitboards(const std::string fen, Bitboard *bitboards, Color *CurrentPlayerColor);

#endif
