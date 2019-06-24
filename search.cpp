#include <stdio.h>
#include <malloc.h>
#include "search.h"
void InsertSort(RecType R[],int n) //对R[0..n-1]按递增有序进行直接插入排序
{
    int i,j;
    RecType tmp;
    for (i=1; i<n; i++)
    {
        tmp=R[i];
        j=i-1;            //从右向左在有序区R[0..i-1]中找R[i]的插入位置
        while (j>=0 && tmp.key<R[j].key)
        {
            R[j+1]=R[j]; //将关键字大于R[i].key的记录后移
            j--;
        }
        R[j+1]=tmp;      //在j+1处插入R[i]
    }
}

void ShellSort(RecType R[],int n)   //希尔排序算法
{
    int i,j,gap;
    RecType tmp;
    gap=n/2;                //增量置初值
    while (gap>0)
    {
        for (i=gap; i<n; i++) //对所有相隔gap位置的所有元素组进行排序
        {
            tmp=R[i];
            j=i-gap;
            while (j>=0 && tmp.key<R[j].key)//对相隔gap位置的元素组进行排序
            {
                R[j+gap]=R[j];
                j=j-gap;
            }
            R[j+gap]=tmp;
            j=j-gap;
        }
        gap=gap/2;  //减小增量
    }
}

void BubbleSort1(RecType R[],int n)
{
    int i,j,k,exchange;
    RecType tmp;
    for (i=0; i<n-1; i++)
    {
        exchange=0;
        for (j=n-1; j>i; j--)   //比较,找出最小关键字的记录
            if (R[j].key<R[j-1].key)
            {
                tmp=R[j];  //R[j]与R[j-1]进行交换,将最小关键字记录前移
                R[j]=R[j-1];
                R[j-1]=tmp;
                exchange=1;
            }

        printf("  i=%d :",i);
        for (k=0; k<n; k++)
            printf("%d ",R[k].key);
        printf("\n");

        if (exchange==0)    //中途结束算法
            return;
    }
}

void QuickSort(RecType R[],int s,int t) //对R[s]至R[t]的元素进行快速排序
{
    int i=s,j=t;
    RecType tmp;
    if (s<t)                //区间内至少存在两个元素的情况
    {
        tmp=R[s];           //用区间的第1个记录作为基准
        while (i!=j)        //从区间两端交替向中间扫描,直至i=j为止
        {
            while (j>i && R[j].key>=tmp.key)
                j--;        //从右向左扫描,找第1个小于tmp.key的R[j]
            R[i]=R[j];      //找到这样的R[j],R[i]"R[j]交换
            while (i<j && R[i].key<=tmp.key)
                i++;        //从左向右扫描,找第1个大于tmp.key的记录R[i]
            R[j]=R[i];      //找到这样的R[i],R[i]"R[j]交换
        }
        R[i]=tmp;
        QuickSort(R,s,i-1);     //对左区间递归排序
        QuickSort(R,i+1,t);     //对右区间递归排序
    }
}

//调整堆
void sift(RecType R[],int low,int high)
{
    int i=low,j=2*i;                        //R[j]是R[i]的左孩子
    RecType temp=R[i];
    while (j<=high)
    {
        if (j<high && R[j].key<R[j+1].key)  //若右孩子较大,把j指向右孩子
            j++;                                //变为2i+1
        if (temp.key<R[j].key)
        {
            R[i]=R[j];                          //将R[j]调整到双亲结点位置上
            i=j;                                //修改i和j值,以便继续向下筛选
            j=2*i;
        }
        else break;                             //筛选结束
    }
    R[i]=temp;                                  //被筛选结点的值放入最终位置
}

//堆排序
void HeapSort(RecType R[],int n)
{
    int i;
    RecType temp;
    for (i=n/2; i>=1; i--) //循环建立初始堆
        sift(R,i,n);
    for (i=n; i>=2; i--) //进行n-1次循环,完成推排序
    {
        temp=R[1];       //将第一个元素同当前区间内R[1]对换
        R[1]=R[i];
        R[i]=temp;
        sift(R,1,i-1);   //筛选R[1]结点,得到i-1个结点的堆
    }
}

void Merge(RecType R[],int low,int mid,int high)
{
    RecType *R1;
    int i=low,j=mid+1,k=0; //k是R1的下标,i、j分别为第1、2段的下标
    R1=(RecType *)malloc((high-low+1)*sizeof(RecType));  //动态分配空间
    while (i<=mid && j<=high)       //在第1段和第2段均未扫描完时循环
        if (R[i].key<=R[j].key)     //将第1段中的记录放入R1中
        {
            R1[k]=R[i];
            i++;
            k++;
        }
        else                            //将第2段中的记录放入R1中
        {
            R1[k]=R[j];
            j++;
            k++;
        }
    while (i<=mid)                      //将第1段余下部分复制到R1
    {
        R1[k]=R[i];
        i++;
        k++;
    }
    while (j<=high)                 //将第2段余下部分复制到R1
    {
        R1[k]=R[j];
        j++;
        k++;
    }
    for (k=0,i=low; i<=high; k++,i++) //将R1复制回R中
        R[i]=R1[k];
}

void MergePass(RecType R[],int length,int n)    //对整个数序进行一趟归并
{
    int i;
    for (i=0; i+2*length-1<n; i=i+2*length)     //归并length长的两相邻子表
        Merge(R,i,i+length-1,i+2*length-1);
    if (i+length-1<n)                       //余下两个子表,后者长度小于length
        Merge(R,i,i+length-1,n-1);          //归并这两个子表
}
void MergeSort(RecType R[],int n)           //自底向上的二路归并算法
{
    int length;
    for (length=1; length<n; length=2*length) //进行log2n趟归并
        MergePass(R,length,n);
}





