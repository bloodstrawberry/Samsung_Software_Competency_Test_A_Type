#include <stdio.h>

#define MAX (100 + 10)

int V, E; // Vertex, Edge
int MAP[MAX][MAX];
int index[MAX];

int queue[MAX];
bool visit[MAX];

void input()
{
	scanf("%d %d", &V, &E);

	for (int i = 0; i < E; i++)
	{
		int n1, n2;

		scanf("%d %d", &n1, &n2);

		MAP[n1][index[n1]++] = n2;
		MAP[n2][index[n2]++] = n1;
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= V; r++)
	{
		for (int c = 0; c < index[r]; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void BFS(int node)
{
	int rp, wp, count;

	rp = wp = 0;

	queue[wp++] = node;

	visit[node] = true;

	count = 0;
	while (rp < wp)
	{
		int out = queue[rp++];

		for (int i = 0; i < index[out]; i++)
		{
			int number = MAP[out][i];

			if (visit[number] == true) continue;

			count++;

			queue[wp++] = number;

			visit[number] = true;
		}
	}

	printf("%d\n", count);
}

int main()
{
	input();

	// printMap();

	BFS(1);

	return 0;
}