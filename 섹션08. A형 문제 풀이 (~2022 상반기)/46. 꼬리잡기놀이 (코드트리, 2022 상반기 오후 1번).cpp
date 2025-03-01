#include <stdio.h>

#define MAX_N (20 + 5)
#define MAX_M (5 + 2)

#define HEAD (1)
#define BODY (2)
#define TAIL (3)
#define ROOP (4)

// 공을 던지는 방향
#define RIGHT (0)
#define UP (1)
#define LEFT (2)
#define DOWN (3)

int T;

int N, M, K;

struct MAP_INFO
{
	int value; // 입력 값
	int order; // k번째 사람
	int loop; // loop의 번호
};

MAP_INFO MAP[MAX_N][MAX_N];
bool visit[MAX_N][MAX_N];

struct RCON
{
	int r;
	int c;
	int value; 
	int order; // k번째 사람
};

RCON queue[MAX_N * MAX_N];

RCON position[MAX_M][MAX_N * MAX_N]; // 루프 : 1, 2, 2, 3, 4, 4, 4, 4, 4, ... 의 좌표가 생성
int posIndex[MAX_M]; // 1 ~ 4의 수
int peopleIndex[MAX_M]; // 1 ~ 3의 수

bool checkDirection[MAX_M]; // 방향이 바뀌었는지 여부

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &MAP[r][c].value);
			MAP[r][c].loop = MAP[r][c].order = -1;
		}
	}

	for (int i = 0; i < M; i++)
		posIndex[i] = peopleIndex[i] = checkDirection[i] = 0;
}

void printMap(int map[MAX_N][MAX_N]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void printMapValue(MAP_INFO map[MAX_N][MAX_N]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", map[r][c].value);
		putchar('\n');
	}
	putchar('\n');
}

void printPosition(int loop) // for debug
{
	int index = posIndex[loop];

	for (int i = 0; i < index; i++)
	{
		RCON p = position[loop][i];

		printf("%d] (%d, %d) %d, %d\n", i, p.r, p.c, p.order, p.value);
	}
	putchar('\n');
}

void BFS(int r, int c, int loop)
{
	int rp, wp, order;

	order = 1;

	MAP[r][c].loop = loop;
	MAP[r][c].order = order;

	position[loop][posIndex[loop]].r = r;
	position[loop][posIndex[loop]].c = c;
	position[loop][posIndex[loop]].order = order++;
	position[loop][posIndex[loop]++].value = HEAD;

	rp = wp = 0;

	visit[r][c] = true;

	// 1 -> 2 먼저 찾기
	for (int i = 0; i < 4; i++)
	{
		int nr, nc;

		nr = r + dr[i];
		nc = c + dc[i];

		if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

		if (MAP[nr][nc].value == BODY)
		{
			queue[wp].r = nr;
			queue[wp++].c = nc;
			
			visit[nr][nc] = true;

			MAP[nr][nc].loop = loop;
			MAP[nr][nc].order = order;

			position[loop][posIndex[loop]].r = nr;
			position[loop][posIndex[loop]].c = nc;
			position[loop][posIndex[loop]].order = order++;
			position[loop][posIndex[loop]++].value = BODY;

			break;
		}
	}

	// 1, 2 count
	peopleIndex[loop] = 2;

	while (rp < wp)
	{
		RCON out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;
			if (MAP[nr][nc].value == 0 || visit[nr][nc] == true) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;

			MAP[nr][nc].loop = loop;
			MAP[nr][nc].order = order;

			position[loop][posIndex[loop]].r = nr;
			position[loop][posIndex[loop]].c = nc;
			position[loop][posIndex[loop]].order = order++;
			position[loop][posIndex[loop]++].value = MAP[nr][nc].value;

			if (MAP[nr][nc].value <= TAIL) peopleIndex[loop]++;
		}
	}
}

void move(int loop)
{
	RCON tmp;
	int index = posIndex[loop];
	bool check = checkDirection[loop];

	if (check == false) // 1 -> 4 -> .. -> 2 -> 1로 이동
	{
		tmp = position[loop][index - 1];

		for (int i = index - 2; i >= 0; i--)
		{
			int r, c;

			r = position[loop][i].r;
			c = position[loop][i].c;

			position[loop][i + 1].r = r;
			position[loop][i + 1].c = c;
		}

		position[loop][0].r = tmp.r;
		position[loop][0].c = tmp.c;
	}
	else // 1 -> 2 -> 2 -> ... -> 3 -> 4 -> 1로 이동
	{
		tmp = position[loop][0];

		for (int i = 1; i < index; i++)
		{
			int r, c;

			r = position[loop][i].r;
			c = position[loop][i].c;

			position[loop][i - 1].r = r;
			position[loop][i - 1].c = c;
		}

		position[loop][index - 1].r = tmp.r;
		position[loop][index - 1].c = tmp.c;
	}

	for (int i = 0; i < index; i++)
	{
		int r = position[loop][i].r;
		int c = position[loop][i].c;
		int order = position[loop][i].order;
		int value = position[loop][i].value;

		MAP[r][c].order = order;
		MAP[r][c].value = value;
	}
}

int getScore(int round)
{
	bool hit[5] = { false, true, true, true, false };

	// → 1 ~ N ==> 0번 방향
	// ↑ N + 1 ~ 2 * N ==> 1번 방향
	// ← 2 * N + 1 ~ 3 * N ==> 2번 방향
	// ↓ 3 * N + 1 ~ 4 * N ==> 3번 방향

	// if N == 7 
	// → 1 ~ 7  ==> 0번 방향
	// ↑ 8 ~ 14 ==> 1번 방향
	// ← 15 ~ 21 ==> 2번 방향
	// ↓ 22 ~ 28 ==> 3번 방향

	int ballDir = (((round - 1) % (4 * N))) / N;
	int line = ((round - 1) % N) + 1;
	
	if (ballDir == RIGHT) // →
	{
		for (int c = 1; c <= N; c++)
		{
			if (hit[MAP[line][c].value] == true)
			{
				int order = MAP[line][c].order;
				int loop = MAP[line][c].loop;

				if (checkDirection[loop] == true)
					order = peopleIndex[loop] - order + 1;

				checkDirection[loop] = !checkDirection[loop];

				return order * order;
			}
		}
	}
	else if (ballDir == UP) // ↑
	{
		for (int r = N; r >= 1; r--)
		{
			if (hit[MAP[r][line].value] == true)
			{
				int order = MAP[r][line].order;
				int loop = MAP[r][line].loop;

				if (checkDirection[loop] == true)
					order = peopleIndex[loop] - order + 1;

				checkDirection[loop] = !checkDirection[loop];

				return order * order;
			}
		}
	}
	else if (ballDir == LEFT) // ←
	{
		for (int c = N; c >= 1; c--)
		{
			if (hit[MAP[N + 1 - line][c].value] == true)
			{
				int order = MAP[N + 1 - line][c].order;
				int loop = MAP[N + 1 - line][c].loop;

				if (checkDirection[loop] == true)
					order = peopleIndex[loop] - order + 1;

				checkDirection[loop] = !checkDirection[loop];

				return order * order;
			}
		}
	}
	else if (ballDir == DOWN) // ↓
	{
		for (int r = 1; r <= N; r++)
		{
			if (hit[MAP[r][N + 1 - line].value] == true)
			{
				int order = MAP[r][N + 1 - line].order;
				int loop = MAP[r][N + 1 - line].loop;

				if (checkDirection[loop] == true)
					order = peopleIndex[loop] - order + 1;

				checkDirection[loop] = !checkDirection[loop];

				return order * order;
			}
		}
	}

	return 0;
}

int simulate()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			visit[r][c] = false;

	int loop = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c].value != HEAD || visit[r][c] == true) continue;

			BFS(r, c, loop);

			//printPosition(loop);

			loop++;
		}
	}

	int score = 0;
	for (int k = 1; k <= K; k++)
	{
		for (int m = 0; m < M; m++) move(m);

		score += getScore(k);
	}

	return score;
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