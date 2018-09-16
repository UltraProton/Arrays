#include<stdio.h>

#define size 10

int arr[size]={9,7,11,19,7,5,4,0,-1,10};


void swap(int * a, int *b){
	int t=*a;
	*a=*b;
	*b=t;
}

//Partitioning the array into two halves
int partition(int *arr,int p,int r){
	int x,i,j;
	x=arr[r];
	i=p-1;
	
	for(j=p;j<r;j++){
		if(arr[j]<=x){
			i++;
			swap(&arr[i],&arr[j]);
		}
	}

	swap(&arr[i+1],&arr[r]);
	return i+1;
}

int KthMininmum(int *arr,int K ,int p,int r){
	int index=0;
	if((r+1 < K) || (K<0)){
		printf("%d Mininmum doesn't exist in the array",K);
		return;
	}

	index=partition(arr,p,r);

	if((index+1)==K)
		return arr[index];

	else if((index+1)>K)
		return KthMininmum(arr,K,0,index-1);
	else 
		return KthMininmum(arr+index+1,K-index-1,0,r-index-1);
}

int main(void){
	int K=0;
	printf("Enter K : ");
	scanf("%d",&K);
	printf("%dthMininmum : %d",K,KthMininmum(arr,K,0,9));
	return 0;
}
