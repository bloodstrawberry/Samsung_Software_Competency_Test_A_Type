#include <stdio.h>

#define MAX (4 + 2)
#define MAX_H (16 + 5) // 도둑말의 수

int T;

int MAP[MAX][MAX];

struct CHESS
{
	int r;
	int c;
	int dir;
	bool dead;
};

CHESS chess[MAX_H];
CHESS tagger;

int maxAnswer;

// -, ↑, ↖, ←, ↙, ↓, ↘, →, ↗
int dr[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[] = { 0, 0, -1, -1, -1, 0, 1, 1, 1 };

void input()
{
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			int index, dir;

			scanf("%d %d", &index, &dir);

			MAP[r][c] = index;

			chess[index].r = r;
			chess[index].c = c;
			chess[index].dir = dir;
			chess[index].dead = false;
		}
	}
}

void printStatus(CHESS tagger, int map[MAX][MAX], CHESS chess[MAX_H], int score) // for debug
{
	printf("score : %d\n", score);
	printf("tagger : r %d, c %d, dir %d\n", tagger.r, tagger.c, tagger.dir);

	printf("live chess : ");
	for (int i = 1; i <= 16; i++)
		if (chess[i].dead == false) printf("%d, ", i);
	putchar('\n');

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			if (r == tagger.r && c == tagger.c) printf("(%d, %d) ", -1, tagger.dir);
			else printf("(%d, %d) ", map[r][c], chess[map[r][c]].dir);
		}
		putchar('\n');
	}
	putchar('\n');
}

void DFS(CHESS prevTagger, int prevMap[MAX][MAX], CHESS prevChess[MAX_H], int score)
{
	int tmpMAP[MAX][MAX] = { 0 };
	CHESS tmpChess[MAX_H] = { 0 };
	CHESS pt = prevTagger;

	// copy
	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 4; c++)
			tmpMAP[r][c] = prevMap[r][c];

	for (int i = 1; i <= 16; i++) tmpChess[i] = prevChess[i];

	int deadIndex = tmpMAP[pt.r][pt.c];

	// 이미 잡힌 도둑말인 경우
	if (tmpChess[deadIndex].dead == true) return;

	// 술래 방향 변경
	pt.dir = tmpChess[deadIndex].dir;

	// 도둑말 사망 처리
	tmpChess[deadIndex].dead = true;

	// 점수 누적
	score += deadIndex;

	// 도둑말 이동
	for (int i = 1; i <= 16; i++)
	{
		CHESS horse = tmpChess[i];

		if (horse.dead == true) continue;

		while (1)
		{
			int nr, nc, dir;

			dir = horse.dir;
			nr = horse.r + dr[dir];
			nc = horse.c + dc[dir];

			if ((nr == pt.r && nc == pt.c)
				|| (nr < 0 || nc < 0 || nr > 3 || nc > 3))
			{
				//    -, ↑, ↖, ←, ↙, ↓, ↘, →, ↗
				// => -, ↖, ←, ↙, ↓, ↘, →, ↗, ↑
				int changeDir[9] = { 0, 2, 3, 4, 5, 6, 7, 8, 1 };
				int nextDir = changeDir[dir];

				horse.dir = nextDir;
				tmpChess[i].dir = nextDir;

				continue;
			}
			else
			{
				int tmp;
				int changeIndex = tmpMAP[nr][nc];

				// 좌표만 변경
				tmp = tmpChess[i].r;
				tmpChess[i].r = tmpChess[changeIndex].r;
				tmpChess[changeIndex].r = tmp;

				tmp = tmpChess[i].c;
				tmpChess[i].c = tmpChess[changeIndex].c;
				tmpChess[changeIndex].c = tmp;

				// MAP에서 index 변경
				tmp = tmpMAP[nr][nc];
				tmpMAP[nr][nc] = tmpMAP[horse.r][horse.c];
				tmpMAP[horse.r][horse.c] = tmp;

				break;
			}
		}
	}

	// 술래 1 ~ 3칸 이동
	int sr, sc;

	sr = pt.r;
	sc = pt.c;
	for (int i = 1; i <= 3; i++)
	{
		int nr, nc;

		nr = sr + dr[pt.dir] * i;
		nc = sc + dc[pt.dir] * i;

		if (nr < 0 || nc < 0 || nr > 3 || nc > 3)
		{
			if (maxAnswer < score) maxAnswer = score;

			break;
		}

		pt.r = nr;
		pt.c = nc;

		DFS(pt, tmpMAP, tmpChess, score);
	}
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		maxAnswer = 0;

		tagger.r = tagger.c = 0;

		DFS(tagger, MAP, chess, 0);

		printf("%d\n", maxAnswer);
	}

	return 0;
}