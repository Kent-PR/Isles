#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

char main_field[8][8];
int data_h[8][5];
int data_v[8][5];
int N;

//in out
void input(void);
void print(void);
//

//file
FILE* opening(void);
//

//tmp
void create_data(FILE* fin);
void rus(void);
//

int main(void)
{
	rus();
	input();


	return 0;
}

void clean_hash(void)
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (main_field[y][x] == '#')
				main_field[y][x] = ' ';
		}
	}
}
void check(void)
{
	clean_hash();
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			ban_cross_check(x, y);
		}
	}
}
void ban_cross_check(int y, int x)
{
	int column = 0;
	int row = 0;
	for (int i = 0; i < N; i++)
	{
		if (main_field[i][x] == '*')
			column++;
		if (main_field[y][i] == '*')
			row++;
	}

	int vert = 0;
	int hor = 0;
	for (int i = 0; i < 5; i++)
	{
		vert += data_h[y][i];
		hor += data_v[x][i];
	}

	if (vert == column)
		ban_column(x);
	if (hor == row)
		ban_row(y);

}
void ban_row(int y)
{
	for (int i = 0; i < N; i++)
	{
		if (main_field[y][i] == ' ')
			main_field[y][i] = '#';
	}
}
void ban_column(int x)
{
	for (int i = 0; i < N; i++)
	{
		if (main_field[i][x] == ' ')
			main_field[i][x] = '#';
	}
}


bool check_sum()
{
	for (int i = 0; i < N; i++)
	{
		if (!sum(i))
			return sum(i);
	}
}
bool sum(int index)
{
	int column = 0;
	int row = 0;
	for (int i = 0; i < N; i++)
	{
		if (main_field[i][index] == '*')
			column++;
		if (main_field[index][i] == '*')
			row++;
	}

	int vert = 0;
	int hor = 0;
	for (int i = 0; i < 5; i++)
	{
		vert += data_h[index][i];
		hor += data_v[index][i];
	}

	if (vert != column) return false;
	if (hor != row)return false;
}


void create_data(FILE* fin)
{
	N = fgetc(fin) - 48;
	fgetc(fin);
	char tmp[4]; int counter = 0;
	char c; int i;
	while ((c = fgetc(fin)) != EOF)
	{
		i = 0;
		while ((c != '\n') && (c != EOF))
		{
			if (c != ' ') 
			{
				if (counter < N)
				{
					data_h[counter][i] = c-48;
					i++;
				}
				else
				{
					data_v[counter-N][i] = c-48;
					i++;
				}
			}
			c = fgetc(fin);
		}
		counter++;
	}
}
FILE* opening(void)
{
	char name[100];//отводим массив под имя файла.
	printf("Ввведите имя файла: ");
	gets(name);
	FILE* file_in = fopen(name, "r");

	while (file_in == NULL)// если файл не открылся.
	{
		printf("Допущена ошибка в имени файла!\n");
		printf("Введите имя файла: ");
		gets(name);
		file_in = fopen(name, "r");
	}
	return file_in;//возвращаем указатель на поток.
}
void input(void)
{
	create_data(opening());

	/*printf("Введите N: ");
	scanf("%d", &N);
	for (int hor = 0; hor < N; hor++)
	{
		int tmp;
		int i = 0;
		while (1)
		{
			scanf("%d", &tmp);
			data_h[hor][i] = tmp;			
			i++;
			if (!tmp) break;
		}
	}

	for (int vert = 0; vert < N; vert++)
	{
		int tmp;
		int i = 0;
		while (1)
		{
			scanf("%d", &tmp);
			data_v[vert][i] = tmp;			
			i++;
			if (!tmp) break;
		}
	}*/
}

void print(void)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%c", main_field[i][j]);
		}
		printf("\n");
	}
}

void rus(void)
{
	system("chcp 1251");
	system("cls");
}