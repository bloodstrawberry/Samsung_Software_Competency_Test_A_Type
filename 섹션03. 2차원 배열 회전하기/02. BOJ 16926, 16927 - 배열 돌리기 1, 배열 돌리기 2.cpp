#include <stdio.h>

#define MAX (300 + 30)

int N, M, R;
int MAP[MAX][MAX];
int temp[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC arr[MAX * MAX];

void input()
{
	scanf("%d %d %d", &N, &M, &R);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%d", &MAP[r][c]);
}

void copyMap(int copy[MAX][MAX], int original[MAX][MAX])
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

void rotateStep(int sr, int sc, int n, int m, int rotateCount)
{
	int er, ec;

	er = sr + n - 1;
	ec = sc + m - 1;

	copyMap(temp, MAP);

	int index = 0;
	for (int c = sc; c <= ec; c++)
	{
		arr[index].r = sr;
		arr[index++].c = c;
	}

	for (int r = sr + 1; r <= er; r++)
	{
		arr[index].r = r;
		arr[index++].c = ec;
	}

	for (int c = ec - 1; c >= sc; c--)
	{
		arr[index].r = er;
		arr[index++].c = c;
	}

	for (int r = er - 1; r >= sr + 1; r--)
	{
		arr[index].r = r;
		arr[index++].c = sc;
	}

	for (int i = 0; i < index; i++)
	{
		int newIndex = (i - rotateCount) % index;

		newIndex = newIndex < 0 ? newIndex + index : newIndex;

		RC front = arr[newIndex];

		MAP[front.r][front.c] = temp[arr[i].r][arr[i].c];
	}
}

void rotate(int rotateCount)
{
	int sr, sc, n, m;
	int step = N < M ? N / 2 : M / 2;

	sr = sc = 1;
	n = N, m = M;
	for (int s = 0; s < step; s++)
	{
		rotateStep(sr, sc, n, m, rotateCount);

		sr++, sc++;
		n -= 2, m -= 2;
	}
}

int main()
{
	input();

	rotate(R);

	printMap();

	return 0;
}