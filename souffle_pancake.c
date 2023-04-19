//This program calculates how many resources you will need to cook any given amount of souffle pancakes!

#include <stdio.h>

//Function prototypes
double divide(double top, double bottom);
int ceiling(double num);
void print_time(int minutes);

int main() {
  //Variables for recipe
  double eggs_per_pancake = divide(2, 3);
  double sugar_per_pancake = divide(10, 3);
  double flour_per_pancake = divide(8, 3);

  //Variables for user input
  int num_pancakes;
  printf("How many souffle pancakes do you want to make? ");
  scanf("%d", &num_pancakes);

  //Calculations
  double eggs_needed = eggs_per_pancake * num_pancakes;
  double sugar_needed = sugar_per_pancake * num_pancakes;
  double flour_needed = flour_per_pancake * num_pancakes;

  //Output
  printf("You will need:\n");
  printf("- %.0f eggs\n", eggs_needed);
  printf("- %.0fg sugar\n", sugar_needed);
  printf("- %.0fg flour\n", flour_needed);

  //Calculate frying time
  int frying_time = ceiling(num_pancakes * 2.5);
  print_time(frying_time);

  return 0;
}

//Function to divide two doubles
double divide(double top, double bottom) {
  return top / bottom;
}

//Function to round up a given double to the closest integer
int ceiling(double num) {
  int int_part = (int) num;
  double frac_part = num - int_part;

  if (frac_part > 0) {
    int_part++;
  }

  return int_part;
}

//Procedure to print out the time in hours and minutes
void print_time(int minutes) {
  int hours = minutes / 60;
  int remaining_minutes = minutes % 60;

  printf("Frying will take you %d hours and %d minutes.\n", hours, remaining_minutes);
}
