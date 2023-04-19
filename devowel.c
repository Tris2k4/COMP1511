#include <stdio.h>

int main(void) {
    int letter;

    letter = getchar();
    while (letter != EOF) {

        if (letter != 'a' && letter != 'e' && letter != 'i' && letter != 'o' && letter != 'u') {
            putchar(letter);
        }

        letter = getchar();
    }

    return 0;
}


// 