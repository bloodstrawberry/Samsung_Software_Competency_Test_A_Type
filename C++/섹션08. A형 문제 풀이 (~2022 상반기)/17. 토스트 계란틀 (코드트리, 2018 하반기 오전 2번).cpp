#include <stdio.h>

#define MAX (100 + 20)

int T;

int N, L, R;
int MAP[MAX][MAX];
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
	scanf("%d %d %d", &N, &L, &R);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", MAP[r][c]);
		putchar('\n');
	}
}

int abs(int x)
{
	return (x > 0) ? x : -x;
}

int BFS(int r, int c)
{
	int rp, wp;
	int sum;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	sum = MAP[r][c];

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr = out.r + dr[i];
			int nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

			int diff = abs(MAP[out.r][out.c] - MAP[nr][nc]);

			if (visit[nr][nc] == true || (L <= diff && diff <= R) == false) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;	
			sum += MAP[nr][nc];
		}
	}

	for (int i = 0; i < wp; i++)
	{
		RC tmp = queue[i];
		MAP[tmp.r][tmp.c] = sum / wp;
	}

	return wp;
}

bool simulate()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			visit[r][c] = false;

	bool result = false;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (visit[r][c] == true) continue;

			int moveEggCount = BFS(r, c);
			if (moveEggCount != 1) result = true;
		}
	}

	return result;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		int answer = 0;

		while (1)
		{
			bool result = simulate();

			if (result == false) break;

			answer++;
		}

		printf("%d\n", answer);
	}

	return 0;
}