#include <stdio.h>

#define MAX (20 + 5)
#define INF (0x7fff0000)

#define WALL (-1)

int T;

int N;
int MAP[MAX][MAX];

int student[MAX * MAX];
bool love[MAX * MAX][MAX * MAX];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

struct SEAT
{
	int like; // 주변의 좋아하는 친구 수
	int empty; // 주변의 빈 자리 수
	int r;
	int c;
};

void input()
{
	scanf("%d", &N);

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = WALL;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			MAP[r][c] = 0;

	for (int r = 1; r <= N * N; r++)
		for (int c = 1; c <= N * N; c++)
			love[r][c] = false;

	for (int i = 0; i < N * N; i++)
	{
		int num, one, two, three, four;

		scanf("%d %d %d %d %d", &num, &one, &two, &three, &four);

		student[i] = num;
		love[num][one] = true;
		love[num][two] = true;
		love[num][three] = true;
		love[num][four] = true;
	}
}

void printMap() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

SEAT getSeatInfo(int index, int r, int c)
{
	int like, empty;

	like = empty = 0;
	for (int i = 0; i < 4; i++)
	{
		int nr, nc;

		nr = r + dr[i];
		nc = c + dc[i];

		if (MAP[nr][nc] == WALL) continue;

		if (MAP[nr][nc] == 0) empty++;
		else if (love[index][MAP[nr][nc]] == true) like++;
	}

	return { like, empty, r, c };
}

// a가 우선순위가 더 높으면 true
bool isPriority(SEAT a, SEAT b)
{	
	if (a.like != b.like) return a.like > b.like;
	if (a.empty != b.empty) return a.empty > b.empty;
	if (a.r != b.r) return a.r < b.r;
	   
	return a.c < b.c;
}

void simulate()
{
	for (int i = 0; i < N * N; i++)
	{
		int index = student[i];

		SEAT wanted = { 0 };

		wanted.r = wanted.c = INF;
		for (int r = 1; r <= N; r++)
		{
			for (int c = 1; c <= N; c++)
			{
				if (MAP[r][c] != 0) continue;

				SEAT tmp = getSeatInfo(index, r, c);

				if (isPriority(tmp, wanted) == true)
					wanted = tmp;
			}
		}
		
		MAP[wanted.r][wanted.c] = index;
	}

	// printMap();
}

int getAnswer()
{
	int board[5] = { 0, 1, 10, 100, 1000 };

	int score = 0;
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			int index, count;
			
			index = MAP[r][c];
			count = 0;
			for (int i = 0; i < 4; i++)
			{
				int nr, nc;

				nr = r + dr[i];
				nc = c + dc[i];

				if (MAP[nr][nc] == WALL) continue;

				if (love[index][MAP[nr][nc]] == true) count++;
			}

			//if (count == 1) score += 1;
			//else if (count == 2) score += 10;
			//else if (count == 3) score += 100;
			//else if (count == 4) score += 1000;

			score += board[count];
		}
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

		simulate();

		printf("%d\n", getAnswer());
	}

	return 0;
}