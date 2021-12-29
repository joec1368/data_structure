#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode *polyPointer;
typedef struct polyNode{
    int coef;
    int expon;
    polyPointer link;
};
polyPointer a,b,c,d,e;



void checkname(char name[5][100], int* num_name, int* point_name){
    char name_temp[100];
    char temp;
    int i = 0;
    int ans = 0;
    while(1){
        scanf("%c",&temp);
        if(temp == ' '||temp == '\n') break;
        name_temp[i++] = temp;
    }
    int j = 0;
    for( ; j < *num_name ; j++){
        for(int z = 0 ; z < i ; z++){
            if(name[j][z] == name_temp[z]) ans++;
        }
        if(ans >= i) {
            *point_name = j;
            return ;
        }
        ans = 0;
    }

    for(int z = 0 ; z < i ; z++){
        name[*num_name][z] = name_temp[z];
        *point_name = *num_name;

    }
    (*num_name)++;
    return ;


}
int compare(int a,int b){
    if(a > b) return 1;
    if(a == b) return 0;
    if(a < b) return -1;
}
int main() {
    int num;
    scanf("%d",&num);
    getchar();
    char declare_name[8];
    char polynomial_name[5][100];
    char temp;
    int count = 0;
    int i = 0;
    int *num_name;
    int fornum_name = 0;
    num_name = &fornum_name;
    int forpoint_name = 0;
    int *point_name;
    point_name = &forpoint_name;
    polyPointer polynode[5] = {a,b,c,d,e};
    polynode[0] = malloc(sizeof(struct polyNode));
    polynode[0]->link = NULL;
    polynode[1] = malloc(sizeof(struct polyNode));
    polynode[1]->link = NULL;
    polynode[2] = malloc(sizeof(struct polyNode));
    polynode[2]->link = NULL;
    polynode[3] = malloc(sizeof(struct polyNode));
    polynode[3]->link = NULL;
    polynode[4] = malloc(sizeof(struct polyNode));
    polynode[4]->link = NULL;
    while(num > 0) {
        i = 0;
        while (1) {
            scanf("%c", &temp);
            if (temp == ' ' || temp == '\n') break;
            declare_name[i++] = temp;
        }
        switch (declare_name[0]) {
            case 'p':
                switch (declare_name[1]) {
                    case 'e':
                        checkname(polynomial_name, num_name, point_name);
                        polyPointer newfortemp ;
                        newfortemp = malloc(sizeof(struct polyNode));
                        newfortemp->link = NULL;
                        polynode[*num_name] = newfortemp;
                        (*num_name)--;
                        printf("erased\n");
                        break;
                    case 'r':
                        checkname(polynomial_name, num_name, point_name);
                        char temp_coef;
                        char temp_expon;
                        scanf("%c", &temp_coef);
                        getchar();
                        while (1) {
                            scanf("%c", &temp_coef);
                            getchar();
                            scanf("%c", &temp_expon);
                            polyPointer pointer = polynode[*point_name];
                            for (; pointer->link != NULL; pointer = pointer->link);
                            pointer->link = malloc(sizeof(struct polyNode));
                            pointer->link->expon = temp_expon - '0';
                            pointer->link->coef = temp_coef - '0';
                            pointer->link->link = NULL;
                            if (getchar() == '\n') break;
                        }
                        printf("ok\n");
                        break;
                    case 'm':
                        count = 0;
                        while(1){
                            char temp;
                            scanf("%c",&temp);
                            if(temp == ' ' || temp == '\n') break;
                            polynomial_name[*num_name][count++] = temp;
                        }
                        (*num_name)+1;

                        checkname(polynomial_name, num_name, point_name);
                        int first_mul[100];
                        int count_first_mul = 0;
                        polyPointer pointer = polynode[*point_name];
                        pointer = pointer -> link;
                        while(1) {
                            first_mul[count_first_mul++] = pointer ->coef;
                            first_mul[count_first_mul++] = pointer ->expon;
                            if(pointer -> link != NULL) {
                                pointer = pointer -> link;
                            }
                            else break;
                        }

                        checkname(polynomial_name, num_name, point_name);
                        int second_mul[100];
                        int count_second_mul = 0;
                        pointer = polynode[*point_name];
                        pointer = pointer -> link;
                        while(1) {
                            second_mul[count_second_mul++] = pointer ->coef;
                            second_mul[count_second_mul++] = pointer ->expon;
                            if(pointer -> link != NULL) {
                                pointer = pointer -> link;
                            }
                            else break;
                        }
                        int x = 1;
                        int y = 1;
                        int total[10][10];
                        for(int clearx = 0 ; clearx < 10 ; clearx ++){
                            for(int cleary = 0 ; cleary < 10 ; cleary++){
                                total[clearx][cleary] = 0;
                            }
                        }
                        int count_for_expo = 0;
                        for(int x = 1;x < count_first_mul ; x+=2){
                            for(int y = 1; y <count_second_mul ; y+=2){
                                if(first_mul[x] == 1  ) total[1][count_for_expo]= second_mul[y]+ 1;
                                else if(second_mul[y] == 1)total[1][count_for_expo]= first_mul[x]+ 1;
                                else
                                total[1][count_for_expo] = first_mul[x]*second_mul[y];

                                total[0][count_for_expo++] = first_mul[x-1]*second_mul[y-1];
                            }

                        }

                        for(int count_for_add = 0 ; count_for_add < count_for_expo ; count_for_add++){
                            for(int count_for_add_two = count_for_add +1 ; count_for_add_two < count_for_expo;count_for_add_two++){
                                if(total[1][count_for_add] == total[1][count_for_add_two]){
                                    total[0][count_for_add] = total[0][count_for_add] + total[0][count_for_add_two];
                                    total[1][count_for_add_two] = 0;
                                    total[0][count_for_add_two] = 0;
                                }
                            }
                        }
                        for(int count_for_add = 0 ; count_for_add < count_for_expo ; count_for_add++){
                            for(int count_for_add_two = count_for_add +1 ; count_for_add_two < count_for_expo;count_for_add_two++){
                                if(total[1][count_for_add] < total[1][count_for_add_two]){
                                    int tempforchange = total[1][count_for_add];
                                    total[1][count_for_add] = total[1][count_for_add_two];
                                    total[1][count_for_add_two] = tempforchange;

                                    tempforchange = total[0][count_for_add];
                                    total[0][count_for_add] = total[0][count_for_add_two];
                                    total[0][count_for_add_two] = tempforchange;

                                    count_for_add = 0;
                                    count_for_add_two = count_for_add +1;
                                }
                            }
                        }
                        polyPointer tempformul = polynode[*num_name];
                        tempformul->link = NULL;
                        for(int pull = 0 ; total[0][pull] != 0 ; pull++) {
                            tempformul->link = malloc(sizeof(struct polyNode));
                            tempformul = tempformul->link;
                            tempformul->link = NULL;
                            tempformul->coef = total[0][pull];
                            tempformul->expon = total[1][pull];
                        }
                        printf("multiplied\n");
                        break;
                    case 'w':
                        checkname(polynomial_name, num_name, point_name);
                         pointer = polynode[*point_name];
                        pointer = pointer -> link;
                        while(1) {
                            printf("%dx^%d",pointer -> coef,pointer -> expon);

                            if(pointer -> link != NULL) {
                                pointer = pointer -> link;
                                if(pointer -> coef > 0 ) printf("+");
                            }
                            else break;
                        }
                        printf("\n");
                        break;
                    case 'a':
                        count = 0;
                        while(1){
                            char temp;
                            scanf("%c",&temp);
                            if(temp == ' ' || temp == '\n') break;
                            polynomial_name[*num_name][count++] = temp;
                        }
                        (*num_name)+1;

                        checkname(polynomial_name, num_name, point_name);
                        int first[100];
                        int count_first = 0;
                        pointer = polynode[*point_name];
                        pointer = pointer -> link;
                        while(1) {
                            first[count_first++] = pointer ->coef;
                            first[count_first++] = pointer ->expon;
                            if(pointer -> link != NULL) {
                                pointer = pointer -> link;
                            }
                            else break;
                        }

                        checkname(polynomial_name, num_name, point_name);
                        int second[100];
                        int count_second = 0;
                        pointer = polynode[*point_name];
                        pointer = pointer -> link;
                        while(1) {
                            second[count_second++] = pointer ->coef;
                            second[count_second++] = pointer ->expon;
                            if(pointer -> link != NULL) {
                                pointer = pointer -> link;
                            }
                            else break;
                        }
                         x = 1;
                         y = 1;
                        polyPointer tempforadd = polynode[*num_name];
                        tempforadd->link = NULL;
                        while(x < count_first && y < count_second){

                            tempforadd ->link = malloc(sizeof(struct polyNode));
                            tempforadd = tempforadd -> link;
                            tempforadd->link = NULL;
                            switch(compare(first[x],second[y])){
                                case 1:
                                    tempforadd -> coef = first[x-1];
                                    tempforadd -> expon = first[x];
                                    x += 2;

                                    break;
                                case 0:
                                    tempforadd -> coef= first[x-1] + second[y-1];
                                    tempforadd -> expon = first[x];
                                    x += 2;
                                    y += 2;
                                    break;
                                case -1:
                                    tempforadd -> coef = second[y-1];
                                    tempforadd -> expon = second[y];
                                    y += 2;
                                    break;
                            }
                        }
                        printf("added\n");
                        break;
                    case 's':

                        count = 0;
                        while(1){
                            char temp;
                            scanf("%c",&temp);
                            if(temp == ' ' || temp == '\n') break;
                            polynomial_name[*num_name][count++] = temp;
                        }
                        (*num_name)+1;

                        checkname(polynomial_name, num_name, point_name);
                        int first_sub[100];
                        int count_first_sub = 0;
                        pointer = polynode[*point_name];
                        pointer = pointer -> link;
                        while(1) {
                            first_sub[count_first_sub++] = pointer ->coef;
                            first_sub[count_first_sub++] = pointer ->expon;
                            if(pointer -> link != NULL) {
                                pointer = pointer -> link;
                            }
                            else break;
                        }

                        checkname(polynomial_name, num_name, point_name);
                        int second_sub[100];
                        int count_second_sub = 0;
                        pointer = polynode[*point_name];
                        pointer = pointer -> link;
                        while(1) {
                            second_sub[count_second_sub++] = pointer ->coef;
                            second_sub[count_second_sub++] = pointer ->expon;
                            if(pointer -> link != NULL) {
                                pointer = pointer -> link;
                            }
                            else break;
                        }
                         x = 1;
                         y = 1;
                        polyPointer tempforsub = polynode[*num_name];
                        tempforsub->link = NULL;
                        while(x < count_first_sub && y < count_second_sub){

                            tempforsub ->link = malloc(sizeof(struct polyNode));
                            tempforsub = tempforsub -> link;
                            tempforsub->link = NULL;
                            switch(compare(first[x],second[y])){
                                case 1:
                                    tempforsub -> coef = first[x-1];
                                    tempforsub -> expon = first[x];
                                    x += 2;

                                    break;
                                case 0:
                                    tempforsub -> coef= first[x-1] - second[y-1];
                                    tempforsub -> expon = first[x];
                                    x += 2;
                                    y += 2;
                                    break;
                                case -1:
                                    tempforsub -> coef = second[y-1];
                                    tempforsub -> expon = second[y];
                                    y += 2;
                                    break;
                            }
                        }
                        printf("substracted\n");
                        break;

                }
                break;
            case 'e':
                checkname(polynomial_name, num_name, point_name);
                float total = 0;
                float temp_for_mul = 1;
                float save ;
                int expo;
                scanf("%f",&save);
                polyPointer tempforsub = polynode[*point_name];
                tempforsub = tempforsub->link;
                while(tempforsub  != NULL) {
                    expo = tempforsub->expon;
                    temp_for_mul = 1;
                    for(int last = 1;last <= expo; last++ ){
                        temp_for_mul = temp_for_mul * save;
                    }
                    total = total + temp_for_mul*(tempforsub->coef);
                    tempforsub = tempforsub->link;

                }
                printf("%.2f\n",total);
                break;

        }
        num--;
    }
    return 0;
}
