.data
JumpTable: 
.word L0
.word L1
.word L2 
.word L3 
.word L4 
.word L5 
.word L6
SUNDAY: .ascii "SUNDAY"
MONDAY: .ascii "MONDAY"
TUESDAY: .ascii "TUESDAY"
WEDNESDAY: .ascii "WEDNESDAY"
THURSDAY: .ascii "THURSDAY"
FRIDAY: .ascii "FRIDAY"
SATURDAY: .ascii "SATURDAY"
.text 
#a0-pointer to a list of 10 char, a1-enum(only valid if 0-6)
main:
DaysofWeek:
	li $v0, 0
	la $t0, JumpTable #t0 is the start address of the jump table 
	bltz, $a1, Exit #exit if a1<0
	slti $v0, $a1, 6 #set v0 to be 0 if a1>6, 1 if a1<6
	beq $v0, $zero, Exit 
	sll $a1, $a1, 2 #a1=a1*4
	add $t0, $t0, $a1 #t0 is the address of label  
	lw $t1, 0($t0) #get the label in t1 
	jr $t1 #jump #ra??????
 
#check if enum is in range 
#if not, set v0 to be 0 and quit 
#if is, using jumptable 
#case0: set the list to be the word 
L0:
	la $t2, SUNDAY #pointer to the first value in SUNDAY 
	li $t3, 6 #length
	j loop
L1:
	la $t2, MONDAY 
	li $t3, 6 #length
	j loop
L2:
	la $t2, TUESDAY 
	li $t3, 7 #length
	j loop
L3:
	la $t2, WEDNESDAY 
	li $t3, 9 #length
	j loop
L4:
	la $t2, THURSDAY  
	li $t3, 8 #length
	j loop
L5:
	la $t2, FRIDAY 
	li $t3, 6 #length
	j loop
L6:
	la $t2, SATURDAY 
	li $t3, 8 #length
	j loop 
loop:
	li $t4, 0 #$t4 is index 
	j Cond                 
Loop1: 
	lw $t5, 0($t2) #t5 stores the first character 
	sw $t5, 0($a0)
	addi $t2, $t2, 4 #move t2 
	addi $a0, $a0, 4
	addi $t4, $t4, 1 #t4++
Cond:
	blt $t4, $t3, Loop1
	sw $zero, 0($a0) #setting the null char at the end 
Exit:
	jr $ra
	