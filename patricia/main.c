#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct patriciaTree *partrecia;
struct patriciaTree{
    int binNumber;//第幾個數字
    char add[1005];//addres EX 101010
    int data; // save data
    int num_add; // how many words in address
    partrecia left,right;
};
partrecia root;
partrecia parent;

int bit(char temp[1005], int m){
    if(temp[m-1] == '1'){
        return 1;
    }else {
        return 0;
    }
}

int inorder(partrecia t , char k[1005]){

    if(t -> left->binNumber > t -> binNumber &&  inorder(t -> left,k) == 1) {
        if(parent == NULL)parent = t;
        return 1;
    }
    if(t ->right -> binNumber > t -> binNumber && inorder(t -> right,k) == 1 ) {
        if(parent == NULL)parent = t;
        return 1;
    }
    if(0 == strcmp(t -> add , k)) return 1;
    return 0;
}

partrecia search(partrecia t , char k[1005]){
    parent = NULL;
    partrecia currentNode, nextNode;
    if(!t) return NULL;//NULL tree;
    nextNode = t -> left;
    currentNode = t;
    parent = currentNode;
    while(nextNode -> binNumber > currentNode -> binNumber){
        currentNode = nextNode;
        nextNode = (bit(k,nextNode -> binNumber)) ? nextNode -> right : nextNode -> left;//right == 1, left == 0;
        if(nextNode != currentNode){
            parent = currentNode;
        }
    }

    return nextNode;
}

void delete(partrecia t , char k[1005]){
    partrecia p = search(t, k);
    if(p == NULL){
        printf("delete -> not found\n");
        return;
    }
    else if(0 != strcmp(k, p->add)){
        printf("delete -> not found\n");
        return;
    }else{
        printf("delete -> %d\n",p->data);
    }
    if(p -> left == p || p -> right == p){//one self pointer

        if(p == root){
            root = NULL;
            return;
        }else {
            if(parent -> left == p){
                if(p -> left == p){
                    parent -> left = p -> right;
                }else{
                    parent -> left = p -> left;
                }
            }else{
                if(p -> left == p){
                    parent -> right = p -> right;
                }else{
                    parent -> right = p -> left;
                }
            }
        }
    }
    else{ // no self pointer
        partrecia q = parent;
        partrecia temp;
        if(q->left == p) {
             temp = search(q->right,q->add);
        }
        else if(q -> right == p){
             temp = search(q->left,q->add);
        }
        else{
            assert(0);
        }


        if(0 == strcmp(q->add, temp->add)){
            partrecia r = parent;
            p -> data = q -> data;
            strcpy(p->add,q->add);
            if(r -> left == q) r -> left = p;
            else r -> right = p;
            parent = NULL;
            inorder(p , q -> add);
            partrecia qpar = parent;
            if(qpar -> left == q){
                if(q ->left == p) qpar -> left = q -> right;
                else  qpar -> left = q -> left;
            }else if(qpar -> right == q){
                if(q ->left == p) qpar -> right = q -> right;
                else  qpar -> right = q -> left;
            }else{
                printf("false");
                assert(0);
            }

        }else {
            if(q -> left == q || q -> right == q){
                if(p -> left == q || p -> right == q){
                    if(p -> left == q){
                        p ->data = q -> data;
                        stpcpy(p -> add , q -> add);
                        p -> left = p;
                    }else{
                        p ->data = q -> data;
                        stpcpy(p -> add , q -> add);
                        p -> right = p;
                        p ->data = q -> data;
                        stpcpy(p -> add , q -> add);
                    }
                }
                else{
                    if(q -> left == q){
                        inorder(q -> right , q ->add);
                        p ->data = q -> data;
                        stpcpy(p -> add , q -> add);
                        if(parent -> right == q)parent -> right = p;
                        else if(parent -> left == q) parent -> left = p;
                        else{
                            assert(0);
                        }
                    }else if(q -> right == q) {
                        inorder(q -> left , q ->add);
                        p ->data = q -> data;
                        stpcpy(p -> add , q -> add);
                        if(parent -> right == q)parent -> right = p;
                        else if(parent -> left == q) parent -> left = p;
                        else{
                            assert(0);
                        }
                    }else{
                        assert(0);
                    }

                }
            }
            else{
                assert(0);
            }
        }
    }


}

void insert(partrecia *t, char new_add[1005] , int data, int num_add){
    partrecia current, parent, last, new;
    int i;
    if(!(*t)){
        *t = malloc(sizeof (struct patriciaTree));
        (*t) -> binNumber = 0;
        for(int j = 0 ; j < 1005 ; j++){
            (*t) -> add[j] = 0;
        }
        strcpy((*t) -> add , new_add);
        (*t) -> left = (*t);
        (*t) -> num_add = num_add;
        (*t) -> right = NULL;
        (*t) -> data = data;
        printf("insert -> %d\n",(*t)->data);
        return;
    }
    last = search(*t, new_add);
    if(0 == strcmp(new_add, last->add)){
        printf("insert -> conflict\n");
        return;
    }
    for(i = 1; bit(new_add, i) == bit(last->add , i) ; i++);
    current = (*t) -> left;
    parent = *t;
    while(current -> binNumber > parent -> binNumber && current -> binNumber < i){
        parent = current;
        current = (bit(new_add, current ->binNumber)) ? current -> right : current -> left;
    }

    new = malloc(sizeof (struct patriciaTree));
    strcpy(new->add , new_add);
    new -> binNumber = i;
    new -> data = data;
    new -> num_add = num_add;
    new -> left = (bit(new_add, i)) ? current : new;
    new -> right = (bit(new_add, i)) ? new : current;
    printf("insert -> %d\n",new->data);
    if(current == parent -> left) parent -> left = new;
    else parent -> right = new;

}

int main() {
    int total_number;
    scanf("%d",&total_number);
    while(1){
        char decide[20];
        char temp[1005];
        scanf("%s",&decide);
        switch (decide[0]) {
            case 'i'://insert
                for(int i = 0 ; i < 1005 ; i++) temp[i] = 0;
                scanf("%s",&temp);
                int data;
                scanf("%d",&data);
                insert(&root,temp,data,total_number);
                break;
            case 'd'://delete
                for(int i = 0 ; i < 1005 ; i++) temp[i] = 0;
                scanf("%s",&temp);
                delete(root,temp);
                break;
            case 's'://search
                for(int i = 0 ; i < 1005 ; i++) temp[i] = 0;
                scanf("%s",&temp);
                partrecia part = search(root, temp);
                if(part == NULL){
                    printf("search -> not found\n");
                }
                else if(0 == strcmp(temp, part->add)){
                    printf("search -> %d\n",part->data);
                }else{
                    printf("search -> not found\n");
                }
                break;
            case 'q':
                return 0;
        }


    }

}
