#include <stdio.h>
#include <stdlib.h>

struct node{
    int num;
    struct node *left;
    struct node *right;
    int Threaded_left;
    int Threaded_right;
}node;

struct node* insucc(struct node* tree){
    struct node* temp;
    temp = tree -> right;
    if(!tree -> Threaded_right){
        while(!temp -> Threaded_left){
            temp = temp ->left;
        }
    }
    return temp;
}

void insertRight(struct node* r,struct node* s){
    struct node* temp;
    r->right = s->right;
    r->Threaded_right = s->Threaded_right;
    r->left = s;
    r->Threaded_left = 1;
    s->Threaded_right = 0;
    s->right = r;
    return ;
}

void insertLeft(struct node* r,struct node* s){
    struct node* temp;
    r->left = s->left;
    r->Threaded_left = s->Threaded_left;
    r->right = s;
    r->Threaded_right = 1;
    s->left = r;
    s->Threaded_left = 0;
    return ;
}

void search_inorder(struct node* tree , int check , int find,int save){
    struct node* temp = tree;
    for(;;){
        temp = insucc(temp);
         if( temp -> num == find) {
            struct node* forbuilt;
            forbuilt = malloc(sizeof(struct node));
            forbuilt ->num = save;
            if(check == 1){
                insertRight(forbuilt,temp);
            }
            else insertLeft(forbuilt,temp);
            break;
        }
    }
}
//從root出發，然後會先走到左邊最底，在一個個走訪，找到相同的值後，去做插入動作
void inorder(struct node* tree, int *point , int num){
    struct node* temp = tree;
    for(;;){
        temp = insucc(temp);
        if(temp == tree) break;
        printf("%d",temp->num);
        if(num != ++(*point)) printf(" ");
    }
}

int main() {
    int number , first;
    scanf("%d %d",&number , &first);
    struct node* root;
    root  = malloc(sizeof (struct node));
    root->num = -1;
    root->right = malloc(sizeof(struct node));
    root -> left = root;
    root->Threaded_left = 1;
    root -> Threaded_right = 0;

    root->right->Threaded_right = 1;
    root->right->Threaded_left = 1;
    root->right->num = first;
    root->right->right = root;
    root->right->left = root;

    for(int i = 0 ; i < number ; i++){
        int find = 0;
        int save;
        char forchar[10];
        scanf("%d",&find);
        scanf("%s",&forchar);
        scanf("%d",&save);
        switch(forchar[0]){
            case 'l':
                search_inorder(root,0,find,save);
                break;
            case 'r':
                search_inorder(root,1,find,save);
                break;
        }
    }
    int count = 0;
    int *point = 0;
    point = &count;
    inorder(root,point , number+1);
    printf("\n");
    return 0;
}
