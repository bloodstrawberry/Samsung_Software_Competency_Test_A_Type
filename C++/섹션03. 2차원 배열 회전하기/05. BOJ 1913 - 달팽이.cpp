#include <stdio.h>

#define MAX (1000 + 100)

int N, K;
int MAP[MAX][MAX];

// 상, 우, 하, 좌 (↑, →, ↓, →)
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void printMap()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
}

void makeSnail()
{
	int ansR, ansC;
	int r, c, direction;
	int index, size;
		
	r = c = ansR = ansC = (N + 1) / 2;
	direction = 0;
	index = 1;
	size = 0;

	MAP[r][c] = index++;

	for (int i = 0; i < 2 * N - 1; i++)
	{
		if(i % 2 == 0) size++;

		for (int s = 0; s < size; s++)
		{
			int nr, nc;

			nr = r + dr[direction];
			nc = c + dc[direction];

			if (index == K)
			{
				ansR = nr;
				ansC = nc;
			}

			MAP[nr][nc] = index++;

			r = nr;
			c = nc;
		}

		direction++;

		if (direction == 4) direction = 0;
	}

	printMap();

	printf("%d %d\n", ansR, ansC);
}

int main()
{
	scanf("%d %d", &N, &K);

	makeSnail();

	return 0;
}