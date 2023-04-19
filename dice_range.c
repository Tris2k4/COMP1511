#include <stdio.h>
#include <math.h>
int main() {
    int faces, rolled, a;
    float b;
    printf("Enter the number of sides on your dice: ");
    scanf("%d", &faces);
    printf("Enter the number of dice being rolled: ");
    scanf("%d", &rolled);

    if (faces > 0 && rolled > 0) {
        a = rolled * faces;
        b = (rolled + a) / 2;
        printf("Your dice range is %d to %d.\n", rolled, a);
        printf("The average value is %f\n", b);
    } else if (faces < 0 && rolled > 0) {
        printf("These dice will not produce a range.\n");
    } else if (faces > 0 && rolled < 0) { 
        printf("These dice will not produce a range.\n");
    } else {
         printf("These dice will not produce a range.\n");

    }
    return 0;
}

