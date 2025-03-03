#include <stdio.h>

#define MAX (29 + 5)

int T;

int N;
int halfN;
int MAP[MAX][MAX];
int tmpMAP[MAX][MAX];
int visit[MAX][MAX];

struct GROUP
{
	int value;
	int count;
	int groupNumber;
};

GROUP group[MAX * MAX];
int gcnt;

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int harmony[MAX * MAX][MAX * MAX];

void input()
{
	scanf("%d", &N);

	halfN = (N + 1) / 2;

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = 0;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &MAP[r][c]);
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

void copyMap(int copy[MAX][MAX], int original[MAX][MAX])
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			copy[r][c] = original[r][c];
}

GROUP BFS(int r, int c, int mark)
{
	GROUP ret = { 0 };
	int value;
	int rp, wp;

	rp = wp = 0;

	value = MAP[r][c];

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = mark;

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

			if (MAP[nr][nc] != value || visit[nr][nc] != 0) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = mark;
		}
	}

	ret.value = value;
	ret.count = wp;
	ret.groupNumber = mark;

	return ret;
}

void rotateCenter()
{
	copyMap(tmpMAP, MAP);

	for (int r = 1; r <= N; r++)
		MAP[r][halfN] = tmpMAP[halfN][N + 1 - r];

	for (int c = 1; c <= N; c++)
		MAP[halfN][c] = tmpMAP[c][halfN];
}

void rotate(int sr, int sc)
{
	int size = N / 2;

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			tmpMAP[r][c] = MAP[sr + r][sc + c];

	for (int r = 0; r < size; r++)
		for (int c = 0; c < size; c++)
			MAP[sr + r][sc + c] = tmpMAP[size - 1 - c][r];
}

void makeHarmony()
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

				if (visit[r][c] == visit[nr][nc]) continue;

				harmony[visit[r][c]][visit[nr][nc]]++; // harmony[A][B]++;
				harmony[visit[nr][nc]][visit[r][c]]++; // harmony[B][A]++;
			}
		}
	}

	for (int r = 1; r <= N * N; r++)
		for (int c = 1; c <= N * N; c++)
			harmony[r][c] /= 2;

	return;
	// for debug
	for (int r = 1; r <= N * N; r++)
	{
		for (int c = 1; c <= N * N; c++)
		{
			printf("%d %d %d\n", r, c, harmony[r][c]);
		}
	}
}

int getScore()
{
	int score = 0;
	for (int i = 0; i < gcnt - 1; i++)
	{
		for (int k = i + 1; k < gcnt; k++)
		{
			GROUP a = group[i];
			GROUP b = group[k];

			score
				+= ((a.count + b.count) * a.value * b.value * harmony[a.groupNumber][b.groupNumber]);
		}
	}

	return score;
}


int simulate()
{
	int score = 0;
	for (int round = 0; round < 4; round++)
	{
		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				visit[r][c] = 0;

		gcnt = 0;

		int groupNumber = 1;
		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= N; c++)
			{
				if (visit[r][c] != 0) continue;

				GROUP ret = BFS(r, c, groupNumber);
				group[gcnt++] = ret;
				groupNumber++;
			}
		}

		// for debug
		//printf("round : %d\n", round);
		//for (int i = 0; i < gcnt; i++)
		//{
		//	GROUP g = group[i];

		//	printf("%d %d %d\n", g.value, g.count, g.groupNumber);
		//}

		for (int r = 1; r <= N * N; r++)
			for (int c = 1; c <= N * N; c++)
				harmony[r][c] = 0;

		makeHarmony();

		score += getScore();

		rotateCenter();

		rotate(1, 1);
		rotate(halfN + 1, 1);
		rotate(1, halfN + 1);
		rotate(halfN + 1, halfN + 1);
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