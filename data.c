#include "defs.h"

// OFFSETS

int KnightOffset[] = {-21, -19, -12, -8, 8, 12, 19, 21};
int KingOffset[] = {-11, -10, -9, -1, 1, 9, 10, 11};

//	Sliding Pieces(Rook, Bishop, Queen)
// 
//	These pieces move in a direction until they hit a piece 
//	or the OFFBOARD edge.We use the same offset logic,
//	but we put them in a while loop.

int RookOffset[] = {-10, -1, 1, 10};
int BishopOffset[] = {-11, -9, 9, 11};
int QueenOffset[] = {-11, -10, -9, -1, 1, 9, 10, 11};



int IsEnemy(int piece, int side)
{
    if (piece == EMPTY || piece == OFFBOARD) return 0;

    if (side == WHITE)
        return (piece >= B_PAWN && piece <= B_KING);
    else
        return (piece >= W_PAWN && piece <= W_KING);

}

/*
Step 1: Look at sq + 11, sq + 9, etc. Do you see an enemy Pawn?

Step 2: Look at all Knight offsets. Do you see an enemy Knight?

Step 3: Look along Rook lines. Do you see an enemy Rook or Queen?

Step 4: Look along Bishop lines. Do you see an enemy Bishop or Queen?

Step 5: Look at the 8 squares around you. Is the enemy King there?
*/

int SqAttacked(int sq, int side, S_BOARD* pos)
{
    int pce, target_sq, dir;

    // 1. PAWNS
    if (side == WHITE) 
    {
        if (pos->board[sq - 11] == W_PAWN || pos->board[sq - 9] == W_PAWN) return 1;
    }
    else {
        if (pos->board[sq + 11] == B_PAWN || pos->board[sq + 9] == B_PAWN) return 1;
    }

    // 2. KNIGHTS
    for (int i = 0; i < 8; i++)
    {
        pce = pos->board[sq + KnightOffset[i]];
        if (side == WHITE) {
            if (pce == W_KNIGHT) return 1;
        }
        else {
            if (pce == B_KNIGHT) return 1;
        }
    }

    // 3. ROOKS AND QUEEN 
    for (int i = 0; i < 4; i++)
    {
        dir = RookOffset[i];
        target_sq = sq + dir;
        while (pos->board[target_sq] != OFFBOARD) {
            pce = pos->board[target_sq];
            if (pce != EMPTY) {
                if (side == WHITE) {
                    if (pce == W_ROOK || pce == W_QUEEN) return 1;
                }
                else {
                    if (pce == B_ROOK || pce == B_QUEEN) return 1;
                }
                break; // Line blocked by a piece
            }
            target_sq += dir;
        }
    }

    // 4. BISHOPS AND QUEEN
    for (int i = 0; i < 4; i++)
    {
        dir = BishopOffset[i];
        target_sq = sq + dir;
        while (pos->board[target_sq] != OFFBOARD) {
            pce = pos->board[target_sq];
            if (pce != EMPTY) {
                if (side == WHITE) {
                    if (pce == W_BISHOP || pce == W_QUEEN) return 1;
                }
                else {
                    if (pce == B_BISHOP || pce == B_QUEEN) return 1;
                }
                break; // Line blocked
            }
            target_sq += dir;
        }
    }

    // 5. KING
    for (int i = 0; i < 8; i++) 
    {
        pce = pos->board[sq + KingOffset[i]];
        if (side == WHITE) {
            if (pce == W_KING) return 1;
        }
        else {
            if (pce == B_KING) return 1;
        }
    }

    return 0;
}


int IsCheck(S_BOARD* pos)
{
    if (pos->side == WHITE)
    {
        if (SqAttacked(pos->KingSq[0], BLACK, pos)) return 1;
    }
    else if (pos->side == BLACK)
    {
        if (SqAttacked(pos->KingSq[1], WHITE, pos)) return 1;
    }

    return 0;

}
