#include <stdio.h>
#include "Moving.h"

char *mover(int number_of_box){
	int truck_A;
	int truck_B;
	if (number_of_box % 23 != 0){
		truck_A = number_of_box / 23 + 1;
	}
	else{
		truck_A = number_of_box / 23;
	}
	if (number_of_box % 30 != 0){
		truck_A = number_of_box / 30 + 1;
	}
	else{
		truck_A = number_of_box / 30; 
	}
	if (200 * truck_A > 260 * truck_B){
		return "Bob";
	}
	else {
		return "Alice";
	}
}

int main(){
	char *result = mover(1);
	printf("%c",result[1]);
}