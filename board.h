#include "pieceData.h"

#ifndef board_h
#define board_h

#include <iostream>
#include <map>
#include <string>

// Bitboard data type
#define Bitboard uint64_t

// BIT MACROS for board manipulation
#define getBit(bitboard, square) (bitboard & (1ULL << square))
#define setBit(bitboard, square) (bitboard |= (1ULL << square))
#define popBit(bitboard, square) \
    (getBit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

extern std::map<std::string, Index> stringToIndexMap;
void printBoard(Bitboard* bitboard);
void fenToBitboards(const std::string fen, Bitboard* bitboards,
                    Color* CurrentPlayerColor);

#endif
