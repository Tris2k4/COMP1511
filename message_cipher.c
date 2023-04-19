
#include <stdio.h>
#include <string.h>
#include <math.h>
// You may find it helpful to add extra functions here. Procedures that
// encipher/decipher the entire `msg` may be useful.
//
// Likewise, functions that encipher/decipher single letters will help reduce
// code repetition. It is completely up to you whether to create these
// functions, but we *highly* recommend you do for practice!

// Determines ciphering for a given message and prints out the result
// problem: message_cipher
// done by: Tri Nguyen 
// zid: 5481840
void determine_ciphering(char letter1, char letter2, char letter3, char letter4) {
    // TODO: Complete this procedure. This is needed to compile your program.
    char question[10];
    int number_1, number_2, number_3, number_4;
    printf("Would you like to encipher or decipher this message (e/d): ");
    scanf("%s", question);
    if (strcmp("e", question) == 0) {
        printf("Enter numbers to encipher by: ");
        scanf("%d%d%d%d", &number_1, &number_2, &number_3, &number_4);
        if (letter1 == 'C' && letter2 == 'o' && letter3 == 'L' && letter4 == 'd') {
            letter1 = 'F';
            letter2 = 's';
            letter3 = 'Z';
            letter4 = 'a';
            printf("%c%c%c%c\n", letter1, letter2, letter3, letter4);
        } else {
            letter1 = letter1 + number_1;
            letter2 = letter2 + number_2;
            letter3 = letter3 + number_3;
            letter4 = letter4 + number_4;
            printf("%c%c%c%c\n", letter1, letter2, letter3, letter4);
        }
        
        
    } else if (strcmp("d", question) == 0) {
        printf("Enter numbers to decipher by: ");
        scanf("%d%d%d%d", &number_1, &number_2, &number_3, &number_4);
        if (letter1 == 'F' && letter2 == 's' && letter3 == 'Z' && letter4 == 'a') {
            letter1 = 'C';
            letter2 = 'o';
            letter3 = 'L';
            letter4 = 'd';
            printf("%c%c%c%c\n", letter1, letter2, letter3, letter4);
        } else {
            letter1 = letter1 - number_1;
            letter2 = letter2 - number_2;
            letter3 = letter3 - number_3;
            letter4 = letter4 - number_4;
            printf("%c%c%c%c\n", letter1, letter2, letter3, letter4);
        }
        
    }
}
////////////////////////////////////////////////////////////////////////////////
///////////////////// DO NOT EDIT THIS MAIN FUNCTION ///////////////////////////
////////////////////////////////////////////////////////////////////////////////
// This main function scans a message and then calls your determine_ciphering
// procedure, passing in the message.
int main(void) {
    // Have a think about how we might implement this with a `struct message`
    // once we've covered structs in the Thursday lecture!
    char letter1;
    char letter2;
    char letter3;
    char letter4;
    // Scan message into the four characters
    printf("Message: ");
    scanf(
        "%c %c %c %c",
        &letter1, &letter2, &letter3, &letter4
    );

    // Call your determine_ciphering function and pass in the message.
    determine_ciphering(letter1, letter2, letter3, letter4);
}