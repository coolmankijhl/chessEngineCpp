#include "board.h"

#include "pieceData.h"

// clang-format off

// Map for converting user input to index
std::map<std::string, Index> stringToIndexMap = {
    {"a8", a8}, {"b8", b8}, {"c8", c8}, {"d8", d8}, {"e8", e8}, {"f8", f8}, {"g8", g8}, {"h8", h8},
    {"a7", a7}, {"b7", b7}, {"c7", c7}, {"d7", d7}, {"e7", e7}, {"f7", f7}, {"g7", g7}, {"h7", h7},
    {"a6", a6}, {"b6", b6}, {"c6", c6}, {"d6", d6}, {"e6", e6}, {"f6", f6}, {"g6", g6}, {"h6", h6},
    {"a5", a5}, {"b5", b5}, {"c5", c5}, {"d5", d5}, {"e5", e5}, {"f5", f5}, {"g5", g5}, {"h5", h5},
    {"a4", a4}, {"b4", b4}, {"c4", c4}, {"d4", d4}, {"e4", e4}, {"f4", f4}, {"g4", g4}, {"h4", h4},
    {"a3", a3}, {"b3", b3}, {"c3", c3}, {"d3", d3}, {"e3", e3}, {"f3", f3}, {"g3", g3}, {"h3", h3},
    {"a2", a2}, {"b2", b2}, {"c2", c2}, {"d2", d2}, {"e2", e2}, {"f2", f2}, {"g2", g2}, {"h2", h2},
    {"a1", a1}, {"b1", b1}, {"c1", c1}, {"d1", d1}, {"e1", e1}, {"f1", f1}, {"g1", g1}, {"h1", h1}
};

// clang-format on

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

void fenToBitboards(const std::string fen, Bitboard *bitboards, Color *currentPlayerColor) {
    // Reset bitboards
    for (int i = 0; i < 20; ++i) {
        bitboards[i] = 0ULL;
    }

    // Parse FEN string
    size_t index = 0;
    size_t rank = 0, file = 0;
    int parsingStage = 0;

    for (char c : fen) {
        if (c == '/') {
            rank++;
            file = 0;
        } else if (c >= '1' && c <= '8') {
            file += (c - '0');
        } else {
            int square = rank * 8 + file;
            if (parsingStage == 0) {
                switch (c) {
                // Parsing piece placements
                case 'P':
                    setBit(bitboards[WHITE_PAWNS], square);
                    setBit(bitboards[WHITE_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'N':
                    setBit(bitboards[WHITE_KNIGHTS], square);
                    setBit(bitboards[WHITE_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'B':
                    setBit(bitboards[WHITE_BISHOPS], square);
                    setBit(bitboards[WHITE_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'R':
                    setBit(bitboards[WHITE_ROOKS], square);
                    setBit(bitboards[WHITE_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'Q':
                    setBit(bitboards[WHITE_QUEENS], square);
                    setBit(bitboards[WHITE_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'K':
                    setBit(bitboards[WHITE_KING], square);
                    setBit(bitboards[WHITE_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'p':
                    setBit(bitboards[BLACK_PAWNS], square);
                    setBit(bitboards[BLACK_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'n':
                    setBit(bitboards[BLACK_KNIGHTS], square);
                    setBit(bitboards[BLACK_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'b':
                    setBit(bitboards[BLACK_BISHOPS], square);
                    setBit(bitboards[BLACK_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'r':
                    setBit(bitboards[BLACK_ROOKS], square);
                    setBit(bitboards[BLACK_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'q':
                    setBit(bitboards[BLACK_QUEENS], square);
                    setBit(bitboards[BLACK_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case 'k':
                    setBit(bitboards[BLACK_KING], square);
                    setBit(bitboards[BLACK_PIECES], square);
                    setBit(bitboards[OCCUPIED_SPACES], square);
                    break;
                case ' ':
                    parsingStage++;
                    break;
                default:
                    break; // Ignore other characters
                }
                file++;
            }
            if (parsingStage == 1) {
                switch (c) {
                case 'w':
                    *currentPlayerColor = WHITE;
                    break;
                case 'b':
                    *currentPlayerColor = BLACK;
                    break;
                case ' ':
                    parsingStage++;
                    break;
                defeault:
                    break;
                }
            }
            if (parsingStage == 2) {
                // Parsing castling rights
                switch (c) {
                case 'K':
                    setBit(bitboards[CASTLING_RIGHTS], h1); // White kingside castle
                    break;
                case 'Q':
                    setBit(bitboards[CASTLING_RIGHTS], a1); // White queenside castle
                    break;
                case 'k':
                    setBit(bitboards[CASTLING_RIGHTS], h8); // Black kingside castle
                    break;
                case 'q':
                    setBit(bitboards[CASTLING_RIGHTS], a8); // Black queenside castle
                    break;
                default:
                    break; // Ignore other characters
                }
            }
        }
    }

    // Set bitboards for empty spaces and pieces
    bitboards[EMPTY_SPACES] = ~bitboards[OCCUPIED_SPACES];
}
