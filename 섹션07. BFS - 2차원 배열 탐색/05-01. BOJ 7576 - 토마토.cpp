#include <stdio.h>

#define MAX (1000 + 100)

int M, N;
int MAP[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d", &M, &N);

	// 주변을 빈 상자 (-1)로 처리
	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= M + 1; c++)
			MAP[r][c] = -1;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%2d ", MAP[r][c]);
		putchar('\n');
	}
}

void BFS()
{
	int rp, wp;

	rp = wp = 0;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (MAP[r][c] == 1)
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

			// (0, 0) 부터 (N + 1, M + 1)까지 -1로 초기화 한 경우 생략 가능
			// if (nr < 1 || nc < 1 || nr > N || nc > M) continue;
			if (MAP[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			MAP[nr][nc] = MAP[out.r][out.c] + 1;
		}
	}
}

int getAnswer()
{
	int maxAnswer = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (MAP[r][c] == 0) return -1;
			if (maxAnswer < MAP[r][c]) maxAnswer = MAP[r][c];
		}
	}

	return maxAnswer - 1;
}

int main()
{
	input();

	BFS();

	printf("%d\n", getAnswer());

	return 0;
}