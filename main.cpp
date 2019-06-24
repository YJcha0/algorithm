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
        printf("打开文件错！请下载文件，并将之复制到与源程序文件同一文件夹下。\n");
        exit(1);
    }
    while(fscanf(fp, "%d", &x[n])!=EOF)
        n++;
    printf("数据量：%d, 开始排序....", n);
    t1=time(0);
/*-----------------------------------------------------*/
    MergeSort(x, n);
/*-----------------------------------------------------*/
    t2=time(0);
    printf("用时 %d 秒!", (int)(t2-t1));
    fclose(fp);
    return 0;
}
