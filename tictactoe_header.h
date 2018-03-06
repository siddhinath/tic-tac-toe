#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;

typedef struct TicTacToe
{
	int current_mov;//which user moved this state || index number
    int status;
	int tic[3][3];
	struct TicTacToe *node[9];
}tictactoe;

char name1[80];			//User Entry
char symbol_1;
char name2[80];
char symbol_2;

tictactoe *newTree()
{
	tictactoe *newNode;
	newNode=(tictactoe *)malloc(sizeof(tictactoe));
	newNode->current_mov=-1;
        newNode->status=0;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			newNode->tic[i][j]=0;
	for(int i=0;i<9;i++)
		newNode->node[i]=NULL;
	return newNode;
}

//Name: newTree
//Disc:	It creates new node of tic tac toe
//Date:	14/9/2017

void Display(tictactoe *tree,int turn)
{
	if(tree==NULL){
		printf("NULL\n");return ;}
	//system("clear");
	printf("\nPlayer1-[%c]\t[%s]\nPlayer2-[%c]\t[%s]\n\n",symbol_1,name1,symbol_2,name2);
	for(int k=0;k<13;k++)
		printf("-");
	printf("\n");
	for(int i=0;i<3;i++){
		printf("|");
		for(int j=0;j<3;j++){
			if(tree->tic[i][j]==1)
				printf(" %c |",symbol_1);
			else if(tree->tic[i][j]==2)
				printf(" %c |",symbol_2);
			else
				printf("   |");
		}
	printf("\n");
	for(int k=0;k<13;k++)
		printf("-");
	printf("\n");
	}
	if(turn>0)
		printf("\nPlayer %d turn- ",turn);
}
void ChooseSymbol(int user)
{
	char sym[3]={'O','X'};
	printf("\n1.	O\n2.	X\n");
	int choice;
	printf("Chhose symbol- ");
	scanf("%d",&choice);
	if(choice==1){
		symbol_1=sym[0];
		symbol_2=sym[1];
	}
	else
	{
		symbol_1=sym[1];
		symbol_2=sym[0];
	}

}

//Disc:	Check win or continue
//Return 1	Win Player1
//Return 2	Win Player2
//Return 4	Continue (rest of game)
//Return 3	End	Tie

int Check(tictactoe *t)
{
	int no;
	no=t->tic[0][0];
	if(t->tic[0][0]==no && t->tic[0][1]==no && t->tic[0][2]==no)
		return no;
	no=t->tic[1][0];
	if(t->tic[1][0]==no && t->tic[1][1]==no && t->tic[1][2]==no)
		return no;
	no=t->tic[2][0];
	if(t->tic[2][0]==no && t->tic[2][1]==no && t->tic[2][2]==no)
		return no;
	no=t->tic[0][0];
	if(t->tic[0][0]==no && t->tic[1][0]==no && t->tic[2][0]==no)
		return no;
	no=t->tic[0][1];
	if(t->tic[0][1]==no && t->tic[1][1]==no && t->tic[2][1]==no)
		return no;
	no=t->tic[0][2];
	if(t->tic[0][2]==no && t->tic[1][2]==no && t->tic[2][2]==no)
		return no;
	no=t->tic[0][0];
	if(t->tic[0][0]==no && t->tic[1][1]==no && t->tic[2][2]==no)
		return no;
	no=t->tic[1][1];
	if(t->tic[0][2]==no && t->tic[1][1]==no && t->tic[2][0]==no)
		return no;
	else
	{
		int flag=0;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(t->tic[i][j]==0)
					flag=1;
		if(flag==1)
			return 4;//continue to play
		else
			return 3;//tie game
	}
}

void DisplayWin(tictactoe *t,int id)
{
	system("clear");
	Display(t,-1);
	printf("\nPlayer %d Win",id);
	char ch[10];
	printf("\nYou wan to play again (y/n)- ");
	scanf("%s",ch);
	if(strcmp(ch,"n")==0)
		exit(0);
	free(t);
	t=newTree();
}


int convertMove(int i,int j)
{
	if(i==0 && j==0)
		return 1;
	else if(i==0 && j==1)
		return 2;
	else if(i==0 && j==2)
		return 3;
	else if(i==1 && j==0)
		return 4;
	else if(i==1 && j==1)
		return 5;
	else if(i==1 && j==2)
		return 6;
	else if(i==2 && j==0)
		return 7;
	else if(i==2 && j==1)
		return 8;
	else if(i==2 && j==2)
		return 9;
}
int addMove(tictactoe *t,int turn,int user)		//return 1 for laready one and 0 for update turn
{
	if(turn==1 && t->tic[0][0]==0){
		t->tic[0][0]=user;
		return 0;}
	else if(turn==2 && t->tic[0][1]==0){
		t->tic[0][1]=user;
		return 0;}
	else if(turn==3 && t->tic[0][2]==0){
		t->tic[0][2]=user;
		return 0;}
	else if(turn==4 && t->tic[1][0]==0){
		t->tic[1][0]=user;
		return 0;}
	else if(turn==5 && t->tic[1][1]==0){
		t->tic[1][1]=user;
		return 0;}
	else if(turn==6 && t->tic[1][2]==0){
		t->tic[1][2]=user;
		return 0;}
	else if(turn==7 && t->tic[2][0]==0){
		t->tic[2][0]=user;
		return 0;}
	else if(turn==8 && t->tic[2][1]==0){
		t->tic[2][1]=user;
		return 0;}
	else if(turn==9 && t->tic[2][2]==0){
		t->tic[2][2]=user;
		return 0;}
	else
		return 1;
}


//Disc:	use for user1 and user2 game only
void U1U2(tictactoe *t)
{
	Display(t,0);
	while(1)
	{
		int flag=Check(t);
		if(flag==1 || flag==2){
			DisplayWin(t,1);break;}
		if(flag==4){
			DisplayWin(t,4);break;}
		int turn;
		Display(t,1);
		scanf("%d",&turn);
		addMove(t,turn,1);

		flag=Check(t);
		if(flag==1 || flag==2){
			DisplayWin(t,1);break;}
		if(flag==4){
			DisplayWin(t,4);break;}
		Display(t,2);
		scanf("%d",&turn);
		addMove(t,turn,2);
	}
}
int getMax_arr_value_index(int *arr)
{
	int max=0,index=0;
	for(int i=0;i<9;i++)
		if(arr[i]>max){
			max=arr[i];index=i;}
	return index;
}
int getSum_arr(int *arr,int index)
{
	if(index==9)
		return 0;
	else
		return arr[index]+getSum_arr(arr,index+1);
}
int Height(tictactoe *t)
{
			if(t==NULL)
				return 0;
			else
			{
				int arr[9];
				for(int i=0;i<9;i++)
					arr[i]=1+Height(t->node[i]);
				return getMax_arr_value_index(arr);
			}
}

