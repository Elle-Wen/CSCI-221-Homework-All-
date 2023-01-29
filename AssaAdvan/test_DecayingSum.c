#include<stdint.h>
#include<stdio.h>
uint32_t decaying_sum(uint16_t* values, uint16_t length, uint16_t decay){
	if (length <= 0){
	return 0;
	}
	uint32_t rest = decaying_sum(&values[1], length-1, decay);
	uint32_t decayed = rest / decay;
	return values[0] + decayed;
}

int main(){
	uint32_t a;
	uint16_t values[3] = {1,3,4};
	uint16_t length = 3;
	uint16_t decay = 2;
	a = decaying_sum( values, length, decay);
	printf("%d",a);
}