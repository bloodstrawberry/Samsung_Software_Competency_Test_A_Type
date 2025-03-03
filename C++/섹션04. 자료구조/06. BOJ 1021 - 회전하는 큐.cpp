#include <stdio.h>

#define MAX (50 + 5)
#define MAX_DEQUE (MAX * MAX * 2)
#define OFFSET (MAX_DEQUE / 2)

int N, M;
int position[MAX];

int deque[MAX_DEQUE * 2];
int front, back;

void input()
{
	scanf("%d %d", &N, &M);

	for (int i = 0; i < M; i++) scanf("%d", &position[i]);

	// init
	front = back = OFFSET;

	for (int i = 1; i <= N; i++) deque[back++] = i;
}

int getLeftCount(int value)
{
	int ret = 0;
	for (int i = front; i < back; i++)
	{
		if (deque[i] == value) return ret;

		ret++;
	}

	return -1; // error
}

int getRightCount(int value) 
{
	int ret = 0;
	for (int i = back - 1; i >= front; i--)
	{
		ret++;

		if (deque[i] == value) return ret;
	}

	return -1; // error
}

int main()
{
	input();

	int answer = 0;

	for (int i = 0; i < M; i++)
	{
		if (deque[front] == position[i]) front++;
		else
		{
			int leftCount = getLeftCount(position[i]);
			int rightCount = getRightCount(position[i]);

			if (leftCount < rightCount)
			{
				for (int k = 0; k < leftCount; k++)
					deque[back++] = deque[front++];

				front++;

				answer += leftCount;
			}
			else
			{
				for (int k = 0; k < rightCount; k++)
					deque[--front] = deque[--back];

				front++;

				answer += rightCount;
			}
		}
	}

	printf("%d\n", answer);

	return 0;
}