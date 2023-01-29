.data
list: .word 1 , 2 , 3 , 4 , 5 , 6 , 7  #for testing
.text 
main: 
la $a0, list 
li $a1, 7
li $t0, 2
li $t1, 4
li $t2, 6
#array stores in $a0, length in $a1, 3 values in $t0,$t1,$t2 ascending order, store result in $s0(smaller than all 3),$s1(greater),$s2(t0-t1),$s3(t1-t2)
# loop:(scan through values in array, 4 if statement )
	li $s0, 0  #number of values smaller than t0 
	li $s1, 0  #number of values greater than t2
	li $s2, 0  #number of values in the range t0-t1
	li $s3, 0  #number of values in the range t1-t2

j Cond                  #while loop 
Loop1: 
	lw $t4, ($a0) #store the current value in t4
	li $t5, 3
	li $t6, 3
	blt $t4, $t0, LessThan #check if less than t0
A:	blt $t2, $t4, GreaterThan #check if greater than t2
B:	bge $t4, $t0, Geqt0 #check if geq t0
C:	blt $t4, $t1, Let1  #check if less than t1
D:	bge $t4, $t1, Geqt1 #check if geq t1
E:	blt $t4, $t2, Let2  #check if less than t2
F:	addi $a0, $a0, 4
	addi $a1, $a1, -1   #a1--
	
Cond:
	bne $a1, $zero, Loop1

Exit: 
	jr $ra
	
LessThan:
	addi $s0, $s0, 1
	j F
GreaterThan:
	addi $s1, $s1, 1
	j F
Geqt0:
	li $t5, 1 #set a marker variable
	j C
Let1:
	addi $t5, $t5, -1 #t5 should be 0 if t4 in range t0-t1
	beq $t5, $zero, s2Add1
	j D
Geqt1: 
	li $t6, 1 
	j E
Let2:
	addi $t6, $t6, -1 #t6 should be 0 if t4 in range t1-t2
	beq $t6, $zero, s3Add1
	j F
s2Add1:
	addi $s2, $s2, 1
	j F
s3Add1:
	addi $s3, $s3, 1
	j F