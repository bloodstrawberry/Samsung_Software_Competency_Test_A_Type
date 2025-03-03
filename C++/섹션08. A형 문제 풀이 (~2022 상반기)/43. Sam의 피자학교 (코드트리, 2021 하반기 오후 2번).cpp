#include <stdio.h>

#define MAX (100 + 10)
#define INF (0x7fff0000)

int T;

int N, K;
int pizza[MAX][MAX];

struct RC
{
	int r;
	int c;
};

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d", &N, &K);

	// 초기화
	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			pizza[r][c] = 0;

	for (int c = 1; c <= N; c++)
		scanf("%d", &pizza[N][c]);
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", pizza[r][c]);
		putchar('\n');
	}

	putchar('\n');
}

void addFlour()
{
	int min = INF;
	for (int c = 1; c <= N; c++)
		if (pizza[N][c] < min) min = pizza[N][c];

	for (int c = 1; c <= N; c++)
		if (pizza[N][c] == min) pizza[N][c]++;
}

void roll()
{
	// 1, 1 x 1
	// 2, 2 x 1
	// 3, 2 x 2
	// 5, 3 x 2
	// 7, 3 x 3
	// 10, 4 x 3

	int start, height, width;

	start = height = width = 1;

	int count = 0;
	while (1)
	{
		if (start + height + width - 1 > N) break;

		// 밀가루 이동
		for (int c = start; c < start + width; c++)
		{
			for (int r = N; r > N - height; r--)
			{
				int nr, nc;

				nr = N - width + (c - start);
				nc = start + width + (N - r);

				// for debug
				// printf("%d %d -> %d %d\n", r, c, nr, nc);

				pizza[nr][nc] = pizza[r][c];
				pizza[r][c] = 0;
			}
		}

		if (count % 2 == 0) height++;
		else width++; 

		start += (count / 2 + 1);

		count++;
	}
}

void press()
{
	int tmpPizza[MAX][MAX] = { 0 };
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (pizza[r][c] == 0) continue;

			int flour = pizza[r][c];

			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (pizza[nr][nc] == 0) continue;

				if (pizza[r][c] > pizza[nr][nc])
				{
					int diff = (pizza[r][c] - pizza[nr][nc]) / 5;

					flour -= diff;
					tmpPizza[nr][nc] += diff;
				}
			}

			tmpPizza[r][c] += flour;
		}
	}

	int index = 1;
	for (int c = 1; c <= N; c++)
	{
		if (tmpPizza[N][c] == 0) continue;

		int sr = N;
		while (1)
		{
			if (tmpPizza[sr][c] == 0) break;

			pizza[N][index++] = tmpPizza[sr][c];
			sr--;
		}
	}

	for (int r = 1; r <= N - 1; r++)
		for (int c = 1; c <= N; c++)
			pizza[r][c] = 0;
}

void fold()
{
	// 한 번 접기
	int sc = (N / 2) + 1;
	for (int c = N / 2; c >= 1; c--)
	{
		pizza[N - 1][sc++] = pizza[N][c];
		pizza[N][c] = 0;
	}

	// 두 번 접기
	int nr = N - 2;
	for (int r = N - 1; r <= N; r++)
	{
		int ec = (N / 4) * 3;
		int nc = N;
		for (int c = (N / 2) + 1; c <= ec; c++)
		{
			// for debug
			// printf("%d %d -> %d %d\n", r, c, nr, nc);

			pizza[nr][nc] = pizza[r][c];
			pizza[r][c] = 0;

			nc--;
		}

		nr--;
	}
}

bool check()
{
	int max = 0;
	int min = INF;

	for (int c = 1; c <= N; c++)
	{
		if (pizza[N][c] < min) min = pizza[N][c];
		if (pizza[N][c] > max) max = pizza[N][c];
	}
	
	return (max - min) <= K;
}

int simulate()
{
	int count = 0;
	while (1)
	{
		addFlour();
		roll();
		press();
		fold();
		press();

		count++;

		if (check() == true) break;
	}

	return count;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		printf("%d\n", simulate());
	}

	return 0;
}