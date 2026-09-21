

#include "defs.h" 

// SLIDING LOOPS SLIDING PIECES (QUEEN, ROOK, BISHOP)

// Generaljuk a lehetseeges helyeket ahova a ROOK lephet

void GenerateRookMoves(int sq, S_BOARD* pos, S_MOVELIST* list)
{
    for (int i = 0; i < 4; i++)  // 0,1,2,3 (4) db irany a bastyanak
    {
        int dir = RookOffset[i];
        int target_sq = sq + dir; // Egy mezovel arrebb nezzuk

        while (pos->board[target_sq] != OFFBOARD)
        {
            if (pos->board[target_sq] != EMPTY)
            {
                if (IsEnemy(pos->board[target_sq], pos->side))
                    AddMove(sq, target_sq, pos->board[target_sq], EMPTY, EMPTY, list);

                break;

            }


            // Ha ures a mezo
            else
                AddMove(sq, target_sq, EMPTY, EMPTY, EMPTY, list);
            target_sq += dir;

            // TODO : minden AddMove uj formatumba irasa  : void AddMove(int from, int to, int cap, int promoted, int en_passant, S_MOVELIST* list)
            


        }
    }
}

void GenerateBishopMoves(int sq, S_BOARD* pos, S_MOVELIST* list)
{
    for (int i = 0; i < 4; i++)
    {
        int dir = BishopOffset[i];
        int target_sq = sq + dir;

        while (pos->board[target_sq] != OFFBOARD)
        {
            if (pos->board[target_sq] != EMPTY)
            {
                if (IsEnemy(pos->board[target_sq], pos->side))
                    AddMove(sq, target_sq, pos->board[target_sq], EMPTY, EMPTY, list);
                break;

            }



            // Ha ures a mezo

            AddMove(sq, target_sq, EMPTY, EMPTY, EMPTY, list);
            target_sq += dir;
        }

    }
}

void GenerateQueenMoves(int sq, S_BOARD* pos, S_MOVELIST* list) {
    for (int i = 0; i < 8; i++) {
        int dir = QueenOffset[i];
        int target_sq = sq + dir;


        while (pos->board[target_sq] != OFFBOARD)
        {
            if (pos->board[target_sq] != EMPTY)
            {
                if (IsEnemy(pos->board[target_sq], pos->side))
                    AddMove(sq, target_sq, pos->board[target_sq], EMPTY, EMPTY, list);
                break;
            }




            // Ha ures a mezo

            AddMove(sq, target_sq, EMPTY, EMPTY, EMPTY, list);
            target_sq += dir;
        }

    }
}

void GenerateKingMoves(int sq, S_BOARD* pos, S_MOVELIST* list)
{
    for (int i = 0; i < 8; i++)
    {
        int dir = KingOffset[i];
        int target_sq = sq + dir;

        if (pos->board[target_sq] == OFFBOARD) continue;
        if (pos->board[target_sq] == EMPTY)
            AddMove(sq, target_sq, EMPTY, EMPTY, EMPTY, list);

        else if (IsEnemy(pos->board[target_sq], pos->side))
            AddMove(sq, target_sq, pos->board[target_sq], EMPTY, EMPTY, list);
    }
}

void GenerateKnightMoves(int sq, S_BOARD* pos, S_MOVELIST* list)
{
    for (int i = 0; i < 8; i++)  // 8 irany a huszarnak
    {
        int dir = KnightOffset[i];
        int target_sq = sq + dir;


        if (pos->board[target_sq] == OFFBOARD) continue;

        if (pos->board[target_sq] == EMPTY)
            AddMove(sq, target_sq, EMPTY, EMPTY, EMPTY, list);

        else if (IsEnemy(pos->board[target_sq], pos->side))
            AddMove(sq, target_sq, pos->board[target_sq], EMPTY, EMPTY, list);
    }

}


/*

GeneratePawnMoves()


- we have to keep in mind if its the first step of the pawn, because then it can either go two forward or one.
if its not the first step then it can only go forward once.

- the pawn can only capture diagonally. which means that
we have to scan the squares +11 and +9 always to see if it can capture

- promotion. if the pawn gets to the 8th rank the player has to make a choice,
select a piece to promote the pawn to. in this situation we save all four legit moves to the list
(queen, rook, bishop, knight)

- en passant: if the enemy's pawn makes its first move of the game,
and after that it gets next to our pawn (so -1 or +1) we have the option to capture it.
en passant can ONLY happen RIGHT AFTER the double-step.



*/

GeneretaePawnMoves(int sq, S_BOARD* pos, S_MOVELIST* list)
{
    if (pos->side == WHITE)
    {
        if (pos->board[sq + 10] == EMPTY)
        {
            // promotion
            if(sq + 10 >= A8 && sq + 10 <= H8)
            {
                AddMove(sq, sq + 10, EMPTY, W_QUEEN, 0, list);
                AddMove(sq, sq + 10, EMPTY, W_ROOK, 0, list);
                AddMove(sq, sq + 10, EMPTY, W_BISHOP, 0, list);
                AddMove(sq, sq + 10, EMPTY, W_KNIGHT, 0, list);

            }
            // else normal move
            else
            { 
                // if its on the 2nd rank it has the option to go 2 forward
                if (sq >= A2 && sq <= H2)
                {
                    AddMove(sq, sq + 10, EMPTY, EMPTY, 0, list);
                    if (pos->board[sq + 20] == EMPTY)
                        AddMove(sq, sq + 20, EMPTY, EMPTY, 0, list);
                }
                else AddMove(sq, sq + 10, EMPTY, EMPTY, 0, list);
            }
        }

        // diagonal capture option
       
       int piece;
       if(pos->board[sq + 9] != OFFBOARD)
       {
           piece = pos->board[sq + 9];
           if (piece >= B_PAWN && piece <= B_KING) {
               
               // if: promotion
               if (sq + 9 >= A8 && sq + 9 <= H8)
               {
                   AddMove(sq, sq + 9, piece, W_QUEEN, 0, list);
                   AddMove(sq, sq + 9, piece, W_ROOK, 0, list);
                   AddMove(sq, sq + 9, piece, W_BISHOP, 0, list);
                   AddMove(sq, sq + 9, piece, W_KNIGHT, 0, list);

               }
               else AddMove(sq, sq + 9, piece, EMPTY, 0, list);
           }

       }
        
       if (pos->board[sq + 11] != OFFBOARD)
       {
           piece = pos->board[sq + 11];
           if (piece >= B_PAWN && piece <= B_KING)
           {

               if (sq + 11 >= A8 && sq + 11 <= H8)
               {
                   AddMove(sq, sq + 11, piece, W_QUEEN, 0, list);
                   AddMove(sq, sq + 11, piece, W_ROOK, 0, list);
                   AddMove(sq, sq + 11, piece, W_BISHOP, 0, list);
                   AddMove(sq, sq + 11, piece, W_KNIGHT, 0, list);

               }
               else AddMove(sq, sq + 11, piece, EMPTY, 0, list);
           }
       }
        

        // en passant
       if (pos->en_passant != NO_SQ)
       {
           if (sq + 9 == pos->en_passant)
               AddMove(sq, sq + 9, B_PAWN, EMPTY, 1, list); // 1 = en passant
           if (sq + 11 == pos->en_passant)
               AddMove(sq, sq + 11, B_PAWN, EMPTY, 1, list);
       }
    }

    else // if black's turn
    {
        if (pos->board[sq - 10] == EMPTY)
        {
            // promotion
            if (sq - 10 >= A1 && sq - 10 <= H1)
            {
                AddMove(sq, sq - 10, EMPTY, B_QUEEN, 0, list);
                AddMove(sq, sq - 10, EMPTY, B_ROOK, 0, list);
                AddMove(sq, sq - 10, EMPTY, B_BISHOP, 0, list);
                AddMove(sq, sq - 10, EMPTY, B_KNIGHT, 0, list);

            }
            // else normal move
            else
            {
                // if its on the 2nd rank it has the option to go 2 forward
                if (sq >= A7 && sq <= H7)
                {
                    AddMove(sq, sq - 10, EMPTY, EMPTY, 0, list);
                    if (pos->board[sq - 20] == EMPTY)
                        AddMove(sq, sq - 20, EMPTY, EMPTY, 0, list);
                }
                else AddMove(sq, sq - 10, EMPTY, EMPTY, 0, list);
            }
        }

        // diagonal capture option

        int piece;
        if (pos->board[sq - 9] != OFFBOARD)
        {
            piece = pos->board[sq - 9];
            if (piece >= W_PAWN && piece <= W_KING) {

                // if: promotion
                if (sq - 9 >= A1 && sq - 9 <= H1)
                {
                    AddMove(sq, sq - 9, piece, B_QUEEN, 0, list);
                    AddMove(sq, sq - 9, piece, B_ROOK, 0, list);
                    AddMove(sq, sq - 9, piece, B_BISHOP, 0, list);
                    AddMove(sq, sq - 9, piece, B_KNIGHT, 0, list);

                }
                else AddMove(sq, sq - 9, piece, EMPTY, 0, list);
            }

        }

        if (pos->board[sq - 11] != OFFBOARD)
        {
            piece = pos->board[sq - 11];
            if (piece >= W_PAWN && piece <= W_KING)
            {

                if (sq - 11 >= A1 && sq - 11 <= H1)
                {
                    AddMove(sq, sq - 11, piece, B_QUEEN, 0, list);
                    AddMove(sq, sq - 11, piece, B_ROOK, 0, list);
                    AddMove(sq, sq - 11, piece, B_BISHOP, 0, list);
                    AddMove(sq, sq - 11, piece, B_KNIGHT, 0, list);

                }
                else AddMove(sq, sq - 11, piece, EMPTY, 0, list);
            }
        }


        // en passant
        if (pos->en_passant != NO_SQ)
        {
            if (sq - 9 == pos->en_passant)
                AddMove(sq, sq - 9, W_PAWN, EMPTY, 1, list); // 1 = en passant
            if (sq - 11 == pos->en_passant)
                AddMove(sq, sq - 11, W_PAWN, EMPTY, 1, list);
        }
    }
   
}


void AddMove(int from, int to, int cap, int promoted, int en_passant, S_MOVELIST* list)
{
    int index = list->count;

    list->moves[index].from = from;
    list->moves[index].to = to;
    list->moves[index].cap = cap;
    list->moves[index].promoted = EMPTY;
    list->moves[index].en_passant = EMPTY;

    list->count++;
}


void GenerateAllMoves(S_MOVELIST* list, S_BOARD* pos)
{
    list->count = 0;
    int side = pos->side;

    if (side == WHITE)
    {
        if (pos->castle_rights & WQCA) {
            if (pos->board[D1] == EMPTY && pos->board[C1] == EMPTY && pos->board[B1] == EMPTY) {
                if (!IsCheck(pos) && !SqAttacked(D1, BLACK, pos) && !SqAttacked(C1, BLACK, pos)) {
                    AddMove(E1, C1, EMPTY, EMPTY, 0, list);
                }
            }
        }
        if (pos->castle_rights & WKCA) {
            if (pos->board[F1] == EMPTY && pos->board[G1] == EMPTY) {
                if (!IsCheck(pos) && !SqAttacked(F1, BLACK, pos) && !SqAttacked(G1, BLACK, pos)) {
                    AddMove(E1, G1, EMPTY, EMPTY, 0, list);
                }
            }
        }
    }
    if (side == BLACK)
    {

        if (pos->castle_rights & BQCA) {
            if (pos->board[D8] == EMPTY && pos->board[C8] == EMPTY && pos->board[B8] == EMPTY) {
                if (!IsCheck(pos) && !SqAttacked(D8, WHITE, pos) && !SqAttacked(C8, WHITE, pos)) {
                    AddMove(E8, C8, EMPTY, EMPTY, 0, list);
                }
            }
        }
        if (pos->castle_rights & BKCA) {
            if (pos->board[F8] == EMPTY && pos->board[G8] == EMPTY) {
                if (!IsCheck(pos) && !SqAttacked(F8, WHITE, pos) && !SqAttacked(G8, WHITE, pos)) {
                    AddMove(E8, G8, EMPTY, EMPTY, 0, list);
                }
            }
        }
    }
    for (int rank = 0; rank <= 7; rank++)
    {
        for (int file = 0; file <= 7; file++)
        {
            int sq = (21 + (rank * 10) + file);
            int piece = pos->board[sq];



            if (piece == OFFBOARD || piece == EMPTY) continue;


            if (side == WHITE)
            {
                if (piece >= B_PAWN) continue;
            }
            else
            {
                if (piece <= W_KING && piece != EMPTY) continue;
            }

            switch (piece)
            {
            case W_KNIGHT:
                GenerateKnightMoves(sq, pos, list); break;
            case B_KNIGHT:
                GenerateKnightMoves(sq, pos, list); break;
            case W_BISHOP:
                GenerateBishopMoves(sq, pos, list); break;
            case B_BISHOP:
                GenerateBishopMoves(sq, pos, list); break;
            case W_KING:
                GenerateKingMoves(sq, pos, list); break;
            case B_KING:
                GenerateKingMoves(sq, pos, list); break;
            case W_QUEEN:
                GenerateQueenMoves(sq, pos, list); break;
            case B_QUEEN:
                GenerateQueenMoves(sq, pos, list); break;
            case W_ROOK:
                GenerateRookMoves(sq, pos, list); break;
            case B_ROOK:
                GenerateRookMoves(sq, pos, list); break;
            case W_PAWN:
                GeneretaePawnMoves(sq, pos, list); break;
            case B_PAWN:
                GeneretaePawnMoves(sq, pos, list); break;

            }



        }
    }
}
