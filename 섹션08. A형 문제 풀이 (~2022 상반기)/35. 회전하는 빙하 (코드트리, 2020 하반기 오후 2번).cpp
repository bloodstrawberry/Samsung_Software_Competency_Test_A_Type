#include <stdio.h>

#define MAX (64 + 5)

int T;

int N, Q, MAP_SIZE;
int MAP[MAX][MAX];
int tmpMAP[MAX][MAX];
int L[1000 + 50];

bool visit[MAX][MAX];

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
	scanf("%d %d", &N, &Q);

	MAP_SIZE = 1 << N;

	for (int r = 1; r <= MAP_SIZE; r++)
		for (int c = 1; c <= MAP_SIZE; c++)
			scanf("%d", &MAP[r][c]);

	for (int q = 0; q < Q; q++) scanf("%d", &L[q]);
}

void printMap() // for debug
{
	for (int r = 1; r <= MAP_SIZE; r++)
	{
		for (int c = 1; c <= MAP_SIZE; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void rotate(int sr, int sc, int size)
{
	int half = size / 2;

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			tmpMAP[r][c] = MAP[sr + r][sc + c];

	// 3 -> 1
	for (int r = 0; r < half; r++)
		for (int c = 0; c < half; c++)
			MAP[sr + r][sc + c] = tmpMAP[r + half][c];

	// 1 -> 2
	for (int r = 0; r < half; r++)
		for (int c = 0; c < half; c++)
			MAP[sr + r][sc + c + half] = tmpMAP[r][c];

	// 2 -> 4
	for (int r = 0; r < half; r++)
		for (int c = 0; c < half; c++)
			MAP[sr + r + half][sc + c + half] = tmpMAP[r][c + half];

	// 4 -> 3
	for (int r = 0; r < half; r++)
		for (int c = 0; c < half; c++)
			MAP[sr + r + half][sc + c] = tmpMAP[r + half][c + half];
}

void meltIce()
{
	int ICE[MAX][MAX] = { 0 };
	for (int r = 1; r <= MAP_SIZE; r++)
	{
		for (int c = 1; c <= MAP_SIZE; c++)
		{
			if (MAP[r][c] == 0) continue;

			int count = 0;
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				count += !MAP[nr][nc];
			}

			if (count >= 2) ICE[r][c] = 1;
		}
	}

	for (int r = 1; r <= MAP_SIZE; r++)
		for (int c = 1; c <= MAP_SIZE; c++)
			MAP[r][c] -= ICE[r][c];
}

void simulate()
{
	for (int q = 0; q < Q; q++)
	{
		int level = L[q];
		int divide = 1 << level;

		for (int r = 1; r <= MAP_SIZE; r += divide)
			for (int c = 1; c <= MAP_SIZE; c += divide)
				rotate(r, c, divide);

		meltIce();
	}
}

int getIceCount()
{
	int sum = 0;
	for (int r = 1; r <= MAP_SIZE; r++)
		for (int c = 1; c <= MAP_SIZE; c++)
			sum += MAP[r][c];

	return sum;
}

int BFS(int r, int c)
{
	int rp, wp;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (MAP[nr][nc] == 0 || visit[nr][nc] == true) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;
		}
	}

	return wp;
}

int getGroupCount()
{
	for (int r = 1; r <= MAP_SIZE; r++)
		for (int c = 1; c <= MAP_SIZE; c++)
			visit[r][c] = false;

	int max = 0;
	for (int r = 1; r <= MAP_SIZE; r++)
	{
		for (int c = 1; c <= MAP_SIZE; c++)
		{
			if (MAP[r][c] == 0 || visit[r][c] == true) continue;

			int tmp = BFS(r, c);
			if (max < tmp) max = tmp;
		}
	}

	return max;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		simulate();

		int iceCount = getIceCount();
		int groupCount = getGroupCount();

		printf("%d\n%d\n", iceCount, groupCount);
	}

	return 0;
}