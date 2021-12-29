#include <stdio.h>
#include <stdlib.h>



int main() {
    int decide;
    int array[100];
    int last;
    last = 0;
    array[0] = -2;
    while (1) {
    printf("1. Create a min heap.\n"
           "2. Remove the key with the lowest value.\n"
           "3. Change the priority of an arbitrary element.\n4. Insert an element into the heap.\n");
    scanf("%d", &decide);
    switch (decide) {
        case 1:
            if(last == 0){
                printf("creat\n");
            }
            else{
                printf("remove old and creat new\n");
            }
            last = 1;
            for(int i = 0 ; i < 100 ; i++){
                array[i] = -1;
            }
            break;
        case 2:
            if(last == 0) {
                printf("you need to create a heap\n");
                break;
            }
            if(array[1] == -1){
                printf("none\n");
                break;
            }
            printf("%d\n",array[1]);
            int z = 2;
            array[1] = array[last-1];
            array[last-1] = -1;
            for( ; z+1 < last ; ){
                if(array[z] != -1 && array[z+1] != -1) {
                    if (array[z] > array[z + 1]) {
                        if(array[z/2]> array[z+1]) {
                            int temp = array[z / 2];
                            array[z / 2] = array[z + 1];
                            array[z + 1] = temp;
                            z = (z + 1) * 2;
                        }
                        else {
                            z = (z + 1) * 2;
                        }
                    } else {
                        if(array[z/2]> array[z]) {
                            int temp = array[z / 2];
                            array[z / 2] = array[z ];
                            array[z ] = temp;
                            z = z  * 2;
                        }
                        else {
                            z = z  * 2;
                        }
                    }
                }
                else{
                    if(array[z] == -1){
                        if(array[z+1] < array[z/2]) {
                            int temp = array[z / 2];
                            array[z / 2] = array[z + 1];
                            array[z + 1] = temp;
                            z = (z + 1) * 2;
                        }
                    }
                    else{
                        if(array[z ] < array[z/2]) {
                            int temp = array[z / 2];
                            array[z / 2] = array[z];
                            array[z] = temp;
                            z = z * 2;
                        }
                        else {
                            z = z*2;
                        }
                    }
                }
            }
            last--;
            break;
        case 3:
            if(last == 0) {
                printf("you need to create a heap\n");
                break;
            }
            int temp;
            int temp_Second;
            int judge;
            judge= 0;
            printf("change a to b\n");
            scanf("%d",&temp);
            scanf("%d",&temp_Second);
            int i = 1;
            for( ; i < last  ; i++){
                if(array[i] == temp){
                    array[i] = temp_Second;
                    break;
                }
                if( i + 1 >= last ) {
                    printf("don't exist\n");
                    judge = 1;
                    break;
                }
            }
            if(judge == 1) break;

            for(int j = i  ; j > 0 ; ){
                if(array[j/2] != -1 && j/2 != 0) {
                    if (array[j] < array[j / 2]) {
                        temp = array[j];
                        array[j] = array[j / 2];
                        array[j / 2] = temp;
                    } else break;
                }
                if(array[j/2] == -1 && j/2 != 0){
                    array[j / 2] = array[j];
                }
                j = j / 2;
            }
            z = 2*i;
            for( ; z+1 <= last-1 ; ){
                if(array[z] != -1 && array[z+1] != -1) {
                    if (array[z] > array[z + 1]) {
                        if(array[z/2]> array[z+1]) {
                            int temp = array[z / 2];
                            array[z / 2] = array[z + 1];
                            array[z + 1] = temp;
                            z = (z + 1) * 2;
                        }
                        else {
                            z = (z + 1) * 2;
                        }
                    } else {
                        if(array[z/2]> array[z]) {
                            int temp = array[z / 2];
                            array[z / 2] = array[z ];
                            array[z ] = temp;
                            z = z  * 2;
                        }
                        else {
                            z = z  * 2;
                        }
                    }
                }
                else{
                    if(array[z] == -1){
                        array[z / 2] = array[z + 1];
                        z = (z + 1) * 2;
                    }
                    else{
                        int temp = array[z / 2];
                        array[z / 2] = array[z ];
                        array[z ] = temp;
                        z = z * 2;
                    }
                }
            }
            printf("done change\n");


            break;
        case 4:
            if(last == 0){
                printf("you need to create a heap\n");
                break;
            }
            scanf("%d",&temp);
            array[last++] = temp;
            for(i = last-1  ; i > 0 ; ){
                if(array[i/2] != -1 && i/2 != 0) {
                    if (array[i] < array[i / 2]) {
                        temp = array[i];
                        array[i] = array[i / 2];
                        array[i / 2] = temp;

                    } else break;
                }
                if(array[i/2] == -1 && i/2 != 0){
                    array[i / 2] = array[i];
                }
                i = i / 2;
            }
            printf("you add a new number\n");
            break;

    }
    }
    return 0;
}
