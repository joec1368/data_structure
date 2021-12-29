#include <stdio.h>
#include <time.h>
#include <stdlib.h>


struct leftist{
    struct leftist* left;
    struct leftist* right;
    int key;
    int data;
};

void SWAP(struct leftist **a , struct leftist **b, struct leftist *temp){
    temp = *a;
    *a = *b;
    *b = temp;
}

void minUnion(struct leftist* *a , struct leftist* *b){
    struct leftist* temp;
    if((*a)->data > (*b)->data) SWAP(a,b, temp);

    if(!(*a) ->right) (*a) -> right = *b;
    else minUnion(&(*a)->right ,b);

    if(!(*a)->left){
        (*a) -> left = (*a) ->right;
        (*a) -> right = NULL;
    }
    else if((*a) -> left ->key < (*a) ->right ->key) SWAP(&((*a)->left) ,&( (*a) ->right) , temp);
    (*a) ->key = (!(*a)->right) ? 1 : (*a) ->right->key + 1;
}
void minMeld(struct leftist* *a , struct leftist* *b){
    if(!*a) *a = *b;
    else if(*b) minUnion(a,b);
    *b = NULL;
}



int main() {
    int range;
    range = 5000;
    int point_range = 0;
    int ran_num[range];
    struct leftist *tree;
    struct leftist *temp;
    srand(time(NULL));
    for(int i = 0 ; i < range ; i++){

        ran_num[i] = rand()%10000+1;
    }
    tree = malloc(sizeof (struct leftist));
    tree->right = NULL;
    tree -> left = NULL;
    tree ->key = 1;
    tree ->data = ran_num[0];
    for(int i = 1 ; i < range ; i++){
        temp = malloc(sizeof (struct leftist));
        temp ->right = NULL;
        temp -> left = NULL;
         temp -> key = 1;
         temp -> data = ran_num[i];
        minMeld(&tree,&temp);
    }

    int ran_num_for_all[5000];
    for(int i = 0 ; i < 5000 ; i++){
        ran_num_for_all[i] = rand()%10000+1;
    }
    point_range = 0;
    int ran_decide[5000];
    for(int i = 0 ; i < 5000 ; i++){
        ran_decide[i] = rand()%2+1;
    }

    clock_t start,end;
    start = clock();
    for(int i = 0 ; i < 5000 ; i++){
        if(ran_decide[i] == 1){
            temp = malloc(sizeof (struct leftist));
            temp ->right = NULL;
            temp -> left = NULL;
            temp -> key = 1;
            temp -> data = ran_num_for_all[point_range++];
            minMeld(&tree,&temp);
        }
        else{
            temp = tree->right;
            tree = tree->left;
            minMeld(&tree,&temp);
        }
    }
    end = clock();
    double ans_first ;
    ans_first = end - start;
    ans_first = ans_first / CLOCKS_PER_SEC;


    int decide;
    int array[range];
    int last;
    array[0] = -2;
    last = 1;
    for(int i = 0 ; i < range ; i++){
        array[i] = -1;
    }
    int num_temp;
    for(int i = 0 ; i < range ; i++){
        array[last++] = ran_num[i];
        for(i = last-1  ; i > 0 ; ){
            if(array[i/2] != -1 && i/2 != 0) {
                if (array[i] < array[i / 2]) {
                    num_temp = array[i];
                    array[i] = array[i / 2];
                    array[i / 2] = num_temp;

                } else break;
            }
            if(array[i/2] == -1 && i/2 != 0){
                array[i / 2] = array[i];
            }
            i = i / 2;
        }
    }
    start = clock();
    for(int j = 0 ; j < 5000 ; j++){
        if(ran_decide[j] == 1) {
            int z = 2;
            array[1] = array[last-1];
            array[last-1] = -1;
            for( ; z+1 < last ; ){
                if(array[z] != -1 && array[z+1] != -1) {
                    if (array[z] > array[z + 1]) {
                        if(array[z/2]> array[z+1]) {
                             num_temp = array[z / 2];
                            array[z / 2] = array[z + 1];
                            array[z + 1] = num_temp;
                            z = (z + 1) * 2;
                        }
                        else {
                            z = (z + 1) * 2;
                        }

                    } else {
                        if(array[z/2]> array[z]) {
                             num_temp = array[z / 2];
                            array[z / 2] = array[z ];
                            array[z ] = num_temp;
                            z = z  * 2;
                        }
                        else {
                            z = z  * 2;
                        }

                    }

                }
                else{
                    if(array[z] == -1){
                        if(array[z+1] < array[z/2]) {
                             num_temp = array[z / 2];
                            array[z / 2] = array[z + 1];
                            array[z + 1] = num_temp;
                            z = (z + 1) * 2;
                        }
                    }
                    else{
                        if(array[z ] < array[z/2]) {
                             num_temp = array[z / 2];
                            array[z / 2] = array[z];
                            array[z] = num_temp;
                            z = z * 2;
                        }
                        else {
                            z = z*2;
                        }
                    }
                }
            }

            last--;
        }
        else{
            array[last++] = ran_num_for_all[j];
            for(int i = last-1  ; i > 0 ; ){
                if(array[i/2] != -1 && i/2 != 0) {
                    if (array[i] < array[i / 2]) {
                        num_temp = array[i];
                        array[i] = array[i / 2];
                        array[i / 2] = num_temp;

                    } else break;
                }
                if(array[i/2] == -1 && i/2 != 0){
                    array[i / 2] = array[i];
                }
                i = i / 2;
            }
        }
    }
    end = clock();
    double answer_two = end - start;
    answer_two = answer_two/CLOCKS_PER_SEC;






    printf("tree : %lf \n",ans_first);
    printf("heap : %lf \n",answer_two);
    return 0;
}
