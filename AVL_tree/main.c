#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode *treePointer;

struct treeNode{
    treePointer leftchild;
    treePointer rightchild;
    int bf;
    int data;
    int ht;
};
int height(treePointer parent)
{
    int lh , rh;
    if( parent == NULL ) return(0);
    if( parent -> leftchild == NULL ) lh=0;
    else lh = 1 + parent -> leftchild -> ht;
    if( parent -> rightchild == NULL) rh=0;
    else rh = 1 + parent -> rightchild -> ht;
    if(lh>rh) return(lh);
    else return(rh);
}

void RL(treePointer *parent , int *unbalanced){
    treePointer grandchild, child;
    child = (*parent) -> rightchild;
    grandchild = child->leftchild;
    child->leftchild = grandchild->rightchild;
    grandchild->rightchild = child;
    (*parent)->rightchild = grandchild->leftchild;
    grandchild->leftchild = *parent;
    *parent = grandchild;
}

void RR(treePointer *parent , int *unbalanced){
    treePointer grandchild, child;
    child = (*parent) -> rightchild;
    (*parent)->rightchild = child->leftchild;
    child->leftchild = *parent;
    (*parent)->bf = 0;
    (*parent) = child;
}

void LL(treePointer *parent , int *unbalanced){
    treePointer grandchild, child;
    child = (*parent) -> leftchild;
        (*parent) -> leftchild = child -> rightchild;
        child -> rightchild = *parent;
        (*parent) -> bf = 0;
        (*parent) = child;
}

void LR(treePointer *parent , int *unbalanced){
    treePointer grandchild, child;
    child = (*parent) -> leftchild;
    grandchild = child -> rightchild;
    child -> rightchild = grandchild ->leftchild;
    grandchild -> leftchild = child;
    (*parent) -> leftchild = grandchild -> rightchild;
    grandchild -> rightchild = *parent;
//    switch (grandchild -> bf) {
//        case 1: (*parent ) -> bf = -1; child ->bf = 0 ;break;
//        case 0 : (*parent) -> bf = 0 ; child -> bf = 0;break;
//        case -1 : (*parent) -> bf = 0 ; child -> bf = 1; break;
//    }
    *parent = grandchild;
}

void rightRotation(treePointer *parent , int *unbalanced){
    treePointer grandchild, child;
    child = (*parent) -> rightchild;
    if(child) {
        if (child->bf == -1) {//RR rotation
            RR(parent , unbalanced);
        } else { //RL rotation
            grandchild = child->leftchild;
            child->leftchild = grandchild->rightchild;
            grandchild->rightchild = child;
            (*parent)->rightchild = grandchild->leftchild;
            grandchild->leftchild = *parent;

            switch (grandchild->bf) {
                case -1:
                    (*parent)->bf = 1;
                    child->bf = 0;
                    break;
                case 0 :
                    (*parent)->bf = 0;
                    child->bf = 0;
                    break;
                case 1 :
                    (*parent)->bf = 0;
                    child->bf = -1;
                    break;
            }
            *parent = grandchild;
        }
        (*parent)->bf = 0;
        *unbalanced = 0;
    }
}

void leftRotation(treePointer *parent , int *unbalanced){
    treePointer grandchild, child;
    child = (*parent) -> leftchild;
    if(child -> bf == 1){//LL rotation
        (*parent) -> leftchild = child -> rightchild;
        child -> rightchild = *parent;
        (*parent) -> bf = 0;
        (*parent) = child;
    } else { //LR rotation
        grandchild = child -> rightchild;
        child -> rightchild = grandchild ->leftchild;
        grandchild -> leftchild = child;
        (*parent) -> leftchild = grandchild -> rightchild;
        grandchild -> rightchild = *parent;
        switch (grandchild -> bf) {
            case 1: (*parent ) -> bf = -1; child ->bf = 0 ;break;
            case 0 : (*parent) -> bf = 0 ; child -> bf = 0;break;
            case -1 : (*parent) -> bf = 0 ; child -> bf = 1; break;
        }
        *parent = grandchild;
    }
    (*parent) -> bf = 0;
    *unbalanced = 0;
}//



int BF(treePointer parent)
{
    int lh,rh;
    if( parent ==NULL)
        return(0);

    if( parent ->leftchild ==NULL)
        lh=0;
    else
        lh = 1 + parent -> leftchild -> ht;

    if(parent -> rightchild ==NULL)
        rh = 0 ;
    else
        rh = 1 + parent -> rightchild -> ht;

    return (lh-rh) ;
}

void inorder(treePointer parent) {
    int temp;
    if (parent != NULL) {
        inorder(parent->leftchild);
        parent->ht = height(parent);
        inorder(parent->rightchild);
    }
}

void inorder_bf(treePointer parent) {
    int temp;
    if (parent != NULL) {
        inorder_bf(parent->leftchild);
        parent->bf = BF(parent);
        inorder_bf(parent->rightchild);
    }
}

void inorder_three_bf(treePointer parent) {
    if (parent->leftchild) {
    if (parent->leftchild->leftchild)
        parent->leftchild->leftchild->bf = BF(parent->leftchild->leftchild);
    if (parent->leftchild->rightchild)
        parent->leftchild->rightchild->bf = BF(parent->leftchild->rightchild);
    parent->leftchild->bf = BF(parent->leftchild);
    }
    if(parent -> rightchild) {
        if (parent->rightchild->leftchild)
            parent->rightchild->leftchild->bf = BF(parent->rightchild->leftchild);
        if (parent->rightchild->rightchild)
            parent->rightchild->rightchild->bf = BF(parent->rightchild->rightchild);

        parent->rightchild->bf = BF(parent->rightchild);
    }
    parent -> bf = BF(parent);
}

void inorder_three_ht(treePointer parent){
    if(parent -> leftchild) {
        if (parent->leftchild->leftchild)
            parent->leftchild->leftchild->ht = height(parent->leftchild->leftchild);
        if (parent->leftchild->rightchild)
            parent->leftchild->rightchild->ht = height(parent->leftchild->rightchild);

        parent->leftchild->ht = height(parent->leftchild);
    }
    if(parent -> rightchild){
    if(parent -> rightchild -> leftchild)
        parent -> rightchild -> leftchild -> ht = height(parent -> rightchild -> leftchild);
    if(parent -> rightchild -> rightchild)
        parent -> rightchild -> rightchild -> ht = height(parent -> rightchild -> rightchild);

    parent -> rightchild -> ht = height(parent -> rightchild);
    }
    parent -> ht = height(parent);

}

treePointer delete(treePointer parent , int x){
    int *unbalanced;
    int temp_num = -1;
    unbalanced = &temp_num;
    treePointer temp;
    if(parent == NULL) return NULL;
    if(parent -> data < x) {
        parent->rightchild = delete(parent->rightchild, x);
    }
    else if( parent -> data > x){
        parent -> leftchild = delete(parent -> leftchild , x);
    }
    else {
        if(parent -> rightchild !=NULL)
        { //delete its inorder succesor
            temp = parent -> rightchild ;
            while(temp -> leftchild != NULL)
                temp = temp -> leftchild ;
            parent -> data = temp -> data;
            parent -> rightchild = delete( parent -> rightchild , temp -> data);
        }
        else
            return( parent -> leftchild );
    }

    if(parent -> leftchild)
    parent -> leftchild -> ht = height(parent->leftchild);
    if(parent -> rightchild)
    parent -> rightchild -> ht = height(parent -> rightchild );
    parent -> ht = height(parent);
    if(BF( parent )>=2 && BF(parent -> leftchild )==1){ LL(&parent,0); }
    else if(BF(parent) >= 2 && BF( parent -> leftchild ) == -1 ){   LR(&parent,0); }
    else if(BF(parent) >= 2 && BF( parent -> leftchild ) == 0){ LL(&parent,0); }
    else if(BF(parent) <= -2 && BF( parent -> rightchild ) == -1){ RR(&parent,0); }
    else if(BF(parent) <= -2 && BF( parent -> rightchild ) == 1 ){ RL(&parent,0); }
    else if(BF(parent) <= -2 && BF( parent -> rightchild ) == 0 ){ RR(&parent,0); }//change

    if(parent -> leftchild)
        parent -> leftchild -> ht = height(parent->leftchild);
    if(parent -> rightchild)
        parent -> rightchild -> ht = height(parent -> rightchild );
    parent -> ht = height(parent);
    parent -> bf = BF(parent);
    return(parent);
}


void avlInsert(treePointer *parent, int x ,int *unbalanced ){
    if(!*parent){
        *unbalanced = 1;
        *parent = malloc(sizeof (struct treeNode));
        (*parent) ->leftchild = NULL;
        (*parent) -> rightchild = NULL;
        (*parent) -> bf = 0;
        (*parent) -> data = x;
        (*parent) -> ht = 0;
    } else if(x < (*parent)->data){
        avlInsert(&(*parent) -> leftchild , x , unbalanced);
        if(BF(*parent) >= 2){
            if(x < (*parent) -> leftchild -> data)
                LL(parent , 0);
            else
                LR(parent , 0);
            inorder_three_ht(*parent);
            inorder_three_bf(*parent);
        }
    }else if(x > (*parent) -> data){
        avlInsert(&(*parent) -> rightchild , x, unbalanced);
        if( BF(*parent) <= -2)
            if(x > (*parent) -> rightchild ->data)
                RR(parent,0);
            else
                RL(parent,0);
        inorder_three_ht(*parent);
        inorder_three_bf(*parent);

    }else{
        *unbalanced = 0;
    }


    if((*parent) -> leftchild)
    (*parent) -> leftchild -> ht = height((*parent)->leftchild);
    if((*parent) -> rightchild)
    (*parent) -> rightchild -> ht = height((*parent) -> rightchild );
    (*parent) -> ht = height((*parent));
    (*parent) -> bf = BF(*parent);
    }



void search(treePointer parent , int x){
    if(parent == NULL){
        printf("Not found\n");
        return;
    }
    if(x == parent->data){
        printf("%d\n",parent -> bf);
    }else if(x > parent->data){
        search(parent -> rightchild , x);
    }
    else if(x < parent -> data) {
        search(parent->leftchild , x);
    }
    return;
}

void exist(treePointer parent , int x){
    if(parent == NULL){
        printf("Not exist\n");
        return;
    }
    if(x == parent->data){
        printf("exist\n");
    }else if(x > parent->data){
        exist(parent -> rightchild , x);
    }
    else if(x < parent -> data) {
        exist(parent->leftchild , x);
    }
    return;
}


int main() {
    treePointer parent;
    parent = NULL;
    int *unbalenced;
    int num_avl_save = 0;
    int choose = 1;
    unbalenced = &num_avl_save;
    while (1) {
        int temp;
        char decide[100];
        scanf("%s", &decide);
        switch (decide[0]) {
            case 's': //search
            if (choose == 1 ) {
                inorder(parent);
                inorder_bf(parent);
            }
                scanf("%d",&temp);
                search(parent,temp);
                break;
            case 'd' : //delete
            choose = 0;
                scanf("%d",&temp);
                parent = delete(parent,temp );
            //    inorder(parent);
            //    inorder_bf(parent);
                break;
            case 'i' ://insert
                choose = 0;
                scanf("%d",&temp);
                avlInsert(&parent , temp ,unbalenced);
            //    inorder(parent);
            //    inorder_bf(parent);
                break;
            case 'e':
                choose = 0;
                scanf("%d",&temp);
                exist(parent,temp);
                break;
            case 'q' : return 0;
        }
    }

}
