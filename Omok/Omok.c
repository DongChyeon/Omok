// �¸�����, �ݼ�ó��, Ÿ�̸� ��� ���� ����

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
};	//����ǥ

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32
#define ESC 27 //Ű �� ����

void show_omok();	//������ ��� �Լ�
void move_omok();	//���� �� ��ġ �̵� �Լ�
void go_omok(int x, int y);	//���� �α� �Լ�
void timer_check();	// Ÿ�̸� �ð� üũ
int wincheck(int x, int y, int k);	//���� üũ �Լ�
int jangmokcheck(int x, int y);	//6�� üũ �Լ�
void threecheck(int x, int y);	//�ֻ� üũ �Լ�
void fourcheck(int x, int y);	//�ֻ� üũ �Լ�
int closedfour(int x, int y);	//���� 4üũ �Լ�
void ending(int t);	//���� ȭ�� ��� �Լ�
void gotoxy(int x, int y);	//Ŀ�� �̵��� ���� �ʿ��� �Լ�
void setcursortype(CURSOR_TYPE c);	//Ŀ�� Ÿ�� ���� �Լ�
void pointermove(int x, int y);	//������ �̵� ó�� �Լ�
void SetColor(int txt, int bg);	//���� ���� ���� ���� �Լ�
void draw_info();	//���� ���� ��� �Լ�

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
};	//�迭 �������� ����

int x, y;	// ���� ��ġ ����
int turn = 1;	//���� ������ ���� �������� ����
int sequence = 0;	//sequence��° ����
int three_count = 0;	//3����
int four_count = 0;	//4����
clock_t start, end;
double limit_time;	// ���ѽð� ����

int main()
{
	setcursortype(NOCURSOR);
	system("mode con cols=65 lines=28");	//â ũ�� ����
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
		printf("���� �ð� : 0%f��", 30 - (double)(end - start) / CLOCKS_PER_SEC);
	}
	else if (limit_time <= 0)
	{
		gotoxy(33, 8);
		SetColor(White, Black);
		printf("�ð� �ʰ��� ���ʰ� �Ѿ�ϴ�.");	//�޼��� ���
		Sleep(1000);
		gotoxy(32, 8);
		printf("                              ");	//�޼��� ����
		start = clock();
		if (turn == 1)
		{
			turn--;
			gotoxy(42, 8);
			printf("���� �� : ��");
		}
		else
		{
			turn++;
			gotoxy(42, 8);
			printf("���� �� : ��");
		}	//�� ��ȯ
	}
	else
		printf("���� �ð� : %f��", 30 - (double)(end - start) / CLOCKS_PER_SEC);
	gotoxy(x, y);
}

void draw_info()
{
	SetColor(White, Black);
	gotoxy(1, 17);
	printf("���ӹ��");
	gotoxy(1, 19);
	printf("ȭ��ǥŰ�� �̵�");
	gotoxy(1, 21);
	printf("�����̽��ٸ� ������ ���� ���� ������.");
	gotoxy(1, 23);
	printf("ESC�� ���� �� ����");
	gotoxy(1, 25);
	printf("���ӷ��� ���ַ��� ����Դϴ�.");
}

void show_omok()
{
	SetColor(Black, Brown);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (omok[i][j] == 5)
				printf("�� ");
			else if (omok[i][j] == 51)
				printf("�� ");
			else if (omok[i][j] == 52)
				printf("�� ");
			else if (omok[i][j] == 53)
				printf("�� ");
			else if (omok[i][j] == 54)
				printf("�� ");
			else if (omok[i][j] == 6)
				printf("�� ");
			else if (omok[i][j] == 7)
				printf("�� ");
			else if (omok[i][j] == 8)
				printf("�� ");
			else if (omok[i][j] == 9)
				printf("�� ");
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
	printf("���� �� : ��");
	gotoxy(x, y);
	SetColor(Black, Brown);
	printf("��");

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
					printf("��");
					gotoxy(x, y);
				}
				else
				{
					SetColor(White, Brown);
					printf("��");
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
					printf("��");
					gotoxy(x, y);
				}
				else
				{
					SetColor(White, Brown);
					printf("��");
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
					printf("��");
					gotoxy(x, y);
				}
				else
				{
					SetColor(White, Brown);
					printf("��");
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
					printf("��");
					gotoxy(x, y);
				}
				else
				{
					SetColor(White, Brown);
					printf("��");
					gotoxy(x, y);
				}
			}
			break;
		case SPACEBAR:
			if (turn == 1 && sequence == 0)	//õ���� ����
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
					printf("ó�� ������ ������ �߾� ");
					gotoxy(37, 8);
					printf("���� ���� �� �ֽ��ϴ�.");	//�޼��� ���

					Sleep(1000);	//������

					gotoxy(36, 6);
					printf("                      ");
					gotoxy(37, 8);
					printf("                        ");	//�޼��� ����

					gotoxy(42, 8);
					printf("���� �� : ��");
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
				printf("�̹� ���� �ִ� ��ġ��");
				gotoxy(40, 8);
				printf("�� �� �����ϴ�.");	//�޼��� ���

				Sleep(1000);	//������

				gotoxy(37, 6);
				printf("                      ");
				gotoxy(40, 8);
				printf("                 ");	//�޼��� ����

				if (turn == 1)
				{
					gotoxy(42, 8);
					printf("���� �� : ��");
				}
				else
				{
					gotoxy(42, 8);
					printf("���� �� : ��");
				}
			}
			break;
		case ESC:
			SetColor(White, Black);
			system("cls");
			gotoxy(26, 13);
			printf("�ȳ��� ������.\n\n\n\n\n\n\n\n\n\n");
			exit(0);
		}
	}
}

void go_omok(int x, int y)
{
	sequence++;
	if (turn == 1)
	{
		omok[y][x / 2] = 11;	//�浹�� ������ �迭�� ���� 11�� ����
		if (jangmokcheck(x, y) == 1)
		{
			omok[y][x / 2] = 10;
			SetColor(Red, Brown);
			printf("��");

			sequence--;
			SetColor(White, Black);
			gotoxy(36, 6); 
			printf("�浹�� ��쿡�� �����");
			gotoxy(42, 8);
			printf("�����˴ϴ�.");
			gotoxy(32, 10);
			printf("�ݼ����Ƽ�� ���ʰ� �Ѿ�ϴ�.");	//�޼��� ���

			Sleep(1000);	//������

			gotoxy(36, 6);
			printf("                      ");
			gotoxy(42, 8);
			printf("                 ");
			gotoxy(32, 10);
			printf("                               ");	//�޼��� ����
		}
		else
		{
			if (wincheck(x, y, 11) == 1)
				ending(11);	// �ݼ��� 5���� �ϼ��Ǹ� �¸�
			else
			{
				threecheck(x, y);
				fourcheck(x, y);

				if (four_count == 2 && closedfour(x, y) != 1)	// ���� 4�� ���� 44üũ
				{
					omok[y][x / 2] = 10;
					SetColor(Red, Brown);
					printf("��");

					sequence--;
					SetColor(White, Black);
					gotoxy(36, 6);
					printf("�浹�� ��쿡�� �ֻ簡");
					gotoxy(42, 8);
					printf("�����˴ϴ�.");
					gotoxy(32, 10);
					printf("�ݼ����Ƽ�� ���ʰ� �Ѿ�ϴ�.");	//�޼��� ���

					Sleep(1000);	//������

					gotoxy(36, 6);
					printf("                      ");
					gotoxy(42, 8);
					printf("                 ");
					gotoxy(32, 10);
					printf("                               ");	//�޼��� ����

					three_count = 0;
					four_count = 0;
				}
				else
				{
					if (three_count == 2 && four_count < 1)	//43�� �ƴ� ���� 33�˻�
					{
						omok[y][x / 2] = 10;
						SetColor(Red, Brown);
						printf("��");

						sequence--;
						SetColor(White, Black);
						gotoxy(36, 6);
						printf("�浹�� ��쿡�� �ֻ���");
						gotoxy(42, 8);
						printf("�����˴ϴ�.");
						gotoxy(32, 10);
						printf("�ݼ����Ƽ�� ���ʰ� �Ѿ�ϴ�.");	//�޼��� ���

						Sleep(1000);	//������

						gotoxy(36, 6);
						printf("                      ");
						gotoxy(42, 8);
						printf("                 ");
						gotoxy(32, 10);
						printf("                               ");	//�޼��� ����

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
		printf("���� �� : ��");
	}
	else
	{
		omok[y][x / 2] = 12;	//�鵹�� ������ �迭�� ���� 12�� ����

		if (wincheck(x, y ,12) == 1)
			ending(12);

		turn++;
		SetColor(White, Black);
		gotoxy(42, 8);
		printf("���� �� : ��");
	}	//1�� �� �浹, 0�� �� �鵹
}

void fourcheck(int x, int y)
{
	int i = y;
	int j = x / 2;

	if (omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11)	//������ �˻�
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11)	// ����������� �˻� 1
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i - 4][j] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11)	// ����������� �˻� 2
		four_count++;
	if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 3][j] == 11 && omok[i - 4][j] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 4][j] == 11)	// ����������� �˻� 3
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11 && omok[i - 4][j] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][i + 3] == 11)	//�ֹ��� �˻�
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][i + 4] == 11)	// ������ֹ��� �˻� 1
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][i + 4] == 11)	// ������ֹ��� �˻� 2
		four_count++;
	if (omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 4][i + 4] == 11)	// ������ֹ��� �˻� 3
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11)	//������ �˻�
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11)	// ����������� �˻� 1
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11)	// ����������� �˻� 2
		four_count++;
	if (omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 4] == 11)	// ����������� �˻� 3
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11)	//�ٹ��� �˻�
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11)	// ������ٹ��� �˻� 1
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11)
		four_count++;
	else if (omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11)	// ������ٹ��� �˻� 2
		four_count++;
	if (omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11)
		four_count++;
	if (omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 1][j - 1] == 11)
		four_count++;

	if (omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 4][j + 4] == 11)	// ������ٹ��� �˻� 3
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

	if (omok[i - 1][j] == 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 12)	//������ �˻�
		return 1;
	else if (omok[i - 2][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 12)
		return 1;
	else if (omok[i - 3][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 12)
		return 1;
	else if (omok[i - 4][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11 && omok[i + 1][j] == 12)
		return 1;
	else if (omok[i - 1][j] == 12 && omok[i][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11 && omok[i + 5][j] == 12)	// ����������� �˻� 1
		return 1;
	else if (omok[i - 3][j] == 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 12)
		return 1;
	else if (omok[i - 4][j] == 12 && omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 12)
		return 1;
	else if (omok[i - 5][j] == 12 &&omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i - 4][j] == 11 && omok[i + 1][j] == 12)
		return 1;
	else if (omok[i - 1][j] == 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11 && omok[i + 5][j] == 12)	// ����������� �˻� 2
		return 1;
	else if (omok[i - 2][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 12)
		return 1;
	else if (omok[i - 4][j] == 12 && omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 12)
		return 1;
	else if (omok[i - 5][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 3][j] == 11 && omok[i - 4][j] == 11 && omok[i + 1][j] == 12)
		return 1;
	else if (omok[i - 1][j] == 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 4][j] == 11 && omok[i + 5][j] == 12)	// ����������� �˻� 3
		return 1;
	else if (omok[i - 2][j] == 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 12)
		return 1;
	else if (omok[i - 3][j] == 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 12)
		return 1;
	else if (omok[i - 5][j] == 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11 && omok[i - 4][j] == 11 && omok[i + 1][j] == 12)
		return 1;

	if (omok[i + 1][j - 1] == 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][i + 3] == 11 && omok[i - 4][j + 4] == 12)	//�ֹ��� �˻�
		return 1;
	else if (omok[i + 2][j - 2] == 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 12)
		return 1;
	else if (omok[i + 3][j - 3] == 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 12)
		return 1;
	else if (omok[i + 4][j - 4] == 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 12)
		return 1;
	else if (omok[i + 1][j - 1] == 12 && omok[i][j] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][i + 4] == 11 && omok[i - 5][j + 5] == 12)	// ������ֹ��� �˻� 1
		return 1;
	else if (omok[i + 3][j - 3] == 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 12)
		return 1;
	else if (omok[i + 4][j - 4] == 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 12)
		return 1;
	else if (omok[i + 5][j - 5] == 12 && omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 12)
		return 1;
	else if (omok[i + 1][j - 1] == 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 11&& omok[i - 5][j + 5] == 12)	// ������ֹ��� �˻� 2
		return 1;
	else if (omok[i + 2][j - 2] == 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 12)
		return 1;
	else if (omok[i + 4][j - 4] == 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 12)
		return 1;
	else if (omok[i + 5][j - 5] == 12 && omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 12)
		return 1;
	else if (omok[i + 1][j - 1] == 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 4][i + 4] == 11 && omok[i - 5][j + 5] == 12)	// ������ֹ��� �˻� 3
		return 1;
	else if (omok[i + 2][j - 2] == 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 12)
		return 1;
	else if (omok[i + 3][j - 3] == 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 12)
		return 1;
	else if (omok[i + 5][j - 5] == 12 && omok[i][j] == 11 && omok[i + 4][j - 4] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 12)
		return 1;

	if (omok[i][j - 1] == 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 12)	//������ �˻�
		return 1;
	else if (omok[i][j - 2] == 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 12)
		return 1;
	else if (omok[i][j - 3] == 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 12)
		return 1;
	else if (omok[i][j - 4] == 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 12)
		return 1;
	else if (omok[i][j - 1] == 12 && omok[i][j] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11 && omok[i][j + 5] == 12)	// ����������� �˻� 1
		return 1;
	else if (omok[i][j - 3] == 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 12)
		return 1;
	else if (omok[i][j - 4] == 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 12)
		return 1;
	else if (omok[i][j - 5] == 12 && omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 12)
		return 1;
	else if (omok[i][j - 1] == 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11 && omok[i][j + 5] == 12)	// ����������� �˻� 2
		return 1;
	else if (omok[i][j - 2] == 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 12)
		return 1;
	else if (omok[i][j - 4] == 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 12)
		return 1;
	else if (omok[i][j - 5] == 12 && omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 12)
		return 1;
	else if (omok[i][j - 1] == 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 4] == 11 && omok[i][j + 5] == 12)	// ����������� �˻� 3
		return 1;
	else if (omok[i][j - 2] == 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 12)
		return 1;
	else if (omok[i][j - 3] == 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 12)
		return 1;
	else if (omok[i][j - 5] == 12 && omok[i][j] == 11 && omok[i][j - 4] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] == 12)
		return 1;

	if (omok[i - 1][j - 1] == 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 12)	//�ٹ��� �˻�
		return 1;
	else if (omok[i - 2][j - 2] == 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 12)
		return 1;
	else if (omok[i - 3][j - 3] == 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 12)
		return 1;
	else if (omok[i - 4][j - 4] == 12 && omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 12)
		return 1;
	else if (omok[i - 1][j - 1] == 12 && omok[i][j] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11 && omok[i + 5][j + 5] == 12)	// ������ٹ��� �˻� 1
		return 1;
	else if (omok[i - 3][j - 3] == 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 12)
		return 1;
	else if (omok[i - 4][j - 4] == 12 && omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 12)
		return 1;
	else if (omok[i - 5][j - 5] == 12 && omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 12)
		return 1;
	else if (omok[i - 1][j - 1] == 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11 && omok[i + 5][j + 5] == 12)	// ������ٹ��� �˻� 2
		return 1;
	else if (omok[i - 2][j - 2] == 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 12)
		return 1;
	else if (omok[i - 4][j - 4] == 12 && omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 12)
		return 1;
	else if (omok[i - 5][j - 5] == 12 && omok[i][j] == 11 && omok[i - 4][j - 4] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 12)
		return 1;
	else if (omok[i - 1][j - 1] == 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 4][j + 4] == 11 && omok[i + 5][j + 5] == 12)	// ������ٹ��� �˻� 3
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

	
	if (omok[i - 1][j] != 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] != 12)	//������ �˻�
		three_count++;
	else if (omok[i - 2][j] != 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] != 12)
		three_count++;
	else if (omok[i - 3][j] != 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] != 12)
		three_count++;
	else if (omok[i - 1][j] != 12 && omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] != 12)	// ����������� �˻� 1
		three_count++;
	else if (omok[i - 2][j] != 12 && omok[i][j] == 11 && omok[i - 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] != 12)
		three_count++;
	else if (omok[i - 4][j] != 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i - 3][j] == 11 && omok[i + 1][j] != 12)
		three_count++;
	else if (omok[i - 1][j] != 12 && omok[i][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] != 12)	// ����������� �˻� 2
		three_count++;
	else if (omok[i - 3][j] != 12 && omok[i][j] == 11 && omok[i - 2][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] != 12)
		three_count++;
	else if (omok[i - 4][j] != 12 && omok[i][j] == 11 && omok[i - 3][j] == 11 && omok[i - 1][j] == 11 && omok[i + 1][j] != 12)
		three_count++;

	if (omok[i + 1][j - 1] != 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] != 12)	//�ֹ��� �˻�
		three_count++;
	else if (omok[i + 2][j - 2] != 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] != 12)
		three_count++;
	else if (omok[i - 1][j + 1] != 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 1][j - 1] == 11 && omok[i + 3][j - 3] != 12)
		three_count++;
	else if (omok[i + 1][j - 1] != 12 && omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] != 12)	// ������ֹ��� �˻� 1
		three_count++;
	else if (omok[i + 2][j - 2] != 12 && omok[i][j] == 11 && omok[i + 1][j - 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] != 12)
		three_count++;
	else if (omok[i - 1][j + 1] != 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 2][j - 2] == 11 && omok[i + 4][j - 4] != 12)
		three_count++;
	else if (omok[i + 1][j - 1] != 12 && omok[i][j] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] != 12)	// ������ֹ��� �˻� 2
		three_count++;
	else if (omok[i + 3][j - 3] != 12 && omok[i][j] == 11 && omok[i + 2][j - 2] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] != 12)
		three_count++;
	else if (omok[i - 1][j + 1] != 12 && omok[i][j] == 11 && omok[i + 3][j - 3] == 11 && omok[i + 1][j - 1] == 11 && omok[i + 4][j - 4] != 12)
		three_count++;

	if (omok[i - 1][j - 1] != 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] != 12)	//�ٹ��� �˻�
		three_count++;
	else if (omok[i - 2][j - 2] != 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] != 12)
		three_count++;
	else if (omok[i - 3][j - 3] != 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 1][j + 1] != 12)
		three_count++;
	else if (omok[i - 1][j - 1] != 12 && omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] != 12)	// ������ٹ��� �˻� 1
		three_count++;
	else if (omok[i - 2][j - 2] != 12 && omok[i][j] == 11 && omok[i - 1][j - 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] != 12)
		three_count++;
	else if (omok[i - 4][j - 4] != 12 && omok[i][j] == 11 && omok[i - 3][j - 3] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] != 12)
		three_count++;
	else if (omok[i - 1][j - 1] != 12 && omok[i][j] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] != 12)	// ������ٹ��� �˻� 2
		three_count++;
	else if (omok[i - 3][j - 3] != 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] != 12)
		three_count++;
	else if (omok[i - 4][j - 4] != 12 && omok[i][j] == 11 && omok[i - 2][j - 2] == 11 && omok[i - 3][j - 3] == 11 && omok[i + 1][j + 1] != 12)
		three_count++;

	if (omok[i][j - 1] != 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] != 12)	//������ �˻�
		three_count++;
	else if (omok[i][j - 2] != 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] != 12)
		three_count++;
	else if (omok[i][j - 3] != 12 && omok[i][j] == 11 && omok[i][j - 2] == 11 && omok[i][j - 1] == 11 && omok[i][j + 1] != 12)
		three_count++;
	else if (omok[i][j - 1] != 12 && omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] != 12)	// ����������� �˻� 1
		three_count++;
	else if (omok[i][j - 2] != 12 && omok[i][j] == 11 && omok[i][j - 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] != 12)
		three_count++;
	else if (omok[i][j - 4] != 12 && omok[i][j] == 11 && omok[i][j - 3] == 11 && omok[i][j - 2] == 11 && omok[i][j + 1] != 12)
		three_count++;
	else if (omok[i][j - 1] != 12 && omok[i][j] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] != 12)	// ����������� �˻� 2
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

	if (omok[i][j] == 11 && omok[i + 1][j + 1] == 11 && omok[i + 2][j + 2] == 11 && omok[i + 3][j + 3] == 11 && omok[i + 4][j + 4] == 11 && omok[i + 5][j + 5] == 11)	//�ٹ��� �˻�
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
	
	if (omok[i][j] == 11 && omok[i - 1][j + 1] == 11 && omok[i - 2][j + 2] == 11 && omok[i - 3][j + 3] == 11 && omok[i - 4][j + 4] == 11 && omok[i - 5][j + 5] == 11)	//�ֹ��� �˻�
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

	if (omok[i][j] == 11 && omok[i][j + 1] == 11 && omok[i][j + 2] == 11 && omok[i][j + 3] == 11 && omok[i][j + 4] == 11 && omok[i][j + 5] == 11)	//������ �˻�
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

	if (omok[i][j] == 11 && omok[i + 1][j] == 11 && omok[i + 2][j] == 11 && omok[i + 3][j] == 11 && omok[i + 4][j] == 11 && omok[i + 5][j] == 11)	//������ �˻�
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

	if (omok[i][j] == k && omok[i + 1][j + 1] == k && omok[i + 2][j + 2] == k && omok[i + 3][j + 3] == k && omok[i + 4][j + 4] == k)	//�ٹ��� �˻�
		return 1;
	if (omok[i - 1][j - 1] == k && omok[i][j] == k && omok[i + 1][j + 1] == k && omok[i + 2][j + 2] == k && omok[i + 3][j + 3] == k)
		return 1;
	if (omok[i - 2][j - 2] == k && omok[i - 1][j - 1] == k && omok[i][j] == k && omok[i + 1][j + 1] == k && omok[i + 2][j + 2] == k)
		return 1;
	if (omok[i - 3][j - 3] == k && omok[i - 2][j - 2] == k && omok[i - 1][j - 1] == k && omok[i][j] == k && omok[i + 1][j + 1] == k)
		return 1;
	if (omok[i - 4][j - 4] == k && omok[i - 3][j - 3] == k && omok[i - 2][j - 2] == k && omok[i - 1][j - 1] == k && omok[i][j] == k)
		return 1;

	if (omok[i][j] == k && omok[i - 1][j + 1] == k && omok[i - 2][j + 2] == k && omok[i - 3][j + 3] == k && omok[i - 4][j + 4] == k)	//�ֹ��� �˻�
		return 1;
	if (omok[i + 1][j - 1] == k && omok[i][j] == k && omok[i - 1][j + 1] == k && omok[i - 2][j + 2] == k && omok[i - 3][j + 3] == k)
		return 1;
	if (omok[i + 2][j - 2] == k && omok[i + 1][j - 1] == k && omok[i][j] == k && omok[i - 1][j + 1] == k && omok[i - 2][j + 2] == k)
		return 1;
	if (omok[i + 3][j - 3] == k && omok[i + 2][j - 2] == k && omok[i + 1][j - 1] == k && omok[i][j] == k && omok[i - 1][j + 1] == k)
		return 1;
	if (omok[i + 4][j - 4] == k && omok[i + 3][j - 3] == k && omok[i + 2][j - 2] == k && omok[i + 1][j - 1] == k && omok[i][j] == k)
		return 1;
	
	if (omok[i][j] == k && omok[i][j + 1] == k && omok[i][j + 2] == k && omok[i][j + 3] == k && omok[i][j + 4] == k)	//������ �˻�
		return 1;
	if (omok[i][j - 1] == k && omok[i][j] == k && omok[i][j + 1] == k && omok[i][j + 2] == k && omok[i][j + 3] == k)
		return 1;
	if (omok[i][j - 2] == k && omok[i][j - 1] == k && omok[i][j] == k && omok[i][j + 1] == k && omok[i][j + 2] == k)
		return 1;
	if (omok[i][j - 3] == k && omok[i][j - 2] == k && omok[i][j - 1] == k && omok[i][j] == k && omok[i][j + 1] == k)
		return 1;
	if (omok[i][j - 4] == k && omok[i][j - 3] == k && omok[i][j - 2] == k && omok[i][j - 1] == k && omok[i][j] == k)
		return 1;

	if (omok[i][j] == k && omok[i + 1][j] == k && omok[i + 2][j] == k && omok[i + 3][j] == k && omok[i + 4][j] == k)	//������ �˻�
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
		printf("�浹���� %d �� ����", sequence);
		gotoxy(40, 8);
		printf("�¸��ϼ̽��ϴ�.");
	}	//�޼��� ���
	else
	{
		gotoxy(38, 6);
		printf("�鵹���� %d �� ����", sequence);
		gotoxy(40, 8);
		printf("�¸��ϼ̽��ϴ�.");
	}	//�޼��� ���

	gotoxy(38, 10);
	printf("������� ���Ͻó���?");
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
			}	//���� ���� �ʱ�ȭ

			main();

		case 50:
			SetColor(White, Black);
			system("cls");
			gotoxy(26, 13);
			printf("�ȳ��� ������.\n\n\n\n\n\n\n\n\n\n");
			exit(0);
		}
	}
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y }; //x, y ��ǥ ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //Ŀ�� ����
}

void pointermove(int x, int y)
{
	gotoxy(x, y);
	SetColor(Black, Brown);
	if (omok[y][x / 2] == 5)
		printf("�� ");
	else if (omok[y][x / 2] == 51)
		printf("�� ");
	else if (omok[y][x / 2] == 52)
		printf("�� ");
	else if (omok[y][x / 2] == 53)
		printf("�� ");
	else if (omok[y][x / 2] == 54)
		printf("�� ");
	else if (omok[y][x / 2] == 6)
		printf("�� ");
	else if (omok[y][x / 2] == 7)
		printf("�� ");
	else if (omok[y][x / 2] == 8)
		printf("�� ");
	else if (omok[y][x / 2] == 9)
		printf("�� ");
	else if (omok[y][x / 2] == 10)
	{
		SetColor(Red, Brown);
		printf("��");
	}
	else if (omok[y][x / 2] == 11)
		printf("��");
	else if (omok[y][x / 2] == 12)
	{
		SetColor(White, Brown);
		printf("��");
	}
}	// �ٵϵ� ������ ó��

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
}	// ���콺 Ŀ�� ���� �Լ�


void SetColor(int txt, int bg)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), txt + bg * 16);
}	// ���콺 Ŀ�� ��ġ ���� �Լ�