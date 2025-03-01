#include <stdio.h>

#define MAX_N (50 + 5)
#define MAX_M (10 + 3)

#define INF (0x7fff0000)

#define VIRUS (0)
#define WALL (1)
#define HOSPITAL (2)

int T;

int N, M;
int MAP[MAX_N][MAX_N];
int tmpMAP[MAX_N][MAX_N];

int num_of_cases[MAX_M];

int minAnswer;

struct RC
{
	int r;
	int c;
};

RC queue[MAX_N * MAX_N];

RC hospital[MAX_M];
int hcnt;

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);

	// 전처리
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] == WALL) MAP[r][c] = -1;
			else if (MAP[r][c] == HOSPITAL)
			{
				hospital[hcnt].r = r;
				hospital[hcnt++].c = c;

				MAP[r][c] = -2;
			}
		}
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", tmpMAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void copyMAP(int copy[MAX_N][MAX_N], int original[MAX_N][MAX_N])
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			copy[r][c] = original[r][c];
}

void printCases()
{
	for (int i = 0; i < 3; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

bool checkVirus()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			if (tmpMAP[r][c] == VIRUS) return true;

	return false;
}

void BFS()
{
	copyMAP(tmpMAP, MAP);
	
	for (int i = 0; i < M; i++)
	{
		int hr, hc;
		int index = num_of_cases[i];

		hr = hospital[index].r;
		hc = hospital[index].c;

		tmpMAP[hr][hc] = 1;
	}


	int rp, wp;

	rp = wp = 0;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (tmpMAP[r][c] == 1)
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

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

			if (tmpMAP[nr][nc] == 0)
			{
				queue[wp].r = nr;
				queue[wp++].c = nc;

				tmpMAP[nr][nc] = tmpMAP[out.r][out.c] + 1;
			}
			else if(tmpMAP[nr][nc] == -2) 
			{
				if (checkVirus() == true)
				{
					queue[wp].r = nr;
					queue[wp++].c = nc;

					tmpMAP[nr][nc] = tmpMAP[out.r][out.c] + 1;
				}
			}
		}
	}
}

int getAnswer()
{
	int max = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (tmpMAP[r][c] == 0) return INF;
			if (max < tmpMAP[r][c]) max = tmpMAP[r][c];
		}
	}

	return max - 1;
}

void DFS(int depth, int start)
{
	if (depth == M)
	{
		// printCases();

		BFS();

		int tmp = getAnswer();
		if (tmp < minAnswer) minAnswer = tmp;

		return;
	}

	for (int i = start; i < hcnt; i++)
	{
		num_of_cases[depth] = i;

		DFS(depth + 1, i + 1);
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

		DFS(0, 0);

		if (minAnswer == INF) printf("-1\n");
		else printf("%d\n", minAnswer);
	}

	return 0;
}