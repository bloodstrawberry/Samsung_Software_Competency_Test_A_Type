#include <stdio.h>

#define MAX (20 + 5)

#define EAST (1)
#define WEST (2)
#define NORTH (3)
#define SOUTH (4)

int T;
int N, M;
int MAP[MAX][MAX];

bool visit[MAX][MAX];
int scoreBoard[MAX][MAX];

struct CUBE
{
	int up;
	int left; int top; int right;
	int down;
	int bottom;
};

CUBE cube;

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

// -, 동, 서, 북, 남 
int dr[] = { 0, 0, 0, -1, 1 };
int dc[] = { 0, 1, -1, 0, 0 };

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);
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

void printCube() // for debug
{
	printf("  %d\n", cube.up);
	printf("%d %d %d\n", cube.left, cube.top, cube.right);
	printf("  %d\n", cube.down);
	printf("  %d\n", cube.bottom);
	putchar('\n');
}

void moveEast()
{
	int tmp[6] = { cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom };

	cube.top = tmp[1];
	cube.right = tmp[2];
	cube.bottom = tmp[3];
	cube.left = tmp[5];
}

void moveWest()
{
	int tmp[6] = { cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom };

	cube.top = tmp[3];
	cube.right = tmp[5];
	cube.bottom = tmp[1];
	cube.left = tmp[2];
}

void moveNorth()
{
	int tmp[6] = { cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom };

	cube.up = tmp[2];
	cube.top = tmp[4];
	cube.down = tmp[5];
	cube.bottom = tmp[0];
}

void moveSouth()
{
	int tmp[6] = { cube.up, cube.left, cube.top, cube.right, cube.down, cube.bottom };

	cube.up = tmp[5];
	cube.top = tmp[0];
	cube.down = tmp[2];
	cube.bottom = tmp[4];
}

void BFS(int r, int c)
{
	int number;
	int rp, wp;

	number = MAP[r][c];

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 1; i <= 4; i++) 
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

			if (MAP[nr][nc] != number || visit[nr][nc] == true) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;
		}
	}

	for (int i = 0; i < wp; i++)
	{
		int r, c;

		r = queue[i].r;
		c = queue[i].c;

		scoreBoard[r][c] = number * wp;
	}
}

void makeScoreBoard()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			visit[r][c] = false;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (visit[r][c] == true) continue;

			BFS(r, c);
		}
	}

	// printMap(scoreBoard);
}

int simulate()
{
	// 동 : 1, 서 : 2, 북 : 3, 남 : 4
	int changeDir[5] = { 0, 2, 1, 4, 3 };
	int changeClock[5] = { 0, 4, 3, 1, 2 };
	int changeCounterClock[5] = { 0, 3, 4, 2, 1 };

	// 방향 전환 배열 만들기
	// changeDir[EAST] = WEST;
	// changeDir[WEST] = EAST;
	// changeDir[NORTH] = SOUTH;
	// changeDir[SOUTH] = NORTH;

	// changeClock[EAST] = SOUTH;
	// changeClock[WEST] = NORTH;
	// changeClock[NORTH] = EAST;
	// changeClock[SOUTH] = WEST;

	// changeCounterClock[EAST] = NORTH;
	// changeCounterClock[WEST] = SOUTH;
	// changeCounterClock[NORTH] = WEST;
	// changeCounterClock[SOUTH] = EAST;

	int sr, sc, dir;

	sr = sc = 1;
	dir = EAST;

	cube.up = 5;
	cube.left = 4; cube.top = 1; cube.right = 3;
	cube.down = 2;
	cube.bottom = 6;

	int score = 0;
	for (int i = 0; i < M; i++)
	{
		int nr, nc;

		nr = sr + dr[dir];
		nc = sc + dc[dir];

		if (nr < 1 || nc < 1 || nr > N || nc > N)
		{
			dir = changeDir[dir];
			nr = sr + dr[dir];
			nc = sc + dc[dir];
		}

		if (dir == EAST) moveEast();
		else if (dir == WEST) moveWest();
		else if (dir == NORTH) moveNorth();
		else if (dir == SOUTH) moveSouth();

		score += scoreBoard[nr][nc];

		int A = cube.bottom;
		int B = MAP[nr][nc];

		if (A > B) dir = changeClock[dir];
		else if (A < B) dir = changeCounterClock[dir];

		sr = nr;
		sc = nc;
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

		makeScoreBoard();

		printf("%d\n", simulate());
	}

	return 0;
}