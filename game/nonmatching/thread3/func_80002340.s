glabel func_80002340
  /* 002F40 80002340 3C028004 */       lui $v0, %hi(D_80044ECC)
  /* 002F44 80002344 8C424ECC */        lw $v0, %lo(D_80044ECC)($v0)
  /* 002F48 80002348 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 002F4C 8000234C AFBF0014 */        sw $ra, 0x14($sp)
  /* 002F50 80002350 1040002D */      beqz $v0, .L80002408
  /* 002F54 80002354 00000000 */       nop 
  /* 002F58 80002358 8C4E0018 */        lw $t6, 0x18($v0)
  /* 002F5C 8000235C 24010002 */     addiu $at, $zero, 2
  /* 002F60 80002360 15C10029 */       bne $t6, $at, .L80002408
  /* 002F64 80002364 00000000 */       nop 
  /* 002F68 80002368 8C4F0000 */        lw $t7, ($v0)
  /* 002F6C 8000236C 24010001 */     addiu $at, $zero, 1
  /* 002F70 80002370 15E10020 */       bne $t7, $at, .L800023F4
  /* 002F74 80002374 00000000 */       nop 
  /* 002F78 80002378 8C44006C */        lw $a0, 0x6c($v0)
  /* 002F7C 8000237C 50800006 */      beql $a0, $zero, .L80002398
  /* 002F80 80002380 8C440020 */        lw $a0, 0x20($v0)
  /* 002F84 80002384 0C0005EE */       jal func_800017B8
  /* 002F88 80002388 00000000 */       nop 
  /* 002F8C 8000238C 3C028004 */       lui $v0, %hi(D_80044ECC)
  /* 002F90 80002390 8C424ECC */        lw $v0, %lo(D_80044ECC)($v0)
  /* 002F94 80002394 8C440020 */        lw $a0, 0x20($v0)
  .L80002398:
  /* 002F98 80002398 00003025 */        or $a2, $zero, $zero
  /* 002F9C 8000239C 50800006 */      beql $a0, $zero, .L800023B8
  /* 002FA0 800023A0 8C580008 */        lw $t8, 8($v0)
  /* 002FA4 800023A4 0C00C000 */       jal osSendMesg
  /* 002FA8 800023A8 8C45001C */        lw $a1, 0x1c($v0)
  /* 002FAC 800023AC 3C028004 */       lui $v0, %hi(D_80044ECC)
  /* 002FB0 800023B0 8C424ECC */        lw $v0, %lo(D_80044ECC)($v0)
  /* 002FB4 800023B4 8C580008 */        lw $t8, 8($v0)
  .L800023B8:
  /* 002FB8 800023B8 24010004 */     addiu $at, $zero, 4
  /* 002FBC 800023BC 3C048004 */       lui $a0, %hi(D_80044ED0)
  /* 002FC0 800023C0 1701000C */       bne $t8, $at, .L800023F4
  /* 002FC4 800023C4 00000000 */       nop 
  /* 002FC8 800023C8 8C844ED0 */        lw $a0, %lo(D_80044ED0)($a0)
  /* 002FCC 800023CC 0C00C1B3 */       jal osSpTaskLoad
  /* 002FD0 800023D0 24840028 */     addiu $a0, $a0, 0x28
  /* 002FD4 800023D4 3C048004 */       lui $a0, %hi(D_80044ED0)
  /* 002FD8 800023D8 8C844ED0 */        lw $a0, %lo(D_80044ED0)($a0)
  /* 002FDC 800023DC 0C00C217 */       jal osSpTaskStartGo
  /* 002FE0 800023E0 24840028 */     addiu $a0, $a0, 0x28
  /* 002FE4 800023E4 3C088004 */       lui $t0, %hi(D_80044ED0)
  /* 002FE8 800023E8 8D084ED0 */        lw $t0, %lo(D_80044ED0)($t0)
  /* 002FEC 800023EC 24190002 */     addiu $t9, $zero, 2
  /* 002FF0 800023F0 AD190008 */        sw $t9, 8($t0)
  .L800023F4:
  /* 002FF4 800023F4 3C018004 */       lui $at, %hi(D_80044ECC)
  /* 002FF8 800023F8 0C000799 */       jal func_80001E64
  /* 002FFC 800023FC AC204ECC */        sw $zero, %lo(D_80044ECC)($at)
  /* 003000 80002400 10000037 */         b .L800024E0
  /* 003004 80002404 8FBF0014 */        lw $ra, 0x14($sp)
  .L80002408:
  /* 003008 80002408 3C028004 */       lui $v0, %hi(D_80044EE4)
  /* 00300C 8000240C 8C424EE4 */        lw $v0, %lo(D_80044EE4)($v0)
  /* 003010 80002410 3C078004 */       lui $a3, 0x8004
  /* 003014 80002414 10400013 */      beqz $v0, .L80002464
  /* 003018 80002418 00000000 */       nop 
  /* 00301C 8000241C 8C44006C */        lw $a0, 0x6c($v0)
  /* 003020 80002420 50800006 */      beql $a0, $zero, .L8000243C
  /* 003024 80002424 8C440020 */        lw $a0, 0x20($v0)
  /* 003028 80002428 0C0005EE */       jal func_800017B8
  /* 00302C 8000242C 00000000 */       nop 
  /* 003030 80002430 3C028004 */       lui $v0, %hi(D_80044EE4)
  /* 003034 80002434 8C424EE4 */        lw $v0, %lo(D_80044EE4)($v0)
  /* 003038 80002438 8C440020 */        lw $a0, 0x20($v0)
  .L8000243C:
  /* 00303C 8000243C 00003025 */        or $a2, $zero, $zero
  /* 003040 80002440 10800003 */      beqz $a0, .L80002450
  /* 003044 80002444 00000000 */       nop 
  /* 003048 80002448 0C00C000 */       jal osSendMesg
  /* 00304C 8000244C 8C45001C */        lw $a1, 0x1c($v0)
  .L80002450:
  /* 003050 80002450 3C018004 */       lui $at, %hi(D_80044EE4)
  /* 003054 80002454 0C0007FD */       jal func_80001FF4
  /* 003058 80002458 AC204EE4 */        sw $zero, %lo(D_80044EE4)($at)
  /* 00305C 8000245C 10000020 */         b .L800024E0
  /* 003060 80002460 8FBF0014 */        lw $ra, 0x14($sp)
  .L80002464:
  /* 003064 80002464 8CE74ED4 */        lw $a3, 0x4ed4($a3)
  /* 003068 80002468 50E0001D */      beql $a3, $zero, .L800024E0
  /* 00306C 8000246C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 003070 80002470 8CE90018 */        lw $t1, 0x18($a3)
  /* 003074 80002474 24010002 */     addiu $at, $zero, 2
  /* 003078 80002478 55210019 */      bnel $t1, $at, .L800024E0
  /* 00307C 8000247C 8FBF0014 */        lw $ra, 0x14($sp)
  /* 003080 80002480 8CEA0000 */        lw $t2, ($a3)
  /* 003084 80002484 24010001 */     addiu $at, $zero, 1
  /* 003088 80002488 15410012 */       bne $t2, $at, .L800024D4
  /* 00308C 8000248C 00000000 */       nop 
  /* 003090 80002490 8CE4006C */        lw $a0, 0x6c($a3)
  /* 003094 80002494 50800006 */      beql $a0, $zero, .L800024B0
  /* 003098 80002498 8CE40020 */        lw $a0, 0x20($a3)
  /* 00309C 8000249C 0C0005EE */       jal func_800017B8
  /* 0030A0 800024A0 00000000 */       nop 
  /* 0030A4 800024A4 3C078004 */       lui $a3, %hi(D_80044ED4)
  /* 0030A8 800024A8 8CE74ED4 */        lw $a3, %lo(D_80044ED4)($a3)
  /* 0030AC 800024AC 8CE40020 */        lw $a0, 0x20($a3)
  .L800024B0:
  /* 0030B0 800024B0 00003025 */        or $a2, $zero, $zero
  /* 0030B4 800024B4 10800005 */      beqz $a0, .L800024CC
  /* 0030B8 800024B8 00000000 */       nop 
  /* 0030BC 800024BC 0C00C000 */       jal osSendMesg
  /* 0030C0 800024C0 8CE5001C */        lw $a1, 0x1c($a3)
  /* 0030C4 800024C4 3C078004 */       lui $a3, %hi(D_80044ED4)
  /* 0030C8 800024C8 8CE74ED4 */        lw $a3, %lo(D_80044ED4)($a3)
  .L800024CC:
  /* 0030CC 800024CC 0C000375 */       jal func_80000DD4
  /* 0030D0 800024D0 00E02025 */        or $a0, $a3, $zero
  .L800024D4:
  /* 0030D4 800024D4 0C000799 */       jal func_80001E64
  /* 0030D8 800024D8 00000000 */       nop 
  /* 0030DC 800024DC 8FBF0014 */        lw $ra, 0x14($sp)
  .L800024E0:
  /* 0030E0 800024E0 27BD0018 */     addiu $sp, $sp, 0x18
  /* 0030E4 800024E4 03E00008 */        jr $ra
  /* 0030E8 800024E8 00000000 */       nop 
