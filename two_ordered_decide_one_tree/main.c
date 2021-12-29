
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
};

struct node* Postorderbuilttree(int in[], int pos[], int start, int end ,int *last){

    if(start > end) return NULL;
    struct node* temp;
    temp = malloc(sizeof(struct node));
    temp->right = NULL;
    temp->left = NULL;
    temp->data = pos[(*last)--];

    if(start == end) return temp;
    int i = start;
    for( ; i <= end ; i++){
        if(in[i] == temp->data) break;
    }
    temp->right = Postorderbuilttree(in,pos,i+1,end,last);
    temp->left = Postorderbuilttree(in , pos, start, i-1,last);

    return temp;
}
struct node* Preorderbuilttree(int in[], int pre[], int start, int end,int *first){
    if(start > end) return NULL;
    struct node* temp;
    temp = malloc(sizeof(struct node));
    temp->right = NULL;
    temp->left = NULL;
    temp->data = pre[(*first)++];
    if(start == end) return temp;
    int i = start;
    for( ; i <= end ; i++){
        if(in[i] == temp->data) break;
    }
    temp->left = Preorderbuilttree(in , pre, start, i-1,first);
    temp->right = Preorderbuilttree(in,pre,i+1,end,first);
    return temp;
}
void Preorder(struct node *current , int num,int* point){
    if (current) {// if current != NULL

        printf("%d",current->data);// V
        if((*point)++ != num) printf(" ");
        Preorder(current->left,num,point);       // L
        Preorder(current->right,num,point);      // R
    }
}
void Postorder(struct node *current, struct node *root){
    if (current) {                         // if current != NULL
        Postorder(current->left,root);     // L
        Postorder(current->right,root);    // R
        printf("%d",current->data); // V
        if(current != root) printf(" ");
    }
}
int *point;
int main() {
    int times,number;

    scanf("%d",&times);
    while(times-- > 0) {
        char check[20];
        scanf("%s", &check);
        scanf("%d", &number);
        int firstline[number];
        int secondline[number];
        for(int i = 0 ; i < number ; i++){
            scanf("%d",&firstline[i]);
        }
        for(int i = 0 ; i < number ; i++){
            scanf("%d",&secondline[i]);
        }
        struct node* root;
        int* last;
        int num_last = number-1;
        int *first;
        int num_first = 0;
        first = &num_first;
        last = &num_last;
        switch (check[1]) {
            case 'r':
                root = Preorderbuilttree(secondline,firstline,0,number-1,first);
                Postorder(root,root);
                printf("\n");
                break;
            case 'o':

                root = Postorderbuilttree(secondline,firstline,0,number-1,last);
                int point = 1;
                int *point_point;
                point_point = &point;
                Preorder(root,number,point_point);
                printf("\n");
                break;
        }
    }
    return 0;
}

