#include <stdio.h>

#define MAX (20 + 5)

#define UP (0)
#define RIGHT (1)
#define DOWN (2)
#define LEFT (3)

int T;

int N;
int oMAP[MAX][MAX]; // original Map
int ansMAP[MAX][MAX]; // answerMap

int num_of_cases[5 + 5];

int maxAnswer;

void input()
{
	scanf("%d", &N);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &oMAP[r][c]);
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void copyMap(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			copy[r][c] = original[r][c];
}

void printCases()
{
	for (int i = 0; i < 5; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

void moveUp()
{
	int tmpMAP[MAX][MAX] = { 0 };

	for (int c = 1; c <= N; c++)
	{
		int index = 1;
		for (int r = 1; r <= N; r++)
		{
			if (ansMAP[r][c] == 0) continue;

			tmpMAP[index++][c] = ansMAP[r][c];
		}

		for (int r = 1; r <= N - 1; r++)
		{
			if (tmpMAP[r][c] != tmpMAP[r + 1][c]) continue;
			if (tmpMAP[r][c] == 0) break;

			// 기준이 되는 점을 2배로 
			tmpMAP[r][c] *= 2;
			
			// 남은 칸을 앞으로 1칸씩 옮긴다. 
			for (int tr = r + 1; tr <= N - 1; tr++)
				tmpMAP[tr][c] = tmpMAP[tr + 1][c];

			tmpMAP[N][c] = 0;
		}
	}

	copyMap(ansMAP, tmpMAP);
}

void moveRight()
{
	int tmpMAP[MAX][MAX] = { 0 };

	for (int r = 1; r <= N; r++)
	{
		int index = N; // 
		for (int c = N; c >= 1; c--)
		{
			if (ansMAP[r][c] == 0) continue;

			tmpMAP[r][index--] = ansMAP[r][c];
		}

		for (int c = N; c >= 2; c--)
		{
			if (tmpMAP[r][c] != tmpMAP[r][c - 1]) continue;
			if (tmpMAP[r][c] == 0) break;

			tmpMAP[r][c] *= 2;

			for (int tc = c - 1; tc >= 2; tc--) 
				tmpMAP[r][tc] = tmpMAP[r][tc - 1];

			tmpMAP[r][1] = 0;
		}
	}

	copyMap(ansMAP, tmpMAP);
}

void moveDown() 
{
	int tmpMAP[MAX][MAX] = { 0 };

	for (int c = 1; c <= N; c++)
	{
		int index = N;
		for (int r = N; r >= 1; r--)
		{
			if (ansMAP[r][c] == 0) continue;

			tmpMAP[index--][c] = ansMAP[r][c];
		}

		for (int r = N; r >= 2; r--)
		{
			if (tmpMAP[r][c] != tmpMAP[r - 1][c]) continue;
			if (tmpMAP[r][c] == 0) break;

			tmpMAP[r][c] *= 2;
 
			for (int tr = r - 1; tr >= 2; tr--)
				tmpMAP[tr][c] = tmpMAP[tr - 1][c];

			tmpMAP[1][c] = 0;
		}
	}

	copyMap(ansMAP, tmpMAP);
}

void moveLeft()
{
	int tmpMAP[MAX][MAX] = { 0 };

	for (int r = 1; r <= N; r++)
	{
		int index = 1; // (1, 1) 부터 시작
		for (int c = 1; c <= N; c++)
		{
			if (ansMAP[r][c] == 0) continue;

			tmpMAP[r][index++] = ansMAP[r][c];
		}

		for (int c = 1; c <= N - 1; c++)
		{
			if (tmpMAP[r][c] != tmpMAP[r][c + 1]) continue;
			if (tmpMAP[r][c] == 0) break;

			tmpMAP[r][c] *= 2;
			for (int tc = c + 1; tc <= N - 1; tc++) 
				tmpMAP[r][tc] = tmpMAP[r][tc + 1];

			tmpMAP[r][N] = 0;
		}
	}

	copyMap(ansMAP, tmpMAP);
}

void simulate()
{
	copyMap(ansMAP, oMAP);

	for (int i = 0; i < 5; i++)
	{
		int direction = num_of_cases[i];

		if (direction == UP) moveUp();
		else if (direction == RIGHT) moveRight();
		else if (direction == DOWN) moveDown();
		else if (direction == LEFT) moveLeft();
	}
}

int findMax()
{
	int maxValue = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			if (maxValue < ansMAP[r][c]) maxValue = ansMAP[r][c];

	return maxValue;
}

void DFS(int depth)
{
	if (depth == 5)
	{
		// printCases();

		simulate();

		int tmp = findMax();
		if (maxAnswer < tmp) maxAnswer = tmp;

		return;
	}

	for (int i = 0; i < 4; i++)
	{
		num_of_cases[depth] = i;

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