#include <stdio.h>
#include <math.h>

int main() {
    char instruction;
    int num1, num2;

    while (1) {
        printf("Enter instruction: ");
        int num_inputs = scanf(" %c %d %d", &instruction, &num1, &num2);

        if (num_inputs == EOF) {
            break;
        } else if (num_inputs == 2 && instruction == 's') {
            printf("%d\n", num1 * num1);
        } else if (num_inputs == 3 && instruction == 'p') {
            printf("%d\n", (int) pow(num1, num2));
        } else {
            printf("Invalid instruction\n");
        }
    }

    return 0;
}
