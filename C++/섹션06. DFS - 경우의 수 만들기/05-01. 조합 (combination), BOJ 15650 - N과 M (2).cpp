#include <stdio.h>

#define MAX (8 + 3)

int N, M;

int num_of_cases[MAX];

void printCases()
{
	for (int i = 0; i < M; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

void DFS(int depth, int start)
{
	if (depth == M)
	{
		printCases();
		return;
	}

	for (int i = start; i <= N; i++)
	{
		num_of_cases[depth] = i;

		DFS(depth + 1, i + 1);
	}
}

int main()
{
	scanf("%d %d", &N, &M);

	DFS(0, 1);

	return 0;
}