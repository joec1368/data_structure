#include <stdio.h>
#include <stdlib.h>

struct node{
    int myself;
    int already;
};
int main() {
    int big,entry,number;
    scanf("%d",&number);
    while(--number >= 0) {
        int answer[200];
        for(int i = 0 ; i < 200 ; i++){
            answer[i] = 0;
        }
        scanf("%d %d", &big, &entry);
        int array[big][big];
        int print_answer[100];
        int num_ans = 0;
        int point = 0;
        int temp = 0;
        for(int i = 0 ; i < big ; i++){
            for(int j = 0 ; j < big ; j++){
                scanf("%d",&array[i][j]);
            }
        }
        struct node* sure[200];
        sure[point] = malloc(sizeof(struct node));
        sure[point]->myself = entry;
        sure[point]->already = -1;
        print_answer[num_ans++] = entry;
        answer[entry] = 1;
        while(point >= 0){



            int my = sure[temp]->myself ;
            int next = sure[temp]->already + 1;
            while(next < big) {
                if (array[my][next] != 0 && answer[next] != 1) {
                    sure[++point] = malloc(sizeof(struct node));
                    sure[point]->myself = next;
                    sure[point]->already = -1;
                    answer[next] = 1;
                    print_answer[num_ans++] = next;
                }
                else next++;
            }

            if(temp == point) break;
            temp ++;

        }
        for(int i = 0 ; i < num_ans ; i++){
            printf("%d",print_answer[i]);
            if(i + 1 != num_ans) printf(" ");
        }
        if(number>= 0)
            printf("\n");

    }


    return 0;
}
