#include <stdint.h>
#include <stdio.h>
#include "AddFloat.h"
/*
uint8_t AddFloat(uint8_t x, uint8_t y){ // x=0 0000 000 y=0 0000 000
    // both normalized input:
    uint8_t sign_x = x & 0x80; //get 1 0000 000 if x is negative, 0 0000 000 if x is positive/zero
    uint8_t sign_y = y & 0x80; 
    uint8_t sign_result; 
    uint8_t exp_x = x & 0x78; //get 0 xxxx 000
    uint8_t exp_y = y & 0x78; 
    uint8_t exp_result;
    uint8_t sig_x = x & 0x07; //get 0 0000 xxx 
    uint32_t Mx = ((uint32_t) sig_x) << 24 + 0x08000000; //get 0000 1xxx 0000 0000 0000 0000 0000 0000 (cuz the max possible rshift is 15)
    uint32_t Mx_align; 
    uint8_t sig_y = y & 0x07; 
    uint32_t My = ((uint32_t) sig_y) << 24 + 0x08000000;
    uint32_t My_align; 
    uint32_t M_new; // abs value
    uint32_t sig_result_32b; 
    uint8_t sig_result;
    // determine the sign of the result:
    if (exp_x > exp_y){
        sign_result = sign_x;
    }
    else if (exp_y > exp_x){
        sign_result = sign_y;
    }
    else{ // equal exp, then compare significand 
        if (sig_x > sig_y){
            sign_result = sign_x;
        }
        else if (sig_y > sig_x){
            sign_result = sign_y;
        }
        else{ //equal significand, equal exp
            if (sign_x == sign_y){
                sign_result = sign_x; // take either
            }
            else{ //opp sign
                return 0;
            }
            
        }
    }
    // determine the significand of the result:
    if (exp_x >= exp_y){
        My_align = My >> (exp_x - exp_y);
        if (sign_x == sign_y){
            M_new = My_align + Mx;
        }
        else{ // x and y not the same sign
            M_new = Mx - My_align; 
        }
        if (M_new >= 0x10000000){ //M_new >= 0001 0000 0000 0000 0000 0000 0000 0000
            exp_result = exp_x + 1; //increment exp 
            sig_result_32b = M_new & 0x0FFFFFFF // get rid of leading 1 
            // rounding 
        }

    }
}

int main(){
}
*/

uint8_t AddFloat(uint8_t x1, uint8_t x2){ //(-1)^s * M * 2^E   /  input is x xxxx xxx 
    int s1 = (int)((x1 & 0x80) ? 1 : 0); //sign of x1 
    int s2 = (int)((x2 & 0x80) ? 1 : 0); //sign of x2
    int exp1 = (int)((x1 & 0x78) >> 3); // 0000.. xxxx
    int exp2 = (int)((x2 & 0x78) >> 3); // 0000.. xxxx
    int leading_number1 = (int)(exp1 ? 1 : 0); // normalized then 1, denormalized then 0 
    int leading_number2 = (int)(exp1 ? 1 : 0);
    int E1 = (int)(leading_number1 ? (exp1 - 7) : -6); // denormalized is -6, range is  8 to -6. bias is 7 
    int E2 = (int)(leading_number2 ? (exp2 - 7) : -6);
    int M1 = (int)((leading_number1 == 1) ? ((x1 & 0x07) + 0x08) : (x1 & 0x07)) ; // 0000... 1xxx or 0000... 0xxx
    int M2 = (int)((leading_number2 == 1) ? ((x2 & 0x07) + 0x08) : (x2 & 0x07)) ;
    int M = 0;
    int E = E1 >= E2 ? E1 : E2; //initial value is the max of E1, E2 
    int s;
    // determine s:
    if (exp1 > exp2){
        s = s1;
    }
    else if (exp2 > exp1){
        s = s2;
    }
    else{ // equal exp, then compare significand 
        if (M1 > M2){
            s = s1;
        }
        else if (M2 > M1){
            s = s2;
        }
        else{ //equal significand, equal exp
            if (s1 == s2){
                s = s1; // take either
            }
            else{ //opp sign
                return 0;
            }
        }
    }
    // determine M:
    // align
    if (exp1 > exp2){
        M2 = M2 >> (exp1 - exp2);
    }
        
    else if (exp2 > exp1){
        M1 = M1 >> (exp2 - exp1);
    }
    // add 
    if (s1 == s2){
        M = M1 + M2; 
    } 
    else{
        if (exp1 > exp2){
            M = M1 - M2;
        }
        else if (exp2 > exp1){
            M = M2 -M1;
        }
        else{
            if (M1 > M2){
                M = M1 - M2;
            }
            else if (M2 > M1){
                M = M2 - M1; 
            }
        }
    }
    // fixing
    while (M >= 16){ //increment E if M = 000.. 1 xxxx
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
        if (E > 8){ //mod
            E = -7; 
        }
    }
    while (M < 8){ //M = 000.. 0xxx
        M = M << 1;
        E --; 
        if (E < -6){ //mod
            E = 8;
        }
    } 
    if (E == -6){ //denormal
        E = -7;
    uint8_t sign = (uint8_t) s << 7; //x000 0000
    uint8_t sig = (uint8_t) M & 0x07; // 0000 0xxx
    int exp_prime = E + 7;
    uint8_t exp = (uint8_t) exp_prime << 3;
    return  sign + sig + exp; 
}
int main(){

}
