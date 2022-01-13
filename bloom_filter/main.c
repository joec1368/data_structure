#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//different h
//fix u update, m bit , n records
//總共n筆資料 有u筆資料要先更新


const int num_buckets = 63;
 int num_hash_funciont ;
int buckets[num_buckets];
const int n = 743;
const int u = 13;
int check_save[n+3];



int mother , son;

void reset(){
    for(int i = 0 ; i <= num_buckets ; i++){
        buckets[i] = 0;

    }
    for(int i = 0 ; i < n+3 ; i++){
        check_save[i] = 0;
    }

    mother = 0;
    son = 0;
    return;
}

int h_function(int temp){
    return temp%num_buckets;
}

int insert(int temp){
    check_save[temp%n] = 1;
    int new = temp%n;
    for(int i = 1 ; i <= num_hash_funciont ; i++){
        buckets[ ((new*i) % num_buckets )] = 1;
    }
}
void search(int temp){
    mother++;
    temp = temp%n;
    for(int i = 1 ; i <= num_hash_funciont ; i++){
        if(buckets[ ((temp*i) % num_buckets) ] == 0){
            return;
        }
    }
    if(check_save[temp] == 0){//o check
        son++;
    }
    return;
}


int main() {
    num_hash_funciont = 0;
    float save_ans = 1;
    int who;
    srand((unsigned)time(NULL));
//    int random[u+10];
//    for(int i = 0 ; i < u +9; i++){
//        random[i] = rand();
//    }
    while(1) {
        num_hash_funciont++;
        reset();
        for (int i = 0; i < u; i++) {
            int x = rand();
            insert(x);
           // check_save[x % n + 1] = 1;
           // insert( random[i]);
        }
        for (int i = 1; i <= n; i++) {
            search(i );
        }
        float ans = (float) son / (float) mother;
        printf("%d %lf\n", num_hash_funciont,ans);
        if(ans < save_ans){
            who = num_hash_funciont;
            save_ans = ans;
        }
        if(num_hash_funciont == 20) break;

    }
    //printf("%d",who);
}
