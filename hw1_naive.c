#include <stdio.h>
#include <string.h>

#define STR_MAX 10000000 //str배열의 최대 크기
#define PAT_MAX 3000 // pat배열의 최대 크기

char str[STR_MAX], pat[PAT_MAX];
int idx[STR_MAX - PAT_MAX + 1] = { 0 };

int main(void)
{
	FILE *fpstr, *fppat, *fpresult; // 파일 포인터 선언
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
	fpresult = fopen("result_naive.txt", "w"); // 각각의 파일 개방 및 파일이 없을 시 에러 메세지 출력 후 프로그램 종료.
	
	fgets(str, sizeof(str), fpstr); // str배열에 문자열 대입
	fgets(pat, sizeof(pat), fppat); // pat배열에 문자열 대입
        
        str[strlen(str) - 1] = '\0';
        pat[strlen(pat) - 1] = '\0';//개행문자 널문자로 치환

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
	}//pattern match의 개수인 cnt와 pattern match의 index를 저장하는 idx[] 수정

	fprintf(fpresult, "%d\n", cnt); // 첫 줄에 pattern match 개수 출력
	for (i = 0; i < STR_MAX - PAT_MAX + 1; i++)
	{
		if (idx[i] == 1)
		{
			fprintf(fpresult, "%d ", i);
		}
	}
        fprintf(fpresult, "\n"); // 다음 줄에 pattern match index 출력하고 줄바꿈.

        printf("Program complete. Result saved to result_naive.txt\n");

	fclose(fpstr);
	fclose(fppat);
	fclose(fpresult); // 입력 및 출력 파일 닫기

	return 0;
}
