#include <stdio.h>

#define MAX (4 + 3)
#define MAX_DIR (8 + 2)

int T;

int M, TURN;

bool grid[MAX][MAX];
int deadBody[MAX][MAX];

struct PACKMAN
{
	int r;
	int c;
};

PACKMAN packMan;

int monster[MAX][MAX][MAX_DIR]; // (r, c)에 dir 방향의 몬스터 수

int num_of_cases[10];
int position[64 + 10][3];
int pcnt;

// -, ↑, ←, ↓, →
int dr4[] = { 0, -1, 0, 1, 0 };
int dc4[] = { 0, 0, -1, 0, 1 };

// -, ↑, ↖, ←, ↙, ↓, ↘, →, ↗ 
int dr8[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dc8[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };

void input()
{
	scanf("%d %d %d %d", &M, &TURN, &packMan.r, &packMan.c);

	for (int r = 1; r <= 4; r++)
		for (int c = 1; c <= 4; c++)
			for (int d = 1; d <= 8; d++)
				monster[r][c][d] = 0;

	for (int m = 0; m < M; m++)
	{
		int r, c, d;

		scanf("%d %d %d", &r, &c, &d);

		monster[r][c][d]++;
	}

	for (int r = 1; r <= 4; r++)
		for (int c = 1; c <= 4; c++)
			deadBody[r][c] = 0;

	for (int r = 0; r <= 5; r++)
		for (int c = 0; c <= 5; c++)
			grid[r][c] = true;

	for (int r = 1; r <= 4; r++)
		for (int c = 1; c <= 4; c++)
			grid[r][c] = false;
}

void printDeadBody() // for debug
{
	printf("Dead Body\n");
	for (int r = 1; r <= 4; r++)
	{
		for (int c = 1; c <= 4; c++)
			printf("%d ", deadBody[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void printMonster() // for debug
{
	for (int r = 1; r <= 4; r++)
	{
		for (int c = 1; c <= 4; c++)
		{
			printf("(%d, %d)\n", r, c);

			for (int d = 1; d <= 8; d++)
				printf("%d : %d / ", d, monster[r][c][d]);
			putchar('\n');
		}
	}
	putchar('\n');
}

void copyMonster(int copy[MAX][MAX][MAX_DIR], int original[MAX][MAX][MAX_DIR])
{
	for (int r = 1; r <= 4; r++)
		for (int c = 1; c <= 4; c++)
			for (int d = 1; d <= 8; d++)
				copy[r][c][d] = original[r][c][d];
}

void printCases()
{
	//for (int i = 0; i < 3; i++) printf("%d ", num_of_cases[i]);  
	//putchar('\n');

	position[pcnt][0] = num_of_cases[0];
	position[pcnt][1] = num_of_cases[1];
	position[pcnt++][2] = num_of_cases[2];
}

void DFS(int depth)
{
	if (depth == 3)
	{
		printCases();
		return;
	}

	for (int i = 1; i <= 4; i++)
	{
		num_of_cases[depth] = i;

		DFS(depth + 1);
	}
}

void moveMonster()
{
	int tmpMonster[MAX][MAX][MAX_DIR] = { 0 };
	for (int r = 1; r <= 4; r++)
	{
		for (int c = 1; c <= 4; c++)
		{
			for (int d = 1; d <= 8; d++)
			{
				if (monster[r][c][d] == 0) continue;

				int i;
				for (i = 0; i < 8; i++) // 반시계 방향 회전
				{
					int nr, nc, dir;

					dir = (d + i - 1 + 8) % 8 + 1;
					nr = r + dr8[dir];
					nc = c + dc8[dir];

					if ((nr == packMan.r && nc == packMan.c)
						|| deadBody[nr][nc] != 0
						|| grid[nr][nc] == true) continue;
					else
					{
						tmpMonster[nr][nc][dir] += monster[r][c][d];
						break;
					}
				}

				// 이동 불가
				if (i == 8) tmpMonster[r][c][d] += monster[r][c][d];				
			}
		}
	}

	copyMonster(monster, tmpMonster);
}

int getMonster(int step)
{
	PACKMAN tmpPackMan = packMan;
	int tmpMonster[MAX][MAX][MAX_DIR] = { 0 };

	copyMonster(tmpMonster, monster);

	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		int nr, nc;

		nr = tmpPackMan.r + dr4[position[step][i]];
		nc = tmpPackMan.c + dc4[position[step][i]];

		if (grid[nr][nc] == true) return -1;

		for (int d = 1; d <= 8; d++)
		{
			count += tmpMonster[nr][nc][d];
			tmpMonster[nr][nc][d] = 0;
		}

		tmpPackMan.r = nr;
		tmpPackMan.c = nc;
	}

	return count;
}

void movePackMan(int step)
{
	for (int i = 0; i < 3; i++)
	{
		int nr, nc;

		nr = packMan.r + dr4[position[step][i]];
		nc = packMan.c + dc4[position[step][i]];

		for (int d = 1; d <= 8; d++)
		{
			if (monster[nr][nc][d] == 0) continue;

			monster[nr][nc][d] = 0;
			deadBody[nr][nc] = 3;
		}

		packMan.r = nr;
		packMan.c = nc;
	}	   	  
}

void disappear()
{
	for (int r = 1; r <= 4; r++)
		for (int c = 1; c <= 4; c++)
			if (deadBody[r][c] != 0) deadBody[r][c]--;
}

void simulate()
{
	for (int t = 0; t < TURN; t++)
	{
		int egg[MAX][MAX][MAX_DIR] = { 0 };

		// 1. 몬스터 복제 시도
		copyMonster(egg, monster);

		// 2. 몬스터 이동
		moveMonster();

		int step, maxMonster;

		step = maxMonster = -1;
		for (int i = 0; i < 64; i++)
		{
			int tmp = getMonster(i);

			if (tmp > maxMonster)
			{
				maxMonster = tmp;
				step = i;
			}
		}

		// 3. 팩맨 이동
		movePackMan(step);

		// 4. 몬스터 시체 소멸
		disappear();

		// 5. 몬스터 복제 완성
		for (int r = 1; r <= 4; r++)
			for (int c = 1; c <= 4; c++)
				for (int d = 1; d <= 8; d++)
					monster[r][c][d] += egg[r][c][d];
	}
}

int getAnswer()
{
	int sum = 0;
	for (int r = 1; r <= 4; r++)
		for (int c = 1; c <= 4; c++)
			for (int d = 1; d <= 8; d++)
				sum += monster[r][c][d];

	return sum;
}

int main()
{
	DFS(0);

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