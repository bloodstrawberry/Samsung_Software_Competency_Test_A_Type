#include <stdio.h>

#define MAX (20 + 5)
#define WALL (-1)

int T;
int N, M, K;

int MAP[MAX][MAX]; // 독점하고 있는 player 번호
int time[MAX][MAX]; // 독점 시간

struct PLAYER
{
	int r;
	int c;
	int dir;
	int priority[5][5];
	bool dead;
};

PLAYER player[MAX * MAX];

// -, 위, 아래, 왼쪽, 오른쪽
int dr[] = { 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, -1, 1 };

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = WALL;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &MAP[r][c]);

			int playerNumber = MAP[r][c];
			if (playerNumber != 0)
			{
				player[playerNumber].r = r;
				player[playerNumber].c = c;
			}
		}
	}

	for (int i = 1; i <= M; i++)
	{
		int dir;

		scanf("%d", &dir);

		player[i].dir = dir;
	}

	for (int i = 1; i <= M; i++)
		for (int d = 1; d <= 4; d++)
			scanf("%d %d %d %d", &player[i].priority[d][1], &player[i].priority[d][2], &player[i].priority[d][3], &player[i].priority[d][4]);
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

void printPlayer(int number) // for debug
{
	PLAYER p = player[number];
	printf("number %d / (%d, %d) / dir %d / dead %d\n", number, p.r, p.c, p.dir, p.dead);
}

void printPlayerAll() // for debug
{
	for (int m = 1; m <= M; m++)
		printPlayer(m);
}

int getDirection(int number)
{
	PLAYER p = player[number];
	int dir = p.dir;

	// 빈 공간 찾기
	for (int i = 1; i <= 4; i++)
	{
		int nr, nc, nextDir;

		nextDir = p.priority[dir][i]; // 우선순위에 의한 다음 방향
		nr = p.r + dr[nextDir];
		nc = p.c + dc[nextDir];

		if (MAP[nr][nc] == WALL) continue;

		if (time[nr][nc] == 0) 
			return nextDir;
	}

	// 자신의 구역 찾기
	for (int i = 1; i <= 4; i++)
	{
		int nr, nc, nextDir;

		nextDir = p.priority[dir][i]; // 우선순위에 의한 다음 방향
		nr = p.r + dr[nextDir];
		nc = p.c + dc[nextDir];

		if (MAP[nr][nc] == number) 
			return nextDir;
	}

	return -1; // for debug;
}

int simulate()
{
	int playerCount = M;
	for (int i = 1; i <= 1000; i++)
	{
		for (int p = 1; p <= M; p++)
		{
			if (player[p].dead == true) continue;

			int r, c;

			r = player[p].r;
			c = player[p].c;

			MAP[r][c] = p;
			time[r][c] = K;
		}

		int tmpMAP[MAX][MAX] = { 0 };
		for (int p = 1; p <= M; p++)
		{
			if (player[p].dead == true) continue;

			int sr, sc;
			int nr, nc, dir;

			sr = player[p].r;
			sc = player[p].c;

			dir = getDirection(p);

			nr = sr + dr[dir];
			nc = sc + dc[dir];

			// 이동 후, 해당 칸에 player가 두 명 이상 있는 경우 
			if (tmpMAP[nr][nc] == 0) // 아무도 없는 경우
			{
				player[p].r = nr;
				player[p].c = nc;
				player[p].dir = dir;

				tmpMAP[nr][nc] = p;
			}
			else
			{
				int anotherPlayer = tmpMAP[nr][nc];

				playerCount--;

				if (anotherPlayer < p) player[p].dead = true;
				else
				{
					player[anotherPlayer].dead = true;

					player[p].r = nr;
					player[p].c = nc;
					player[p].dir = dir;

					tmpMAP[nr][nc] = p;
				}
			}
		}

		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= N; c++)
			{
				if (tmpMAP[r][c] == 0) continue;

				MAP[r][c] = tmpMAP[r][c];
			}
		}

		// printf("MAP\n"); printMap(MAP);
		// printf("tmpMAP\n"); printMap(tmpMAP);

		if (playerCount == 1) return i;

		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				if(time[r][c] != 0) time[r][c]--;
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

		printf("%d\n", simulate());
	}

	return 0;
}