#include <stdio.h>

#define MAX (1000000 + 50000)

typedef long long ll;

int T;

int N;
int restaurant[MAX];
int leader, member;

void input()
{
	scanf("%d", &N);

	for (int i = 0; i < N; i++) scanf("%d", &restaurant[i]);

	scanf("%d %d", &leader, &member);
}

int main()
{
	// scanf("%d", &T);
	T = 1;
	for (int tc = 1; tc <= T; tc++)
	{
		input();

		ll sum = 0;

		for (int i = 0; i < N; i++) restaurant[i] -= leader;

		sum += N;

		for (int i = 0; i < N; i++)
		{
			if(restaurant[i] > 0)
				sum += ((restaurant[i] - 1) / member) + 1;
		}		

		printf("%lld\n", sum);
	}

	return 0;
}