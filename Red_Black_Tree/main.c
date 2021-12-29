#include <stdio.h>
#include <stdlib.h>


typedef struct node *nodePointer;
typedef struct node{  //color 0 == R ; 1 == B
    int data;
    int color;
    nodePointer left;
    nodePointer right;
    nodePointer parent;
}node_rbt;
nodePointer root;
nodePointer neel;


void leftrotation_rbt(nodePointer *parent){
    nodePointer son , gson;
    son = (*parent) -> right;
    gson = son -> left;

    (*parent) -> right = gson;
    if(gson != neel) gson -> parent = (*parent);
    son -> parent = (*parent) -> parent;
    if( (*parent) -> parent == neel) root = son;
    else if( (*parent) == (*parent) -> parent -> left)  (*parent) -> parent -> left = son;
    else (*parent) -> parent -> right = son;
    son -> left = *parent;
    (*parent) -> parent = son;
}

void rightrotation_rbt(nodePointer *parent){
    nodePointer son , gson;
    son = (*parent) -> left;
    gson = son -> right;

    (*parent) -> left = gson;
    if(gson != neel) gson -> parent = (*parent);
    son -> parent = (*parent) -> parent;
    if( (*parent) -> parent == neel) root = son;
    else if( (*parent) == (*parent) -> parent -> left)  (*parent) -> parent -> left = son;
    else (*parent) -> parent -> right = son;
    son -> right = *parent;
    (*parent) -> parent = son;

}

void Insertfixed(nodePointer now){
    nodePointer parent , uncle , gparent;

    parent = now -> parent;
    gparent = parent -> parent;

    if(now -> color == 1 ) return;
    else if( parent -> color == 1) return;
    else if( parent == gparent -> left){
        uncle = gparent -> right;
        if(uncle ->color == 0){ //case 1
            parent -> color = 1;
            gparent -> color = 0;
            uncle -> color = 1;
        }
        else if( uncle -> color == 1 && now == parent -> right){// case 2
            leftrotation_rbt(&parent);
            now = parent;
            parent = now -> parent;
            gparent = parent -> parent;
            parent -> color = 1;
            gparent -> color = 0;
            rightrotation_rbt(&gparent);
            gparent = now -> parent -> parent;
            root -> color = 1;
        }
        else if( uncle -> color == 1 && now == parent -> left ) {// case3
            parent -> color = 1;
            gparent -> color = 0;
            rightrotation_rbt(&gparent);
            gparent = now -> parent -> parent;
            root -> color = 1;

        }
    }
    else if(parent == gparent -> right) {// parent == gparent -> right
        uncle = gparent -> left;
        if(uncle ->color == 0){ //case 1
            parent -> color = 1;
            gparent -> color = 0;
            uncle -> color = 1;
        }
        else if( uncle -> color == 1 && now == parent -> left){// case 2
            rightrotation_rbt(&parent);
            now = parent;
            parent = now -> parent;
            gparent = parent -> parent;
            parent -> color = 1;
            gparent -> color = 0;
            leftrotation_rbt(&gparent);
            gparent = now -> parent -> parent;
            root -> color = 1;

        }
        else if( uncle -> color == 1 && now == parent -> right ) {// case3
            parent -> color = 1;
            gparent -> color = 0;
            leftrotation_rbt(&gparent);
            gparent = now -> parent -> parent;
            root -> color = 1;

        }
    }
    neel -> color = 1;
    Insertfixed(gparent);
    root -> color = 1;
    return;
}

void insert_rbt(int data){
    nodePointer x = root;
    nodePointer temp;
    temp = neel;

    while(x != neel){
        temp = x;
        if( data < x -> data){
            x = x -> left;
        }
        else if(data == x -> data) return;
        else x = x -> right;
    }

    nodePointer insert_node;
    insert_node = malloc(sizeof(node_rbt));
    insert_node -> data = data;
    insert_node -> left = neel;
    insert_node -> right = neel;
    insert_node -> parent = temp;
    insert_node -> color = 0;

    if(temp == neel || temp == NULL) root = insert_node;
    else if(data < temp ->data) temp ->left = insert_node;
    else temp -> right = insert_node;

    Insertfixed(insert_node);
    root -> color = 1;
}

void search_rbt(nodePointer parent , int target){
    if(parent == neel){
        printf("Not found\n");
        return;
    }
    else if(parent -> data == target) {
        int temp;
        temp = parent -> color;
        if(temp == 0) printf("red\n");
        else printf("black\n");
        return;
    }
    else if(parent -> data < target){
        search_rbt(parent -> right , target);
    }
    else search_rbt(parent -> left , target);
    return;

}

void exist_rbt(nodePointer parent , int target){
    if(parent == neel){
        printf("Not exist\n");
        return;
    }
    else if(parent -> data == target) {
        printf("exist\n");
        return;
    }
    else if(parent -> data < target){
        exist_rbt(parent -> right , target);
    }
    else exist_rbt(parent -> left , target);
    return;
}

void DeleteFix(nodePointer current){
    if(current->color == 0) {
        current -> color = 1;
        return;
    }
    if(current == root){
        current -> color = 1;
        return ;
    }
    if(current == root || current -> color == 0 || current == neel) return;
    nodePointer neighbor , parent;
    parent = current -> parent;
    if(parent -> left == current){
        neighbor = parent -> right;
        if(neighbor -> color == 0){ //case 1
            neighbor -> color = 1;
            parent -> color = 0;
            leftrotation_rbt(&parent);
            current = parent;
            parent = current -> parent;
            neighbor = parent -> right;
        }
        if(neighbor -> color == 1 && neighbor ->left -> color == 1 && neighbor -> right -> color == 1){ //case 2
            neighbor -> color = 0;
            current = parent;
            parent = current -> parent;
            if(current -> color == 0){
                current -> color = 1;
                return;
            }
            else if(current -> color == 1 && root != current){
                DeleteFix(parent);
            }
        }
        else {
            if (neighbor->color == 1 &&  neighbor->right->color == 1) { // case3
                neighbor->left->color = 1;
                neighbor->color = 0;
                rightrotation_rbt(&neighbor);
                parent = current->parent;
                neighbor = parent->right;
            }
            //case 4
            neighbor -> color = parent ->color;
            parent -> color = 1;
            neighbor -> right -> color = 1;
            leftrotation_rbt(&parent);
            root -> color = 1;
            return;

        }

    }

    else if(parent -> right == current){
        neighbor = parent -> left;
        if(neighbor -> color == 0){ //case 1
            neighbor -> color = 1;
            parent -> color = 0;
            rightrotation_rbt(&parent);
            current = parent;
            parent = current -> parent;
            neighbor = parent -> left;
        }
        if(neighbor -> color == 1 && neighbor ->right -> color == 1 && neighbor -> left -> color == 1){ //case 2
            neighbor -> color = 0;
            current = parent;
            parent = current -> parent;
            if(current -> color == 0){
                current -> color = 1;
                return;
            }
            else if(current -> color == 1 && root != current){
                DeleteFix(parent);
            }
        }
        else {
            if (neighbor->color == 1  && neighbor->left->color == 1) { // case3
                neighbor->right->color = 1;
                neighbor->color = 0;
                leftrotation_rbt(&neighbor);
                parent = current->parent;
                neighbor = parent->left;
            }
            //case 4
            neighbor -> color = parent ->color;
            parent -> color = 1;
            neighbor -> left -> color = 1;
            rightrotation_rbt(&parent);
            root -> color = 1;
            return;

        }

    }


}

void delete_rbt( int data){
    nodePointer x = root;
    nodePointer temp , target;
    temp = neel;

    while(x != neel){
        temp = x;
        if( data < x -> data){
            x = x -> left;
        }
        else if(data == x -> data) break;
        else x = x -> right;
    }
    if(x == neel) return;
    target = temp;

    if(target -> left == neel || target -> right == neel){
        temp = target;
    }else {
        if (x->right != NULL) {
            x = x->right;
            while (x != neel) {
                temp = x;
                x = x->left;
            }
        }
    }

    target -> data = temp -> data;
    if(temp -> left != neel) x = temp -> left;
    else x = temp -> right;

    x -> parent = temp -> parent;

    if(temp -> parent == neel) root = x;
    else if(temp == temp -> parent ->left) temp -> parent -> left = x;
    else temp -> parent -> right = x;

    if(temp -> color == 1){
        if(temp -> left != neel) DeleteFix(temp -> left);
        else DeleteFix(temp -> right);
    }
}

int main() {

    neel = malloc(sizeof (node_rbt));
    neel -> parent = neel;
    neel -> color = 1;
    neel -> left = neel;
    neel -> right = neel;
    neel -> data = INT16_MAX;
    root = neel;
    while(1){
        char decide[10];
        int temp;
        scanf("%s",&decide);
        switch (decide[0]) {
            case 'i'://insert
                scanf("%d",&temp);
                insert_rbt(temp);
                neel -> color = 1;
                break;
            case 'd': //delete
                scanf("%d",&temp);
                delete_rbt(temp);

                break;
            case 's': //search
                scanf("%d",&temp);
                search_rbt(root,temp);
                break;
            case 'e': //exist
                scanf("%d",&temp);
                exist_rbt(root,temp);
                break;
            case 'q': //quit
                return 0;
        }
    }
    return 0;
}
