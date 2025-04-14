#include <stdio.h>

#define MAX_L (40 + 5)
#define MAX_N (30 + 5)

#define EMPTY (0)
#define TRAP (-1)
#define WALL (-2)

int T;

int L, N, Q;

int MAP[MAX_L][MAX_L]; // 함정과 벽만 기록
int tmpMAP[MAX_L][MAX_L];

struct COMMAND
{
	int index;
	int direction;
};

COMMAND command[100 + 10];

struct RCI
{
	int r;
	int c;
	int index;
};

RCI queue[MAX_L * MAX_L];

struct KNIGHT
{
	int r;
	int c;
	int h;
	int w;
	int k; // 기사의 체력
	int init_k; // 기사의 원래 체력
};

KNIGHT knight[MAX_N];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &L, &N, &Q);

	for (int r = 0; r <= L + 1; r++)
		for (int c = 0; c <= L + 1; c++)
			MAP[r][c] = WALL;

	for (int r = 1; r <= L; r++)
	{
		for (int c = 1; c <= L; c++)
		{
			scanf("%d", &MAP[r][c]);

			if (MAP[r][c] == 1) MAP[r][c] = TRAP;
			else if (MAP[r][c] == 2) MAP[r][c] = WALL;
		}
	}

	for (int n = 1; n <= N; n++)
	{
		scanf("%d %d %d %d %d", &knight[n].r, &knight[n].c, &knight[n].h, &knight[n].w, &knight[n].k);

		// 최초 체력 저장
		knight[n].init_k = knight[n].k;
	}

	for (int q = 0; q < Q; q++)
		scanf("%d %d", &command[q].index, &command[q].direction);
}

void printMap(int map[MAX_L][MAX_L]) // for debug
{
	for (int r = 1; r <= L; r++)
	{
		for (int c = 1; c <= L; c++)
			printf("%2d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void printStatus() // for debug
{
	for (int n = 1; n <= N; n++)
	{
		KNIGHT tmp = knight[n];
		printf("%d] (%d, %d) %d, %d, : %d\n", n, tmp.r, tmp.c, tmp.h, tmp.w, tmp.k);
	}
	putchar('\n');
}

void setKnight()
{
	for (int r = 1; r <= L; r++)
		for (int c = 1; c <= L; c++)
			tmpMAP[r][c] = 0;

	for (int n = 1; n <= N; n++)
	{
		if (knight[n].k <= 0) continue;

		int kr, kc, kh, kw;

		kr = knight[n].r;
		kc = knight[n].c;
		kh = knight[n].h;
		kw = knight[n].w;

		for (int r = kr; r < (kr + kh); r++)
			for (int c = kc; c < (kc + kw); c++)
				tmpMAP[r][c] = n;
	}
}

void BFS(int index, int direction)
{
	if (knight[index].k <= 0) return;

	int rp, wp;
	bool visit[MAX_L][MAX_L] = { 0 };
	int kr, kc, kh, kw;

	kr = knight[index].r;
	kc = knight[index].c;
	kh = knight[index].h;
	kw = knight[index].w;

	rp = wp = 0;

	for (int r = kr; r < (kr + kh); r++)
	{
		for (int c = kc; c < (kc + kw); c++)
		{
			queue[wp].r = r;
			queue[wp].c = c;
			queue[wp++].index = index;

			visit[r][c] = true;
		}
	}

	while (rp < wp)
	{
		RCI out = queue[rp++];

		int nr, nc;

		nr = out.r + dr[direction];
		nc = out.c + dc[direction];

		if (MAP[nr][nc] == WALL) return;

		if (visit[nr][nc] == true || tmpMAP[nr][nc] == EMPTY) continue;

		int another = tmpMAP[nr][nc];
		int kr, kc, kh, kw;

		kr = knight[another].r;
		kc = knight[another].c;
		kh = knight[another].h;
		kw = knight[another].w;

		for (int r = kr; r < (kr + kh); r++)
		{
			for (int c = kc; c < (kc + kw); c++)
			{
				queue[wp].r = r;
				queue[wp].c = c;
				queue[wp++].index = another;

				visit[r][c] = true;
			}
		}
	}

	bool check[MAX_N] = { 0 };
	for (int i = 0; i < wp; i++)
	{
		int knightIndex = queue[i].index;

		check[knightIndex] = true;
	}

	for (int n = 1; n <= N; n++)
	{
		if (check[n] == false) continue;

		knight[n].r = knight[n].r + dr[direction];
		knight[n].c = knight[n].c + dc[direction];

		if (n == index) continue;

		int kr, kc, kh, kw;

		kr = knight[n].r;
		kc = knight[n].c;
		kh = knight[n].h;
		kw = knight[n].w;

		for (int r = kr; r < (kr + kh); r++)
			for (int c = kc; c < (kc + kw); c++)
				if (MAP[r][c] == TRAP) knight[n].k--;
	}
}

void simulate()
{
	for (int q = 0; q < Q; q++)
	{
		setKnight();
		BFS(command[q].index, command[q].direction);
	}
}

int getAnswer()
{
	int sum = 0;
	for (int n = 1; n <= N; n++)
		if (knight[n].k > 0) sum += (knight[n].init_k - knight[n].k);

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