#include <stdio.h>

#define MAX (300 + 30)

int T, L;
int sr, sc, er, ec;
int MAP[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

int dr[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int dc[] = { 1, 2, 2, 1, -1, -2, -2, -1 };

void input()
{
	scanf("%d %d %d %d %d", &L, &sr, &sc, &er, &ec);

	for (int r = 0; r < L; r++)
		for (int c = 0; c < L; c++)
			MAP[r][c] = 0;
}

void printMap() // for debug
{
	for (int r = 0; r < L; r++)
	{
		for (int c = 0; c < L; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

int BFS(int r, int c)
{
	int rp, wp;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	MAP[r][c] = 1;

	while (rp < wp)
	{
		RC out = queue[rp++];

		if (out.r == er && out.c == ec)
			return MAP[out.r][out.c] - 1;

		for (int i = 0; i < 8; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (nr < 0 || nc < 0 || nr > L - 1 || nc > L - 1) continue;
			if (MAP[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			MAP[nr][nc] = MAP[out.r][out.c] + 1;
		}
	}

	return -1; // error
}

int main()
{
	scanf("%d", &T);

	for (int tc = 0; tc < T; tc++)
	{
		input();

		printf("%d\n", BFS(sr, sc));
	}

	return 0;
}