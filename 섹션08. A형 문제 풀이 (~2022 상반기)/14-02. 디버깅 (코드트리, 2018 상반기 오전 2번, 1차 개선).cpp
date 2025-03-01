#include <stdio.h>

#define MAX_H (30 + 5)
#define MAX_N (10 + 5)

int T;

int C, M, R; // N = C, H = R
int MAP[MAX_H][MAX_N];
int tmpMAP[MAX_H][MAX_N];

int num_of_cases[MAX_H * MAX_N];

struct RC
{
	int r;
	int c;
};

RC ladder[MAX_H * MAX_N];
int lcnt;

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

void printCases()
{
	for (int i = 0; i < lcnt; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

bool check(int setup)
{
	copyMap(tmpMAP, MAP);

	// setup만큼 사다리 설치 
	for (int i = 0; i < setup; i++)
	{
		int r, c;

		r = ladder[num_of_cases[i]].r;
		c = ladder[num_of_cases[i]].c;

		tmpMAP[r][c] = 1;
	}

	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			if (tmpMAP[r][c] == 1 && tmpMAP[r][c + 1] == 1)
				return false;

	int start[MAX_N] = { 0 };
	for (int c = 1; c <= C; c++) start[c] = c;

	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
		{
			if (tmpMAP[r][c] == 0) continue;

			int tmp = start[c];
			start[c] = start[c + 1];
			start[c + 1] = tmp;
		}
	}

	for (int c = 1; c <= C; c++)
		if (start[c] != c) return false;

	return true;
}

void DFS(int depth, int start, int setup)
{
	if (depth == setup)
	{
		// printCases();

		if (check(setup) == true) PASS = true;

		return;
	}

	for (int i = start; i < lcnt; i++)
	{
		num_of_cases[depth] = i;

		DFS(depth + 1, i + 1, setup);
	}
}

int simulate()
{
	if (check(0) == true) return 0;

	for (int setup = 1; setup <= 3; setup++)
	{
		DFS(0, 0, setup);

		if (PASS == true) return setup;
	}

	return -1;
}

void getEmptyLadder()
{
	lcnt = 0;
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C - 1; c++)
		{
			if ((MAP[r][c] == 0 && MAP[r][c + 1] == 0) 
				&& (MAP[r][c] == 0 && MAP[r][c - 1] == 0))
			{
				ladder[lcnt].r = r;
				ladder[lcnt++].c = c;
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

		getEmptyLadder();

		PASS = false;

		printf("%d\n", simulate());
	}

	return 0;
}