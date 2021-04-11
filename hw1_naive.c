#include <stdio.h>
#include <string.h>

#define STR_MAX 10000000 //str�迭�� �ִ� ũ��
#define PAT_MAX 3000 // pat�迭�� �ִ� ũ��

char str[STR_MAX], pat[PAT_MAX];
int idx[STR_MAX - PAT_MAX + 1] = { 0 };

int main(void)
{
	FILE *fpstr, *fppat, *fpresult; // ���� ������ ����
	int cnt, i, temp, j, len_str, len_pat;
	cnt = 0;

	fpstr = fopen("string.txt", "r");
	if (fpstr == NULL)
	{
		printf("The string file does not exist.");
		return 1;
	}
	fppat = fopen("pattern.txt", "r");
	if (fppat == NULL)
	{
		printf("The pattern file does not exist.");
		return 1;
	}
	fpresult = fopen("result_naive.txt", "w"); // ������ ���� ���� �� ������ ���� �� ���� �޼��� ��� �� ���α׷� ����.
	
	fgets(str, sizeof(str), fpstr); // str�迭�� ���ڿ� ����
	fgets(pat, sizeof(pat), fppat); // pat�迭�� ���ڿ� ����
        
        str[strlen(str) - 1] = '\0';
        pat[strlen(pat) - 1] = '\0';//���๮�� �ι��ڷ� ġȯ

        len_str = strlen(str);
        len_pat = strlen(pat);

	for (i = 0; i < len_str - len_pat + 1; i++)
	{
		temp = i;
		for (j = 0; j < len_pat; j++)
		{
			if (str[i] == pat[j])
			{
				i++;
				if (pat[j+1] == '\0')
				{
					cnt++;
					idx[temp] = 1;
					i = temp;
				}
			}
			else
			{
				i = temp;
				break;
			}
		}
	}//pattern match�� ������ cnt�� pattern match�� index�� �����ϴ� idx[] ����

	fprintf(fpresult, "%d\n", cnt); // ù �ٿ� pattern match ���� ���
	for (i = 0; i < STR_MAX - PAT_MAX + 1; i++)
	{
		if (idx[i] == 1)
		{
			fprintf(fpresult, "%d ", i);
		}
	}
        fprintf(fpresult, "\n"); // ���� �ٿ� pattern match index ����ϰ� �ٹٲ�.

        printf("Program complete. Result saved to result_naive.txt\n");

	fclose(fpstr);
	fclose(fppat);
	fclose(fpresult); // �Է� �� ��� ���� �ݱ�

	return 0;
}
