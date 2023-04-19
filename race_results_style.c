// 
// Written INSERT-DATE-HERE
// By INSERT-AUTHOR-HERE
//
// INSERT-DESCRIPTION-HERE
//

#include <stdio.h>


#define MAX_CARS 20

struct race_result {
    // TODO: fill this in with the details of the result of a single car in the
    // race.
    //
    // i.e. This struct should contain:
    //      the car number (int), 
    //      and the race time (double).
};


// Prints the race result in the correct format.
void print_result(int car_number, double race_time);

int main(void) {

    // TODO: Declare an array of structs of size MAX_CARS

    printf("How many cars in the race? ");
    // TODO: scan in number of cars in the race

    printf("Enter results:\n");
    // TODO: scan in the details of each car into the array

    printf("Results:\n");
    // TODO: print all the results

    return 0;
}


//  Prints the race result in the correct format.
//
// Parameters:
// - `car_number` -- The car number of the result
// - `race_time` -- The time the car took to finish the race.
//
// Returns: nothing.
void print_result(int car_number, double race_time) {
    
    printf("%2d: %.2lf\n", car_number, race_time);
}

