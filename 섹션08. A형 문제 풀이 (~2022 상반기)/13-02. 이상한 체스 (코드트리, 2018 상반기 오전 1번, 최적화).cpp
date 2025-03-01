#include <stdio.h>

#define MAX (8 + 5)
#define INF (0x7fff0000)

#define EMPTY (0)
#define OTHER (6) // 상대편 말
#define MARK (7)

int T;

int N, M;
int MAP[MAX][MAX];
int tmpMAP[MAX][MAX];

int num_of_cases[MAX];

struct CHESS
{
	int r;
	int c;
	int number;
};

CHESS chess[8 + 2];
CHESS chess5[8 + 2];
int cidx, cidx5;

int minAnswer;

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= M + 1; c++)
			MAP[r][c] = OTHER; /* 벽 */

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%d", &MAP[r][c]);

	cidx = cidx5 = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (MAP[r][c] == EMPTY || MAP[r][c] == OTHER) continue;

			if (MAP[r][c] == 5)
			{
				chess5[cidx5].r = r;
				chess5[cidx5].c = c;
				chess5[cidx5++].number = MAP[r][c];
			}
			else
			{
				chess[cidx].r = r;
				chess[cidx].c = c;
				chess[cidx++].number = MAP[r][c];
			}
		}
	}
}

void printMap() // for debug
{
	for (int r = 0; r <= N + 1; r++)
	{
		for (int c = 0; c <= M + 1; c++)
			printf("%d ", tmpMAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void copyMap(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int i = 0; i <= N + 1; i++) 
		for (int k = 0; k <= M + 1; k++)
			copy[i][k] = original[i][k];
}

void printCases()
{
	for (int i = 0; i < cidx; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

void checkArea(int map[MAX][MAX], int sr, int sc, int direction)
{
	int r, c;

	r = sr;
	c = sc;
	while (1)
	{
		r = r + dr[direction];
		c = c + dc[direction];

		if (map[r][c] == OTHER) return;

		map[r][c] = MARK;
	}
}

void simulate()
{
	copyMap(tmpMAP, MAP);

	for (int i = 0; i < cidx; i++)
	{
		int sr = chess[i].r;
		int sc = chess[i].c;
		int chessNumber = chess[i].number;
		int direction = num_of_cases[i];

		if (chessNumber == 1)
		{
			checkArea(tmpMAP, sr, sc, direction);
		}
		else if (chessNumber == 2)
		{
			int inverse = direction + 2;
			if (inverse > 3) inverse -= 4;

			checkArea(tmpMAP, sr, sc, direction);
			checkArea(tmpMAP, sr, sc, inverse);
		}
		else if (chessNumber == 3)
		{
			int nextDir = direction + 1;
			if (nextDir == 4) nextDir = 0;

			checkArea(tmpMAP, sr, sc, direction);
			checkArea(tmpMAP, sr, sc, nextDir);
		}
		else if (chessNumber == 4)
		{
			for (int i = 0; i < 4; i++)
			{
				if (i == direction) continue;

				checkArea(tmpMAP, sr, sc, i);
			}
		}
	}
}

int getArea()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			sum += !tmpMAP[r][c];

	return sum;
}

void DFS(int depth)
{
	if (depth == cidx)
	{
		// printCases();

		simulate();

		// printMap();

		int tmp = getArea();
		if (tmp < minAnswer) minAnswer = tmp;

		return;
	}

	for (int i = 0; i < 4; i++)
	{
		num_of_cases[depth] = i;

		DFS(depth + 1);
	}
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		for (int i = 0; i < cidx5; i++)
		{
			int sr = chess5[i].r;
			int sc = chess5[i].c;

			checkArea(MAP, sr, sc, 0);
			checkArea(MAP, sr, sc, 1);
			checkArea(MAP, sr, sc, 2);
			checkArea(MAP, sr, sc, 3);
		}


		minAnswer = INF;

		DFS(0);

		printf("%d\n", minAnswer);
	}

	return 0;
}