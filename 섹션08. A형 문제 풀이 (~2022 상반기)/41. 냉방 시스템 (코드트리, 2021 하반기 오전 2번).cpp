#include <stdio.h>

#define MAX (20 + 10)

#define OFFICE (1)
#define LEFT (2)
#define UP (3)
#define RIGHT (4)
#define DOWN (5)

int T;

int N, K, W;
int MAP[MAX][MAX];
int temperature[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC office[MAX * MAX];
int ocnt;

struct RCD
{
	int r;
	int c;
	int dir;
};

RCD airConditioner[MAX * MAX];
int acnt;

struct RCL
{
	int r;
	int c;
	int length;
};

RCL queue[MAX * MAX];

struct WALL
{
	bool direction[6];
};

WALL wall[MAX][MAX];

// -, -, ←, ↑, →, ↓
int dr[] = { 0, 0, 0, -1, 0, 1 };
int dc[] = { 0, 0, -1, 0, 1, 0 };

void input()
{
	scanf("%d %d %d", &N, &W, &K);

	ocnt = acnt = 0;
	
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &MAP[r][c]);

			if (MAP[r][c] == OFFICE)
			{
				office[ocnt].r = r;
				office[ocnt++].c = c;
			}
			else if (MAP[r][c] != 0)
			{
				airConditioner[acnt].r = r;
				airConditioner[acnt].c = c;
				airConditioner[acnt++].dir = MAP[r][c];
			}
		}
	}

	for (int w = 0; w < W; w++)
	{
		int r, c, s;

		scanf("%d %d %d", &r, &c, &s);

		if (s == 0)
		{
			wall[r][c].direction[UP] = true;
			wall[r - 1][c].direction[DOWN] = true;
		}
		else // s == 1
		{
			wall[r][c].direction[LEFT] = true;
			wall[r][c - 1].direction[RIGHT] = true;
		}
	}
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void BFS(int r, int c, int dir)
{
	int rp, wp;
	bool visit[MAX][MAX] = { 0 };
	int sr, sc;

	sr = r + dr[dir];
	sc = c + dc[dir];

	rp = wp = 0;

	queue[wp].r = sr;
	queue[wp].c = sc;
	queue[wp++].length = 5;

	visit[sr][sc] = true;
	
	while (rp < wp)
	{
		RCL out = queue[rp++];

		if (out.length == 0) break;

		if (out.r < 1 || out.c < 1 || out.r > N || out.c > N) continue;

		temperature[out.r][out.c] += out.length;

		if (dir == RIGHT || dir == LEFT)
		{
			int nr, nc;

			nc = out.c + dc[dir];

			// ↖ ↗ 위
			nr = out.r - 1;
			if (visit[nr][nc] == false
				// (r, c)와 (r - 1, c) 사이에 벽이 없어야 한다.
				&& (wall[out.r][out.c].direction[UP] == false)
				// (r - 1, c)와 (r - 1, c + dc[dir]) 사이에 벽이 없어야 한다.
				&& (wall[nr][out.c].direction[dir] == false))
			{
				queue[wp].r = nr;
				queue[wp].c = nc;
				queue[wp++].length = out.length - 1;

				visit[nr][nc] = true;
			}

			// ← → 옆
			nr = out.r;
			if (visit[nr][nc] == false
				// (r, c)와 (r, c + dc[dir]) 사이에 벽이 없어야 한다.
				&& (wall[out.r][out.c].direction[dir] == false))
			{
				queue[wp].r = nr;
				queue[wp].c = nc;
				queue[wp++].length = out.length - 1;

				visit[nr][nc] = true;
			}

			// ↙ ↘ 아래
			nr = out.r + 1;
			if (visit[nr][nc] == false
				// (r, c)와 (r + 1, c) 사이에 벽이 없어야 한다.
				&& (wall[out.r][out.c].direction[DOWN] == false)
				// (r + 1, c)와 (r + 1, c + dc[dir]) 사이에 벽이 없어야 한다.
				&& (wall[nr][out.c].direction[dir] == false))
			{
				queue[wp].r = nr;
				queue[wp].c = nc;
				queue[wp++].length = out.length - 1;

				visit[nr][nc] = true;
			}
		}
		else // UP or DOWN
		{
			int nr, nc;

			nr = out.r + dr[dir];

			// ↖ ↙ 왼
			nc = out.c - 1;
			if (visit[nr][nc] == false
				// (r, c)와 (r, c - 1) 사이에 벽이 없어야 한다.
				&& (wall[out.r][out.c].direction[LEFT] == false)
				// (r, c - 1)와 (r + dr[dir], c - 1) 사이에 벽이 없어야 한다.
				&& (wall[out.r][nc].direction[dir] == false))
			{
				queue[wp].r = nr;
				queue[wp].c = nc;
				queue[wp++].length = out.length - 1;

				visit[nr][nc] = true;
			}

			// ↑ ↓ 위, 아래
			nc = out.c;
			if (visit[nr][nc] == false
				// (r, c)와 (r + dr[dir], c) 사이에 벽이 없어야 한다.
				&& (wall[out.r][out.c].direction[dir] == false))
			{
				queue[wp].r = nr;
				queue[wp].c = nc;
				queue[wp++].length = out.length - 1;

				visit[nr][nc] = true;
			}

			// ↗ ↘
			nc = out.c + 1;
			if (visit[nr][nc] == false
				// (r, c)와 (r, c + 1) 사이에 벽이 없어야 한다.
				&& (wall[out.r][out.c].direction[RIGHT] == false)
				// (r, c + 1)와 (r + dr[dir], c + 1) 사이에 벽이 없어야 한다.
				&& (wall[out.r][nc].direction[dir] == false))
			{
				queue[wp].r = nr;
				queue[wp].c = nc;
				queue[wp++].length = out.length - 1;

				visit[nr][nc] = true;
			}
		}
	}
}

void controlTemperature()
{
	int tmpTemp[MAX][MAX] = { 0 };
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (temperature[r][c] == 0) continue;

			int value = temperature[r][c];
			for (int i = 2; i <= 5; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (nr < 1 || nc < 1 || nr > N || nc > N) continue;
				if (wall[r][c].direction[i] == true) continue;

				if (temperature[r][c] > temperature[nr][nc])
				{
					int diff = (temperature[r][c] - temperature[nr][nc]) / 4;

					value -= diff;
					tmpTemp[nr][nc] += diff;
				}
			}

			tmpTemp[r][c] += value;
		}
	}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			temperature[r][c] = tmpTemp[r][c];
}

void decreaseTemperature()
{
	if (temperature[1][1] != 0) temperature[1][1]--;
	if (temperature[N][1] != 0) temperature[N][1]--;
	if (temperature[1][N] != 0) temperature[1][N]--;
	if (temperature[N][N] != 0) temperature[N][N]--;

	for (int r = 2; r <= N - 1; r++)
		if (temperature[r][1] != 0) temperature[r][1]--;

	for (int r = 2; r <= N - 1; r++)
		if (temperature[r][N] != 0) temperature[r][N]--;

	for (int c = 2; c <= N - 1; c++)
		if (temperature[1][c] != 0) temperature[1][c]--;

	for (int c = 2; c <= N - 1; c++)
		if (temperature[N][c] != 0) temperature[N][c]--;
}

bool checkOffice()
{
	for (int i = 0; i < ocnt; i++)
		if (temperature[office[i].r][office[i].c] < K)
			return false;

	return true;
}

int simulate()
{
	int time = 0;
	while (1)
	{
		for (int i = 0; i < acnt; i++)
		{
			int r, c, dir;

			r = airConditioner[i].r;
			c = airConditioner[i].c;
			dir = airConditioner[i].dir;

			BFS(r, c, dir);
		}

		controlTemperature();

		decreaseTemperature();

		time++;
		if (time > 100) return -1;

		if (checkOffice() == true) break;
	}

	return time;
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