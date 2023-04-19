// Written by <YOUR-NAME-HERE> (<YOUR-ZID>) 
// on <DATE>
//
// Interactive program to scan in and calculate 
// details about the weather

#define NUM_TEMPS 4
#define NUM_HUMIDITY 5

#include <stdio.h>


int main(void) {

    // Intro
    printf("Hello and welcome to CS Weather!\n");
    printf("=======================================\n");
    printf("This program will help you to analyse a given weather patten\n");
    printf("and make some predictions about the coming day\n");

    // Read Temperatures
    printf("Please enter the past %d day(s) worth of temperatures.\n", NUM_TEMPS);

    double temps[NUM_TEMPS] = {0.0};
    int counter = 0;
    while (counter < NUM_TEMPS) {
        scanf("%lf", &temps[counter]);
        counter++;
    }

    // Read Humidities
    printf("Please enter the last %d days(s) worth of humidities\n", NUM_HUMIDITY);
    double humidity[NUM_HUMIDITY] = {0.0};
    counter = 0;
    while (counter < NUM_HUMIDITY) {
        scanf("%lf", &humidity[counter]);
        counter++;
    }

    // Get average Temperature
    counter = 0;
    double sum = 0.0;
    while (counter < NUM_TEMPS)
    {
        sum += temps[counter];
        counter++;
    }
    double average_temp = sum / NUM_TEMPS;

    // Get average humidity
    counter = 0;
    sum = 0.0;
    while (counter < NUM_HUMIDITY)
    {
        sum += humidity[counter];
        counter++;
    }
    double average_humidity = sum / NUM_HUMIDITY;

    // Give info about average temp
    printf("The average temperature was: %lf\n", average_temp);
    if (average_temp >= 28.0) {
        printf("It will be hot tomorrow!");
    } else if (average_temp >= 15.0 && average_temp < 28.0 ) {
        printf("Should be a lovely temperature tomorrow.\n");
    } else {
        printf("It'll be chilly tomorrow, pack a jumper!\n");
    }

    // Give info about average humidity
    printf("The average humidity was: %lf\n", average_humidity);
    if (average_humidity > 80.0) {
        printf("It will be humid tomorrow.\n");
    } else {
        printf("Shouldn't be too humid tomorrow.\n");
    }

    return 0;
}