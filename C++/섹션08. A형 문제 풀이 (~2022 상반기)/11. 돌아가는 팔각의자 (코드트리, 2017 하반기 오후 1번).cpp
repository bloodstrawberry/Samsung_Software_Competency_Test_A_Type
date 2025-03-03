#include <stdio.h>

#define MAX (100 + 20)

#define CLOCKWISE (1)
#define COUNTER_CLOCKWISE (-1)

int T;

int K;
int chair[5][10];
int chairNumber[MAX];
int directions[MAX];

void input()
{
	for (int number = 1; number <= 4; number++)
		for (int index = 1; index <= 8; index++)
			scanf("%1d", &chair[number][index]);

	scanf("%d", &K);
	for (int i = 0; i < K; i++)
		scanf("%d %d", &chairNumber[i], &directions[i]);
}

void rotate(int number, int direction)
{
	int tmp;

	if (direction == COUNTER_CLOCKWISE)
	{
		tmp = chair[number][1];
		for (int index = 1; index <= 7; index++)
			chair[number][index] = chair[number][index + 1];
		chair[number][8] = tmp;
	}
	else
	{
		tmp = chair[number][8];
		for (int index = 8; index >= 2; index--)
			chair[number][index] = chair[number][index - 1];
		chair[number][1] = tmp;
	}
}

void simulate()
{
	for (int k = 0; k < K; k++)
	{
		int check[5 + 1] = { 0 };

		int target = chairNumber[k];
		int direction = directions[k];

		check[target] = direction;

		for (int right = target; right <= 3; right++)
		{
			if (chair[right][3] != chair[right + 1][7])
				check[right + 1] = check[right] * (-1);
			else
				break;
		}

		for (int left = target; left >= 2; left--)
		{
			if (chair[left][7] != chair[left - 1][3])
				check[left - 1] = check[left] * (-1);
			else
				break;
		}
		
		for (int i = 1; i <= 4; i++)
			if (check[i] != 0) rotate(i, check[i]);
	}
}

int getScore()
{	
	// 의자가 많은 경우

	//int sum, mul;

	//sum = 0;
	//mul = 1;
	//for (int i = 1; i <= 4; i++)
	//{
	//	sum += mul * chair[i][1];
	//	mul *= 2;
	//}

	return (chair[1][1] * 1) + (chair[2][1] * 2) 
		+ (chair[3][1] * 4) + (chair[4][1] * 8);
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		simulate();

		printf("%d\n", getScore());
	}

	return 0;
}