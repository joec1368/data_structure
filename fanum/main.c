#include <stdio.h>
int fanum(int num){
    if(num == -1) return 0;
    if(num == 0){
        return 1;
    }
    else if(num == 1){
        return 1;
    }
    return fanum(num - 1) + fanum(num - 2);
}
int iter ( int num){
    int now;
    int past1 = 1;
    int past2 = 0;
    if (num == 0) return 0;
    else if (num == 1) return 1;
    else{
        for(int i = 1 ; i <  num ; i++ ){
            now = past1 + past2;
            past2 = past1;
            past1 = now;
        }
        return now;

    }
}
int main() {
    int num;
    int times;
    char ask[100];
    scanf("%d",&times);
    while(times>0) {
        scanf("%s",&ask);
        switch(ask[0]){
            case 'r':
                scanf("%d", &num);
                int total = fanum(num - 1);
                printf("%d\n", total);
                break;
            case 'i':
                scanf("%d", &num);
                 total = iter(num);
                printf("%d\n", total);


        }

        times--;
    }
    return 0;

}
