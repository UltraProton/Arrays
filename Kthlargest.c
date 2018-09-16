#include<stdio.h>

#define size 10

int arr[size]={11,12,13,14,15,10,9,65,4,3,2,1};

void swap(int *a ,int *b){
    int t=*a;
    *a=*b;
    *b=t;
}

int Partition(int *arr, int p, int r ){
    int x,i,j;
    x=arr[p];
    i=p;

    for(j=i+1;j<=r;j++){
        if(arr[j]<=x){
            i=i+1;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[p],&arr[i]);
    return i;
}

int Kthlargest(int *arr,int K, int p, int r){
    int index=0;
    index=Partition(arr,p,r);

    if((index+1)==K)
        return arr[index];

    else if(index+1 > K){
        return Kthlargest(arr,K,0,index-1);
    }
    else{
        return Kthlargest(arr+index+1,K-index-1,0,r-index-1);
    }
}

int main(void){
    int i=0;
    printf("%d\n",Kthlargest(arr,12,0,11));
    return 0;
}


