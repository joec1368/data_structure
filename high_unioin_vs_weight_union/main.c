#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int parent[1010];
int range;
range = 100;
int num_round;
num_round = 1000000;

struct node {
    int data;
    struct node* next;
    int num;
    struct node* par;
};
void weightUnion(int i, int j){
    int temp = parent[i] + parent[j];
    if(parent[i] > parent[j]){
        parent[i] = j;
        parent[j] = temp;
    }
    else{
        parent[j] = i;
        parent[i] = temp;
    }
}
int collapsingFind(int i){
    int root,trail, lead;
    for(root = i ; parent[root] >= 0 ; root = parent[root]);
    for(trail = i ; trail != root ; trail = lead){
        lead = parent[trail];
        parent[trail] = root;
    }
  //  printf("%d",parent[root]);
    return root;
}
int main() {
    int times = 5;
    while (--times >= 0) {
        int count = 0;
        int point_range = 0;
        int ran_num[range];

        srand(time(NULL));
        for (int i = 0; i < range; i++) {
            ran_num[i] = rand() % range + 1;
        }
        for (int i = 0; i < range; i++) {
            parent[i] = -1;
        }
        while (count + 1 <= range) {
            int temp, temp2;
            temp = ran_num[count++];
            temp2 = ran_num[count++];
            for (; parent[temp] > 0; temp = parent[temp]);
            for (; parent[temp2] > 0; temp2 = parent[temp2]);
            weightUnion(temp, temp2);
        }
        for (int i = 0; i < range; i++) {
            int temp, temp2;
            temp = parent[i];
            temp2 = parent[i + 1];
            int j = temp;
            if (j > 0)
                for (; temp >= 0; temp = parent[temp]) {
                    j = temp;
                }
            else j = i;
            int z = temp2;
            if (z > 0)
                for (; temp2 >= 0; temp2 = parent[temp2]) {
                    z = temp2;
                }
            else z = i + 1;
            if (j != z)
                weightUnion(j, z);
        }

        int num_ran_find[num_round];
        for (int i = 0; i < num_round; i++) {
            num_ran_find[i] = rand() % range + 1;
        }
        clock_t start, end;

        start = clock();
        for (int i = 0; i < num_round; i++) {
            collapsingFind(num_ran_find[i]);
        }
        end = clock();

        double ans_one = end - start;

        printf("weight : %lf\n", ans_one);


        int number, num_case;
        number = range;
        num_case = num_round;
        count = 0;
        struct node *ans[number + 1];
        for (int i = 0; i <= number; i++) {
            ans[i] = malloc(sizeof(struct node));
            ans[i]->data = 1;
            ans[i]->next = NULL;
            ans[i]->par = NULL;
            ans[i]->num = i;
        }
        for (int i = 0; i < range;) {
            struct node *temp_height;
            struct node *temp_height_second;
            temp_height = ans[ran_num[i++]];
            temp_height_second = ans[i++];
            for (; temp_height->par; temp_height = temp_height->par);
            for (; temp_height_second->par; temp_height_second = temp_height_second->par);
            if (temp_height->num != temp_height_second->num) {
                if (temp_height->data >= temp_height_second->data) {
                    temp_height_second->par = temp_height;
                    temp_height->next = temp_height_second;

                } else {
                    temp_height->par = temp_height_second;
                    temp_height_second->next = temp_height;

                }
                if (temp_height->data == temp_height_second->data) {
                    temp_height->data++;
                }
            }

        }

        start = clock();
        for (int i = 0; i < num_case; i++) {
            struct node *temp_first;
            struct node *mid;
            struct node *find;
            temp_first = ans[num_ran_find[i]];
            for (; temp_first->par; temp_first = temp_first->par);
            for (find = temp_first; find != temp_first;) {
                mid = find;
                find = find->par;
                mid->par = temp_first;
            }
        }
        end = clock();
        double ans_two = end - start;

        printf("height : %lf\n\n", ans_two);
    }
}

