#include <stdio.h>

#define MAX (50 + 5)

int T;
int N, M, maxBoxNum;

int MAP[MAX][MAX];

struct BOX
{
	int k; // 택배 번호
	int h; // 세로 크기
	int w; // 가로 크기
	int r; // 행
	int c; // 열
	bool drop; // 하차 여부
};

BOX box[100 + 10];

void input()
{
	maxBoxNum = 0;

	scanf("%d %d", &N, &M);

	for (int i = 1; i <= 100; i++)
		box[i].k = 0;

	for (int r = 0; r <= N + 1; r++)
		for (int c = 0; c <= N + 1; c++)
			MAP[r][c] = -1;

	for (int r = 1; r <= N; r++)
		for (int c = 1; c <= N; c++)
			MAP[r][c] = 0;
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

bool checkDown(int index)
{
	BOX b = box[index];

	for (int c = b.c; c < b.c + b.w; c++)
		if (MAP[b.r + b.h][c] != 0) return false; // 이동 불가

	return true;
}

void setBox(int index)
{
	BOX b = box[index];
	for (int r = b.r; r < b.r + b.h; r++)
		for (int c = b.c; c < b.c + b.w; c++)
			MAP[r][c] = index;
}

void deleteBox(int index)
{
	BOX b = box[index];
	for (int r = b.r; r < b.r + b.h; r++)
		for (int c = b.c; c < b.c + b.w; c++)
			MAP[r][c] = 0;
}

void moveDown(int index)
{
	BOX b = box[index];

	deleteBox(index);

	while (1)
	{
		if (checkDown(index) == false) break;

		b.r += 1; // 임시 변수 수정
		box[index].r += 1; // 실제값 수정
	}
	
	setBox(index);
}

bool checkLeft(int index)
{
	BOX b = box[index];

	for (int r = b.r; r < b.r + b.h; r++)
		for (int c = 1; c < b.c; c++)
			if (MAP[r][c] != 0) return false;

	return true;
}

void moveLeft()
{
	for (int i = 1; i <= maxBoxNum; i++)
	{
		if (box[i].drop == true || box[i].k == 0) continue;

		if (checkLeft(i) == true)
		{
			box[i].drop = true;
			deleteBox(i);

			printf("%d\n", i);

			return;
		}
	}
}

bool checkRight(int index)
{
	BOX b = box[index];

	for (int r = b.r; r < b.r + b.h; r++)
		for (int c = b.c + b.w; c <= N; c++)
			if (MAP[r][c] != 0) return false;

	return true;
}

void moveRight()
{
	for (int i = 1; i <= maxBoxNum; i++)
	{
		if (box[i].drop == true || box[i].k == 0) continue;

		if (checkRight(i) == true)
		{
			box[i].drop = true;
			deleteBox(i);

			printf("%d\n", i);

			return;
		}
	}
}

void moveDownAll()
{
	while (1)
	{
		bool check = true;
		for (int i = 1; i <= maxBoxNum; i++)
		{
			if (box[i].drop == true || box[i].k == 0) continue;
			if (checkDown(i) == false) continue;

			check = false;

			moveDown(i);
		}

		if (check == true) break;
	}
}

void simulate()
{
	// 1. 택배 투입
	for (int m = 0; m < M; m++)
	{
		int k, h, w, c;

		scanf("%d %d %d %d", &k, &h, &w, &c);

		box[k].k = k; // M과 최대 k가 다를 수 있음.
		box[k].h = h;
		box[k].w = w;
		box[k].r = 1;
		box[k].c = c;
		box[k].drop = false;

		if (maxBoxNum < k) maxBoxNum = k;

		moveDown(k);
	}

	// printMap();

	for (int m = 0; m < M; m += 2)
	{
		// 2. 택배 하차 (좌측)
		moveLeft();
		moveDownAll();

		// 3. 택배 하차 (우측)
		moveRight();
		moveDownAll();
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
	}

	return 0;
}