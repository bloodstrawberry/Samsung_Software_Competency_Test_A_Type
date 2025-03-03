#include <stdio.h>

#define MAX (1000 + 50)

int N, M, V;
int MAP[MAX][MAX];

int queue[MAX * MAX];
bool visit[MAX];

void input()
{
	scanf("%d %d %d", &N, &M, &V);

	for (int i = 1; i <= M; i++)
	{
		int n1, n2;

		scanf("%d %d", &n1, &n2);

		MAP[n1][n2] = MAP[n2][n1] = 1;
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void DFS(int node)
{
	visit[node] = true;

	printf("%d ", node);

	for (int c = 1; c <= N; c++)
	{
		if (MAP[node][c] == 0 || visit[c] == true) continue;

		DFS(c);
	}
}

void BFS(int node)
{
	int rp, wp;

	rp = wp = 0;

	queue[wp++] = node;

	visit[node] = true;

	while (rp < wp)
	{
		int out = queue[rp++];

		printf("%d ", out);

		for (int c = 1; c <= N; c++)
		{
			if (MAP[out][c] == 0 || visit[c] == true) continue;

			queue[wp++] = c;

			visit[c] = true;
		}
	}
}

int main()
{
	input();

	DFS(V);
	putchar('\n');

	for (int i = 1; i <= N; i++) visit[i] = false;

	BFS(V);
	putchar('\n');

	return 0;
}