#include <stdio.h>

#define MAX (500 + 50)

int T, N, D;
int MAP[MAX][MAX];
int temp[MAX][MAX];

void input()
{
	scanf("%d %d", &N, &D);

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

void rotate45Clockwise()
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

void rotate45CounterClockwise()
{
	copyMap(temp, MAP);

	int arr[MAX] = { 0 };
	int half = (N + 1) / 2;

	// 행 가운데를 왼쪽 아래 ~ 오른쪽 위로
	for (int c = 1; c <= N; c++) arr[c] = temp[half][c];
	for (int i = 1; i <= N; i++) MAP[N - i + 1][i] = arr[i];

	// 왼쪽 위 ~ 오른쪽 아래 대각선을 행 가운데로
	for (int i = 1; i <= N; i++) arr[i] = temp[i][i];
	for (int c = 1; c <= N; c++) MAP[half][c] = arr[c];

	// 열 가운데를 왼쪽 위 ~ 오른쪽 아래로
	for (int r = 1; r <= N; r++) arr[r] = temp[r][half];
	for (int i = 1; i <= N; i++) MAP[i][i] = arr[i];

	// 오른쪽 위 ~ 왼쪽 아래 대각선을 열 가운데로
	for (int i = 1; i <= N; i++) arr[i] = temp[i][N - i + 1];
	for (int r = 1; r <= N; r++) MAP[r][half] = arr[r];
}

int main()
{
	scanf("%d", &T);

	for (int tc = 1; tc <= T; tc++)
	{
		input();

		int count = D / 45;

		// D가 음수인 경우 회전 횟수는 양수로 변경
		count = count > 0 ? count : -count;
		for (int c = 0; c < count; c++)
		{
			if (D >= 0) rotate45Clockwise();
			else rotate45CounterClockwise();
		}

		printMap();
	}

	return 0;
}