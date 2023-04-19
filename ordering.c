#include <stdio.h>

int main() {
	int number_1, number_2, number_3, small, middle, large;
	printf("Enter integer: ");
	scanf("%d", &number_1);
	printf("Enter integer: ");
	scanf("%d", &number_2);
	printf("Enter integer: ");
	scanf("%d", &number_3);


// consider the first case where as a <= b <= c 
	if (number_1 <= number_2 && number_3 >= number_1) {
		small = number_1;
		// next we consider whether b <= c || c <= b
		if (number_2 <= number_3) {
		middle = number_2;
		large = number_3;
		} else {
			middle = number_3;
			large = number_2;
		}
		// consider the second case where b <= a <= c 
	} else if (number_2 <= number_1 && number_3 >= number_2) {
		small = number_2;
		// similarly, consider the case whether a <= c || c <= a 
		if (number_1 <= number_3) {
			middle = number_1;
			large = number_3;
		} else {
			middle = number_3;
			large = number_1;
		}
		// lastly, consider the third case which is c <= b <= a
	} else {
		small = number_3;
		// consider where b <= a || a <= b
		if(number_2 <= number_1) {
			middle = number_2;
			large = number_1;
		} else {
			middle = number_1;
			large = number_2;
		}
	}
	printf("The integers in order are: %d %d %d \n", small, middle, large);
	return 0;



}
