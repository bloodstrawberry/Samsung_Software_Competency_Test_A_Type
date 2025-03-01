#include <stdio.h>

#define MAX (128 + 10)

#define FLIP_UPDOWN (1)
#define FLIP_LEFTRIGHT (2)
#define CLOCKWISE (3)
#define COUNTER_CLOCKWISE (4)
#define SPLIT_UPDOWN (5)
#define SPLIT_LEFTRIGHT (6)
#define SPLIT_CLOCKWISE (7)
#define SPLIT_COUNTER_CLOCKWISE (8)

int N, R, S;
int MAP[MAX][MAX];
int temp[MAX][MAX];

void input()
{
	scanf("%d %d", &N, &R);

	S = (1 << N);

	for (int r = 1; r <= S; r++)
		for (int c = 1; c <= S; c++)
			scanf("%d", &MAP[r][c]);
}

void copyMAP(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int r = 1; r <= S; r++)
		for (int c = 1; c <= S; c++)
			copy[r][c] = original[r][c];
}

void printMap()
{
	for (int r = 1; r <= S; r++)
	{
		for (int c = 1; c <= S; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
}

void flipUpDownDivide(int sr, int sc, int size)
{
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			temp[r][c] = MAP[sr + r][sc + c];

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			MAP[sr + r][sc + c] = temp[size - 1 - r][c];
}

void flipUpdown(int level)
{
	int divide = (1 << level);

	for (int r = 1; r <= S; r += divide)
		for (int c = 1; c <= S; c += divide)
			flipUpDownDivide(r, c, divide);
}

void flipLeftRightDivide(int sr, int sc, int size)
{
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			temp[r][c] = MAP[sr + r][sc + c];

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			MAP[sr + r][sc + c] = temp[r][size - 1 - c];
}

void flipLeftRight(int level)
{
	int divide = (1 << level);

	for (int r = 1; r <= S; r += divide)
		for (int c = 1; c <= S; c += divide)
			flipLeftRightDivide(r, c, divide);
}

void clockwiseDivide(int sr, int sc, int size)
{
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			temp[r][c] = MAP[sr + r][sc + c];

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			MAP[sr + r][sc + c] = temp[size - 1 - c][r];
}

void clockwise(int level)
{
	int divide = (1 << level);

	for (int r = 1; r <= S; r += divide)
		for (int c = 1; c <= S; c += divide)
			clockwiseDivide(r, c, divide);
}

void counterClockwiseDivide(int sr, int sc, int size)
{
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			temp[r][c] = MAP[sr + r][sc + c];

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			MAP[sr + r][sc + c] = temp[c][size - 1 - r];
}

void counterClockwise(int level)
{
	int divide = (1 << level);

	for (int r = 1; r <= S; r += divide)
		for (int c = 1; c <= S; c += divide)
			counterClockwiseDivide(r, c, divide);
}

void splitUpDown(int level)
{
	flipUpdown(N);
	flipUpdown(level);
}

void splitLeftRight(int level)
{
	flipLeftRight(N);
	flipLeftRight(level);
}

void splitClockwise(int level)
{
	clockwise(N);
	counterClockwise(level);
}

void splitCounterClockwise(int level)
{
	counterClockwise(N);
	clockwise(level);
}

int main()
{
	input();

	for (int r = 0; r < R; r++)
	{
		int COMMAND, level;

		scanf("%d %d", &COMMAND, &level);

		if (COMMAND == FLIP_UPDOWN) flipUpdown(level);
		else if (COMMAND == FLIP_LEFTRIGHT) flipLeftRight(level);
		else if (COMMAND == CLOCKWISE) clockwise(level);
		else if (COMMAND == COUNTER_CLOCKWISE) counterClockwise(level);
		else if (COMMAND == SPLIT_UPDOWN) splitUpDown(level);
		else if (COMMAND == SPLIT_LEFTRIGHT) splitLeftRight(level);
		else if (COMMAND == SPLIT_CLOCKWISE) splitClockwise(level);
		else if (COMMAND == SPLIT_COUNTER_CLOCKWISE) splitCounterClockwise(level);
	}

	printMap();

	return 0;
}