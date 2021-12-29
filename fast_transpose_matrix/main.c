#include <stdio.h>
typedef struct {
    int row;
    int col;
    int val;
} term;

int main() {
    int row , col ,val;
    scanf("%d %d %d", &row , &col , &val);
    term all[val+1];
    all[0].col = col;
    all[0].row = row;
    all[0].val = val;
    for(int i = 1 ; i < all[0].val+1 ; i++){
        scanf("%d %d %d", &row , &col , &val);
        all[i].col = col;
        all[i].row = row;
        all[i].val = val;
    }
    term ans[all[0].val + 1];

    int MAX_COL = all[0].col;
    int  startingPos[MAX_COL] ;
    for(int i = 0 ; i < MAX_COL ; i++){
        startingPos[i] = 0;
    }


    ans[0].col = all[0].row;
    ans[0].row = all[0].col;
    ans[0].val = all[0].val;
    startingPos[0] = 1;
    for(int i = 1 ; i <= all[0].col ; i++ ){
        int temp = 0;
        for(int j = 1 ; j <= all[0].val ; j++){
            if(all[j].col == i - 1) temp++;
        }
        startingPos[i] = startingPos[i-1] + temp;

    }
    for (int i = 1; i <= all[0].val; i++) {
        int j = startingPos[all[i].col]++;
        ans[j].row = all[i].col;
        ans[j].col = all[i].row;
        ans[j].val = all[i].val;
    }


    for(int i = 0 ; i < ans[0].val+1 ; i++){
        printf("%d %d %d\n",ans[i].row,ans[i].col,ans[i].val);
    }
    return 0;
}
