#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
    int num;
    struct node* par;
};
int main() {
    int round;
    scanf("%d",&round);
    while(--round >= 0){
        int number,num_case;

        scanf("%d %d",&number , &num_case);
        struct node* ans[number+1] ;
        for(int i = 0 ; i <= number  ; i++){
            ans[i] = malloc(sizeof (struct node));
            ans[i]->data = 1;
            ans[i]->next = NULL;
            ans[i]->par = NULL;
            ans[i]->num = i;
        }
        struct node* temp_second;

        while(--num_case >= 0){
            int first,second;
            char temp[10];
            scanf("%s",&temp);
            switch(temp[0]){
                case'u':
                    scanf("%d %d",&first,&second);
                    struct node* temp;
                    temp = ans[first];

                    temp_second = ans[second];

                    for(;temp -> par;temp = temp->par){

                    }
                    for(;temp_second -> par;temp_second = temp_second->par){

                    }
                    if(temp->num != temp_second->num ) {
                        if (temp->data >= temp_second->data) {
                            temp_second->par = temp;
                            temp->next = temp_second;

                        } else {
                            temp->par = temp_second;
                            temp_second->next = temp;

                        }
                        if(temp->data == temp_second->data){
                            temp->data++;
                        }
                    }
                    break;
                case'f':
                    scanf("%d",&first);
                    struct node* temp_first;
                    temp_first = ans[first];
                    for(;temp_first -> par ;temp_first = temp_first->par){

                    }
                    printf("%d\n",temp_first->num);
                    break;
                case's':
                    scanf("%d",&first);
                    scanf("%d",&second);

                    temp = ans[first];
                    temp_second = ans[second];
                    for(;temp -> par;temp = temp->par){

                    }
                    for(;temp_second -> par;temp_second = temp_second->par){

                    }
                    if(temp->num == temp_second->num){
                        printf("true\n");
                    }
                    else printf("false\n");
                    break;
            }
        }

    }
    return 0;
}
