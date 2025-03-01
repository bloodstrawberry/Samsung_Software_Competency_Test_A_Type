#include <stdio.h>

#define MAX (7 + 3)

int N, M;

int num_of_cases[MAX];
int number[MAX];
bool check[10000 + 100];

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
		num_of_cases[depth] = number[i];

		DFS(depth + 1);
	}
}

int main()
{
	scanf("%d %d", &N, &M);

	int count = 1;
	for (int i = 1; i <= N; i++)
	{
		int value;

		scanf("%d", &value);

		if (check[value] == false)
		{
			number[count++] = value;
			check[value] = true;
		}
	}

	N = count - 1;

	/* 정렬 */
	for (int i = 1; i <= N - 1; i++)
	{
		for (int k = i + 1; k <= N; k++)
		{
			if (number[i] > number[k])
			{
				int tmp = number[i];
				number[i] = number[k];
				number[k] = tmp;
			}
		}
	}

	DFS(0);

	return 0;
}