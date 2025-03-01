#include <stdio.h>

#define MAX (10 + 5)
#define INF (0x7fff0000)

int T;

int N, M;
char MAP[MAX][MAX];

int num_of_cases[10 + 5];

struct RC
{
	int r;
	int c;
};

RC RED, BLUE;

int minAnswer;

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d", &N, &M);

	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
		{
			scanf(" %c", &MAP[r][c]);

			if (MAP[r][c] == 'R')
			{
				RED.r = r;
				RED.c = c;
				
				MAP[r][c] = '.';
			}
			else if (MAP[r][c] == 'B')
			{
				BLUE.r = r;
				BLUE.c = c;

				MAP[r][c] = '.';
			}
		}
	}
}

void printMap() // for debug
{
	MAP[RED.r][RED.c] = 'R';
	MAP[BLUE.r][BLUE.c] = 'B';

	for (int r = 0; r < N; r++) 
		printf("%s\n", MAP[r]);
	putchar('\n');

	MAP[RED.r][RED.c] = '.';
	MAP[BLUE.r][BLUE.c] = '.';
}

void printCases()
{
	for (int i = 0; i < 10; i++) printf("%d ", num_of_cases[i]);
	putchar('\n');
}

int simulate()
{
	RC red, blue;

	red = RED;
	blue = BLUE;

	for (int i = 0; i < 10; i++)
	{
		int direction = num_of_cases[i];
	
		while (1)
		{
			int red_nr = red.r + dr[direction];
			int red_nc = red.c + dc[direction];
			int blue_nr = blue.r + dr[direction];
			int blue_nc = blue.c + dc[direction];

			bool checkWallRed = MAP[red_nr][red_nc] == '#';
			bool checkWallBlue = MAP[blue_nr][blue_nc] == '#';
			bool checkCandyRed = (red_nr == blue.r) && (red_nc == blue.c);
			bool checkCandyBlue = (blue_nr == red.r) && (blue_nc == red.c);

			// for debug
			// RED = red; BLUE = blue;
			// printMap();

			// 둘 다 다음 좌표가 벽이면 break;
			if (checkWallRed == true && checkWallBlue == true) break;

			// 둘 다 다음 좌표가 벽이 아니라면, 1칸 이동
			if (checkWallRed == false && checkWallBlue == false)
			{
				red.r = red_nr;
				red.c = red_nc;

				blue.r = blue_nr;
				blue.c = blue_nc;
			}
			// 둘 중 하나의 사탕만 움직이는 경우
			else if (checkWallRed == true && checkCandyBlue == false)
			{
				blue.r = blue_nr;
				blue.c = blue_nc;
			}
			else if (checkWallBlue == true && checkCandyRed == false)
			{
				red.r = red_nr;
				red.c = red_nc;
			}
			// 그 외의 모든 경우 break
			else
				break;

			if (MAP[red.r][red.c] == 'O')
			{
				while (MAP[blue.r][blue.c] != '#')
				{
					if (MAP[blue.r][blue.c] == 'O') return INF;

					blue.r += dr[direction];
					blue.c += dc[direction];
				}

				return i + 1;
			}

			if (MAP[blue.r][blue.c] == 'O') return INF;
		}
	}

	return INF;
}

void DFS(int depth, int direction)
{
	if (depth == 10)
	{
		// printCases();

		int tmp = simulate();
		if (tmp < minAnswer) minAnswer = tmp;
				
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		// 연속된 방향 무시
		if (i == direction) continue;

		num_of_cases[depth] = i;

		DFS(depth + 1, i);
	}
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		minAnswer = INF;
		
		DFS(0, -1);

		if (minAnswer == INF) printf("-1\n");
		else printf("%d\n", minAnswer);
	}
	
	return 0;
}