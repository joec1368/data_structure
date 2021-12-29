#include <stdio.h>

struct bucket{
    int key;
    int data;
};


const int num_buckets = 31;
struct bucket buckets[num_buckets];

void reset(){
    for(int i = 0 ; i < 31 ; i++){
        buckets[i].key = -1;
    }
    return;
}




int h_function(int temp){
    return temp%num_buckets;
}

int search(int temp){
    int locate = h_function(temp);
    int final = locate;
    while(1){
        if(buckets[locate].key == temp){
            return buckets[locate].data;//return where the value is;
        }else if(buckets[locate].key == -1){
            //printf("not found\n");
            return -1;
        }
        else{
            locate++;
            if(locate >= num_buckets) locate = 0;
            if(final == locate){
              // printf("not found\n");
                return -1;
            }
        }
    }
}

int search_for_delete(int temp){
    int locate = h_function(temp);
    int final = locate;
    while(1){
        if(buckets[locate].key == temp){
            return locate;//return where the value is;
        }else if(buckets[locate].key == -1){
            //printf("not found\n");
           return -1;
            locate++;
            if(final == locate){
                // printf("not found\n");
                return -1;
            }
        }
        else{
            locate++;
            if(locate >= num_buckets) locate = 0;
            if(final == locate){
                // printf("not found\n");
                return -1;
            }
        }
    }
}

int insert(int temp,int data){
    int round = 0;
    int locate = h_function(temp);
    int final = locate;
    while(1){
        if(buckets[locate].key == -1){
            buckets[locate].key = temp;
            buckets[locate].data = data;
            printf("insertion succeed %d\n",data);
            return data;
        }
        else{
            locate++;
            if(locate >= num_buckets) locate = 0;
            if(final == locate) {
                printf("full");
                return -1;
            }
        }
    }
}

int delete(int temp){
    int locate = h_function(temp);
    int save_Search = search_for_delete(temp);
    if(save_Search == -1){
        printf("do not exist\n");
        return -1;
    }else{

        buckets[save_Search].key = -1;
        buckets[save_Search].data = -1;
        int next,now;
        now = save_Search;
        next = now + 1;
        if(next >= num_buckets) next = 0;
        while(1){
            if(buckets[next].key == -1){
                printf("delete succeed\n");
                return temp;
            }else if(next != h_function(buckets[next].key)){
                if(next > now && (next < h_function(buckets[next].key) || h_function(buckets[next].key) <= now)){
                    buckets[now] = buckets[next];
                    buckets[next].key = -1;
                    now = next;
                    next = now + 1;
                    if(next >= num_buckets){
                        next = 0;
                    }
                }else if(next < now && (h_function(buckets[next].key )> next && h_function(buckets[next].key) <= now)){
                    buckets[now] = buckets[next];
                    buckets[next].key = -1;
                    now = next;
                    next = now + 1;
                    if(next >= num_buckets){
                        next = 0;
                    }
                }else{
                    next++;
                    if(next >= num_buckets){
                        next = 0;
                    }
                    if(next == locate){
                        printf("delete succeed\n");
                        return temp;
                    }
                }

            }else{
                next++;
                if(next >= num_buckets){
                    next = 0;
                }
                if(next == locate){
                    printf("delete succeed\n");
                    return temp;
                }
            }
        }
    }
}

int main() {
    for(int i = 0 ; i < 31 ; i++)  buckets[i].key = -1;
    while(1){
        char decide[10];
        scanf("%s",&decide);
        int temp;
        int data;
        int receive;
        switch (decide[0]) {
            case 'i':
                scanf("%d %d",&temp,&data);
                insert(temp,data);
                break;
            case 'd':
                scanf("%d",&temp);
                delete(temp);
                break;
            case 's':
                scanf("%d",&temp);
                receive = search(temp);
                if(receive == -1){
                    printf("not found");
                }else{
                    printf("found %d",receive);
                }
                break;
            case 'q':
                return 0;
        }
    }
}
