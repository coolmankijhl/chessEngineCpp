// https://www.chessprogramming.org/Direction
// Note: north and south are swapped here.

#include "movegen.h"

#include "board.h"
#include "pieceData.h"

// Calculates possible movements for a pawn at a given position 'square'
void pawnMoves(Index square, Color color, Bitboard *board) {

    // INIT BOARD TO STORE POSSIBLE MOVES
    Bitboard pawnMoves = EMPTY_BITBOARD;

    // HANDLES ENEMY PAWN COLOR AND HOME ROW DEFINITION
    int enemyPieceBoard, homeRowRightBound, homeRowLeftBound, direction;
    if (color == WHITE) {
        enemyPieceBoard = BLACK_PIECES;
        homeRowRightBound = 56, homeRowLeftBound = 47;
        direction = -1;
    } else {
        enemyPieceBoard = WHITE_PIECES;
        homeRowRightBound = 17, homeRowLeftBound = 8;
        direction = 1;
    }

    // HANDLES JUMP/DOUBLE JUMP
    if (getBit(board[OCCUPIED_SPACES], square + 8 * direction) == 0) {
        setBit(pawnMoves, square + 8 * direction); // single jump
        if (square < homeRowRightBound && homeRowLeftBound > 8 && getBit(board[OCCUPIED_SPACES], square + 16 * direction) == 0)
            setBit(pawnMoves, square + 16 * direction); // double jump
    }

    // HANDLES CAPTURE
    if (square % 8 != 0 && getBit(board[enemyPieceBoard], square + 7 * direction) != 0) {
        setBit(pawnMoves, square + 7 * direction); // forward right
    }
    if (square % 8 != 7 && getBit(board[enemyPieceBoard], square + 9 * direction) != 0) {
        setBit(pawnMoves, square + 9 * direction); // forward left
    }
}

// Calculates possible movements for a knight at a given position 'square'
void knightMoves(Index square, Color color, Bitboard *board) {

    // INIT BOARD TO STORE POSSIBLE MOVES
    Bitboard knightMoves = EMPTY_BITBOARD;

    // POSSIBLE CHANGES IN POSITION FOR A KNIGHT
    int posChange[] = {15, 17, 10, -6, -15, -17, -10, 6};

    // HANDLES POSSIBLE MOVEMENTS
    for (int i = 0; i < 8; i++) { // iterate through posChange array
        int targetSquare = square + posChange[i];
        int currRank = square / 8, currFile = square % 8;
        int targetRank = targetSquare / 8, targetFile = targetSquare % 8;

        // Check if the knight's move doesn't wrap around horizontally and vertically, and is not out of bounds
        if (abs(currRank - targetRank) <= 2 && abs(currFile - targetFile) <= 2 && abs(currRank - targetRank) + abs(currFile - targetFile) == 3 &&
            targetSquare < 64 && targetSquare > -1) {
            // Check if the target square is occupied by an opponent's piece
            if ((color == WHITE && getBit(board[WHITE_PIECES], targetSquare) == 0) || (color == BLACK && getBit(board[BLACK_PIECES], targetSquare) == 0)) {
                setBit(knightMoves, targetSquare);
            }
        }
    }
}

// Calculates possible movements for a knight at a given position 'square'
void rookMoves(Index square, Color color, Bitboard *board) {

    // INIT BOARD TO STORE POSSIBLE MOVES
    Bitboard rookMoves = EMPTY_BITBOARD;

    // POSSIBLE CHANGES IN POSITION FOR A ROOK
    int posChange[] = {8, -8, 1, -1};

    // HANDLES ENEMY AND ALLY PAWN BOARDS
    int allyPieceBoard, enemyPieceBoard;
    if (color == WHITE) {
        allyPieceBoard = WHITE_PIECES;
        enemyPieceBoard = BLACK_PIECES;
    } else {
        allyPieceBoard = BLACK_PIECES;
        enemyPieceBoard = WHITE_PIECES;
    }

    // GENERATES POSSIBLE MOVES
    for (int i = 0; i < 4; i++) {     // iterate through posChange array
        for (int j = 1; j < 8; j++) { // generate possible moves in current direction determined by posChange
            int targetSquare = square + posChange[i] * j;
            if (targetSquare > -1 && targetSquare < 64) {
                // if target square is an ally or current piece is on a border column and moving into it break
                if (getBit(board[allyPieceBoard], targetSquare) || (square % 8 == 0 && posChange[i] == -1) || (square % 8 == 7 && posChange[i] == 1)) {
                    break;
                    // if hit column border break
                } else if (targetSquare % 8 == 0 || targetSquare % 8 == 7) {
                    setBit(rookMoves, targetSquare);
                    break;
                    // if target square is an enemy set as a possible move then break
                } else if (getBit(board[enemyPieceBoard], targetSquare) != 0) {
                    setBit(rookMoves, targetSquare);
                    break;
                    // if in bounds then store as available move then continue looping
                } else {
                    setBit(rookMoves, targetSquare);
                }
            }
        }
    }
    printBitboard(rookMoves);
}

// Generates possible moves for a bishop at a given position 'square'
void bishopMoves(Index square, Color color, Bitboard *board) {

    // INIT BOARD TO STORE POSSIBLE MOVES
    Bitboard bishopMoves = EMPTY_BITBOARD;

    // POSSIBLE CHANGES IN POSITON FOR A BISHOP
    int posChange[] = {7, 9, -7, -9};

    // HANDLES ALLY AND ENEMY BOARD DEFINITIONS
    int allyPieceBoard, enemyPieceBoard;
    if (color == WHITE) {
        allyPieceBoard = WHITE_PIECES;
        enemyPieceBoard = BLACK_PIECES;
    } else {
        allyPieceBoard = BLACK_PIECES;
        enemyPieceBoard = WHITE_PIECES;
    }

    // GENERATES POSSIBLE MOVES
    for (int i = 0; i < 4; i++) {     // iterate through posChange array
        for (int j = 1; j < 8; j++) { // iterate through possible moves in a given direction determined by posChange
            int targetSquare = square + posChange[i] * j;
            // if in bounds
            if (targetSquare > -1 && targetSquare < 64) {
                // if target square is an ally piece or current piece is on border column and moving into border then break
                if (getBit(board[allyPieceBoard], targetSquare) || (square % 8 == 0 && (posChange[i] == -9 || posChange[i] == 7)) ||
                    (square % 8 == 7 && (posChange[i] == -7 || posChange[i] == 9))) {
                    break;
                    // if target square is an enemy piece, store as possible move then break
                } else if (getBit(board[enemyPieceBoard], targetSquare) != 0) {
                    setBit(bishopMoves, targetSquare);
                    break;
                } else {
                    setBit(bishopMoves, targetSquare);
                }
            }
        }
    }
    printBitboard(bishopMoves);
}

// Generates possible moves for a queen at a given postition 'square'
void queenMoves(Index square, Color color, Bitboard *board) {

    // INIT BOARD TO STORE POSSIBLE MOVES
    Bitboard queenMoves = EMPTY_BITBOARD;

    // POSSIBLE CHANGES IN POSITION FOR A QUEEN
    int posChangeRook[] = {8, -8, 1, -1};
    int posChangeBishop[] = {7, 9, -7, -9};

    // HANDLES ALLY AND ENEMY BOARD DEFINITIONS
    int allyPieceBoard, enemyPieceBoard;
    if (color == WHITE) {
        allyPieceBoard = WHITE_PIECES;
        enemyPieceBoard = BLACK_PIECES;
    } else {
        allyPieceBoard = BLACK_PIECES;
        enemyPieceBoard = WHITE_PIECES;
    }

    // GENERATES POSSIBLE MOVES FOR ROOK MOVEMENT
    for (int i = 0; i < 4; i++) {     // iterate through posChangeRook array
        for (int j = 1; j < 8; j++) { // generate possible moves in current direction determined by posChangeRook
            int targetSquare = square + posChangeRook[i] * j;
            // if in bounds
            if (targetSquare > -1 && targetSquare < 64) {
                // if target square is an ally or current piece is on a border column and moving into it break
                if (getBit(board[allyPieceBoard], targetSquare) || (square % 8 == 0 && posChangeRook[i] == -1) || (square % 8 == 7 && posChangeRook[i] == 1)) {
                    break;
                    // if hit column border break
                } else if (targetSquare % 8 == 0 || targetSquare % 8 == 7) {
                    setBit(queenMoves, targetSquare);
                    break;
                    // if target square is an enemy set as a possible move then break
                } else if (getBit(board[enemyPieceBoard], targetSquare) != 0) {
                    setBit(queenMoves, targetSquare);
                    break;
                } else {
                    setBit(queenMoves, targetSquare);
                }
            }
        }
    }

    // GENERATES POSSIBLE MOVES FOR BISHOP MOVEMENT
    for (int i = 0; i < 4; i++) {     // iterate through posChangeBishop array
        for (int j = 1; j < 8; j++) { // iterate through possible moves in a given direction determined by posChangeBishop
            int targetSquare = square + posChangeBishop[i] * j;
            // if in bounds
            if (targetSquare > -1 && targetSquare < 64) {
                // if target square is an ally piece or current piece is on border column and moving into border then break
                if (getBit(board[allyPieceBoard], targetSquare) || (square % 8 == 0 && (posChangeBishop[i] == -9 || posChangeBishop[i] == 7)) ||
                    (square % 8 == 7 && (posChangeBishop[i] == -7 || posChangeBishop[i] == 9))) {
                    break;
                    // if target square is an enemy piece, store as possible move then break
                } else if (getBit(board[enemyPieceBoard], targetSquare) != 0) {
                    setBit(queenMoves, targetSquare);
                    break;
                    // if in bounds then store as available move then continue looping
                } else {
                    setBit(queenMoves, targetSquare);
                }
            }
        }
    }
    printBitboard(queenMoves);
}

void kingMoves(Index square, Color color, Bitboard *board) {

    // INIT BOARD TO STORE POSSIBLE MOVES
    Bitboard kingMoves = EMPTY_BITBOARD;

    // POSSIBLE CHANGES IN POSITION FOR A KING
    int posChange[] = {8, -8, 1, -1, 7, 9, -7, -9};

    // HANDLES ALLY AND ENEMY BOARD DEFINITIONS
    int allyPieceBoard, enemyPieceBoard;
    if (color == WHITE) {
        allyPieceBoard = WHITE_PIECES;
        enemyPieceBoard = BLACK_PIECES;
    } else {
        allyPieceBoard = BLACK_PIECES;
        enemyPieceBoard = WHITE_PIECES;
    }

    // GENERATES POSSIBLE MOVES
    for (int i = 0; i < 8; i++) { // iterate through posChange array
        int targetSquare = square + posChange[i];

        // Check if target square is within bounds and doesn't cross board boundaries when wrapping around
        if (targetSquare >= 0 && targetSquare < 64 && !(square % 8 == 0 && (posChange[i] == -1 || posChange[i] == -9 || posChange[i] == 7)) &&
            !(square % 8 == 7 && (posChange[i] == 1 || posChange[i] == -7 || posChange[i] == 9))) {
            // Check if target square is not occupied by an ally piece
            if (!getBit(board[allyPieceBoard], targetSquare)) {
                // If target square is empty or occupied by an enemy piece, it's a possible move
                setBit(kingMoves, targetSquare);
            }
        }
    }
    printBitboard(kingMoves);
}

