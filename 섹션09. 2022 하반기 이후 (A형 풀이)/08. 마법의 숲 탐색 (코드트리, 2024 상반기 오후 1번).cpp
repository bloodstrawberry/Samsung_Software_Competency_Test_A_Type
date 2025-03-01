#include <stdio.h>

#define MAX (70 + 10)
#define MAX_K (1000 + 10)

#define BODY (1)
#define CENTER (2)
#define EXIT (3)
#define GOLEM_ID (10)

int T;

int R, C, K;

int MAP[MAX][MAX];
int start_c[MAX_K];
int exit_d[MAX_K];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

struct GOLEM
{
	int r;
	int c;
	int dir;
	int id;
};

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &R, &C, &K);

	for (int r = 0; r < MAX; r++)
		for (int c = 0; c < MAX; c++)
			MAP[r][c] = 0;

	for (int k = 1; k <= K; k++)
		scanf("%d %d", &start_c[k], &exit_d[k]);
}

void printMAP() // for debug
{
	for (int r = 3; r <= R + 2; r++)
	{
		for (int c = 1; c <= C; c++)
			printf("%2d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

// 남쪽
bool checkSouth(GOLEM golem)
{
	int gr, gc;

	gr = golem.r;
	gc = golem.c;

	if (gr == R + 1) return false;

	int nr[3] = { 0 };
	int nc[3] = { 0 };

	nr[0] = gr + 1;
	nc[0] = gc - 1;

	nr[1] = gr + 2;
	nc[1] = gc;

	nr[2] = gr + 1;
	nc[2] = gc + 1;

	for (int i = 0; i < 3; i++)
		if (MAP[nr[i]][nc[i]] != 0) return false;

	return true;
}

// 서쪽 + 남쪽
bool checkWest(GOLEM golem)
{
	int gr, gc;

	gr = golem.r;
	gc = golem.c;

	if (gc == 2) return false;

	int nr[3] = { 0 };
	int nc[3] = { 0 };

	nr[0] = gr - 1;
	nc[0] = gc - 1;

	nr[1] = gr;
	nc[1] = gc - 2;

	nr[2] = gr + 1;
	nc[2] = gc - 1;

	for (int i = 0; i < 3; i++)
		if (MAP[nr[i]][nc[i]] != 0) return false;

	GOLEM tmpGolem = { 0 };

	tmpGolem.r = gr;
	tmpGolem.c = gc - 1;

	return checkSouth(tmpGolem);
}

// 동쪽 + 남쪽
bool checkEast(GOLEM golem)
{
	int gr, gc;

	gr = golem.r;
	gc = golem.c;

	if (gc == C - 1) return false;

	int nr[3] = { 0 };
	int nc[3] = { 0 };

	nr[0] = gr - 1;
	nc[0] = gc + 1;

	nr[1] = gr;
	nc[1] = gc + 2;

	nr[2] = gr + 1;
	nc[2] = gc + 1;

	for (int i = 0; i < 3; i++)
		if (MAP[nr[i]][nc[i]] != 0) return false;

	GOLEM tmpGolem = { 0 };

	tmpGolem.r = gr;
	tmpGolem.c = gc + 1;

	return checkSouth(tmpGolem);
}

void setGolem(GOLEM golem)
{
	int gr, gc, gid, dir;

	gr = golem.r;
	gc = golem.c;
	gid = golem.id;
	dir = golem.dir;

	MAP[gr][gc] = CENTER + gid;

	for (int i = 0; i < 4; i++)
	{
		int nr, nc;

		nr = gr + dr[i];
		nc = gc + dc[i];

		MAP[nr][nc] = BODY + gid;
	}

	MAP[gr + dr[dir]][gc + dc[dir]] = EXIT + gid;
}

int BFS(GOLEM golem)
{
	int rp, wp;
	bool visit[MAX][MAX] = { 0 };

	rp = wp = 0;

	queue[wp].r = golem.r;
	queue[wp++].c = golem.c;

	visit[golem.r][golem.c] = true;

	int maxR = 0;
	while (rp < wp)
	{
		RC out = queue[rp++];

		if (maxR < out.r) maxR = out.r;

		int golemID = (MAP[out.r][out.c] / GOLEM_ID) * GOLEM_ID;
		int type = MAP[out.r][out.c] % GOLEM_ID;

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > (R + 2) || nc > C) continue;
			if (MAP[nr][nc] == 0 || visit[nr][nc] == true) continue;

			int nGolemID = (MAP[nr][nc] / GOLEM_ID) * GOLEM_ID;

			// 뽑은 좌표의 타입이 출구가 아니고
			// 다음 좌표의 ID가 다른 경우
			if (type != EXIT && golemID != nGolemID) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;
		}
	}

	return maxR - 2;
}

int simulate(GOLEM golem)
{
	GOLEM g = golem;

	while (1)
	{
		if (checkSouth(g) == true) g.r = g.r + 1;
		else if (checkWest(g) == true) // 서쪽 + 남쪽
		{
			g.r = g.r + 1;
			g.c = g.c - 1;
			g.dir = (g.dir - 1 + 4) % 4;
		}
		else if (checkEast(g) == true) // 동쪽 + 남쪽
		{
			g.r = g.r + 1;
			g.c = g.c + 1;
			g.dir = (g.dir + 1) % 4;
		}
		else
			break;
	}

	if (g.r <= 3)
	{
		for (int r = 0; r < MAX; r++)
			for (int c = 0; c < MAX; c++)
				MAP[r][c] = 0;

		return 0;
	}

	setGolem(g);

	return BFS(g);
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		int sum = 0;
		for (int k = 1; k <= K; k++)
		{
			GOLEM g = { 0 };

			g.r = 1;
			g.c = start_c[k];
			g.dir = exit_d[k];
			g.id = k * GOLEM_ID;

			int row = simulate(g);

			// printMAP();

			sum += row;
		}

		printf("%d\n", sum);
	}

	return 0;
}