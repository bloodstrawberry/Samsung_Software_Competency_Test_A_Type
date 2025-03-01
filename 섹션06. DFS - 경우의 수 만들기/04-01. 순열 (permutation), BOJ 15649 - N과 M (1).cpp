#include <stdio.h>

#define MAX (8 + 3)

int N, M;

int num_of_cases[MAX];
bool visit[MAX]; 

void printCases()
{
	for (int i = 0; i < M; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

void DFS(int depth)
{
	if (depth == M)
	{
		printCases();
		return;
	}

	for (int i = 1; i <= N; i++)
	{
		if (visit[i] == true) continue;

		num_of_cases[depth] = i;

		visit[i] = true;
		DFS(depth + 1);		
		visit[i] = false;
	}
}

int main()
{
	scanf("%d %d", &N, &M);

	DFS(0);

	return 0;
}