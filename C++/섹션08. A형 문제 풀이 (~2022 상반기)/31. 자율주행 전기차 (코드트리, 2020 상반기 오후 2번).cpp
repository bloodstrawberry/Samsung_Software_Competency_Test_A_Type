#include <stdio.h>

#define MAX (20 + 5)
#define INF (0x7fff0000)

#define ROAD (0)
#define WALL (1)

int T;

int N, M, C;
int MAP[MAX][MAX];
int tmpMAP[MAX][MAX];
int visit[MAX][MAX];

struct RC
{
	int r;
	int c;
};

RC car;
RC queue[MAX * MAX];

struct PEOPLE
{
	int sr;
	int sc;
	int er;
	int ec;
	bool check; // 승객 도착 유무
};

PEOPLE people[MAX * MAX];

struct INFO
{
	int peopleNumber;
	int distance;
};

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &C);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = -1;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &MAP[r][c]);
			if (MAP[r][c] == WALL) MAP[r][c] = -1;
		}
	}

	scanf("%d %d", &car.r, &car.c);

	for (int m = 1; m <= M; m++)
	{
		int sr, sc, er, ec;

		scanf("%d %d %d %d", &sr, &sc, &er, &ec);

		people[m].sr = sr;
		people[m].sc = sc;
		people[m].er = er;
		people[m].ec = ec;
		people[m].check = false;
	}
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", map[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

INFO findPeople()
{
	int rp, wp;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			visit[r][c] = 0;

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			tmpMAP[r][c] = MAP[r][c];

	for (int i = 1; i <= M; i++)
	{
		if (people[i].check == true) continue;

		int pr, pc;

		pr = people[i].sr;
		pc = people[i].sc;

		tmpMAP[pr][pc] = i;

		// A 승객의 도착지(= 현재 전기차의 좌표)와 B 승객의 출발지가 같은 경우
		if (pr == car.r && pc == car.c)
			return { i, 0 };
	}

	rp = wp = 0;

	queue[wp].r = car.r;
	queue[wp++].c = car.c;

	visit[car.r][car.c] = 1;

	int minDistance, minR, minC, peopleNumber;

	minDistance = minR = minC = INF;
	peopleNumber = -1;
	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int k = 0; k < 4; k++)
		{
			int nr, nc;

			nr = out.r + dr[k];
			nc = out.c + dc[k];

			if (tmpMAP[nr][nc] == -1 || visit[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = visit[out.r][out.c] + 1;

			// 승객의 번호
			if (tmpMAP[nr][nc] != 0)
			{
				if ((visit[nr][nc] < minDistance)
					|| (visit[nr][nc] == minDistance && nr < minR)
					|| (visit[nr][nc] == minDistance && nr == minR && nc < minC))
				{
					peopleNumber = tmpMAP[nr][nc];
					minDistance = visit[nr][nc];
					minR = nr;
					minC = nc;
				}
			}
		}
	}

	return { peopleNumber, minDistance - 1 };
}

int goToDestination(int er, int ec)
{
	int rp, wp;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			visit[r][c] = 0;

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			tmpMAP[r][c] = MAP[r][c];

	rp = wp = 0;

	queue[wp].r = car.r;
	queue[wp++].c = car.c;

	visit[car.r][car.c] = 1;

	while (rp < wp)
	{
		RC out = queue[rp++];

		if (out.r == er && out.c == ec)
			return visit[out.r][out.c] - 1;

		for (int k = 0; k < 4; k++)
		{
			int nr, nc;

			nr = out.r + dr[k];
			nc = out.c + dc[k];

			if (tmpMAP[nr][nc] == -1 || visit[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = visit[out.r][out.c] + 1;
		}
	}

	return -1;
}

int simulate()
{
	for (int i = 0; i < M; i++)
	{
		// 남은 승객 중 가장 가까이 있는 승객의 번호와 거리 획득
		INFO info = findPeople();

		if (C <= info.distance) return -1;

		C -= info.distance;

		int number = info.peopleNumber;

		if (number == -1) return -1;

		// 자동차를 출발지로 이동
		car.r = people[number].sr;
		car.c = people[number].sc;

		// 전기차와 승객의 목적지까지의 거리
		int capacity = goToDestination(people[number].er, people[number].ec);

		if (capacity == -1 || C < capacity) return -1;

		C += capacity;

		// 자동차를 목적지로 이동
		car.r = people[number].er;
		car.c = people[number].ec;

		people[number].check = true;
	}

	return C;
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