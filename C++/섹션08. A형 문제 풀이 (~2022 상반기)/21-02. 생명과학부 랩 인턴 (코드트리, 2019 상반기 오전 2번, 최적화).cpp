#include <stdio.h>

#define MAX (100 + 20)

int T;
int N, M, K;

struct MOLD
{
	int distance; // 움직이는 거리 s
	int dir; // 이동 방향 d
	int size; // 곰팡이의 크기 b
};

MOLD mold[MAX][MAX];
MOLD tmpMold[MAX][MAX];

// -, 위, 아래, 오른쪽, 왼쪽
int dr[] = { 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, 1, -1 };

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			mold[r][c].distance = mold[r][c].dir = mold[r][c].size = 0;

	for (int k = 0; k < K; k++)
	{
		int r, c, s, d, b;

		scanf("%d %d %d %d %d", &r, &c, &s, &d, &b);

		mold[r][c].distance = s;
		mold[r][c].dir = d;
		mold[r][c].size = b;
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
			printf("%d ", mold[r][c].size); // or dir, distance
		putchar('\n');
	}
	putchar('\n');
}

// 2. 곰팡이 채취
int catchMold(int sc)
{
	// 2-1. 해당 열의 위치에서 아래로 내려가며
	for (int r = 1; r <= N; r++)
	{
		// 2-2. 가장 먼저 발견한 곰팡이를 채취
		if (mold[r][sc].size != 0)
		{
			int ret = mold[r][sc].size;

			// 2-3. 곰팡이를 채취하고 나면 해당 칸은 빈칸
			mold[r][sc].size = 0;

			return ret;
		}
	}

	return 0;
}

void moveMold()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			tmpMold[r][c].distance = tmpMold[r][c].dir = tmpMold[r][c].size = 0;

	int changeDir[5] = { 0, 2, 1, 4, 3 };

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= M; c++)
		{
			if (mold[r][c].size == 0) continue;

			MOLD md = mold[r][c];
			int sr, sc, dir;

			sr = r;
			sc = c;
			dir = md.dir;

			int move = md.distance;

			// dir = 1, 2 (위, 아래)
			if(dir <= 2) move = md.distance % ((N - 1) * 2);
			else  move = md.distance % ((M - 1) * 2);

			// 4-1. 곰팡이 이동
			for (int m = 0; m < move; m++)
			{
				int nr, nc;

				nr = sr + dr[dir];
				nc = sc + dc[dir];

				// 4-2. 방향 변경
				if (nr < 1 || nc < 1 || nr > N || nc > M)
				{
					dir = changeDir[dir];

					nr = sr + dr[dir];
					nc = sc + dc[dir];
				}

				sr = nr;
				sc = nc;
			}

			// 5. 이동 후, 한 칸에 곰팡이가 두마리 이상일 경우, 큰 곰팡이만 남기기			
			// 이동할 위치 (sr, sc), 이동 전 위치의 곰팡이는 (r, c)
			if (tmpMold[sr][sc].size < mold[r][c].size)
			{
				tmpMold[sr][sc] = mold[r][c];
				tmpMold[sr][sc].dir = dir;
			}
		}
	}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= M; c++)
			mold[r][c] = tmpMold[r][c];	
}

int simulate()
{
	int sum = 0;
	// 1. 승용이는 첫번째 열부터 탐색을 시작
	for (int c = 1; c <= M; c++)
	{
		// 2. 곰팡이 채취
		sum += catchMold(c);

		// 3. 곰팡이 이동 시작
		moveMold();
	}

	return sum;
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