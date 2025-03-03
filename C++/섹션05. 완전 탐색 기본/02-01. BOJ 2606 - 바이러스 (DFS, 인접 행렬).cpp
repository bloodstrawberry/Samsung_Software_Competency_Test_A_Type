#include <stdio.h>

#define MAX (100 + 10)

int V, E; // Vertex, Edge
int MAP[MAX][MAX];

bool visit[MAX];
int count;

void input()
{
	scanf("%d %d", &V, &E);

	for (int i = 0; i < E; i++)
	{
		int n1, n2;

		scanf("%d %d", &n1, &n2);

		MAP[n1][n2] = MAP[n2][n1] = 1;
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= V; r++)
	{
		for (int c = 1; c <= V; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void DFS(int node)
{
	visit[node] = true;

	for (int c = 1; c <= V; c++)
	{
		if (MAP[node][c] == 0 || visit[c] == true) continue;

		count++;

		DFS(c);
	}
}

int main()
{
	input();

	DFS(1);

	printf("%d\n", count);

	return 0;
}