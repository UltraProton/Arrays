#include<stdio.h>
#include<limits.h>
#include<time.h>
#include<stdlib.h>

#define n 10000


typedef struct  item
{
    long long max_sum;
    long long l_index;
    long long r_index;
}Item;


long long max3(long long a, long long b, long long c);
long long max2(long long a, long long b);
Item * max_crossing_subarray_sum(long long arr[],long long low, long long mid, long long high);
Item * max_subarray_sum(long long *, long long, long long);
long long max_subarray_sum_DP(long long arr[],long long low, long long high);
Item * max_subarray_sum_DP1(long long arr[],long long low, long long high);



int main(void){

clock_t start,end;
long long arr[n];
//long long *arr=(long long *)(malloc(sizeof(long long)*n));

long long i=0;
long long number=0;

FILE *infile= fopen("max_subarray_input4.txt","r");

 while (i<n){
     fscanf(infile,"%lld",&arr[i]);
       i++;
 }

i=0;

printf("Array content:\n");

while(i<n){
    printf("%lld ",arr[i]);
    i++;
}

printf("\n\n\n\n");

start=clock();

Item * final_max_sum1=malloc(sizeof(Item));

final_max_sum1=max_subarray_sum(arr,0,n-1);
    printf("Divide and Conquer ans :%lld\n",final_max_sum1->max_sum);
    printf("Left index: %lld\nRight index: %lld\n",final_max_sum1->l_index,final_max_sum1->r_index);

end=clock();

printf("CPU Time used in Divide and Conquer:%f\n\n\n",((double)(end-start)/CLOCKS_PER_SEC));

start=clock();

Item *final_max_sum2= (Item *)malloc(sizeof(Item));
final_max_sum2=max_subarray_sum_DP1(arr,0,n-1);

    printf("DP ans: %lld\n",final_max_sum2->max_sum);
    printf("Left index: %lld\nRight index: %lld\n",final_max_sum2->l_index,final_max_sum2->r_index);

end=clock();

printf("CPU Time used in Dynamic Programming:%f\n\n",((double)(end-start)/CLOCKS_PER_SEC));

    return 0;
}


long long max2(long long a, long long b){
    return (a)>(b)?(a):(b);
}

long long max3(long long a, long long b, long long c){
    if(a>b && a >c)
      return a;

    else if(b>a && b>c)
      return b;

    else
    return c;
}

// max crossing subarray
Item * max_crossing_subarray_sum(long long arr[],long long low, long long mid, long long high){
    long long left_sum=LONG_MIN;
    long long right_sum=LONG_MIN;
    long long sum=0;
    long long left_index=-100;
    long long right_index=-100;

    long long i=mid;

    Item *value= (Item*)malloc(sizeof(Item));

//search for max sum value in the left
    while(i>=0){
        sum+=arr[i];
        if(sum>left_sum){
            left_sum=sum;
            left_index=i;
        }

        i--;
    }

    sum=0;
    i=mid+1;

//search for max sum value in the right
    while(i<=high){
        sum+=arr[i];
        if(sum>right_sum){
           right_sum=sum;
           right_index=i;
        }

      i++;
    }

    value->max_sum=left_sum+right_sum;
    value->l_index=left_index;
    value->r_index=right_index;

    return value;
}


//max subarray using divide and conquer
Item * max_subarray_sum(long long arr[],long long low ,long long high){
    long long mid= low +(high-low)/2;
    long long max_sum_value=0;
    Item *final_item=(Item *)malloc(sizeof(Item));

    if(low==high){
        Item *value=(Item *)malloc(sizeof(Item));
        value->l_index=low;
        value->r_index=low;
        value->max_sum=arr[low];

        return value;
    }

    else{
        //max subarray sum in the left part of the array
        Item *left_arr= max_subarray_sum(arr,low,mid);
        //max subarray sum at the right part of the array
        Item *right_arr= max_subarray_sum(arr,mid+1,high);
        //max subarray crossing the array
        Item *cross_arr= max_crossing_subarray_sum(arr,low,mid,high);

        //return the max of three

        if(left_arr->max_sum > right_arr->max_sum && left_arr-> max_sum > cross_arr->max_sum){
            final_item->max_sum=left_arr->max_sum;
            final_item->l_index=left_arr->l_index;
            final_item->r_index=left_arr->r_index;

        }


        else if(right_arr->max_sum > left_arr->max_sum && right_arr-> max_sum > cross_arr->max_sum){
            final_item->max_sum=right_arr->max_sum;
            final_item->l_index=right_arr->l_index;
            final_item->r_index=right_arr->r_index;
        }

        else{
            final_item->max_sum=cross_arr->max_sum;
            final_item->l_index= cross_arr->l_index;
            final_item->r_index=cross_arr->r_index;
        }
    }

    return final_item;

}


// Dynamic programming solution

long long max_subarray_sum_DP(long long arr[],long long low, long long high){
    long long max_ending_here=arr[0];
    long long max_so_far=arr[0];

    long long i=1;

    while(i<=high){
        max_ending_here=max2(max_ending_here+arr[i],arr[i]);
        max_so_far=max2(max_ending_here,max_so_far);

        i++;
    }

    return max_so_far;
}


Item * max_subarray_sum_DP1(long long arr[],long long low, long long high){
    long long max_ending_here=arr[0];
    long long max_so_far=arr[0];

    long long i=1;
    long long start=0,end=0,s=0;

    Item *value=(Item *)malloc(sizeof(Item));


    while(i<=high){
        max_ending_here+=arr[i];

        if(max_ending_here > max_so_far){
           max_so_far=max_ending_here;
           start=s;
           end=i;
        }

        if(max_ending_here < 0){
            max_ending_here=0;
            s=i+1;
        }

        i++;
    }

    value->l_index=start;
    value->r_index=end;
    value->max_sum=max_so_far;

    return value;

}

