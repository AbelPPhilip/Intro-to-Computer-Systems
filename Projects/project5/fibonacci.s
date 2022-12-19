#Abel Philip 
#UID: 117868234
#GRACEID: aphilip2
#Providing the sum of the fibonacci sequence 
fibonacci:
    # PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra
    # Body
    bgt $a0, 1, recur       # if a0>1 branch to recur 
    move $v0, $a0           #return a0
    j exit

recur: 
    subu $sp, $sp 8
    sw $a0, 8($sp)          #Storing the passed in argument to stack
    
    sub  $a0, $a0, 1        #n-1 
    jal  fibonacci          # fib(n-1)
    lw   $a0, 8($sp)        #reloading a0 with the original value 
    sw   $v0, 4($sp)        # store return value to stack 

    sub  $a0, $a0, 2       # Substracting -2 from n 
    jal  fibonacci          #calling  fib(n-2)
    lw   $t0, 4($sp)        #Retrieving the fibonacci(n-1) value 
    add  $v0 , $t0, $v0     #fibonacci(n-1) + fibonacci(n-2)
    addi  $sp, $sp, 8         #Close the stack 
    j exit

    #Epilogue 
exit: 
    move $sp, $fp           # restore $sp
    lw   $ra, ($fp)         # restore saved $ra
    lw   $fp, -4($sp)       # restore saved $fp
    j    $ra                # return to kernel
