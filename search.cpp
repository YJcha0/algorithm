#include <stdio.h>
#include <malloc.h>
#include "search.h"
void InsertSort(RecType R[],int n) //��R[0..n-1]�������������ֱ�Ӳ�������
{
    int i,j;
    RecType tmp;
    for (i=1; i<n; i++)
    {
        tmp=R[i];
        j=i-1;            //����������������R[0..i-1]����R[i]�Ĳ���λ��
        while (j>=0 && tmp.key<R[j].key)
        {
            R[j+1]=R[j]; //���ؼ��ִ���R[i].key�ļ�¼����
            j--;
        }
        R[j+1]=tmp;      //��j+1������R[i]
    }
}

void ShellSort(RecType R[],int n)   //ϣ�������㷨
{
    int i,j,gap;
    RecType tmp;
    gap=n/2;                //�����ó�ֵ
    while (gap>0)
    {
        for (i=gap; i<n; i++) //���������gapλ�õ�����Ԫ�����������
        {
            tmp=R[i];
            j=i-gap;
            while (j>=0 && tmp.key<R[j].key)//�����gapλ�õ�Ԫ�����������
            {
                R[j+gap]=R[j];
                j=j-gap;
            }
            R[j+gap]=tmp;
            j=j-gap;
        }
        gap=gap/2;  //��С����
    }
}

void BubbleSort1(RecType R[],int n)
{
    int i,j,k,exchange;
    RecType tmp;
    for (i=0; i<n-1; i++)
    {
        exchange=0;
        for (j=n-1; j>i; j--)   //�Ƚ�,�ҳ���С�ؼ��ֵļ�¼
            if (R[j].key<R[j-1].key)
            {
                tmp=R[j];  //R[j]��R[j-1]���н���,����С�ؼ��ּ�¼ǰ��
                R[j]=R[j-1];
                R[j-1]=tmp;
                exchange=1;
            }

        printf("  i=%d :",i);
        for (k=0; k<n; k++)
            printf("%d ",R[k].key);
        printf("\n");

        if (exchange==0)    //��;�����㷨
            return;
    }
}

void QuickSort(RecType R[],int s,int t) //��R[s]��R[t]��Ԫ�ؽ��п�������
{
    int i=s,j=t;
    RecType tmp;
    if (s<t)                //���������ٴ�������Ԫ�ص����
    {
        tmp=R[s];           //������ĵ�1����¼��Ϊ��׼
        while (i!=j)        //���������˽������м�ɨ��,ֱ��i=jΪֹ
        {
            while (j>i && R[j].key>=tmp.key)
                j--;        //��������ɨ��,�ҵ�1��С��tmp.key��R[j]
            R[i]=R[j];      //�ҵ�������R[j],R[i]"R[j]����
            while (i<j && R[i].key<=tmp.key)
                i++;        //��������ɨ��,�ҵ�1������tmp.key�ļ�¼R[i]
            R[j]=R[i];      //�ҵ�������R[i],R[i]"R[j]����
        }
        R[i]=tmp;
        QuickSort(R,s,i-1);     //��������ݹ�����
        QuickSort(R,i+1,t);     //��������ݹ�����
    }
}

//������
void sift(RecType R[],int low,int high)
{
    int i=low,j=2*i;                        //R[j]��R[i]������
    RecType temp=R[i];
    while (j<=high)
    {
        if (j<high && R[j].key<R[j+1].key)  //���Һ��ӽϴ�,��jָ���Һ���
            j++;                                //��Ϊ2i+1
        if (temp.key<R[j].key)
        {
            R[i]=R[j];                          //��R[j]������˫�׽��λ����
            i=j;                                //�޸�i��jֵ,�Ա��������ɸѡ
            j=2*i;
        }
        else break;                             //ɸѡ����
    }
    R[i]=temp;                                  //��ɸѡ����ֵ��������λ��
}

//������
void HeapSort(RecType R[],int n)
{
    int i;
    RecType temp;
    for (i=n/2; i>=1; i--) //ѭ��������ʼ��
        sift(R,i,n);
    for (i=n; i>=2; i--) //����n-1��ѭ��,���������
    {
        temp=R[1];       //����һ��Ԫ��ͬ��ǰ������R[1]�Ի�
        R[1]=R[i];
        R[i]=temp;
        sift(R,1,i-1);   //ɸѡR[1]���,�õ�i-1�����Ķ�
    }
}

void Merge(RecType R[],int low,int mid,int high)
{
    RecType *R1;
    int i=low,j=mid+1,k=0; //k��R1���±�,i��j�ֱ�Ϊ��1��2�ε��±�
    R1=(RecType *)malloc((high-low+1)*sizeof(RecType));  //��̬����ռ�
    while (i<=mid && j<=high)       //�ڵ�1�κ͵�2�ξ�δɨ����ʱѭ��
        if (R[i].key<=R[j].key)     //����1���еļ�¼����R1��
        {
            R1[k]=R[i];
            i++;
            k++;
        }
        else                            //����2���еļ�¼����R1��
        {
            R1[k]=R[j];
            j++;
            k++;
        }
    while (i<=mid)                      //����1�����²��ָ��Ƶ�R1
    {
        R1[k]=R[i];
        i++;
        k++;
    }
    while (j<=high)                 //����2�����²��ָ��Ƶ�R1
    {
        R1[k]=R[j];
        j++;
        k++;
    }
    for (k=0,i=low; i<=high; k++,i++) //��R1���ƻ�R��
        R[i]=R1[k];
}

void MergePass(RecType R[],int length,int n)    //�������������һ�˹鲢
{
    int i;
    for (i=0; i+2*length-1<n; i=i+2*length)     //�鲢length�����������ӱ�
        Merge(R,i,i+length-1,i+2*length-1);
    if (i+length-1<n)                       //���������ӱ�,���߳���С��length
        Merge(R,i,i+length-1,n-1);          //�鲢�������ӱ�
}
void MergeSort(RecType R[],int n)           //�Ե����ϵĶ�·�鲢�㷨
{
    int length;
    for (length=1; length<n; length=2*length) //����log2n�˹鲢
        MergePass(R,length,n);
}





