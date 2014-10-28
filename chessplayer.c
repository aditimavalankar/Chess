#include<stdio.h>
#include<string.h>
#include<math.h>
typedef struct piece
{
	int code;
	int points;
}piece;
typedef struct team
{
	piece p[6];
	int number[6];
}team;
team white,black;
int moves=0;
int killed[5000]={0};
int killedpieces=0;
int wkingx=7,wkingy=4;
int bkingx=0,bkingy=4;
int arr[8][8]={0};
int king_under_attack(int,int,int,int);
void printboard()
{
	printf("\n");
	int i,j;
	printf("    |");
	for(j=0;j<8;j++)
		printf("    %d    |",j+1);
	for(i=0;i<8;i++)
	{
		printf("\n");
		for(j=0;j<85;j++)
			printf("-");
		printf("\n");
		printf("| %c ",i+'A');
		printf("|");
		for(j=0;j<8;j++)
		{
			if(arr[i][j]==0)
				printf("         |");
			else if(arr[i][j]==10)
				printf(" WKing   |");
			else if(arr[i][j]==20)
				printf(" BKing   |");
			else if(arr[i][j]==11)
				printf(" WQueen  |");
			else if(arr[i][j]==21)
				printf(" BQueen  |");
			else if(arr[i][j]==12)
				printf(" WRook   |");
			else if(arr[i][j]==22)
				printf(" BRook   |");
			else if(arr[i][j]==13)
				printf(" WBishop |");
			else if(arr[i][j]==23)
				printf(" BBishop |");
			else if(arr[i][j]==14)
				printf(" WKnight |");
			else if(arr[i][j]==24)
				printf(" BKnight |");
			else if(arr[i][j]==15)
				printf(" WPawn   |");
			else
				printf(" BPawn   |");
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<81;i++)
		printf("-");
	printf("\n\n");
	return;
}
int final_checkmate(int x,int y,int team)
{
	int checkflag=0;
	int i,j,temp,flag,flag1,flag2,flag3,flag4,intermediate,savex,savey;
	if(team==1)
	{
		//pawn attacking king
		if(arr[x-1][y+1]==25 && y<7)
		{
			checkflag=1;
			if(!(king_under_attack(x-1,y+1,1,0)))
				return 0;
		}
		if(arr[x-1][y-1]==25 && y>0)
		{
			checkflag=1;
			if(!(king_under_attack(x-1,y-1,1,0)))
				return 0;
		}
		//knight attacking king
		if(arr[x+2][y+1]==24 && x<6 && y<7)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x+2,y+1,2,0)))
				return 1;
		}
		if(arr[x+2][y-1]==24 && x<6 && y>0)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x+2,y-1,2,0)))
				return 1;
		}
		if(arr[x-2][y+1]==24 && x>1 && y<7)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x-2,y+1,2,0)))
				return 1;
		}
		if(arr[x-2][y-1]==24 && x>1 && y>0)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x-2,y-1,2,0)))
				return 1;
		}
		if(arr[x+1][y+2]==24 && x<7 && y<6)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x+1,y+2,2,0)))
				return 1;
		}
		if(arr[x+1][y-2]==24 && x<7 && y>1)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x+1,y-2,2,0)))
				return 1;
		}
		if(arr[x-1][y+2]==24 && x>0 && y<6)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x-1,y+2,2,0)))
				return 1;
		}
		if(arr[x-1][y-2]==24 && x>0 && y>1)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x-1,y-2,2,0)))
				return 1;
		}
		//Bishop or queen attacking king
		flag1=0;
		flag2=0;
		flag3=0;
		flag4=0;
		intermediate=0;	//0 for no piece in diagonal, 1 for piece other than bishop, 2 for bishop
		arr[wkingx][wkingy]=26;
		for(i=1;i<8;i++)
		{
			if((arr[x+i][y+i]==23 || arr[x+i][y+i]==21) && flag1==0)
			{
				if(checkflag==1)
					return 1;
				checkflag=1;
				flag1=2;
				if(king_under_attack(x+i,y+i,1,0))
					intermediate=1;
				for(j=1;j<i;j++)
				{
					if(king_under_attack(x+j,y+j,2,0))
					{
						intermediate=1;
						break;
					}
				}
				if(intermediate!=1)
				{
					arr[wkingx][wkingy]=10;
					return 1;
				}
				intermediate=0;
			}
			if(arr[x+i][y+i]!=0 && x+i<8 && y+i<8 && flag1==0)
			{
				flag1=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}		
			if((arr[x+i][y-i]==23 || arr[x+i][y-i]==21) && flag2==0)
			{
				flag2=2;
				if(checkflag==1)
				{
					arr[wkingx][wkingy]=10;
					return 1;
				}
				checkflag=1;
				if(king_under_attack(x+i,y-i,1,0))
					intermediate=1;
				for(j=1;j<i;j++)
				{
					if(king_under_attack(x+j,y-j,2,0))
					{
						intermediate=1;
						break;
					}
				}
				if(intermediate!=1)
				{
					arr[wkingx][wkingy]=10;
					return 1;
				}
				intermediate=0;
			}
			if(arr[x+i][y-i]!=0 && x+i<8 && y-i>=0 && flag2==0)
			{
				flag2=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x-i][y+i]==23 || arr[x-i][y+i]==21) && flag3==0)
			{
				flag3=2;
				if(checkflag==1)
				{
					arr[wkingx][wkingy]=10;
					return 1;
				}
				checkflag=1;
				if(king_under_attack(x-i,y+i,1,0))
					intermediate=1;
				for(j=1;j<i;j++)
				{
					if(king_under_attack(x-j,y+j,2,0))
					{
						intermediate=1;
						break;
					}
				}
				printboard();
				if(intermediate!=1)
				{
					arr[wkingx][wkingy]=10;
					return 1;
				}
				intermediate=0;
			}
			if(arr[x-i][y+i]!=0 && x-i>=0 && y+i<8 && flag3==0)
			{
				flag3=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x-i][y-i]==23 || arr[x-i][y-i]==21) && flag4==0)
			{
				flag4=2;
				if(checkflag==1)
				{
					arr[wkingx][wkingy]=10;
					return 1;
				}
				checkflag=1;
				if(king_under_attack(x-i,y-i,1,0))
					intermediate=1;
				for(j=1;j<i;j++)
				{
					if(king_under_attack(x-j,y-j,2,0))
					{
						intermediate=1;
						break;
					}
				}
				if(intermediate!=1)
				{
					arr[wkingx][wkingy]=10;
					return 1;
				}
				intermediate=0;
			}
			if(arr[x-i][y-i]!=0 && x-i>=0 && y-i>=0 && flag4==0)
			{
				flag4=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
		}
		//rook or queen attacking king
		flag=0;
		intermediate=0;
		for(i=1;x+i<8;i++)
		{
			if(arr[x+i][y]/10==1)
			{
				flag=1;
				break;
			}
			if(arr[x+i][y]/10==2)
			{
				if(arr[x+i][y]==22 || arr[x+i][y]==21)
				{
					flag=2;
					if(checkflag==1)
					{
						arr[wkingx][wkingy]=10;
						return 1;
					}
					checkflag=1;
					if(king_under_attack(x+i,y,1,0))
						intermediate=1;
					for(j=1;j<i;j++)
					{
						if(king_under_attack(x+j,y,2,0))
						{
							intermediate=1;
							break;
						}
					}
					if(intermediate!=1)
					{
						arr[wkingx][wkingy]=10;
						return 1;
					}
					intermediate=0;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;x-i>=0;i++)
		{
			if(arr[x-i][y]/10==1)
			{
				flag=1;
				break;
			}
			if(arr[x-i][y]/10==2)
			{
				if(arr[x-i][y]==22 || arr[x-i][y]==21)
				{
					flag=2;
					if(checkflag==1)
					{
						arr[wkingx][wkingy]=10;
						return 1;
					}
					checkflag=1;
					if(king_under_attack(x-i,y,1,0))
						intermediate=1;
					for(j=1;j<i;j++)
					{
						if(king_under_attack(x-j,y,2,0))
						{
							intermediate=1;
							break;
						}
					}
					if(intermediate!=1)
					{
						arr[wkingx][wkingy]=10;
						return 1;
					}
					intermediate=0;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;y+i<8;i++)
		{
			if(arr[x][y+i]/10==1)
			{
				flag=1;
				break;
			}
			if(arr[x][y+i]/10==2)
			{
				if(arr[x][y+i]==22 || arr[x][y+i]==21)
				{
					flag=2;
					if(checkflag==1)
					{
						arr[wkingx][wkingy]=10;
						return 1;
					}
					checkflag=1;
					if(king_under_attack(x,y+i,1,0))
						intermediate=1;
					for(j=1;j<i;j++)
					{
						if(king_under_attack(x,y+j,2,0))
						{
							intermediate=1;
							break;
						}
					}
					if(intermediate!=1)
					{
						arr[wkingx][wkingy]=10;
						return 1;
					}
					intermediate=0;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;y-i>=0;i++)
		{
			if(arr[x][y-i]/10==1)
			{
				flag=1;
				break;
			}
			if(arr[x][y-i]/10==2)
			{
				if(arr[x][y-i]==22 || arr[x][y-i]==21)
				{
					flag=2;
					if(checkflag==1)
					{
						arr[wkingx][wkingy]=10;
						return 1;
					}
					checkflag=1;
					if(king_under_attack(x,y-i,1,0))
						intermediate=1;
					for(j=1;j<i;j++)
					{
						if(king_under_attack(x,y-j,2,0))
						{
							intermediate=1;
							break;
						}
					}
					if(intermediate!=1)
					{
						arr[wkingx][wkingy]=10;
						return 1;
					}
					intermediate=0;
				}
				else
				{
					flag=1;
					break;
				}
			
			}
		}
		arr[wkingx][wkingy]=10;
		return 0;
	}
	else
	{
		//pawn attacking king
		if(arr[x-1][y+1]==15 && y<7)
		{
			checkflag=1;
			if(!(king_under_attack(x-1,y+1,2,0)))
				return 0;
		}
		if(arr[x-1][y-1]==15 && y>0)
		{
			checkflag=1;
			if(!(king_under_attack(x-1,y-1,2,0)))
				return 0;
		}
		//knight attacking king
		if(arr[x+2][y+1]==14 && x<6 && y<7)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x+2,y+1,1,0)))
				return 1;
		}
		if(arr[x+2][y-1]==14 && x<6 && y>0)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x+2,y-1,1,0)))
				return 1;
		}
		if(arr[x-2][y+1]==14 && x>1 && y<7)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x-2,y+1,1,0)))
				return 1;
		}
		if(arr[x-2][y-1]==14 && x>1 && y>0)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x-2,y-1,1,0)))
				return 1;
		}
		if(arr[x+1][y+2]==14 && x<7 && y<6)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x+1,y+2,1,0)))
				return 1;
		}
		if(arr[x+1][y-2]==14 && x<7 && y>1)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x+1,y-2,1,0)))
				return 1;
		}
		if(arr[x-1][y+2]==14 && x>0 && y<6)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x-1,y+2,1,0)))
				return 1;
		}
		if(arr[x-1][y-2]==14 && x>0 && y>1)
		{
			if(checkflag==1)
				return 1;
			checkflag=1;
			if(!(king_under_attack(x-1,y-2,1,0)))
				return 1;
		}
		//Bishop or queen attacking king
		flag1=0;
		flag2=0;
		flag3=0;
		flag4=0;
		intermediate=0;	//0 for no piece in diagonal, 1 for piece other than bishop, 2 for bishop
		arr[bkingx][bkingy]=16;
		for(i=1;i<8;i++)
		{
			if((arr[x+i][y+i]=13 || arr[x+i][y+i]==11) && flag1==0)
			{
				if(checkflag==1)
				{
					arr[bkingx][bkingy]=20;
					return 1;
				}
				checkflag=1;
				flag1=2;
				if(king_under_attack(x+i,y+i,2,0))
					intermediate=1;
				for(j=1;j<i;j++)
				{
					if(king_under_attack(x+j,y+j,1,0))
					{
						intermediate=1;
						break;
					}
				}
				if(intermediate!=1)
				{
					arr[bkingx][bkingy]=20;
					return 1;
				}
				intermediate=0;
			}
			if(arr[x+i][y+i]!=0 && x+i<8 && y+i<8 && flag1==0)
			{
				flag1=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}		
			if((arr[x+i][y-i]==13 || arr[x+i][y-i]==11) && flag2==0)
			{
				flag2=2;
				if(checkflag==1)
				{
					arr[bkingx][bkingy]=20;
					return 1;
				}
				checkflag=1;
				if(king_under_attack(x+i,y-i,2,0))
					intermediate=1;
				for(j=1;j<i;j++)
				{
					if(king_under_attack(x+j,y-j,1,0))
					{
						intermediate=1;
						break;
					}
				}
				if(intermediate!=1)
				{
					arr[bkingx][bkingy]=20;
					return 1;
				}
				intermediate=0;
			}
			if(arr[x+i][y-i]!=0 && x+i<8 && y-i>=0 && flag2==0)
			{
				flag2=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x-i][y+i]==13 || arr[x-i][y+i]==11) && flag3==0)
			{
				flag3=2;
				if(checkflag==1)
				{
					arr[bkingx][bkingy]=20;
					return 1;
				}
				checkflag=1;
				if(king_under_attack(x-i,y+i,2,0))
					intermediate=1;
				for(j=1;j<i;j++)
				{
					if(king_under_attack(x-j,y+j,1,0))
					{
						intermediate=1;
						break;
					}
				}
				if(intermediate!=1)
				{
					arr[bkingx][bkingy]=20;
					return 1;
				}
				intermediate=0;
			}
			if(arr[x-i][y+i]!=0 && x-i>=0 && y+i<8 && flag3==0)
			{
				flag3=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x-i][y-i]==13 || arr[x-i][y-i]==11) && flag4==0)
			{
				flag4=2;
				if(checkflag==1)
				{
					arr[bkingx][bkingy]=20;
					return 1;
				}
				checkflag=1;
				if(king_under_attack(x-i,y-i,2,0))
					intermediate=1;
				for(j=1;j<i;j++)
				{
					if(king_under_attack(x-j,y-j,1,0))
					{
						intermediate=1;
						break;
					}
				}
				if(intermediate!=1)
				{
					arr[bkingx][bkingy]=20;
					return 1;
				}
				intermediate=0;
			}
			if(arr[x-i][y-i]!=0 && x-i>=0 && y-i>=0 && flag4==0)
			{
				flag4=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
		}
		//rook or queen attacking king	
		flag=0;
		intermediate=0;
		for(i=1;x+i<8;i++)
		{
			if(arr[x+i][y]/10==2)
			{
				flag=1;
				break;
			}
			if(arr[x+i][y]/10==1)
			{
				if(arr[x+i][y]==12 || arr[x+i][y]==11)
				{
					flag=2;
					if(checkflag==1)
					{
						arr[bkingx][bkingy]=20;
						return 1;
					}
					checkflag=1;
					if(king_under_attack(x+i,y,2,0))
						intermediate=1;
					for(j=1;j<i;j++)
					{
						if(king_under_attack(x+j,y,1,0))
						{
							intermediate=1;
							break;
						}
					}
					if(intermediate!=1)
					{
						arr[bkingx][bkingy]=20;
						return 1;
					}
					intermediate=0;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;x-i>=0;i++)
		{
			if(arr[x-i][y]/10==2)
			{
				flag=1;
				break;
			}
			if(arr[x-i][y]/10==1)
			{
				if(arr[x-i][y]==12 || arr[x-i][y]==11)
				{
					flag=2;
					if(checkflag==1)
					{
						arr[bkingx][bkingy]=20;
						return 1;
					}
					checkflag=1;	
					if(king_under_attack(x-i,y,2,0))
						intermediate=1;
					for(j=1;j<i;j++)
					{
						if(king_under_attack(x-j,y,1,0))
						{
							intermediate=1;
							break;
						}
						arr[x-i][y]=temp;
					}
					if(intermediate!=1)
					{
						arr[bkingx][bkingy]=20;
						return 1;
					}
					intermediate=0;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;y+i<8;i++)
		{
			if(arr[x][y+i]/10==2)
			{
				flag=1;
				break;
			}
			if(arr[x][y+i]/10==1)
			{
				if(arr[x][y+i]==12 || arr[x][y+i]==11)
				{
					flag=2;
					if(checkflag==1)
					{
						arr[bkingx][bkingy]=20;
						return 1;
					}
					checkflag=1;
					if(king_under_attack(x,y+i,2,0))
						intermediate=1;
					for(j=1;j<i;j++)
					{
						if(king_under_attack(x,y+j,1,0))
						{
							intermediate=1;
							break;
						}
					}
					if(intermediate!=1)
					{
						arr[bkingx][bkingy]=20;
						return 1;
					}
					intermediate=0;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;y-i>=0;i++)
		{
			if(arr[x][y-i]/10==2)
			{
				flag=1;
				break;
			}
			if(arr[x][y-i]/10==1)
			{
				if(arr[x][y-i]==12 || arr[x][y-i]==11)
				{
					flag=2;
					if(checkflag==1)
					{
						arr[bkingx][bkingy]=20;
						return 1;
					}
					checkflag=1;
					if(king_under_attack(x,y-i,2,0))
						intermediate=1;
					for(j=1;j<i;j++)
					{
						if(king_under_attack(x,y-j,1,0))
						{
							intermediate=1;
							break;
						}
					}
					if(intermediate!=1)
					{
						arr[bkingx][bkingy]=20;
						return 1;
					}
					intermediate=0;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
	}
	return 0;
}

void printkilled(int x)
{
	if(x==21)
	{
		killedpieces++;
		printf("\nBlack queen killed\n\n");
		black.number[1]--;
	}
	else if(x==22)
	{
		killedpieces++;
		printf("\nBlack rook killed\n\n");
		black.number[2]--;
	}
	else if(x==23)
	{
		killedpieces++;
		printf("\nBlack bishop killed\n\n");
		black.number[3]--;
	}
	else if(x==24)
	{
		killedpieces++;
		printf("\nBlack knight killed\n\n");
		black.number[4]--;
	}
	else if(x==25)
	{
		killedpieces;
		printf("\nBlack pawn killed\n\n");
		black.number[5]--;
	}
	else if(x==11)
	{
		killedpieces++;
		printf("\nWhite queen killed\n\n");
		white.number[1]--;
	}
	else if(x==12)
	{
		killedpieces++;
		printf("\nWhite rook killed\n\n");
		white.number[2]--;
	}
	else if(x==13)
	{
		killedpieces++;
		printf("\nWhite bishop killed\n\n");
		white.number[3]--;
	}
	else if(x==14)
	{
		killedpieces++;
		printf("\nWhite knight killed\n\n");
		white.number[4]--;
	}
	else if(x==15)
	{
		killedpieces++;
		printf("\nWhite pawn killed\n\n");
		white.number[5]--;
	}
	return;
}
int king_under_attack(int x,int y,int team,int pr)
{
	if(team==1)
	{
		//pawn attacking king
		if((arr[x-1][y+1]==25 && y<7 && arr[x][y]!=0) || (arr[x-1][y]==25 && arr[x][y]==0 && x>0) || (arr[x-2][y]==25 && x==3 && arr[x][y]==0))
		{
			if(pr)
				printf("\nWhite King under attack from pawn at %c%c\n",x-1+'A',y+1+'1');
			return 1;
		}
		if(arr[x-1][y-1]==25 && y>0 && arr[x][y]!=0)
		{
			if(pr)
				printf("\nWhite King under attack from pawn at %c%c\n",x-1+'A',y-1+'1');
			return 1;
		}
		//knight attacking king
		if(arr[x+2][y+1]==24 && x<6 && y<7)
		{
			if(pr)
				printf("\nWhite King under attack from knight at %c%c\n",x+2+'A',y+1+'1');
			return 1;
		}
		if(arr[x+2][y-1]==24 && x<6 && y>0)
		{
			if(pr)
				printf("\nWhite King under attack from knight at %c%c\n",x+2+'A',y-1+'1');
			return 1;
		}
		if(arr[x-2][y+1]==24 && x>1 && y<7)
		{
			if(pr)
				printf("\nWhite King under attack from knight at %c%c\n",x-2+'A',y+1+'1');
			return 1;
		}
		if(arr[x-2][y-1]==24 && x>1 && y>0)
		{
			if(pr)
				printf("\nWhite King under attack from knight at %c%c\n",x-2+'A',y-1+'1');
			return 1;
		}
		if(arr[x+1][y+2]==24 && x<7 && y<6)
		{
			if(pr)
				printf("\nWhite King under attack from knight at %c%c\n",x+1+'A',y+2+'1');
			return 1;
		}
		if(arr[x+1][y-2]==24 && x<7 && y>1)
		{
			if(pr)
				printf("\nWhite King under attack from knight at %c%c\n",x+1+'A',y-2+'1');
			return 1;
		}
		if(arr[x-1][y+2]==24 && x>0 && y<6)
		{
			if(pr)
				printf("\nWhite King under attack from knight at %c%c\n",x-1+'A',y+2+'1');
			return 1;
		}
		if(arr[x-1][y-2]==24 && x>0 && y>1)
		{
			if(pr)
				printf("\nWhite King under attack from knight at %c%c\n",x-1+'A',y-2+'1');
			return 1;
		}
		//Bishop or queen attacking king
		int i,j;
		int flag1=0,flag2=0,flag3=0,flag4=0;	//0 for no piece in diagonal, 1 for piece other than bishop, 2 for bishop
		for(i=1;i<8;i++)
		{
			if((arr[x+i][y+i]==23 || arr[x+i][y+i]==21) && x+i<8 && y+i<8 && flag1==0)
			{
				flag1=2;
				if(arr[x+i][y+i]==23)
					if(pr)
						printf("\n\nWhite King under attack from bishop at %c%c\n",x+i+'A',y+i+'1');
				else
					if(pr)
						printf("\n\nWhite King under attack from queen at %c%c\n",x+i+'A',y+i+'1');
				return 1;
			}
			if(arr[x+i][y+i]!=0 && x+i<8 && y+i<8 && flag1==0)
			{
				flag1=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x+i][y-i]==23 || arr[x+i][y-i]==21) && x+i<8 && y-i>=0 && flag2==0)
			{
				flag2=2;
				if(arr[x+i][y-i]==23)
					if(pr)
						printf("\n\nWhite King under attack from bishop at %c%c\n",x+i+'A',y-i+'1');
				else
					if(pr)
						printf("\n\nWhite King under attack from queen at %c%c\n",x+i+'A',y-i+'1');
				return 1;
			}
			if(arr[x+i][y-i]!=0 && x+i<8 && y-i>=0 && flag2==0)
			{
				flag2=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x-i][y+i]==23 || arr[x-i][y+i]==21) && x-i>=0 && y+i<8 && flag3==0)
			{
				flag3=2;
				if(arr[x-i][y+i]==23)
					if(pr)
						printf("\n\nWhite King under attack from bishop at %c%c\n",x-i+'A',y+i+'1');
				else
					if(pr)
						printf("\n\nWhite King under attack from bishop at %c%c\n",x-i+'A',y+i+'1');
				return 1;
			}
			if(arr[x-i][y+i]!=0 && x-i>=0 && y+i<8 && flag3==0)
			{
				flag3=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x-i][y-i]==23 || arr[x-i][y-i]==21) && x-i>=0 && y-i>=0 && flag4==0)
			{
				flag4=2;
				if(arr[x-i][y-i]==23)
					if(pr)
						printf("\n\nWhite King under attack from bishop at %c%c\n",x-i+'A',y-i+'1');
				else
					if(pr)
						printf("\n\nWhite King under attack from queen at %c%c\n",x-i+'A',y-i+'1');
				return 1;
			}
			if(arr[x-i][y-i]!=0 && x-i>=0 && y-i>=0 && flag4==0)
			{
				flag4=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
		}
		if(flag1==2 || flag2==2 || flag3==2 || flag4==2)
			return 1;
		//rook or queen attacking king	
		int flag;
		flag=0;
		for(i=1;x+i<8;i++)
		{
			if(arr[x+i][y]/10==1)
			{
				flag=1;
				break;
			}
			if(arr[x+i][y]/10==2)
			{
				if(arr[x+i][y]==22 || arr[x+i][y]==21)
				{
					flag=2;
					if(arr[x+i][y]==22)
						if(pr)
							printf("\n\nWhite King under attack from rook at %c%c\n",x+i+'A',y+'1');
					else
						if(pr)
							printf("\n\nWhite King under attack from queen at %c%c\n",x+i+'A',y+'1');
					return 1;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;x-i>=0;i++)
		{
			if(arr[x-i][y]/10==1)
			{
				flag=1;
				break;
			}
			if(arr[x-i][y]/10==2)
			{
				if(arr[x-i][y]==22 || arr[x-i][y]==21)
				{
					flag=2;
					if(arr[x-i][y]==22)
						if(pr)
							printf("\n\nWhite King under attack from rook at %c%c\n",x-i+'A',y+'1');
					else
						if(pr)
							printf("\n\nWhite King under attack from queen at %c%c\n",x-i+'A',y+'1');
					return 1;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;y+i<8;i++)
		{
			if(arr[x][y+i]/10==1)
			{
				flag=1;
				break;
			}
			if(arr[x][y+i]/10==2)
			{
				if(arr[x][y+i]==22 || arr[x][y+i]==21)
				{
					flag=2;
					if(arr[x][y+i]==22)
						if(pr)
							printf("\n\nWhite King under attack from rook at %c%c\n",x+'A',y+i+'1');
					else
						if(pr)
							printf("\n\nWhite King under attack from queen at %c%c\n",x+'A',y+i+'1');
					return 1;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;y-i>=0;i++)
		{
			if(arr[x][y-i]/10==1)
			{
				flag=1;
				break;
			}
			if(arr[x][y-i]/10==2)
			{
				if(arr[x][y-i]==22 || arr[x][y-i]==21)
				{
					flag=2;
					if(arr[x][y-i]==22)
						if(pr)
							printf("\n\nWhite King under attack from rook at %c%c\n",x+'A',y-i+'1');
					else
						if(pr)
							printf("\n\nWhite King under attack from queen at %c%c\n",x+'A',y-i+'1');
					return 1;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		//king attacking king
		if(arr[x][y+1]==20)
		{
			if(pr)
				printf("\n\nWhite king under attack from black king at %c%c\n",x+'A',y+1+'1');
			return -1;
		}
		if(arr[x][y-1]==20)
		{
			if(pr)
				printf("\n\nWhite king under attack from black king at %c%c\n",x+'A',y-1+'1');
			return -1;
		}
		if(arr[x+1][y]==20)
		{
			if(pr)
				printf("\n\nWhite king under attack from black king at %c%c\n",x+1+'A',y+'1');
			return -1;
		}
		if(arr[x+1][y+1]==20)
		{
			if(pr)
				printf("\n\nWhite king under attack from black king at %c%c\n",x+1+'A',y+1+'1');
			return -1;
		}
		if(arr[x+1][y-1]==20)
		{
			if(pr)
				printf("\n\nWhite king under attack from black king at %c%c\n",x+1+'A',y-1+'1');
			return -1;
		}
		if(arr[x-1][y]==20)
		{
			if(pr)
				printf("\n\nWhite king under attack from black king at %c%c\n",x-1+'A',y+'1');
			return -1;
		}
		if(arr[x-1][y+1]==20)
		{
			if(pr)
				printf("\n\nWhite king under attack from black king at %c%c\n",x-1+'A',y+1+'1');
			return -1;
		}
		if(arr[x-1][y-1]==20)
		{
			if(pr)
				printf("\n\nWhite king under attack from black king at %c%c\n",x-1+'A',y-1+'1');
			return -1;
		}
	}
	else
	{
		//pawn attacking king
		if((arr[x+1][y+1]==15 && arr[x][y]!=0 && y<7) || (arr[x][y]==0 && arr[x+1][y]==15 && x<7) || (arr[x+2][y]==15 && x==4 && arr[x][y]==0))
		{
			if(pr)
				printf("\nBlack King under attack from pawn at %c%c\n",x-1+'A',y+1+'1');
			return 1;
		}
		if(arr[x+1][y-1]==15 && y>0 && arr[x][y]!=0)
		{
			if(pr)
				printf("\nBlack King under attack from pawn at %c%c\n",x-1+'A',y-1+'1');
			return 1;
		}
		//knight attacking king
		if(arr[x+2][y+1]==14 && x<6 && y<7)
		{
			if(pr)
				printf("\nBlack King under attack from knight at %c%c\n",x+2+'A',y+1+'1');
			return 1;
		}
		if(arr[x+2][y-1]==14 && x<6 && y>0)
		{
			if(pr)
				printf("\nBlack King under attack from knight at %c%c\n",x+2+'A',y-1+'1');
			return 1;
		}
		if(arr[x-2][y+1]==14 && x>1 && y<7)
		{
			if(pr)
				printf("\nBlack King under attack from knight at %c%c\n",x-2+'A',y+1+'1');
			return 1;
		}
		if(arr[x-2][y-1]==14 && x>1 && y>0)
		{
			if(pr)
				printf("\nBlack King under attack from knight at %c%c\n",x-2+'A',y-1+'1');
			return 1;
		}
		if(arr[x+1][y+2]==14 && x<7 && y<6)
		{
			if(pr)
				printf("\nBlack King under attack from knight at %c%c\n",x+1+'A',y+2+'1');
			return 1;
		}
		if(arr[x+1][y-2]==14 && x<7 && y>1)
		{
			if(pr)
				printf("\nBlack King under attack from knight at %c%c\n",x+1+'A',y-2+'1');
			return 1;
		}
		if(arr[x-1][y+2]==14 && x>0 && y<6)
		{
			if(pr)
				printf("\nBlack King under attack from knight at %c%c\n",x-1+'A',y+2+'1');
			return 1;
		}
		if(arr[x-1][y-2]==14 && x>0 && y>1)
		{
			if(pr)
				printf("\nBlack King under attack from knight at %c%c\n",x-1+'A',y-2+'1');
			return 1;
		}
		//Bishop or queen attacking king
		int i,j;
		int flag1=0,flag2=0,flag3=0,flag4=0;	//0 for no piece in diagonal, 1 for piece other than bishop, 2 for bishop
		for(i=1;i<8;i++)
		{
			if((arr[x+i][y+i]==13 || arr[x+i][y+i]==11) && x+i<8 && y+i<8 && flag1==0)
			{
				flag1=2;
				if(arr[x+i][y+i]==13 && pr)
					printf("\n\nBlack King under attack from bishop at %c%c\n",x+i+'A',y+i+'1');
				else
					if(pr)
						printf("\n\nBlack King under attack from queen at %c%c\n",x+i+'A',y+i+'1');
				return 1;
			}
			if(arr[x+i][y+i]!=0 && x+i<8 && y+i<8 && flag1==0)
			{
				flag1=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x+i][y-i]==13 || arr[x+i][y-i]==11) && x+i<8 && y-i>=0 && flag2==0)
			{
				flag2=2;
				if(arr[x+i][y-i]==13 && pr)
					printf("\n\nBlack King under attack from bishop at %c%c\n",x+i+'A',y-i+'1');
				else
					if(pr)
						printf("\n\nBlack King under attack from queen at %c%c\n",x+i+'A',y-i+'1');
				return 1;
			}
			if(arr[x+i][y-i]!=0 && x+i<8 && y-i>=0 && flag2==0)
			{
				flag2=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x-i][y+i]==13 || arr[x-i][y+i]==11) && x-i>=0 && y+i<8 && flag3==0)
			{
				flag3=2;
				if(arr[x-i][y+i]==13 && pr)
					printf("\n\nBlack King under attack from bishop at %c%c\n",x-i+'A',y+i+'1');
				else
					if(pr)
						printf("\n\nBlack King under attack from bishop at %c%c\n",x-i+'A',y+i+'1');
				return 1;
			}
			if(arr[x-i][y+i]!=0 && x-i>=0 && y+i<8 && flag3==0)
			{
				flag3=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
			if((arr[x-i][y-i]==13 || arr[x-i][y-i]==11) && x-i>=0 && y-i>=0 && flag4==0)
			{
				flag4=2;
				if(arr[x-i][y-i]==13 && pr)
					printf("\n\nBlack King under attack from bishop at %c%c\n",x-i+'A',y-i+'1');
				else
					if(pr)
						printf("\n\nBlack King under attack from queen at %c%c\n",x-i+'A',y-i+'1');
				return 1;
			}
			if(arr[x-i][y-i]!=0 && x-i>=0 && y-i>=0 && flag4==0)
			{
				flag4=1;
				if(flag1 && flag2 && flag3 && flag4)
					break;
			}
		}
		if(flag1==2 || flag2==2 || flag3==2 || flag4==2)
			return 1;
		//rook or queen attacking king	
		int flag;
		flag=0;
		for(i=1;x+i<8;i++)
		{
			if(arr[x+i][y]/10==2)
			{
				flag=1;
				break;
			}
			if(arr[x+i][y]/10==1)
			{
				if(arr[x+i][y]==12 || arr[x+i][y]==11)
				{
					flag=2;
					if(arr[x+i][y]==12 && pr)
						printf("\n\nBlack King under attack from rook at %c%c\n",x+i+'A',y+'1');
					else
						if(pr)
							printf("\n\nBlack King under attack from queen at %c%c\n",x+i+'A',y+'1');
					return 1;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;x-i>=0;i++)
		{
			if(arr[x-i][y]/10==2)
			{
				flag=1;
				break;
			}
			if(arr[x-i][y]/10==1)
			{
				if(arr[x-i][y]==12 || arr[x-i][y]==11)
				{
					flag=2;
					if(arr[x-i][y]==12 && pr)
						printf("\n\nBlack King under attack from rook at %c%c\n",x-i+'A',y+'1');
					else
						if(pr)
							printf("\n\nBlack King under attack from queen at %c%c\n",x-i+'A',y+'1');
					return 1;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;y+i<8;i++)
		{
			if(arr[x][y+i]/10==2)
			{
				flag=1;
				break;
			}
			if(arr[x][y+i]/10==1)
			{
				if(arr[x][y+i]==12 || arr[x][y+i]==11)
				{
					flag=2;
					if(arr[x][y+i]==12 && pr)
						printf("\n\nBlack King under attack from rook at %c%c\n",x+'A',y+i+'1');
					else
						if(pr)
							printf("\n\nBlack King under attack from queen at %c%c\n",x+'A',y+i+'1');
					return 1;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		flag=0;
		for(i=1;y-i>=0;i++)
		{
			if(arr[x][y-i]/10==2)
			{
				flag=1;
				break;
			}
			if(arr[x][y-i]/10==1)
			{
				if(arr[x][y-i]==12 || arr[x][y-i]==11)
				{
					flag=2;
					if(arr[x][y-i]==12 && pr)
						printf("\n\nBlack King under attack from rook at %c%c\n",x+'A',y-i+'1');
					else
						if(pr)
							printf("\n\nBlack King under attack from queen at %c%c\n",x+'A',y-i+'1');
					return 1;
				}
				else
				{
					flag=1;
					break;
				}
			}
		}
		//king attacking king
		if(arr[x][y+1]==10)
		{
			if(pr)
				printf("\n\nBlack king under attack from white king at %c%c\n",x+'A',y+1+'1');
			return -1;
		}
		if(arr[x][y-1]==10)
		{
			if(pr)
				printf("\n\nBlack king under attack from white king at %c%c\n",x+'A',y-1+'1');
			return -1;
		}
		if(arr[x+1][y]==10)
		{
			if(pr)
				printf("\n\nBlack king under attack from white king at %c%c\n",x+1+'A',y+'1');
			return -1;
		}
		if(arr[x+1][y+1]==10)
		{
			if(pr)
				printf("\n\nBlack king under attack from white king at %c%c\n",x+1+'A',y+1+'1');
			return -1;
		}
		if(arr[x+1][y-1]==10)
		{
			if(pr)
				printf("\n\nBlack king under attack from white king at %c%c\n",x+1+'A',y-1+'1');
			return -1;
		}
		if(arr[x-1][y]==10)
		{
			if(pr)
				printf("\n\nBlack king under attack from white king at %c%c\n",x-1+'A',y+'1');
			return -1;
		}
		if(arr[x-1][y+1]==10)
		{
			if(pr)
				printf("\n\nBlack king under attack from white king at %c%c\n",x-1+'A',y+1+'1');
			return -1;
		}
		if(arr[x-1][y-1]==10)
		{
			if(pr)
				printf("\n\nBlack king under attack from white king at %c%c\n",x-1+'A',y-1+'1');
			return -1;
		}
	}
	return 0;
}
int playermove(int team)
{
	int flag,x,i,j,kx,ky,flag1,flag2;
	char s1[3],s2[3];
	int y;
	y=getchar();
	while(!((y>='A' && y<='Z') || (y>='a' && y<='z') || (y>='0' && y<='9')))
		y=getchar();
	ungetc(y,stdin);
	scanf("%s",s1);
	y=getchar();
	while(!((y>='A' && y<='Z') || (y>='a' && y<='z') || (y>='0' && y<='9')))
		y=getchar();
	ungetc(y,stdin);
	scanf("%s",s2);
	x=getchar();
	int n1,n2;
	n1=strlen(s1);
	n2=strlen(s2);
	s1[0]=toupper(s1[0]);
	s2[0]=toupper(s2[0]);
	if(n1!=2 || n2!=2 || s1[0]-'A'>8 || s2[0]-'A'>8 || s1[0]-'A'<0 || s2[0]-'A'<0 || s1[1]-'0'>8 || s1[1]-'0'<0 || s2[1]-'0'>8 || s2[1]-'0'<0)
		return -1;
	if(strcmp(s1,s2)==0)
		return -1;
	int xold,xnew,yold,ynew;
	xold=s1[0]-'A';
	yold=s1[1]-'1';
	xnew=s2[0]-'A';
	ynew=s2[1]-'1';
	int temp;
//	printf("xold=%d yold=%d\nxnew=%d ynew=%d\n\n",xold,yold,xnew,ynew);
	if(arr[xold][yold]==0)
		return -1;
	int choice=0;
	if(team==1)
	{
		if(arr[xold][yold]/10==2 || arr[xnew][ynew]/10==1)
			return -1;
		switch(arr[xold][yold])
		{
			case 15:			//pawn's move
				if(yold==ynew)
				{
					if(xold==6)
					{
						if(xnew==5 && arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else if(xnew==4 && arr[xnew][ynew]==0 && arr[xnew-1][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
							return -1;
					}
					else
					{
						if(xnew==xold-1 && arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							if(xnew==0)
							{
								printf("\n\nWhat do you want to exchange the pawn with?\nEnter the relevant number.\n\n1 for queen\n2 for rook\n3 for bishop\n4 for knight");
								printf("\nEnter choice:");
								scanf("%d",&choice);
								while(!(choice>=1 && choice<=4))
								{
									printf("\nWrong choice. Enter again:");
									scanf("%d",&choice);
								}
								if(choice==1)
								{
									printf("\nYour pawn has been exchanged with a queen.\n");
									arr[xnew][ynew]=11;
								}
								else if(choice==2)
								{
									printf("\nYour pawn has been exchanged with a rook.\n");
									arr[xnew][ynew]=12;
								}
								else if(choice==3)
								{
									printf("\nYour pawn has been exchanged with a bishop.\n");
									arr[xnew][ynew]=13;
								}
								else if(choice==4)
								{
									printf("\nYour pawn has been exchanged with a knight.\n");
									arr[xnew][ynew]=14;
								}
								printboard();
							}
							return 0;
						}
						else
							return -1;
					}
				}
				else if((ynew==yold+1 || ynew==yold-1) && (xnew==xold-1) && (arr[xnew][ynew]/10==2))
				{
					temp=arr[xnew][ynew];
					//		printkilled(arr[xnew][ynew]);
					arr[xnew][ynew]=arr[xold][yold];
					arr[xold][yold]=0;
					if(king_under_attack(wkingx,wkingy,1,1))
					{
						printf("Cannot make move.\n");
						arr[xold][yold]=arr[xnew][ynew];
						arr[xnew][ynew]=temp;
						return -1;
					}
					printkilled(temp);
					if(xnew==0)
					{
						printf("\n\nWhat do you want to exchange the pawn with?\nEnter the relevant number.\n\n1 for queen\n2 for rook\n3 for bishop\n4 for knight");
						printf("\nEnter choice:");
						scanf("%d",&choice);
						while(!(choice>=1 && choice<=4))
						{
							printf("\nWrong choice. Enter again:");
							scanf("%d",&choice);
						}
						if(choice==1)
						{
							printf("\nYour pawn has been exchanged with a queen.\n");
							arr[xnew][ynew]=11;
						}
						else if(choice==2)
						{
							printf("\nYour pawn has been exchanged with a rook.\n");
							arr[xnew][ynew]=12;
						}
						else if(choice==3)
						{
							printf("\nYour pawn has been exchanged with a bishop.\n");
							arr[xnew][ynew]=13;
						}
						else if(choice==4)
						{
							printf("\nYour pawn has been exchanged with a knight.\n");
							arr[xnew][ynew]=14;
						}
						printboard();
					}
					return 0;
				}
				else
					return -1;
				break;
			case 14:			//knight's move
				if(xnew==xold+2)
				{
					if(ynew==yold+1 || ynew==yold-1)
					{
						if(arr[xnew][ynew]/10==1)
							return -1;
						if(arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
						{
							//printkilled(arr[xnew][ynew]);
							temp=arr[xnew][ynew];
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=temp;
								return -1;
							}
							printkilled(temp);
							return 0;
						}
					}
					else
						return -1;
				}
				else if(xnew==xold-2)
				{
					if(ynew==yold+1 || ynew==yold-1)
					{
						if(arr[xnew][ynew]/10==1)
							return -1;
						if(arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
						{
							//printkilled(arr[xnew][ynew]);
							temp=arr[xnew][ynew];
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=temp;
								return -1;
							}
							return 0;
						}
					}
					else
						return -1;
				}
				else if(ynew==yold+2)
				{
					if(xnew==xold+1 || xnew==xold-1)
					{
						if(arr[xnew][ynew]/10==1)
							return -1;
						if(arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
						{
							//printkilled(arr[xnew][ynew]);
							temp=arr[xnew][ynew];
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=temp;
								return -1;
							}
							printkilled(temp);
							return 0;
						}
					}
					else
						return -1;
				}
				else if(ynew==yold-2)
				{
					if(xnew==xold+1 || xnew==xold-1)
					{
						if(arr[xnew][ynew]/10==1)
							return -1;
						if(arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
						{
							//printkilled(arr[xnew][ynew]);
							temp=arr[xnew][ynew];
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(wkingx,wkingy,1,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=temp;
								return -1;
							}
							printkilled(temp);
							return 0;
						}
					}
					else
						return -1;
				}
				else
					return -1;
			case 13:			//bishop's move
				if(fabs(xold-xnew)!=fabs(yold-ynew))
					return -1;
				kx=xnew-xold;
				ky=ynew-yold;
				flag1=1;
				flag2=1;
				if(kx<0)
					flag1=-1;
				if(ky<0)
					flag2=-1;
				for(i=1;i<fabs(kx);i++)
				{
					if(arr[xold+(flag1*i)][yold+(flag2*i)]!=0)
						return -1;
				}
				if(arr[xnew][ynew]/10==1)
					return -1;
				if(arr[xnew][ynew]==0)
				{
					arr[xnew][ynew]=arr[xold][yold];
					arr[xold][yold]=0;
					if(king_under_attack(wkingx,wkingy,1,1))
					{
						printf("Cannot make move.\n");
						arr[xold][yold]=arr[xnew][ynew];
						arr[xnew][ynew]=0;
						return -1;
					}
					return 0;
				}
				else
				{
					//printkilled(arr[xnew][ynew]);
					temp=arr[xnew][ynew];
					arr[xnew][ynew]=arr[xold][yold];
					arr[xold][yold]=0;
					if(king_under_attack(wkingx,wkingy,1,1))
					{
						printf("Cannot make move.\n");
						arr[xold][yold]=arr[xnew][ynew];
						arr[xnew][ynew]=temp;
						return -1;
					}
					printkilled(temp);
					return 0;
				}
			case 12:			//rook's move
				if(!(xold==xnew || yold==ynew))
					return -1;
				if(xold==xnew)
				{
					if(ynew-yold>0)
						flag1=1;
					else
						flag1=-1;
					for(i=1;i<fabs(ynew-yold);i++)
					{
						if(arr[xold][yold+(flag1*i)]!=0 && fabs(yold-ynew)!=1)
							return -1;
					}
					if(arr[xnew][ynew]/10==1)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
				else
				{
					if(xnew-xold>0)
						flag1=1;
					else
						flag1=-1;
					for(i=1;i<fabs(xnew-xold);i++)
					{
						if(arr[xold+(flag1*i)][yold]!=0)
							return -1;
					}
					if(arr[xnew][ynew]/10==1)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
			case 11:				//queen's move
				if(xnew!=xold && ynew!=yold && fabs(xnew-xold)!=fabs(ynew-yold))
					return -1;
				if(xnew==xold)
				{
					if(ynew-yold>0)
						flag1=1;
					else
						flag1=-1;
					for(i=1;i<fabs(ynew-yold);i++)
					{
						if(arr[xold][yold+(flag1*i)]!=0)
							return -1;
					}
					if(arr[xnew][ynew]/10==1)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
				else if(ynew==yold)
				{
					if(xnew-xold>0)
						flag1=1;
					else
						flag1=-1;
					for(i=1;i<fabs(xnew-xold);i++)
					{
						if(arr[xold+(flag1*i)][yold]!=0)
							return -1;
					}
					if(arr[xnew][ynew]/10==1)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
				else
				{
					kx=xnew-xold;
					ky=ynew-yold;
					flag1=1;
					flag2=1;
					if(kx<0)
						flag1=-1;
					if(ky<0)
						flag2=-1;
					for(i=1;i<fabs(kx);i++)
					{
						if(arr[xold+(flag1*i)][yold+(flag2*i)]!=0)
							return -1;
					}
					if(arr[xnew][ynew]/10==1)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(wkingx,wkingy,1,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
			case 10:			//king's move
				if(fabs(xnew-xold)>1 || fabs(ynew-yold)>1)
					return -1;
				if(arr[xnew][ynew]/10==1)
					return -1;
				int ret=king_under_attack(xnew,ynew,1,0);	//some ambiguity in here. change in both b and w
				if(ret==0)
				{
					if(arr[xnew][ynew]/10==2)
						printkilled(arr[xnew][ynew]);
					arr[xnew][ynew]=arr[xold][yold];
					arr[xold][yold]=0;
					wkingx=xnew;
					wkingy=ynew;
					//printf("\nthe new position of the king is (%c,%c)\n",xnew+'A',ynew+'1');
					return 0;
				}
				else
					return -1;
			}
	}
	else
	{
		if(arr[xold][yold]/10==1 || arr[xnew][ynew]/10==2)
			return -1;
		switch(arr[xold][yold])
		{
			case 25:			//pawn's move
				if(yold==ynew)
				{
					if(xold==1)
					{
						if(xnew==2 && arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
														return 0;
						}
						else if(xnew==3 && arr[xnew][ynew]==0 && arr[xnew-1][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
							return -1;
					}
					else
					{
						if(xnew==xold+1 && arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							if(xnew==7)
							{
								printf("\n\nWhat do you want to exchange the pawn with?\nEnter the relevant number.\n\n1 for queen\n2 for rook\n3 for bishop\n4 for knight");
								printf("\nEnter choice:");
								scanf("%d",&choice);
								while(!(choice>=1 && choice<=4))
								{
									printf("\nWrong choice. Enter again:");
									scanf("%d",&choice);
								}
								if(choice==1)
								{
									printf("\nYour pawn has been exchanged with a queen.\n");
									arr[xnew][ynew]=21;
								}
								else if(choice==2)
								{
									printf("\nYour pawn has been exchanged with a rook.\n");
									arr[xnew][ynew]=22;
								}
								else if(choice==3)
								{
									printf("\nYour pawn has been exchanged with a bishop.\n");
									arr[xnew][ynew]=23;
								}
								else if(choice==4)
								{
									printf("\nYour pawn has been exchanged with a knight.\n");
									arr[xnew][ynew]=24;
								}
								printboard();
							}

							return 0;
						}
						else
							return -1;
					}
				}
				else if((ynew==yold+1 || ynew==yold-1) && (xnew==xold+1) && (arr[xnew][ynew]/10==1))
				{
					temp=arr[xnew][ynew];
					//		printkilled(arr[xnew][ynew]);
					arr[xnew][ynew]=arr[xold][yold];
					arr[xold][yold]=0;
					if(king_under_attack(bkingx,bkingy,2,1))
					{
						printf("Cannot make move.\n");
						arr[xold][yold]=arr[xnew][ynew];
						arr[xnew][ynew]=temp;
						return -1;
					}
					printkilled(temp);
					if(xnew==7)
					{
						printf("\n\nWhat do you want to exchange the pawn with?\nEnter the relevant number.\n\n1 for queen\n2 for rook\n3 for bishop\n4 for knight");
						printf("\nEnter choice:");
						scanf("%d",&choice);
						while(!(choice>=1 && choice<=4))
						{
							printf("\nWrong choice. Enter again:");
							scanf("%d",&choice);
						}
						if(choice==1)
						{
							printf("\nYour pawn has been exchanged with a queen.\n");
							arr[xnew][ynew]=21;
						}
						else if(choice==2)
						{
							printf("\nYour pawn has been exchanged with a rook.\n");
							arr[xnew][ynew]=22;
						}
						else if(choice==3)
						{
							printf("\nYour pawn has been exchanged with a bishop.\n");
							arr[xnew][ynew]=23;
						}
						else if(choice==4)
						{
							printf("\nYour pawn has been exchanged with a knight.\n");
							arr[xnew][ynew]=24;
						}
						printboard();
					}
					return 0;
				}
				else
					return -1;
				break;
			case 24:			//knight's move
				if(xnew==xold+2)
				{
					if(ynew==yold+1 || ynew==yold-1)
					{
						if(arr[xnew][ynew]/10==2)
							return -1;
						if(arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
						{
							//printkilled(arr[xnew][ynew]);
							temp=arr[xnew][ynew];
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=temp;
								return -1;
							}
							printkilled(temp);
							return 0;
						}
					}
					else
						return -1;
				}
				else if(xnew==xold-2)
				{
					if(ynew==yold+1 || ynew==yold-1)
					{
						if(arr[xnew][ynew]/10==2)
							return -1;
						if(arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
						{
							//printkilled(arr[xnew][ynew]);
							temp=arr[xnew][ynew];
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=temp;
								return -1;
							}
							return 0;
						}
					}
					else
						return -1;
				}
				else if(ynew==yold+2)
				{
					if(xnew==xold+1 || xnew==xold-1)
					{
						if(arr[xnew][ynew]/10==2)
							return -1;
						if(arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
						{
							//printkilled(arr[xnew][ynew]);
							temp=arr[xnew][ynew];
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=temp;
								return -1;
							}
							printkilled(temp);
							return 0;
						}
					}
					else
						return -1;
				}
				else if(ynew==yold-2)
				{
					if(xnew==xold+1 || xnew==xold-1)
					{
						if(arr[xnew][ynew]/10==2)
							return -1;
						if(arr[xnew][ynew]==0)
						{
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=0;
								return -1;
							}
							return 0;
						}
						else
						{
							//printkilled(arr[xnew][ynew]);
							temp=arr[xnew][ynew];
							arr[xnew][ynew]=arr[xold][yold];
							arr[xold][yold]=0;
							if(king_under_attack(bkingx,bkingy,2,1))
							{
								printf("Cannot make move.\n");
								arr[xold][yold]=arr[xnew][ynew];
								arr[xnew][ynew]=temp;
								return -1;
							}
							printkilled(temp);
							return 0;
						}
					}
					else
						return -1;
				}
				else
					return -1;
			case 23:			//bishop's move
				if(fabs(xold-xnew)!=fabs(yold-ynew))
					return -1;
				kx=xnew-xold;
				ky=ynew-yold;
				flag1=1;
				flag2=1;
				if(kx<0)
					flag1=-1;
				if(ky<0)
					flag2=-1;
				for(i=1;i<fabs(kx);i++)
				{
					if(arr[xold+(flag1*i)][yold+(flag2*i)]!=0)
						return -1;
				}
				if(arr[xnew][ynew]/10==2)
					return -1;
				if(arr[xnew][ynew]==0)
				{
					arr[xnew][ynew]=arr[xold][yold];
					arr[xold][yold]=0;
					if(king_under_attack(bkingx,bkingy,2,1))
					{
						printf("Cannot make move.\n");
						arr[xold][yold]=arr[xnew][ynew];
						arr[xnew][ynew]=0;
						return -1;
					}
					return 0;
				}
				else
				{
					//printkilled(arr[xnew][ynew]);
					temp=arr[xnew][ynew];
					arr[xnew][ynew]=arr[xold][yold];
					arr[xold][yold]=0;
					if(king_under_attack(bkingx,bkingy,2,1))
					{
						printf("Cannot make move.\n");
						arr[xold][yold]=arr[xnew][ynew];
						arr[xnew][ynew]=temp;
						return -1;
					}
					printkilled(temp);
					return 0;
				}
			case 22:			//rook's move
				if(!(xold==xnew || yold==ynew))
					return -1;
				if(xold==xnew)
				{
					if(ynew-yold>0)
						flag1=1;
					else
						flag1=-1;
					for(i=1;i<fabs(ynew-yold);i++)
					{
						if(arr[xold][yold+(flag1*i)]!=0 && fabs(yold-ynew)!=1)
							return -1;
					}
					if(arr[xnew][ynew]/10==2)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
				else
				{
					if(xnew-xold>0)
						flag1=1;
					else
						flag1=-1;
					for(i=1;i<fabs(xnew-xold);i++)
					{
						if(arr[xold+(flag1*i)][yold]!=0)
							return -1;
					}
					if(arr[xnew][ynew]/10==2)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
			case 21:				//queen's move
				if(xnew!=xold && ynew!=yold && fabs(xnew-xold)!=fabs(ynew-yold))
					return -1;
				if(xnew==xold)
				{
					if(ynew-yold>0)
						flag1=1;
					else
						flag1=-1;
					for(i=1;i<fabs(ynew-yold);i++)
					{
						if(arr[xold][yold+(flag1*i)]!=0)
							return -1;
					}
					if(arr[xnew][ynew]/10==2)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
				else if(ynew==yold)
				{
					if(xnew-xold>0)
						flag1=1;
					else
						flag1=-1;
					for(i=1;i<fabs(xnew-xold);i++)
					{
						if(arr[xold+(flag1*i)][yold]!=0)
							return -1;
					}
					if(arr[xnew][ynew]/10==2)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
				else
				{
					kx=xnew-xold;
					ky=ynew-yold;
					flag1=1;
					flag2=1;
					if(kx<0)
						flag1=-1;
					if(ky<0)
						flag2=-1;
					for(i=1;i<fabs(kx);i++)
					{
						if(arr[xold+(flag1*i)][yold+(flag2*i)]!=0)
							return -1;
					}
					if(arr[xnew][ynew]/10==2)
						return -1;
					if(arr[xnew][ynew]==0)
					{
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=0;
							return -1;
						}
						return 0;
					}
					else
					{
						//printkilled(arr[xnew][ynew]);
						temp=arr[xnew][ynew];
						arr[xnew][ynew]=arr[xold][yold];
						arr[xold][yold]=0;
						if(king_under_attack(bkingx,bkingy,2,1))
						{
							printf("Cannot make move.\n");
							arr[xold][yold]=arr[xnew][ynew];
							arr[xnew][ynew]=temp;
							return -1;
						}
						printkilled(temp);
						return 0;
					}
				}
			case 20:			//king's move
				if(fabs(xnew-xold)>1 || fabs(ynew-yold)>1)
					return -1;
				if(arr[xnew][ynew]/10==2)
					return -1;
				int ret=king_under_attack(xnew,ynew,2,0);
				if(ret==0)
				{
					if(arr[xnew][ynew]/10==2)
						printkilled(arr[xnew][ynew]);
					arr[xnew][ynew]=arr[xold][yold];
					arr[xold][yold]=0;
					wkingx=xnew;
					wkingy=ynew;
					//printf("\nthe new position of the king is (%c,%c)\n",xnew+'A',ynew+'1');
					return 0;
				}
				else
					return -1;
		}
	}
	return 0;
}
int main()
{
	int index=0;
	white.p[0].code=10;	//white king
	white.p[0].points=100;
	white.number[0]=1;
	black.p[0].code=20;	//black king
	black.p[0].points=100;
	black.number[0]=1;
	white.p[1].code=11;	//white queen
	white.p[1].points=10;
	white.number[1]=1;
	black.p[1].code=21;	//black queen
	black.p[1].points=10;
	black.number[1]=1;
	white.p[2].code=12;	//white rook
	white.p[2].points=5;
	white.number[2]=2;
	black.p[2].code=22;	//black rook
	black.p[2].points=5;
	black.number[2]=2;
	white.p[3].code=13;	//white bishop
	white.p[3].points=3;
	white.number[3]=2;
	black.p[3].code=23;	//black bishop
	black.p[3].points=3;
	black.number[3]=2;
	white.p[4].code=14;	//white knight
	white.p[4].points=3;
	white.number[4]=2;
	black.p[4].code=24;	//black knight
	black.p[4].points=3;
	black.number[4]=2;
	white.p[5].code=15;	//white pawn
	white.p[5].points=1;
	white.number[5]=8;
	black.p[5].code=25;	//black pawn
	black.p[5].points=1;
	black.number[5]=8;
	int k;
	arr[0][0]=22;
	arr[0][7]=22;
	arr[0][1]=24;
	arr[0][6]=24;
	arr[0][2]=23;
	arr[0][5]=23;
	arr[0][3]=21;
	arr[0][4]=20;
	for(k=0;k<8;k++)
	{
		arr[1][k]=25;
	}
	for(k=0;k<8;k++)
	{
		arr[6][k]=15;
	}
	arr[7][0]=12;
	arr[7][7]=12;
	arr[7][1]=14;
	arr[7][6]=14;
	arr[7][2]=13;
	arr[7][5]=13;
	arr[7][3]=11;
	arr[7][4]=10;
	printf("\n\n\t\tWELCOME TO SHATRANJ\n");
	printf("\t\t----------------------\n\n\n");
	printf("Player1\n");
	printf("-------\n\n");
	printf("Enter name: ");
	char name1[100],name2[100];
	scanf("%s",name1);
	printf("\n\nPlayer2");
	printf("\n-------\n");
	printf("\nEnter name:");
	scanf("%s",name2);
	int x=getchar();
	printf("\n\nHello %s and %s!\n\n",name1,name2);
	printf("\n\nThe rules of the game are very simple.\n\n1. There are 2 sides - black and white\n");
	printf("2. There are 16 pieces for each side - 1 king, 1 queen, 2 rooks, 2 bishops, 2 knights and 8 pawns");
	printf("\n3. The distribution of points is as follows:\n");
	printf("\tKing - 100\n\tQueen - 10\n\tRook - 5\n\tKnight - 3\n\tBishop - 3\n\tPawn - 1\n");
	printf("4. The directions in which the pieces can move is given as follows:\n");
	printf("\tKing - 1 step in any direction\n\tQueen - any number of steps horizontally, vertically or diagonally\n\tRook - any number of steps horizontally or vertically\n\tBishop - any number of steps diagonally\n\tKnight - 3 steps, 2 forward or backward and 1 to the right or left\n\tPawn - 1 step in forward direction. But can take 2 steps in the first move. Also, pawn can only kill a piece, which is diagonal forward direction by 1 step.\n\n");
	printf("5. The white pieces are denoted with a W before the piece name. For example, WBishop means a white bishop. Similarly for the black pieces.\n");
	printf("6. To make a move, type the square number on which the piece is now and the square number of the square, to which you want to move it. For example, to move a piece from B1 to D1, enter B1 D1 \n");
	printf("\nIf you have understood all the rules, please press enter to continue...");
	x=getchar();
	printf("\n\n");
	printf("This is what the chess board looks like initially...\n\n\n");
	printboard();
	int ret,y,flag,i,j;
	printf("Now, %s is on the white side and %s on the black side. So %s has to make the first move\n",name1,name2,name1);
	while(1)
	{
		flag=0;
		killedpieces=0;
		if(wkingy+1<8)
			if(!(king_under_attack(wkingx,wkingy+1,1,0)))
				flag=1;
		if(wkingy-1>=0)
			if(!(king_under_attack(wkingx,wkingy-1,1,0)))
				flag=1;
		if(wkingx>0)
		{
			if(!(king_under_attack(wkingx-1,wkingy,1,0)))
				flag=1;
			if(wkingy+1<8)
				if(!(king_under_attack(wkingx-1,wkingy+1,1,0)))
					flag=1;
			if(wkingy-1>=0)
				if(!(king_under_attack(wkingx-1,wkingy-1,1,0)))
					flag=1;
		}
		if(wkingx<7)
		{
			if(!(king_under_attack(wkingx+1,wkingy,1,0)))
				flag=1;
			if(wkingy+1<8)
				if(!(king_under_attack(wkingx+1,wkingy+1,1,0)))
					flag=1;
			if(wkingy-1>=0)
				if(!(king_under_attack(wkingx+1,wkingy-1,1,0)))
					flag=1;
		}
		//here flag=0 implies that king is under attack from all positions other than the current position.
		if(king_under_attack(wkingx,wkingy,1,0))
			flag=2;
		if(flag==0)	//if no other piece can move, it is a stalemate
		{
			for(i=0;i<8;i++)
			{
				for(j=0;j<8;j++)
				{
					if(arr[i][j]==15)
					{
						if((i-1>=0) && (arr[i-1][j]==0 || (arr[i-1][j+1]/10==2 && j+1<8) || (arr[i-1][j-1]/10==2 && j-1>=0)))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==14)
					{
						if((arr[i+1][j+2]/10!=1 && i+1<8 && j+2<8) || (arr[i+1][j-2]/10!=1 && i+1<8 && j-2>=0) || (arr[i-1][j+2]/10!=1 && i-1>=0 && j+2<8) || (arr[i-1][j-2]/10!=1 && i-1>=0 && j-2>=0) || (arr[i+2][j+1]/10!=1 && i+2<8 && j+1<8) || (arr[i+2][j-1]/10!=1 && i+2<8 && j-1>=0) || (arr[i-2][j+1]/10!=1 && i-2>=0 && j+1<8) || (arr[i-2][j-1]/10!=1 && i-2>=0 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==13 || arr[i][j]==11)
					{
						if((arr[i+1][j+1]/10!=1 && i+1<8 && j+1<8) || (arr[i+1][j-1]/10!=1 && i+1<8 && j-1>=0) || (arr[i-1][j+1]/10!=1 && i-1>=0 && j+1<8) || (arr[i-1][j-1]/10!=1 && i-1>=0 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==12 || arr[i][j]==11)
					{
						if((arr[i+1][j]/10!=1 && i+1<8) || (arr[i-1][j]/10!=1 && i-1>=0) || (arr[i][j+1]/10!=1 && j+1<8) || (arr[i][j-1]/10!=1 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
				}
				if(flag==1)
					break;
			}
		}
		if(flag==0)
		{
			printf("\n\nStalemate. Game is a draw.\n\n\n");
			return 0;
		}
		if(flag==2)	//left from here.. checkmate condition
		{
			if(final_checkmate(wkingx,wkingy,1))
			{
				printf("\n\nCheckmate! Black wins! Congratulations BLACK!\n\n\n");
				return 0;
			}
			else
				printf("match continues...\n\n\n");
		}
		flag=0;
		if(bkingy+1<8)
			if(!(king_under_attack(bkingx,bkingy+1,2,0)))
				flag=1;
		if(bkingy-1>=0)
			if(!(king_under_attack(bkingx,bkingy-1,2,0)))
				flag=1;
		if(bkingx>0)
		{
			if(!(king_under_attack(bkingx-1,bkingy,2,0)))
				flag=1;
			if(bkingy+1<8)
				if(!(king_under_attack(bkingx-1,bkingy+1,2,0)))
					flag=1;
			if(bkingy-1>=0)
				if(!(king_under_attack(bkingx-1,bkingy-1,2,0)))
					flag=1;
		}
		if(bkingx<7)
		{
			if(!(king_under_attack(bkingx+1,bkingy,2,0)))
				flag=1;
			if(bkingy+1<8)
				if(!(king_under_attack(bkingx+1,bkingy+1,2,0)))
					flag=1;
			if(bkingy-1>=0)
				if(!(king_under_attack(bkingx+1,bkingy-1,2,0)))
					flag=1;
		}
		//here flag=0 implies that king is under attack from all positions other than the current position.
		if(king_under_attack(bkingx,bkingy,2,0))
			flag=2;
		if(flag==0)	//if no other piece can move, it is a stalemate
		{
			for(i=0;i<8;i++)
			{
				for(j=0;j<8;j++)
				{
					if(arr[i][j]==25)
					{
						if((i-1>=0) && (arr[i-1][j]==0 || (arr[i-1][j+1]/10==1 && j+1<8) || (arr[i-1][j-1]/10==1 && j-1>=0)))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==24)
					{
						if((arr[i+1][j+2]/10!=2 && i+1<8 && j+2<8) || (arr[i+1][j-2]/10!=2 && i+1<8 && j-2>=0) || (arr[i-1][j+2]/10!=2 && i-1>=0 && j+2<8) || (arr[i-1][j-2]/10!=2 && i-1>=0 && j-2>=0) || (arr[i+2][j+1]/10!=2 && i+2<8 && j+1<8) || (arr[i+2][j-1]/10!=2 && i+2<8 && j-1>=0) || (arr[i-2][j+1]/10!=2 && i-2>=0 && j+1<8) || (arr[i-2][j-1]/10!=2 && i-2>=0 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==23 || arr[i][j]==21)
					{
						if((arr[i+1][j+1]/10!=2 && i+1<8 && j+1<8) || (arr[i+1][j-1]/10!=2 && i+1<8 && j-1>=0) || (arr[i-1][j+1]/10!=2 && i-1>=0 && j+1<8) || (arr[i-1][j-1]/10!=2 && i-1>=0 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==22 || arr[i][j]==21)
					{
						if((arr[i+1][j]/10!=2 && i+1<8) || (arr[i-1][j]/10!=2 && i-1>=0) || (arr[i][j+1]/10!=2 && j+1<8) || (arr[i][j-1]/10!=2 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
				}
				if(flag==1)
					break;
			}
		}
		if(flag==0)
		{
			printf("\n\nStalemate. Game is a draw.\n\n\n");
			return 0;
		}
		if(flag==2)	//left from here.. checkmate condition
		{
			if(final_checkmate(bkingx,bkingy,2))
			{
				printf("\n\nCheckmate! White wins! Congratulations WHITE!\n\n\n");
				return 0;
			}
		}
		printf("%s's move:",name1);
		ret=playermove(1);
		while(ret==-1)
		{
			printf("Invalid move. Enter again:");
			ret=playermove(1);
		}
		moves++;
		if(index==0)
			killed[index]=killedpieces;
		else
			killed[index]=killed[index-1]+killedpieces;
		printf("\n\n");
		printboard();
		printf("\n\n");
		if(moves>=50 && killed[index]==killed[index-50])
		{
			printf("\n\nThe match was a draw...\n\nThank you for playing!!! \n\n");
			break;
		}
		index++;
		killedpieces=0;
		flag=0;
		if(wkingy+1<8)
			if(!(king_under_attack(wkingx,wkingy+1,1,0)))
				flag=1;
		if(wkingy-1>=0)
			if(!(king_under_attack(wkingx,wkingy-1,1,0)))
				flag=1;
		if(wkingx>0)
		{
			if(!(king_under_attack(wkingx-1,wkingy,1,0)))
				flag=1;
			if(wkingy+1<8)
				if(!(king_under_attack(wkingx-1,wkingy+1,1,0)))
					flag=1;
			if(wkingy-1>=0)
				if(!(king_under_attack(wkingx-1,wkingy-1,1,0)))
					flag=1;
		}
		if(wkingx<7)
		{
			if(!(king_under_attack(wkingx+1,wkingy,1,0)))
				flag=1;
			if(wkingy+1<8)
				if(!(king_under_attack(wkingx+1,wkingy+1,1,0)))
					flag=1;
			if(wkingy-1>=0)
				if(!(king_under_attack(wkingx+1,wkingy-1,1,0)))
					flag=1;
		}
		//here flag=0 implies that king is under attack from all positions other than the current position.
		if(king_under_attack(wkingx,wkingy,1,0))
			flag=2;
		if(flag==0)	//if no other piece can move, it is a stalemate
		{
			for(i=0;i<8;i++)
			{
				for(j=0;j<8;j++)
				{
					if(arr[i][j]==15)
					{
						if((i-1>=0) && (arr[i-1][j]==0 || (arr[i-1][j+1]/10==2 && j+1<8) || (arr[i-1][j-1]/10==2 && j-1>=0)))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==14)
					{
						if((arr[i+1][j+2]/10!=1 && i+1<8 && j+2<8) || (arr[i+1][j-2]/10!=1 && i+1<8 && j-2>=0) || (arr[i-1][j+2]/10!=1 && i-1>=0 && j+2<8) || (arr[i-1][j-2]/10!=1 && i-1>=0 && j-2>=0) || (arr[i+2][j+1]/10!=1 && i+2<8 && j+1<8) || (arr[i+2][j-1]/10!=1 && i+2<8 && j-1>=0) || (arr[i-2][j+1]/10!=1 && i-2>=0 && j+1<8) || (arr[i-2][j-1]/10!=1 && i-2>=0 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==13 || arr[i][j]==11)
					{
						if((arr[i+1][j+1]/10!=1 && i+1<8 && j+1<8) || (arr[i+1][j-1]/10!=1 && i+1<8 && j-1>=0) || (arr[i-1][j+1]/10!=1 && i-1>=0 && j+1<8) || (arr[i-1][j-1]/10!=1 && i-1>=0 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==12 || arr[i][j]==11)
					{
						if((arr[i+1][j]/10!=1 && i+1<8) || (arr[i-1][j]/10!=1 && i-1>=0) || (arr[i][j+1]/10!=1 && j+1<8) || (arr[i][j-1]/10!=1 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
				}
				if(flag==1)
					break;
			}
		}
		if(flag==0)
		{
			printf("\n\nStalemate. Game is a draw.\n\n\n");
			return 0;
		}
		if(flag==2)	//left from here.. checkmate condition
		{
			if(final_checkmate(wkingx,wkingy,1))
			{
				printf("\n\nCheckmate! Black wins! Congratulations BLACK!\n\n\n");
				return 0;
			}
		}
		flag=0;
		if(bkingy+1<8)
			if(!(king_under_attack(bkingx,bkingy+1,2,0)))
				flag=1;
		if(bkingy-1>=0)
			if(!(king_under_attack(bkingx,bkingy-1,2,0)))
				flag=1;
		if(bkingx>0)
		{
			if(!(king_under_attack(bkingx-1,bkingy,2,0)))
				flag=1;
			if(bkingy+1<8)
				if(!(king_under_attack(bkingx-1,bkingy+1,2,0)))
					flag=1;
			if(bkingy-1>=0)
				if(!(king_under_attack(bkingx-1,bkingy-1,2,0)))
					flag=1;
		}
		if(bkingx<7)
		{
			if(!(king_under_attack(bkingx+1,bkingy,2,0)))
				flag=1;
			if(bkingy+1<8)
				if(!(king_under_attack(bkingx+1,bkingy+1,2,0)))
					flag=1;
			if(bkingy-1>=0)
				if(!(king_under_attack(bkingx+1,bkingy-1,2,0)))
					flag=1;
		}
		//here flag=0 implies that king is under attack from all positions other than the current position.
		if(king_under_attack(bkingx,bkingy,2,0))
			flag=2;
		if(flag==0)	//if no other piece can move, it is a stalemate
		{
			for(i=0;i<8;i++)
			{
				for(j=0;j<8;j++)
				{
					if(arr[i][j]==25)
					{
						if((i-1>=0) && (arr[i-1][j]==0 || (arr[i-1][j+1]/10==1 && j+1<8) || (arr[i-1][j-1]/10==1 && j-1>=0)))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==24)
					{
						if((arr[i+1][j+2]/10!=2 && i+1<8 && j+2<8) || (arr[i+1][j-2]/10!=2 && i+1<8 && j-2>=0) || (arr[i-1][j+2]/10!=2 && i-1>=0 && j+2<8) || (arr[i-1][j-2]/10!=2 && i-1>=0 && j-2>=0) || (arr[i+2][j+1]/10!=2 && i+2<8 && j+1<8) || (arr[i+2][j-1]/10!=2 && i+2<8 && j-1>=0) || (arr[i-2][j+1]/10!=2 && i-2>=0 && j+1<8) || (arr[i-2][j-1]/10!=2 && i-2>=0 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==23 || arr[i][j]==21)
					{
						if((arr[i+1][j+1]/10!=2 && i+1<8 && j+1<8) || (arr[i+1][j-1]/10!=2 && i+1<8 && j-1>=0) || (arr[i-1][j+1]/10!=2 && i-1>=0 && j+1<8) || (arr[i-1][j-1]/10!=2 && i-1>=0 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
					if(arr[i][j]==22 || arr[i][j]==21)
					{
						if((arr[i+1][j]/10!=2 && i+1<8) || (arr[i-1][j]/10!=2 && i-1>=0) || (arr[i][j+1]/10!=2 && j+1<8) || (arr[i][j-1]/10!=2 && j-1>=0))
						{
							flag=1;
							break;
						}
					}
				}
				if(flag==1)
					break;
			}
		}
		if(flag==0)
		{
			printf("\n\nStalemate. Game is a draw.\n\n\n");
			return 0;
		}
		if(flag==2)	
		{
			if(final_checkmate(bkingx,bkingy,2))
			{
				printf("\n\nCheckmate! White wins! Congratulations WHITE!\n\n\n");
				return 0;
			}
		}

		printf("\n\n%s's move:",name2);
		ret=playermove(2);
		while(ret==-1)
		{
			printf("Invalid move. Enter again:");
			ret=playermove(2);
		}
		moves++;
		killed[index]=killed[index-1]+killedpieces;
		printf("\n\n");
		printboard();
		printf("\n\n");
		if(moves>=50 && killed[index]==killed[index-50])
		{
			printf("\n\nThe match was a draw...\n\nThank you for playing!!! \n\n");
			break;
		}
		index++;
	}
	return 0;
}
