#include <stdio.h>
#include "FindStrings.h"

char* FindStr(char* str1, char* str2, int size1, int size2){
    int i = 0;
    int g = 0;
    int l = 0;
    int first_position = 0;
    for (i = 0; i < size1; i++){
        l = 0;
        for (g = 0 ; g < size2 ; g++)
            if (str1[i + g] == str2[g]){
                if (g == 0){
                    first_position = i;
                }
                l ++;
                if (l == size2){
                    return (str1 + first_position);
                }
            }
    }
    
    return ( str1 + size1 - 1);
}

int main(){
    char* str1 = "Hello";
    char* str2 = "k";
    printf("%s", FindStr(str1, str2,5,2));
    return 0;
}
