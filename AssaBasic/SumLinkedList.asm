.data 

.text 
#a0-pointer to the first node  v0-sum of all values. node:2 byte int + 4 byte pointer to next node 
main:
#this does not consider the empty linked list case
li $v0, 0
j Cond                  #while loop 
Loop1: 
	lh $t1, 0($a0) #store value 
	add $v0 $t1, $v0 #updating sum
	lw $a0, 4($a0) 
Cond:
	bne $a0, $zero, Loop1 
Exit: 
	jr $ra