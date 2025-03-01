#include <stdio.h>

#define MAX (10 + 3)
#define MAX_K (10000 + 500)

#define START (4)
#define END (9)

#define WALL (-1)

int T;

int K;
int MAP[MAX][MAX];

int TYPE[MAX_K];
int R[MAX_K];
int C[MAX_K];

void input()
{
	for (int r = 0; r < MAX; r++)
		for (int c = 0; c < MAX; c++)
			MAP[r][c] = 0;

	MAP[0][10] = MAP[1][10] = MAP[2][10] = MAP[3][10] = WALL;
	MAP[10][0] = MAP[10][1] = MAP[10][2] = MAP[10][3] = WALL;

	scanf("%d", &K);

	for (int k = 0; k < K; k++)
		scanf("%d %d %d", &TYPE[k], &R[k], &C[k]);
}

void printMap() // for debug
{
	for (int r = 0; r < 11; r++)
	{
		for (int c = 0; c < 11; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void moveRed(int type, int sr, int sc)
{
	int c = sc;
	if (type == 1)
	{
		while (1)
		{
			if (MAP[sr][c + 1] != 0) break;

			c++;
		}

		MAP[sr][c] = 1;		
	}
	else if (type == 2)
	{
		while (1)
		{
			if (MAP[sr][c + 2] != 0) break;

			c++;
		}

		MAP[sr][c] = MAP[sr][c + 1] = 1;
	}
	else if (type == 3)
	{
		while (1)
		{
			if (MAP[sr][c + 1] != 0) break;
			if (MAP[sr + 1][c + 1] != 0) break;

			c++;
		}

		MAP[sr][c] = MAP[sr + 1][c] = 1;
	}
}

void moveYellow(int type, int sr, int sc)
{
	int r = sr;
	if (type == 1)
	{
		while (1)
		{
			if (MAP[r + 1][sc] != 0) break;

			r++;
		}

		MAP[r][sc] = 1;
	}
	else if (type == 2)
	{
		while (1)
		{
			if (MAP[r + 1][sc] != 0) break;
			if (MAP[r + 1][sc + 1] != 0) break;

			r++;
		}

		MAP[r][sc] = MAP[r][sc + 1] = 1;
	}
	else if (type == 3)
	{
		while (1)
		{
			if (MAP[r + 2][sc] != 0) break;

			r++;
		}

		MAP[r][sc] = MAP[r + 1][sc] = 1;
	}
}

void deleteRed(int col)
{
	for (int c = col; c > START; c--)	
		for (int r = 0; r < 4; r++)
			MAP[r][c] = MAP[r][c - 1];

	MAP[0][START] = MAP[1][START] = MAP[2][START] = MAP[3][START] = 0;
}

void deleteYellow(int row)
{
	for (int r = row; r > START; r--)
		for (int c = 0; c < 4; c++)
			MAP[r][c] = MAP[r - 1][c];

	MAP[START][0] = MAP[START][1] = MAP[START][2] = MAP[START][3] = 0;
}

int getScoreRed()
{
	for (int c = START + 2; c <= END; c++)
	{
		int cnt = 0;
		for (int r = 0; r < 4; r++) cnt += MAP[r][c];

		if (cnt == 4)
		{
			deleteRed(c);
			return 1;
		}
	}

	return 0;
}

int getScoreYellow()
{
	for (int r = START + 2; r <= END; r++)
	{
		int cnt = 0;
		for (int c = 0; c < 4; c++) cnt += MAP[r][c];

		if (cnt == 4)
		{
			deleteYellow(r);
			return 1;
		}
	}

	return 0;
}

bool checkRed()
{
	for (int r = 0; r < 4; r++)
		if (MAP[r][START + 1] == 1) return true;

	return false;
}

bool checkYellow()
{
	for (int c = 0; c < 4; c++)
		if (MAP[START + 1][c] == 1) return true;

	return false;
}

void simulate()
{
	int score = 0;
	for (int k = 0; k < K; k++)
	{
		moveRed(TYPE[k], R[k], C[k]);
		moveYellow(TYPE[k], R[k], C[k]);

		score += getScoreRed();
		score += getScoreRed();

		score += getScoreYellow();
		score += getScoreYellow();

		if (checkRed() == true) deleteRed(END);
		if (checkRed() == true) deleteRed(END);

		if (checkYellow() == true) deleteYellow(END);
		if (checkYellow() == true) deleteYellow(END);
	}

	int blockCount = 0;

	// red
	for (int c = START + 2; c <= END; c++)
		for (int r = 0; r < 4; r++)
			blockCount += MAP[r][c];

	// yellow
	for (int r = START + 2; r <= END; r++)
		for (int c = 0; c < 4; c++)
			blockCount += MAP[r][c];

	printf("%d\n%d\n", score, blockCount);
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