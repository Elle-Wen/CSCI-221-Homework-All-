#include <stdio.h>
#include "Negation.h"

int main(){
    printf("%d", Negation(103));
}

int Negation(int x){
    int result = (1 && x)^1;
    return result; 
}
