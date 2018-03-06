#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include "tictactoe_header.h"
using namespace std;
static int counter=0;

tictactoe *copyData(tictactoe *old,tictactoe *t)
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
			t->tic[i][j]=old->tic[i][j];
		}
	return t;
}
void D(tictactoe *t)
{
	printf("\n");
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("%d ",t->tic[i][j]);}printf("\n");}

}
tictactoe *genTree(tictactoe *t,tictactoe *old,int times,int turn)
{
	if(times==0)
		return t;
	if(t==NULL)
	{
		t=newTree();
	}
	if(old!=NULL)
	{
		t=copyData(old,t);
	}
	//Display(t,-1);
	int i=0;
	//printf("(%d) ",counter);
	for(int k=0;k<9;k++){
		t->node[k]=genTree(t->node[k],t,times-1,turn);
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(t->tic[i][j]==0)
			{
				int mov=convertMove(i,j);
				int temp=addMove(t,mov,turn);
				//printf("\n[%d]-[%d]\n",mov,t->tic[i][j]);
				if(turn==0){
					t->node[mov-1]=genTree(t->node[mov-1],t,times-1,2);
					}
				if(turn==1){
						t->node[mov-1]=genTree(t->node[mov-1],t,times-1,2);
					}
				else{
						t->node[mov-1]=genTree(t->node[mov-1],t,times-1,1);
					}
				counter++;
	//printf("(%d) ",counter);
			}
		}
	}
	return t;
	}
	return t;
}

void U1AI()
{
	//Display(t,-1);
	tictactoe *t=newTree();
	t=genTree(t,t,9,0);
	printf("Total Count-[%d]",counter);
	Display(t,-1);
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
				/*printf("\nEnter user1 name-");
				scanf("%s",name1);
				ChooseSymbol(1);
				strcpy(name2,"Computer");*/
				ChooseSymbol(1);
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
