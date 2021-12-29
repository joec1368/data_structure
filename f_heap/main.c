#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct b_tree_nodes{
    int degree;
    int key;
    int value;
    int delete_tree;
    struct b_tree_nodes *child;
    struct b_tree_nodes *neighbor;
    struct b_tree_nodes *parent;
};
const int total = 100;
const int range = 100;
struct b_tree_nodes *store[15];
int stage;


struct b_tree_nodes* container[total*3];
int count = 0;
struct b_tree_nodes* find_min(){
    for(int i = 1; i < count ; i++){
        if(container[i] -> key < container[0] -> key){
            struct b_tree_nodes * temp = container[0];
            container[0] = container[i];
            container[i] = temp;
        }
    }
    return container[0];
}
struct b_tree_nodes* insert(struct b_tree_nodes* min, int key,int value ){

    if(min == NULL){
        min  = malloc(sizeof (struct b_tree_nodes));
        container[count++] = min ;
        min  ->key = key;
        min  -> degree = 0;
        min  -> child = NULL;
        min  -> neighbor = NULL;
        min -> value = value;
        min -> delete_tree = 0;
        min -> parent = NULL;

    }
    else if(key < min->key){
        container[count++] = min ;
        container[0] = malloc(sizeof (struct b_tree_nodes));
        min = container[0];
        min  ->key = key;
        min -> degree = 0;
        min -> neighbor = NULL;
        min -> child = NULL;
        min -> value = value;
        min -> delete_tree = 0;
        min ->parent = NULL;


    } else {
        container[count] = malloc(sizeof (struct b_tree_nodes));
        container[count]->key = key;
        container[count]->value = value;
        container[count] -> degree = 0;
        container[count] -> child = NULL;
        container[count] -> delete_tree = 0;
        container[count] -> parent = NULL;
        container[count++] -> neighbor = NULL;
    }
    return min;
}
void arrange(int start){
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
            if(container[i] -> key < store[container[i] -> degree]->key){
                if(container[i] -> child){
                    struct b_tree_nodes *temp = container[i] -> child;
                    container[i] -> child  = store[container[i]->degree];
                    container[i] -> child -> neighbor  = temp;
                    temp -> parent = container[i];

                }
                else{
                    container[i] -> child = store[container[i]->degree];
                    store[container[i]->degree] ->parent = container[i];
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
                    temp ->parent =  store[container[i]->degree];

                }
                else{
                    store[container[i]->degree] -> child = container[i];
                    container[i] -> parent = store[container[i]->degree];

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
        if(container[i] -> key < container[0] -> key){
            struct b_tree_nodes * temp = container[0];
            container[0] = container[i];
            container[i] = temp;
        }
    }


    return container[0];
}
struct b_tree_nodes *find(int key, int value){
    struct b_tree_nodes* stack[100];
    int num_stack = -1;
    for(int i = 0 ; i < count ; i++){
        stack[++num_stack] = container[i];
    }
    while(num_stack>=0){
        struct b_tree_nodes* temp = stack[num_stack--];
        if(temp->key == key && temp ->value == value) return stack[num_stack+1];
        if(temp->neighbor != NULL) {
            if(temp-> neighbor ->key == key && temp -> neighbor -> value == value) return temp;
            stack[++num_stack] = temp->neighbor;
        }
        if(temp -> child != NULL) {
            if(temp-> child ->key == key && temp -> child -> value == value) return temp;
            stack[++num_stack] = temp->child;
        }
    }
    return NULL;
}

struct b_tree_nodes* extract(struct b_tree_nodes* min){

    if(!container[0]) return NULL;
    stage = 1;
    printf("(%d)%d\n",container[0]->key,container[0]->value);
    int temp;
    temp = container[0]->degree;
    container[0] = container[0]->child;
    min = container[0];
    if(container[0] == NULL){
        arrange(0);
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
                container[count] = temp_delete;
                container[count++] ->parent = NULL;
                i = 1;
            }
            if (temp) {
                container[count] = temp;
                container[count++] -> parent = NULL;
                temp_delete->neighbor = NULL;
                temp_delete->parent = NULL;

            } else {
                temp_delete->neighbor = NULL;
                temp_delete->parent = NULL;

                break;
            }
        }
    }
    if(container[0] == NULL) return NULL;
    container[0]-> neighbor = NULL;
    container[0]-> parent = NULL;
    return unionheap();
}
void cut(struct b_tree_nodes* start){
    while(1) {
        struct b_tree_nodes *temp_delete;
        container[count] = start;
        start = start->parent;
        container[count++] ->parent = NULL;
        temp_delete = container[count-1]->neighbor;
        container[count-1]->neighbor = NULL;
        container[count-1]->delete_tree = 0;
        for(;temp_delete;) {
            container[count] = temp_delete;
            temp_delete  =temp_delete -> neighbor;
            container[count] -> parent = NULL;
            container[count++] ->neighbor = NULL;
        }
        start ->degree --;
        if(start->delete_tree == 0)return;
    }
}
struct b_tree_nodes* delete(struct b_tree_nodes* min , int key , int value){
    int temp;
    struct b_tree_nodes *temp_pre;
    temp_pre = min;
    struct b_tree_nodes *temp_delete;
    if(min->child!=NULL) {
        if (min->child->key == key && min->child->value == value) {
            min->degree--;
            min->delete_tree++;
            temp_delete = min->child;
            min->child = temp_delete->neighbor;
            temp_delete = temp_delete->child;
            for (; temp_delete;) {
                container[count] = temp_delete;
                temp_delete = temp_delete->neighbor;
                container[count]->parent = NULL;
                container[count++]->neighbor = NULL;
            }
        }
    }
    else if(min ->neighbor != NULL) {
        if (min->neighbor->key == key && min->neighbor->value == value) {
            min->parent->delete_tree++;
            min->parent->degree--;
            temp_delete = min->neighbor;
            min->neighbor = min->neighbor->neighbor;
            temp_delete = temp_delete->child;
            for (; temp_delete;) {
                container[count] = temp_delete;
                temp_delete = temp_delete->neighbor;
                container[count]->parent = NULL;
                container[count++]->neighbor = NULL;
            }
        }
    }
    else{
        if(min->parent != NULL){
            min = NULL;
        }
        else{
            for(int i = 0 ; i < count ; i++){
                if(min == container[i]){
                    container[i] = NULL;
                    arrange(i);
                    break;
                }
            }
        }
    }
    if(temp_pre->delete_tree == 1){
        cut(temp_pre);
    }
      return NULL;
}
struct b_tree_nodes* decrease(struct b_tree_nodes* min , int key , int value,int del_val){
    if(min->child != NULL) {
        if (min->child->key == key && min->child->value == value) {
            struct b_tree_nodes *temp_delete;
            min->child->key -= del_val;
            if (min->child->key < min->key) {
                min->degree--;
                min->delete_tree++;
                temp_delete = min->child;
                min->child = temp_delete->neighbor;
                temp_delete = temp_delete->child;
                for (; temp_delete;) {
                    container[count] = temp_delete;
                    temp_delete = temp_delete->neighbor;
                    container[count]->parent = NULL;
                    container[count++]->neighbor = NULL;
                }
            }
            if (min->delete_tree == 1) {
                cut(min);
            }
        }
    }
    else if(min -> neighbor != NULL) {
        if (min->neighbor->key == key && min->neighbor->value == value) {
            struct b_tree_nodes *temp_delete;
            min->neighbor->key -= del_val;
            if (min->child->key < min->key) {
                min->parent->delete_tree++;
                min->parent->degree--;
                temp_delete = min->neighbor;
                min->neighbor = min->neighbor->neighbor;
                temp_delete = temp_delete->child;
                for (; temp_delete;) {
                    container[count] = temp_delete;
                    temp_delete = temp_delete->neighbor;
                    container[count]->parent = NULL;
                    container[count++]->neighbor = NULL;
                }
            }
            if (min->parent->delete_tree == 1) {
                cut(min->parent);
            }
        }
    }
    else{
        for(int i = 0 ; i < count ; i++){
            if(container[i]->key == key && container[i]->value == value){
                container[i] ->key -= del_val;
            }
        }
    }
    return NULL;
}


int main() {

    struct b_tree_nodes *min;
    for(int i = 0 ; i <= total ; i++ ){
        container[i] = malloc(sizeof (struct b_tree_nodes));
        container[i]->key = 0;
        container[i] -> child = NULL;
        container[i] -> neighbor = NULL;
        container[i] -> degree = 0;
        container[i] -> value = 0;
        container[i] -> delete_tree = 0;
    }
    while(1){
        char temp[50];
        scanf("%s",&temp);
        int temp_key;
        int temp_value;
        int temp_down_key;
        switch (temp[2]) {
            case 's': //insert
                scanf("%d %d",&temp_key,&temp_value);
                min = insert(container[0] , temp_key,temp_value);
                break;
            case 't': //extract
                extract(min);
                min = container[0];
                break;
            case 'l' : //delete
                scanf("%d %d",&temp_key,&temp_value);
                struct b_tree_nodes* temp;
                temp = find(temp_key,temp_value);
                delete(temp,temp_key,temp_value);
                min = find_min();
                break;
            case 'c': //decrease
                scanf("%d %d %d",&temp_key,&temp_value,&temp_down_key);
                temp = find(temp_key,temp_value);
                decrease(temp,temp_key,temp_value,temp_down_key);
                min = find_min();
                break;
            case 'i': //quit
                return 0;
        }
    }
}
