#include <stdio.h>

#define MAX (5 + 3)

int T;

int K, M;

int MAP[MAX][MAX];
bool visit[MAX][MAX];
int piece[300 + 50];
int pcnt;

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
	scanf("%d %d", &K, &M);

	for (int r = 1; r <= 5; r++)
		for (int c = 1; c <= 5; c++)
			scanf("%d", &MAP[r][c]);

	pcnt = 0;

	for (int m = 0; m < M; m++) scanf("%d", &piece[m]);
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 1; r <= 5; r++)
	{
		for (int c = 1; c <= 5; c++)
			printf("%d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void copyMap(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int i = 1; i <= 5; i++)
		for (int k = 1; k <= 5; k++)
			copy[i][k] = original[i][k];
}

void rotate(int map[MAX][MAX], int sr, int sc)
{
	int tmpMAP[MAX][MAX] = { 0 };

	int size = 3;
	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			tmpMAP[r][c] = map[sr + r][sc + c];

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			map[sr + r][sc + c] = tmpMAP[size - 1 - c][r];
}

int BFS(int map[MAX][MAX], int r, int c)
{
	int rp, wp, number;

	rp = wp = 0;

	number = map[r][c];

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr = out.r + dr[i];
			int nc = out.c + dc[i];

			if (map[nr][nc] != number || visit[nr][nc] == true) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;
		}
	}

	if (wp < 3) return 0;

	for (int i = 0; i < wp; i++)
	{
		int r, c;

		r = queue[i].r;
		c = queue[i].c;

		map[r][c] = 0;
	}

	return wp;
}

int getItem(int map[MAX][MAX])
{
	for (int r = 1; r <= 5; r++)
		for (int c = 1; c <= 5; c++)
			visit[r][c] = false;

	int sum = 0;
	for (int r = 1; r <= 5; r++)
	{
		for (int c = 1; c <= 5; c++)
		{
			if (visit[r][c] == true) continue;

			int count = BFS(map, r, c);

			sum += count;
		}
	}

	return sum;
}

void setItem(int map[MAX][MAX])
{
	for (int c = 1; c <= 5; c++)
		for (int r = 5; r >= 1; r--)
			if (map[r][c] == 0) map[r][c] = piece[pcnt++];
}

int simulate()
{
	int maxItemCount = 0;
	int maxMAP[MAX][MAX] = { 0 };

	// 회전 각도가 작고
	for (int rot = 1; rot <= 3; rot++)
	{
		// 열이 작고
		for (int c = 1; c <= 3; c++)
		{
			// 행이 작은 순서대로
			for (int r = 1; r <= 3; r++)
			{
				int tmpMAP[MAX][MAX] = { 0 };

				copyMap(tmpMAP, MAP);

				for (int rotCount = 1; rotCount <= rot; rotCount++)
					rotate(tmpMAP, r, c);

				int itemCount = getItem(tmpMAP);
				if (maxItemCount < itemCount)
				{
					maxItemCount = itemCount;
					copyMap(maxMAP, tmpMAP);
				}
			}
		}
	}

	if (maxItemCount == 0) return 0;

	int sum = maxItemCount;
	while (1)
	{
		setItem(maxMAP);

		int itemCount = getItem(maxMAP);

		if (itemCount == 0) break;

		sum += itemCount;
	}

	copyMap(MAP, maxMAP);

	return sum;
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		for (int k = 0; k < K; k++)
		{
			int result = simulate();

			if (result == 0) break;

			printf("%d ", result);
		}
	}

	return 0;
}