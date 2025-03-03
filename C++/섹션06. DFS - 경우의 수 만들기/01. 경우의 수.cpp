#include <stdio.h>

int main()
{
	int count;

	if (1)
	{
		// 4 Pi 3;
		count = 1;
		for (int a = 1; a <= 4; a++)
			for (int b = 1; b <= 4; b++)
				for (int c = 1; c <= 4; c++)
					printf("%d] %d %d %d\n", count++, a, b, c);
	}

	if (0)
	{
		// 4 H 3;
		count = 1;
		for (int a = 1; a <= 4; a++)
			for (int b = a; b <= 4; b++)
				for (int c = b; c <= 4; c++)
					printf("%d] %d %d %d\n", count++, a, b, c);
	}

	if (0)
	{
		// 4 C 3;
		count = 1;
		for (int a = 1; a <= 4; a++)
			for (int b = a + 1; b <= 4; b++)
				for (int c = b + 1; c <= 4; c++)
					printf("%d] %d %d %d\n", count++, a, b, c);
	}

	if (0)
	{
		// 4 P 3;
		count = 1;
		bool visit[5] = { 0 };
		for (int a = 1; a <= 4; a++)
		{
			visit[a] = true;
			for (int b = 1; b <= 4; b++)
			{
				if (visit[b] == true) continue;

				visit[b] = true;
				for (int c = 1; c <= 4; c++)
				{
					if (visit[c] == true) continue;

					printf("%d] %d %d %d\n", count++, a, b, c);
				}
				visit[b] = false;
			}
			visit[a] = false;
		}
	}


	return 0;
}