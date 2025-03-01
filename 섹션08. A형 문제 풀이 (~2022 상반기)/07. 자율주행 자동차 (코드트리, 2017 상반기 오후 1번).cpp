#include <stdio.h>

#define MAX (50 + 5)

#define ROAD (0) // 도로
#define STREET (1) // 인도
#define MARK (2)

int T;
int N, M, R, C, D; // X = R, Y = C
int MAP[MAX][MAX];

// 북, 동, 남, 서
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

void input()
{
	scanf("%d %d %d %d %d", &N, &M, &R, &C, &D);

	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			scanf("%d", &MAP[r][c]);
}

void printMap() // for debug
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < M; c++)
			printf("%d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

void simulate()
{
	int changeDir[] = { 3, 0, 1, 2 };
	
	// int count = 0;
	while (1)
	{
		// 종료 조건 구현 전, while 문 디버깅
		// count++;
		// if (count == 10) break; 
		
		// for debug
		// printf("%d, %d / dir : %d\n", R, C, D);
		// printMap();

		MAP[R][C] = MARK;

		// 1. 현재 방향을 기준으로 왼쪽 방향으로 한 번도 간 적이 없다면 

		int nDir = changeDir[D]; // or (D - 1 + 4) % 4;
		int nr = R + dr[nDir];
		int nc = C + dc[nDir];

		// 좌회전해서 해당 방향으로 1 칸 전진합니다.
		if (MAP[nr][nc] == ROAD)
		{
			D = nDir;
			R = nr;
			C = nc;
		}
		else  // 2. 만약 왼쪽 방향이 인도거나 이미 방문한 도로인 경우
		{
			int i;
			for (i = 0; i < 4; i++)
			{
				D = nDir;
				int nr = R + dr[D];
				int nc = C + dc[D];

				// 좌회전하고 다시 1번 과정을 시도합니다.
				if (MAP[nr][nc] == ROAD)
				{
					R = nr;
					C = nc;
					break;
				}

				nDir = changeDir[D]; // or (D - 1 + 4) % 4;
			}

			// 3. 2번에 대해 4방향 모두 확인하였으나 전진하지 못한 경우에는 
			// 바라보는 방향을 유지한 채로 한 칸 후진을 하고 다시 1번 과정을 시도합니다.
			if (i == 4)
			{
				nr = R - dr[D];
				nc = C - dc[D];

				R = nr;
				C = nc;

				// 4. 3번 과정을 시도하려 했지만 
				// 뒷 공간이 인도여서 후진조차 하지 못한다면 작동을 멈춥니다.  
				if (MAP[R][C] == STREET) break;
			}	 
		}		             
	}
}

int getAnswer()
{
	int sum = 0;
	for (int r = 0; r < N; r++)
		for (int c = 0; c < M; c++)
			if (MAP[r][c] == MARK) sum++;

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