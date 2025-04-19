#include <stdio.h>

#define MAX (15 + 5)
#define MAX_Q (50 + 5)

int T;
int N, Q;
int MAP[MAX][MAX]; // 배양 용기

struct QUERY
{
	int r1;
	int c1;
	int r2;
	int c2;
};

QUERY query[MAX_Q];

struct MICRO
{
	int id;
	int minR;
	int minC;
	int maxR;
	int maxC;
	int size;
};

MICRO micro[MAX_Q];
int mcnt;

bool dead[MAX_Q]; // id로 따로 관리

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];
bool visit[MAX][MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d", &N, &Q);

	// 미생물 번호는 1번부터
	for (int q = 1; q <= Q; q++)
		scanf("%d %d %d %d", &query[q].r1, &query[q].c1, &query[q].r2, &query[q].c2);
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 0; r <= N; r++)
	{
		for (int c = 0; c <= N; c++)
			printf("%d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void printMicro(MICRO m)
{
	printf("id %d] (%d, %d) ~ (%d, %d) / size %d [dead=%d]\n",
		m.id, m.minR, m.minC, m.maxR, m.maxC, m.size, dead[m.id]);
}

void printMicroAll()
{
	for (int i = 0; i < mcnt; i++) printMicro(micro[i]);
}

void insert(int id, int r1, int c1, int r2, int c2)
{
	for (int r = r1; r < r2; r++)
		for (int c = c1; c < c2; c++)
			MAP[r][c] = id;
}

MICRO BFS(int r, int c)
{
	int rp, wp;
	int minR, minC, maxR, maxC;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	minR = maxR = r;
	minC = maxC = c;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (MAP[out.r][out.c] != MAP[nr][nc] || visit[nr][nc] == true) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;

			if (nr < minR) minR = nr;
			if (nc < minC) minC = nc;
			if (nr > maxR) maxR = nr;
			if (nc > maxC) maxC = nc;
		}
	}

	MICRO ret = { 0 };

	ret.id = MAP[r][c];
	ret.minR = minR;
	ret.minC = minC;
	ret.maxR = maxR;
	ret.maxC = maxC;
	ret.size = wp;

	return ret;
}

void findLiveMicro()
{
	mcnt = 0;

	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			visit[r][c] = false;

	bool check[MAX_Q] = { false };
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			int id = MAP[r][c];

			if (id == 0 || dead[id] == true || visit[r][c] == true) continue;

			MICRO m = BFS(r, c);

			if (check[id] == true)
			{
				dead[id] = true;
				continue;
			}

			check[id] = true;
			micro[mcnt++] = m;
		}
	}

	int tcnt = mcnt;

	mcnt = 0;
	for (int i = 0; i < tcnt; i++)
	{
		if (dead[micro[i].id] == true) continue;

		micro[mcnt++] = micro[i];
	}
}

// a가 우선순위가 더 높으면 true
bool isPriority(MICRO a, MICRO b)
{
	if (a.size != b.size) return a.size > b.size;

	return a.id < b.id;
}

void sort()
{
	for (int i = 0; i < mcnt - 1; i++)
	{
		for (int k = i + 1; k < mcnt; k++)
		{
			if (isPriority(micro[i], micro[k]) == false)
			{
				MICRO tmp = micro[i];
				micro[i] = micro[k];
				micro[k] = tmp;
			}
		}
	}
}

bool checkMove(int newMAP[MAX][MAX], MICRO m, int fr, int fc)
{
	int sr = m.minR;
	int sc = m.minC;
	int er = m.maxR;
	int ec = m.maxC;

	for (int r = sr; r <= er; r++)
	{
		for (int c = sc; c <= ec; c++)
		{
			// 미생물 사각형 범위에 다른 미생물 or 비어있는 경우
			if (MAP[r][c] != m.id || MAP[r][c] == 0) continue;

			int newR = fr - sr + r;
			int newC = fc - sc + c;

			// 격자 밖을 넘어가는 경우
			if (newR >= N || newC >= N) return false;

			// 새 용기에 이미 다른 미생물이 있는 경우
			if (newMAP[newR][newC] != 0) return false;
		}
	}

	return true;
}

void move(int newMAP[MAX][MAX], MICRO m, int fr, int fc)
{
	int sr = m.minR;
	int sc = m.minC;
	int er = m.maxR;
	int ec = m.maxC;

	for (int r = sr; r <= er; r++)
	{
		for (int c = sc; c <= ec; c++)
		{
			// 미생물 사각형 범위에 다른 미생물 or 비어있는 경우
			if (MAP[r][c] != m.id || MAP[r][c] == 0) continue;

			int newR = fr - sr + r;
			int newC = fc - sc + c;

			newMAP[newR][newC] = m.id;
		}
	}
}

void moveMicro(int newMAP[MAX][MAX], MICRO m)
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (checkMove(newMAP, m, r, c) == true)
			{
				move(newMAP, m, r, c);
				return;
			}
		}
	}
}

void moveAll()
{
	int newMAP[MAX][MAX] = { 0 }; // 새 배양 용기

	for (int i = 0; i < mcnt; i++) moveMicro(newMAP, micro[i]);

	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			MAP[r][c] = newMAP[r][c];
}

int getSize(int id)
{
	for (int i = 0; i < mcnt; i++)
		if (micro[i].id == id) return micro[i].size;

	return -1; // for debug
}

int getScore(int maxID)
{
	bool company[MAX_Q][MAX_Q] = { false };
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (MAP[r][c] == 0) continue;

			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				int id1 = MAP[r][c];
				int id2 = MAP[nr][nc];

				if (id1 == id2 || id2 == 0) continue;

				company[id1][id2] = true;
				company[id2][id1] = true;
			}
		}
	}

	int score = 0;
	for (int i = 1; i <= maxID - 1; i++)
	{
		for (int k = i + 1; k <= maxID; k++)
		{
			if (company[i][k] == false) continue;

			int size1 = getSize(i);
			int size2 = getSize(k);

			score += (size1 * size2);
		}
	}

	return score;
}

void simulate()
{
	for (int id = 1; id <= Q; id++)
	{
		int r1, c1, r2, c2;

		r1 = query[id].r1;
		c1 = query[id].c1;
		r2 = query[id].r2;
		c2 = query[id].c2;

		// 미생물 투입
		insert(id, r1, c1, r2, c2);

		// 배양 용기 이동
		findLiveMicro();
		sort();
		moveAll();

		// printMap(MAP);

		// 실험 결과 기록
		printf("%d\n", getScore(id));
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