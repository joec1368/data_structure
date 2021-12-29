#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct node* nodePointer;

typedef struct node{
    int num_node;
    int first;
    int second;
    int third;
    int hegiht;
    int total;
    int leaf;
    nodePointer forward;
    nodePointer backward;
    nodePointer left;
    nodePointer mid;
    nodePointer right;
    nodePointer last;
    nodePointer parent;

}node;

nodePointer root;


int  check(nodePointer start){
    if(start == NULL) return 1;
    if(start -> left){
        if(start -> left ->first > start -> first) return 0;
        if(start -> left -> num_node == 2 && start -> left -> first > start -> second) return 0;
        if(start -> left -> num_node == 2 && start -> left -> second > start ->second) return 0;
        if(start -> left -> num_node == 2 && start -> left -> second > start ->first) return 0;
        if (check(start -> left)==0) return 0;
    }
    if (start ->mid ){
        if(start -> mid ->first < start -> first) return 0;
        if(start -> num_node == 2 && start -> second < start -> mid -> first) return 0;
        if(start -> num_node == 2 && start -> second < start -> mid -> second)  return 0;
        if (check(start -> mid)==0) return 0;
    }
    if(start -> right){
        if(start -> right ->first < start -> second) return 0;
        if (check(start -> right)==0) return 0;
    }
    return  1;
}

void fixup(nodePointer current){
    while(current != NULL){
        int n1,n2,n3;
        n1 = 0;
        n2 = 0;
        n3 = 0;
        if(current -> left) n1 = current -> left -> total + current ->left -> num_node;
        if(current -> mid)  n2 = current -> mid -> total + current -> mid -> num_node;
        if(current -> right ) n3 = current -> right -> total + current -> right ->num_node;
        current -> total = n1 + n2 + n3 ;
        current = current -> parent;
    }
}

void treversal(nodePointer start){
    if(start == NULL) return;
    if(start -> left) treversal(start ->left);
    fixup(start);
    if(start -> mid) treversal(start -> mid);
    fixup(start);
    if(start -> right) treversal(start -> right);
    fixup(start);
}

void change(nodePointer current){
    if(current -> first > current -> second ){
        int temp;
        temp = current -> first;
        current -> first = current -> second;
        current -> second = temp;
        if(current -> mid) current -> right = current -> mid;
        if(current -> left) {
            current -> mid = current -> left;
        }
        current -> left = NULL;
    }
}

void compare(nodePointer *current){
    int p1 , p2 , p3;
    p1 = (*current) -> first;
    p2 = (*current) -> second;
    p3 = (*current) -> third;
    nodePointer left,mid,right,last;
    left = (*current) -> left;
    mid = (*current) -> mid;
    right = (*current) -> right;
    last = (*current) -> last;
    if( p1 >= p2){
        if(p2 >= p3){
            (*current) -> first = p3;
            (*current) -> second = p2;
            (*current) -> third = p1;

        }
        else {//p2 < p3
            if(p1 >= p3){
                (*current) -> first = p2;
                (*current) -> second = p3;
                (*current) -> third = p1;
            }
            else{
                (*current) -> first = p2;
                (*current) -> second = p1;
                (*current) -> third = p3;
            }
        }
    }
    else{ // p1 < p2
        if(p2 >= p3){
            if(p1 >= p3){
                (*current) -> first = p3;
                (*current) -> second = p1;
                (*current) -> third = p2;
                (*current) -> last = right;

            }
            else{
                (*current) -> first = p1;
                (*current) -> second = p3;
                (*current) -> third = p2;
            }
        }
        else {//p2 < p3
            (*current) -> first = p1;
            (*current) -> second = p2;
            (*current) -> third = p3;
        }
    }

}

void rotation_mid_right(nodePointer current){
    if(current -> mid -> leaf == 1){
        current -> mid -> first = current -> right -> first;
        current -> first = current -> mid -> first;
        current -> right -> first = current -> right -> second;
        current -> right -> num_node = 1;
        current -> second = current -> right -> first;
    } else {
        int x, y, w, z;
        y = current->second;
        w = current->right->first;
        z = current->right->second;
        current->right->first = z;
        current->right->num_node = 1;
        current->second = w;
        current->mid->first = y;

        nodePointer a, b, c, d, e;
        c = current->right->left;
        d = current->right->mid;
        e = current->right->right;

        current->mid->mid = c;
        current->right->left = d;
        current->right->mid = e;
        current->right->right = NULL;

        if (c) c->parent = current->mid;
    }

}

void insert_split(nodePointer * current , nodePointer * p1 , nodePointer *p2){
    int n1,n2;
    n1 = 0;
    n2 = 0;

    (*p1) = malloc(sizeof (node));
    (*p1) ->first = (*current) -> first;
    (*p1) ->left = (*current) ->left;
    (*p1) -> mid = (*current) -> mid;
    (*p1) -> hegiht = (*current) -> hegiht;
    (*p1) -> num_node = 1;
    (*p1) -> right = NULL;
    (*p1) -> parent = NULL;
    if((*p1) -> left){
        (*p1) -> left ->parent = (*p1);
        n1 = (*p1) -> left -> total  + (*p1) ->left ->num_node;
    }
    if((*p1) -> mid) {
        (*p1) -> mid ->parent = (*p1);
        n2 = (*p1) -> mid -> total + (*p1) ->mid ->num_node;
    }
    (*p1) -> total = n1+n2;

    n1 = 0;
    n2 = 0;


    (*p2) = malloc(sizeof (node));
    (*p2) ->first = (*current) -> third;
    (*p2) ->left = (*current) ->right;
    (*p2) -> mid = (*current) -> last;
    (*p2) -> hegiht = (*current) -> hegiht;
    (*p2) -> num_node = 1;
    (*p2) -> right = NULL;
    (*p2) -> parent = NULL;
    if((*p2) -> left ) {
        (*p2) -> left ->parent = (*p2);
        n1 = (*p2) -> left -> total + (*p2) -> left -> num_node;
    }
    if((*p2) -> mid && (*p2) -> mid -> parent){
        (*p2) -> mid ->parent = (*p2);
        n2 = (*p2) -> mid -> total + (*p2) -> mid -> num_node;
    }
    (*p2) -> total = n1+n2;
}

void insert(nodePointer * temp , int x){

    nodePointer current = *temp;

    if(current == NULL) {
        (current) = malloc(sizeof(node));
        (current) -> left = NULL;
        (current) -> right = NULL;
        (current) -> mid = NULL;
        (current) -> last = NULL;
        (current) -> first = x;
        (current) -> second = 0;
        (current) -> num_node = 1;
        (current) -> hegiht = 1;
        (current) -> parent = NULL;
        current -> total = 0;
        current -> leaf = 1;
        current -> forward = NULL;
        current -> backward = NULL;
        root = current;
        fixup(current);

        return;
    }
    while(1) {
        if (current -> leaf != 1) {
            switch ((current)->num_node) {
                case 1:
                    if (x < (current)->first) (current) = (current) -> left;
                    else {
                        if(current -> mid) (current) = (current) -> mid;
                    }
                    break;
                case 2:
                    if(x < (current) -> first) (current) = (current) -> left;
                    else if( x > (current) ->second ) (current) = (current) -> right;
                    else {
                        if(current -> mid) (current) = (current) -> mid;
                    }
                    break;
            }
        }
        else break;
    }

    if((current) -> num_node == 1){
        (current) -> second = x;
        (current) -> num_node = 2;
        change(current);
        current -> last = NULL;
        fixup(current);
        if( current -> parent && current == current -> parent ->mid){
            current ->parent -> first = current -> first;
        }else if( current -> parent && current == current -> parent -> right){
            current -> parent -> second = current -> first;
        }

        return;
    }
    else{
        nodePointer p1 , p2 , p3 , p4 ,box;
        (current) -> third = x;
        compare(&current);
        current -> last = NULL;

        while(1){

            int mid = (current) -> second;
            insert_split(&current , &p1 , &p2);

            box = malloc(sizeof (node));
            box -> first = mid;
            box -> left = p1;
            p1 -> parent = box;
            box -> mid = p2;
            p2 -> parent = box;
            box -> hegiht = (current) -> hegiht + 1;
            box -> num_node = 1;
            box -> right = NULL;
            box -> parent = NULL;
            if(current -> leaf == 1){

                p2 -> second = p2 ->first;
                p2 -> first = mid;
                p1 -> backward = p2;

                p2 -> forward = p1;

                p2 -> num_node = 2;
                p1 -> leaf = 1;
                p2 -> leaf = 1;
                if(current -> forward){
                    current -> forward -> backward = p1;
                    p1 -> forward = current -> forward;
                }
                else{
                    p1 -> forward = NULL;
                }
                if(current -> backward){
                    current -> backward -> forward = p2;
                    p2 -> backward = current -> backward;
                }
                else{
                    p2 -> backward = NULL;
                }
            }
            box -> total = p1 -> total + p1 -> num_node + p2 -> total + p2 -> num_node;

            if((current)->parent == NULL){

                current -> parent = box;
                // (current) = box;
                root = box;
                root -> last = NULL;
                root -> right = NULL;
                box -> parent = NULL;
                fixup(current);

                return;
            }
            else if ((current)->parent -> num_node == 1){

                if((current)->parent -> left == (current)){

                    box -> second = (current)->parent -> first;
                    box -> right = (current)->parent ->mid;
                    box -> parent = (current)->parent -> parent;
                    if((current)->parent ->parent && (current)->parent ->parent -> left && (current)->parent ->parent ->left == (current)->parent) (current)->parent -> parent -> left = box;
                    else if((current)->parent -> parent && (current)->parent -> parent  -> right == (current)->parent) (current)->parent -> parent -> right = box;
                    else if((current)->parent -> parent && (current)->parent -> parent-> mid == (current)->parent)(current)->parent -> parent -> mid = box;
                    else root = box;
                    (current) = box;
                    fixup(current -> left);
                    fixup(current -> mid);
                    fixup(current);

                }
                else {
                    (current)->parent -> mid = box -> left;
                    box -> left -> parent = (current)->parent;
                    (current)->parent -> right = box -> mid;
                    box -> mid -> parent =(current)->parent;
                    (current)->parent -> second = box -> first;
                    fixup(current -> left);
                    fixup(current -> mid);
                    fixup(current);
                    fixup(current);
                    (current) = (current)->parent;

                }
                (current) -> num_node +=1;
                if(current -> left) current -> left -> parent  = current;
                if(current -> mid) current -> mid -> parent = current;
                if(current -> right) current -> right -> parent = current;
                fixup(current);
                current -> last = NULL;

                return;
            }
            else{

                current -> parent -> last = NULL;
                if((current) -> parent -> left == (current)){

                    (current) -> parent -> third = (current) -> parent -> second;
                    (current) -> parent -> second = (current) -> parent -> first;
                    (current) -> parent -> first = box -> first;
                    (current) -> parent ->last = (current) -> parent -> right;
                    (current) -> parent -> right = (current) -> parent -> mid;
                    (current) -> parent -> mid = box -> mid;
                    box -> mid -> parent = (current)->parent;
                    (current) -> parent ->left = box -> left;
                    box -> left -> parent = (current)->parent;
                    nodePointer  parent = current -> parent;

                }
                else if((current) -> parent -> mid == (current)){

                    (current) -> parent -> third = (current) -> parent -> second;
                    (current) -> parent -> second = box -> first;

                    (current) -> parent -> last = (current) -> parent -> right;
                    (current) -> parent -> right = box -> mid;
                    box -> mid -> parent =(current)->parent;
                    (current) -> parent -> mid = box -> left;
                    box -> left -> parent = (current)->parent;
                    nodePointer  parent = current -> parent;
                }
                else{
                    (current) -> parent -> third = box -> first;
                    (current) -> parent -> last = box -> mid;
                    box -> mid -> parent = (current)->parent;
                    (current) -> parent -> right = box -> left;
                    box -> left -> parent = (current)->parent;
                    nodePointer  parent = current -> parent;
                }

                (current) = (current)->parent;
                if(current -> left) current -> left -> parent  = current;
                if(current -> mid) current -> mid -> parent = current;
                if(current -> right) current -> right -> parent = current;
                if(current -> last) current -> last -> parent = current;

            }
        }
    }
    fixup(current);
}

void rotation_left(nodePointer current){ // parent

    if(current -> left -> leaf == 1){
        current  -> left -> first = current -> mid -> first;
        current -> mid -> first = current -> mid -> second;
        current -> mid -> num_node = 1;
        current -> first = current -> mid -> first;


    }else {
        current->left->first = current->first;
        current->first = current->mid->first;
        current->mid->first = current->mid->second;
        current->mid->num_node = 1;
        nodePointer b, c, d;
        b = current->mid->left;
        current->mid->left = NULL;
        c = current->mid->mid;
        current->mid->mid = NULL;
        d = current->mid->right;
        current->mid->right = NULL;
        current->left->mid = b;
        if (b) b->parent = current->left;
        current->mid->left = c;
        current->mid->mid = d;
    }

}

void rotation_mid(nodePointer current){

    if(current -> mid -> leaf == 1){
        current -> mid -> first = current -> left -> second;
        current -> left -> num_node = 1;
        current -> first = current -> mid -> first;
        current -> mid ->num_node = 1;
    }else {
        current->mid->first = current->first;
        current->first = current->left->second;
        current->left->num_node = 1;
        nodePointer b, c, d;
        c = current->left->right;
        current->left->right = NULL;
        d = current->mid->left;
        current->mid->left = NULL;
        current->mid->mid = d;
        current->mid->left = c;
        if (c) c->parent = current->mid;
    }

}

void rotation_right(nodePointer current){

    if(current -> right -> leaf == 1){
        current -> right -> first = current -> mid -> second;
        current -> mid -> num_node = 1;
        current -> second = current -> right -> first;
    }else {
        current->right->first = current->second;
        current->second = current->mid->second;
        current->mid->num_node = 1;

        nodePointer d, e;
        d = current->mid->right;
        current->mid->right = NULL;
        e = current->right->left;
        current->right->left = NULL;
        current->right->mid = e;
        current->right->left = d;
        if (d) d->parent = current->right;

    }
}

void meld_left(nodePointer current, int* decide){

    if (current -> left ->leaf == 1){
        if(current -> num_node == 2){
            current -> left -> first = current -> mid -> first;
            current -> mid = current -> right;
            current -> right = NULL;
            current -> first = current -> mid -> first;
            current -> num_node = 1;
            *decide = 2;

            current -> left -> backward = current -> mid;
            current -> mid -> forward = current -> left;
        }else{
            current -> left -> first = current -> mid -> first;
            current ->left -> backward = current -> mid -> backward;
            if(current -> mid -> backward )  current -> mid -> backward -> forward = current -> left;
            current -> mid = NULL;
        }
    }
    else {
        if (current->num_node == 2) {
            current->left->first = current->first;
            current->left->second = current->mid->first;
            current->first = current->second;
            current->num_node = 1;
            current->left->num_node = 2;

            nodePointer b, c, d;
            b = current->mid->left;
            c = current->mid->mid;
            d = current->right;

            current->right = NULL;
            current->mid = d;
            current->left->mid = b;
            current->left->right = c;
            if (c) c->parent = current->left;
            if (b) b->parent = current->left;
            //current 為最中間的那個
            *decide = 2;


        } else {

            current->left->first = current->first;
            current->left->second = current->mid->first;
            current->left->num_node = 2;

            nodePointer b, c;
            b = current->mid->left;
            c = current->mid->mid;
            current->left->mid = b;
            if (b) b->parent = current->left;
            current->left->right = c;
            if (c) c->parent = current->left;
            current->mid = NULL;
            *decide = 1;
            current->first = current->left->second;
            //

        }
    }
}

void meld_mid(nodePointer current, int * decide){

    if (current -> mid ->leaf == 1){
        if(current -> num_node == 2){
            current -> mid = current -> right;
            current -> right = NULL;
            current -> first = current -> mid -> first;
            current -> num_node = 1;
            *decide = 2;

            current -> left -> backward = current -> mid;
            current -> mid -> forward = current -> left;
        }else{
            current -> left -> backward = current -> mid -> backward;
            if(current -> mid -> backward )  current -> mid -> backward -> forward = current -> left;
            current -> mid = NULL;
        }
    }
    else {
        if (current->num_node == 2) {
            current->left->second = current->first;
            current->first = current->second;
            current->num_node = 1;
            current->left->num_node = 2;


            nodePointer c, d;
            c = current->mid->left;
            d = current->right;
            current->left->right = c;
            if (c) c->parent = current->left;
            current->mid = d;
            current->right = NULL;
            *decide = 2;

        } else {

            current->left->second = current->first;
            current->left->num_node = 2;
            nodePointer c;
            c = current->mid->left;
            current->left->right = c;
            if (c) c->parent = current->left;
            current->mid = NULL;
            current->right = NULL;
            *decide = 1;

        }
    }
}

void meld_right(nodePointer current){
    if(current -> right -> leaf == 1){
        current -> mid -> backward = current -> right -> backward;
        if(current -> right -> backward) current -> right -> backward -> forward = current -> mid;
        current -> num_node = 1;
        current -> right = NULL;
    }
    else {
        current->mid->second = current->second;
        current->num_node = 1;
        current->mid->num_node = 2;
        nodePointer a, b, c;
        c = current->right->left;
        current->mid->right = c;
        current->right = NULL;
        if (c) c->parent = current->mid;
    }



}

void delete_operation(nodePointer target , int x){
    if(target -> parent == NULL){
        if(target -> num_node == 2){
            if(target -> first == x){
                target ->  first = target -> second;
                target -> num_node = 1;
            }
            else target -> num_node = 1;
        }
        else {
            root = NULL ;

            return ;
        }
    }
    else if(target -> left == NULL && target -> mid == NULL && target -> right == NULL ) { //case 1

        if (target->num_node == 2) {
            if (target->first == x) {
                target->first = target->second;
                target->num_node = 1;
                if(target -> parent -> mid == target){
                    target -> parent -> first = target -> first;
                }else if(target -> parent -> right == target){
                    target -> parent -> second = target -> first;
                }
            } else {
                target->num_node = 1;
            }
            fixup(target);
            return;
        }
    }
    while(target -> parent != NULL){
        if(target -> parent -> left == target){
            if(target -> parent -> mid -> num_node == 2) {
                rotation_left(target -> parent);
                fixup(target);
                return;
            }
            else {
                int *temp;
                int zero = 0;
                temp = &zero;
                meld_left(target -> parent,temp);
                if(*temp == 2) {
                    fixup(target);
                    return;
                }
                target = target->parent;
            }
        }
        else if(target -> parent -> mid == target){
            //
            if(target -> parent -> left -> num_node == 2){
                rotation_mid(target -> parent);
                fixup(target);

                return;
            }
            else if(target->parent->right && target -> parent -> right -> num_node == 2){
                rotation_mid_right(target -> parent);
                fixup(target);

                return;
            }
            else {
                int *temp;
                int zero = 0;
                temp = &zero;
                meld_mid(target -> parent,temp);
                if(*temp == 2){
                    fixup(target);

                    return;

                }
                target = target->parent;
            }
        }
        else{

            if(target -> parent ->mid -> num_node == 2){
                rotation_right(target -> parent);
                fixup(target);

                return;
            }
            else {

                meld_right(target -> parent);
                target = target->parent;

            }
            fixup(target);
            return;
        }
    }
    if(target -> left) root = target -> left;
    root  -> parent = NULL;
}

void delete_searcht(nodePointer *now , int x ){
    nodePointer target, current;
    current = *now;
    while (current != NULL) {
        if (current->num_node == 1) {
            if (current->first == x) {
                target = current;
                break;
            }
            if (current->first < x) current = current->mid;
            else current = current->left;
        } else {
            if (current->first == x) {
                target = current;
                break;
            } else if (current->second == x) {
                target = current;
                break;
            }
            if (current->first > x) current = current->left;
            else if (current->second < x) current = current->right;
            else current = current->mid;
        }
    }
    if(current != NULL && current -> leaf != 1) {
        nodePointer temp_for_find;
        temp_for_find = current;
        there:
        if(current -> left) {
            current = current->left;

            while (current != NULL) {
                if (current->num_node == 1) {
                    if (current->first == x) {
                        target = current;
                        break;
                    }
                    if (current->first < x) current = current->mid;
                    else current = current->left;
                } else {
                    if (current->first == x) {
                        target = current;
                        break;
                    } else if (current->second == x) {
                        target = current;
                        break;
                    }
                    if (current->first > x) current = current->left;
                    else if (current->second < x) current = current->right;
                    else current = current->mid;
                }
            }
        }
        if(current != NULL && current -> leaf == 1);
        else if(current != NULL && current -> leaf != 1){
            temp_for_find = current;
            goto there;
        }
        else if(current == NULL || current -> leaf != 1 && temp_for_find -> mid){
            current = temp_for_find;
            if(current -> mid){
                current = current -> mid;
                while (current != NULL) {
                    if (current->num_node == 1) {
                        if (current->first == x) {
                            target = current;
                            break;
                        }
                        if (current->first < x) current = current->mid;
                        else current = current->left;
                    } else {
                        if (current->first == x) {
                            target = current;
                            break;
                        } else if (current->second == x) {
                            target = current;
                            break;
                        }
                        if (current->first > x) current = current->left;
                        else if (current->second < x) current = current->right;
                        else current = current->mid;
                    }
                }
            }
            if(current != NULL && current -> leaf == 1);
            else if(current != NULL && current -> leaf != 1 && current != temp_for_find){
                temp_for_find = current;
                goto there;
            }
            else if(current == NULL || current -> leaf != 1){
                current = temp_for_find;
                if(current -> right){
                    current = current -> right;
                    while (current != NULL) {
                        if (current->num_node == 1) {
                            if (current->first == x) {
                                target = current;
                                break;
                            }
                            if (current->first < x) current = current->mid;
                            else current = current->left;
                        } else {
                            if (current->first == x) {
                                target = current;
                                break;
                            } else if (current->second == x) {
                                target = current;
                                break;
                            }
                            if (current->first > x) current = current->left;
                            else if (current->second < x) current = current->right;
                            else current = current->mid;
                        }
                    }
                }
                if(current != NULL && current -> leaf == 1);
                else if(current != NULL && current -> leaf != 1 && current != temp_for_find){
                    temp_for_find = current;
                    goto there;
                }
                else return;
            }
        }
        else if(current == NULL || current -> leaf != 1 && temp_for_find -> right){
            current = temp_for_find;
            if(current -> right){
                current = current -> right;
                while (current != NULL) {
                    if (current->num_node == 1) {
                        if (current->first == x) {
                            target = current;
                            break;
                        }
                        if (current->first < x) current = current->mid;
                        else current = current->left;
                    } else {
                        if (current->first == x) {
                            target = current;
                            break;
                        } else if (current->second == x) {
                            target = current;
                            break;
                        }
                        if (current->first > x) current = current->left;
                        else if (current->second < x) current = current->right;
                        else current = current->mid;
                    }
                }
            }
            if(current != NULL && current -> leaf == 1);
            else if(current != NULL && current -> leaf != 1 && current != temp_for_find){
                temp_for_find = current;
                goto there;
            }
            else return;
        }

    }
    if(current == NULL){
        return;
    }
    target = current;
    nodePointer floor;
    int y;
    y = x;
    delete_operation(target , x);
    fixup(target);

}

void range(nodePointer now,int low , int high){
    if(now == NULL) {
        printf("range [%d,%d) = []\n",low,high);
        return;
    }
    while(1){
        if(now -> leaf == 1) break;
        else if(now ->first > low) now = now -> left;
        else if(now -> num_node == 2 && now ->second < low) now = now -> right;
        else now = now -> mid;
    }
    while (1){
        if( now -> forward && now -> forward -> first < low && now ->forward -> first <= now ->first){
            now = now -> forward;
            break;
        }
        else if(now -> forward && now -> forward -> first < low && now ->forward -> first >= now ->first){
            break;
        }
        else if(now -> forward && now ->forward -> first >= low && now ->forward -> first <= now ->first){
            now = now -> forward;
        }
        else if(now -> forward && now ->forward -> first >= low && now ->forward -> first >= now ->first){
            break;
        }else break;
    }
    printf("range [%d,%d) = [",low,high);
    while(1){
        if(now -> first < high ){
            if(now -> backward){
                if(now -> first >= low  && now -> first <= now -> backward -> first){
                    printf("%d",now->first);
                    if(now -> num_node == 2 && now -> second < high){
                        printf(",%d",now->second);
                        if(now -> backward && now -> backward  -> first < high && now ->backward ->first >= now ->first){
                            now = now->backward;
                            printf(",");
                        }else break;

                    }
                    else if(now -> num_node == 2 && now -> second > high  ) break;
                    else {
                        if(now -> backward && now -> backward  -> first < high && now ->backward ->first >= now ->first){
                            now = now->backward;
                            printf(",");
                        }else break;
                    }
                }
                else if(now -> forward && now -> first >= now -> forward -> first && now ->first < high && now -> first >= low){
                    printf("%d",now->first);
                    if(now -> num_node == 2 && now -> second < high){
                        printf(",%d",now->second);
                        if(now -> backward && now -> backward  -> first < high && now ->backward ->first >= now ->first){
                            now = now->backward;
                            printf(",");
                        }
                    }
                    break;
                }
                else if(now -> num_node == 2 && now -> second >= low && now -> second < high){
                    printf("%d",now->second);
                    if(now -> backward && now -> backward  -> first < high && now ->backward ->first >= now ->first){
                        now = now->backward;
                        printf(",");
                    }else break;
                }
                else now = now -> backward;
            }
            else if(now -> first >= low &&  now -> first  < high){
                printf("%d",now->first);
                if(now -> num_node == 2 && now -> second < high){
                    printf(",%d",now->second);
                }
                break;
            }
            else break;

        }
        else break;
    }
    printf("]\n");

}


int main() {

    int round;

    scanf("%d",&round);

    root = NULL;
    int count = 0;
    while(round-- >0){
        char decide[15];
        int temp;
        scanf("%s",decide);

        switch (decide[0]) {
            case 'a':
                scanf("%d",&temp);
                insert(&root , temp);
                break;
            case 'r':
                if(decide[1] == 'e') {
                    scanf("%d",&temp);
                    delete_searcht(&root ,temp);

                }
                else{
                    int low, high;
                    scanf("%d %d",&low ,&high);
                    range(root,low,high);

                }

                break;
            case 'q':
                return 0;
        }
    }
    return 0;
}
