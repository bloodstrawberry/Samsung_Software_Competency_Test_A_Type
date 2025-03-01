#include <stdio.h>

#define MAX (100 + 20)

int T;

int R, C, K;
int MAP[MAX][MAX];

struct GRID
{
	int value;
	int count;
};

GRID grid[MAX];

void input()
{
	scanf("%d %d %d", &R, &C, &K);

	for (int r = 1; r <= 3; r++)
		for (int c = 1; c <= 3; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap(int row, int col) // for debug
{
	printf("row :%d, col : %d\n", row, col);
	for (int r = 1; r <= row; r++)
	{
		for (int c = 1; c <= col; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

int makeArrayRow(int row, int col)
{
	int count[MAX] = { 0 };
	int number[MAX] = { 0 };
	int ncnt;

	ncnt = 0;
	for (int c = 1; c <= col; c++)
	{
		if (MAP[row][c] == 0) continue;

		int value = MAP[row][c];
		if (count[value] == 0) number[ncnt++] = value;
		
		count[value]++;
	}

	for (int i = 0; i < ncnt; i++)
	{
		int value = number[i];

		grid[i].value = value;
		grid[i].count = count[value];
	}

	for (int i = 0; i < ncnt - 1; i++)
	{
		for (int k = i + 1; k < ncnt; k++)
		{
			if ((grid[i].count > grid[k].count)
				|| ((grid[i].count == grid[k].count) && (grid[i].value > grid[k].value)))
			{
				GRID tmp = grid[i];
				grid[i] = grid[k];
				grid[k] = tmp;
			}
		}
	}

	int index = 1;
	for (int i = 0; i < ncnt; i++)
	{
		MAP[row][index++] = grid[i].value;
		MAP[row][index++] = grid[i].count;

		// 배열이 100을 넘어가는 경우
		// if (index == 101) break;
	}

	for (int i = index; i <= col; i++) MAP[row][i] = 0;
	
	return index - 1;
}

void transpose(int row, int col)
{
	int maxLength = row > col ? row : col;
	for (int r = 1; r <= maxLength - 1; r++)
	{
		for (int c = r + 1; c <= maxLength; c++)
		{
			int tmp = MAP[r][c];
			MAP[r][c] = MAP[c][r];
			MAP[c][r] = tmp;
		}
	}
}

int simulate()
{
	if (MAP[R][C] == K) return 0;

	int lenR, lenC;

	lenR = lenC = 3;
	for (int i = 1; i <= 100; i++)
	{
		if (lenR >= lenC)
		{
			for (int r = 1; r <= lenR; r++)
			{
				int length = makeArrayRow(r, lenC);
				if (lenC < length) lenC = length;
			}
		}
		else
		{
			int tmp;

			transpose(lenR, lenC);

			tmp = lenR;
			lenR = lenC;
			lenC = tmp;

			for (int r = 1; r <= lenR; r++)
			{
				int length = makeArrayRow(r, lenC);
				if (lenC < length) lenC = length;
			}

			tmp = lenR;
			lenR = lenC;
			lenC = tmp;

			transpose(lenR, lenC);
		}

		if (MAP[R][C] == K) return i;
	}

	return -1;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		printf("%d\n", simulate());
	}

	return 0;
}