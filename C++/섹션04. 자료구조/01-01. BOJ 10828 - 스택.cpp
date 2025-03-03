#include <stdio.h>

#define MAX (10000 + 500)

int N;

int stack[MAX];
int sp; /* stack pointer */

int strCompare(const char *a, const char *b)
{
	while (*a && *a == *b) ++a, ++b;
	return *a - *b;
}

void printStack()
{
	for (int i = sp - 1; i >= 0; i--)
		printf("%d ", stack[i]);
	putchar('\n');
}

int main()
{
	sp = 0;

	scanf("%d", &N);

	for (int i = 0; i < N; i++)
	{
		char command[100];

		scanf("%s", command);

		if (strCompare(command, "push") == 0)
		{
			int value;

			scanf("%d", &value);

			stack[sp++] = value;
		}
		else if (strCompare(command, "pop") == 0)
		{
			if (sp) printf("%d\n", stack[--sp]);
			else printf("-1\n");
		}
		else if (strCompare(command, "size") == 0)
			printf("%d\n", sp);
		else if (strCompare(command, "empty") == 0)
			printf("%d\n", sp ? 0 : 1);
		else if (strCompare(command, "top") == 0)
			printf("%d\n", sp ? stack[sp - 1] : -1);
	}

	return 0;
}