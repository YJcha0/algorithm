#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include "search.h"
int main()
{
    RecType x[MaxSize];
    int n = 0;
    double t1,t2;
    FILE *fp;
    fp = fopen("numbers.txt", "r");
    if(fp==NULL)
    {
        printf("���ļ����������ļ�������֮���Ƶ���Դ�����ļ�ͬһ�ļ����¡�\n");
        exit(1);
    }
    while(fscanf(fp, "%d", &x[n])!=EOF)
        n++;
    printf("��������%d, ��ʼ����....", n);
    t1=time(0);
/*-----------------------------------------------------*/
    MergeSort(x, n);
/*-----------------------------------------------------*/
    t2=time(0);
    printf("��ʱ %d ��!", (int)(t2-t1));
    fclose(fp);
    return 0;
}
