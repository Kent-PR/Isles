#define _CRT_SECURE_NO_WARNINGS
#define XC 1
#define YC 0

#include <stdio.h>
#include <stdbool.h>

char seamap[8][8];
int rows_data[8][5];
int columns_data[8][5];
int islands_left;

int Y[64] = { -1 }; int X[64] = { -1 };
int last_error_coords[2];

int N;

//in out
void input(void);
void create_data(FILE* fin);
FILE* opening(void);
void set_map(void);
void output(void);
void coord_set(void);
//

//file
FILE* opening(void);
//

//tmp func
void create_data(FILE* fin);
//void rus(void);
int islands_count(void);
//

//logics func
void all_maps_logiks(void);
bool map_build_logics(void);
void place(int y, int x, int num);
bool error_check(int y, int x);
bool free_place(int num);
int get_num(int y, int x);
bool free_islands(int islands);
int islands_count(void);

void identification_of_complete(void);
void full_row(void);
void full_column(void);
void ban_row(int num);
void ban_column(int num);
void clear_hash(void);
void local_hash(void);

void settings(int num);
void set_ban(int num);
void set_error_coord(void);
//

//debug
void full_field(void);
//

int main(void)
{
	//rus();
	input();
	set_map();

	all_maps_logiks();
	return 0;
}


void identification_of_complete(void)
{
	clear_hash();
	full_row();
	full_column();
	//local_hash();
}
void full_row(void)
{
	for (int i = 0; i < N; i++)
	{
		int sum = 0;
		for (int j = 0; j < 5; j++)
		{
			sum += rows_data[i][j];
		}
		int isl_cnt = 0;
		for (int j = 0; j < N; j++)
		{
			if (seamap[i][j] == '*')
				isl_cnt++;
		}
		if (sum <= isl_cnt)
		{
			ban_row(i);
		}
	}
}
void full_column(void)
{
	for (int j = 0; j < N; j++)
	{
		int sum = 0;
		for (int i = 0; i < 5; i++)
		{
			sum += columns_data[j][i];
		}
		int isl_cnt = 0;
		for (int i = 0; i < N; i++)
		{
			if (seamap[i][j] == '*')
				isl_cnt++;
		}
		if (sum <= isl_cnt)
		{
			ban_column(j);
		}
	}
}
void ban_row(int num)
{
	for (int j = 0; j < N; j++)
	{
		if (seamap[num][j] == ' ')
		{
			seamap[num][j] = '#';
		}
	}
}
void ban_column(int num)
{
	for (int i = 0; i < N; i++)
	{
		if (seamap[i][num] == ' ')
		{
			seamap[i][num] = '#';
		}
	}
}
void clear_hash(void)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (seamap[i][j] == '#') seamap[i][j] = ' ';
		}
	}
}
void local_hash(void)
{
	for (int y = 0; y < N; y++)
	{
		int block;
		for (int i = 0; i < 5; i++)
		{
			block = rows_data[y][i];
			if (!block) break;

			for (int j = 0; j < N; j++)
			{
				if ((seamap[y][j] == '*') && ((block + j) < N))
				{
					seamap[y][j + block] = '#';
				}
			}
		}
	}

	for (int x = 0; x < N; x++)
	{
		int block;
		for (int i = 0; i < 5; i++)
		{
			block = columns_data[x][i];
			if (!block) break;
			
			for (int j = 0; j < N; j++)
			{
				if ((seamap[j][x] == '*') && ((j+block)<N))
				{
					seamap[j + block][x] = '#';
				}
			}
		}
	}
}


void delete_last(void)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (seamap[i][j] == 'e')
			{
				seamap[i][j] = ' ';
			}
		}
	}

	for (int i = 63; i >= 0; i--)
	{
		if (X[i] != -1)
		{
			seamap[Y[i]][X[i]] = 'e';
			last_error_coords[XC] = X[i];
			last_error_coords[YC] = Y[i];
			X[i] = -1; Y[i] = -1;
			break;
		}
	}
	islands_left++;
	identification_of_complete();
}
bool exist_last()
{
	if (X[0] == -1) return false;
	else return true;
}


void all_maps_logiks(void)
{
	int islands = islands_count();
	int map_counter = 0;
	bool flag = false;
	while (1)
	{
		settings(map_counter);

		if (map_build_logics())
		{
			flag = true;
			output();
		}
		map_counter++;
		if (map_counter >= (N * N)) break;
		
	}
	if (!flag) printf("no map");
}
bool map_build_logics(void)
{
	islands_left = islands_count();
	bool unfinished_map_flag = free_islands(islands_left);
	while (1) 
	{
		unfinished_map_flag = free_islands(islands_left);
		if (!unfinished_map_flag) 
			return true;
		//
		identification_of_complete();
		//
		bool placed = free_place(islands_count() - islands_left);

		if(!placed)
		{
			if (exist_last())
			{
				delete_last();
			}
			else
			{
				return false;
			}
		}
	}
}
void place(int y, int x,int num)
{
	islands_left--;
	seamap[y][x] = '*';
	X[num] = x;
	Y[num] = y;
}
bool free_place(int num)
{
	int error_tile_num = get_num(last_error_coords[YC], last_error_coords[XC]);
	for (int y = last_error_coords[YC]; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			int current_tile_num = get_num(y, x);
			if ((seamap[y][x] != '#') && (seamap[y][x] != '*') && (seamap[y][x] != '@') && (seamap[y][x] != 'e') && (current_tile_num >= error_tile_num))
			{
				place(y, x, num);
				return error_check(y, x);
			}
		}
	}
	return false;
}
int get_num(int y, int x)
{
	int num = y * N + x;
	return num;
}
bool error_check(int y, int x) 
{
	int isl_cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (!rows_data[y][isl_cnt]) break;
		if (seamap[y][i] == '*')
		{
			if (seamap[y][i + rows_data[y][isl_cnt]] == '*')
				return false;
			isl_cnt++;
			i = i + rows_data[y][isl_cnt] - 1;
		}
	}
	isl_cnt = 0;
	for (int j = 0; j < N; j++)
	{
		if (!columns_data[x][isl_cnt]) break;
		if (seamap[j][x] == '*')
		{
			if (seamap[j + columns_data[x][isl_cnt]][x] == '*')
				return false;
			isl_cnt++;
			j = j + columns_data[x][isl_cnt] - 1;
		}
	}
	return true;
}
bool free_islands(int islands)
{
	if (islands)
	{
		return 1;
	}
	else return 0;
}
int islands_count(void)
{
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			sum += rows_data[i][j];
		}
	}
	return sum;
}
void set_ban(int num)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!num) break;
			seamap[i][j] = '@';
			num--;
		}
		if (!num) break;
	}
}
void set_error_coord(void)
{
	last_error_coords[YC] = 0;
	last_error_coords[XC] = 0;
}
void settings(int map_counter)
{
	set_error_coord();
	set_map();
	coord_set();
	set_ban(map_counter);
}

void full_field(void)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			seamap[i][j] = (i * j) % 10 + 48;
		}
	}
}


//void rus(void)
//{
//	system("chcp 1251");
//	system("cls");
//}


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
					rows_data[counter][i] = c-48;
					i++;
				}
				else
				{
					columns_data[counter-N][i] = c-48;
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
	char name[100];//отводим массив под им€ файла.
	printf("Enter file name: ");
	gets(name);
	FILE* file_in = fopen(name, "r");

	while (file_in == NULL)// если файл не открылс€.
	{
		printf("Error in file name!\n");
		printf("Enter file name: ");
		gets(name);
		file_in = fopen(name, "r");
	}
	return file_in;//возвращаем указатель на поток.
}
void input(void)
{
	create_data(opening());

	/*printf("¬ведите N: ");
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
void set_map(void)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			seamap[i][j] = ' ';
		}
	}
}
void coord_set(void)
{
	for (int i = 0; i < 64; i++)
	{
		X[i] = -1;
		Y[i] = -1;
	}
}


void output(void)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (seamap[i][j] != '*') seamap[i][j] = ' ';
			printf("(%c)", seamap[i][j]);
		}
		printf("\n");
	}
	getchar();
}