#include <stdio.h>

#define MAX (12 + 5)

#define WHITE (0)
#define RED (1)
#define BLUE (2)

int T;
int N, K;
int MAP[MAX][MAX];

struct HORSE
{
	int r;
	int c;
	int dir;
	int pos; // position
};

HORSE horse[10 + 3];
int hcnt;

int board[MAX][MAX][10 + 3];
int index[MAX][MAX]; 

// -, 오른쪽, 왼쪽, 위쪽, 아래쪽
int dr[] = { 0, 0, 0, -1, 1 };
int dc[] = { 0, 1, -1, 0, 0 };

void input()
{
	scanf("%d %d", &N, &K);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = BLUE;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			index[r][c] = 0;

	hcnt = 1; // 1번 말부터 K번 말까지
	for (int k = 0; k < K; k++)
	{
		int r, c, dir;

		scanf("%d %d %d", &r, &c, &dir);

		horse[hcnt].r = r;
		horse[hcnt].c = c;
		horse[hcnt].dir = dir;

		int& position = index[r][c];
		
		board[r][c][position] = hcnt;
		horse[hcnt].pos = position;

		position++;

		hcnt++;
	}
}

void printBoard() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int idx = index[r][c];
			if (idx == 0) continue;

			printf("%d, %d : ", r, c);
			for (int i = 0; i < idx; i++)
				printf("%d ", board[r][c][i]);
			putchar('\n');
		}
	}
	putchar('\n');
}

void moveWhite(int number)
{
	HORSE h = horse[number];
	int sr, sc, dir;
	int nr, nc;

	sr = h.r;
	sc = h.c;
	dir = h.dir;

	nr = sr + dr[dir];
	nc = sc + dc[dir];

	int front = h.pos;
	int& back = index[sr][sc];
	int& nextBack = index[nr][nc];

	for (int k = front; k < back; k++)
	{
		int selectedNumber = board[sr][sc][k];

		horse[selectedNumber].r = nr;
		horse[selectedNumber].c = nc;
		horse[selectedNumber].pos = nextBack;

		board[nr][nc][nextBack++] = selectedNumber;
	}

	back = front;
}

void moveRed(int number)
{
	HORSE h = horse[number];
	int sr, sc, dir;
	int nr, nc;

	sr = h.r;
	sc = h.c;
	dir = h.dir;

	nr = sr + dr[dir];
	nc = sc + dc[dir];

	int front = h.pos;
	int& back = index[sr][sc];
	int& nextBack = index[nr][nc];

	for (int k = back - 1; k >= front; k--)
	{
		int selectedNumber = board[sr][sc][k];

		horse[selectedNumber].r = nr;
		horse[selectedNumber].c = nc;
		horse[selectedNumber].pos = nextBack;

		board[nr][nc][nextBack++] = selectedNumber;
	}

	back = front;
}

int simulation()
{
	int changeDir[5] = { 0, 2, 1, 4, 3 };

	for (int i = 1; i <= 1000; i++)
	{
		// printBoard();
		// printf("===================================\n");

		// 1번 말 부터 이동
		for (int h = 1; h < hcnt; h++)
		{
			int sr, sc, dir;
			int nr, nc;
			
			sr = horse[h].r;
			sc = horse[h].c;
			dir = horse[h].dir;

			nr = sr + dr[dir];
			nc = sc + dc[dir];

			if (MAP[nr][nc] == WHITE) moveWhite(h);
			else if (MAP[nr][nc] == RED) moveRed(h);
			else if (MAP[nr][nc] == BLUE)
			{
				dir = changeDir[dir];
				horse[h].dir = dir;

				nr = sr + dr[dir];
				nc = sc + dc[dir];

				if (MAP[nr][nc] == WHITE) moveWhite(h);
				else if (MAP[nr][nc] == RED) moveRed(h);
				// BLUE는 아무 일도 하지 않음.
			}

			if (index[nr][nc] >= 4) return i;
		}
	}

	return -1;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		printf("%d\n", simulation());
	}

	return 0;
}