#include <stdio.h>

#define MAX_N (50 + 5)
#define MAX_M (100 + 10)

int T;

int N, M;
int MAP[MAX_N][MAX_N];
int D[MAX_M];
int P[MAX_M];

int snail[MAX_N][MAX_N];
int monster[MAX_N * MAX_N];

// ←, ↓, →, ↑ for snail
int drs[] = { 0, 1, 0, -1 };
int dcs[] = { -1, 0, 1, 0 };

// →, ↓, ←, ↑
int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };

void input()
{
	scanf("%d %d", &N, &M);
	
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);

	for (int m = 0; m < M; m++)
		scanf("%d %d", &D[m], &P[m]);
}

void printMap(int map[MAX_N][MAX_N]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void makeSnail(int map[MAX_N][MAX_N], int arr[MAX_M])
{
	int sr, sc, direction;
	int index, size;

	sr = sc = (N + 1) / 2;
	direction = 0;
	index = 0;
	size = 0;

	map[sr][sc] = arr[index++];
	for (int i = 0; i < 2 * N - 1; i++)
	{
		if (i % 2 == 0) size++;

		for (int s = 0; s < size; s++)
		{
			int nr, nc;

			nr = sr + drs[direction];
			nc = sc + dcs[direction];

			map[nr][nc] = arr[index++];

			sr = nr;
			sc = nc;
		}

		direction++;

		if (direction == 4) direction = 0;
	}
}

int deleteMonster()
{
	int score, count, start;

	score = 0;
	start = count = 1;

	int mcnt = 1;
	for (int i = 1; i < N * N; i++)
	{
		if (monster[i] == monster[i + 1]) count++;
		else
		{
			if (count < 4)
			{
				for (int k = start; k < start + count; k++)
					monster[mcnt++] = monster[k];
			}
			else
			{
				score += (monster[i] * count);
			}

			count = 1;
			start = i + 1;
		}
	}

	// 남은 칸을 0으로 만들기
	for (int i = mcnt; i < N * N; i++) monster[i] = 0;

	return score;
}

void makeNewTower()
{
	int newMonster[MAX_N * MAX_N] = { 0 };
	int ncnt, count;

	ncnt = count = 1;
	for (int i = 1; i < N * N; i++)
	{
		if (monster[i] == 0) break;

		if (monster[i] == monster[i + 1]) count++;
		else
		{
			newMonster[ncnt++] = count;
			newMonster[ncnt++] = monster[i];

			count = 1;
		}

		if (ncnt == N * N) break;
	}

	for (int i = 1; i < ncnt; i++) monster[i] = newMonster[i];

	makeSnail(MAP, monster);
}

int simulate()
{
	int sr, sc;

	sr = sc = (N + 1) / 2;

	int score = 0;
	for (int m = 0; m < M; m++)
	{
		int d, p;

		d = D[m];
		p = P[m];

		for (int k = 1; k <= p; k++)
		{
			int nr, nc;

			nr = sr + (dr[d]) * k;
			nc = sc + (dc[d]) * k;

			score += MAP[nr][nc];
			MAP[nr][nc] = 0;

			int index = snail[nr][nc];
			monster[index] = 0;
		}

		int mcnt = 1;
		for (int i = 1; i < N * N; i++)
			if (monster[i] != 0) monster[mcnt++] = monster[i];

		// 남은 칸을 0으로 만들기
		for (int i = mcnt; i < N * N; i++) monster[i] = 0;

		while (1)
		{
			int result = deleteMonster();

			if (result == 0) break;

			score += result;
		}

		makeNewTower();
	}

	return score;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		// init
		int snailIndex[MAX_N * MAX_N] = { 0 };
		for (int i = 0; i < N * N; i++) snailIndex[i] = i;

		makeSnail(snail, snailIndex);

		//printMap(snail);

		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				monster[snail[r][c]] = MAP[r][c];

		printf("%d\n", simulate());
	}

	return 0;
}