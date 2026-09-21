#include "defs.h"

void ResetBoard(S_BOARD* pos)
{

	int i;

	// 1. CLEAR: Set every single one of the 120 squares to OFFBOARD
	for (i = 0; i < 120; i++) 
	{
		pos->board[i] = OFFBOARD;
	}

    // 2. INITIALIZE PLAYABLE AREA: Set the 8x8 grid to EMPTY
        // We use nested loops to skip the padding automatically
    for (int rank = 0; rank <= 7; rank++) {
        for (int file = 0; file <= 7; file++) {
            int sq = (21 + (rank * 10) + file);
            pos->board[sq] = EMPTY;
        }
    }

    // PAWNS

    for (i = A2; i <= H2; i++)
    {
        pos->board[i] = W_PAWN;
    }
    for (i = A7; i <= H7; i++)
    {
        pos->board[i] = B_PAWN;
    }

    // KINGS

    pos->board[E1] = W_KING;
    pos->board[E8] = B_KING;

    // QUEENS

    pos->board[D1] = W_QUEEN;
    pos->board[D8] = B_QUEEN;

    // ROOKS

    pos->board[A1] = W_ROOK;
    pos->board[H1] = W_ROOK;
    pos->board[A8] = B_ROOK;
    pos->board[H8] = B_ROOK;
    
    // BISHOPS

    pos->board[C1] = W_BISHOP;
    pos->board[F1] = W_BISHOP;
    pos->board[C8] = B_BISHOP;
    pos->board[F8] = B_BISHOP;

    // KNIGHTS

    pos->board[B1] = W_KNIGHT;
    pos->board[G1] = W_KNIGHT;
    pos->board[B8] = B_KNIGHT;
    pos->board[G8] = B_KNIGHT;


    pos->side = WHITE;
    pos->en_passant = NO_SQ;
    pos->fifty_move = 0;
    pos->castle_rights = 0; 
}

void PrintBoard(S_BOARD* pos)
{
    // mapping enum values to readable characters
    // . = empty, uppercase = White, lowercase = black
    char PreChar[] = ".PNBRQKpnbrqk";

    int counter = 1;

    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file <= 7; file++) 
        {
            int sq = (21 + (rank * 10) + file);

            int piece = pos->board[sq];

       
            if (piece == EMPTY)    printf("%2c", PreChar[0]);
            if (piece == W_PAWN)   printf("%2c", PreChar[1]);
            if (piece == W_KNIGHT) printf("%2c", PreChar[2]);
            if (piece == W_BISHOP) printf("%2c", PreChar[3]);
            if (piece == W_ROOK)   printf("%2c", PreChar[4]);
            if (piece == W_QUEEN)  printf("%2c", PreChar[5]);
            if (piece == W_KING)   printf("%2c", PreChar[6]);
            if (piece == B_PAWN)   printf("%2c", PreChar[7]);
            if (piece == B_KNIGHT) printf("%2c", PreChar[8]);
            if (piece == B_BISHOP) printf("%2c", PreChar[9]);
            if (piece == B_ROOK)   printf("%2c", PreChar[10]);
            if (piece == B_QUEEN)  printf("%2c", PreChar[11]);
            if (piece == B_KING)   printf("%2c", PreChar[12]);

            if (counter % 8 == 0) printf("\n");
            counter++;
        }
    }
    printf("\n");

    
}


char* NumberToSquare(const int sq)
{
    static char output[3];

    int file = (sq % 10) - 1;  // oszlop: A oszlop: 21, 21 % 10 - 1 = 0 -> 'a' betu lesz
    int rank = (sq / 10) - 1;// sor. 1. sor: 21/10 = 2, - 1 = '1'. elso oszlop


    sprintf_s(output, 3, "%c%d", ('a' + file), rank); 
    return output;

}

void PrintMoveList(S_MOVELIST* list)
{
    printf("MoveList found a total moves of: %d!\n", list->count);
    
    for (int i = 0; i < list->count; i++)
    {
        int from = list->moves[i].from;
        int to = list->moves[i].to;
        int cap = list->moves[i].cap;
        int promoted = list->moves[i].promoted;
	
	
        // int en_passant --- we might not need it

        // mivel NumberToSquare-ben output static:
        printf("Move: %d: %s", i + 1, NumberToSquare(from));
        printf("%s", NumberToSquare(to));

        // promotion

        if (promoted != EMPTY) {
            // We only care about the piece type. 
            // If it's W_QUEEN(5) or B_QUEEN(11), we want to print 'q'.

            char pchar = ' ';

            // We check the piece type specifically. 
            
            if (promoted == W_KNIGHT || promoted == B_KNIGHT) pchar = 'n';
            else if (promoted == W_BISHOP || promoted == B_BISHOP) pchar = 'b';
            else if (promoted == W_ROOK || promoted == B_ROOK) pchar = 'r';
            else if (promoted == W_QUEEN || promoted == B_QUEEN) pchar = 'q';

            printf("%c", pchar);
        }

        // to make captures obvius just in case
        if (cap != EMPTY)
            printf(" (capture)");

        // en passant 
        if (list->moves[i].en_passant)
            printf(" (en passant)");

        printf("\n");
    }
}
