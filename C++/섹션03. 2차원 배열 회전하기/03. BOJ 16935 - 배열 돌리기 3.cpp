#include <stdio.h>

#define MAX (100 + 10)

#define FLIP_UPDOWN (1)
#define FLIP_LEFTRIGHT (2)
#define CLOCKWISE (3)
#define COUNTER_CLOCKWISE (4)
#define SPLIT_CLOCKWISE (5)
#define SPLIT_COUNTER_CLOCKWISE (6)

int N, M, R;
int MAP[MAX][MAX];
int temp[MAX][MAX];

void input()
{
	scanf("%d %d %d", &N, &M, &R);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%d", &MAP[r][c]);
}

void copyMAP(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			copy[r][c] = original[r][c];
}

void printMap()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
}

void flipUpdown()
{
	copyMAP(temp, MAP);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			MAP[r][c] = temp[N + 1 - r][c];
}

void flipLeftRight()
{
	copyMAP(temp, MAP);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			MAP[r][c] = temp[r][M + 1 - c];
}

void clockwise()
{
	copyMAP(temp, MAP);

	int t = N;
	N = M;
	M = t;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			MAP[r][c] = temp[M + 1 - c][r];
}

void counterClockwise()
{
	copyMAP(temp, MAP);

	int t = N;
	N = M;
	M = t;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			MAP[r][c] = temp[c][N + 1 - r];
}

void splitClockwise()
{
	copyMAP(temp, MAP);

	// 1, 2
	// 4, 3
	// 1 -> 2 -> 3 -> 4 -> 1
	int sr1, sc1, sr2, sc2, sr3, sc3, sr4, sc4;
	int halfN, halfM;

	halfN = (N / 2);
	halfM = (M / 2);

	sr1 = 1; sc1 = 1;
	sr2 = 1; sc2 = halfM + 1;
	sr3 = halfN + 1; sc3 = halfM + 1;
	sr4 = halfN + 1; sc4 = 1;

	for (int r = 0; r < halfN; r++)
		for (int c = 0; c < halfM; c++)
			MAP[sr2 + r][sc2 + c] = temp[sr1 + r][sc1 + c];

	for (int r = 0; r < halfN; r++)
		for (int c = 0; c < halfM; c++)
			MAP[sr3 + r][sc3 + c] = temp[sr2 + r][sc2 + c];

	for (int r = 0; r < halfN; r++)
		for (int c = 0; c < halfM; c++)
			MAP[sr4 + r][sc4 + c] = temp[sr3 + r][sc3 + c];

	for (int r = 0; r < halfN; r++)
		for (int c = 0; c < halfM; c++)
			MAP[sr1 + r][sc1 + c] = temp[sr4 + r][sc4 + c];
}

void splitCounterClockwise()
{
	copyMAP(temp, MAP);

	// 1, 2
	// 4, 3
	// 1 <- 2 <- 3 <- 4 <- 1
	int sr1, sc1, sr2, sc2, sr3, sc3, sr4, sc4;
	int halfN, halfM;

	halfN = (N / 2);
	halfM = (M / 2);

	sr1 = 1; sc1 = 1;
	sr2 = 1; sc2 = halfM + 1;
	sr3 = halfN + 1; sc3 = halfM + 1;
	sr4 = halfN + 1; sc4 = 1;

	for (int r = 0; r < halfN; r++)
		for (int c = 0; c < halfM; c++)
			MAP[sr1 + r][sc1 + c] = temp[sr2 + r][sc2 + c];

	for (int r = 0; r < halfN; r++)
		for (int c = 0; c < halfM; c++)
			MAP[sr2 + r][sc2 + c] = temp[sr3 + r][sc3 + c];

	for (int r = 0; r < halfN; r++)
		for (int c = 0; c < halfM; c++)
			MAP[sr3 + r][sc3 + c] = temp[sr4 + r][sc4 + c];

	for (int r = 0; r < halfN; r++)
		for (int c = 0; c < halfM; c++)
			MAP[sr4 + r][sc4 + c] = temp[sr1 + r][sc1 + c];
}

int main()
{
	input();

	for (int r = 0; r < R; r++)
	{
		int COMMAND;

		scanf("%d", &COMMAND);

		if (COMMAND == FLIP_UPDOWN) flipUpdown();
		else if (COMMAND == FLIP_LEFTRIGHT) flipLeftRight();
		else if (COMMAND == CLOCKWISE) clockwise();
		else if (COMMAND == COUNTER_CLOCKWISE) counterClockwise();
		else if (COMMAND == SPLIT_CLOCKWISE) splitClockwise();
		else if (COMMAND == SPLIT_COUNTER_CLOCKWISE) splitCounterClockwise();
	}

	printMap();

	return 0;
}