#include <stdio.h>

#define MAX (50 + 10)
#define MAX_HOSPITAL (13 + 5)
#define INF (0x7fff0000)

#define PERSON (1)
#define HOSPITAL (2)

int T;

int N, M;
int MAP[MAX][MAX];

int num_of_cases[MAX_HOSPITAL];

struct RC
{
	int r;
	int c;
};

RC person[MAX * 2];
RC hospital[MAX_HOSPITAL];
int pcnt, hcnt;

int minAnswer;

void input()
{
	scanf("%d %d", &N, &M);

	pcnt = hcnt = 0;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &MAP[r][c]);

			if (MAP[r][c] == PERSON)
			{
				person[pcnt].r = r;
				person[pcnt++].c = c;
			}
			else if (MAP[r][c] == HOSPITAL)
			{
				hospital[hcnt].r = r;
				hospital[hcnt++].c = c;
			}
		}
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void printCases()
{
	for (int i = 0; i < M; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

int abs(int x)
{
	return (x > 0) ? x : -x;
}

// 맨해튼 거리 (Manhattan Distance)
int getDistance(int r1, int c1, int r2, int c2)
{
	return abs(r1 - r2) + abs(c1 - c2);
}

int calculate()
{
	bool selectedHospital[MAX_HOSPITAL] = { 0 };

	for (int i = 0; i < M; i++)
		selectedHospital[num_of_cases[i]] = true;

	int sum = 0;
	for (int i = 0; i < pcnt; i++)
	{
		int minDistance = INF;
		for (int k = 0; k < hcnt; k++)
		{
			if (selectedHospital[k] == false) continue;

			int distance
				= getDistance(person[i].r, person[i].c, hospital[k].r, hospital[k].c);

			minDistance = (distance < minDistance) ? distance : minDistance;
		}

		sum += minDistance;
	}

	return sum;
}

void DFS(int depth, int start)
{
	if (depth == M) // M개를 고른 경우
	{
		// printCases();
	
		int tmp = calculate();
		if (tmp < minAnswer) minAnswer = tmp;

		return;
	}

	for (int i = start; i < hcnt; i++) // 병원의 개수에서
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

		DFS(0, 0);

		printf("%d\n", minAnswer);
	}

	return 0;