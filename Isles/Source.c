#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

char matrix[8][8];
int data_h[8][4];
int data_v[8][4];
int N;

//in out
void input(void);
void output(void);
//


int main(void)
{
	input();


	return 0;
}

void input(void)
{
	printf("������� N: ");
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
	}
}

void output(void)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}
}