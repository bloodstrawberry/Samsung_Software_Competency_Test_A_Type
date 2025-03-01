#include <stdio.h>

#define MAX_N (50 + 5)
#define MAX_M (300 + 30)

#define WALL (1)

#define UP (0)
#define DOWN (1)
#define LEFT (2)
#define RIGHT (3)

#define STRAIGHT (1)

int T;

int N, M;
int MAP[MAX_N][MAX_N];
int visit[MAX_N][MAX_N];
int scope[MAX_N][MAX_N]; // 메두사의 시선 처리

struct RC
{
	int r;
	int c;
};

RC start, end, medusa;
RC queue[MAX_N * MAX_N];
RC before[MAX_N][MAX_N];
RC position[MAX_N * MAX_N]; // 메두사의 경로
int pcnt; // 메두사의 경로 길이

struct RCD
{
	int r;
	int c;
	bool dead;
};

RCD warrior[MAX_M];

struct ANSWER
{
	int distance; // 모든 전사가 이동한 거리의 합
	int stone; // 메두사로 인해 돌이 된 전사의 수
	int attack; // 메두사를 공격한 전사의 수
};

ANSWER answer;

// ↑, ↓, ←, → (상, 하, 좌, 우)
int dr[] = { -1, 1, 0, 0 };
int dc[] = { 0, 0, -1, 1 };

void input()
{
	int sr, sc, er, ec;

	scanf("%d %d %d %d %d %d", &N, &M, &sr, &sc, &er, &ec);

	start.r = sr + 1;
	start.c = sc + 1;
	end.r = er + 1;
	end.c = ec + 1;

	pcnt = 0;

	for (int m = 0; m < M; m++)
	{
		int r, c;

		scanf("%d %d", &r, &c);

		warrior[m].r = r + 1;
		warrior[m].c = c + 1;
		warrior[m].dead = false;
	}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap(int map[MAX_N][MAX_N]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void printStatus() // for debug
{
	int tmpMAP[MAX_N][MAX_N] = { 0 };

	tmpMAP[medusa.r][medusa.c] = -1;

	for (int m = 0; m < M; m++)
	{
		if (warrior[m].dead == true) continue;

		int r, c;

		r = warrior[m].r;
		c = warrior[m].c;

		tmpMAP[r][c] = m;
	}

	printMap(tmpMAP);
}

void BFS()
{
	int rp, wp;
	int sr, sc, er, ec;

	rp = wp = 0;

	sr = start.r;
	sc = start.c;
	er = end.r;
	ec = end.c;

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

			position[pcnt].r = er;
			position[pcnt++].c = ec;

			while (1)
			{
				int br, bc; // 이전 좌표

				br = before[tr][tc].r;
				bc = before[tr][tc].c;

				if (br == sr && bc == sc) break;

				position[pcnt].r = br;
				position[pcnt++].c = bc;

				tr = br;
				tc = bc;
			}

			for (int i = 0; i < (pcnt / 2); i++)
			{
				RC tmp = position[i];
				position[i] = position[pcnt - 1 - i];
				position[pcnt - 1 - i] = tmp;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			int nr = out.r + dr[i];
			int nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;
			if (visit[nr][nc] != 0 || MAP[nr][nc] == WALL) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = visit[out.r][out.c] + 1;

			before[nr][nc] = out;
		}
	}
}

void moveMedusa(int index)
{
	medusa = position[index];

	for (int m = 0; m < M; m++)
	{
		if (warrior[m].dead == true) continue;

		int wr, wc;

		wr = warrior[m].r;
		wc = warrior[m].c;

		if (wr == medusa.r && wc == medusa.c)
			warrior[m].dead = true;
	}
}

void straight(int r, int c, int dir, int value)
{
	int sr, sc;

	sr = r;
	sc = c;

	while (1)
	{
		int nr, nc;

		nr = sr + dr[dir];
		nc = sc + dc[dir];

		if (nr < 1 || nc < 1 || nr > N || nc > N) break;

		scope[nr][nc] = value;

		sr = nr;
		sc = nc;
	}
}

void diagonal(int r, int c, int dir, int nDir, int value)
{
	int step = 1;
	while (1)
	{
		int sr, sc;

		sr = r + (dr[dir] + dr[nDir]) * step;
		sc = c + (dc[dir] + dc[nDir]) * step;

		if (sr < 1 || sc < 1 || sr > N || sc > N) break;

		scope[sr][sc] = value;

		while (1)
		{
			int nr, nc;

			nr = sr + dr[dir];
			nc = sc + dc[dir];

			if (nr < 1 || nc < 1 || nr > N || nc > N) break;

			scope[nr][nc] = value;

			sr = nr;
			sc = nc;
		}

		step++;
	}
}

// ↑, ↓, ←, → (상, 하, 좌, 우 / 0, 1, 2, 3)
void leftLook(int r, int c, int dir, int value)
{
	int changeDir[4] = { 2, 3, 1, 0 };
	int leftDir = changeDir[dir];

	diagonal(r, c, dir, leftDir, value);
}

void rightLook(int r, int c, int dir, int value)
{
	int changeDir[4] = { 3, 2, 0, 1 };
	int rightDir = changeDir[dir];

	diagonal(r, c, dir, rightDir, value);
}

int countStoneWarrior(int dir)
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scope[r][c] = 0;

	int mr, mc;

	mr = medusa.r;
	mc = medusa.c;

	straight(mr, mc, dir, STRAIGHT);
	leftLook(mr, mc, dir, LEFT);
	rightLook(mr, mc, dir, RIGHT);

	for (int m = 0; m < M; m++)
	{
		if (warrior[m].dead == true) continue;

		int wr = warrior[m].r;
		int wc = warrior[m].c;

		if (scope[wr][wc] == STRAIGHT) straight(wr, wc, dir, 0);
		else if (scope[wr][wc] == LEFT)
		{
			straight(wr, wc, dir, 0);
			leftLook(wr, wc, dir, 0);
		}
		else if (scope[wr][wc] == RIGHT)
		{
			straight(wr, wc, dir, 0);
			rightLook(wr, wc, dir, 0);
		}
	}

	int count = 0;
	for (int m = 0; m < M; m++)
	{
		if (warrior[m].dead == true) continue;

		int wr, wc;

		wr = warrior[m].r;
		wc = warrior[m].c;

		if (scope[wr][wc] != 0) count++;
	}

	return count;
}

void lookAt()
{
	int maxCount, maxDir;

	maxCount = maxDir = 0;
	for (int i = 0; i < 4; i++)
	{
		int tmp = countStoneWarrior(i);
		if (maxCount < tmp)
		{
			maxCount = tmp;
			maxDir = i;
		}
	}

	countStoneWarrior(maxDir);

	answer.stone = maxCount;
}

int checkRow(RCD w)
{
	int mr = medusa.r;
	int wr = w.r;

	// mr > wr -> 메두사는 아래에
	// mr = wr -> 같은 행, 상하로 움직일 수 없음.
	// mr < wr -> 메두사는 위에
	return mr - wr;
}

int checkCol(RCD w)
{
	int mc = medusa.c;
	int wc = w.c;

	// mc > wc -> 메두사는 오른쪽에
	// mc = wc -> 같은 열, 좌우로 움직일 수 없음.
	// mc < wc -> 메두사는 왼쪽에
	return mc - wc;
}

bool checkScope(RCD w, int dir)
{
	int nr, nc;

	nr = w.r + dr[dir];
	nc = w.c + dc[dir];

	if (scope[nr][nc] != 0) return false;

	return true;
}

void moveWarrior(bool first)
{
	for (int m = 0; m < M; m++)
	{
		RCD w = warrior[m];

		if (w.dead == true) continue;
		if (scope[w.r][w.c] != 0) continue;

		int upDown = checkRow(w);
		int leftRight = checkCol(w);

		int direction = -1;

		// 메두사를 향해서 이동하므로 격자의 바깥으로 나가지 않는다.
		if (first == true)
		{
			if (upDown < 0 && checkScope(w, UP) == true) direction = UP;
			else if (upDown > 0 && checkScope(w, DOWN) == true) direction = DOWN;
			else if (leftRight < 0 && checkScope(w, LEFT) == true) direction = LEFT;
			else if (leftRight > 0 && checkScope(w, RIGHT) == true) direction = RIGHT;
		}
		else
		{
			if (leftRight < 0 && checkScope(w, LEFT) == true) direction = LEFT;
			else if (leftRight > 0 && checkScope(w, RIGHT) == true) direction = RIGHT;
			else if (upDown < 0 && checkScope(w, UP) == true) direction = UP;
			else if (upDown > 0 && checkScope(w, DOWN) == true) direction = DOWN;
		}

		if (direction == -1) continue;

		int nr, nc;

		nr = w.r + dr[direction];
		nc = w.c + dc[direction];

		warrior[m].r = nr;
		warrior[m].c = nc;

		answer.distance++;

		if (nr == medusa.r && nc == medusa.c)
		{
			answer.attack++;
			warrior[m].dead = true;
		}
	}
}

void simulate()
{
	if (pcnt == 0)
	{
		printf("-1\n");
		return;
	}

	for (int p = 0; p < pcnt - 1; p++)
	{
		answer.distance = answer.stone = answer.attack = 0;

		moveMedusa(p);

		lookAt();

		moveWarrior(true);
		moveWarrior(false);

		printf("%d %d %d\n", answer.distance, answer.stone, answer.attack);
	}

	printf("%d\n", 0);
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		BFS();

		simulate();
	}

	return 0;
}