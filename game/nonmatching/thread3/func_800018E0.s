glabel func_800018E0
  /* 0024E0 800018E0 3C0E8004 */       lui $t6, %hi(D_80044ECC)
  /* 0024E4 800018E4 8DCE4ECC */        lw $t6, %lo(D_80044ECC)($t6)
  /* 0024E8 800018E8 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 0024EC 800018EC AFBF0014 */        sw $ra, 0x14($sp)
  /* 0024F0 800018F0 11C0000E */      beqz $t6, .L8000192C
  /* 0024F4 800018F4 AFA40020 */        sw $a0, 0x20($sp)
  /* 0024F8 800018F8 0C00CA48 */       jal osSpTaskYield
  /* 0024FC 800018FC 00000000 */       nop 
  /* 002500 80001900 3C028004 */       lui $v0, %hi(D_80044ECC)
  /* 002504 80001904 24424ECC */     addiu $v0, $v0, %lo(D_80044ECC)
  /* 002508 80001908 8C580000 */        lw $t8, ($v0) # D_80044ECC + 0
  /* 00250C 8000190C 240F0004 */     addiu $t7, $zero, 4
  /* 002510 80001910 AF0F0008 */        sw $t7, 8($t8)
  /* 002514 80001914 0C000351 */       jal func_80000D44
  /* 002518 80001918 8C440000 */        lw $a0, ($v0) # D_80044ECC + 0
  /* 00251C 8000191C 8FA80020 */        lw $t0, 0x20($sp)
  /* 002520 80001920 24190003 */     addiu $t9, $zero, 3
  /* 002524 80001924 1000000A */         b .L80001950
  /* 002528 80001928 AD190008 */        sw $t9, 8($t0)
  .L8000192C:
  /* 00252C 8000192C 8FA40020 */        lw $a0, 0x20($sp)
  /* 002530 80001930 24840028 */     addiu $a0, $a0, 0x28
  /* 002534 80001934 0C00C1B3 */       jal osSpTaskLoad
  /* 002538 80001938 AFA4001C */        sw $a0, 0x1c($sp)
  /* 00253C 8000193C 0C00C217 */       jal osSpTaskStartGo
  /* 002540 80001940 8FA4001C */        lw $a0, 0x1c($sp)
  /* 002544 80001944 8FAA0020 */        lw $t2, 0x20($sp)
  /* 002548 80001948 24090002 */     addiu $t1, $zero, 2
  /* 00254C 8000194C AD490008 */        sw $t1, 8($t2)
  .L80001950:
  /* 002550 80001950 8FBF0014 */        lw $ra, 0x14($sp)
  /* 002554 80001954 8FAB0020 */        lw $t3, 0x20($sp)
  /* 002558 80001958 3C018004 */       lui $at, %hi(D_80044ECC)
  /* 00255C 8000195C 27BD0020 */     addiu $sp, $sp, 0x20
  /* 002560 80001960 03E00008 */        jr $ra
  /* 002564 80001964 AC2B4ECC */        sw $t3, %lo(D_80044ECC)($at)
