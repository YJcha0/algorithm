#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#define MaxSize 100000
typedef int KeyType;    //����ؼ�������
typedef char InfoType[10];
typedef struct          //��¼����
{
    KeyType key;        //�ؼ�����
    InfoType data;      //����������,����ΪInfoType
} RecType;              //����ļ�¼���Ͷ���

void InsertSort(RecType R[],int n); //��R[0..n-1]�������������ֱ�Ӳ�������
void ShellSort(RecType R[],int n);   //ϣ�������㷨
void BubbleSort1(RecType R[],int n);  //ð�������㷨
void QuickSort(RecType R[],int s,int t); //��R[s]��R[t]��Ԫ�ؽ��п�������
void HeapSort(RecType R[],int n);   //�������㷨
void MergePass(RecType R[],int length,int n);    //�������������һ�˹鲢
void MergeSort(RecType R[],int n);           //�Ե����ϵĶ�·�鲢�㷨

#endif // SEARCH_H_INCLUDED
