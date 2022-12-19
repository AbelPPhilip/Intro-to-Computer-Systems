#Abel Philip 
#UID: 117868234
#GRACEID: aphilip2
#Reverse_prefix_sum function 

reverse_prefix_sum:
    #Prologue 
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra
    
    lw      $t1, ($a0)      #setting pointer to first element in the array
    bne     $t1, -1, recur  #if the dereference arr is not equal to -1 it branch to recur
    move $v0, $zero
    j exit
recur:
    subu    $sp, $sp, 4     # grow stack to store the pointer
    sw      $t1, 4($sp)     # storing the current pointer value to stack 
    addi    $a0, $a0, 4     #pointer++
    jal     reverse_prefix_sum  # recursive call 
    lw      $t1, 4($sp)     # load the original pointer dereferenced
    addu    $t1, $v0, $t1   # adding parameter of the recursive call to t1    
    move    $v0, $t1        #return (r)
    sub     $a0, $a0, 4     #Setting a0 back to the start
    sw      $t1, ($a0)      #Setting t1 back to the start of the array 
    addu    $sp, $sp, 4     #Shrinking the stack
    j exit                  #jump to epilogue
    
exit:
    move $sp, $fp           # restore $sp
    lw   $ra, ($fp)         # restore saved $ra
    lw   $fp, -4($sp)       # restore saved $fp
    j    $ra                # jump ra 
