#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polyNode{
    char data;
    struct polyNode *link_next;
    struct polyNode *link_down;
};

struct polyNode* createtree(struct polyNode **node, char **que){
    struct polyNode* temp = malloc(sizeof(struct polyNode));
        if(**que == ',') (*que)++;
        if (**que == '(') {
            temp->data = **que;
            (*que)++;

            (temp)->link_down = createtree(&temp, que);
            if(**que != ')' && **que !='\0')
            (*que)++;
            (*temp) .link_next = NULL;
            if(**que == '\0') return temp;
            (temp)->link_next = createtree(&(temp), que);
            return temp;

        }else if(**que != ')'){
            temp->data = **que;
            (*que)++;
            (temp)->link_down = NULL;
            (temp)->link_next = createtree(&(temp), que);
            return temp;

        }


        if (**que == ')') {
            temp->data = **que;
            (*que)++;
            (temp)->link_down = NULL;
            (temp)->link_next = NULL;
            return temp;
        }

        return temp;

}
int print(struct polyNode *root, char *ans , int *count){
    if(root != NULL){
        ans[(*count)++] = root->data;
        if(root->link_down != NULL) print(root ->link_down , ans ,count);
        if(root->link_next != NULL) print(root -> link_next,ans,count);
        return 0;
    }
}
void change(char *ans) {
    int i = 0;
    int j = 0;
    while (1) {
    for (i = j; ans[i] != '\0'; i++) {
        if (ans[i] == '(') break;
    }
         j = i+1;
    for (; ans[j] != '\0'; j++) {
        if (ans[j] == ')') break;
        else if (ans[j] == '(') break;
    }
    if(ans[j] == ')')break ;
    }
    for(int k = i+1; k < j ; k++){
        for(int z = k ; z < j ; z++){
            if(ans[z] - ans[k] < 0){
                char temp;
                temp = ans[k];
                ans[k] = ans[z];
                ans[z] = temp;
            }
        }
    }
}


int main() {
    int num;
    scanf("%d", &num);
    getchar();
    struct polyNode *now;
    int playone;
    int playtwo;
    int name_id;
    int i = 0;
    int *num_name;
    int fornum_name = 0;
    num_name = &fornum_name;
    int forpoint_name = 0;
    int *point_name;
    point_name = &forpoint_name;
    struct polyNode *polynode[100];
    char answer[5][100];
    int *count ;
    int a = 0;
    count = &a;
    while (num > 0) {
        i = 0;

        char declare_name[100];
        scanf("%s",declare_name);
        switch (declare_name[0]) {
            case 'r':
                scanf("%d",&name_id);
                now = polynode[name_id];

                char question[100];
                scanf("%s",question);
                char *pointer;
                pointer = question;
                polynode[name_id] = createtree(&now,&pointer);
                *count = 0;
                now = polynode[name_id];

                print(now,answer[name_id],count);
                change(answer[name_id]);
                printf("readed\n");
                break;
            case 'c':
                switch (declare_name[1]) {
                    case 'l':
                        scanf("%d",&name_id);
                        polynode[name_id] = NULL;
                        printf("cleared\n");
                        break;
                    case 'o':
                        scanf("%d %d",&playone,&playtwo);
                        polynode[playtwo] = polynode[playone];
                        *count = 0;
                        print(polynode[playtwo],answer[playtwo],count);
                        printf("copied\n");
                        break;
                }
                break;
            case 'i':
                scanf("%d %d",&playone,&playtwo);
                polynode[playtwo] = polynode[playone];
                  if(strcmp(answer[playone], answer[playtwo]) == 0) printf("true\n");
                  else printf("false\n");

                break;
            case 'w':
                scanf("%d",&name_id);

                char ans[100];
//                now = polynode[name_id];
//                print(now,ans,count);
                for(int k = 0 ; k < *count ; k++){
                    printf("%c",answer[name_id][k]);
                    if(answer[name_id][k] == '(');
                    else if(k+1 < *count){
                        if(answer[name_id][k+1] != '(' && answer[name_id][k+1] != ')'){
                            printf(",");
                        }
                    }
                }
                printf("\n");

                break;
        }
        num--;
    }
}
