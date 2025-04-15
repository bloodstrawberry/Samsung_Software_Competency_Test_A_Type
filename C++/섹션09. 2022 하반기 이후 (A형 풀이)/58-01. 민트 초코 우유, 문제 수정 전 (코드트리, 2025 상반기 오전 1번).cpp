#include <stdio.h>

#define MAX (50 + 5)

#define TMINT_CHOKO_MILK (111)
#define TMINT_CHOKO (1 + 10)
#define TMINT_MILK (1 + 100)
#define CHOKO_MILK (100 + 10)
#define MILK (100)
#define CHOKO (10)
#define TMINT (1)

#define UP (0)
#define DOWN (1)
#define LEFT (2)
#define RIGHT (3)

int TestCase;
int N, T;
char F[MAX][MAX];
int B[MAX][MAX];

struct STUDENT
{
	int food; // 신봉하는 음식
	int believe; // 신앙심
	bool isLeader; // 대표
	int defense; // 방어 여부
	int row; // 대표자 선정을 위한 값
	int col;
};

STUDENT student[MAX][MAX];
STUDENT candidates[MAX * MAX];
int ccnt;

STUDENT group[3 + 1][MAX * MAX];
int index[3 + 1];

struct RC
{
	int r;
	int c;
};

RC queue[MAX * MAX];
bool visit[MAX][MAX];

// 위, 아래, 왼쪽, 오른쪽
int dr[4] = { -1, 1, 0, 0 };
int dc[4] = { 0, 0, -1, 1 };

void input()
{
	scanf("%d %d", &N, &T);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf(" %c", &F[r][c]);

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			scanf("%d", &B[r][c]);

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			student[r][c].believe = B[r][c];
			student[r][c].isLeader = false; // 초기화
			student[r][c].defense = 0; // 초기화
			student[r][c].row = r;
			student[r][c].col = c;

			if (F[r][c] == 'T') student[r][c].food = TMINT;
			else if (F[r][c] == 'C') student[r][c].food = CHOKO;
			else if (F[r][c] == 'M') student[r][c].food = MILK;
		}
	}
}

void printBelieve() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			printf("%d ", student[r][c].believe);
		}
		putchar('\n');
	}
	putchar('\n');
}

void printFood() // for debug
{
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			printf("%3d ", student[r][c].food);
		}
		putchar('\n');
	}
	putchar('\n');
}

void printGroup() // for debug
{
	for (int g = 1; g <= 3; g++)
	{
		int gIndex = index[g];
		printf("group %d ", g);

		for (int i = 0; i < gIndex; i++)
			printf("(%d, %d) ", group[g][i].row, group[g][i].col);

		putchar('\n');
	}
}

void morning()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			student[r][c].believe++;
}

// a가 우선순위가 더 높으면 true
bool isPriority(STUDENT a, STUDENT b)
{
	if (a.believe != b.believe) return a.believe > b.believe;
	if (a.row != b.row) return a.row < b.row;

	return a.col < b.col;
}

void BFS(int r, int c)
{
	int rp, wp;

	rp = wp = 0;

	queue[wp].r = r;
	queue[wp++].c = c;

	visit[r][c] = true;

	ccnt = 0;
	candidates[ccnt++] = student[r][c];

	while (rp < wp)
	{
		RC out = queue[rp++];

		for (int i = 0; i < 4; i++)
		{
			int nr, nc;

			nr = out.r + dr[i];
			nc = out.c + dc[i];

			if (nr < 1 || nc < 1 || nr > N || nc > N) continue;
			if (visit[nr][nc] == true) continue;

			// 인접한 학생들과 신봉 음식이 완전히 같은 경우에만 그룹을 형성
			if (student[out.r][out.c].food != student[nr][nc].food) continue;

			queue[wp].r = nr;
			queue[wp++].c = nc;

			visit[nr][nc] = true;

			candidates[ccnt++] = student[nr][nc];
		}
	}

	STUDENT leader = { 0 };
	for (int i = 0; i < ccnt; i++)
		if (isPriority(candidates[i], leader) == true)
			leader = candidates[i];

	student[leader.row][leader.col].isLeader = true;
	student[leader.row][leader.col].believe += (ccnt - 1);

	for (int i = 0; i < ccnt; i++)
	{
		STUDENT c = candidates[i];

		if (c.row == leader.row && c.col == leader.col) continue;

		student[c.row][c.col].believe--;
	}
}

void lunch()
{
	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			visit[r][c] = student[r][c].isLeader = false;

	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			if (visit[r][c] == true) continue;

			BFS(r, c);
		}
	}
}

int getGroupNumber(int food)
{
	if (food == TMINT_CHOKO_MILK) return 3;
	if (food == TMINT || food == CHOKO || food == MILK) return 1;

	return 2;
}

int mixFood(int sFood, int nFood)
{
	return sFood | nFood;
}

void dinner()
{
	int defense[MAX][MAX] = { 0 };

	for (int g = 1; g <= 3; g++) index[g] = 0;

	// 그룹 별 분리
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
		{
			STUDENT s = student[r][c];

			if (s.isLeader == false) continue;

			int groupNumber = getGroupNumber(s.food);

			group[groupNumber][index[groupNumber]++] = s;
		}
	}

	// 그룹 내 정렬
	for (int g = 1; g <= 3; g++)
	{
		int gIndex = index[g];
		for (int i = 0; i < gIndex - 1; i++)
		{
			for (int k = i + 1; k < gIndex; k++)
			{
				STUDENT a = group[g][i];
				STUDENT b = group[g][k];

				if (isPriority(a, b) == false)
				{
					group[g][i] = b;
					group[g][k] = a;
				}
			}
		}
	}

	// printGroup();

	// 전파 시작
	for (int g = 1; g <= 3; g++)
	{
		int gIndex = index[g];
		for (int i = 0; i < gIndex; i++)
		{
			int gr, gc;

			gr = group[g][i].row;
			gc = group[g][i].col;

			STUDENT spreader = student[gr][gc];

			// 방어 상태에서는 대표자가 되어도 전파를 하지 않음.
			if (spreader.defense != 0) continue;

			int sr, sc;

			sr = spreader.row;
			sc = spreader.col;

			// 원본의 신앙심을 1로 변경
			student[sr][sc].believe = 1;

			int x = spreader.believe - 1; // 간절함
			int dir = spreader.believe % 4;

			while (1)
			{
				int nr, nc;

				nr = sr + dr[dir];
				nc = sc + dc[dir];

				// 격자 밖으로 나가거나 간절함이 0이 되면 전파 종료
				if (nr < 1 || nc < 1 || nr > N || nc > N || x == 0) break;

				// 전파 대상
				STUDENT next = student[nr][nc];

				// 전파 대상이 전파자와 신봉 음식이 완전히 같은 경우
				// 다른 대표자가 전파를 시도하더라도, 같은 음식처럼 처리
				if (next.food == spreader.food || next.defense != 0)
				{
					// 전파를 하지 않고 바로 다음으로 진행
					sr = nr;
					sc = nc;

					continue;
				}

				// 전파 대상이 전파자와 신봉 음식이 다른 경우, 전파 시도
				int y = next.believe; // 신앙심

				// 대표자에게 전파가 시도된 학생은 방어 상태
				defense[next.row][next.col] = 2;

				if (x > y) // 전파 실패
				{
					x -= (y + 1);
					if (x < 0) x = 0;

					student[next.row][next.col].believe++;
				}
				else // x <= y, 전파 성공
				{
					student[next.row][next.col].believe += x;
					student[next.row][next.col].food = mixFood(spreader.food, next.food);

					x = 0;

					break;
				}

				sr = nr;
				sc = nc;
			}
		}
	}

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			student[r][c].defense = defense[r][c];
}

void printAnswer()
{
	int sum[TMINT_CHOKO_MILK + 1] = { 0 };

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			sum[student[r][c].food] += student[r][c].believe;

	int outputIndex[7]
		= { TMINT_CHOKO_MILK, TMINT_CHOKO, TMINT_MILK, CHOKO_MILK, MILK, CHOKO, TMINT };

	for (int i = 0; i < 7; i++)
		printf("%d ", sum[outputIndex[i]]);
	putchar('\n');
}

void simulate()
{
	for (int t = 0; t < T; t++)
	{
		morning();
		lunch();
		dinner();

		for (int r = 1; r <= N; r++)
			for (int c = 1; c <= N; c++)
				if (student[r][c].defense != 0) student[r][c].defense--;

		printAnswer();
	}
}

int main()
{
	// scanf("%d", &TestCase);
	TestCase = 1;
	for (int tc = 1; tc <= TestCase; tc++)
	{
		input();

		simulate();
	}

	return 0;
}