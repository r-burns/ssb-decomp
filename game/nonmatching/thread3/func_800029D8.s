glabel func_800029D8
  /* 0035D8 800029D8 240E0001 */     addiu $t6, $zero, 1
  /* 0035DC 800029DC 3C018004 */       lui $at, %hi(D_80045020)
  /* 0035E0 800029E0 AC2E5020 */        sw $t6, %lo(D_80045020)($at)
  /* 0035E4 800029E4 27BDFFE0 */     addiu $sp, $sp, -0x20
  /* 0035E8 800029E8 3C013F80 */       lui $at, (0x3F800000 >> 16) # 1.0
  /* 0035EC 800029EC AFBF001C */        sw $ra, 0x1c($sp)
  /* 0035F0 800029F0 44816000 */      mtc1 $at, $f12 # 1.0 to cop1
  /* 0035F4 800029F4 AFB10018 */        sw $s1, 0x18($sp)
  /* 0035F8 800029F8 0C00E4B8 */       jal osViSetYScale
  /* 0035FC 800029FC AFB00014 */        sw $s0, 0x14($sp)
  /* 003600 80002A00 0C00CA18 */       jal osViBlack
  /* 003604 80002A04 24040001 */     addiu $a0, $zero, 1
  /* 003608 80002A08 00008025 */        or $s0, $zero, $zero
  /* 00360C 80002A0C 24110004 */     addiu $s1, $zero, 4
  .L80002A10:
  /* 003610 80002A10 0C00112D */       jal func_800044B4
  /* 003614 80002A14 02002025 */        or $a0, $s0, $zero
  /* 003618 80002A18 0C001125 */       jal func_80004494
  /* 00361C 80002A1C 02002025 */        or $a0, $s0, $zero
  /* 003620 80002A20 26100001 */     addiu $s0, $s0, 1
  /* 003624 80002A24 1611FFFA */       bne $s0, $s1, .L80002A10
  /* 003628 80002A28 00000000 */       nop 
  /* 00362C 80002A2C 0C00CD48 */       jal osAfterPreNMI
  /* 003630 80002A30 00000000 */       nop 
  /* 003634 80002A34 8FBF001C */        lw $ra, 0x1c($sp)
  /* 003638 80002A38 3C018004 */       lui $at, %hi(D_80045024)
  /* 00363C 80002A3C 8FB00014 */        lw $s0, 0x14($sp)
  /* 003640 80002A40 8FB10018 */        lw $s1, 0x18($sp)
  /* 003644 80002A44 AC225024 */        sw $v0, %lo(D_80045024)($at)
  /* 003648 80002A48 03E00008 */        jr $ra
  /* 00364C 80002A4C 27BD0020 */     addiu $sp, $sp, 0x20

  /* 003650 80002A50 3C018004 */       lui $at, %hi(D_80045018)
  /* 003654 80002A54 03E00008 */        jr $ra
  /* 003658 80002A58 AC245018 */        sw $a0, %lo(D_80045018)($at)

  /* 00365C 80002A5C 00000000 */       nop 