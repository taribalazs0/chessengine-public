
#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long U64; // garantalt 64 bites, csak pozitiv (unsigned) - 64 mezo van a tablan is pontosan

enum { EMPTY, W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING, 
			  B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING};

enum {WHITE, BLACK, BOTH}; // melyik fel jon? both, ha megneznenk hogy egy mezot mindket fel tamad-e

// CASTLING
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 }; //white kingside castle, whit queenside castle... 

// 10X12-es tabla. A1 = 21, B1 = 22, ... H1 = 28
//				   A2 = 31, B2 = 32, ... H2 = 38
// NO_SQ: egy ertek, nem egy mezo/ nullpointer -> en passant-nal (mivel a jatszhato mezok 0-98)
// OFFBOARD: ez a mezo mar nem a palya resze, itt nem nezelodunk

enum {
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD = 99
};

typedef struct S_BOARD {

	int board[120];
	int side;
	int castle_rights;
	int en_passant;
	int fifty_move; // AFTER 50 MOVE NO PAWN MOVEMENT OR CAPTURE ITS DRAW
	int KingSq[2];  // INDEX 0: WHITE KING, INDEX 1: BLACK KING: SO WE DONT HAVE TO CHECK ALL 64 SQ FOR CHECKS & MATE


} S_BOARD;

typedef struct S_MOVE {

	int from;
	int to;
	int cap;	// enum-ban vannak eltarolva a babuk.
	int promoted;    // The piece the pawn became (EMPTY if none)
	int en_passant;  // 1 if it was an en passant capture

} S_MOVE;

typedef struct S_MOVELIST {
	S_MOVE moves[256]; // Max moves in any position is roughly 218
	int count;
} S_MOVELIST;

// main.c



// data.c

extern int KnightOffset[];
extern int KingOffset[];
extern int RookOffset[];
extern int BishopOffset[];
extern int QueenOffset[];
int IsEnemy(int piece, int side);
int SqAttacked(int sq, int side, S_BOARD* pos);
int IsCheck(S_BOARD* pos);


// movegen.c


void GenerateAllMoves(S_MOVELIST* list, S_BOARD* pos);

void GenerateBishopMoves(int sq, S_BOARD* pos, S_MOVELIST* list);
void GenerateQueenMoves(int sq, S_BOARD* pos, S_MOVELIST* list);
void GenerateKingMoves(int sq, S_BOARD* pos, S_MOVELIST* list);
void GenerateKnightMoves(int sq, S_BOARD* pos, S_MOVELIST* list);


void AddMove(int from, int to, int cap, int promoted, int en_passant, S_MOVELIST* list); // cap = capture


// board.c

void ResetBoard(S_BOARD* pos);
void PrintBoard(S_BOARD* pos);
char* NumberToSquare(const int sq);
void PrintMoveList(S_MOVELIST* list);

#endif