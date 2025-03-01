#include <stdio.h>

#define MAX (20 + 5)
#define WALL (-1)

int T;

int N, M, K, C;
int MAP[MAX][MAX];
int herbicide[MAX][MAX]; // 제초제

struct INFO
{
	int r;
	int c;
	int count;
};

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

// ↖, ↗, ↘, ↙
int dr2[] = { -1, -1, 1, 1 };
int dc2[] = { -1, 1, 1, -1 };

void input()
{
	scanf("%d %d %d %d", &N, &M, &K, &C);

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

void spreadTree()
{
	// 1. 인접한 칸 만큼 나무가 성장
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] == 0 || MAP[r][c] == WALL) continue;

			int count = 0; // 주변 나무의 개수
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

				if (MAP[nr][nc] > 0) count++;
			}

			MAP[r][c] += count;
		}
	}

	// 2. 인접한 칸에 동시에 번식
	int tmpMAP[MAX][MAX] = { 0 };
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (MAP[r][c] == 0 || MAP[r][c] == WALL) continue;

			int count = 0; // 번식 가능한 칸
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

				if (MAP[nr][nc] == WALL) continue;

				if (MAP[nr][nc] == 0 && herbicide[nr][nc] == 0) count++;
			}

			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (nr < 1 || nc < 1 || nr > N || nc > N) continue;

				if (MAP[nr][nc] == WALL) continue;

				if (MAP[nr][nc] == 0 && herbicide[nr][nc] == 0)
					tmpMAP[nr][nc] += (MAP[r][c] / count);
			}
		}
	}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			MAP[r][c] += tmpMAP[r][c];
}

// (r, c)에 제초제를 나뒀을 때, 사라지는 나무의 수
int getDeleteTreeCount(int r, int c)
{
	int sum = 0;

	sum += MAP[r][c];

	for (int i = 0; i < 4; i++)
	{
		for (int k = 1; k <= K; k++)
		{
			int nr, nc;

			nr = r + dr2[i] * k;
			nc = c + dc2[i] * k;

			if (nr < 1 || nc < 1 || nr > N || nc > N) break;
			if (MAP[nr][nc] == 0 || MAP[nr][nc] == WALL) break;

			sum += MAP[nr][nc];
		}
	}

	return sum;
}

INFO findMaxDeleteTree()
{
	INFO result;
	int maxR, maxC, maxTree;

	maxR = maxC = maxTree = 0;
	for (int r = 1; r <= N; r++) // 행이 작은 순서대로
	{
		for (int c = 1; c <= N; c++) // 열이 작은 순서대로
		{
			if (MAP[r][c] == 0 || MAP[r][c] == WALL) continue;

			int deleteTreeCount = getDeleteTreeCount(r, c);
			if (maxTree < deleteTreeCount)
			{
				maxR = r;
				maxC = c;
				maxTree = deleteTreeCount;
			}

		}
	}	

	result.r = maxR;
	result.c = maxC;
	result.count = maxTree;

	return result;
}

void weeding(int r, int c)
{
	MAP[r][c] = 0;
	herbicide[r][c] = C;
	for (int i = 0; i < 4; i++)
	{
		for (int k = 1; k <= K; k++)
		{
			int nr, nc;

			nr = r + dr2[i] * k;
			nc = c + dc2[i] * k;

			if (nr < 1 || nc < 1 || nr > N || nc > N) break;
			if (MAP[nr][nc] == WALL) break;

			if (MAP[nr][nc] == 0)
			{
				herbicide[nr][nc] = C;
				break;
			}

			MAP[nr][nc] = 0;
			herbicide[nr][nc] = C;
		}
	}
}

int simulate()
{
	int sum = 0;
	for (int m = 0; m < M; m++)
	{
		spreadTree(); // 나무의 성장, 번식

		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				if (herbicide[r][c] != 0) herbicide[r][c]--;

		INFO target = findMaxDeleteTree(); // 제초제를 뿌릴 위치 선정

		weeding(target.r, target.c); // 제초제를 뿌리는 작업 진행 

		sum += target.count; // 총 박멸한 나무의 그루 수
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