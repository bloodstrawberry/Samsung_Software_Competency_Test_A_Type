#include <stdio.h>
#include <stack>

using namespace std;

int N;
stack<int> stk;

int strCompare(const char *a, const char *b)
{
	while (*a && *a == *b) ++a, ++b;
	return *a - *b;
}

void printStack(stack<int> stk)
{
	while (!stk.empty())
	{
		printf("%d ", stk.top());
		stk.pop();
	}

	putchar('\n');
}

int main()
{
	stk = {};

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		char command[100];

		scanf("%s", command);

		if (strCompare(command, "push") == 0)
		{
			int value;

			scanf("%d", &value);

			stk.push(value);
		}
		else if (strCompare(command, "pop") == 0)
		{
			if (stk.empty() == false)
			{
				printf("%d\n", stk.top());
				stk.pop();
			}
			else
				printf("-1\n");
		}
		else if (strCompare(command, "size") == 0) 
			printf("%d\n", stk.size());
		else if (strCompare(command, "empty") == 0) 
			printf("%d\n", stk.empty() ? 1 : 0);
		else if (strCompare(command, "top") == 0) 
			printf("%d\n", stk.empty() ? -1 : stk.top());
	}

	return 0;
}