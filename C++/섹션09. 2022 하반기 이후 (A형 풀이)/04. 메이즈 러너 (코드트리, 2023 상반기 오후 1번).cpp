#include <stdio.h>

#define MAX (10 + 5)

#define PLAYER_NUMBER (10)
#define DESTINATION (-1)

#define UP (0)
#define RIGHT (1)
#define DOWN (2)
#define LEFT (3)

int T;

int N, M, K;
int MAP[MAX][MAX];

struct RCE
{
	int r;
	int c;
	bool escape; // Player 탈출 확인
};

RCE player[MAX];
RCE destination;

struct RCS
{
	int r;
	int c;
	int size; // 회전을 위한 크기
};

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);

	for (int m = 0; m < M; m++)
	{
		scanf("%d %d", &player[m].r, &player[m].c);
		player[m].escape = false;
	}

	scanf("%d %d", &destination.r, &destination.c);
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

void printStatus() // for debug
{
	int tmpMAP[MAX][MAX] = { 0 };
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			tmpMAP[r][c] = MAP[r][c];

	for (int m = 0; m < M; m++)
	{
		RCE p = player[m];

		printf("%d : %d, %d (exit : %d)\n", m, p.r, p.c, p.escape);
		if (p.escape == false)
			tmpMAP[p.r][p.c] = m + PLAYER_NUMBER;
	}

	putchar('\n');

	tmpMAP[destination.r][destination.c] = DESTINATION;

	printMap(tmpMAP);
}

void copyMap(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			copy[r][c] = original[r][c];
}

bool check()
{
	for (int m = 0; m < M; m++)
		if (player[m].escape == false) return false;

	return true;
}

int checkRow(RCE player)
{
	int dr = destination.r;
	int pr = player.r;

	// dr > pr -> 출구는 아래에
	// dr = pr -> 같은 행, 상하로 움직일 수 없음.
	// dr < pr -> 출구는 위에
	return dr - pr;
}

int checkColumn(RCE player)
{
	int dc = destination.c;
	int pc = player.c;

	// dc > pc -> 출구는 오른쪽에
	// dc = pc -> 같은 열, 좌우로 움직일 수 없음.
	// dc < pc -> 출구는 왼쪽에
	return dc - pc;
}

int move()
{
	int step = 0;
	for (int m = 0; m < M; m++)
	{
		if (player[m].escape == true) continue;

		int nextR[4] = { 0 };
		int nextC[4] = { 0 };

		for (int i = 0; i < 4; i++)
		{
			nextR[i] = player[m].r + dr[i];
			nextC[i] = player[m].c + dc[i];
		}

		int upDown = checkRow(player[m]);
		int leftRight = checkColumn(player[m]);
		
		int direction = -1;

		// 항상 출구를 향해 움직이기 때문에 격자를 벗어나지 않음.
		if (upDown < 0 && MAP[nextR[UP]][nextC[UP]] == 0) direction = UP;
		else if (upDown > 0 && MAP[nextR[DOWN]][nextC[DOWN]] == 0) direction = DOWN;
		else if (leftRight < 0 && MAP[nextR[LEFT]][nextC[LEFT]] == 0) direction = LEFT;
		else if (leftRight > 0 && MAP[nextR[RIGHT]][nextC[RIGHT]] == 0) direction = RIGHT;

		if (direction == -1) continue;

		player[m].r = player[m].r + dr[direction];
		player[m].c = player[m].c + dc[direction];

		if (player[m].r == destination.r && player[m].c == destination.c)
			player[m].escape = true;

		step++;
	}

	return step;
}

bool rotateCheck(int map[MAX][MAX], int sr, int sc, int size)
{
	bool destinationCheck, playerCheck;

	destinationCheck = playerCheck = false;
	for (int r = sr; r < sr + size; r++)
	{
		for (int c = sc; c < sc + size; c++)
		{
			if (map[r][c] >= PLAYER_NUMBER) playerCheck = true;
			else if (map[r][c] == DESTINATION) destinationCheck = true;
		}
	}

	return playerCheck && destinationCheck;
}

RCS getSqureInfo()
{
	RCS ret = { 0 };
	for (int size = 2; size <= N; size++)
	{
		for (int r = 1; r <= N - size + 1; r++)
		{
			for (int c = 1; c <= N - size + 1; c++)
			{
				int tmpMAP[MAX][MAX] = { 0 };

				copyMap(tmpMAP, MAP);

				for (int m = 0; m < M; m++)
				{
					if (player[m].escape == true) continue;

					tmpMAP[player[m].r][player[m].c] = m + PLAYER_NUMBER;
				}

				tmpMAP[destination.r][destination.c] = DESTINATION;

				if (rotateCheck(tmpMAP, r, c, size) == true)
				{
					ret.r = r;
					ret.c = c;
					ret.size = size;

					return ret;
				}
			}
		}
	}

	// for debug
	ret.r = ret.c = ret.size = -1;
	
	return ret;
}

void rotate(int map[MAX][MAX], int sr, int sc, int size)
{
	int tmpMAP[MAX][MAX] = { 0 };

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			tmpMAP[r][c] = map[sr + r][sc + c];

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			map[sr + r][sc + c] = tmpMAP[size - 1 - c][r];
}

RCE rotateRC(RCE rce, RCS squareInfo)
{
	RCE ret = { 0 };
	int tmpMAP[MAX][MAX] = { 0 };

	tmpMAP[rce.r][rce.c] = 1;
	
	rotate(tmpMAP, squareInfo.r, squareInfo.c, squareInfo.size);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (tmpMAP[r][c] == 1)
			{
				ret.r = r;
				ret.c = c;

				return ret;
			}
		}
	}

	// for debug
	ret.r = ret.c = -1;

	return ret;
}

void durabilityDown(RCS squareInfo)
{
	int sr = squareInfo.r;
	int er = squareInfo.r + squareInfo.size;
	int sc = squareInfo.c;
	int ec = squareInfo.c + squareInfo.size;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] == 0) continue;

			if (sr <= r && r < er && sc <= c && c < ec)
				MAP[r][c]--;
		}
	}
}

void rotateMaze()
{
	RCS squareInfo = getSqureInfo();

	rotate(MAP, squareInfo.r, squareInfo.c, squareInfo.size);

	destination = rotateRC(destination, squareInfo);

	for (int m = 0; m < M; m++)
	{
		if (player[m].escape == true) continue;

		player[m] = rotateRC(player[m], squareInfo);
	}

	durabilityDown(squareInfo);
}

void simulate()
{
	int sum = 0;
	for (int k = 0; k < K; k++)
	{
		int step = move();

		sum += step;

		if (check() == true) break;

		rotateMaze();
	}

	printf("%d\n", sum);
	printf("%d %d\n", destination.r, destination.c);
}

int main()
{
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		//printStatus();

		simulate();
	}

	return 0;
}