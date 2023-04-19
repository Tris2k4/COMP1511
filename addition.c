#include <stdio.h>

int main() {
	int student, tutors, sum;
	printf("Please enter the number of students and tutors: ");
	scanf("%d%d", &student, &tutors);
	sum = student + tutors;
	printf("%d + %d = %d\n", student, tutors, sum);
	return 0;
}
