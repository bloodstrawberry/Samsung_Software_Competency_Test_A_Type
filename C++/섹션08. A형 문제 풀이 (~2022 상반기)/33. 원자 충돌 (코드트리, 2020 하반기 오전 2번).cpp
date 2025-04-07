#include <stdio.h>

#define MAX (50 + 5)

int T;
int N, M, K;

struct ATOM
{
	int r;
	int c;
	int m; // 질량
	int s; // 속력
	int d; // 방향
};

ATOM atom[100000 + 5000];
int acnt;

// ↑, ↗, →, ↘, ↓, ↙, ←, ↖
int dr[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

struct INFO
{
	int m; // 질량
	int s; // 속력
	int d; // 방향
	int even; // 상하좌우
	int odd; // 대각선
	int count; // 원자의 개수
};

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	acnt = 0;
	for (int i = 0; i < M; i++)
	{
		scanf("%d %d %d %d %d", &atom[acnt].r, &atom[acnt].c, &atom[acnt].m, &atom[acnt].s, &atom[acnt].d);
		acnt++;
	}
}

void printAtom() // for debug
{
	for (int i = 0; i < acnt; i++)
		printf("%d %d %d %d %d", atom[i].r, atom[i].c, atom[i].m, atom[i].s, atom[i].d);		
	putchar('\n');
}

void simulate()
{
	for (int k = 0; k < K; k++)
	{
		INFO MAP[MAX][MAX] = { 0 };

		// 1. 원자는 자신의 속력만큼 이동
		for (int i = 0; i < acnt; i++)
		{
			int nr, nc;
			int d, s, m;

			d = atom[i].d;
			s = atom[i].s;
			m = atom[i].m;

			nr = atom[i].r + dr[d] * (s % N);
			nc = atom[i].c + dc[d] * (s % N);

			if (nr > N) nr -= N;
			if (nc > N) nc -= N;
			if (nr < 1) nr += N;
			if (nc < 1) nc += N;

			// 2. 합성
			MAP[nr][nc].m += m;
			MAP[nr][nc].s += s;
			MAP[nr][nc].d = d;  // 원자가 1개인 경우 유효

			if (d % 2 == 0) MAP[nr][nc].even++;
			else MAP[nr][nc].odd++;

			MAP[nr][nc].count++;
		}

		// MAP을 보고 atom 배열 생성
		acnt = 0;
		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= N; c++)
			{
				if (MAP[r][c].count == 0) continue;

				if (MAP[r][c].count == 1)
				{
					atom[acnt].r = r;
					atom[acnt].c = c;
					atom[acnt].m = MAP[r][c].m;
					atom[acnt].s = MAP[r][c].s;
					atom[acnt++].d = MAP[r][c].d;

					continue;
				}

				// 2.d 질량이 0인 원자는 소멸
				if ((MAP[r][c].m / 5) == 0) continue;

				// 2.b 합쳐진 원자는 4개의 원자로 분해
				int dir[4] = { 0 };
				if (MAP[r][c].even == MAP[r][c].count
					|| MAP[r][c].odd == MAP[r][c].count)
				{
					dir[0] = 0;
					dir[1] = 2;
					dir[2] = 4;
					dir[3] = 6;
				}
				else
				{
					dir[0] = 1;
					dir[1] = 3;
					dir[2] = 5;
					dir[3] = 7;
				}

				for (int i = 0; i < 4; i++)
				{
					atom[acnt].r = r;
					atom[acnt].c = c;
					atom[acnt].m = MAP[r][c].m / 5; // 2.c.2
					atom[acnt].s = MAP[r][c].s / MAP[r][c].count; // 2.c.3
					atom[acnt++].d = dir[i];
				}
			}
		}
	}
}

int getAnswer()
{
	int sum = 0;
	for (int i = 0; i < acnt; i++) 
		sum += atom[i].m;

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