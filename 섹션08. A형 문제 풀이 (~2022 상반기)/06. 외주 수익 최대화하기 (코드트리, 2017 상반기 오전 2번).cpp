#include <stdio.h>

#define MAX (15 + 5)

int T;

int N;
int time[MAX];
int profit[MAX];

int num_of_cases[MAX];

int maxAnswer;

void input()
{
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
		scanf("%d %d", &time[i], &profit[i]);
}

void printCases()
{
	for (int i = 1; i <= N; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

bool check()
{
	bool visit[MAX] = { 0 };
	for (int i = 1; i <= N; i++)
	{
		if (num_of_cases[i] == 0) continue;

		for (int k = 0; k < time[i]; k++)
		{
			if (N < i + k) return false;
			// i + k가 MAX를 넘지 않도록 주의!, 작업 기한의 최대값은 5
			if (visit[i + k] == true) return false;

			visit[i + k] = true;
		}
	}

	return true;
}

int getProfit()
{
	int sum = 0;
	for (int i = 1; i <= N; i++)
		sum += (num_of_cases[i] * profit[i]);

	return sum;
}

void DFS(int depth)
{
	if (depth == N)
	{
		// printCases();

		if (check() == true)
		{
			int tmp = getProfit();
			if (maxAnswer < tmp) maxAnswer = tmp;
		}

		return;
	}

	for (int i = 0; i < 2; i++)
	{
		num_of_cases[depth + 1] = i; // 1일차 ~ N일차

		DFS(depth + 1);
	}
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		maxAnswer = 0;

		DFS(0);

		printf("%d\n", maxAnswer);
	}

	return 0;
}