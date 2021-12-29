#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "leftiest tree.h"

struct b_tree_nodes{
    int degree;
    int data;
    struct b_tree_nodes *child;
    struct b_tree_nodes *neighbor;
};
const int total = 5000;
const int range = 5000;
struct b_tree_nodes *store[15];
int stage;


struct b_tree_nodes* container[total*3];
int count = 0;

struct b_tree_nodes* insert(struct b_tree_nodes* min, int num ){

    if(min == NULL){
        min  = malloc(sizeof (struct b_tree_nodes));
        container[count++] = min ;
        min  ->data = num;
        min  -> degree = 0;
        min  -> child = NULL;
        min  -> neighbor = NULL;
    }
    else if(num < min->data){
        container[count++] = min ;
        container[0] = malloc(sizeof (struct b_tree_nodes));
        min = container[0];
        min  ->data = num;
        min -> degree = 0;
        min -> neighbor = NULL;
        min -> child = NULL;


    } else {
        container[count] = malloc(sizeof (struct b_tree_nodes));
        container[count]->data = num;
        container[count] -> degree = 0;
        container[count] -> child = NULL;
        container[count++] -> neighbor = NULL;
    }
    return min;
}
void arragnge(int start){
    if(start >=count ) return;
    for(;start + 1 < count ; start++){
        struct b_tree_nodes *temp = container[start];
        container[start] = container[start + 1];
        container[start + 1] = temp;
    }

    container[count--] = NULL;
}
struct b_tree_nodes *unionheap() {
    store[container[0]->degree] = container[0];
    for(int i = 1 ; i < count ; i++){
        first:
        if(store[container[i] -> degree] != NULL){
            if(container[i] -> data < store[container[i] -> degree]->data){
                if(container[i] -> child){
                    struct b_tree_nodes *temp = container[i] -> child;
                    container[i] -> child  = store[container[i]->degree];
                    container[i] -> child -> neighbor  = temp;

                }
                else{
                    container[i] -> child = store[container[i]->degree];
                }
                if(store[container[i]->degree+1]  == NULL){
                    store[container[i]->degree] = NULL;
                    container[i]->degree++;
                    store[container[i]->degree ] = container[i];
                }
                else{
                    store[container[i]->degree] = NULL;
                    container[i] -> degree++;
                    goto first;
                }
            }
            else{
                if(store[container[i]->degree]-> child){
                    struct b_tree_nodes *temp = store[container[i]->degree] -> child;
                    store[container[i]->degree] -> child  = container[i];
                    store[container[i]->degree] -> child  -> neighbor = temp;

                }
                else{
                    store[container[i]->degree] -> child = container[i];

                }
                if(store[container[i]->degree+1]  == NULL){
                    store[container[i]->degree+1] = store[container[i]->degree];
                    store[container[i]->degree+1]->degree++;
                    store[container[i]->degree] = NULL;
                }
                else{
                    container[i] = store[container[i]->degree];
                    container[i] -> degree++;
                    store[container[i]->degree-1] = NULL;
                    goto first;
                }
            }

        }
        else{
            store[container[i]->degree ] = container[i];
        }
    }
    count = 0;
    for(int i = 0 ; i < 15 ; i++){
        if(store[i] != NULL) {
            container[count++] = store[i];
            store[i] = NULL;
        }
    }
    //找最小
    for(int i = 1; i < count ; i++){
        if(container[i] -> data < container[0] -> data){
            struct b_tree_nodes * temp = container[0];
            container[0] = container[i];
            container[i] = temp;
        }
    }


    return container[0];
}

struct b_tree_nodes* delete(struct b_tree_nodes* min){
    if(!container[0]) return NULL;
    int temp;
    temp = container[0]->degree;


    container[0] = container[0]->child;

    min = container[0];
    if(container[0] == NULL){
        arragnge(0);
    }
    else {
        temp = container[0]->degree;

        int i = 0;
        for (struct b_tree_nodes *temp = container[0]->neighbor; temp;) {
            container[0] -> neighbor = NULL;
            struct b_tree_nodes *temp_delete;
            temp_delete = temp;
            temp = temp->neighbor;
            if(i == 0){
                container[count++] = temp_delete;

                i = 1;
            }
            if (temp) {
                container[count++] = temp;

                temp_delete->neighbor = NULL;

            } else {
                temp_delete->neighbor = NULL;

                break;
            }
        }
    }
    if(container[0] == NULL) return NULL;
    container[0]-> neighbor = NULL;
    return unionheap();
}

int const operation = 5000;

int main() {

    double time_array_first[15];
    double time_array_second[15];
    for(int i = 0 ; i < 11 ; i++){
        time_array_first[i] = 0;
        time_array_second[i] = 0;
    }
    int count = 0;
    while(count++ <=10) {
        int num_rand_count = 0;
        struct b_tree_nodes *min;

        int rand_list_pre[total + 10];
        int operation_list[5005];
        int rand_list_pro[5005];
        for (int i = 0; i <= total; i++) {
            container[i] = malloc(sizeof(struct b_tree_nodes));
            container[i]->data = 0;
            container[i]->child = NULL;
            container[i]->neighbor = NULL;
            container[i]->degree = 0;
        }
        min = container[0];
        for (int i = 0; i < total + 3; i++) {
            int j = 0;
            j = rand();
            rand_list_pre[i] = j;
        }
        for (int i = 0; i <= 5000; i++) {
            int j = 0;
            j = rand();
            rand_list_pro[i] = j;
        }
        for (int i = 0; i <= 5000; i++) {
            int j = 0;
            j = (rand() % 2);
            operation_list[i] = j;
        }
        for (int i = 0; i < total; i++) {
            min = insert(container[0], rand_list_pre[i]);
        }

        // min = delete(container[0]);
        clock_t start, end;
        start = clock();
        for (int i = 0; i < operation; i++) {
            if (operation_list[i] == 0) {
                min = insert(container[0], rand_list_pro[num_rand_count++]);
            } else {
                min = delete(container[0]);
            }
        }
        end = clock();
        double ans_first;
        ans_first = end - start;
        printf("heap : %lf \n", ans_first / 5000);
        time_array_first[count] = ans_first/5000;


        int point_range = 0;
        int ran_num[range];
        struct leftist *tree;
        struct leftist *temp;
        srand(time(NULL));
        tree = malloc(sizeof(struct leftist));
        tree->right = NULL;
        tree->left = NULL;
        tree->key = 1;
        tree->data = ran_num[0];
        for (int i = 1; i < range; i++) {
            temp = malloc(sizeof(struct leftist));
            temp->right = NULL;
            temp->left = NULL;
            temp->key = 1;
            temp->data = rand_list_pre[i];
            minMeld(&tree, &temp);
        }


        num_rand_count = 0;
        start = clock();
        for (int i = 0; i < 5000; i++) {
            if (operation_list[i] == 1) {
                temp = malloc(sizeof(struct leftist));
                temp->right = NULL;
                temp->left = NULL;
                temp->key = 1;
                temp->data = rand_list_pro[num_rand_count++];
                minMeld(&tree, &temp);
            } else {
                temp = tree->right;
                tree = tree->left;
                minMeld(&tree, &temp);
            }
        }
        end = clock();
        double ans_second;
        ans_second = end - start;

        printf("tree : %lf \n", ans_second / 5000);
        time_array_second[count] = ans_second/5000;
        printf("\n");
    }
    int total_1,total_2;
    total_1 = 0;
    total_2 = 0;
    for(int bb = 0 ; bb <10 ;bb++){
        total_1 = total_1 + time_array_first[bb];
        total_2 = total_2 + time_array_second[bb];
    }
    printf("average : heap : %lf\n",total_1/10);
    printf("aberage : tree : %lf\n",total_2/10);
    return 0;



}
