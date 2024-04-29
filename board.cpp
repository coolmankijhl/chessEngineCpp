#include "board.h"

#include "pieceData.h"

// Prints Chess Board
void printBoard(Bitboard *bitboards) {
    char pieces[64]; // Array to store ASCII representations of pieces

    // Initialize the pieces array
    for (int i = 0; i < 64; ++i) {
        int row = i / 8;
        int col = i % 8;
        int square = row * 8 + col;
        pieces[i] = '.'; // Default empty square

        // Check each bitboard to determine the piece at the current square
        for (int j = 0; j < 18; ++j) {
            if (getBit(bitboards[j], square)) {
                switch (j) {
                case WHITE_PAWNS:
                    pieces[i] = 'P';
                    break;
                case WHITE_KNIGHTS:
                    pieces[i] = 'N';
                    break;
                case WHITE_BISHOPS:
                    pieces[i] = 'B';
                    break;
                case WHITE_ROOKS:
                    pieces[i] = 'R';
                    break;
                case WHITE_QUEENS:
                    pieces[i] = 'Q';
                    break;
                case WHITE_KING:
                    pieces[i] = 'K';
                    break;
                case BLACK_PAWNS:
                    pieces[i] = 'p';
                    break;
                case BLACK_KNIGHTS:
                    pieces[i] = 'n';
                    break;
                case BLACK_BISHOPS:
                    pieces[i] = 'b';
                    break;
                case BLACK_ROOKS:
                    pieces[i] = 'r';
                    break;
                case BLACK_QUEENS:
                    pieces[i] = 'q';
                    break;
                case BLACK_KING:
                    pieces[i] = 'k';
                    break;
                case EMPTY_SPACES:
                    pieces[i] = '.';
                    break;
                default:
                    break; // Ignore other bitboards
                }
                break; // Exit loop once a piece is found
            }
        }
    }

    // Print the board with pieces
    printf("\n       a b c d e f g h\n\n");
    for (int row = 0; row < 8; row++) {
        printf("    %d  ", 8 - row);
        for (int col = 0; col < 8; col++) {
            printf("%c ", pieces[row * 8 + col]);
        }
        printf("\n");
    }
    printf("\n");
}

void printBitboard(Bitboard bitboard) {
    printf("\n");
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (col == 0)
                printf("  %d  ", 8 - row);
            int square = row * 8 + col;
            printf(" %d", getBit(bitboard, (row * 8) + col) ? 1 : 0);
        }
        printf("\n");
    }
    printf("\n      a b c d e f g h\n\n");
    printf("      Bitboard: %lu \n\n", bitboard);
}

int getPieceType(char piece) {
    switch (piece) {
    case 'P':
        return WHITE_PAWNS;
    case 'N':
        return WHITE_KNIGHTS;
    case 'B':
        return WHITE_BISHOPS;
    case 'R':
        return WHITE_ROOKS;
    case 'Q':
        return WHITE_QUEENS;
    case 'K':
        return WHITE_KING;
    case 'p':
        return BLACK_PAWNS;
    case 'n':
        return BLACK_KNIGHTS;
    case 'b':
        return BLACK_BISHOPS;
    case 'r':
        return BLACK_ROOKS;
    case 'q':
        return BLACK_QUEENS;
    case 'k':
        return BLACK_KING;
    default:
        return -1;
    }
}

void fenToBitboards(const std::string fen, Bitboard *bitboards, Color *currentPlayerColor) {
    // Reset bitboards
    for (int i = 0; i < 20; ++i) {
        bitboards[i] = EMPTY_BITBOARD;
    }

    // Parse FEN string
    size_t rank = 0, file = 0;
    int parsingStage = 0;
    bool castlingRightsParsed = false; // Flag to check if castling rights are parsed

    for (char c : fen) {
        if (c == '/') {
            rank++;
            file = 0;
        } else if (c >= '1' && c <= '8') {
            file += (c - '0');
        } else {
            int square = rank * 8 + file;
            switch (parsingStage) {
            case 0: // Piece placements
                if (c != ' ') {
                    int pieceType = getPieceType(c);
                    if (pieceType != -1) {
                        setBit(bitboards[pieceType], square);
                        setBit(bitboards[OCCUPIED_SPACES], square);
                        if (islower(c)) {
                            setBit(bitboards[BLACK_PIECES], square);
                        } else {
                            setBit(bitboards[WHITE_PIECES], square);
                        }
                        file++;
                    }
                } else {
                    parsingStage++;
                }
                break;
            case 1: // Current player color
                *currentPlayerColor = (c == 'w') ? WHITE : BLACK;
                parsingStage++;
                break;
            case 2: // Castling rights
                if (c == ' ') {
                    parsingStage++;
                    break;
                }
                if (c != '-') {
                    switch (c) {
                    case 'K':
                        setBit(bitboards[CASTLING_RIGHTS], h1);
                        break;
                    case 'Q':
                        setBit(bitboards[CASTLING_RIGHTS], a1);
                        break;
                    case 'k':
                        setBit(bitboards[CASTLING_RIGHTS], h8);
                        break;
                    case 'q':
                        setBit(bitboards[CASTLING_RIGHTS], a8);
                        break;
                    }
                }
                break;
            case 3: // En passant target square and halfmove and fullmove counters (not implemented in this example)
                // Handle en passant target square, halfmove and fullmove counters here
                break;
            }
            if (parsingStage > 2 && !castlingRightsParsed) {
                castlingRightsParsed = true;
                parsingStage++; // Move to the next parsing stage after parsing castling rights
            }
        }
    }

    // Set bitboard for empty spaces
    bitboards[EMPTY_SPACES] = ~bitboards[OCCUPIED_SPACES];
}

