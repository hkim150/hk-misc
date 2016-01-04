#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAP_WIDTH = 25;
const int MAP_HEIGHT = 25;
const int MAX_BODY_LEN = MAP_WIDTH * MAP_HEIGHT;

enum{UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77};
enum{PAUSE = 112, ESC = 27};
enum{NOTHING = 0, FOOD, WALL, BODY};

struct bodyPos{
	int x;
	int y;
};

int object[MAP_HEIGHT][MAP_WIDTH] = {};

int head, tail;
int speed, dir, score;
int deleteMessageCount;

bodyPos BODY_POS[MAX_BODY_LEN];

void gotoxy(int, int, char*);
void init();
void drawWall();
bool checkNext();
void addHead();
void removeTail();
void pause();
void quit();
void checkMessage();
void invalid_key();
void invalid_turn();
void gameOver();
void makeFood();
void scoreUp();
void title();

int main(){
	bool startOver;
	int input;
	title();
		while(true){
		startOver = true;
		init();
		drawWall();
		makeFood();
		makeFood();
	
		while(startOver){
			if(_kbhit()){
				do{input = getch();}
				while(input == 224);
			
				switch(input){
				case UP:
				case DOWN:
				case LEFT:
				case RIGHT:	if((dir==UP&&input!=DOWN)||(dir==DOWN&&input!=UP)||(dir==LEFT&&input!=RIGHT)||(dir==RIGHT&&input!=LEFT)){dir = input;}
							else{invalid_turn();}	break;
				case PAUSE:	pause();				break;
				case ESC:	quit();					return 0;
				default:	invalid_key();			break;
				}
			}
			startOver = checkNext();
			checkMessage();
			Sleep(speed);
		}
	}
	return 0;
}


void gotoxy(int x, int y, char* str){
	COORD pos = {2*x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	cout<<str;
}

void init(){
	speed = 200;
	dir = RIGHT;
	score = 0;

	for(int x=0; x<MAP_WIDTH; x++){
		for(int y=0; y<MAP_HEIGHT; y++){
			if(x == 0 || x == MAP_WIDTH-1 || y == 0 || y == MAP_HEIGHT-1){
				object[y][x] = WALL;
			}
			else{object[y][x] = NOTHING;}
		}
	}

	head = 0;
	tail = 0;


	BODY_POS[head].x = MAP_WIDTH/2;
	BODY_POS[head].y = MAP_HEIGHT/2;

	gotoxy(BODY_POS[head].x, BODY_POS[head].y, "¡Ü");
	object[BODY_POS[head].y][BODY_POS[head].x] = BODY;

	gotoxy(0, MAP_HEIGHT, "Score: 0");
}

void drawWall(){
	for(int x=0; x<MAP_WIDTH; x++){
		for(int y=0; y<MAP_HEIGHT; y++){
			if(object[y][x] == WALL){
				gotoxy(x, y, "¡á");
			}
		}
	}
}

bool checkNext(){
	bool continueGame = true;
	int nextX, nextY;

	nextX = BODY_POS[head].x;
	nextY = BODY_POS[head].y;

	switch(dir){
	case UP:	nextY--;	break;
	case DOWN:	nextY++;	break;
	case LEFT:	nextX--;	break;
	case RIGHT:	nextX++;	break;
	}

	switch(object[nextY][nextX]){
	case NOTHING:	addHead();	removeTail();			break;
	case FOOD: 		addHead();	makeFood();	scoreUp();	break;
	case WALL:
	case BODY:		gameOver();	continueGame = false;	break;
	}
	return continueGame;
}

void addHead(){
	gotoxy(BODY_POS[head].x, BODY_POS[head].y, "¡Ü");

	BODY_POS[(head+1)%MAX_BODY_LEN] = BODY_POS[head];
	head = (head+1)%MAX_BODY_LEN;

	switch(dir){
	case UP:	BODY_POS[head].y--;	gotoxy(BODY_POS[head].x, BODY_POS[head].y, "¡ã");	break;
	case DOWN:	BODY_POS[head].y++;	gotoxy(BODY_POS[head].x, BODY_POS[head].y, "¡å");	break;
	case LEFT:	BODY_POS[head].x--;	gotoxy(BODY_POS[head].x, BODY_POS[head].y, "¢¸");	break;
	case RIGHT:	BODY_POS[head].x++;	gotoxy(BODY_POS[head].x, BODY_POS[head].y, "¢º");	break;
	}

	object[BODY_POS[head].y][BODY_POS[head].x] = BODY;
}

void removeTail(){
	gotoxy(BODY_POS[tail].x, BODY_POS[tail].y, "  ");
	object[BODY_POS[tail].y][BODY_POS[tail].x] = NOTHING;
	tail = (tail+1)%MAX_BODY_LEN;
}

void pause(){
	int input = 0;
	gotoxy(MAP_WIDTH+1, MAP_HEIGHT/2-1, "< Game Paused >");
	gotoxy(MAP_WIDTH+1, MAP_HEIGHT/2, "- press 'p' to resume -");
	
	while(true){
		input = getch();
		if(input == PAUSE){break;}
	}

	gotoxy(MAP_WIDTH+1, MAP_HEIGHT/2-1, "               ");
	gotoxy(MAP_WIDTH+1, MAP_HEIGHT/2, "                       ");
}

void quit(){
	system("cls");
	gotoxy(0, MAP_HEIGHT/2, "- Thank you for playing! -");
	Sleep(1200);
}

void invalid_key(){
	deleteMessageCount = 1;
	gotoxy(0, MAP_HEIGHT+1, "                           ");
	gotoxy(0, MAP_HEIGHT+1, "Invalid key input");
}

void invalid_turn(){
	deleteMessageCount = 1;
	gotoxy(0, MAP_HEIGHT+1, "                           ");
	gotoxy(0, MAP_HEIGHT+1, "You cannot turn 180 degrees");
}

void checkMessage(){
	if(deleteMessageCount > 0 && deleteMessageCount < 2000/speed){deleteMessageCount++;}
	else if(deleteMessageCount >= 2000/speed){
		gotoxy(0, MAP_HEIGHT+1, "                           ");
		deleteMessageCount = 0;
	}
}

void gameOver(){
	system("cls");
	gotoxy(1, 1, "< Game Over >");
	gotoxy(1, 2, "");	cout<<"Score: "<<score;
	gotoxy(1, 4, "- Press any key to play again -");
	while(!kbhit()){}
	fflush(stdin);
	system("cls");
}

void makeFood(){
	srand(time(NULL));
	int foodX, foodY;

	do{
		foodX = (rand()%(MAP_WIDTH-1))+1;
		foodY = (rand()%(MAP_HEIGHT-1))+1;
	}while(object[foodY][foodX] != NOTHING);

	gotoxy(foodX, foodY, "¡Ú");
	object[foodY][foodX] = FOOD;
}

void scoreUp(){
	score = score + 10;
	gotoxy(0, MAP_HEIGHT, "Score: ");
	cout<<score;

	if(score > 0 && (score%50) == 0){
		speed *= 0.9;
		deleteMessageCount = 1;
		gotoxy(0, MAP_HEIGHT+1, "                           ");
		gotoxy(0, MAP_HEIGHT+1, "* Speed Up! *");
	}
}

void title(){
	gotoxy(1, 1, "< SNAKE >");
	gotoxy(1, 3, "- Controls -");
	gotoxy(1, 4, "Up:¡è Down:¡é Left:¡ç Right:¡æ");
	gotoxy(1, 5, "Pause:'p'");
	gotoxy(1, 6, "Quit: 'esc'");
	gotoxy(1, 8, "- Press any key to start - ");

	while(!kbhit()){}
	system("cls");
	fflush(stdin);
}