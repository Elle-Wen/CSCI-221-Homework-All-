.data

.text
#a0+a1-value, v0-output, f0+f1-input fp number,t0-pointer to the list,t1-length 
main:
	addiu $sp, $sp, -32 
	sw $ra, 28($sp)
	sw $fp, 24($sp)
	addiu $fp, $sp, 32
	li $t2,0 #t2 is i 
	j Cond                  #while loop to go through list 
Loop1: 
	jal Add
	addi $t2, $t2, 1 #i++
Cond:
	blt $t2, $t1, Loop1 #goto Loop1 if i<length
	lw $fp, 24($sp)
	lw $ra, 28($sp)
	addiu $sp, $sp, 32
	sll $a0, $a0, 1 #shift left by 1 to get rid of the sign bit 
	srl $v0, $a0, 21 #shift a0 21 bits to the right to get only the exponent field 
	jr $ra 
Add:
	sll $t3,$t2, 4 #i*16=t3
	add $t3, $t3, $t0 #t3 is current address of the desired value
	lw $t4, ($t3) #t4 is the first half of the value 
	lw $t5, 4($t3) #t5 is the second half of the value 
	mtc1 $t4, $f2 #transfer int to float for float addition later  -f2-upper half 
	mtc1 $t5, $f3 #f3-lower half 
	add.d $f4, $f0, $f2 #f4-f5 is the current sum 
	mfc1 $a0,$f4
	mfc1 $a1,$f5 #now a0,a1 is the value of the resultting floating point 
	jr $ra 
#sudo code:
#while i<length
#	Add(curr,i)
#	i++
#Add:curr=list[i]+curr 