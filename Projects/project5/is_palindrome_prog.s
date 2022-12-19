   .data
str1:
   .asciiz "abba"
str2:
   .asciiz "racecar"
str3:
   .asciiz "swap paws",
str4:
   .asciiz "not a palindrome"
str5:
   .asciiz "another non palindrome"
str6:
   .asciiz "almost but tsomla"

# array of char pointers = {&str1, &str2, ..., &str6}
ptr_arr:
   .word str1, str2, str3, str4, str5, str6, 0

yes_str:
   .asciiz " --> Y\n"
no_str:
   .asciiz " --> N\n"

   .text

# main(): ##################################################
#   char ** j = ptr_arr
#   while (*j != 0):
#     rval = is_palindrome(*j)
#     printf("%s --> %c\n", *j, rval ? yes_str: no_str)
#     j++
#
main:
   li   $sp, 0x7ffffffc    # initialize $sp

   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   subu $sp, $sp, 8        # save s0, s1 on stack before using them
   sw   $s0, 8($sp)        # push $s0
   sw   $s1, 4($sp)        # push $s1

   la   $s0, ptr_arr        # use s0 for j. init ptr_arr
main_while:
   lw   $s1, ($s0)         # use s1 for *j
   beqz $s1, main_end      # while (*j != 0):
   move $a0, $s1           #    print_str(*j)
   li   $v0, 4
   syscall
   move $a0, $s1           #    v0 = is_palindrome(*j)
   jal  is_palindrome
   beqz $v0, main_print_no #    if v0 != 0:
   la   $a0, yes_str       #       print_str(yes_str)
   b    main_print_resp
main_print_no:             #    else:
   la   $a0, no_str        #       print_str(no_str)
main_print_resp:
   li   $v0, 4
   syscall

   addu $s0, $s0, 4       #     j++
   b    main_while        # end while
main_end:

   # EPILOGUE
   move $sp, $fp           # restore $sp
   lw   $ra, ($fp)         # restore saved $ra
   lw   $fp, -4($sp)       # restore saved $fp
   j    $ra                # return to kernel
# end main ################################################

is_palindrome:
    # PROLOGUE
    subu $sp, $sp, 8        # expand stack by 8 bytes
    sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
    sw   $fp, 4($sp)        # push $fp (4 bytes)
    addu $fp, $sp, 8        # set $fp to saved $ra
    
   

    jal     strlen                              #call strlen
    move    $t0,    $v0                         #store strlen in t0
 
    move    $t1, $a0
    div     $t3,    $t0,    2                   #t3 = strlen/2 The limiter for the for loop
    
    li      $t2,    0                           #i = 0 Counter Variable 
    
loop:
    bge     $t2,    $t3,     exit               #For loop limit is half 
    lb      $t4,    0($a0)                      #get character from beginning

    sub     $t5,    $t0,    $t2
    sub     $t5,    $t5, 1                       
    add 	$t5,    $t5,    $t1			        
    lb      $t5,    ($t5)                      #Accessing last elem            

    beq     $t4,    $t5,    increment           
    li      $v0,    0                           
    j       exit

    increment:
        addi    $a0,    $a0,    1                  
        addi    $t2,    $t2,    1                   
        j       loop

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

 



