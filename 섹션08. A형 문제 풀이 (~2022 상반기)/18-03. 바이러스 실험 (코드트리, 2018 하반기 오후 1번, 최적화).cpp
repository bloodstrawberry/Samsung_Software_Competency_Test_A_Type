#include <stdio.h>

#define MAX (10 + 5)
#define MAX_VIRUS (100000)
#define OFFSET (10000)

int T;
int N, M, K;
int food[MAX][MAX]; // 양분
int MAP[MAX][MAX]; // 증가되는 양분

int virus[MAX][MAX][MAX_VIRUS]; // deque
int front[MAX][MAX];
int back[MAX][MAX];

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

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			front[r][c] = back[r][c] = OFFSET;

	for (int i = 0; i < M; i++)
	{
		int r, c, age;

		scanf("%d %d %d", &r, &c, &age);

		int& virusCount = back[r][c];
		virus[r][c][virusCount++] = age;
	}
}

void printVirus() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if ((back[r][c] - front[r][c]) == 0) continue;

			printf("%d, %d) : ", r, c);
			for (int t = front[r][c]; t < back[r][c]; t++)
				printf("%d ", virus[r][c][t]);
			putchar('\n');
		}
	}
	putchar('\n');
}

void step1_2()
{
	// 바이러스의 양분 섭취
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int start = front[r][c];
			int end = back[r][c];

			int& fr = front[r][c];
			int& bk = back[r][c];

			int t;
			for (t = start; t < end; t++)
			{
				if (virus[r][c][t] <= food[r][c])
				{
					food[r][c] -= virus[r][c][t];
					virus[r][c][t]++;

					fr++;
					virus[r][c][bk++] = virus[r][c][t];
				}
				else
					break;
			}

			for (; t < end; t++)
			{
				food[r][c] += (virus[r][c][t] / 2);
				fr++;
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
			int start = front[r][c];
			int end = back[r][c];

			for (int t = start; t < end; t++)
			{				
				if (virus[r][c][t] % 5 != 0) continue;

				for (int i = 0; i < 8; i++)
				{
					int nr, nc;

					nr = r + dr[i];
					nc = c + dc[i];

					if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

					int& fr = front[nr][nc];

					virus[nr][nc][--fr] = 1;
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
		for (int c = 1; c <= N; c++)
			sum += (back[r][c] - front[r][c]);
	
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

	// 필요한 메모리 확인
	//for (int r = 1; r <= N; r++)
	//	for (int c = 1; c <= N; c++)
	//		printf("%d %d / %d %d\n", r, c, front[r][c], back[r][c]);

	return 0;
}