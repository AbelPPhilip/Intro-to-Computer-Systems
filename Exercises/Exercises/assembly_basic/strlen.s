# strlen(str)

strlen:
   # PROLOGUE
   subu $sp, $sp, 8        # expand stack by 8 bytes
   sw   $ra, 8($sp)        # push $ra (ret addr, 4 bytes)
   sw   $fp, 4($sp)        # push $fp (4 bytes)
   addu $fp, $sp, 8        # set $fp to saved $ra

   # BODY
   li $t0, 0   # i = 0
   j loop 
   
   loop:
      lb $t1, 0($a0)
      beqz $t1, exit 
      addi $a0, $a0, 1
      addi $t0, $t0, 1 
      j loop
   # EPILOGUE
   exit :
      move $v0, $t0
      move $sp, $fp           # restore $sp
      lw   $ra, ($fp)         # restore saved $ra
      lw   $fp, -4($sp)       # restore saved $fp
      j    $ra 


   
