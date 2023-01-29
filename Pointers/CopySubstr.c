#include <stdio.h>
#include <stdlib.h>
#include "CopySubstr.h"
void CopySubstr(char* str, int start, int end){
    int new_length = end - start;
    copysub = (char*) malloc(new_length * sizeof(char));
    int i =0;
    for (i = 0; i < new_length; i++){
        copysub[i] = str[start + i];
    }
}
int main(){
    CopySubstr("yahelloyaya", 2,7);
    printf("%s", copysub);
    free(copysub);
    return 0;
}
