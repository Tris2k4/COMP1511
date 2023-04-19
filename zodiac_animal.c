// Zodiac animals
// Tri Nguyen (z5481840) 
// 28/2/2023

#include <stdio.h>

// This year corresponds to the Rat.
#define MIN_YEAR 1900

// Enum defining the different zodiac ANIMALS
enum zodiac_animal {
    RAT = 0,
    OX,
    TIGER,
    RABBIT,
    DRAGON,
    SNAKE,
    HORSE,
    GOAT,
    MONKEY,
    ROOSTER,
    DOG,
    PIG
};

int main(void) {
    int year, formula;
    printf("Enter the year of your birth: ");
    //TODO complete the program:
    scanf("%d", &year);
    formula = (year - 1900) % 12;
    if (formula == RAT) {
        printf("You were born in the year of the Rat!\n");
    } else if (formula == OX) {
        printf("You were born in the year of the Ox!\n");
    } else if (formula == TIGER) {
        printf("You were born in the year of the Tiger!\n");
    } else if (formula == RABBIT) {
        printf("You were born in the year of the Rabbit!\n");
    } else if (formula == DRAGON) {
        printf("You were born in the year of the Dragon!\n");
    } else if (formula == SNAKE) {
        printf("You were born in the year of the Snake!\n");
    } else if (formula == HORSE) {
        printf("You were born in the year of the Horse!\n");
    } else if (formula == GOAT) {
        printf("You were born in the year of the Goat!\n");
    } else if (formula == MONKEY) {
        printf("You were born in the year of the Monkey!\n");
    } else if (formula == ROOSTER) {
        printf("You were born in the year of the Rooster!\n");
    } else if (formula == DOG) {
        printf("You were born in the year of the Dog!\n ");
    } else if (formula == PIG) {
        printf("You were born in the year of the Pig!\n ");
    }
    return 0;
}