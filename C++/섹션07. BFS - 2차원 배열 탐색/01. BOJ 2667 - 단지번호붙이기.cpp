#include <stdio.h>

#define MAX (25 + 5)

int N;

int MAP[MAX][MAX];
bool visit[MAX][MAX];

int answers[MAX * MAX];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void printVisit() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", visit[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void input()
{
	scanf("%d", &N);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%1d", &MAP[r][c]);
}

int BFS(int r, int c)
{
	// printf("start %d, %d\n", r, c);

	int rp, wp;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;
	
	visit[r][c] = true;
	// printVisit();

	while (rp < wp)
	{
		RC out = queue[rp++];

		// printf("out %d, %d\n", out.r, out.c);

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (MAP[nr][nc] == 0 || visit[nr][nc] == true) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;

			// printf("push %d, %d\n", nr, nc);
			// printVisit();
		}
	}

	return wp;
}

int main()
{
	input();

	int ansCount = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if(MAP[r][c] == 1 && visit[r][c] == false)
				answers[ansCount++] = BFS(r, c);
		}
	}

	printf("%d\n", ansCount);

	for (int i = 0; i < ansCount - 1; i++)
	{
		for (int k = i + 1; k < ansCount; k++)
		{
			if (answers[i] > answers[k])
			{
				int tmp = answers[i];
				answers[i] = answers[k];
				answers[k] = tmp;
			}
		}
	}

	for (int i = 0; i < ansCount; i++) printf("%d\n", answers[i]);

	return 0;
}