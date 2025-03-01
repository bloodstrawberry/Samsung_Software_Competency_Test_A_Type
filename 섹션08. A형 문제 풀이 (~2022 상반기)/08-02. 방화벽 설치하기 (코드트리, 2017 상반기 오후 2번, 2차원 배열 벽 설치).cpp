#include <stdio.h>

#define MAX (8 + 3)

#define EMPTY (0)
#define WALL (1)
#define FIRE (2)

int T;

int N, M;
int MAP[MAX][MAX];
int tmpMAP[MAX][MAX];

int num_of_cases[5];

int maxAnswer;

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

RC emptyRoom[MAX * MAX];
int emptyCount;

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void copyMAP(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			copy[r][c] = original[r][c];
}

void BFS()
{
	copyMAP(tmpMAP, MAP);

	int rp, wp;

	rp = wp = 0;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (tmpMAP[r][c] == FIRE)
			{
				queue[wp].r = r;
				queue[wp++].c = c;
			}
		}
	}

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > M) continue;
			if (tmpMAP[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			tmpMAP[nr][nc] = FIRE;
		}
	}
}

int countEmpty()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			sum += !tmpMAP[r][c];

	return sum;
}

void DFS(int depth, int sr)
{
	// printMap()

	if (depth == 3)
	{
		// printCases();

		BFS();

		int tmp = countEmpty();
		if (maxAnswer < tmp) maxAnswer = tmp;

		return;
	}

	for (int r = sr; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (MAP[r][c] != EMPTY) continue;

			MAP[r][c] = WALL;
			DFS(depth + 1, r);
			MAP[r][c] = EMPTY;
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

		// setEmptyCount();

		maxAnswer = 0;

		DFS(0, 1);

		printf("%d\n", maxAnswer);
	}

	return 0;
}