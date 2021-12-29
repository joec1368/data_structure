#include <stdio.h>
#include <stdlib.h>


struct node{
    int data;
    int who;
    struct node* next;
    int myself;
};
struct node* route[10000005];
int answer[10000005];
int already[1000005];
struct node* stack[1000005];
int main() {
    int num_nodes;
    int num_root;
    scanf("%d",&num_nodes);

    for(int i = 0 ; i <= num_nodes ; i++){
        answer[i] = 0;
    }
    for(int i = 0 ; i<=num_nodes ; i++){
        route[i] = NULL;
    }
    for(int i = 1 ; i < num_nodes ; i++){
        int first, second , third;
        scanf("%d %d %d",&first , &second , &third);
        struct node* temp;
        temp = malloc(sizeof(struct node));
        temp->data = third;
        temp->who = second;
        temp -> next = route[first];
        temp->myself = first;
        route[first] = temp;
            temp = malloc(sizeof(struct node));
            temp->data = third;
            temp->who = first;
            temp->next = route[second];
            temp->myself = second;
            route[second] = temp;
    }
    scanf("%d",&num_root);
    long decide = num_root;
    long save = -1;
    stack[++save] = route[decide];


    int count = 0;
    for (int i = 0 ;  i <= num_nodes ; i++) already[i] = 0;
    already[decide] = 1;
    while(save >= 0){
        struct node* temp;
        temp = stack[save--];
        count--;
        if(temp) {

            for (; ; temp = temp->next) {
                if (already[temp->who] == 0) {
                    already[temp->myself] = 1;
                    answer[temp->who] = answer[temp->who] + temp->data + answer[temp->myself];
                    stack[++save] = route[temp->who];
                    count++;
                }
                if(temp->next == NULL) break;
            }
        }
        if(count <0 )break;
    }
    for(long i = 1 ; i<= num_nodes ; i++){
        printf("%ld %d\n",i,answer[i]);
    }
    return 0;
}





