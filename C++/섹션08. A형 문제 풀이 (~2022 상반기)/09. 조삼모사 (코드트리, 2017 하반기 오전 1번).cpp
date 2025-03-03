#include <stdio.h>

#define MAX (20 + 5)
#define INF (0x7fff0000)

int T;

int N, halfN;
int MAP[MAX][MAX];

int num_of_cases[MAX];

int minAnswer;

void input()
{
	scanf("%d", &N);

	halfN = N / 2;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);
}

void printCases()
{
	for (int i = 0; i < halfN; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

int abs(int x)
{
	return (x > 0) ? x : -x;
}

int calculate()
{
	bool isMorning[MAX] = { 0 };
	int morning[MAX] = { 0 };
	int dinner[MAX] = { 0 };
	int mcnt, dcnt;
	int sum1, sum2;

	for (int i = 0; i < halfN; i++)
		isMorning[num_of_cases[i]] = true;

	mcnt = dcnt = 0;
	for (int i = 1; i <= N; i++)
	{
		if (isMorning[i] == true) morning[mcnt++] = i;
		else dinner[dcnt++] = i;
	}

	// for debug
	//printf("morning : ");
	//for (int i = 0; i < mcnt; i++) printf("%d ", morning[i]);
	//putchar('\n');
	//printf("dinner : ");
	//for (int i = 0; i < dcnt; i++) printf("%d ", dinner[i]);
	//putchar('\n'); putchar('\n');

	sum1 = sum2 = 0;

	// 23 24 34 / 15 16 56
	for (int i = 0; i < halfN; i++)
	{
		for (int k = i + 1; k < halfN; k++)
		{
			int mr, mc, dr, dc;

			mr = morning[i]; mc = morning[k];
			dr = dinner[i]; dc = dinner[k];

			sum1 += (MAP[mr][mc] + MAP[mc][mr]);
			sum2 += (MAP[dr][dc] + MAP[dc][dr]);
		}
	}

	return abs(sum1 - sum2);
}

void DFS(int depth, int start)
{
	if (depth == halfN)
	{
		// printCases();

		int tmp = calculate();
		if (tmp < minAnswer) minAnswer = tmp;

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
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		minAnswer = INF;

		DFS(0, 1);

		printf("%d\n", minAnswer);
	}

	return 0;
}