#include <stdio.h>

#define MAX (500 + 50)

int T, N, D;
int MAP[MAX][MAX];
int temp[MAX][MAX];

void input()
{
	scanf("%d %d", &N, &D);

	// if (D < 0) D += 360;
	D = (D + 360) % 360;	

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
}

void copyMap(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			copy[r][c] = original[r][c];
}

void rotate45()
{
	copyMap(temp, MAP);

	int arr[MAX] = { 0 };
	int half = (N + 1) / 2;

	for (int c = 1; c <= N; c++) arr[c] = temp[half][c];
	for (int i = 1; i <= N; i++) MAP[i][i] = arr[i];

	for (int i = 1; i <= N; i++) arr[i] = temp[i][i];
	for (int r = 1; r <= N; r++) MAP[r][half] = arr[r];

	for (int r = 1; r <= N; r++) arr[r] = temp[r][half];
	for (int i = 1; i <= N; i++) MAP[i][N - i + 1] = arr[i];

	for (int i = 1; i <= N; i++) arr[i] = temp[N - i + 1][i];
	for (int c = 1; c <= N; c++) MAP[half][c] = arr[c];
}

int main()
{
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++)
	{
		input();

		// 회전
		int count = D / 45;
		for (int c = 0; c < count; c++) rotate45();

		printMap();
	}

	return 0;
}