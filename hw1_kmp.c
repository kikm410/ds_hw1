#include <stdio.h>
#include <string.h>

#define STR_MAX 10000000 //str배열의 최대 크기
#define PAT_MAX 3000 //pat배열의 최대 크기

char str[STR_MAX], pat[PAT_MAX];
int failure[PAT_MAX];
int idx[STR_MAX - PAT_MAX + 1] = { 0 };
void fail(char*);

int main(void)
{
        FILE *fpstr, *fppat, *fpresult; // 파일 포인터 선언
        int cnt = 0, i = 0, j = 0, len_str, len_pat;

        fpstr = fopen("string.txt", "r");
        if (fpstr == NULL)
        {
                printf("string file not found.");
                return 1;
        }
        fppat = fopen("pattern.txt", "r");
        if (fppat == NULL)
        {
                printf("pattern file not found.");
                return 1;
        }

        fpresult = fopen("result_kmp.txt", "w"); // 각 파일 개방 및 파일 없을 시 에러 메세지 출력 후 프로그램 종료

        fgets(str, sizeof(str), fpstr);
        fgets(pat, sizeof(pat), fppat); // 각 배열에 문자열 대입
        
        str[strlen(str) - 1] = '\0';
        pat[strlen(pat) - 1] = '\0';// 각 배열의 개행문자 널문자로 변경
        
        fail(pat); // fail 함수 호출해 failure배열 조정

        len_str = strlen(str);
        len_pat = strlen(pat);

        while (i < len_str)
        {
                if(str[i] == pat[j])
                {

                        if (j == len_pat - 1)
                        {
                                cnt++;
                                idx[i - len_pat + 1] = 1;
                        }
                        i++;
                        j++;
                }
                else if (j == 0)
                {
                        i++;
                }
                else
                {
                        j = failure[j - 1] + 1;
                }
        } // failure 배열 이용한 kmp 알고리즘 구현, 올바른 출력을 위해 cnt 와 idx배열 조정

        fprintf(fpresult, "%d\n", cnt); // 첫 줄에 pattern match 개수 출력
        for (i = 0; i < STR_MAX - PAT_MAX + 1; i++)
        {
                if (idx[i] == 1)
                {
                        fprintf(fpresult, "%d ", i);
                }
        }
        fprintf(fpresult, "\n"); // 다음 줄에 pattern match index 출력하고 줄바꿈 

        printf("Program complete. Result saved to result_kmp.txt\n");

        fclose(fpstr);
        fclose(fppat);
        fclose(fpresult); // 입력 및 출력 파일 닫기

        return 0;
}

void fail(char *pat)
{
        int i, j;
        failure[0] = -1;
        for(j = 1; j < strlen(pat); j++)
        {
                i = failure[j - 1];
                while ((pat[j] != pat[i + 1]) && (i >= 0))
                {
                        i = failure[i];
                }
                if (pat[j] == pat[i + 1])
                {
                        failure[j] = i + 1;
                }
                else
                {
                        failure[j] = -1;
                }
        }
}
