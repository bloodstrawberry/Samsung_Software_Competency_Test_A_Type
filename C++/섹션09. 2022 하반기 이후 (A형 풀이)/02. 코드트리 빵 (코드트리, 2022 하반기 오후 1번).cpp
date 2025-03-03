#include <stdio.h>

#define MAX_N (15 + 5)
#define MAX_M (30 + 5)

#define INF (0x7fff0000)
#define BASECAMP (1)
#define WALL (2)

int T;

int N, M;

int MAP[MAX_N][MAX_N];
int BLOCK[MAX_N][MAX_N]; // 이동 불가 확인

struct RC
{
	int r;
	int c;
};

RC STORE[MAX_M];
RC PLAYER[MAX_M];
RC queue[MAX_N * MAX_N];

// ↑, ←, →, ↓
int dr[] = { -1, 0, 0, 1 };
int dc[] = { 0, -1, 1, 0 };

void input()
{
	scanf("%d %d\n", &N, &M);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = BLOCK[r][c] = 0;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);

	for (int m = 1; m <= M; m++)
	{
		int r, c;

		scanf("%d %d", &r, &c);

		STORE[m].r = r;
		STORE[m].c = c;
	}
}

void printStatus() // for debug
{
	int tmpMAP[MAX_N][MAX_N] = { 0 };

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			tmpMAP[r][c] = MAP[r][c];

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			if (tmpMAP[r][c] == BASECAMP) tmpMAP[r][c] = -1;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			if (BLOCK[r][c] == WALL) tmpMAP[r][c] = -2;

	for (int p = 1; p <= M; p++)
		tmpMAP[PLAYER[p].r][PLAYER[p].c] = p;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", tmpMAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void printBefore(RC before[MAX_N][MAX_N]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("(%d, %d) ", before[r][c].r, before[r][c].c);
		putchar('\n');
	}
	putchar('\n');
}

RC getNextStep(int index) // BFS
{
	RC ret;
	int rp, wp;
	int visit[MAX_N][MAX_N] = { 0 };
	RC before[MAX_N][MAX_N] = { 0 };

	rp = wp = 0;

	int sr = PLAYER[index].r;
	int sc = PLAYER[index].c;
	int er = STORE[index].r;
	int ec = STORE[index].c;

	queue[wp].r = sr;
	queue[wp++].c = sc;

	visit[sr][sc] = 1;

	before[sr][sc].r = -1;
	before[sr][sc].c = -1;

	while (rp < wp)
	{
		RC out = queue[rp++];

		if (er == out.r && ec == out.c)
		{
			int tr = er;
			int tc = ec;
			while (1)
			{
				int br, bc; // 이전 좌표

				br = before[tr][tc].r;
				bc = before[tr][tc].c;

				if (br == sr && bc == sc) break;

				tr = br;
				tc = bc;
			}

			ret.r = tr;
			ret.c = tc;

			return ret;

		}
	
		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;
			if (visit[nr][nc] != 0 || BLOCK[nr][nc] == WALL) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = visit[out.r][out.c] + 1;

			before[nr][nc] = out;
		}	
	}

	ret.r = ret.c = -1;
	
	return ret; // for debug
}

RC getBaseCamp(int index) // BFS
{
	RC ret;
	int rp, wp;
	int visit[MAX_N][MAX_N] = { 0 };

	rp = wp = 0;

	int sr = STORE[index].r;
	int sc = STORE[index].c;

	queue[wp].r = sr;
	queue[wp++].c = sc;

	visit[sr][sc] = 1;

	ret.r = ret.c = INF;
	int minDistance = INF;
	while (rp < wp)
	{
		RC out = queue[rp++];

		// basecamp를 찾은 경우
		if (MAP[out.r][out.c] == BASECAMP && BLOCK[out.r][out.c] == 0)
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

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;
			if (visit[nr][nc] != 0 || BLOCK[nr][nc] == WALL) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = visit[out.r][out.c] + 1;
		}
	}

	return ret;
}

int simulate()
{
	int time = 0;
	while (1)
	{
		// 1.
		RC nextStep[MAX_M] = { 0 };
		for (int p = 1; p <= time; p++)
		{
			if (p > M) break;

			if (PLAYER[p].r == STORE[p].r && PLAYER[p].c == STORE[p].c) continue;

			nextStep[p] = getNextStep(p);
		}

		// 2.
		int count = 0;
		for (int p = 1; p <= time; p++)
		{
			if (p > M) break;

			if (PLAYER[p].r == STORE[p].r && PLAYER[p].c == STORE[p].c)
			{
				count++;
				continue;
			}

			int nr, nc;

			nr = nextStep[p].r;
			nc = nextStep[p].c;

			PLAYER[p].r = nr;
			PLAYER[p].c = nc;

			if (nr == STORE[p].r && nc == STORE[p].c)
				BLOCK[nr][nc] = WALL;

		}

		if (count == M) return time;

		time++;

		// 3.
		if (time <= M)
		{
			RC position = getBaseCamp(time);

			BLOCK[position.r][position.c] = WALL;

			PLAYER[time] = position;
		}
	}

	return -1; // for debug
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		printf("%d\n", simulate());
	}

	return 0;
}