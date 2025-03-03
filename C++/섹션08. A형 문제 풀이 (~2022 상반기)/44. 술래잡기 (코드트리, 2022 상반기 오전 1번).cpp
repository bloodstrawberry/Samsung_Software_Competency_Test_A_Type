#include <stdio.h>

#define MAX (100 + 5)

int T;
int N, M, H, K;

int MAP[MAX][MAX]; // 나무
int snail[MAX][MAX];

struct PERSON
{
	int r;
	int c;
	int dir;
	bool dead;
};

PERSON runner[MAX * MAX];
int rcnt;

PERSON taggerInfo[MAX * MAX * 2];
int tcnt;

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d %d", &N, &M, &H, &K);

	rcnt = tcnt = 0;

	// runner
	for (int m = 0; m < M; m++)
	{
		int r, c, d;
		scanf("%d %d %d", &r, &c, &d);

		runner[rcnt].dead = false; 

		runner[rcnt].r = r;
		runner[rcnt].c = c;

		runner[rcnt++].dir = d;
	}

	// MAP init
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			MAP[r][c] = 0;

	// MAP
	for (int h = 0; h < H; h++)
	{
		int r, c;

		scanf("%d %d", &r, &c);

		MAP[r][c] = 1;
	}
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void makeSnail()
{
	int sr, sc, direction;
	int index, size;

	sr = sc = (N + 1) / 2;
	direction = 0;
	index = 1;
	size = 0;

	snail[sr][sc] = index++;

	taggerInfo[tcnt].r = sr;
	taggerInfo[tcnt++].c = sc;

	for (int i = 0; i < 2 * N - 1; i++)
	{
		if (i % 2 == 0) size++;

		for (int s = 0; s < size; s++)
		{
			int nr, nc;

			nr = sr + dr[direction];
			nc = sc + dc[direction];

			snail[nr][nc] = index++;

			sr = nr;
			sc = nc;

			taggerInfo[tcnt].r = nr;
			taggerInfo[tcnt++].c = nc;
		}

		direction++;

		if (direction == 4) direction = 0;
	}

	tcnt = N * N;
	for (int i = 0; i < tcnt; i++)
		taggerInfo[tcnt + i] = taggerInfo[tcnt - i - 2];

	tcnt = 2 * N * N - 2;

	for (int i = 0; i < tcnt - 1; i++)
	{
		int r, c, nr, nc;

		r = taggerInfo[i].r;
		c = taggerInfo[i].c;
		nr = taggerInfo[i + 1].r;
		nc = taggerInfo[i + 1].c;

		if (nr - r == -1) taggerInfo[i].dir = 0; // 위
		else if (nr - r == 1) taggerInfo[i].dir = 2; // 아래
		else if (nc - c == 1) taggerInfo[i].dir = 1; // 오른쪽
		else if (nc - c == -1) taggerInfo[i].dir = 3; // 왼쪽
	}

	taggerInfo[tcnt - 1].dir = 0;

	return; // for debug
	printMap(snail);
	for (int i = 0; i < tcnt; i++)
		printf("%d] (%d, %d) / %d\n", i, taggerInfo[i].r, taggerInfo[i].c, taggerInfo[i].dir);
}

int abs(int x)
{
	return (x > 0) ? x : -x;
}

int getDistance(int r1, int c1, int r2, int c2)
{
	return abs(r1 - r2) + abs(c1 - c2);
}

void moveRunner(int k)
{
	PERSON tagger = taggerInfo[k % tcnt];

	int changeDir[4] = { 2, 3, 0, 1 };

	for (int i = 0; i < rcnt; i++)
	{
		if (runner[i].dead == true) continue;

		int sr, sc;

		sr = runner[i].r;
		sc = runner[i].c;

		int distance = getDistance(tagger.r, tagger.c, sr, sc);

		if (distance > 3) continue;

		int dir;
		int nr, nc;

		dir = runner[i].dir;

		nr = sr + dr[dir];
		nc = sc + dc[dir];

		if (nr < 1 || nc < 1 || nr > N || nc > N)
		{
			dir = changeDir[dir];
			runner[i].dir = dir;

			nr = sr + dr[dir];
			nc = sc + dc[dir];
		}

		if (nr == tagger.r && nc == tagger.c) continue;

		runner[i].r = nr;
		runner[i].c = nc;
	}
}

int moveTagger(int k)
{
	PERSON tagger = taggerInfo[(k + 1) % tcnt];

	int catchCount = 0;
	for (int d = 0; d < 3; d++)
	{
		int nr, nc;

		nr = tagger.r + dr[tagger.dir] * d;
		nc = tagger.c + dc[tagger.dir] * d;

		if (nr < 1 || nc < 1 || nr > N || nc > N) break;
		if (MAP[nr][nc] == 1) continue; // 나무

		for (int i = 0; i < rcnt; i++)
		{
			if (runner[i].dead == true) continue;

			if (runner[i].r == nr && runner[i].c == nc)
			{
				runner[i].dead = true;
				catchCount++;
			}
		}

	}

	return catchCount * (k + 1);
}

int simulate()
{
	int score = 0;
	for (int k = 0; k < K; k++)
	{
		moveRunner(k);

		score += moveTagger(k);
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

		makeSnail();

		printf("%d\n", simulate());
	}

	return 0;
}