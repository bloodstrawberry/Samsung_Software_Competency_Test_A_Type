#include <stdio.h>

#define MAX (20 + 5)

#define EAST (1)
#define WEST (2)
#define NORTH (3)
#define SOUTH (4)

int T;

int N, M, R, C, K; // X = R, Y = C
int MAP[MAX][MAX];
int command[1000 + 50];

struct CUBE
{
		  int up;
	int left; int top; int right; 
	          int down;
	          int bottom;
};

CUBE cube;

// -, 동, 서, 북, 남 
int dr[] = { 0, 0, 0, -1, 1 };
int dc[] = { 0, 1, -1, 0, 0 };

void input()
{
	scanf("%d %d %d %d %d", &N, &M, &R, &C, &K);

	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			scanf("%d", &MAP[r][c]);

	for (int k = 0; k < K; k++) scanf("%d", &command[k]);
}

void printMap() // for debug
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
	for (int k = 0; k < K; k++) printf("%d ", command[k]);
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

void simulate()
{
	for (int k = 0; k < K; k++)
	{
		int cmd = command[k];

		/* 바깥으로 나가게 되는 경우 */
		if (R + dr[cmd] < 0 || R + dr[cmd] > N - 1
			|| C + dc[cmd] < 0 || C + dc[cmd] > M - 1) continue;

		R = R + dr[cmd];
		C = C + dc[cmd];

		if (cmd == EAST) moveEast();
		else if (cmd == WEST) moveWest();
		else if (cmd == NORTH) moveNorth();
		else if (cmd == SOUTH) moveSouth();

		// 칸에 쓰여져 있는 수가 0이면, 주사위 바닥 면의 수가 복사
		if (MAP[R][C] == 0) MAP[R][C] = cube.bottom;
		else // 0이 아니면, 주사위 바닥면으로 숫자를 복사하고, 해당 칸은 0
		{
			cube.bottom = MAP[R][C];
			MAP[R][C] = 0;
		}

		printf("%d\n", cube.top);
	}
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		simulate();	
	}

	return 0;
}