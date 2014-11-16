#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

static t;
void main()
{
	
	while(1)
	{
		CLEAR();
		printf("\033[32m1.Mission One:2048\033[0m\n");
		printf("\033[32m2.Mission Two:4096\033[0m\n");
		printf("\033[32m3.Mission Three:8192\033[0m\n");
		printf("\033[32m4.Mission Four:unlimited\033[0m\n");
		printf("\033[34m5.rule\033[0m\n");
		printf("\033[34m6.exit\033[0m\n\n");
		printf("please choose:");
		scanf("%d", &t);
		switch(t)
		{	
			case 1:
				start_game();
				check_game_over(t);
				sleep(5);
				break;
			case 2:
				start_game();
				check_game_over(t);
				sleep(5);
				break;
			case 3:
				start_game();
				check_game_over(t);
				sleep(5);
				break;
			case 4:
				start_game();
				check_game_over(t);
				sleep(5);
				break;								
			case 5:												
				CLEAR();
				printf("\t\033[31mThe rules of the game:\033[0m\n");					
				printf("\n\tturn towards one direction everytime,\n\tthe two same number will crack into their sum,\n\tafter one operation the game will show an random number as 2 or 4,\n\tif the bigest number is 2048 that mean you are win.\n");
				sleep(10);
				CLEAR();
				break;
			case 6:
				exit(0);
			default:													
				break;													
		}
	}
} 

