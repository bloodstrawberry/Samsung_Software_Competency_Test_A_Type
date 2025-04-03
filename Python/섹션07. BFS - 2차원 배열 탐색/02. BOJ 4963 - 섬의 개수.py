#include <stdio.h>

#define MAX (50 + 5)

int W, H;

int MAP[MAX][MAX];
bool visit[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

// 8방향 ↑, ↗, →, ↘, ↓, ↙, ←, ↖
int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void printVisit() // for debug
{
	for (int r = 1; r <= H; r++)
	{
		for (int c = 1; c <= W; c++)
			printf("%d ", visit[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void input()
{
	scanf("%d %d", &W, &H);

	// init
	for (int r = 0; r <= H + 1; r++)
		for (int c = 0; c <= W + 1; c++)
			MAP[r][c] = visit[r][c] = 0;

	for (int r = 1; r <= H; r++)
		for (int c = 1; c <= W; c++)
			scanf("%d", &MAP[r][c]);
}

void BFS(int r, int c)
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

		for (int i = 0; i < 8; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			// if (nr < 1 || nc < 1 || nr > H || nc > W) continue;
			if (MAP[nr][nc] == 0 || visit[nr][nc] == true) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;

			// printf("push %d, %d\n", nr, nc);
			// printVisit();
		}
	}
}

int main()
{
	// int tc = 0;
	while (1)
	{
		// printf("tc : %d!!!!!!!\n", tc);
		// tc++;

		input();

		if (W == 0 && H == 0) break;

		int ansCount = 0;
		for (int r = 1; r <= H; r++)
		{
			for (int c = 1; c <= W; c++)
			{
				if (MAP[r][c] == 1 && visit[r][c] == false)
				{
					BFS(r, c);
					ansCount++;
				}
			}
		}

		printf("%d\n", ansCount);
	}

	return 0;
}