.section .text
glabel func_80003DD4
  /* 0049D4 80003DD4 27BDFFC8 */     addiu $sp, $sp, -0x38
  /* 0049D8 80003DD8 AFB70030 */        sw $s7, 0x30($sp)
  /* 0049DC 80003DDC 3C178004 */       lui $s7, %hi(D_800450F0)
  /* 0049E0 80003DE0 26F750F0 */     addiu $s7, $s7, %lo(D_800450F0)
  /* 0049E4 80003DE4 AFBF0034 */        sw $ra, 0x34($sp)
  /* 0049E8 80003DE8 AFB6002C */        sw $s6, 0x2c($sp)
  /* 0049EC 80003DEC AFB50028 */        sw $s5, 0x28($sp)
  /* 0049F0 80003DF0 AFB40024 */        sw $s4, 0x24($sp)
  /* 0049F4 80003DF4 AFB30020 */        sw $s3, 0x20($sp)
  /* 0049F8 80003DF8 AFB2001C */        sw $s2, 0x1c($sp)
  /* 0049FC 80003DFC AFB10018 */        sw $s1, 0x18($sp)
  /* 004A00 80003E00 AFB00014 */        sw $s0, 0x14($sp)
  /* 004A04 80003E04 0C00C7DC */       jal osContStartReadData
  /* 004A08 80003E08 02E02025 */        or $a0, $s7, $zero
  /* 004A0C 80003E0C 02E02025 */        or $a0, $s7, $zero
  /* 004A10 80003E10 00002825 */        or $a1, $zero, $zero
  /* 004A14 80003E14 0C00C084 */       jal osRecvMesg
  /* 004A18 80003E18 24060001 */     addiu $a2, $zero, 1
  /* 004A1C 80003E1C 3C048004 */       lui $a0, %hi(D_80045188)
  /* 004A20 80003E20 0C00C7FD */       jal osContGetReadData
  /* 004A24 80003E24 24845188 */     addiu $a0, $a0, %lo(D_80045188)
  /* 004A28 80003E28 3C118004 */       lui $s1, %hi(D_80045188)
  /* 004A2C 80003E2C 3C108004 */       lui $s0, %hi(D_800451A8)
  /* 004A30 80003E30 3C148004 */       lui $s4, %hi(D_800452C8)
  /* 004A34 80003E34 3C138004 */       lui $s3, %hi(D_80045178)
  /* 004A38 80003E38 26735178 */     addiu $s3, $s3, %lo(D_80045178)
  /* 004A3C 80003E3C 269452C8 */     addiu $s4, $s4, %lo(D_800452C8)
  /* 004A40 80003E40 261051A8 */     addiu $s0, $s0, %lo(D_800451A8)
  /* 004A44 80003E44 26315188 */     addiu $s1, $s1, %lo(D_80045188)
  /* 004A48 80003E48 00009025 */        or $s2, $zero, $zero
  /* 004A4C 80003E4C 24160004 */     addiu $s6, $zero, 4
  /* 004A50 80003E50 24150068 */     addiu $s5, $zero, 0x68
  .L80003E54:
  /* 004A54 80003E54 92220004 */       lbu $v0, 4($s1) # D_80045188 + 4
  /* 004A58 80003E58 00127080 */       sll $t6, $s2, 2
  /* 004A5C 80003E5C 026E7821 */      addu $t7, $s3, $t6
  /* 004A60 80003E60 54400011 */      bnel $v0, $zero, .L80003EA8
  /* 004A64 80003E64 304A00FF */      andi $t2, $v0, 0xff
  /* 004A68 80003E68 91F80002 */       lbu $t8, 2($t7)
  /* 004A6C 80003E6C 33190001 */      andi $t9, $t8, 1
  /* 004A70 80003E70 5320000D */      beql $t9, $zero, .L80003EA8
  /* 004A74 80003E74 304A00FF */      andi $t2, $v0, 0xff
  /* 004A78 80003E78 9208001C */       lbu $t0, 0x1c($s0) # D_800451A8 + 28
  /* 004A7C 80003E7C 5100000A */      beql $t0, $zero, .L80003EA8
  /* 004A80 80003E80 304A00FF */      andi $t2, $v0, 0xff
  /* 004A84 80003E84 02550019 */     multu $s2, $s5
  /* 004A88 80003E88 02E02025 */        or $a0, $s7, $zero
  /* 004A8C 80003E8C 02403025 */        or $a2, $s2, $zero
  /* 004A90 80003E90 00004812 */      mflo $t1
  /* 004A94 80003E94 02892821 */      addu $a1, $s4, $t1
  /* 004A98 80003E98 0C00C631 */       jal osMotorInit
  /* 004A9C 80003E9C 00000000 */       nop 
  /* 004AA0 80003EA0 92220004 */       lbu $v0, 4($s1) # D_80045188 + 4
  /* 004AA4 80003EA4 304A00FF */      andi $t2, $v0, 0xff
  .L80003EA8:
  /* 004AA8 80003EA8 15400029 */      bnez $t2, .L80003F50
  /* 004AAC 80003EAC A202001C */        sb $v0, 0x1c($s0) # D_800451A8 + 28
  /* 004AB0 80003EB0 96250000 */       lhu $a1, ($s1) # D_80045188 + 0
  /* 004AB4 80003EB4 96040000 */       lhu $a0, ($s0) # D_800451A8 + 0
  /* 004AB8 80003EB8 00A41026 */       xor $v0, $a1, $a0
  /* 004ABC 80003EBC 00A25824 */       and $t3, $a1, $v0
  /* 004AC0 80003EC0 00826024 */       and $t4, $a0, $v0
  /* 004AC4 80003EC4 A60B0002 */        sh $t3, 2($s0) # D_800451A8 + 2
  /* 004AC8 80003EC8 10400006 */      beqz $v0, .L80003EE4
  /* 004ACC 80003ECC A60C000A */        sh $t4, 0xa($s0) # D_800451A8 + 10
  /* 004AD0 80003ED0 8E0D0010 */        lw $t5, 0x10($s0) # D_800451A8 + 16
  /* 004AD4 80003ED4 3162FFFF */      andi $v0, $t3, 0xffff
  /* 004AD8 80003ED8 A6020006 */        sh $v0, 6($s0) # D_800451A8 + 6
  /* 004ADC 80003EDC 1000000C */         b .L80003F10
  /* 004AE0 80003EE0 AE0D0018 */        sw $t5, 0x18($s0) # D_800451A8 + 24
  .L80003EE4:
  /* 004AE4 80003EE4 8E0E0018 */        lw $t6, 0x18($s0) # D_800451A8 + 24
  /* 004AE8 80003EE8 25CFFFFF */     addiu $t7, $t6, -1
  /* 004AEC 80003EEC 19E00004 */      blez $t7, .L80003F00
  /* 004AF0 80003EF0 AE0F0018 */        sw $t7, 0x18($s0) # D_800451A8 + 24
  /* 004AF4 80003EF4 A6000006 */        sh $zero, 6($s0) # D_800451A8 + 6
  /* 004AF8 80003EF8 10000005 */         b .L80003F10
  /* 004AFC 80003EFC 96020002 */       lhu $v0, 2($s0) # D_800451A8 + 2
  .L80003F00:
  /* 004B00 80003F00 8E190014 */        lw $t9, 0x14($s0) # D_800451A8 + 20
  /* 004B04 80003F04 A6050006 */        sh $a1, 6($s0) # D_800451A8 + 6
  /* 004B08 80003F08 96020002 */       lhu $v0, 2($s0) # D_800451A8 + 2
  /* 004B0C 80003F0C AE190018 */        sw $t9, 0x18($s0) # D_800451A8 + 24
  .L80003F10:
  /* 004B10 80003F10 960A0004 */       lhu $t2, 4($s0) # D_800451A8 + 4
  /* 004B14 80003F14 960C000C */       lhu $t4, 0xc($s0) # D_800451A8 + 12
  /* 004B18 80003F18 960D000A */       lhu $t5, 0xa($s0) # D_800451A8 + 10
  /* 004B1C 80003F1C 960F0008 */       lhu $t7, 8($s0) # D_800451A8 + 8
  /* 004B20 80003F20 96180006 */       lhu $t8, 6($s0) # D_800451A8 + 6
  /* 004B24 80003F24 82280002 */        lb $t0, 2($s1) # D_80045188 + 2
  /* 004B28 80003F28 82290003 */        lb $t1, 3($s1) # D_80045188 + 3
  /* 004B2C 80003F2C 01425825 */        or $t3, $t2, $v0
  /* 004B30 80003F30 018D7025 */        or $t6, $t4, $t5
  /* 004B34 80003F34 01F8C825 */        or $t9, $t7, $t8
  /* 004B38 80003F38 A6050000 */        sh $a1, ($s0) # D_800451A8 + 0
  /* 004B3C 80003F3C A60B0004 */        sh $t3, 4($s0) # D_800451A8 + 4
  /* 004B40 80003F40 A60E000C */        sh $t6, 0xc($s0) # D_800451A8 + 12
  /* 004B44 80003F44 A6190008 */        sh $t9, 8($s0) # D_800451A8 + 8
  /* 004B48 80003F48 A208000E */        sb $t0, 0xe($s0) # D_800451A8 + 14
  /* 004B4C 80003F4C A209000F */        sb $t1, 0xf($s0) # D_800451A8 + 15
  .L80003F50:
  /* 004B50 80003F50 26520001 */     addiu $s2, $s2, 1
  /* 004B54 80003F54 26310006 */     addiu $s1, $s1, 6
  /* 004B58 80003F58 1656FFBE */       bne $s2, $s6, .L80003E54
  /* 004B5C 80003F5C 26100020 */     addiu $s0, $s0, 0x20
  /* 004B60 80003F60 8FBF0034 */        lw $ra, 0x34($sp)
  /* 004B64 80003F64 24080001 */     addiu $t0, $zero, 1
  /* 004B68 80003F68 3C018004 */       lui $at, %hi(D_80045250)
  /* 004B6C 80003F6C 8FB00014 */        lw $s0, 0x14($sp)
  /* 004B70 80003F70 8FB10018 */        lw $s1, 0x18($sp)
  /* 004B74 80003F74 8FB2001C */        lw $s2, 0x1c($sp)
  /* 004B78 80003F78 8FB30020 */        lw $s3, 0x20($sp)
  /* 004B7C 80003F7C 8FB40024 */        lw $s4, 0x24($sp)
  /* 004B80 80003F80 8FB50028 */        lw $s5, 0x28($sp)
  /* 004B84 80003F84 8FB6002C */        lw $s6, 0x2c($sp)
  /* 004B88 80003F88 8FB70030 */        lw $s7, 0x30($sp)
  /* 004B8C 80003F8C AC285250 */        sw $t0, %lo(D_80045250)($at)
  /* 004B90 80003F90 03E00008 */        jr $ra
  /* 004B94 80003F94 27BD0038 */     addiu $sp, $sp, 0x38
