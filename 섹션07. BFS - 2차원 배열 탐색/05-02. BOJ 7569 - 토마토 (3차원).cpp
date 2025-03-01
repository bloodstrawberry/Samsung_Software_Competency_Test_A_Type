#include <stdio.h>

#define MAX (100 + 10)

int M, N, H;
int MAP[MAX][MAX][MAX];

struct HRC
{
	int h;
	int r;
	int c;
};

HRC queue[MAX * MAX * MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &M, &N, &H);

	for (int h = 0; h <= H + 1; h++)
		for (int r = 0; r <= N + 1; r++)
			for (int c = 0; c <= M + 1; c++)
				MAP[h][r][c] = -1;

	for (int h = 1; h <= H; h++)
		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= M; c++)
				scanf("%d", &MAP[h][r][c]);
}

void printMap()
{
	for (int h = 0; h <= H + 1; h++)
	{
		printf("h : %d\n", h);
		for (int r = 0; r <= N + 1; r++)
		{
			for (int c = 0; c <= M + 1; c++)
				printf("%d ", MAP[h][r][c]);
			putchar('\n');
		}
		putchar('\n');
	}
}

void BFS()
{
	int rp, wp;

	rp = wp = 0;

	for (int h = 1; h <= H; h++)
	{
		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= M; c++)
			{
				if (MAP[h][r][c] == 1)
				{
					queue[wp].h = h;
					queue[wp].r = r;
					queue[wp++].c = c;
				}
			}
		}
	}

	while (rp < wp)
	{
		HRC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			// (0, 0, 0) 부터 (H + 1, N + 1, M + 1)까지 -1로 초기화 한 경우 생략 가능
			// if (nr < 1 || nc < 1 || nr > N || nc > M) continue;
			if (MAP[out.h][nr][nc] != 0) continue;

			queue[wp].h = out.h;
			queue[wp].r = nr;
			queue[wp++].c = nc;

			MAP[out.h][nr][nc] = MAP[out.h][out.r][out.c] + 1;
		}

		// 아래로 가는 상자 (out.h - 1) != 0 조건 삭제 
		if (MAP[out.h - 1][out.r][out.c] == 0)
		{
			queue[wp].h = out.h - 1;
			queue[wp].r = out.r;
			queue[wp++].c = out.c;

			MAP[out.h - 1][out.r][out.c] = MAP[out.h][out.r][out.c] + 1;
		}

		// 위로 가는 상자, (out.h) != H 조건 삭제
		if (MAP[out.h + 1][out.r][out.c] == 0)
		{
			queue[wp].h = out.h + 1;
			queue[wp].r = out.r;
			queue[wp++].c = out.c;

			MAP[out.h + 1][out.r][out.c] = MAP[out.h][out.r][out.c] + 1;
		}
	}
}

int getAnswer()
{
	int maxAnswer = 0;
	for (int h = 1; h <= H; h++)
	{
		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= M; c++)
			{
				if (MAP[h][r][c] == 0) return -1;
				if (maxAnswer < MAP[h][r][c]) maxAnswer = MAP[h][r][c];
			}
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