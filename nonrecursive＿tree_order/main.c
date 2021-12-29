#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node* left;
    struct node* right;
};
void Inorder(struct node *current){
    if (current) {                          // if current != NULL
        Inorder(current->left);
        if(current->data != -1)
        printf("%d ",current->data); // L
        Inorder(current->right);      // R
    }
}
int buildtree(struct node** tree,int num){
    if(*tree){
        if((*tree)->data == -1) return 0;
        else {
            if (buildtree(&(*tree)->left, num) == 1)return 1;
            else if(buildtree(&(*tree)->right,num) == 1) return 1;
            else return 0;
        }
    }
    else{
        *tree = malloc(sizeof(struct node));
        (*tree) ->data = num;
        (*tree) -> left = NULL;
        (*tree) -> right = NULL;
        return 1;
    }
}
int main() {
    int num;
    struct node *root ;
    int temp;
    root = NULL;
    scanf("%d",&num);
    for(;num>0 ; num--){
        scanf("%d",&temp);
        buildtree(&root,temp);
    }
  //  Inorder(root);
    printf("\n");
    struct node* stack[100];
    int count = 0;
    struct node *current ;
    current = root;
//    while(count != -1){
//        while(1){
//            if(current == NULL || current ->data == -1) break;
//            stack[count++] = current;
//            if(current->left == NULL || current ->data == -1) break;
//            current = current ->left;
//
//
//        }
//        if(--count != -1){
//            current = stack[count];
//            printf("%d ",current->data);
//            current = current ->right;
//        }
//
//    }
    stack[count++] = current;
    while(count != -1){
            current = stack[--count];
            if(current == NULL) break;
            if(current ->data != -1)
            printf("%d ",current->data );
            if(current -> right != NULL && current ->right -> data != -1)
            stack[count++] = current->right;
            if(current -> left != NULL && current ->left -> data != -1)
            stack[count++] = current ->left;
    }
    printf("\b\n");


    current = root;

    int stage = 1;
    struct node* stack2[100];
    while(count != -1 || stage == 1){
        while(current) {
            if (current->right) {
                stack2[++count] = current->right;
            }
            stack2[++count] = current;
            current = current->left;
        }
            current = stack2[count--];
            if (current->right != NULL && stack2[ count ] == current->right) {
                if( stack2[ count ] == current->right && current -> right != -1 ) {
                    stack2[count] = current;
                    current = current->right;
                }


            } else {
                if(current->data != -1)
                printf("%d ", current->data);
                current = NULL;
            }
            stage = 0;
    }

    return 0;
}
