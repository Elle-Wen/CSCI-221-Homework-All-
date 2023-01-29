.data 
array: .word 100, 110, 120
permutation: .word 1 , 2 , 0
#110, 100, 120#110,120,100#100,120,110
.text 
#array-a0, permutation-a1, length-a2, swaping the value store in x and y 
main:
la $a0, array 
la $a1, permutation 
li $a2, 3
li $t0, 0 #stands as i 
move $t4, $a0 #copy the address of array
j Cond                  #while loop 
Loop1: 
	lw $t1, 0($a0) #t1 stores first value 
	lw $t2, 0($a1) #t2 stores permutation(i)
	sll $t2, $t2, 2 #left shift t2 for *4  
	add $t3, $t2, $t4 #t3 stores the address of array[permutation[i]], need to *4, t3 = t2*4 + t4 
	lw $t5, 0($t3) #stores the second value 
	addi $t0, $t0, 1 #increment i 
	sw $t1, 0($t3) #store the first value at second address 
	sw $t5, 0($a0) #store the second value at the first address 
	addi $a1, $a1, 4 #move address of permutation(i)
	addi $a0, $a0, 4 #move address of array(i) 
Cond:
	blt $t0, $a2, Loop1 
Testing:
	lw $t6, 0($t4)
	lw $t7, 4($t4)
	lw $t8, 8($t4)
Exit: 
	jr $ra