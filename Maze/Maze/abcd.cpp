#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int input;
int nowX, nowY;
int count = 0;

typedef struct location{
	int x;
	int y;
}LOCATION;

LOCATION loc[1000] = {};
LOCATION locShort[1000] = {};

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

void arrayInit(void);
void draw(void);
void move(int x);
int check(int x, int y);
void end(void);
void record(void);
void replay(LOCATION*, int a);
void shortest(void);

void main(void){
	arrayInit();
	record();

	do{
		if(input != 224)
			draw();
		input = getch();
		move(input);
	}while(input != '0');

	system("pause");
}

void arrayInit(void){
	maze[1][0] = 2;
	maze[17][7] = 3;
	nowX = 17;
	nowY = 7;
}

void draw(void){
	system("cls");
	for(int i=0;i<19;i++){
		for(int j=0;j<19;j++){
			if(maze[i][j] == 0)
				printf("  ");
			else if(maze[i][j] == 1)
				printf("##");
			else if(maze[i][j] == 2)
				printf("@ ");
			else
				printf("! ");
		}
		printf("\n");
	}
}

void move(int x){
	switch(x){
	case 72:
		if(check(nowX-1,nowY) == 1){
			maze[nowX][nowY] = 0;
			nowX -= 1;
			maze[nowX][nowY] = 3;
			record();
		}
		else if(check(nowX-1,nowY) == 2){
			maze[nowX][nowY] = 0;
			nowX -= 1;
			maze[nowX][nowY] = 3;
			record();
			end();
		}
		break;

	case 75:
		if(check(nowX,nowY-1) == 1){
			maze[nowX][nowY] = 0;
			nowY -= 1;
			maze[nowX][nowY] = 3;
			record();
		}
		else if(check(nowX,nowY-1) ==2){
			maze[nowX][nowY] = 0;
			nowY -= 1;
			maze[nowX][nowY] = 3;
			record();
			end();
		}
		break;

	case 77:
		if(check(nowX,nowY+1) == 1){
			maze[nowX][nowY] = 0;
			nowY += 1;
			maze[nowX][nowY] = 3;
			record();
		}
		else if(check(nowX,nowY+1) == 2){
			maze[nowX][nowY] = 0;
			nowY += 1;
			maze[nowX][nowY] = 3;
			record();
			end();
		}
		break;

	case 80:
		if(check(nowX+1,nowY) == 1){
			maze[nowX][nowY] = 0;
			nowX += 1;
			maze[nowX][nowY] = 3;
			record();
		}
		else if(check(nowX+1,nowY) == 2){
			maze[nowX][nowY] = 0;
			nowX += 1;
			maze[nowX][nowY] = 3;
			record();
			end();
		}
		break;

	default:
		break;
	}
}

int check(int x, int y){
	int num;

	if(maze[x][y] == 0)
		num = 1;
	else if(maze[x][y] == 2)
		num = 2;
	else
		num = 0;

	return num;
}

void end(void){
	draw();
	char choice;
	while(true){
		printf("1.리플레이 보기 2.최단거리 보기 3.다시 플레이 4.종료 \n");
		choice = getch();
		switch(choice){
		case '1':
			replay(loc,count);
			break;
		case '2':
			shortest();
			break;
		case '3':
			arrayInit();
			return;
		case '4':
			input = '0';
			return;
		}
	}
}

void record(void){
	loc[count].x = nowX;
	loc[count].y = nowY;
	count++;
}

void replay(LOCATION* loca, int a){
	arrayInit();
	draw();
	for(int i=1;i<a;i++){
		maze[loca[i-1].x][loca[i-1].y] = 0;
		maze[loca[i].x][loca[i].y] = 3;
		draw();
	}
}

void shortest(void){
	int countShort = 0;
	for(int i=0;i<count;i++){
		for(int j=0;j<countShort;j++){
			if(loc[i].x == locShort[j].x && loc[i].y == locShort[j].y){
				countShort = j;
				break;
			}
		}
		locShort[countShort] = loc[i];
		countShort++;
	}
	replay(locShort,countShort);
}