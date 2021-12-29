#include <stdio.h>
#include <stdlib.h>


int last;
int const arrayLength = 10000;
int h[arrayLength] ;

void insert(int x){
    int currendNode, done, gp, lcgp, rcgp;
    //find x position
    //currentNode starts from new leaf and climb up
    currendNode = ++last;
    if(last % 2 == 1 && x < h[last-1]){
        //because of P1, It is knows that left subline is smaller than right subline
        h[last] = h[last - 1] ;
        currendNode--;
    }
    done = 0; // False
    while( done == 0 && currendNode >= 4){
        //currentNode hass ancestor node
        gp = currendNode / 4; // the position of ancestor node
        lcgp = 2 * gp; //gp's left son
        rcgp = lcgp + 1; //gp's right son
        if(x < h[lcgp]){ //break P2
            h[currendNode] = h[lcgp];
            currendNode = lcgp;
        }
        else if( x > h[rcgp]){ //break P3
            h[currendNode] = h[rcgp];
            currendNode = rcgp;
        }
        else done = 1; // obey P2 and P3
    }
     h[currendNode] = x;

}

void delete_min(){
    int currentNode;
    if(last == 2) {
        h[2] = 0;
        last--;
        return;
    }
    h[2] = h[last--];
    h[last+1] = 0;
    currentNode = 2;
    while(currentNode <= last){
        int compare;
        if(currentNode*2 <= last && (currentNode+1)*2 <= last){
            if(h[(currentNode+1)*2] <= h[currentNode*2]) compare = (currentNode+1)*2;
            else compare= currentNode*2;
        }
        else if(currentNode*2 <= last) compare = currentNode*2;
        else return;
        if(h[compare] <= h[currentNode]){
            int temp;
            temp = h[compare] ;
            h[compare] = h[currentNode];
            h[currentNode] = temp;
            currentNode = compare;
            if(currentNode+1 <=last){
                if(h[currentNode] > h[currentNode+1]){
                    int temp;
                    temp = h[currentNode];
                    h[currentNode] = h[currentNode+1];
                    h[currentNode+1] = temp;
                }
            }
        }
        else return;

    }

}
void delete_max(){
    int currentNode;
    if(last == 2) {
        h[2] = 0;
        last--;
        return;
    }
    h[3] = h[last--];
    h[last+1] = 0;
    currentNode = 3;
    while(currentNode <= last){
        int compare;
        if((currentNode*2) + 1  <= last && ((currentNode-1)*2) + 1 <= last){
            if(h[(currentNode*2) + 1 ] <= h[((currentNode-1)*2) + 1]) compare = ((currentNode-1)*2) + 1;
            else compare= (currentNode*2) + 1 ;
        }
        else if(((currentNode-1)*2) + 1 <= last) compare = ((currentNode-1)*2) + 1;
        else return;
        if(h[compare] >= h[currentNode]){
            int temp;
            temp = h[compare] ;
            h[compare] = h[currentNode];
            h[currentNode] = temp;
            currentNode = compare;
                if(h[currentNode] < h[currentNode-1]){
                    int temp;
                    temp = h[currentNode];
                    h[currentNode] = h[currentNode-1];
                    h[currentNode-1] = temp;
                }

        }
        else return;

    }

}




int main() {
    for(int i = 0 ; i < arrayLength ; i++) h[i] = 0;
    last = 1;
    while(1){
        char temp[10];
        char decide[100];
        int num_insert;
        scanf("%s",&decide);
        getchar();
        switch (decide[0]) {
            case 'i'://insert
                scanf("%d",&num_insert);
                insert(num_insert);
                getchar();
                break;
            case 'd':
                scanf("%s",&temp);
                getchar();
                switch (temp[1]) {
                    case 'i'://delete min
                    delete_min();
                        break;
                    case 'a'://delete max
                    delete_max();
                        break;
                }

                break;
            case 's':
                printf("NULL\n");
                int j = 4;
                for(int i = 2 ; i <= last ; i++){
                    if(i == j){
                        printf("\n");
                        j *=2;
                    }
                    else if (i!=2) printf(" ");
                    printf("%d",h[i]);
                }
                printf("\n");
                break;
            case 'q':
                return 0;

        }
    }
}
