#include <stdio.h>

#define MAX (500 + 20)

int T;

int N;
int MAP[MAX][MAX];
int snail[MAX][MAX];

struct RCD
{
	int r;
	int c;
	int dir;
};

RCD track[MAX * MAX];
int tcnt;

// ←, ↓, →, ↑
int dr[] = { 0, 1, 0, -1 };
int dc[] = { -1, 0, 1, 0 };

void input()
{
	scanf("%d", &N);

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

// ←, ↓, →, ↑
int ratio[4][5][5] =
{
	{
		{0,  0, 2, 0, 0},
		{0, 10, 7, 1, 0},
		{5,  0, 0, 0, 0},
		{0, 10, 7, 1, 0},
		{0,  0, 2, 0, 0},
	},
	{
		{0,  0, 0,  0, 0},
		{0,  1, 0,  1, 0},
		{2,  7, 0,  7, 2},
		{0, 10, 0, 10, 0},
		{0,  0, 5,  0, 0},
	},
	{
		{0, 0, 2,  0, 0},
		{0, 1, 7, 10, 0},
		{0, 0, 0,  0, 5},
		{0, 1, 7, 10, 0},
		{0, 0, 2,  0, 0},
	},
	{
		{0,  0, 5,  0, 0},
		{0, 10, 0, 10, 0},
		{2,  7, 0,  7, 2},
		{0,  1, 0,  1, 0},
		{0,  0, 0,  0, 0},
	}
};

void makeSnail()
{
	int sr, sc, direction;
	int index, size;

	sr = sc = (N + 1) / 2;
	direction = 0;
	index = 1;
	size = 0;

	snail[sr][sc] = index++;
	track[tcnt].r = sr;
	track[tcnt++].c = sc;

	for (int i = 0; i < 2 * N - 1; i++)
	{
		if (i % 2 == 0) size++;

		for (int s = 0; s < size; s++)
		{
			int nr, nc;

			nr = sr + dr[direction];
			nc = sc + dc[direction];

			snail[nr][nc] = index++;

			sr = nr;
			sc = nc;

			track[tcnt].r = nr;
			track[tcnt++].c = nc;
		}

		direction++;

		if (direction == 4) direction = 0;
	}

	tcnt = N * N;
	for (int i = 0; i < tcnt - 1; i++)
	{
		int r, c, nr, nc;

		r = track[i].r;
		c = track[i].c;
		nr = track[i + 1].r;
		nc = track[i + 1].c;

		if (nc - c == -1) track[i].dir = 0; // 왼쪽
		else if (nc - c == 1) track[i].dir = 2; // 오른쪽
		else if (nr - r == -1) track[i].dir = 3; // 위쪽
		else if (nr - r == 1) track[i].dir = 1; // 아래쪽
	}

	track[tcnt - 1].dir = 0;
	
	return;
	printMap(snail);
	for (int i = 0; i < tcnt; i++)
		printf("%d] (%d, %d) / %d\n", i, track[i].r, track[i].c, track[i].dir);
}

int clean(int sr, int sc, int dir)
{
	int center = MAP[sr][sc];
	int tmpMAP[5][5] = { 0 };

	for (int r = 0; r < 5; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			int tr, tc, dust;

			tr = sr + r - 2;
			tc = sc + c - 2;

			dust = center * ratio[dir][r][c] / 100;

			tmpMAP[r][c] = dust;
			MAP[sr][sc] -= dust;
		}
	}

	tmpMAP[2 + dr[dir]][2 + dc[dir]] = MAP[sr][sc];
	MAP[sr][sc] = 0;

	int ret = 0;
	for (int r = 0; r < 5; r++)
	{
		for (int c = 0; c < 5; c++)
		{
			int tr, tc;

			tr = sr + r - 2;
			tc = sc + c - 2;

			if (tr < 1 || tc < 1 || tr > N || tc > N) ret += tmpMAP[r][c];
			else MAP[tr][tc] += tmpMAP[r][c];
		}
	}

	return ret;
}

int simulate()
{
	int outDust = 0;
	for (int i = 0; i < tcnt - 1; i++)
	{
		int r, c, dir;

		r = track[i + 1].r;
		c = track[i + 1].c;
		dir = track[i].dir;

		outDust += clean(r, c, dir);
	}
	   	  
	return outDust;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		makeSnail();

		printf("%d\n", simulate());
	}

	return 0;
}