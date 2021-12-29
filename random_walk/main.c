#include <stdio.h>
#include <stdlib.h>
int main() {
    char decide;

    while(1) {
        scanf("%c",&decide);
        if(decide == 'q') break;
        int x, y;
        int x_start, y_start;
        int count = 0;

        if (decide == 'a') {
            scanf("%d %d", &x, &y);

            x_start = x / 2;
            y_start = y / 2;
        } else {
            int temp;
            scanf("%d", &temp);
            if (temp == 1) {
                x = 15;
                y = 15;
                x_start = 9;
                y_start = 9;
            } else {
                x = 39;
                y = 19;
                x_start = 0;
                y_start = 0;
            }
        }
        char temp;
        scanf("%c",&temp);
        int map[x][y];
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                map[i][j] = 0;
            }
        }
        while (1) {
            map[x_start][y_start]++;
            count++;
            int check = 0;
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) {
                    if (map[i][j] != 0) check++;
                }
            }
            if (check == x * y) break;
            int randnum = rand() % 8;
            switch (randnum) {
                case 0:
                    if (x_start - 1 >= 0) x_start--;
                    break;
                case 1:
                    if (x_start + 1 < x) x_start++;
                    break;
                case 2:
                    if (y_start - 1 >= 0) y_start--;
                    break;
                case 3:
                    if (y_start + 1 < y) y_start++;
                    break;
                case 4:
                    if (x_start - 1 >= 0 && y_start - 1 >= 0) {
                        x_start--;
                        y_start--;
                    }
                    break;
                case 5:
                    if (x_start + 1 < x && y_start - 1 >= 0) {
                        x_start++;
                        y_start--;
                    }
                    break;
                case 6:
                    if (x_start - 1 >= 0 && y_start + 1 < y) {
                        x_start--;
                        y_start++;
                    }
                    break;
                case 7:
                    if (x_start + 1 < x && y_start + 1 < y) {
                        x_start++;
                        y_start++;
                    }
                    break;


            }

        }
        printf("%d\n", count);
        for (int i = 0; i < x; i++) {
            printf(" ");
            for (int j = 0; j < y; j++) {
                int temp;
                temp = map[i][j];
                if( j == 0){
                    if (temp - 10 < 0) {
                        printf(" %d", temp);
                    } else printf("%d", temp);
                }
                else {
                    if (temp - 10 < 0) {
                        printf("  %d", temp);
                    } else printf(" %d", temp);
                }

            }
            printf("\n");
        }
    }


    return 0;
}
