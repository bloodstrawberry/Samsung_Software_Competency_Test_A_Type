#include <stdio.h>

#define MAX (50 + 5)

#define CLOCKWISE (0)
#define COUNTER_CLOCKWISE (1)

int T;
int N, M, Q;

int circle[MAX][MAX];
int visit[MAX][MAX];

int X[MAX];
int D[MAX];
int K[MAX];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &Q);

	for (int r = 0; r < MAX; r++)
		for (int c = 0; c < MAX; c++)
			circle[r][c] = 0;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%d", &circle[r][c]);

	for (int i = 1; i <= Q; i++)
		scanf("%d %d %d", &X[i], &D[i], &K[i]);
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", circle[r][c]);
		putchar('\n');
	}
}

void rotate(int x, int d, int k)
{
	int arr[MAX] = { 0 };

	if (d == COUNTER_CLOCKWISE) k = -k;

	for (int r = x; r <= N; r += x)
	{
		int index = 0;
		for (int c = 1; c <= M; c++) arr[index++] = circle[r][c];

		for (int i = 0; i < index; i++)
		{
			int newIndex = (i - k) % index;

			newIndex = newIndex < 0 ? newIndex + index : newIndex;

			circle[r][i + 1] = arr[newIndex];
		}
	}
}

bool BFS(int r, int c)
{
	int rp, wp;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (circle[nr][nc] == 0) continue;

			if ((circle[nr][nc] != circle[r][c]) || visit[nr][nc] == true) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;
		}

		if (out.c == 1)
		{
			if (circle[r][c] == circle[out.r][M] && visit[out.r][M] == false)
			{
				queue[wp].r = out.r;
				queue[wp++].c = M;

				visit[out.r][M] = true;
			}
		}
		else if (out.c == M)
		{
			if (circle[r][c] == circle[out.r][1] && visit[out.r][1] == false)
			{
				queue[wp].r = out.r;
				queue[wp++].c = 1;

				visit[out.r][1] = true;
			}
		}
	}

	if (wp > 1)
	{
		for (int i = 0; i < wp; i++)
		{
			int r, c;

			r = queue[i].r;
			c = queue[i].c;

			circle[r][c] = 0;
		}

		return true;
	}

	return false;
}

void makeAverage()
{
	int sum, count, avg;

	sum = count = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (circle[r][c] != 0)
			{
				sum += circle[r][c];
				count++;
			}
		}
	}

	if (count == 0) return;

	avg = sum / count;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (circle[r][c] == 0) continue;

			if (circle[r][c] < avg) circle[r][c]++;
			else if (circle[r][c] > avg) circle[r][c]--;
		}
	}
}

void startGame()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			visit[r][c] = false;

	bool deleteCheck = false;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (circle[r][c] == 0 || visit[r][c] == true) continue;

			bool check = BFS(r, c);
			if (check == true) deleteCheck = true;
		}
	}

	if (deleteCheck == false) makeAverage();
}

void simulate()
{
	for (int q = 1; q <= Q; q++)
	{
		rotate(X[q], D[q], K[q]);
		startGame();
	}
}

int getAnswer()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			sum += circle[r][c];

	return sum;
}

int main()
{
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