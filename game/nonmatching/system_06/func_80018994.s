.section .text
glabel func_80018994
  /* 019594 80018994 27BDFFE8 */     addiu $sp, $sp, -0x18
  /* 019598 80018998 AFBF0014 */        sw $ra, 0x14($sp)
  /* 01959C 8001899C 0C006244 */       jal func_80018910
  /* 0195A0 800189A0 AFA40018 */        sw $a0, 0x18($sp)
  /* 0195A4 800189A4 8FAE0018 */        lw $t6, 0x18($sp)
  /* 0195A8 800189A8 8FBF0014 */        lw $ra, 0x14($sp)
  /* 0195AC 800189AC 27BD0018 */     addiu $sp, $sp, 0x18
  /* 0195B0 800189B0 004E0019 */     multu $v0, $t6
  /* 0195B4 800189B4 00001012 */      mflo $v0
  /* 0195B8 800189B8 04410003 */      bgez $v0, .L800189C8
  /* 0195BC 800189BC 00400821 */      addu $at, $v0, $zero
  /* 0195C0 800189C0 3401FFFF */       ori $at, $zero, 0xffff
  /* 0195C4 800189C4 00220821 */      addu $at, $at, $v0
  .L800189C8:
  /* 0195C8 800189C8 00011403 */       sra $v0, $at, 0x10
  /* 0195CC 800189CC 03E00008 */        jr $ra
  /* 0195D0 800189D0 00000000 */       nop 
