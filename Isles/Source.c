#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

char seamap[8][8];
int data_h[8][5];
int data_v[8][5];
int isles_left;
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

//core
void map_building(int tilenum);
void place(int y, int x);
void delete_last(int num);

void clean_hash(void);
void check(void);
void ban_cross_check(int y, int x);
void ban_row(int y);
void ban_column(int x);

bool sum(int index);
bool check_sum(void);
bool sea_check(int index);
//

//setup
void set_seamap(void);
bool set_figures_left(void);
//

int main(void)
{
	rus();
	input();
	if (!set_figures_left())
	{
		printf("no solutions");
		return 0;
	}
	set_seamap();
	map_building(0);


	return 0;
}

bool set_figures_left(void)
{
	int rows = 0; int columns = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < N; j++)
		{
			rows += data_h[j][i];
			columns += data_v[j][i];
		}
	}
	if (rows == columns)
	{
		isles_left = rows;
		return 1;
	}
	else
	{
		return 0;
	}
}
void set_seamap(void)
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			seamap[y][x] = ' ';
		}
	}
}


void map_building(int tilenum)
{
	int counter = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if ((counter >= tilenum) && (seamap[i][j] == ' '))
			{
				tilenum = counter;
				place(i, j);
				if (!isles_left)
				{
					if(check_sum())
						print();
					//output();
					delete_last(tilenum);
				}
				else
				{
					map_building(tilenum);
					delete_last(tilenum);
				}
			}
			counter++;
		}
	}
}
void place(int y, int x)
{
	seamap[y][x] = '*';
	isles_left--;
	//print();
	check();
	//print();
}
void delete_last(int num)
{
	int counter = 0;
	int flag = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (counter == num)
			{
				seamap[i][j] = ' ';
				//print();
				check();
			}
			counter++;
		}
	}
	//	print();
	isles_left++;
}


void clean_hash(void)
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			if (seamap[y][x] == '#')
				seamap[y][x] = ' ';
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
		if (seamap[i][x] == '*')
			column++;
		if (seamap[y][i] == '*')
			row++;
	}

	int vert = 0;
	int hor = 0;
	for (int i = 0; i < 5; i++)
	{
		hor += data_h[y][i];
		vert += data_v[x][i];
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
		if (seamap[y][i] == ' ')
			seamap[y][i] = '#';
	}
}
void ban_column(int x)
{
	for (int i = 0; i < N; i++)
	{
		if (seamap[i][x] == ' ')
			seamap[i][x] = '#';
	}
}


bool check_sum(void)
{
	for (int i = 0; i < N; i++)
	{
		if ((!sum(i)) || (!sea_check(i)))
		{
			return false;
		}
	}
	return true;
}
bool sum(int index)
{
	int column = 0;
	int row = 0;
	for (int i = 0; i < N; i++)
	{
		if (seamap[i][index] == '*')
			column++;
		if (seamap[index][i] == '*')
			row++;
	}

	int vert = 0;
	int hor = 0;
	for (int i = 0; i < 5; i++)
	{
		hor += data_h[index][i];
		vert += data_v[index][i];
	}

	if (vert != column) return false;
	if (hor != row)return false;
}
bool sea_check(int index)
{
	int k = 0;
	for (int j = 0; j < N; j++)
	{
		int adjacent_points = 0;
		if (seamap[index][j] == '*')
		{
			while (seamap[index][j] == '*')
			{
				adjacent_points++;
				j++;
			}
			if (adjacent_points != data_h[index][k])
				return false;
			k++;
		}
	}
	int i = 0;
	for (int j = 0; j < N; j++)
	{
		int adjacent_points = 0;
		if (seamap[j][index] == '*')
		{
			while (seamap[j][index] == '*')
			{
				adjacent_points++;
				j++;
			}
			if (adjacent_points != data_v[index][i])
				return false;
			i++;
		}
	}
	
	return true;
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
	clean_hash();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("(%c)", seamap[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	getchar();
}

void rus(void)
{
	system("chcp 1251");
	system("cls");
}