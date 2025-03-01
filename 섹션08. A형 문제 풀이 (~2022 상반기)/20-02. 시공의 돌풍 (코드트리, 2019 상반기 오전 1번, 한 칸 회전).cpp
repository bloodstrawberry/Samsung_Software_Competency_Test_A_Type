#include <stdio.h>

#define MAX (50 + 10)
#define TORNADO_POSITION (-1)

int T;
int N, M, time;
int MAP[MAX][MAX];
int tmpMAP[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC tornado[2];
int tcnt;

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &time);

	tcnt = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			scanf("%d", &MAP[r][c]);

			if (MAP[r][c] == TORNADO_POSITION)
			{
				tornado[tcnt].r = r;
				tornado[tcnt++].c = c;
			}
		}
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
}

void diffusion()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			tmpMAP[r][c] = 0;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (MAP[r][c] <= 0) continue;

			int dust, count;

			dust = count = 0;
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (nr < 1 || nc < 1 || nr > N || nc > M) continue;
				if (MAP[nr][nc] == TORNADO_POSITION) continue;

				dust = MAP[r][c] / 5;

				tmpMAP[nr][nc] += dust;
				count++;
			}

			MAP[r][c] -= (dust * count);
		}
	}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			MAP[r][c] += tmpMAP[r][c];
}

void cleaning()
{
	int up_r = tornado[0].r;
	int down_r = tornado[1].r;

	// (1, 1) ~ (up_r , C)의 반시계 방향 회전
	for (int r = up_r - 1; r > 1; r--) MAP[r][1] = MAP[r - 1][1];
	for (int c = 1; c <= M - 1; c++) MAP[1][c] = MAP[1][c + 1];
	for (int r = 1; r <= up_r - 1; r++) MAP[r][M] = MAP[r + 1][M];
	for (int c = M; c > 1; c--) MAP[up_r][c] = MAP[up_r][c - 1];

	MAP[up_r][2] = 0;

	// (down_r, 1) ~ (R, C)의 시계 방향 회전
	for (int r = down_r + 1; r <= N - 1; r++) MAP[r][1] = MAP[r + 1][1];
	for (int c = 1; c <= M - 1; c++) MAP[N][c] = MAP[N][c + 1];
	for (int r = N; r > down_r; r--) MAP[r][M] = MAP[r - 1][M];
	for (int c = M; c > 1; c--) MAP[down_r][c] = MAP[down_r][c - 1];

	MAP[down_r][2] = 0;
}

int getAnswer()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			if (MAP[r][c] != TORNADO_POSITION) sum += MAP[r][c];

	return sum;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		for (int t = 0; t < time; t++)
		{
			diffusion();
			cleaning();
			// printMap();
		}

		printf("%d\n", getAnswer());
	}

	return 0;
}