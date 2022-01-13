#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>


#define SWAP(x,y,t) ((t) = (x) , (x) = (y) , (y) = (t))

double long_heap_sort[6];
double long_quick_sort[6];
double long_insertion_sort[6];
double long_merge_sort[6];
double long_com_sort[6] ;


void print(int number){
    printf("%d : insert \n",number);
    printf("insertion : %lf \n",long_insertion_sort[1]);
    printf("quick : %lf \n",long_insertion_sort[2]);
    printf("heap : %lf \n",long_insertion_sort[3]);
    printf("merge : %lf \n",long_insertion_sort[4]);
    printf("com : %lf \n\n",long_insertion_sort[5]);

    printf("%d : quick \n",number);
    printf("insertion : %lf \n",long_quick_sort[1]);
    printf("quick : %lf \n",long_quick_sort[2]);
    printf("heap : %lf \n",long_quick_sort[3]);
    printf("merge : %lf \n",long_quick_sort[4]);
    printf("com : %lf \n\n",long_quick_sort[5]);

    printf("%d : heap \n",number);
    printf("insertion : %lf \n",long_heap_sort[1]);
    printf("quick : %lf \n",long_heap_sort[2]);
    printf("heap : %lf \n",long_heap_sort[3]);
    printf("merge : %lf \n",long_heap_sort[4]);
    printf("com : %lf \n\n",long_heap_sort[5]);

    printf("%d : merge \n",number);
    printf("insertion : %lf \n",long_merge_sort[1]);
    printf("quick : %lf \n",long_merge_sort[2]);
    printf("heap : %lf \n",long_merge_sort[3]);
    printf("merge : %lf \n",long_merge_sort[4]);
    printf("com : %lf \n\n",long_merge_sort[5]);

    printf("%d : com \n",number);
    printf("insertion : %lf \n",long_com_sort[1]);
    printf("quick : %lf \n",long_com_sort[2]);
    printf("heap : %lf \n",long_com_sort[3]);
    printf("merge : %lf \n",long_com_sort[4]);
    printf("com : %lf \n\n",long_com_sort[5]);
}

void permute(int a[], int n){//random sort produce
    //利用這個去找quicksort and heap sort的最久時間
    int i,j,temp;

    for(i = n ; i>= 2 ; i--){
        j = rand() % i + 1;
        SWAP(a[j],a[i],temp);
    }
}



void merge_worst(int a[], int n){
    int num_div = n / 2;
    int new_array[n+12];
    if(n%2  == 1)  num_div = (n+1)/2;
    while(num_div != 1){
        int start = 1;
        int last = num_div;
        while(1){
            int k = 1;
            there:
            ;
            int i = start;
            int j = 1;
            for(; i != k*last + last && k*last + j != n; i++){
                if(i % 2 == 1){
                    new_array[(k-1)*last + j] = a[i];
                }else{
                    new_array[(k)*last + j++] = a[i];
                }
            }
            if(i < start - 1 + k*last + last && i < n){
                for(; i < k*last + last && i < n ;i++){
                    new_array[(k-1)*last + j++] = a[i];
                }
            }
            if(k*last + 2 * last < n ) {
                start = k*last + last + 1;
                k = k + 2;
                goto there;
            }
            if(start + 2 * last <= n){
                if(j<=last){
                    for(;i<n ; i++){
                        new_array[(k-1)*last + j++] = a[i];
                    }
                }
                new_array[start + last] = new_array[start + 2 * last];
                new_array[start + 2 * last] = a[start + 2 * last];
                break;
            }else{
                if(j<=last){
                    for(;i<n ; i++){
                        new_array[(k-1)*last + j++] = a[i];
                    }
                }
              //  new_array[k*last] = new_array[n];
                new_array[n] = a[n];
                break;
            }

        }
        num_div = num_div/2;
        memcpy(a, new_array, sizeof(int) * (n+10));

    }
    for(int i = 1 ; i +2 <= n ; i = i+ 2){
        int temp;
        SWAP(a[i],a[i+1],temp);
    }

}

void reset(int number , int save_link[], int target[]){
    for(int i = 0 ; i < 5005 ; i++){
        save_link[i] = 0;
        target[i] = i;
    }
    for(int i = 5005-1 ; i  < 10004 ; i++){
        save_link[0] = 0;
    }



}

void merge(int initList[], int mergeList[], int i, int m, int n){
    /* 排序過的二串列 initList[i:m] 和 init[m+1 : n] 被合併過後，產生一個排序過的串列mergeList[i:m]
     *
     */
    int j , k , t;
    j = m + 1; // 第二個子串列的索引值
    k = i; // 合併串列的起始索引值

    while( i <= m && j <= n){
        if(initList[i] <= initList[j])
            mergeList[k++] = initList[i++];
        else
            mergeList[k++] = initList[j++];
    }
   // assert(i == m  || j == n );
    if( i > m){

        //mergeList[k:n] = initList[j:n];
        for (t = j ; t <= n ; t++){
            mergeList[t] = initList[t];
        }
    }
    else{
        //mergeList[k:n] = initList[i:m];
        for(t = i ; t <= m ; t++){
            mergeList[k + t - i] = initList[t];
        }
    }
}

void mergePass(int initList[], int mergeList[], int n , int s){//一回合的merge
    //執行一回合的合併排序，將initList[] 中兩兩相鄰的排序過的區段合併到mergeList[]
    //n 為串列中元素個素，s 代表每一個區段的大小
    int i,j;
    for( i = 1; i <= n - 2 * s + 1 ; i += 2*s){
        merge(initList,mergeList,i,i+s-1,i+2*s-1);
    }
    if( i + s - 1 < n){
        merge(initList,mergeList,i,i+s-1,n);
    }else{
        for( j = i ; j <= n ; j++){
            mergeList[j] = initList[j];
        }
    }
}

void mergeSort(int a[], int n, int number){//call mergeSort(target, last_number_position);
    //ust it to sort a[1:n]
    int s = 1; // 現在區段大小
    int extra[number*10];
    while(s < n){
        mergePass(a , extra , n , s);
        s*=2;
        mergePass(extra,a,n,s);
        s*=2;
    }
}

int listMerge(int a[], int link[], int start1, int start2){//link merge sort
    //兩個排序好的鏈分別從start1 及 start2 開始，將他們合併
    //將link[0] 當作一個暫時的標頭。回傳合併好的鏈的標頭
    int last1, last2, lastResult = 0;
    for(last1 = start1, last2 = start2 ; last1 && last2;){
        if(a[last1] <= a[last2]){
            link[lastResult] = last1;
            lastResult = last1;
            last1 = link[last1];
        }
        else{
            link[lastResult] = last2;
            lastResult = last2;
            last2 = link[last2];
        }
    }
    //將其於的紀錄附接到最後的鏈結
    if(last1 == 0) link[lastResult] = last2;
    else link[lastResult] = last1;
    //printf("%d ",link[0]);
    return link[0];

}

int rmergeSort(int a[], int link[], int left, int right){
    //a[left : right] 是要排序的陣列，link[i]所有i 是一開始為0
    //回傳排序好的鏈得第一個元素之索引值
    if(left >= right) return  left;
    int mid = (left + right ) / 2;
    return listMerge(a, link,
                     rmergeSort(a , link , left , mid),// sort left
                     rmergeSort(a , link , mid+1 , right) // sort right
                     );
}

void insert(int e, int a[] , int i){
    /* 將e插入到一個已經排序過串列 a[ 1 : i ] 中，並使得插入過後的串列 a[ 1 : i + 1] 仍然是依序排好
     * 此陣列a至少必須分配到大小為 i+2 個 int
     */
    a[0] = e;
    while(e < a[i]){
        a[i+1] = a[i];
        i--;
    }
    a[i+1] = e;
}

void insertionSort(int a[], int n){//call insertionSort(target, last_number_position);
    //將a[1:n]排序成遞增
    //因為結構簡單，當n比較小的時候(if n <= 30)，他幾乎是最快的排序法
    int j;
    for(j = 2; j <= n ; j++){
        int temp = a[j];
        insert(temp , a , j-1);
    }
}

void quicksort(int a[], int left , int right){//call quicksort(target, 1, last_number_position);
    /* 將 a [left : right] 遞增排序，我們隨意選出 a[left] 並將 a [left] a [left] 作為樞紐鍵值
     * 我們並假設 a[left] <= a[right + 1]
     */
    int pivot , i, j, temp;
    if(left<right){
        i = left;
        j = right+1;
        pivot = a[left];
        do{
            do i++; while(a[i] < pivot);
            do j--; while(a[j] > pivot);
            if(i < j) SWAP(a[i],a[j],temp);
        } while (i < j);
        SWAP(a[left],a[j],temp);
        quicksort(a , left , j-1);
        quicksort(a , j+1 , right);
    }
}

void adjust(int a[], int root, int n){
    //adgust a binary tree to struct a heap
    int child, rootkey,temp;
    temp = a[root];
    rootkey = a[root];
    child = 2*root; //left subtree
    while(child <= n){
        if((child<n) && (a[child] < a[child+1])){
            child++;
        }
        if(rootkey > a[child]) // compare root with the max subtree
            break;
        else{
            a[child/2] = a[child];//move to parent node
            child*=2;
        }
    }
    a[child/2] = temp;
}

void heapsort_write(int a[],int n){//call heapsort_write(target,last_number_position);
    //sort on a[1:n]
    int j , i ,temp;
    for(i = n/2 ; i>0 ; i--){
        adjust(a,i,n);
    }
    for(i = n-1 ; i>0 ; i--){
        SWAP(a[1],a[i+1],temp);
        adjust(a,1,i);
    }
}

void compare(int want, double first, double second, double third, double fourth,double fifth){
    switch (want) {
        case 1:
            if(first > long_insertion_sort[1]){
                long_insertion_sort[1] = first;
                long_insertion_sort[2] = second;
                long_insertion_sort[3] = third;
                long_insertion_sort[4] = fourth;
                long_insertion_sort[5] = fifth;
            } else return;
            break;
        case 2:
            if(second > long_quick_sort[2]){
                long_quick_sort[1] = first;
                long_quick_sort[2] = second;
                long_quick_sort[3] = third;
                long_quick_sort[4] = fourth;
                long_quick_sort[5] = fifth;
            } else return;
            break;
        case 3:
            if(third > long_heap_sort[3]){
                long_heap_sort[1] = first;
                long_heap_sort[2] = second;
                long_heap_sort[3] = third;
                long_heap_sort[4] = fourth;
                long_heap_sort[5] = fifth;
            } else return;
            break;
        case 4:
            if(fourth > long_merge_sort[4]){
                long_merge_sort[1] = first;
                long_merge_sort[2] = second;
                long_merge_sort[3] = third;
                long_merge_sort[4] = fourth;
                long_merge_sort[5] = fifth;
            } else return;
            break;
        case 5:
            if(fifth > long_com_sort[5]) {
                long_com_sort[1] = first;
                long_com_sort[2] = second;
                long_com_sort[3] = third;
                long_com_sort[4] = fourth;
                long_com_sort[5] = fifth;
            }else return;
            break;
    }
    //first insertion  second quick sort third heap fourth merge
}

void insertionSort_com(int a[], int n , int start) {//call insertionSort(target, last_number_position);
    //將a[1:n]排序成遞增
    //因為結構簡單，當n比較小的時候(if n <= 30)，他幾乎是最快的排序法
    int j;
    for (j = start + 1; j <= n; j++) {
        int temp = a[j];
        insert(temp, a, j - 1);
    }
}


void quicksort_com(int a[], int left , int right){//call quicksort(target, 1, last_number_position);
    /* 將 a [left : right] 遞增排序，我們隨意選出 a[left] 並將 a [left] a [left] 作為樞紐鍵值
     * 我們並假設 a[left] <= a[right + 1]
     */
    int pivot , i, j, temp;
    if(right - left <= 30){
        insertionSort_com(a,right,left);
    }
    else if(left<right){
        i = left;
        j = right+1;
        pivot = a[left];
        do{
            do i++; while(a[i] < pivot);
            do j--; while(a[j] > pivot);
            if(i < j) SWAP(a[i],a[j],temp);
        } while (i < j);
        SWAP(a[left],a[j],temp);
        quicksort_com(a , left , j-1);
        quicksort_com(a , j+1 , right);
    }
}


void comopsite(int a[],int n){
    if(n <= 30) insertionSort(a,n);
    else quicksort_com(a,1,n);
}

void count_time(int a[], int n,int number) {
    int new[number];
//    for(int i = 1 ; i <= n; i++){
//        new[i] = a[i];
//    }
    clock_t start, end;
    double ans_ins = 0;
    int temp = 10;
    while (temp-- > 0) {
        memcpy(new, a, sizeof(int) * n);
        start = clock();
        insertionSort(new, n);
        end = clock();
        ans_ins = (double) end - (double) start + ans_ins;
        //printf("insertion sort %lf\n",ans_ins);
    }

    ans_ins = ans_ins / 10;
  //  printf("insertion sort => %lf \n",ans_ins);

    double ans_qui = 0;
    temp = 10;
    while (temp-- > 0) {
        memcpy(new, a, sizeof(int) * n);
    start = clock();
    quicksort(new, 1, n);
    end = clock();
    ans_qui = (double) end - (double) start + ans_qui;
    //printf("quick sort %lf\n",ans_qui);
    }

    ans_qui = ans_qui/10;
   // printf("quick sort => %lf \n",ans_qui);

    double ans_heap = 0;
    temp = 20;
    while(temp-- >0) {
        memcpy(new, a, sizeof(int) * n);
        start = clock();
        heapsort_write(new, n);
        end = clock();
        ans_heap = (double) end - (double) start + ans_heap;
    }
   // printf("heap sort %lf\n",ans_heap);
    ans_heap = ans_heap/20;


    temp = 25;
    double ans_merge = 0;
    while(temp-- >0) {
        memcpy(new, a, sizeof(int) * n);
        start = clock();
        mergeSort(new, n, number);
        end = clock();
        ans_merge = (double) end - (double) start + ans_merge;
    }
  //  printf("merge sort %lf\n\n",ans_merge);
    ans_merge = ans_merge/25;
   // printf("merge sort => %lf \n",ans_merge);
    //printf("heap sort => %lf \n",ans_heap);

    double ans_com = 0;
    temp = 20;
    while (temp-- > 0) {
        memcpy(new, a, sizeof(int) * n);
        start = clock();
        comopsite(new,n);
        end = clock();
        ans_com = (double) end - (double) start + ans_com;
    }
    ans_com = ans_com/20;
    //printf("composite sort => %lf \n",ans_com);

    compare(1,ans_ins,ans_qui,ans_heap,ans_merge,ans_com);
    compare(2,ans_ins,ans_qui,ans_heap,ans_merge,ans_com);
    compare(3,ans_ins,ans_qui,ans_heap,ans_merge,ans_com);
    compare(4,ans_ins,ans_qui,ans_heap,ans_merge,ans_com);
    compare(5,ans_ins,ans_qui,ans_heap,ans_merge,ans_com);
}

void insertion_worst_case(int a[],int number){
    for(int i = number , j = 1; i > 0 ; i-- , j++){
        a[j] = i;
    }
}

int main() {
    int count = 0;
    int number;
    /*while (count++ <= 4) {//測時間：
        for (int i = 0; i < 6; i++) {
            long_heap_sort[i] = 0;
            long_merge_sort[i] = 0;
            long_quick_sort[i] = 0;
            long_insertion_sort[i] = 0;
            long_com_sort[i] = 0;
        }
        if (count == 1 || count == 2) number = 500 * count;
        else if (count == 5) number = 2000;
        else number = 500 * count * 2;
        //500 1000 2000 3000 4000 5000
        int save_link[10005];
        int i = 500;
        int target[10005];
        while (i--) {
            reset(number, save_link, target);
            permute(target, number);
            count_time(target, number, number);
            reset(number, save_link, target);
            insertion_worst_case(target, number);
            count_time(target, number, number);
            reset(number, save_link, target);
            merge_worst(target, number);
            count_time(target, number, number);
        }
        print(number);
    }*/
    int n = 1;
    while (n <= 10000 ){//測composite function
        for (int i = 0; i < 6; i++) {
            long_heap_sort[i] = 0;
            long_merge_sort[i] = 0;
            long_quick_sort[i] = 0;
            long_insertion_sort[i] = 0;
            long_com_sort[i] = 0;
        }
         number = n;
         n += 25;
        int save_link[10005];
        int i = 100;
        int target[10005];
        reset(number, save_link, target);
        permute(target, number);
        count_time(target, number, number);
        printf("%d :  \n",number);
        printf("insertion : %lf \n",long_insertion_sort[1]);
        printf("quick : %lf \n",long_insertion_sort[2]);
        printf("heap : %lf \n",long_insertion_sort[3]);
        printf("merge : %lf \n",long_insertion_sort[4]);
        printf("com : %lf \n\n",long_insertion_sort[5]);

    }

        return 0;
}
