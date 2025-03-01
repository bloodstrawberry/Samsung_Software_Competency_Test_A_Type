#include <stdio.h>

#define MAX (100 + 20)

int T;
int N, L;
int MAP[MAX][MAX];
int TMAP[MAX][MAX]; // transpose

void input()
{
	scanf("%d %d", &N, &L);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &MAP[r][c]);
			TMAP[c][r] = MAP[r][c];
		}
	}
}

int abs(int x)
{
	return (x > 0) ? x : -x;
}

bool isFlat(int arr[MAX], int start, int end)
{
	int value = arr[start];
	for (int i = start + 1; i <= end; i++)
		if (value != arr[i]) return false;

	return true;
}

int checkRow(int arr[MAX])
{
	bool visit[MAX] = { 0 };

	int inverse[MAX] = { 0 };
	bool visit_inverse[MAX] = { 0 };

	for (int c = 1; c <= N - 1; c++)
	{
		if (arr[c] == arr[c + 1]) continue;

		// 1) 높이 차이가 1 보다 큰 경우
		if (abs(arr[c] - arr[c + 1]) > 1) return 0;

		if (arr[c] > arr[c + 1])
		{
			// 2) 경사로의 길이만큼 낮은 칸의 보도블럭이 연속하지 않는 경우
			if (c + L > N) return 0;

			if (isFlat(arr, c + 1, c + L) == false) return 0;

			for (int k = c + 1; k <= c + L; k++)
				visit[k] = true;
		}
	}

	for (int c = 1; c <= N; c++)
	{
		inverse[c] = arr[N + 1 - c];
		visit_inverse[c] = visit[N + 1 - c];
	}

	for (int c = 1; c <= N - 1; c++)
	{
		if (inverse[c] == inverse[c + 1]) continue;

		// 1) 높이 차이가 1 보다 큰 경우
		if (abs(inverse[c] - inverse[c + 1]) > 1) return 0;

		if (inverse[c] > inverse[c + 1])
		{
			// 2) 경사로의 길이만큼 낮은 칸의 보도블럭이 연속하지 않는 경우
			if (c + L > N) return 0;

			if (isFlat(inverse, c + 1, c + L) == false) return 0;

			// 3) 경사로를 놓은 곳에 또 경사로를 놓은 경우
			for (int k = c + 1; k <= c + L; k++)
				if (visit_inverse[k] == true) return 0;
		}
	}

	return 1;
}

int checkAllRow()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
	{
		sum += checkRow(MAP[r]);
		sum += checkRow(TMAP[r]);
	}

	return sum;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		printf("%d\n", checkAllRow());
	}

	return 0;
}