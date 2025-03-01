#include <stdio.h>

#define MAX (20 + 5)
#define INF (0x7fff0000)

int T;

int N;
int MAP[MAX][MAX];

int minAnswer;

void input()
{
	scanf("%d", &N);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = -1;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void calculate(int sr, int sc, int d1, int d2)
{
	int area[MAX][MAX] = { 0 };
	int sum[6] = { 0 };
	int min, max;
	int start, end, left, right;

	start = end = sc;
	left = -1;
	right = 1;

	// 1번 구역
	for (int r = sr; r <= sr + d1 + d2; r++)
	{
		for (int c = start; c <= end; c++) area[r][c] = 1;

		start += left;
		end += right;

		if (start == sc - d1) left = 1;
		if (end == sc + d2) right = -1;
	}

	// 2번 구역
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (area[r][c] == 1) break;

			if ((1 <= r && r <= sr + d1 - 1) && (1 <= c && c <= sc)) area[r][c] = 2;
		}
	}

	// 3번 구역
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (area[r][c] == 1) continue;

			if ((1 <= r && r <= sr + d2) && (sc + 1 <= c && c <= N)) area[r][c] = 3;
		}
	}

	// 4번 구역
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (area[r][c] == 1) break;

			if ((sr + d1 <= r && r <= N) && (1 <= c && c <= sc - d1 + d2 - 1)) area[r][c] = 4;
		}
	}

	// 5번 구역
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (area[r][c] == 1) continue;

			if ((sr + d2 + 1 <= r && r <= N) && (sc - d1 + d2 <= c && c <= N)) area[r][c] = 5;
		}
	}

	//for debug
	//printMap(area);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			sum[area[r][c]] += MAP[r][c];

	min = INF;
	max = -INF;
	for (int i = 1; i <= 5; i++)
	{
		if (sum[i] < min) min = sum[i];
		if (sum[i] > max) max = sum[i];
	}

	if ((max - min) < minAnswer) minAnswer = max - min;
}

void simulate()
{
	for (int r = 1; r <= N - 2; r++)
	{
		for (int c = 2; c <= N - 1; c++)
		{
			int d1 = 1;
			while (1)
			{
				if (MAP[r + d1][c - d1] == -1) break;

				int d2 = 1;
				while (1)
				{
					if (MAP[r + d2][c + d2] == -1 || MAP[r + d1 + d2][c + d2 - d1] == -1) break;

					calculate(r, c, d1, d2);

					d2++;
				}

				d1++;
			}
		}
	}
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		minAnswer = INF;

		simulate();

		printf("%d\n", minAnswer);
	}

	return 0;
}