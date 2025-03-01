#include <stdio.h>

#define MAX (10 + 5)
#define INF (0x7fff0000)

#define BROKEN (0)

int T;
int N, M, K;

int MAP[MAX][MAX];
int tmpMAP[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

int attackTime[MAX][MAX];

// →, ↓, ←, ↑ 
int dr4[] = { 0, 1, 0, -1 };
int dc4[] = { 1, 0, -1, 0 };

// ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 
int dr8[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dc8[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			scanf("%d", &MAP[r][c]);

	// 시점 0에서 모두 공격
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			attackTime[r][c] = 0;
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}

	putchar('\n');
}

// a가 더 약하면 true
bool isWeak(RC a, RC b)
{
	if (MAP[a.r][a.c] != MAP[b.r][b.c])
		return MAP[a.r][a.c] < MAP[b.r][b.c];

	int timeA = attackTime[a.r][a.c];
	int timeB = attackTime[b.r][b.c];
	if (timeA != timeB) return timeA > timeB;

	int sumA = a.r + a.c;
	int sumB = b.r + b.c;
	if (sumA != sumB) return sumA > sumB;

	return a.c > b.c;
}

RC getWeakestTower()
{
	RC ret = { 0 };

	MAP[0][0] = INF; // 최악의 값
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (MAP[r][c] == BROKEN) continue;

			RC tmp = { r, c };
			if (isWeak(tmp, ret) == true)
				ret = tmp;
		}
	}

	return ret;
}

RC getStrongestTower(RC attacker)
{
	RC ret = { 0 };

	MAP[0][0] = 0; // 최악의 값
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (attacker.r == r && attacker.c == c) continue;
			if (MAP[r][c] == BROKEN) continue;

			RC tmp = { r, c };
			if (isWeak(tmp, ret) == false)
				ret = tmp;
		}
	}

	return ret;
}

bool BFS(RC start, RC end)
{
	int rp, wp;
	int visit[MAX][MAX] = { 0 };
	RC before[MAX][MAX] = { 0 };

	rp = wp = 0;

	int sr = start.r;
	int sc = start.c;
	int er = end.r;
	int ec = end.c;

	queue[wp].r = sr;
	queue[wp++].c = sc;

	visit[sr][sc] = 1;

	before[sr][sc].r = -1;
	before[sr][sc].c = -1;

	while (rp < wp)
	{
		RC out = queue[rp++];

		if (out.r == end.r && out.c == end.c)
		{
			int power = MAP[sr][sc];

			int tr = out.r;
			int tc = out.c;

			MAP[tr][tc] -= power;
			
			while (1)
			{
				int br, bc;

				br = before[tr][tc].r;
				bc = before[tr][tc].c;

				if (br == sr && bc == sc) break;

				MAP[br][bc] -= (power / 2);

				tr = br;
				tc = bc;
			}

			return true;
		}

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = (((out.r + dr4[i] + N) - 1) % N) + 1;
			nc = (((out.c + dc4[i] + M) - 1) % M) + 1;

			if (MAP[nr][nc] == BROKEN || visit[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = visit[out.r][out.c] + 1;

			before[nr][nc] = out;
		}
	}

	return false;
}

void attack(RC attacker, RC target, int time)
{
	attackTime[attacker.r][attacker.c] = time;

	// laser
	if (BFS(attacker, target) == true) return;

	// 포탄
	int sr = attacker.r;
	int sc = attacker.c;
	int er = target.r;
	int ec = target.c;

	int power = MAP[sr][sc];

	MAP[er][ec] -= power;

	for (int i = 0; i < 8; i++)
	{
		int nr, nc;

		nr = (((er + dr8[i] + N) - 1) % N) + 1;
		nc = (((ec + dc8[i] + M) - 1) % M) + 1;

		if (MAP[nr][nc] == BROKEN) continue;
		if (nr == sr && nc == sc) continue; // 공격자는 영향 x

		MAP[nr][nc] -= (power / 2);
	}
}

void setBrokenTower()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			if (MAP[r][c] < 0) MAP[r][c] = BROKEN;
}

void maintainTower()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (MAP[r][c] == BROKEN) continue;
			if (tmpMAP[r][c] != MAP[r][c]) continue;

			MAP[r][c]++;
		}
	}
}

void simulate()
{
	for (int k = 1; k <= K; k++)
	{
		// 0. 현재 상태 저장
		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= M; c++)
				tmpMAP[r][c] = MAP[r][c];

		// 1. 공격자 선정
		RC attacker = getWeakestTower();

		// 2. 공격자의 공격
		// 2-1. target 탐색
		RC target = getStrongestTower(attacker);

		// 2-2 target이 없는 경우
		if (target.r == 0 && target.c == 0) break;

		// 2-3 target 공격
		MAP[attacker.r][attacker.c] += (N + M);
		attack(attacker, target, k);

		// 3. 포탑 부서짐
		setBrokenTower();

		// 4. 포탑 정비
		maintainTower();
	}
}

int getAnswer()
{
	int max = 0;
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			if (max < MAP[r][c]) max = MAP[r][c];

	return max;
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