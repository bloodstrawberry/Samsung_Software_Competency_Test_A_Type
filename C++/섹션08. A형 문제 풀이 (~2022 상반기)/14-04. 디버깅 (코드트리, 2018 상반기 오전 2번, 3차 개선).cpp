#include <stdio.h>

#define MAX_H (30 + 5)
#define MAX_N (10 + 5)

int T;

int C, M, R; // N = C, H = R
int MAP[MAX_H][MAX_N];

bool PASS;

void input()
{
	scanf("%d %d %d", &C, &M, &R);

	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			MAP[r][c] = 0;

	for (int i = 0; i < M; i++)
	{
		int r, c;

		scanf("%d %d", &r, &c);

		MAP[r][c] = 1;
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void copyMap(int copy[MAX_H][MAX_N], int original[MAX_H][MAX_N])
{
	for (int i = 1; i <= R; i++)
		for (int k = 1; k <= C; k++)
			copy[i][k] = original[i][k];
}

bool check()
{
	int start[MAX_N] = { 0 };
	for (int c = 1; c <= C; c++) start[c] = c;

	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			if (MAP[r][c] == 0) continue;

			int tmp = start[c];
			start[c] = start[c + 1];
			start[c + 1] = tmp;
		}
	}

	for (int c = 1; c <= C; c++)
		if (start[c] != c) return false;

	return true;
}

void DFS(int depth, int setup)
{
	if (depth == setup)
	{
		// printCases();

		if (check() == true) PASS = true;

		return;
	}

	for (int c = 1; c <= C - 1; c++)
	{
		for (int r = 1; r <= R; r++)
		{
			if (MAP[r][c] == 1 || MAP[r][c + 1] == 1 || MAP[r][c - 1] == 1) continue;

			MAP[r][c] = 1;
			DFS(depth + 1, setup);
			MAP[r][c] = 0;

			// 설치된 사다리 아래의 양 옆에 사다리가 없다면, 같은 결과이기 때문에 무시
			while (r <= R && MAP[r][c - 1] == 0 && MAP[r][c + 1] == 0) r++;
		}
	}
}

int simulate()
{
	if (check() == true) return 0;

	for (int setup = 1; setup <= 3; setup++)
	{
		DFS(0, setup);

		if (PASS == true) return setup;
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

		// getEmptyLadder();

		PASS = false;

		printf("%d\n", simulate());
	}

	return 0;
}