#include "defs.h"


int main()
{

	S_BOARD board;
	S_MOVELIST list;

	ResetBoard(&board);
	PrintBoard(&board);
	GenerateAllMoves(&list, &board);
	PrintMoveList(&list);


	/*
	S_BOARD* pos = malloc(sizeof(S_BOARD));
	S_MOVELIST* list = malloc(sizeof(int) * 256);

	if (pos == NULL) return 1;
	if (list == NULL) return 1;


	ResetBoard(pos);
	PrintBoard(pos);

	GenerateAllMoves(list, pos);

	printf("total found moves: %d\n", list->count);

	free(pos);
	free(list);

	*/

	return 0;
}
