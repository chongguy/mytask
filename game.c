#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<termios.h>
#include<assert.h>
#include<unistd.h>

#define CLEAR() printf("\033[2J")

void start_game(); 
void reset_game(); 
void move_left(); 
void move_right();
void move_up();
void move_down();
void refresh_show();    /*refresh the screen*/
void add_rand_num();    /*generate 2 or 4 as random number,and the ratio is     2:1*/
void check_game_over(); /*check whether the game over*/
int get_null_count();   /*catch the position of empty block*/

int board[4][4];     
int score;          
int best;            
int if_need_add_num; /*1 stands for need a random number to appear,vise versa*/
int if_game_over;   /*1 stands for game over, vise versa*/

int getch()
{
	int c=0;
	struct termios org_opts, new_opts;
	int res=0;
	//-----  store old settings -----------
	res=tcgetattr(STDIN_FILENO, &org_opts);
	assert(res==0);
	//---- set new terminal parms --------
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c=getchar();
	//------  restore old settings ---------
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res==0);
	return c;
}
static t;/*determine game mission*/
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

void start_game()
{
   reset_game();
   char order;
   while (1)
   {
		order = getch(); 
    
	    if (if_game_over) 
		{
			if (order == 'y' || order == 'Y') 
			{
				 reset_game();
                 continue;
			}
            else if (order == 'n' || order == 'N') 
			{
                return;
			}
            else
			{
               continue;
            }
		}
         
        if_need_add_num = 0; 
        switch (order) 
		{
			case 'a':
            case 'A':
              move_left();
              break;
            case 'd':
            case 'D':
               move_right();
               break;
            case 'w':
            case 'W':
               move_up();
               break;
            case 's':
			case 'S':
                move_down();
                break;
		}
           
           score > best ? best = score : 1;
           
           if (if_need_add_num) 
           {
               add_rand_num();
               refresh_show();
           }
   }
}
   
void reset_game()
{
	int i,j;
    score = 0;
    if_need_add_num = 1;
	if_game_over = 0;
	int n = rand() % 16;
    for(i = 0; i < 4; i++)
    	for(j = 0; j < 4; j++)
	   	{
       		board[i][j] = (n-- == 0 ? 2 : 0);
       	}
	
    add_rand_num();
    CLEAR();
    refresh_show();
}
  
 void add_rand_num()
 {
	int i,j;
    srand(time(0));
    int n = rand() % get_null_count();
    for(i = 0; i < 4; i++)
       for(j = 0; j < 4; j++)
       {
           if (board[i][j] == 0 && n-- == 0) 
           {
               board[i][j] = (rand() % 3 ? 2 : 4);
               return;
		   }
	   }
 }
 
 int get_null_count()
 {
     int n = 0;
	 int i, j;
     for(i = 0; i < 4; i++)
	 {
        for(j = 0; j < 4; j++)
		{
            board[i][j] == 0 ? n++ : 1;
        }
     }
    return n;
 }

 void check_game_over(int m)
 {
	int i, j;
	long int max = 0;
    for (i = 0; i < 4; i++)
       for (j = 0; j < 4; j++)
	   {  
		   if(board[i][j] > max)
		   {
			   max = board[i][j];
		   }
	   }
	if (m != 4) 
		if (max = m * 2048)
			if_game_over = 1;printf("U WIN !");
	for (i = 0; i < 4 ; i++)
		for(j = 0; j < 3; j++)
		{
          if ( board[i][j] == board[i][j+1] || board[j][i] == board[j+1][i])
		  {
             if_game_over = 0;
            return;
		  }
        }
   if_game_over = 1;
 } 
 
 void move_left()
 {
	int i, j, k; 
    for (i = 0; i < 4; i++)
		for (j = 1, k = 0; j < 4; j++)
		{
            if (board[i][j] > 0) 
			{
                if (board[i][k] == board[i][j]) 
				{
                    score += board[i][k++] <<= 1;
                    board[i][j] = 0;
                    if_need_add_num = 1; 
				}
              	else if (board[i][k] == 0) 
              	{
                  	board[i][k] = board[i][j];
                  	board[i][j] = 0;
                  	if_need_add_num = 1;
			  	}
              	else 
			  	{
                   	board[i][++k] = board[i][j];
                   	if (j != k) 
                   	{
                       	board[i][j] = 0;
                       	if_need_add_num = 1;
				   	}
			  	}
            }
		}
 }
 
 void move_right()
 {
	int i, j, k;
    for (i = 0; i < 4; i++)
       for (j = 2, k = 3; j >= 0; j--)
       {
          if (board[i][j] > 0)
		  {
              if (board[i][k] == board[i][j])
			  {
                  score += board[i][k--] <<= 1;
                  board[i][j] = 0;
                  if_need_add_num = 1;
			  }
              else if (board[i][k] == 0)
			  {
                  board[i][k] = board[i][j];
                  board[i][j] = 0;
                  if_need_add_num = 1;
			  }
              else
			  {
                  board[i][--k] = board[i][j];
                  if (j != k)
                  {
                      board[i][j] = 0;
                     if_need_add_num = 1;
                  }
			  }
		  }
	   }
 }

void move_up()
{
   int i, j, k;
   for (i = 0; i < 4; i++)
        for (j = 1, k = 0; j < 4; j++)
		{
            if (board[j][i] > 0)
			{
                if (board[k][i] == board[j][i])
				{
                    score += board[k++][i] <<= 1;
                    board[j][i] = 0;
                   if_need_add_num = 1;
				}
                else if (board[k][i] == 0)
				{
                     board[k][i] = board[j][i];
                     board[j][i] = 0;
                     if_need_add_num = 1;
				}
                else
				{
                    board[++k][i] = board[j][i];
                    if (j != k)
					{
                       board[j][i] = 0;
                       if_need_add_num = 1;
					}
				}
           }
        }
}
 
 void move_down()
 {
	 int i, j, k;
     for (i = 0; i < 4; i++)
         for (j = 2, k = 3; j >= 0; j--)
		 {
              if (board[j][i] > 0)
			  {
                  if (board[k][i] == board[j][i])
		
				  
				  {
                     score += board[k--][i] <<= 1;
                     board[j][i] = 0;
                      if_need_add_num = 1;
                  }
                  else if (board[k][i] == 0)
                  {
                      board[k][i] = board[j][i];
                      board[j][i] = 0;
                      if_need_add_num = 1;
                  }
                  else
                  {
                      board[--k][i] = board[j][i];
                      if (j != k)
                      {
                          board[j][i] = 0;
                          if_need_add_num = 1;
                      }
                  }
              }
		 }
 }
  
 void refresh_show()
 {
	 int i, j;

     CLEAR();
      
      printf("\n\n\n\n");
      printf("                GAME: 2048     SCORE: %06d    BEST: %06d\n", score, best);
      printf("             --------------------------------------------------\n\n");
      printf("                        ---------------------\n");
      for (i = 0; i < 4; i++)
      {
          printf("                        |");
          for (j = 0; j < 4; j++)
          {
              if (board[i][j] != 0)
              {
                  if (board[i][j] < 10)
                  {
                     printf("  %d |", board[i][j]);                    
                  }
                  else if (board[i][j] < 100)
                  {
                      printf(" %d |", board[i][j]);
                  }
                  else if (board[i][j] < 1000)
                  {
                      printf(" %d|", board[i][j]);
                  }
                  else if (board[i][j] < 10000)
                  {
                      printf("%4d|", board[i][j]);
                  }
                  else
                  {
                      int n = board[i][j];
					  int k;
                      for (k = 1; k < 20; k++)
                      {
                         n >>= 1;
                          if (n == 1)
                          {
                              printf("2^%02d|", k);
                              break;
                          }
                      }
                  }
              }
              else printf("    |");
          }
          
          if (i < 3)
          {
              printf("\n                        |----|----|----|----|\n");
          }
          else
          {
              printf("\n                        |____|____|____|____|\n");
          }
      }
    
      printf("\n");
      printf("             --------------------------------------------------\n");
      printf("                            W  A   D  S");
      
      if (get_null_count() == 0)
      {
         check_game_over(t);
          if (if_game_over) 
          {
              printf("\r                    GAME OVER! TRY THE GAME AGAIN? [Y/N]");
          }
    }
}
