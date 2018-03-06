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
                t->current_mov=turn;
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
int min_Value_Return(int *arr)
	{
		int min_=0;
		for(int i=0;i<9;i++)
		{
			if(arr[i]!=0){
				min_=arr[i];break;}
		}
		for(int i=0;i<9;i++)
		{
			if(arr[i]!=0 && arr[i] < min_)
			{
				min_=arr[i];
			}
		}
		return min_;
	}
int max_Value_Return(int *arr)
	{
		int max_=0;
		for(int i=0;i<9;i++)
		{
			if(arr[i]!=0){
				max_=arr[i];break;}
		}
	
		for(int i=0;i<9;i++)
		{
			if(arr[i]!=0 && arr[i] > max_)
			{
				max_=arr[i];
			}
		}
		return max_;
	}
int userwin=0,compwin=0;
int minmax(tictactoe *t)
{
	if(t->status==2)//COMPUTER
	{
		//printf("Computer Win\n");
		compwin++;
		return 10;
	}
	else if(t->status==1)
	{
		userwin++;
		//printf("USER Win\n");
		return -10;
	}
	else if(t->status==3)//status ==3 tie
	{
		printf("Tie\n");
		return 0;
	}

	if(t->current_mov==2)//choose max
	{
		int arr[9]={0,0,0,0,0,0,0,0,0};
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				int mov=convertMove(i,j);
				//printf("%d ",t->tic[i][j]);
				if(t->tic[i][j]==0 && t->node[mov-1]!=NULL)
				{
					int temp=minmax(t->node[mov-1]);
					arr[mov-1]=arr[mov-1]+temp;
				}
			}
		}
		printf("%d ",arr[1]);		
		int max_val=max_Value_Return(arr);
		return max_val;
	}
	else//choose min without zero
	{

		int arr[9]={0,0,0,0,0,0,0,0,0};
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				int mov=convertMove(i,j);
				if(t->tic[i][j]==0 && t->node[mov-1]!=NULL)
				{		
					int temp=minmax(t->node[mov-1]);
					arr[mov-1]=arr[mov-1]-temp;
				}
			}
		}
		printf("%d ",arr[1]);
		int min_val=min_Value_Return(arr);
		return min_val;
	}
}
int getWinMove(tictactoe *t)
{
	int max_index=-1,max_value=-10000;
	int arr[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			int mov=convertMove(i,j);
			if(t->tic[i][j]==0 && t->node[mov-1]!=NULL)
			{
				printf("Call mimax\n");
				int temp=minmax(t->node[mov-1]);
				arr[mov-1]=temp;
				if(temp>max_value)
				{
					max_value=temp;
					max_index=mov;
				}
			}
		}
	}
	printf("user-%d  comp-%d",userwin,compwin);
	compwin=0;userwin=0;
	printf("\ngetWinMove-[%d %d %d %d %d %d %d %d %d]\n",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],arr[7],arr[8]);
	return max_index-1;
}

void Play_AIUI(tictactoe *t,int turn)
{
		if(t->status==3 || t->status==USER || t->status==COMPUTER)
		{
			printf("\nWIN\n");
			return;
		}
		if(turn==USER)
		{
			printf("\nBefore Player Enter\n");
			Display(t,turn);
			printf("\n[%c %c turn-%d]\n",symbol_1,symbol_2,turn);
			int move;
			scanf("%d",&move);
			Play_AIUI(t->node[move-1],COMPUTER);
		}
		else
		{
			printf("\nComputer Before Play\n");
			Display(t,turn);
			int ind=getWinMove(t);
			printf("\nIndex Returned-%d\n",ind);
			Play_AIUI(t->node[ind],USER);
		}
}
void U1AI()
{	
	tictactoe *t=newTree();
	counter++;              //Create root node of tree
	t=genTree(t,t,9,2,0);
	printf("Total Count-[%d]",counter);

	//Current Game position
	Display(t,0);
	printf("[%d %d]",USER,COMPUTER);
	USER=1;
	COMPUTER=2;
	printf("[%d %d %c %c]",USER,COMPUTER,symbol_1,symbol_2);
	Play_AIUI(t,1);
}

void Start()
{
	tictactoe *t;
	printf("Size of tree node-%d",sizeof(struct TicTacToe));
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
				printf("\n\nPlayer 1=%c,Player 2=%c\n\n",symbol_1,symbol_2);
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
