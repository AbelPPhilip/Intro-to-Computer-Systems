#Abel Philip 
#UID: 117868234
#GRACEID: aphilip2
#checking if a number is a sqrt
isqrt:
    #Epilogue 
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra

    bge $a0, 2, recur       # if a0>2, else 
    move $v0, $a0           # return n if n<2
    j exit


recur:
    subu $sp, $sp  4        #grow stack
    sw $a0, 4($sp)          #store a0 to stack

    srl $a0, $a0, 2         #n>>2
    jal isqrt
    sll $t0, $v0, 1         #small

    addi $t1, $t0, 1        #large 

    mul $t2, $t1, $t1       #large*large 
    lw  $a0, 4($sp)         #loading the original a0 value from stack
    addu $sp, $sp, 4        #Closing the stack
    bgt		$t2, $a0, return_small	# if $t2 > $a0 then target
    move $v0, $t1           #return large
    j exit

    return_small:
        move $v0, $t0       #return small
        j exit


exit:
    move $sp, $fp           # restore $sp
    lw   $ra, ($fp)         # restore saved $ra
    lw   $fp, -4($sp)       # restore saved $fp
    j    $ra 
    