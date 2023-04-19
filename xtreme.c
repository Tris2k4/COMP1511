#include <stdio.h>

int main() {
    int size; 
    printf("Enter size: ");
    scanf("%d", &size);

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (row == col || row + col % 4 ==0) {
                printf("*");
            }
            
            else {
                printf("-");
            }
    } 
    printf("\n");
    return 0;
   }
}