// Program which prints a letter depending on the user's request.
// by ...

#include <stdio.h>

int main() {

    char is_uppercase;
    printf("Uppercase: ");
    scanf("%c", &is_uppercase);

    int index;
    printf("Index: ");
    scanf("%d", &index);

    if(index < 0 || index > 25) {
    	printf("Number is invalid\n");
    }

    char letter;
    if(is_uppercase == 'y') {
    	letter = 'A' + index;
    } else if(is_uppercase == 'n') {
    	letter = 'a' + index;
    } else {
    	printf("Please enter y/n\n");
    }
    printf("The letter is: %c\n", letter);
}
