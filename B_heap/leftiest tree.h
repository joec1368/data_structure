//
// Created by 陳宥橋 on 2021/12/1.
//

#ifndef B_HEAP_LEFTIEST_TREE_H
#define B_HEAP_LEFTIEST_TREE_H



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










#endif //B_HEAP_LEFTIEST_TREE_H
