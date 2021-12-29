#include <stdio.h>
int moves = 0;
void tower(int num, char A , char B , char C){
    if(num == 1) {
        printf("%d %c %c\n",num,A,C);
        moves++;
        return ;
    }
    else {
        tower(num - 1, A, C, B);
        printf("%d %c %c\n",num,A,C);
        tower(num-1,B,A,C);
    }

}
int main() {
    int num;

    scanf("%d",&num);
    tower(num,'1','2','3');
    return 0;
}
