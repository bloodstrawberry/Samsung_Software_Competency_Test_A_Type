#include <stdio.h>

#define MAX (1000 + 10)

int N, M, K;
int MAP[MAX][MAX];
int visit[11][MAX][MAX];

struct RC
{
	int r;
	int c;
	int crash;
};

RC queue[MAX * MAX * 11];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%1d", &MAP[r][c]);
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void printMapAll() // for debug
{
	printf("MAP\n");
	printMap(MAP);

	printf("visit[0]\n");
	printMap(visit[0]);

	printf("visit[1]\n");
	printMap(visit[1]);

	// or visit[K]까지 출력
}

int BFS(int r, int c)
{
	int rp, wp;

	rp = wp = 0;

	visit[0][r][c] = 1;

	queue[wp].r = r;
	queue[wp++].c = c;

	while (rp < wp)
	{
		RC out = queue[rp++];

		if (out.r == N && out.c == M)
			return visit[out.crash][out.r][out.c];

		for (int i = 0; i < 4; i++)
		{
			int nr = out.r + dr[i];
			int nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > M) continue;

			if (out.crash < K) // K 미만인 경우
			{
				if (MAP[nr][nc] == 0 && visit[out.crash][nr][nc] == 0)
				{
					queue[wp].r = nr;
					queue[wp].c = nc;
					queue[wp++].crash = out.crash;

					visit[out.crash][nr][nc]
						= visit[out.crash][out.r][out.c] + 1;
				}
				else
				{
					if (MAP[nr][nc] == 1 && visit[out.crash + 1][nr][nc] == 0)
					{
						queue[wp].r = nr;
						queue[wp].c = nc;
						queue[wp++].crash = out.crash + 1;

						visit[out.crash + 1][nr][nc]
							= visit[out.crash][out.r][out.c] + 1;
					}
				}
			}
			else // 마지막 K
			{
				if (MAP[nr][nc] == 0 && visit[out.crash][nr][nc] == 0)
				{
					queue[wp].r = nr;
					queue[wp].c = nc;
					queue[wp++].crash = out.crash;

					visit[out.crash][nr][nc]
						= visit[out.crash][out.r][out.c] + 1;
				}
			}
		}
	}

	return -1;
}

int main()
{
	input();

	printf("%d\n", BFS(1, 1));

	// printMapAll();

	return 0;
}