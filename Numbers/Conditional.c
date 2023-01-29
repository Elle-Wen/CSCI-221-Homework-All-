#include <stdio.h>
#include "Conditional.h"

int main(){
    printf("%d", Conditional(0,21,22));
    
}
int Conditional(int x, int y, int z){
    int bool = 1 && x; 
    return (bool * y + (1 - bool) * z); 
}
