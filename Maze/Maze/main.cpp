#include <iostream>
#include <conio.h>
using namespace std;

enum{NOTHING = 0, WALL, PERSON, EXIT};
enum{UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77};
enum{WATCH_REPLAY = '1', WATCH_SHORT = '2', PLAY_AGAIN = '3', QUIT_GAME = '4'};

int nowX, nowY;
int count = 0;
int shortCount = 0;
int moveCount = 0;

typedef struct position{
	int x;
	int y;
} POS;

POS route[500]	= {};
POS shortRoute[500] = {};

int maze[19][19] = {
 { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
 { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
 { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
 { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
 { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1 },
 { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
 { 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
 { 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 },
 { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
 { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } 
};

void init(bool);
void draw();
void move(int);
bool check(int);
bool finish();
void record();
void showReplay(POS*,int);
void shortestRoute();

int main(){
	int input;
	bool flag = true;

	init(true);
	record();
	draw();

	do{
		input = getch();
		if(input == UP || input == DOWN || input == LEFT || input == RIGHT){flag = check(input);}
	}while(flag);

	return 0;
}

void init(bool reset_count){
	moveCount = 0;
	nowX = 17;
	nowY = 17;
	maze[1][0] = EXIT;
	if(reset_count){
		count = 0;
		shortCount = 0;
		maze[nowX][nowY] = PERSON;
	}
}

void draw(){
	system("cls");
	for(int i=0; i<19; i++){
		for(int j=0; j<19; j++){
			switch(maze[i][j]){
			case NOTHING:	cout<<"  ";	break;
			case WALL:		cout<<"¡á";	break;
			case PERSON:	cout<<"¡Ï";	break;
			case EXIT:		cout<<"¡Ú";	break;
			default:		cout<<"??";	break;
			}
		}
		cout<<endl;
	}
	cout<<moveCount<<" move";
	if(moveCount > 1){cout<<'s';}
	cout<<endl;
}

bool check(int input){
	int obj;
	bool flag = true;

	switch(input){
	case UP:	obj = maze[nowX-1][nowY];	break;
	case DOWN:	obj = maze[nowX+1][nowY];	break;
	case LEFT:	obj = maze[nowX][nowY-1];	break;
	case RIGHT:	obj = maze[nowX][nowY+1];	break;
	}

	switch(obj){
	case NOTHING:	move(input);						break;
	case EXIT:		move(input);	flag = finish();	break;
	}
	return flag;
}

bool finish(){
	int choice;
	bool flag = true;
	bool flag_Main = true;
	cout<<"Good Job!"<<endl<<endl;

	while(flag){
		cout<<"1. Watch replay"<<endl;
		cout<<"2. Watch shortest route"<<endl;
		cout<<"3. Play again"<<endl;
		cout<<"4. Quit"<<endl;
	
		do{
			choice = getch();
		}while(choice != WATCH_REPLAY && choice != WATCH_SHORT && choice != PLAY_AGAIN && choice != QUIT_GAME);
	
		switch(choice){
		case WATCH_REPLAY:	showReplay(route, count);						break;
		case WATCH_SHORT:	shortestRoute();
							showReplay(shortRoute, shortCount);				break;
		case PLAY_AGAIN:	init(true);	record();	draw();	flag = false;	break;
		case QUIT_GAME:		flag_Main = false;	flag = false;				break;
		}
	}
	return flag_Main;
}

void move(int input){
	maze[nowX][nowY] = NOTHING;

	switch(input){
	case UP:	maze[--nowX][nowY] = PERSON;	break;
	case DOWN:	maze[++nowX][nowY] = PERSON;	break;
	case LEFT:	maze[nowX][--nowY] = PERSON;	break;
	case RIGHT:	maze[nowX][++nowY] = PERSON;	break;
	}
	++moveCount;
	record();
	draw();
}

void record(){
	route[count].x = nowX;
	route[count].y = nowY;
	count++;
}

void showReplay(POS* route_, int count_){
	init(false);
	draw();
	for(int i=0; i<count_; i++){
		maze[route_[i].x][route_[i].y] = PERSON;
		if(i >= 1){maze[route_[i-1].x][route_[i-1].y] = NOTHING;}
		draw();
		++moveCount;
	}
}

void shortestRoute(){
	for(int i=0; i<count; i++){
		for(int j=0; j<shortCount; j++){
			if(shortRoute[j].x == route[i].x && shortRoute[j].y == route[i].y){
					shortCount = j;
					cout<<"shortCount: "<<shortCount<<endl;
					break;
			}
		}
		shortRoute[shortCount++] = route[i];
	}
}