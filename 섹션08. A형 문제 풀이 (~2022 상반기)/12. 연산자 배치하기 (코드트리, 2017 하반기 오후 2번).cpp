#include <stdio.h>

#define MAX (11 + 5)
#define INF (0x7fff0000)

#define PLUS (0)
#define MINUS (1)
#define MULTIPLY (2)

int T;

int N;
int num_of_cases[MAX];
int visit[MAX];
int possible[3]; // 사용할 수 있는 최대 PLUS, MINUS, MULTIPLY 
int number[MAX];

int minAnswer, maxAnswer;

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++) scanf("%d", &number[i]);
	for (int i = 0; i < 3; i++) scanf("%d", &possible[i]);
}

void printCases()
{
	for (int i = 0; i < N - 1; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

int calculate()
{
	int sum = number[0];
	for (int i = 0; i < N - 1; i++)
	{
		if (num_of_cases[i] == PLUS) sum += number[i + 1];
		else if (num_of_cases[i] == MINUS) sum -= number[i + 1];
		else if (num_of_cases[i] == MULTIPLY) sum *= number[i + 1];
	}

	return sum;
}

void DFS(int depth)
{
	if (depth == N - 1)
	{
		// printCases();
		
		int tmp = calculate();
		if (maxAnswer < tmp) maxAnswer = tmp;
		if (minAnswer > tmp) minAnswer = tmp;

		return;
	}

	for (int i = 0; i < 3; i++)
	{
		if (visit[i] == possible[i]) continue;

		num_of_cases[depth] = i;

		visit[i]++;
		DFS(depth + 1);
		visit[i]--;
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
		maxAnswer = -INF;

		DFS(0);

		printf("%d %d\n", minAnswer, maxAnswer);
	}

	return 0;
}