#include <stdio.h>

int T;

int main()
{
	scanf("%d", &T);

	for (int tc = 0; tc < T; tc++)
	{
		char str[50 + 5];
		int sp, length;
		bool flag; // true = 올바르지 않은 괄호

		scanf("%s", str);

		sp = 0;		

		for (length = 0; str[length]; length++); // 문자열 길이
		
		flag = false;

		for (int i = 0; i < length; i++)
		{
			int ch = str[i];

			if (ch == '(') sp++; 
			else --sp; 

			if (sp < 0)
			{
				flag = true;
				break;
			}
		}

		if (flag == true || sp != 0) printf("NO\n");
		else printf("YES\n");
	}

	return 0;
}