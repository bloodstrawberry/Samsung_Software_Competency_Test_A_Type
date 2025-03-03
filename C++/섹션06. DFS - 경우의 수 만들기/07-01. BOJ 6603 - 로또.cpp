#include <stdio.h>

#define MAX (13 + 3)

int N;

int num_of_cases[MAX];
int number[MAX];

void input()
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) scanf("%d", &number[i]);
}

void printCases()
{
	for (int i = 0; i < 6; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

void DFS(int depth, int start)
{
	if (depth == 6)
	{
		printCases();
		return;
	}

	for (int i = start; i <= N; i++)
	{
		num_of_cases[depth] = number[i];

		DFS(depth + 1, i + 1);
	}
}

int main()
{
	while (1)
	{
		input();

		if (N == 0) break;

		DFS(0, 1);

		putchar('\n');
	}

	return 0;
}