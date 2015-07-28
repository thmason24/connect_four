/* Print the state of the connect 4 board */

#include<stdio.h>
#include<iostream>

// header files
#include "thmmqc_slot_type.h"
#include "thmmqc_print_board.h"

//enum slot {blank, own, opp };


void thmmqc_print_board(slot board[6][7])

{
/*  declare data structute of board.   6 by 7 array of type "SLOT" which can be blank, own, or opp */

int i;
int j;

for(i=5;i>-1;i--)
{
	for(j=0;j<7;j++)
	{
		switch( board[i][j] )
		{
			case 0:
				printf(" --- ");
				break;
			case 1:
				printf("  X  ");
				break;
			case 2:
				printf("  O  ");
				break;
			default:
			    printf("ERROR!!!");
		}
	}
	printf("\n");
}
	printf("\n  0    1    2    3    4    5    6\n");
}

