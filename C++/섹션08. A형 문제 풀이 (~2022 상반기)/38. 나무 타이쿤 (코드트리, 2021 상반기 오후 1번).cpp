#include <stdio.h>

#define MAX_N (50 + 5)
#define MAX_M (100 + 10)

int T;

int N, M;
int MAP[MAX_N][MAX_N];
int D[MAX_M];
int P[MAX_M];

struct RC
{
	int r;
	int c;
};

RC supplement[MAX_N * MAX_N];
int scnt;

// ↖, ↗, ↘, ↙
int dr4[] = { -1, -1, 1, 1 };
int dc4[] = { -1, 1, 1, -1 };

// -, →, ↗, ↑, ↖, ←, ↙, ↓, ↘
int dr8[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };
int dc8[] = { 0, 1, 1, 0, -1, -1, -1, 0, 1 };

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = 0;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);

	for (int m = 0; m < M; m++)
		scanf("%d %d", &D[m], &P[m]);

	supplement[0].r = N; supplement[0].c = 1;
	supplement[1].r = N; supplement[1].c = 2;
	supplement[2].r = N - 1; supplement[2].c = 1;
	supplement[3].r = N - 1; supplement[3].c = 2;
	scnt = 4;
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void moveSupplement(int dir, int size)
{
	for (int i = 0; i < scnt; i++)
	{	
		int nr, nc;

		nr = supplement[i].r + dr8[dir] * (size % N);
		nc = supplement[i].c + dc8[dir] * (size % N);

		if (nr > N) nr -= N;
		if (nc > N) nc -= N;
		if (nr < 1) nr += N;
		if (nc < 1) nc += N;

		supplement[i].r = nr;
		supplement[i].c = nc;	
	}
}

void insert()
{
	for (int i = 0; i < scnt; i++)
	{
		int r, c;

		r = supplement[i].r;
		c = supplement[i].c;

		MAP[r][c]++;
	}
}

void grow()
{
	for (int s = 0; s < scnt; s++)
	{
		int r, c;

		r = supplement[s].r;
		c = supplement[s].c;

		int count = 0;
		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = r + dr4[i];
			nc = c + dc4[i];

			// if (MAP[nr][nc] > 0) count++;
			count += !!MAP[nr][nc];
		}

		MAP[r][c] += count;
	}
}

bool check(int r, int c)
{
	for (int i = 0; i < scnt; i++)
		if (supplement[i].r == r && supplement[i].c == c)
			return true;

	return false;
}

void makeSupplement()
{
	RC tmpSupplement[MAX_N * MAX_N] = { 0 };

	int tcnt = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] < 2) continue;

			// 특수 영양제를 투입한 좌표
			if (check(r, c) == true) continue;

			MAP[r][c] -= 2;

			tmpSupplement[tcnt].r = r;
			tmpSupplement[tcnt++].c = c;
		}
	}
	
	for (int i = 0; i < tcnt; i++)
		supplement[i] = tmpSupplement[i];

	scnt = tcnt;
}

void simulate()
{
	for (int m = 0; m < M; m++)
	{
		moveSupplement(D[m], P[m]);
		insert();
		grow();
		makeSupplement();
	}
}

int getAnswer()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			sum += MAP[r][c];

	return sum;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		simulate();

		printf("%d\n", getAnswer());
	}

	return 0;
}