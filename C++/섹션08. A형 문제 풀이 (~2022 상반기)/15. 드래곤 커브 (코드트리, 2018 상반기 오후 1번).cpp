#include <stdio.h>

#define MAX (100 + 20)

int T;

int N;
int MAP[MAX][MAX];
int dragonPosition[2000]; // 2^10 보다 큰 값

// 오른쪽, 위쪽, 왼쪽, 아래쪽
int dr[] = { 0, -1, 0, 1 };
int dc[] = { 1, 0, -1, 0 };

void makeDragonCurve()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{	
		int r, c, d, g; // x = r, y = c;

		scanf("%d %d %d %d", &r, &c, &d, &g);

		dragonPosition[0] = d;

		int length = 1;
		for (int step = 1; step <= g; step++)
		{
			for (int i = length + 1; i <= length * 2; i++)
				dragonPosition[i - 1] = (dragonPosition[length * 2 - i] + 1) % 4;

			// for debug
			// for (int i = 0; i < length * 2; i++) printf("%d, ", dragonPosition[i]);
			// putchar('\n');

			length *= 2;
		}

		MAP[r][c] = 1;

		int moveCount = 1 << g; // move = 2^g
		for (int k = 0; k < moveCount; k++)
		{
			r = r + dr[dragonPosition[k]];
			c = c + dc[dragonPosition[k]];

			MAP[r][c] = 1;
		}
	}
}

int countSquare()
{
	int sum = 0;
	for (int r = 0; r < 100; r++)
		for (int c = 0; c < 100; c++)
			if (MAP[r][c] + MAP[r + 1][c] + MAP[r][c + 1] + MAP[r + 1][c + 1] == 4) sum++;

	return sum;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		makeDragonCurve();

		printf("%d\n", countSquare());
	}

	return 0;
}