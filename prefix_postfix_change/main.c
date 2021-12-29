#include <stdio.h>
#include <stdlib.h>


struct node{
    char num;
    struct node *left;
    struct node *right;
}node;


int builttree(char c, struct node** tree) {
    if( *tree) {
        if((*tree) -> num - 64 >= 0 && (*tree) -> num != 94)
            return 0;
        else {
            if(builttree(c, &(*tree) ->left) == 1) return 1;
            else if(builttree(c,&(*tree) -> right) == 1) return 1;
            else return 0;
        }
    }
    else  {
        *tree = malloc(sizeof(struct node));
        (*tree) ->num = c;
        (*tree) -> left = NULL;
        (*tree) -> right = NULL;
        return 1;
    }
}
int builttreefromright(char c, struct node** tree) {
    if( *tree) {
        if((*tree) -> num - 64 >= 0 && (*tree) -> num != 94)
            return 0;
        else {
            if(builttreefromright(c,&(*tree) -> right) == 1) return 1;
            else if(builttreefromright(c, &(*tree) ->left) == 1) return 1;
            else return 0;
        }
    }
    else  {
        *tree = malloc(sizeof(struct node));
        (*tree) ->num = c;
        (*tree) -> left = NULL;
        (*tree) -> right = NULL;
        return 1;
    }
}
void Preorder(struct node *current){
    if (current) {                          // if current != NULL
        printf("%c",current->num);   // V
        Preorder(current->left);       // L
        Preorder(current->right);      // R
    }
}
void Inorder(struct node *current){
    if (current) {                          // if current != NULL
        Inorder(current->left);        // L
        printf("%c",current->num);  // V
        Inorder(current->right);       // R
    }
}
void Postorder(struct node *current){
    if (current) {                         // if current != NULL
        Postorder(current->left);     // L
        Postorder(current->right);    // R
        printf("%c",current->num);  // V
    }
}




int main() {
    char temp;
    struct node *root;
    root = NULL;
    while(1){
        scanf("%c",&temp);
        if(temp != '\n'){
            builttree(temp, &root);
        }
        else break;
    }

    char tempfortwo[20];
    struct node *rootfortwo;
    rootfortwo = NULL;
    int count = 0;
    while(1){
        scanf("%c",&temp);
        if(temp != '\n'){
            tempfortwo[count] = temp;
            count++;
        }
        else break;
    }
    for(int i = count-1 ; i >=0 ; i -- ){
        builttreefromright(tempfortwo[i], &rootfortwo);
    }
    Postorder(root);
    printf("\n");


    Preorder(rootfortwo);
    printf("\n");



    return 0;



    }



