#Abel Philip 
#UID: 117868234
#GRACEID: aphilip2
#Ispalindrome function to check if a word is a palindrome. 
is_palindrome:
    # PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra
    
    li  $t2, 0              #i = 0 Counter Variable 
    move $t1, $a0
    jal  strlen             #call strlen
    move $t0,$v0            #store strlen in t0
 
    move $t1, $a0
    div $t3, $t0, 2      #t3 = strlen/2 The limiter for the for loop
    add $t3, $t3, 1         # adding 1 incase of an even number of digits
   
    
loop:
    bge $t2, $t3, exit      #For loop limit is half 
    lb  $t4, 0($a0)         #get character from beginning

    #Accessing the last element
    sub $t5, $t0, $t2               
    sub $t5, $t5, 1                       
    add $t5, $t5, $t1			        
    lb  $t5, ($t5)         #Loading the last element of           

    beq $t4, $t5, increment            
    li  $v0,  0            #if t4 and t5 are not equal, return 0                
    j   exit

    increment:
        addi  $a0, $a0, 1    #Incrementing the index of a0              
        addi  $t2, $t2, 1    #incrementing i                
        j loop

exit:
    #Epilogue 
    move $sp, $fp           # restore $sp
    lw   $ra, ($fp)         # restore saved $ra
    lw   $fp, -4($sp)       # restore saved $fp
    j    $ra

# strlen(str)

strlen:
   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   subu $sp, $sp, 4
   sw $a0, 4($sp)
   # BODY
   li $t0, 0   # i = 0

   str_loop:
      lb $t1, 0($a0)
      beqz $t1, str_exit
      addi $a0, $a0, 1
      addi $t0, $t0, 1
      j str_loop

      # EPILOGUE
   str_exit :
      lw    $a0, 4($sp)      # Setting the a0 back to the original 
      move $v0, $t0           #   
      move $sp, $fp           # restore $sp
      lw   $ra, ($fp)         # restore saved $ra
      lw   $fp, -4($sp)       # restore saved $fp
      jr    $ra 

 



