#include <stdio.h>

#define MAX (50 + 5)

#define LEFT (0) // 서
#define UP (1) // 북
#define RIGHT (2) // 동
#define DOWN (3) // 남

int N, M;
int MAP[MAX][MAX];
int visit[MAX][MAX];

int answers[MAX * MAX];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

// 서쪽, 북쪽, 동쪽, 남쪽
int dr[] = { 0, -1, 0, 1 };
int dc[] = { -1, 0, 1, 0 };

int WALL[16 + 3][5] = {
	{ 0, 0, 0, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 1, 1, 0, 0 },
	{ 0, 0, 1, 0 },
	{ 1, 0, 1, 0 },
	{ 0, 1, 1, 0 },
	{ 1, 1, 1, 0 },
	{ 0, 0, 0, 1 },
	{ 1, 0, 0, 1 },
	{ 0, 1, 0, 1 },
	{ 1, 1, 0, 1 },
	{ 0, 0, 1, 1 },
	{ 1, 0, 1, 1 },
	{ 0, 1, 1, 1 },
	{ 1, 1, 1, 1 }, 
};

// room1 = room1에 적힌 값
int isOpen(int room1, int room2, int direction)
{
	if (direction == LEFT)
		return !(WALL[room1][LEFT] || WALL[room2][RIGHT]);

	if (direction == UP) 
		return !(WALL[room1][UP] || WALL[room2][DOWN]);

	if (direction == RIGHT) 
		return !(WALL[room1][RIGHT] || WALL[room2][LEFT]);

	if (direction == DOWN) 
		return !(WALL[room1][DOWN] || WALL[room2][UP]);

	return -1; // error
}

void input()
{
	scanf("%d %d", &M, &N);

	// init
	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= M + 1; c++)
			MAP[r][c] = 15; // 모두 벽

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", visit[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

int BFS(int r, int c, int mark)
{
	int rp, wp;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = mark;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];
		
			if (isOpen(MAP[out.r][out.c], MAP[nr][nc], i) == 0 ||
				visit[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = mark;
		}
	}

	return wp;
}

int main()
{
	int answerCount, mark, maxAnswer, maxAreaSum;

	input();

	answerCount = 1; // 1번부터 입력
	mark = 1;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (visit[r][c] == 0)
				answers[answerCount++] = BFS(r, c, mark++);
		}
	}

	maxAnswer = 0;
	for (int i = 1; i <= answerCount; i++) // 1번 부터 counting
	{
		if (maxAnswer < answers[i])
			maxAnswer = answers[i];
	}

	maxAreaSum = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				// if (nr < 1 || nc < 1 || nr > N || nc > M) continue;
				if (visit[r][c] == visit[nr][nc]) continue;

				int tmpArea = answers[visit[r][c]] + answers[visit[nr][nc]];
				if (maxAreaSum < tmpArea) maxAreaSum = tmpArea;
			}
		}
	}

	printf("%d\n%d\n%d\n", answerCount - 1, maxAnswer, maxAreaSum);

	// printMap();

	return 0;
}