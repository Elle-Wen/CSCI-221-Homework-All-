#include <stdint.h>
#include <stdio.h>
#include "FloatMulti.h"

uint8_t FloatMulti(uint8_t x1, uint8_t x2){
    int s1 = (int)((x1 & 0x80) ? 1 : 0); //sign of x1 0000.. 1 or 0000.. 0
    int s2 = (int)((x2 & 0x80) ? 1 : 0); //sign of x2
    int exp1 = (int)((x1 & 0x78) >> 3); // 0000.. xxxx
    int exp2 = (int)((x2 & 0x78) >> 3); // 0000.. xxxx
    int leading_number1 = (int)(exp1 ? 1 : 0); // normalized then 1, denormalized then 0 
    int leading_number2 = (int)(exp1 ? 1 : 0);
    int E1 = (int)(leading_number1 ? (exp1 - 7) : -6); // denormalized is -6, range is  8 to -6. bias is 7 
    int E2 = (int)(leading_number2 ? (exp2 - 7) : -6);
    int M1 = (int)((leading_number1 == 1) ? ((x1 & 0x07) + 0x08) : (x1 & 0x07)) ; // 0000... 1xxx or 0000... 0xxx
    int M2 = (int)((leading_number2 == 1) ? ((x2 & 0x07) + 0x08) : (x2 & 0x07)) ;
    int M = M1 * M2; 
    int E = E1 + E2; 
    int s = s1 ^ s2;
    while (M >= 16){
        int M_lst = M & 0x00000001; //0000.. 000x
        int M_2lst = M & 0x00000002; //0000.. 00x0
        if (M_lst == 0){
            M = M >> 1;  // no need to round, just cut it
        }
        else{ //roud to nereast 1/8, apply tie rule,  M_lst == 1
            if (M_2lst == 1){ //round up
                M = (M >> 1) + 1;
            }
            else{ //round down
                M = M >> 1;
            }
        }
        E ++; 
    }
    while (M < 8){ //M = 000.. 0xxx
        M = M << 1;
        E --; 
    } 
    // E overflow
    if ((E > 8) || (E < -6)){
        E = (E + 7) % 15 - 7; 
    }
    else if (E == -6){ //denormal
        E = -7;
    }
    uint8_t sign = (uint8_t) s << 7; //x000 0000
    uint8_t sig = (uint8_t) M & 0x07; // 0000 0xxx
    int exp_prime = E + 7;
    uint8_t exp = (uint8_t) exp_prime << 3;
    return  sign + sig + exp; 
}
int main(){

}
