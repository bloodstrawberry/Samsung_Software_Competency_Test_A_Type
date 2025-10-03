#include <stdio.h>

#define MAX (30 + 5)
#define WALL (-1) // 물건
#define INF (0x7fff0000)

int T;
int N, K, L;

int MAP[MAX][MAX];
bool check[MAX][MAX]; // 청소기 좌표

struct RC
{
	int r;
	int c;
};

RC cleaner[50 + 5];
RC queue[MAX * MAX];

// →, ↓, ←, ↑
int dr[] = { 0, 1, 0, -1 };
int dc[] = { 1, 0, -1, 0 };

void input()
{
	scanf("%d %d %d", &N, &K, &L);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = WALL;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);

	for (int k = 1; k <= K; k++)
	{
		int r, c;

		scanf("%d %d", &r, &c);

		cleaner[k].r = r;
		cleaner[k].c = c;
	}
}

void printMap() // for debug
{
	for (int k = 1; k <= K; k++)
		printf("%d] %d, %d\n", k, cleaner[k].r, cleaner[k].c);
	putchar('\n');

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

RC getPosition(int index) // BFS
{
	RC ret;
	int rp, wp;
	int visit[MAX][MAX] = { 0 };

	rp = wp = 0;

	int sr = cleaner[index].r;
	int sc = cleaner[index].c;

	if (MAP[sr][sc] > 0) return { sr, sc };

	queue[wp].r = sr;
	queue[wp++].c = sc;

	visit[sr][sc] = 1;

	ret.r = ret.c = INF;
	int minDistance = INF;
	while (rp < wp)
	{
		RC out = queue[rp++];

		// 먼지를 찾은 경우 + 다른 청소기가 위치하지 않은 경우
		if (MAP[out.r][out.c] > 0 && check[out.r][out.c] == false)
		{
			if (visit[out.r][out.c] < minDistance)
			{
				minDistance = visit[out.r][out.c];
				ret = out;
			}
			else if (visit[out.r][out.c] == minDistance)
			{
				if (out.r < ret.r) ret = out;
				else if (out.r == ret.r)
				{
					if (out.c < ret.c)
						ret = out;
				}
			}

			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (MAP[nr][nc] == WALL || check[nr][nc] == true) continue;
			if (visit[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = visit[out.r][out.c] + 1;
		}
	}

	if (ret.r == INF) return { sr, sc };

	return ret;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

int getDirection(int index)
{
	RC target = cleaner[index];

	int total = min(MAP[target.r][target.c], 20);
	for (int i = 0; i < 4; i++)
	{
		int nr, nc;

		nr = target.r + dr[i];
		nc = target.c + dc[i];

		if (MAP[nr][nc] == WALL) continue;

		total += min(MAP[nr][nc], 20);
	}

	int maxDir = -1;
	int maxDust = -1;
	int changeDir[] = { 2, 3, 0, 1 };

	for (int i = 0; i < 4; i++)
	{
		int reverse = changeDir[i];
		int nr, nc;

		nr = target.r + dr[reverse];
		nc = target.c + dc[reverse];

		int dust = total;
		if (MAP[nr][nc] != WALL) dust -= min(MAP[nr][nc], 20);

		if (maxDust < dust)
		{
			maxDust = dust;
			maxDir = i;
		}
	}

	return maxDir;
}

void clean(int index)
{
	int changeDir[] = { 2, 3, 0, 1 };
 
	RC target = cleaner[index];
	int direction = getDirection(index);
	int reverse = changeDir[direction];

	for (int i = 0; i < 4; i++)
	{
		if (i == reverse) continue;

		int nr, nc;

		nr = target.r + dr[i];
		nc = target.c + dc[i];

		if (MAP[nr][nc] == WALL) continue;

		MAP[nr][nc] -= 20;
		if (MAP[nr][nc] < 0) MAP[nr][nc] = 0;
	}

	MAP[target.r][target.c] -= 20;
	if (MAP[target.r][target.c] < 0) MAP[target.r][target.c] = 0;
}

void addDust()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] == 0 || MAP[r][c] == WALL) continue;

			MAP[r][c] += 5;
		}
	}
}

void spreadDust()
{
	int tmpMAP[MAX][MAX] = { 0 };
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] != 0) continue;

			int sum = 0;
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (MAP[nr][nc] == WALL) continue;

				sum += MAP[nr][nc];
			}

			tmpMAP[r][c] = sum / 10;
		}
	}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			MAP[r][c] += tmpMAP[r][c];
}

int getDust()
{
	int sum = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] == WALL) continue;

			sum += MAP[r][c];
		}
	}

	return sum;
}

void simulate()
{
	for (int l = 0; l < L; l++)
	{
		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				check[r][c] = false; // 청소기 좌표 초기화

		// 0. 현재 청소기 좌표 체크
		for (int k = 1; k <= K; k++)
			check[cleaner[k].r][cleaner[k].c] = true;

		// 1. 청소기 이동
		for (int k = 1; k <= K; k++)
		{
			RC rc = getPosition(k);

			check[cleaner[k].r][cleaner[k].c] = false;

			cleaner[k].r = rc.r;
			cleaner[k].c = rc.c;

			check[cleaner[k].r][cleaner[k].c] = true;
		}

		// 2. 청소
		for (int k = 1; k <= K; k++) clean(k);

		// 3. 먼지 축적
		addDust();

		// 4. 먼지 확산
		spreadDust();

		// 5. 출력
		printf("%d\n", getDust());
	}
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