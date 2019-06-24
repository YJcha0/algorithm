#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#define MaxSize 100000
typedef int KeyType;    //定义关键字类型
typedef char InfoType[10];
typedef struct          //记录类型
{
    KeyType key;        //关键字项
    InfoType data;      //其他数据项,类型为InfoType
} RecType;              //排序的记录类型定义

void InsertSort(RecType R[],int n); //对R[0..n-1]按递增有序进行直接插入排序
void ShellSort(RecType R[],int n);   //希尔排序算法
void BubbleSort1(RecType R[],int n);  //冒泡排序算法
void QuickSort(RecType R[],int s,int t); //对R[s]至R[t]的元素进行快速排序
void HeapSort(RecType R[],int n);   //堆排序算法
void MergePass(RecType R[],int length,int n);    //对整个数序进行一趟归并
void MergeSort(RecType R[],int n);           //自底向上的二路归并算法

#endif // SEARCH_H_INCLUDED
