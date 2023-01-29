.data
#caller-callee, not using t and a in callee???
.text
#values-a0(int is 2 byte start at 0,2,4;stores the address of the first value), length-a1(2 byte 0x00FF), decay-a2(2 byte), temp-v0(4 byte)
main:
decaying_sum:
	li $v0, 0 
	addiu $sp, $sp, -32 
	sw $ra, 28($sp)
	sw $fp, 24($sp)
	addiu $fp, $sp, 32
	jal decaying_sum_driver
	lw $fp, 24($sp)
	lw $ra, 28($sp)
	addiu $sp, $sp, 32
	jr $ra 
decaying_sum_driver:
	ble $a1, $zero, Exit #base case, if length<=0, return 
	li $t2, 0 #t2=length after loop2
	j Cond                  #while loop to get address of values[length-1]
Loop2: 
	addi $t2, $t2, 1
Cond:
	blt $t2, $a1, Loop2 #goto Loop2 if t2<length
GetValue: #getting values[length-1] in t3
	addi $t2, $t2, -1 $t2=length-1
	sll $t2, $t2, 1 #t2=t2*2(size)
	add $t2, $t2, $a0 
	lhu $t3, 0($t2) #t3 store the last value in the array values i.e. values[length-1]
Division: #getting temp/decay in t4
	div $v0, $a2
	mflo $t4 #move quotient into t4
New_Temp: 
	add $v0, $t4, $t3
Decrease_Length:
	addi $a1, $a1, -1
Loop1:
	j decaying_sum_driver

Exit:
	jr $ra