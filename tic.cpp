#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include "tictactoe_header.h"
using namespace std;
static int counter=0;
int COMPUTER,USER;
tictactoe *copyData(tictactoe *old,tictactoe *t)
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			t->tic[i][j]=old->tic[i][j];
		}
	return t;
}

tictactoe *genTree(tictactoe *t,tictactoe *old,int times,int turn,int mov)
{
        if(times==0)
                return t;
        if(t==NULL)
                t=newTree();
        if(old!=NULL)
                t=copyData(old,t);
        if(mov>0)
        {
                int error=addMove(t,mov,turn);
				t->current_mov=turn;	//represent which user current move
                int st=Check(t);
                t->status=st;
        }
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        if(t->tic[i][j]==0)
                        {
                                counter++;
                                int m=convertMove(i,j);
                                if(turn==1)
                                        t->node[m-1]=genTree(t->node[m-1],t,times-1,2,m);
                                else
                                        t->node[m-1]=genTree(t->node[m-1],t,times-1,1,m);
                                        
                        }
                        }
                        }
        return t;
}
int MinMax(tictactoe *t,int turn)
{

}
tictactoe *getWinMove(tictactoe *t)
{
	int max_val=MinMax(t,COMPUTER);
}
void Play_AIUI(tictactoe *t,int turn)
{
		if(t->status==3 || t->status==USER || t->status==COMPUTER)
			return;
		if(turn==USER)
		{
			Display(t,turn);
			int move;
			scanf("%d",&move);
			Play_AIUI(t->node[move-1],COMPUTER);
		}
		else
		{
			Display(t,turn);
			t=getWinMove(t);
			Play_AIUI(t,USER);
		}
}
void U1AI()
{	
	tictactoe *t=newTree();
	counter++;              //Create root node of tree
	t=genTree(t,t,9,1,0);
	printf("Total Count-[%d]",counter);
	//Current Game position
	Display(t,0);
	//printf("[%d %d]",USER,COMPUTER);
	USER=1;
	COMPUTER=2;
	//printf("[%d %d]",USER,COMPUTER);
	//Play_AIUI(t,1);
}

void Start()
{
	tictactoe *t;
	printf("Size of tree-%d",sizeof(struct TicTacToe));
	t=newTree();
	
	do{
		//system("clear");
		printf("\n1.User1 with User2\n2.User with AI\n3.Replay\n4.Exit ");
		int choice;
		scanf("%d",&choice);
		switch(choice)
		{
			case 1://User1 with User2
				printf("\nEnter user1 name-");
				scanf("%s",name1);
				ChooseSymbol(1);
				printf("\nEnter user2 name-");
				scanf("%s",name2);
				U1U2(t);	
				break;
			case 2:
				printf("\nEnter user1 name-");
				scanf("%s",name1);
				//ChooseSymbol(1);
				symbol_1='X';
				symbol_2='O';
				strcpy(name2,"Computer");
				U1AI();
				break;
			case 3:
				system("clear");
				free(t);
				t=newTree();								
				break;
			default:
				printf("\nThank You for Played\n");
				exit(0);
				
		}
	}while(1);
}


int main()
{
	Start();
	return 0;
}
