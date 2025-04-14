#include <stdio.h>

#define MAX_N (50 + 5)
#define MAX_P (30 + 5)
#define INF (0x7fff0000)

#define RUDOLPH (99)

int T;

int N, M, P, C, D;
int MAP[MAX_N][MAX_N];

struct RC
{
	int r;
	int c;
};

RC rudolph;

struct SANTA
{
	int r;
	int c;
	int stun;
	bool dead;
	int score;
};

SANTA santa[MAX_P];

// 3-7. 상우하좌 우선순위
// ↑, →, ↓, ←
int dr4[] = { -1, 0, 1, 0 };
int dc4[] = { 0, 1, 0, -1 };

// ←, ↖, ↑, ↗, →, ↘, ↓, ↙
int dr8[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int dc8[] = { -1, -1, 0, 1, 1, 1, 0, -1 };

void input()
{
	scanf("%d %d %d %d %d", &N, &M, &P, &C, &D);

	scanf("%d %d", &rudolph.r, &rudolph.c);

	for (int p = 1; p <= P; p++)
	{
		int index, r, c;

		scanf("%d %d %d", &index, &r, &c);

		santa[index].r = r;
		santa[index].c = c;
		santa[index].stun = 0;
		santa[index].dead = false;
	}
}

void printStatus() // for debug
{
	printf("rudolph %d, %d\n", rudolph.r, rudolph.c);

	for (int p = 1; p <= P; p++)
	{
		SANTA s = santa[p];
		printf("%d] (%d, %d) %d / %d / %d\n", p, s.r, s.c, s.stun, s.dead, s.score);
	}
	putchar('\n');

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			printf("%2d ", MAP[r][c]);
		putchar('\n');
	}
	putchar('\n');
}

int getDistance(int r1, int c1, int r2, int c2)
{
	return (r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2);
}

bool check()
{
	for (int p = 1; p <= P; p++)
		if (santa[p].dead == false) return false;

	return true;
}

void scoreUp()
{
	for (int p = 1; p <= P; p++)
	{
		if (santa[p].dead == true) continue;

		santa[p].score++;
	}
}

void setMap()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			MAP[r][c] = 0;

	for (int p = 1; p <= P; p++)
	{
		SANTA s = santa[p];

		if (s.dead == true) continue;

		MAP[s.r][s.c] = p;
	}

	MAP[rudolph.r][rudolph.c] = RUDOLPH;
}

int getNearSantaIndex()
{
	int santaIndex, minDistance;

	santaIndex = 0;
	minDistance = INF;

	for (int r = N; r >= 1; r--)
	{
		for (int c = N; c >= 1; c--)
		{
			if (MAP[r][c] == 0 || MAP[r][c] == RUDOLPH) continue;

			int distance = getDistance(rudolph.r, rudolph.c, r, c);

			if (distance < minDistance)
			{
				minDistance = distance;
				santaIndex = MAP[r][c];
			}
		}
	}
	   	 
	return santaIndex;
}

int getRudolphDirection(int santaIndex)
{
	int direction = -1;
	int minDistance = INF;

	SANTA s = santa[santaIndex];

	for (int i = 0; i < 8; i++)
	{
		int nr, nc;

		nr = rudolph.r + dr8[i];
		nc = rudolph.c + dc8[i];

		int distance = getDistance(nr, nc, s.r, s.c);

		if (distance < minDistance)
		{
			minDistance = distance;
			direction = i;
		}
	}

	return direction;
}

void interaction(int santaIndex, int direction, bool isRudolph)
{
	SANTA startSanta = santa[santaIndex];

	// 5-2 연쇄적으로 밀려날 산타들
	int candidate[MAX_P] = { 0 };
	int count = 0;

	candidate[count++] = santaIndex;

	int sr, sc;

	sr = startSanta.r;
	sc = startSanta.c;

	while (1)
	{
		int nr, nc;

		if (isRudolph == true)
		{
			nr = sr + dr8[direction];
			nc = sc + dc8[direction];
		}
		else
		{
			nr = sr + dr4[direction];
			nc = sc + dc4[direction];
		}

		if (nr < 1 || nc < 1 || nr > N || nc > N) break;
		if (MAP[nr][nc] == 0) break;

		candidate[count++] = MAP[nr][nc];

		sr = nr;
		sc = nc;
	}

	for (int i = 0; i < count; i++)
	{
		int index = candidate[i];
		SANTA s = santa[index];

		int snr, snc;

		snr = s.r;
		snc = s.c;

		if (isRudolph == true)
		{
			snr = snr + dr8[direction];
			snc = snc + dc8[direction];
		}
		else
		{
			snr = snr + dr4[direction];
			snc = snc + dc4[direction];
		}

		if (snr < 1 || snc < 1 || snr > N || snc > N)
		{
			santa[index].dead = true;

			continue;
		}

		santa[index].r = snr;
		santa[index].c = snc;
	}
}

void moveRudolph()
{
	setMap();

	// 2-1, 2-2 우선순위가 가장 높은 가까운 산타의 번호
	int nearSantaIndex = getNearSantaIndex();

	// 2-3 우선순위가 높은 산타를 향해 돌진하는 방향
	int rudolfDirection = getRudolphDirection(nearSantaIndex);

	int nr, nc;

	nr = rudolph.r + dr8[rudolfDirection];
	nc = rudolph.c + dc8[rudolfDirection];

	rudolph.r = nr;
	rudolph.c = nc;
	
	// 4-2 루돌프가 움직여서 충돌이 일어난 경우
	if (MAP[nr][nc] != 0)
	{
		// 4-2 산타의 이동
		int crashSantaIndex = MAP[nr][nc];
		SANTA crashSanta = santa[crashSantaIndex];

		int snr, snc;

		snr = crashSanta.r + (dr8[rudolfDirection]) * C;
		snc = crashSanta.c + (dc8[rudolfDirection]) * C;

		// 4-5 게임판 밖인 경우 탈락
		if (snr < 1 || snc < 1 || snr > N || snc > N)
			santa[crashSantaIndex].dead = true;
		else if (MAP[snr][snc] != 0)
		{
			int interSantaIndex = MAP[snr][snc];

			// 5-2 상호작용
			interaction(interSantaIndex, rudolfDirection, true);
		}

		santa[crashSantaIndex].r = snr;
		santa[crashSantaIndex].c = snc;

		// 6-1 기절
		santa[crashSantaIndex].stun = 2;

		// 4-2 점수 획득
		santa[crashSantaIndex].score += C;
	}
}

void moveSanta(int santaIndex)
{
	setMap();

	SANTA s = santa[santaIndex];
	int distance = getDistance(rudolph.r, rudolph.c, s.r, s.c);
	int direction = -1;
	int minDistance = INF;

	// 3-7 상우하좌 우선순위대로 확인
	for (int i = 0; i < 4; i++)
	{
		int nr, nc;

		nr = s.r + dr4[i];
		nc = s.c + dc4[i];

		int nextDistance = getDistance(rudolph.r, rudolph.c, nr, nc);

		// 3-6 루돌프와 멀어지는 방향
		if (distance < nextDistance) continue;

		// 루돌프 확인
		if (MAP[nr][nc] == RUDOLPH)
		{
			minDistance = 1;
			direction = i;

			break;
		}

		if (MAP[nr][nc] != 0) continue;

		if (nextDistance < minDistance)
		{
			minDistance = nextDistance;
			direction = i;
		}
	}

	// 3-5 움직일 수 있는 칸이 없는 경우
	if (direction == -1) return;

	santa[santaIndex].r = s.r + dr4[direction];
	santa[santaIndex].c = s.c + dc4[direction];

	// 4-3 산타의 다음 좌표가 루돌프인 경우
	if (MAP[santa[santaIndex].r][santa[santaIndex].c] == RUDOLPH)
	{
		santa[santaIndex].stun = 1;
		santa[santaIndex].score += D;

		//    ↑, →, ↓, ← (0, 1, 2, 3)
		// => ↓, ←, ↑, → (2, 3, 0, 1)
		int changeDir[4] = { 2, 3, 0, 1 };
		int snr, snc;

		direction = changeDir[direction];
		snr = santa[santaIndex].r + (dr4[direction]) * D;
		snc = santa[santaIndex].c + (dc4[direction]) * D;

		if (snr < 1 || snc < 1 || snr > N || snc > N)
		{
			santa[santaIndex].dead = true;

			return;
		}

		santa[santaIndex].r = snr;
		santa[santaIndex].c = snc;

		// 5-2 상호작용
		if (MAP[snr][snc] != 0)
		{
			int interSantaIndex = MAP[snr][snc];

			if(interSantaIndex != santaIndex)
				interaction(interSantaIndex, direction, false);
		}
	}
}

void moveAllSanta()
{
	// 3-1 산타는 1번부터 순서대로 이동
	for (int p = 1; p <= P; p++)
	{
		SANTA s = santa[p];

		// 3-2 탈락한 산타
		if (s.dead == true) continue;

		// 3-3 기절한 산타
		// 6-1, 6-2 기절 처리
		if (s.stun != 0)
		{
			santa[p].stun--;

			continue;
		}

		moveSanta(p);
	}
}

void simulate()
{	
	for (int m = 0; m < M; m++)
	{
		// 2. 루돌프의 움직임
		moveRudolph();

		// 3. 산타의 움직임
		moveAllSanta();

		// 7-2 모든 산타가 탈락한 경우, 게임 종료
		if (check() == true) break;

		// 7-3 탈락하지 않은 산타 점수 추가
		scoreUp();
	}

	for (int p = 1; p <= P; p++)
		printf("%d ", santa[p].score);
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		simulate();
	}

	return 0;
}