// 승리조건, 금수처리, 타이머 기능 보완 예정

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

enum color4 {
	Black = 0,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	Lgray,
	Dgray,
	Lblue,
	Lgreen,
	Lcyan,
	Lred,
	Lmagenta,
	Yellow,
	White
};	//색깔표

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32
#define ESC 27 //키 값 설정

void show_omok();	//오목판 출력 함수
void move_omok();	//오목돌 둘 위치 이동 함수
void go_omok(int x, int y);	//오목돌 두기 함수
void timer_check();	// 타이머 시간 체크
int wincheck(int x, int y, int k);	//오목 체크 함수
int jangmokcheck(int x, int y);	//6목 체크 함수
void threecheck(int x, int y);	//쌍삼 체크 함수
void fourcheck(int x, int y);	//쌍사 체크 함수
int closedfour(int x, int y);	//닫힌 4체크 함수
void ending(int t);	//엔딩 화면 출력 함수
void gotoxy(int x, int y);	//커서 이동을 위해 필요한 함수
void setcursortype(CURSOR_TYPE c);	//커서 타입 설정 함수
void pointermove(int x, int y);	//포인터 이동 처리 함수
void SetColor(int txt, int bg);	//글자 색깔 배경색 설정 함수
void draw_info();	//게임 정보 출력 함수

int omok[15][15] = {
 { 51, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 52 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 9 },
 { 53, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 54 }
};	//배열 전역변수 선언

int x, y;	// 오목돌 위치 변수
int turn = 1;	//순서 변경을 위한 전역변수 선언
int sequence = 0;	//sequence번째 차례
int three_count = 0;	//3갯수
int four_count = 0;	//4갯수
clock_t start, end;
double limit_time;	// 제한시간 변수

int main()
{
	setcursortype(NOCURSOR);
	system("mode con cols=65 lines=28");	//창 크기 설정
	show_omok();
	draw_info();
	move_omok();
}

void timer_check() {
	end = clock();
	gotoxy(36, 2);
	SetColor(White, Black);
	limit_time = 30 - (end - start) / CLOCKS_PER_SEC;
	if (limit_time <= 10 && limit_time > 0)
	{
		SetColor(Red, Black);
		printf("남은 시간 : 0%f초", 30 - (double)(end - start) / CLOCKS_PER_SEC);
	}
	else if (limit_time <= 0)
	{
		gotoxy(33, 8);
		SetColor(White, Black);
		printf("시간 초과로 차례가 넘어갑니다.");	//메세지 출력
		Sleep(1000);
		gotoxy(32, 8);
		printf("                              ");	//메세지 제거
		start = clock();
		if (turn == 1)
		{
			turn--;
			gotoxy(42, 8);
			printf("현재 턴 : ●");
		}
		else
		{
			turn++;
			gotoxy(42, 8);
			printf("현재 턴 : ○");
		}	//턴 변환
	}
	else
		printf("남은 시간 : %f초", 30 - (double)(end - start) / CLOCKS_PER_SEC);
	gotoxy(x, y);
}

void draw_info()
{
	SetColor(White, Black);
	gotoxy(1, 17);
	printf("게임방법");
	gotoxy(1, 19);
	printf("화살표키로 이동");
	gotoxy(1, 21);
	printf("스페이스바를 누를시 오목 돌이 놓아짐.");
	gotoxy(1, 23);
	printf("ESC를 누를 시 종료");
	gotoxy(1, 25);
	printf("게임룰은 렌주룰이 기반입니다.");
}

void show_omok()
{
	SetColor(Black, Brown);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (omok[i][j] == 5)
				printf("╋ ");
			else if (omok[i][j] == 51)
				printf("┏ ");
			else if (omok[i][j] == 52)
				printf("┓ ");
			else if (omok[i][j] == 53)
				printf("┗ ");
			else if (omok[i][j] == 54)
				printf("┛ ");
			else if (omok[i][j] == 6)
				printf("┳ ");
			else if (omok[i][j] == 7)
				printf("┣ ");
			else if (omok[i][j] == 8)
				printf("┻ ");
			else if (omok[i][j] == 9)
				printf("┫ ");
			else
				printf(" ");
		}
		printf("\n");
	}
}

void move_omok()
{	
	char shift;
	x = 14, y = 7;
	double limit_time;
	gotoxy(42, 8);
	SetColor(White, Black);
	printf("현재 턴 : ○");
	gotoxy(x, y);
	SetColor(Black, Brown);
	printf("●");

	start = clock();

	while (1)
	{
		timer_check();
		//fflush(stdin);
		shift = _getch();

		if (shift != NULL)
		{
		}

		switch (shift)
		{
		case UP:
			if (y > 0 && x <= 28)
			{
				pointermove(x, y);
				y--;
				gotoxy(x, y);
				if (turn == 1)
				{
					SetColor(Black, Brown);
					printf("●");
					gotoxy(x, y);
				}
				else
				{
					SetColor(White, Brown);
					printf("●");
					gotoxy(x, y);
				}
			}
			break;
		case DOWN:
			if (y < 14 && x <= 28)
			{
				pointermove(x, y);
				y++;
				gotoxy(x, y);
				if (turn == 1)
				{
					SetColor(Black, Brown);
					printf("●");
					gotoxy(x, y);
				}
				else
				{
					SetColor(White, Brown);
					printf("●");
					gotoxy(x, y);
				}
			}
			break;
		case LEFT:
			if (x > 0 && y <= 14)
			{
				pointermove(x, y);
				x -= 2;
				gotoxy(x, y);
				if (turn == 1)
				{
					SetColor(Black, Brown);
					printf("●");
					gotoxy(x, y);
				}
				else
				{
					SetColor(White, Brown);
					printf("●");
					gotoxy(x, y);
				}
			}
			break;
		case RIGHT:
			if (x < 28 && y <= 14)
			{
				pointermove(x, y);
				x += 2;
				gotoxy(x, y);
				if (turn == 1)
				{
					SetColor(Black, Brown);
					printf("●");
					gotoxy(x, y);
				}
				else
				{
					SetColor(White, Brown);
					printf("●");
					gotoxy(x, y);
				}
			}
			break;
		case SPACEBAR:
			if (turn == 1 && sequence == 0)	//천일점 구현
			{
				if (x == 14 && y == 7)
				{
					go_omok(x, y);
					start = clock();
				}
				else
				{
					SetColor(White, Black);
					gotoxy(36, 6);
					printf("처음 시작할 때에는 중앙 ");
					gotoxy(37, 8);
					printf("에만 놓을 수 있습니다.");	//메세지 출력

					Sleep(1000);	//딜레이

					gotoxy(36, 6);
					printf("                      ");
					gotoxy(37, 8);
					printf("                        ");	//메세지 제거

					gotoxy(42, 8);
					printf("현재 턴 : ○");
				}
			}
			else if (omok[y][x / 2] != 11 && omok[y][x / 2] != 12)
			{
				go_omok(x, y);
				start = clock();
			}
			else
			{
				SetColor(White, Black);
				gotoxy(37, 6);
				printf("이미 돌이 있는 위치에");
				gotoxy(40, 8);
				printf("둘 수 없습니다.");	//메세지 출력

				Sleep(1000);	//딜레이

				gotoxy(37, 6);
				printf("                      ");
				gotoxy(40, 8);
				printf("                 ");	//메세지 제거

				if (turn == 1)
				{
					gotoxy(42, 8);
					printf("현재 턴 : ○");
				}
				else
				{
					gotoxy(42, 8);
					printf("현재 턴 : ●");
				}
			}
			break;
		case ESC:
			SetColor(White, Black);
			system("cls");
			gotoxy(26, 13);
			printf("안녕히 가세요.\n\n\n\n\n\n\n\n\n\n");
			exit(0);
		}
	}
}

void go_omok(int x, int y)
{
	sequence++;
	if (turn == 1)
	{
		omok[y][x / 2] = 11;	//흑돌이 놓여진 배열의 값이 11로 변함
		if (jangmokcheck(x, y) == 1)
		{
			omok[y][x / 2] = 10;
			SetColor(Red, Brown);
			printf("△");

			sequence--;
			SetColor(White, Black);
			gotoxy(36, 6); 
			printf("흑돌의 경우에는 장목이");
			gotoxy(42, 8);
			printf("금지됩니다.");
			gotoxy(32, 10);
			printf("금수페널티로 차례가 넘어갑니다.");	//메세지 출력

			Sleep(1000);	//딜레이

			gotoxy(36, 6);
			printf("                      ");
			gotoxy(42, 8);
			printf("                 ");
			gotoxy(32, 10);
			printf("                               ");	//메세지 제거
		}
		else
		{
			if (wincheck(x, y, 11) == 1)
				ending(11);	// 금수라도 5목이 완성되면 승리
			else
			{
				threecheck(x, y);
				fourcheck(x, y);

				if (four_count == 2 && closedfour(x, y) != 1)	// 닫힌 4가 없는 44체크
				{
					omok[y][x / 2] = 10;
					SetColor(Red, Brown);
					printf("△");

					sequence--;
					SetColor(White, Black);
					gotoxy(36, 6);
					printf("흑돌의 경우에는 쌍사가");
					gotoxy(42, 8);
					printf("금지됩니다.");
					gotoxy(32, 10);
					printf("금수페널티로 차례가 넘어갑니다.");	//메세지 출력

					Sleep(1000);	//딜레이

					gotoxy(36, 6);
					printf("                      ");
					gotoxy(42, 8);
					printf("                 ");
					gotoxy(32, 10);
					printf("                               ");	//메세지 제거

					three_count = 0;
					four_count = 0;
				}
				else
				{
					if (three_count == 2 && four_count < 1)	//43이 아닌 열린 33검사
					{
						omok[y][x / 2] = 10;
						SetColor(Red, Brown);
						printf("△");

						sequence--;
						SetColor(White, Black);
						gotoxy(36, 6);
						printf("흑돌의 경우에는 쌍삼이");
						gotoxy(42, 8);
						printf("금지됩니다.");
						gotoxy(32, 10);
						printf("금수페널티로 차례가 넘어갑니다.");	//메세지 출력

						Sleep(1000);	//딜레이

						gotoxy(36, 6);
						printf("                      ");
						gotoxy(42, 8);
						printf("                 ");
						gotoxy(32, 10);
						printf("                               ");	//메세지 제거

						three_count = 0;
						four_count = 0;
					}
				three_count = 0;
				four_count = 0;
				}
			}
		}
		turn--;
		SetColor(White, Black);
		gotoxy(42, 8);
		printf("현재 턴 : ●");
	}
	else
	{
		omok[y][x / 2] = 12;	//백돌이 놓여진 배열의 값이 12로 변함

		if (wincheck(x, y ,12) == 1)
			ending(12);

		turn++;
		SetColor(White, Black);
		gotoxy(42, 8);
		printf("현재 턴 : ○");
	}	//1일 때 흑돌, 0일 때 백돌
}

void fourcheck(int x, int y)
{
	int i = y;
	int j = x / 2;

	if (omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11)	//│방향 검사
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11)	// 띄어진│방향 검사 1
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i - 4][j] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11)	// 띄어진│방향 검사 2
		four_count++;
	if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 3][j] == 11 && omok[i - 4][j] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 4][j] == 11)	// 띄어진│방향 검사 3
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11 && omok[i - 4][j] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][i + 3] == 11)	//↗방향 검사
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][i + 4] == 11)	// 띄어진↗방향 검사 1
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][i + 4] == 11)	// 띄어진↗방향 검사 2
		four_count++;
	if (omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 4][i + 4] == 11)	// 띄어진↗방향 검사 3
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11)	//─방향 검사
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11)	// 띄어진─방향 검사 1
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11)	// 띄어진─방향 검사 2
		four_count++;
	if (omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 4] == 11)	// 띄어진─방향 검사 3
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11)	//↘방향 검사
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11)	// 띄어진↘방향 검사 1
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11)	// 띄어진↘방향 검사 2
		four_count++;
	if (omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 4][j + 4] == 11)	// 띄어진↘방향 검사 3
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 3][j + 3] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11)
		four_count++;
}

int closedfour(int x, int y)
{
	int i = y;
	int j = x / 2;

	if (omok[i - 1][j] == 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 12)	//│방향 검사
		return 1;
	else if (omok[i - 2][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 12)
		return 1;
	else if (omok[i - 3][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 12)
		return 1;
	else if (omok[i - 4][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11 && omok[i + 1][j] == 12)
		return 1;
	else if (omok[i - 1][j] == 12 && omok[i][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11 && omok[i + 5][j] == 12)	// 띄어진│방향 검사 1
		return 1;
	else if (omok[i - 3][j] == 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 12)
		return 1;
	else if (omok[i - 4][j] == 12 && omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 12)
		return 1;
	else if (omok[i - 5][j] == 12 &&omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i - 4][j] == 11 && omok[i + 1][j] == 12)
		return 1;
	else if (omok[i - 1][j] == 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11 && omok[i + 5][j] == 12)	// 띄어진│방향 검사 2
		return 1;
	else if (omok[i - 2][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 12)
		return 1;
	else if (omok[i - 4][j] == 12 && omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 12)
		return 1;
	else if (omok[i - 5][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 3][j] == 11 && omok[i - 4][j] == 11 && omok[i + 1][j] == 12)
		return 1;
	else if (omok[i - 1][j] == 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 4][j] == 11 && omok[i + 5][j] == 12)	// 띄어진│방향 검사 3
		return 1;
	else if (omok[i - 2][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 12)
		return 1;
	else if (omok[i - 3][j] == 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 12)
		return 1;
	else if (omok[i - 5][j] == 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11 && omok[i - 4][j] == 11 && omok[i + 1][j] == 12)
		return 1;

	if (omok[i + 1][j - 1] == 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][i + 3] == 11 && omok[i - 4][j + 4] == 12)	//↗방향 검사
		return 1;
	else if (omok[i + 2][j - 2] == 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 12)
		return 1;
	else if (omok[i + 3][j - 3] == 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 12)
		return 1;
	else if (omok[i + 4][j - 4] == 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 12)
		return 1;
	else if (omok[i + 1][j - 1] == 12 && omok[i][j] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][i + 4] == 11 && omok[i - 5][j + 5] == 12)	// 띄어진↗방향 검사 1
		return 1;
	else if (omok[i + 3][j - 3] == 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 12)
		return 1;
	else if (omok[i + 4][j - 4] == 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 12)
		return 1;
	else if (omok[i + 5][j - 5] == 12 && omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 12)
		return 1;
	else if (omok[i + 1][j - 1] == 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 11&& omok[i - 5][j + 5] == 12)	// 띄어진↗방향 검사 2
		return 1;
	else if (omok[i + 2][j - 2] == 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 12)
		return 1;
	else if (omok[i + 4][j - 4] == 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 12)
		return 1;
	else if (omok[i + 5][j - 5] == 12 && omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 12)
		return 1;
	else if (omok[i + 1][j - 1] == 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 4][i + 4] == 11 && omok[i - 5][j + 5] == 12)	// 띄어진↗방향 검사 3
		return 1;
	else if (omok[i + 2][j - 2] == 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 12)
		return 1;
	else if (omok[i + 3][j - 3] == 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 12)
		return 1;
	else if (omok[i + 5][j - 5] == 12 && omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 12)
		return 1;

	if (omok[i][j - 1] == 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 12)	//─방향 검사
		return 1;
	else if (omok[i][j - 2] == 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 12)
		return 1;
	else if (omok[i][j - 3] == 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 12)
		return 1;
	else if (omok[i][j - 4] == 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 12)
		return 1;
	else if (omok[i][j - 1] == 12 && omok[i][j] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11 && omok[i][j + 5] == 12)	// 띄어진─방향 검사 1
		return 1;
	else if (omok[i][j - 3] == 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 12)
		return 1;
	else if (omok[i][j - 4] == 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 12)
		return 1;
	else if (omok[i][j - 5] == 12 && omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 12)
		return 1;
	else if (omok[i][j - 1] == 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11 && omok[i][j + 5] == 12)	// 띄어진─방향 검사 2
		return 1;
	else if (omok[i][j - 2] == 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 12)
		return 1;
	else if (omok[i][j - 4] == 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 12)
		return 1;
	else if (omok[i][j - 5] == 12 && omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 12)
		return 1;
	else if (omok[i][j - 1] == 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 4] == 11 && omok[i][j + 5] == 12)	// 띄어진─방향 검사 3
		return 1;
	else if (omok[i][j - 2] == 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 12)
		return 1;
	else if (omok[i][j - 3] == 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 12)
		return 1;
	else if (omok[i][j - 5] == 12 && omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 12)
		return 1;

	if (omok[i - 1][j - 1] == 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 12)	//↘방향 검사
		return 1;
	else if (omok[i - 2][j - 2] == 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 12)
		return 1;
	else if (omok[i - 3][j - 3] == 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 12)
		return 1;
	else if (omok[i - 4][j - 4] == 12 && omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 12)
		return 1;
	else if (omok[i - 1][j - 1] == 12 && omok[i][j] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11 && omok[i + 5][j + 5] == 12)	// 띄어진↘방향 검사 1
		return 1;
	else if (omok[i - 3][j - 3] == 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 12)
		return 1;
	else if (omok[i - 4][j - 4] == 12 && omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 12)
		return 1;
	else if (omok[i - 5][j - 5] == 12 && omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 12)
		return 1;
	else if (omok[i - 1][j - 1] == 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11 && omok[i + 5][j + 5] == 12)	// 띄어진↘방향 검사 2
		return 1;
	else if (omok[i - 2][j - 2] == 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 12)
		return 1;
	else if (omok[i - 4][j - 4] == 12 && omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 12)
		return 1;
	else if (omok[i - 5][j - 5] == 12 && omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 12)
		return 1;
	else if (omok[i - 1][j - 1] == 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 4][j + 4] == 11 && omok[i + 5][j + 5] == 12)	// 띄어진↘방향 검사 3
		return 1;
	else if (omok[i - 2][j - 2] == 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 12)
		return 1;
	else if (omok[i - 3][j - 3] == 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 12)
		return 1;
	else if (omok[i - 5][j - 5] == 12 && omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 12)
		return 1;

	else
		return 0;
}

void threecheck(int x, int y)
{
	int i = y;
	int j = x / 2;

	
	if (omok[i - 1][j] != 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] != 12)	//│방향 검사
		three_count++;
	else if (omok[i - 2][j] != 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] != 12)
		three_count++;
	else if (omok[i - 3][j] != 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] != 12)
		three_count++;
	else if (omok[i - 1][j] != 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] != 12)	// 띄어진│방향 검사 1
		three_count++;
	else if (omok[i - 2][j] != 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] != 12)
		three_count++;
	else if (omok[i - 4][j] != 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11 && omok[i + 1][j] != 12)
		three_count++;
	else if (omok[i - 1][j] != 12 && omok[i][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] != 12)	// 띄어진│방향 검사 2
		three_count++;
	else if (omok[i - 3][j] != 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] != 12)
		three_count++;
	else if (omok[i - 4][j] != 12 && omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] != 12)
		three_count++;

	if (omok[i + 1][j - 1] != 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] != 12)	//↗방향 검사
		three_count++;
	else if (omok[i + 2][j - 2] != 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] != 12)
		three_count++;
	else if (omok[i - 1][j + 1] != 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i + 3][j - 3] != 12)
		three_count++;
	else if (omok[i + 1][j - 1] != 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] != 12)	// 띄어진↗방향 검사 1
		three_count++;
	else if (omok[i + 2][j - 2] != 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] != 12)
		three_count++;
	else if (omok[i - 1][j + 1] != 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 4][j - 4] != 12)
		three_count++;
	else if (omok[i + 1][j - 1] != 12 && omok[i][j] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] != 12)	// 띄어진↗방향 검사 2
		three_count++;
	else if (omok[i + 3][j - 3] != 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] != 12)
		three_count++;
	else if (omok[i - 1][j + 1] != 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11 && omok[i + 4][j - 4] != 12)
		three_count++;

	if (omok[i - 1][j - 1] != 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] != 12)	//↘방향 검사
		three_count++;
	else if (omok[i - 2][j - 2] != 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] != 12)
		three_count++;
	else if (omok[i - 3][j - 3] != 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] != 12)
		three_count++;
	else if (omok[i - 1][j - 1] != 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] != 12)	// 띄어진↘방향 검사 1
		three_count++;
	else if (omok[i - 2][j - 2] != 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] != 12)
		three_count++;
	else if (omok[i - 4][j - 4] != 12 && omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] != 12)
		three_count++;
	else if (omok[i - 1][j - 1] != 12 && omok[i][j] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] != 12)	// 띄어진↘방향 검사 2
		three_count++;
	else if (omok[i - 3][j - 3] != 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] != 12)
		three_count++;
	else if (omok[i - 4][j - 4] != 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 3][j - 3] == 11 && omok[i + 1][j + 1] != 12)
		three_count++;

	if (omok[i][j - 1] != 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] != 12)	//─방향 검사
		three_count++;
	else if (omok[i][j - 2] != 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] != 12)
		three_count++;
	else if (omok[i][j - 3] != 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] != 12)
		three_count++;
	else if (omok[i][j - 1] != 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] != 12)	// 띄어진─방향 검사 1
		three_count++;
	else if (omok[i][j - 2] != 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] != 12)
		three_count++;
	else if (omok[i][j - 4] != 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] != 12)
		three_count++;
	else if (omok[i][j - 1] != 12 && omok[i][j] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] != 12)	// 띄어진─방향 검사 2
		three_count++;
	else if (omok[i][j - 3] != 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] != 12)
		three_count++;
	else if (omok[i][j - 4] != 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] != 12)
		three_count++;
}

int jangmokcheck(int x, int y)
{
	int i = y;
	int j = x / 2;

	if (omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11 && omok[i + 5][j + 5] == 11)	//↘방향 검사
		return 1;
	if (omok[i - 1][j - 1] == 11 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11)
		return 1;
	if (omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11)
		return 1;
	if (omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11)
		return 1;
	if (omok[i - 4][j - 4] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11)
		return 1;
	if (omok[i - 5][j - 5] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i][j] == 11)
		return 1;
	
	if (omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 11 && omok[i - 5][j + 5] == 11)	//↗방향 검사
		return 1;
	if (omok[i + 1][j - 1] == 11 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 11)
		return 1;
	if (omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11)
		return 1;
	if (omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11)
		return 1;
	if (omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11)
		return 1;
	if (omok[i + 5][j - 5] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i][j] == 11)
		return 1;

	if (omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11 && omok[i][j + 5] == 11)	//─방향 검사
		return 1;
	if (omok[i][j - 1] == 11 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11)
		return 1;
	if (omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11)
		return 1;
	if (omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11)
		return 1;
	if (omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j] == 11 && omok[i][j + 1] == 11)
		return 1;
	if (omok[i][j - 5] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j] == 11)
		return 1;

	if (omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11 && omok[i + 5][j] == 11)	//│방향 검사
		return 1;
	if (omok[i - 1][j] == 11 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11)
		return 1;
	if (omok[i - 2][j] == 11 && omok[i - 1][j] == 11 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11)
		return 1;
	if (omok[i - 3][j] == 11 && omok[i - 2][j] == 11 && omok[i - 1][j] == 11 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11)
		return 1;
	if (omok[i - 4][j] == 11 && omok[i - 3][j] == 11 && omok[i - 2][j] == 11 && omok[i - 1][j] == 11 && omok[i][j] == 11 && omok[i + 1][j] == 11)
		return 1;
	if (omok[i - 5][j] == 11 && omok[i - 4][j] == 11 && omok[i - 3][j] == 11 && omok[i - 2][j] == 11 && omok[i - 1][j] == 11 && omok[i][j] == 11)
		return 1;

	else
		return 0;
}
 
int wincheck(int x, int y, int k)
{
	int i = y;
	int j = x / 2;

	if (omok[i][j] == k && omok[i + 1][j + 1] == k && omok[i + 2][j + 2] == k && omok[i + 3][j + 3] == k && omok[i + 4][j + 4] == k)	//↘방향 검사
		return 1;
	if (omok[i - 1][j - 1] == k && omok[i][j] == k && omok[i + 1][j + 1] == k && omok[i + 2][j + 2] == k && omok[i + 3][j + 3] == k)
		return 1;
	if (omok[i - 2][j - 2] == k && omok[i - 1][j - 1] == k && omok[i][j] == k && omok[i + 1][j + 1] == k && omok[i + 2][j + 2] == k)
		return 1;
	if (omok[i - 3][j - 3] == k && omok[i - 2][j - 2] == k && omok[i - 1][j - 1] == k && omok[i][j] == k && omok[i + 1][j + 1] == k)
		return 1;
	if (omok[i - 4][j - 4] == k && omok[i - 3][j - 3] == k && omok[i - 2][j - 2] == k && omok[i - 1][j - 1] == k && omok[i][j] == k)
		return 1;

	if (omok[i][j] == k && omok[i - 1][j + 1] == k && omok[i - 2][j + 2] == k && omok[i - 3][j + 3] == k && omok[i - 4][j + 4] == k)	//↗방향 검사
		return 1;
	if (omok[i + 1][j - 1] == k && omok[i][j] == k && omok[i - 1][j + 1] == k && omok[i - 2][j + 2] == k && omok[i - 3][j + 3] == k)
		return 1;
	if (omok[i + 2][j - 2] == k && omok[i + 1][j - 1] == k && omok[i][j] == k && omok[i - 1][j + 1] == k && omok[i - 2][j + 2] == k)
		return 1;
	if (omok[i + 3][j - 3] == k && omok[i + 2][j - 2] == k && omok[i + 1][j - 1] == k && omok[i][j] == k && omok[i - 1][j + 1] == k)
		return 1;
	if (omok[i + 4][j - 4] == k && omok[i + 3][j - 3] == k && omok[i + 2][j - 2] == k && omok[i + 1][j - 1] == k && omok[i][j] == k)
		return 1;
	
	if (omok[i][j] == k && omok[i][j + 1] == k && omok[i][j + 2] == k && omok[i][j + 3] == k && omok[i][j + 4] == k)	//─방향 검사
		return 1;
	if (omok[i][j - 1] == k && omok[i][j] == k && omok[i][j + 1] == k && omok[i][j + 2] == k && omok[i][j + 3] == k)
		return 1;
	if (omok[i][j - 2] == k && omok[i][j - 1] == k && omok[i][j] == k && omok[i][j + 1] == k && omok[i][j + 2] == k)
		return 1;
	if (omok[i][j - 3] == k && omok[i][j - 2] == k && omok[i][j - 1] == k && omok[i][j] == k && omok[i][j + 1] == k)
		return 1;
	if (omok[i][j - 4] == k && omok[i][j - 3] == k && omok[i][j - 2] == k && omok[i][j - 1] == k && omok[i][j] == k)
		return 1;

	if (omok[i][j] == k && omok[i + 1][j] == k && omok[i + 2][j] == k && omok[i + 3][j] == k && omok[i + 4][j] == k)	//│방향 검사
		return 1;
	if (omok[i - 1][j] == k && omok[i][j] == k && omok[i + 1][j] == k && omok[i + 2][j] == k && omok[i + 3][j] == k)
		return 1;
	if (omok[i - 2][j] == k && omok[i - 1][j] == k && omok[i][j] == k && omok[i + 1][j] == k && omok[i + 2][j] == k)
		return 1;
	if (omok[i - 3][j] == k && omok[i - 2][j] == k && omok[i - 1][j] == k && omok[i][j] == k && omok[i + 1][j] == k)
		return 1;
	if (omok[i - 4][j] == k && omok[i - 3][j] == k && omok[i - 2][j] == k && omok[i - 1][j] == k && omok[i][j] == k)
		return 1;

	else
		return 0;
}

void ending(int t)
{
	SetColor(White, Black);

	if (t == 11)
	{
		gotoxy(38, 6);
		printf("흑돌님이 %d 수 만에", sequence);
		gotoxy(40, 8);
		printf("승리하셨습니다.");
	}	//메세지 출력
	else
	{
		gotoxy(38, 6);
		printf("백돌님이 %d 수 만에", sequence);
		gotoxy(40, 8);
		printf("승리하셨습니다.");
	}	//메세지 출력

	gotoxy(38, 10);
	printf("재시작을 원하시나요?");
	gotoxy(40, 12);
	printf("1 : YES  2 : NO");

	int endflag;
	int i, j;

	while (1)
	{
		endflag = _getch();
		switch (endflag)
		{
		case 49:
			turn = 1;
			sequence = 0;

			omok[0][0] = 51;
			omok[0][14] = 52;
			omok[14][0] = 53;
			omok[14][14] = 54;

			for (j = 1; j < 14; j++)
				omok[0][j] = 6;
			for (i = 1; i < 14; i++)
				omok[i][0] = 7;
			for (j = 1; j < 14; j++)
				omok[14][j] = 8;
			for (i = 1; i < 14; i++)
				omok[i][14] = 9;

			for (int i = 1; i < 14; i++)
			{
				for (int j = 1; j < 14; j++)
				{
					omok[i][j] = 5;
				}
			}	//게임 정보 초기화

			main();

		case 50:
			SetColor(White, Black);
			system("cls");
			gotoxy(26, 13);
			printf("안녕히 가세요.\n\n\n\n\n\n\n\n\n\n");
			exit(0);
		}
	}
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y }; //x, y 좌표 설정
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //커서 설정
}

void pointermove(int x, int y)
{
	gotoxy(x, y);
	SetColor(Black, Brown);
	if (omok[y][x / 2] == 5)
		printf("╋ ");
	else if (omok[y][x / 2] == 51)
		printf("┏ ");
	else if (omok[y][x / 2] == 52)
		printf("┓ ");
	else if (omok[y][x / 2] == 53)
		printf("┗ ");
	else if (omok[y][x / 2] == 54)
		printf("┛ ");
	else if (omok[y][x / 2] == 6)
		printf("┳ ");
	else if (omok[y][x / 2] == 7)
		printf("┣ ");
	else if (omok[y][x / 2] == 8)
		printf("┻ ");
	else if (omok[y][x / 2] == 9)
		printf("┫ ");
	else if (omok[y][x / 2] == 10)
	{
		SetColor(Red, Brown);
		printf("△");
	}
	else if (omok[y][x / 2] == 11)
		printf("●");
	else if (omok[y][x / 2] == 12)
	{
		SetColor(White, Brown);
		printf("●");
	}
}	// 바둑돌 움직임 처리

void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}	// 마우스 커서 설정 함수


void SetColor(int txt, int bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt + bg * 16);
}	// 마우스 커서 위치 조절 함수