#include <stdint.h>

#include <iostream>
#include <map>
#include <string>

#ifndef board_h
#define board_h

// Bitboard data type
#define Bitboard uint64_t

// clang-format off
  
// Enum for board indices
enum Index {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1
};

// Indices for bitboard array
enum BoardIndices {
    WHITE_PAWNS,
    WHITE_KNIGHTS,
    WHITE_BISHOPS,
    WHITE_ROOKS,
    WHITE_QUEENS,
    WHITE_KING,
    WHITE_PIECES,
    BLACK_PAWNS,
    BLACK_KNIGHTS,
    BLACK_BISHOPS,
    BLACK_ROOKS,
    BLACK_QUEENS,
    BLACK_KING,
    BLACK_PIECES,
    CASTLING_RIGHTS,
    ENPASSANT_VULNERABLE,
    OCCUPIED_SPACES,
    EMPTY_SPACES,
};

// clang-format on

// BIT MACROS for board manipulation
#define getBit(bitboard, square) (bitboard & (1ULL << square))
#define setBit(bitboard, square) (bitboard |= (1ULL << square))
#define popBit(bitboard, square) \
    (getBit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

extern std::map<std::string, Index> stringToIndexMap;
void printBoard(Bitboard bitboard);
void fenToBitboards(const std::string fen, Bitboard* bitboards);

#endif
