#include<stdint.h>
#include<stdio.h>
uint32_t decaying_sum_driver(uint16_t* values, uint16_t length, uint16_t decay, uint32_t temp){
	if (length <= 0){
		return temp; 
	}
	temp = values[length-1]+temp/decay; 
	length = length - 1;
	return decaying_sum_driver( values, length, decay, temp);
}
uint32_t decaying_sum(uint16_t* values, uint16_t length, uint16_t decay){
	decaying_sum_driver( values, length, decay,0);
}
int main(){
	uint32_t a;
	uint16_t values[3] = {1,3,4};
	uint16_t length = 3;
	uint16_t decay = 2;
	a = decaying_sum( values, length, decay);
	printf("%d",a);
}
