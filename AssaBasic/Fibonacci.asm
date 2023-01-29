.data

.text

main:
	li $a0, 5 #I set a0 to be 5 to test 
	li $t0, 1
	li $v0, 1
	beq $a0, $t0, Exit
	li $t0, 2
	beq $a0, $t0, Exit

	li $t1, 1 #pre1
	li $t2, 1 #pre2
	li $v0, 1 #curr
	addi $a0, $a0, -2

j Cond                  #while loop 
Loop1: 
	addu $v0, $t1, $t2
	move $t2, $t1
	move $t1, $v0
	addi $a0, $a0, -1
	
Cond:
	bne $a0, $zero, Loop1

Exit: 
	jr $ra  #at this point, v0 should be our result! 
	
#I did a translation of this code I wrote in C below: 
#int fib(int n){
#	if (n == 1){
#		return 1;
#	}
#	else if (n == 2){
#		return 1;
#	}
#	int previous1 = 1;
#	int previous2 = 1;
#	int current;
#	n = n-2;
#	while (n!= 0){
#		current = previous1 + previous2;
#		previous2 = previous1; 
#		previous1 = current;
#		n--;
#	}
#	return current;
#}

	

