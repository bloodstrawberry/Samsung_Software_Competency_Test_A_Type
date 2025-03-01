#include <stdio.h>

#define MAX (50 + 10)
#define TORNADO_POSITION (-1)

int T;
int N, M, time;
int MAP[MAX][MAX];
int tmpMAP[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC tornado[2];
int tcnt;

RC arr[MAX * MAX]; // for rotate

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &time);

	tcnt = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			scanf("%d", &MAP[r][c]);

			if (MAP[r][c] == TORNADO_POSITION)
			{
				tornado[tcnt].r = r;
				tornado[tcnt++].c = c;
			}
		}
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
}

void copyMap(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int i = 1; i <= N; i++)
		for (int k = 0; k <= M + 1; k++)
			copy[i][k] = original[i][k];
}

void diffusion()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			tmpMAP[r][c] = 0;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (MAP[r][c] <= 0) continue;

			int dust, count;

			dust = count = 0;
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (nr < 1 || nc < 1 || nr > N || nc > M) continue;
				if (MAP[nr][nc] == TORNADO_POSITION) continue;

				dust = MAP[r][c] / 5;

				tmpMAP[nr][nc] += dust;
				count++;
			}

			MAP[r][c] -= (dust * count);
		}
	}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			MAP[r][c] += tmpMAP[r][c];
}

void rotateStep(int sr, int sc, int n, int m, int rotateCount)
{
	int er, ec;

	er = sr + n - 1;
	ec = sc + m - 1;

	copyMap(tmpMAP, MAP);

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

		MAP[front.r][front.c] = tmpMAP[arr[i].r][arr[i].c];
	}
}

void cleaning()
{
	int up_r = tornado[0].r;
	int down_r = tornado[1].r;

	rotateStep(1, 1, up_r, M, 1);
	MAP[up_r][1] = TORNADO_POSITION;
	MAP[up_r][2] = 0;

	rotateStep(down_r, 1, (N - up_r), M, -1);
	MAP[down_r][1] = TORNADO_POSITION;
	MAP[down_r][2] = 0;
}

int getAnswer()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			if (MAP[r][c] != TORNADO_POSITION) sum += MAP[r][c];

	return sum;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		for (int t = 0; t < time; t++)
		{
			diffusion();
			cleaning();
			// printMap();
		}

		printf("%d\n", getAnswer());
	}

	return 0;
}