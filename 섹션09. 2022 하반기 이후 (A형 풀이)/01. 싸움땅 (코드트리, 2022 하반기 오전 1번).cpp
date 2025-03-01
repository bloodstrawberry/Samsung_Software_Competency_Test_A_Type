#include <stdio.h>

#define MAX (20 + 5)

int T;
int N, M, K;

int GUN[MAX][MAX][MAX * MAX];
int gIndex[MAX][MAX];

struct PLAYER
{
	int r;
	int c;
	int dir;
	int s; // 초기 능력치
	int gun;
};

PLAYER player[30 + 5];

// ↑, →, ↓, ←
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };

int SCORE[30 + 5];

void input()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			gIndex[r][c] = 0;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			scanf("%d", &GUN[r][c][0]);

			if (GUN[r][c][0] != 0) gIndex[r][c] = 1;
		}
	}

	for (int m = 1; m <= M; m++) // player 번호는 1번 부터
	{
		SCORE[m] = 0;

		int r, c, d, s; // x = r, y = c

		scanf("%d %d %d %d", &r, &c, &d, &s);

		player[m].r = r;
		player[m].c = c;
		player[m].dir = d;
		player[m].s = s;
		player[m].gun = 0; // 초기화
	}
}

void printMap(int map[MAX][MAX]) // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%d ", map[r][c]);
		putchar('\n');

	}
	putchar('\n');
}

int getMaxPowerGunIndex(int r, int c)
{
	int max = -1;
	int count = gIndex[r][c];
	int index = 0;
	for (int i = 0; i < count; i++)
	{
		if (max < GUN[r][c][i])
		{
			max = GUN[r][c][i];
			index = i;
		}
	}

	return index;
}

// p1이 이기면 0, p2가 이기면 1
int battle(PLAYER p1, PLAYER p2)
{
	int g1 = p1.gun;
	int s1 = p1.s;
	int g2 = p2.gun;
	int s2 = p2.s;

	int sum1 = g1 + s1;
	int sum2 = g2 + s2;

	if (sum1 > sum2) return 0;
	if (sum1 < sum2) return 1;

	if (s1 > s2) return 0;
	if (s1 < s2) return 1;

	return -1; // for debug
}

void simulate()
{
	int changDir[4] = { 2, 3, 0, 1 };

	for (int k = 0; k < K; k++)
	{
		int tmpMAP[MAX][MAX] = { 0 };

		// 현재 player의 번호를 마킹
		for (int m = 1; m <= M; m++)
		{
			int r, c;

			r = player[m].r;
			c = player[m].c;

			tmpMAP[r][c] = m;
		}

		for (int m = 1; m <= M; m++)
		{
			// 1-1. 플레이어 순차적으로 이동
			PLAYER p = player[m];

			int nr, nc, dir;

			dir = p.dir;
			nr = p.r + dr[dir];
			nc = p.c + dc[dir];

			// 1-1. 격자를 벗어나는 경우, 반대 방향으로 변경 후 이동
			if (nr < 1 || nc < 1 || nr > N || nc > N)
			{
				dir = changDir[dir];
				player[m].dir = dir;

				nr = p.r + dr[dir];
				nc = p.c + dc[dir];
			}

			// 2-1. 이동할 방향에 플레이어가 있는지 체크,
			if (tmpMAP[nr][nc] == 0) // 없는 경우
			{
				// tmpMAP에서 이동
				tmpMAP[p.r][p.c] = 0;
				tmpMAP[nr][nc] = m;

				// player 좌표 갱신
				player[m].r = nr;
				player[m].c = nc;

				if (gIndex[nr][nc] != 0) // 총이 있는 경우
				{
					int playerGun = player[m].gun;
					int gunIndex = getMaxPowerGunIndex(nr, nc);

					if (playerGun < GUN[nr][nc][gunIndex])
					{
						int tmp = player[m].gun;
						player[m].gun = GUN[nr][nc][gunIndex];
						GUN[nr][nc][gunIndex] = tmp;
					}
				}
			}
			else // 2-2. player가 있는 경우
			{
				int another, winner, loser;

				another = tmpMAP[nr][nc];

				// 이동한 플레이어 0으로 갱신
				tmpMAP[player[m].r][player[m].c] = 0;

				if (battle(player[m], player[another]) == 0) // m이 이긴 경우
				{
					winner = m;
					loser = another;
				}
				else
				{
					winner = another;
					loser = m;
				}

				// 2-2-1. 점수 획득
				SCORE[winner]
					+= ((player[winner].gun + player[winner].s)) - ((player[loser].gun + player[loser].s));

				// 2-2-2. 패배한 플레이어
				int loserGun = player[loser].gun;
				player[loser].gun = 0;

				GUN[nr][nc][gIndex[nr][nc]++] = loserGun;

				for (int i = 0; i < 4; i++)
				{
					int lnr, lnc;

					lnr = nr + dr[player[loser].dir];
					lnc = nc + dc[player[loser].dir];

					if (lnr < 1 || lnc < 1 || lnr > N || lnc > N || tmpMAP[lnr][lnc] != 0)					
						player[loser].dir = (player[loser].dir + 1) % 4;
					else
					{
						tmpMAP[nr][nc] = 0;
						tmpMAP[lnr][lnc] = loser;

						player[loser].r = lnr;
						player[loser].c = lnc;

						if (gIndex[lnr][lnc] != 0) // 총이 있는 경우
						{
							int playerGun = player[loser].gun;
							int gunIndex = getMaxPowerGunIndex(lnr, lnc);

							if (playerGun < GUN[lnr][lnc][gunIndex])
							{
								player[loser].gun = GUN[lnr][lnc][gunIndex];
								GUN[lnr][lnc][gunIndex] = 0;
							}
						}

						break;
					}
				}

				// 2-2-3. 이긴 플레이어는 더 좋은 총으로 변경
				int playerGun = player[winner].gun;
				int gunIndex = getMaxPowerGunIndex(nr, nc);
				if (playerGun < GUN[nr][nc][gunIndex])
				{
					int tmp = player[winner].gun;
					player[winner].gun = GUN[nr][nc][gunIndex];
					GUN[nr][nc][gunIndex] = tmp;
				}
				
				// 이긴 플레이어 표시
				tmpMAP[nr][nc] = winner;

				player[winner].r = nr;
				player[winner].c = nc;
			}
		}
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

		for (int m = 1; m <= M; m++) 
			printf("%d ", SCORE[m]);
		putchar('\n');
	}

	return 0;
}