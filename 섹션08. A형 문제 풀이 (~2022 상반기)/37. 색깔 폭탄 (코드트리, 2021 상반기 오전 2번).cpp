#include <stdio.h>

#define MAX (20 + 5)
#define INF (0x7fff0000)

#define RED (0)
#define BLACK (-1)
#define EMPTY (-2)

int T;
int N, M;
int MAP[MAX][MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

struct BOMB
{
	int total; // 전체 폭탄 개수
	int red; // 빨간 폭탄 개수
	int r; // 행
	int c; // 열
};

void input()
{
	scanf("%d %d\n", &N, &M);
	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = BLACK;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);
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

void rotate() // 반시계 방향 회전
{
	int tmpMAP[MAX][MAX] = { 0 };

	copyMap(tmpMAP, MAP);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			MAP[r][c] = tmpMAP[c][N - r + 1];
}

BOMB BFS(int r, int c)
{
	int rp, wp, bomb;
	bool visit[MAX][MAX] = { 0 };
	BOMB selectedBomb = { 0 };

	selectedBomb.total = 1;
	selectedBomb.r = r;
	selectedBomb.c = c;

	rp = wp = 0;

	bomb = MAP[r][c];
	
	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (MAP[nr][nc] == BLACK || visit[nr][nc] == true) continue;

			if (MAP[nr][nc] == bomb || MAP[nr][nc] == RED)
			{
				queue[wp].r = nr;
				queue[wp++].c = nc;

				visit[nr][nc] = true;

				selectedBomb.total++;

				if (MAP[nr][nc] == RED) selectedBomb.red++;
			}
		}
	}

	return selectedBomb;
}

void deleteBomb(int r, int c) // BFS
{
	int rp, wp, bomb;
	bool visit[MAX][MAX] = { 0 };

	rp = wp = 0;

	bomb = MAP[r][c];
	MAP[r][c] = EMPTY;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (MAP[nr][nc] == BLACK || visit[nr][nc] == true) continue;

			if (MAP[nr][nc] == bomb || MAP[nr][nc] == RED)
			{
				queue[wp].r = nr;
				queue[wp++].c = nc;

				visit[nr][nc] = true;
				MAP[nr][nc] = EMPTY;
			}
		}
	}
}

// a가 우선순위가 더 높으면 true
bool isPriority(BOMB a, BOMB b)
{
	if (a.total != b.total) return a.total > b.total;
	if (a.red != b.red) return a.red < b.red;
	if (a.r != b.r) return a.r > b.r;

	return a.c < b.c;
}

void bombDownColumn(int col)
{
	for (int r = N; r >= 1; r--)
	{
		if (MAP[r][col] == BLACK || MAP[r][col] == EMPTY) continue;

		int sr = r;
		while (1)
		{
			if (MAP[sr + 1][col] != EMPTY) break;

			if (MAP[sr + 1][col] == EMPTY)
			{
				int tmp = MAP[sr][col];
				MAP[sr][col] = MAP[sr + 1][col];
				MAP[sr + 1][col] = tmp;
			}

			sr++;
		}
	}
}

void bombDown()
{
	for (int col = 1; col <= N; col++)
		bombDownColumn(col);
}

int simulate()
{
	int score = 0;
	while (1)
	{
		BOMB selectedBomb = { 0 };

		selectedBomb.red = selectedBomb.c = INF;
		selectedBomb.total = selectedBomb.r = -1;
		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= N; c++)
			{
				if (MAP[r][c] == BLACK || MAP[r][c] == RED || MAP[r][c] == EMPTY) continue;

				BOMB tmp = BFS(r, c);

				if (tmp.total == 1) continue;

				if (isPriority(tmp, selectedBomb) == true)
					selectedBomb = tmp;
			}
		}

		if (selectedBomb.total == -1) break;

		score += (selectedBomb.total * selectedBomb.total);
		
		deleteBomb(selectedBomb.r, selectedBomb.c);

		bombDown();
		rotate();
		bombDown();
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

		printf("%d\n", simulate());
	}

	return 0;
}