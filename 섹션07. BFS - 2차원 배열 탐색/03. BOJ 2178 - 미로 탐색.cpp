#include <stdio.h>

#define MAX (100 + 10)

int N, M;

int MAP[MAX][MAX];
bool visit[MAX][MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

void printMap() // for debug
{
	printf("MAP\n");
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%2d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');

	printf("visit\n");
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", visit[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%1d", &MAP[r][c]);
}

void BFS(int r, int c)
{
	int rp, wp;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	// printMap();

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

			MAP[nr][nc] = MAP[out.r][out.c] + 1;

			// printMap();
		}
	}
}

int main()
{
	input();

	BFS(1, 1);

	printf("%d\n", MAP[N][M]);

	return 0;
}