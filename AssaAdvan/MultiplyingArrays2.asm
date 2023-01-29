.data

.text
#t0-x,t1-y,v0-upper half of xy,v1-lower half of xy
#a0-length, a1-pointer of first array of 32 bit int ,a2-pointer of second array of 32 bit int, a3-pointer of 64 bit int
main:
Array_Multiplication:
	li $t8, 0 #i 
	move $t9, $t8 $have a copy of i 
	j Cond                  #while loop 
Loop1: 
	#getting the address of i
	sll $t8, $t8, 2 #i=i*4 
	#to get t0
	add $t2, $a1, $t0 #t2 is the address of value1[i]
	lw $t0, 0($t2)
	#to get t1
	add $t3, $a2, $t0 #t3 is the address of value1[i]
	lw $t1, 0($t3)
	#setting the stack 
	addiu $sp, $sp, -32 
	sw $ra, 28($sp)
	sw $fp, 24($sp)
	addiu $fp, $sp, 32
	jal Multiplication #call Multiplication
	lw $fp, 24($sp)
	lw $ra, 28($sp)
	addiu $sp, $sp, 32
	addi $t9, $t9, 1 #i++
Cond:
	blt $t9, $a0, Loop1 #goto Loop1 if t0<length
jr $ra 
Multiplication:
	mult $t0, $t1 
	mfhi $t4
	mflo $t5 
	#getting address of array3[i]=t6
	sll $t7, $t8, 3 #i*8
	add $t6, $t7, $t8 
	sw $t4, ($t6)
	sw $t5, 4($t6)
	jr $ra 

