#include <stdio.h>
#include <stdlib.h>
#include "FindDivisors.h"

int main(){
    int given[4] = {3,6,4,2};
    FindDivisors(given,4);
    printf("%d", divisors[1]);
    printf("%d", dividends[1]);
    free(divisors);
    free(dividends);
    return 0;
}

void FindDivisors(int GivenArray[], int SizeGiven){ 
    int i = 0;
    int k = 0;
    int g = 0;
    int l = 0;
    //to know the size of the two new arrays
    while (i < SizeGiven) {
        k = i + 1;
        while (k < SizeGiven){
            if (GivenArray[i] % GivenArray[k] == 0){
                g += 1;
            }
            k ++;
        }
        i++;
    }
    divisors = (int*) malloc(g * sizeof(int));
    dividends = (int*) malloc(g * sizeof(int));
    i = 0;
    k = 0;
    l = 0;
    //fill values to arrays
    while (i < SizeGiven){
        k = i + 1;
        while (k < SizeGiven){
            if (GivenArray[i] % GivenArray[k] == 0){
                divisors[l] = GivenArray[k];
                dividends[l] = GivenArray[i];
                l ++;
            }
            k ++;
        }
        i++;
    }
}
