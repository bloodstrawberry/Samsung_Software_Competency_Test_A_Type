#include <stdio.h>

#define MAX (10 + 5)
#define MAX_VIRUS (100000)

int T;
int N, M, K;
int food[MAX][MAX]; // 양분
int MAP[MAX][MAX]; // 증가되는 양분

int virus[MAX][MAX][MAX_VIRUS];
int index[MAX][MAX];

// 8방향 ↑, ↗, →, ↘, ↓, ↙, ←, ↖
int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			food[r][c] = 5;

	for (int i = 0; i < M; i++)
	{
		int r, c, age;

		scanf("%d %d %d", &r, &c, &age);

		int& virusCount = index[r][c];
		virus[r][c][virusCount++] = age;
	}
}

void printVirus() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int virusCount = index[r][c];
			if (virusCount == 0) continue;

			printf("%d, %d) : ", r, c);
			for (int t = 0; t < virusCount; t++)
				printf("%d ", virus[r][c][t]);
			putchar('\n');
		}
	}
	putchar('\n');
}

void step1_2()
{
	// 죽은 바이러스 정리
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int virusCount = index[r][c];

			int newIndex = 0;
			for (int t = 0; t < virusCount; t++)
			{
				if (virus[r][c][t] == 0) continue;

				virus[r][c][newIndex++] = virus[r][c][t];
			}

			index[r][c] = newIndex;
		}
	}

	// 나이가 어린 바이러스부터 양분을 섭취하기 위한 정렬
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int virusCount = index[r][c];

			for (int k = 0; k < virusCount - 1; k++)
			{
				for (int t = k + 1; t < virusCount; t++)
				{
					if (virus[r][c][k] > virus[r][c][t])
					{
						int tmp = virus[r][c][k];
						virus[r][c][k] = virus[r][c][t];
						virus[r][c][t] = tmp;
					}
				}
			}
		}
	}

	// 바이러스의 양분 섭취
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int virusCount = index[r][c];

			int t;
			for (t = 0; t < virusCount; t++)
			{
				if (virus[r][c][t] == 0) continue;

				// 나이만큼 양분이 필요
				if (virus[r][c][t] <= food[r][c])
				{
					food[r][c] -= virus[r][c][t];
					virus[r][c][t]++;
				}
				else
					break;
			}

			// 죽은 바이러스는 양분으로 추가 
			for (; t < virusCount; t++)
			{
				food[r][c] += (virus[r][c][t] / 2);
				virus[r][c][t] = 0;
			}
		}
	}


}

void step3()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int virusCount = index[r][c];
			for (int t = 0; t < virusCount; t++)
			{
				if (virus[r][c][t] == 0) continue;
				if (virus[r][c][t] % 5 != 0) continue;

				for (int i = 0; i < 8; i++)
				{
					int nr, nc;

					nr = r + dr[i];
					nc = c + dc[i];

					if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

					int& idx = index[nr][nc];

					virus[nr][nc][idx++] = 1;
				}
			}
		}
	}
}

void step4()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			food[r][c] += MAP[r][c];
}

int getAnswer()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int end = index[r][c];

			for (int t = 0; t < end; t++)
				if (virus[r][c][t] != 0)
					sum++;
		}
	}

	return sum;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		for (int time = 0; time < K; time++)
		{
			step1_2();
			step3();
			step4();
		}

		printf("%d\n", getAnswer());
	}

	return 0;
}