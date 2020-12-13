.include "macros.inc"

.section .data

#glabel __osPiDevMgr
#  .incbin "system.raw.bin", 0x3D010, 0x8
#
#glabel D_8003D418
#  .incbin "system.raw.bin", 0x3D018, 0x14
#
#glabel __osPiTable
#  .incbin "system.raw.bin", 0x3D02C, 0x4
#
#glabel __osCurrentHandle
#  /* 3D030 03E030 8003D430 */  .4byte CartRomHandle
#  /* 3D034 03E034 8003D434 */  .4byte LeoDiskHandle
#  .incbin "system.raw.bin", 0x3D038, 0x8

#glabel D_8003D440
#  .incbin "system.raw.bin", 0x3D040, 0x10

#glabel D_8003D450
#  /* 3D050 03E050 8003D450 */
#  .asciz "                                "
#  .balign 4

#glabel D_8003D474
#  /* 3D074 03E074 8003D474 */
#  .asciz "00000000000000000000000000000000"
#  .balign 4
#  .incbin "system.raw.bin", 0x3D098, 0x8

#glabel __osTimerList
#  /* 3D0A0 03E0A0 8003D4A0 */  .4byte D_800A0550
#  .incbin "system.raw.bin", 0x3D0A4, 0xC

#glabel osViModeNtscLan1
#  .incbin "system.raw.bin", 0x3D0B0, 0x50
#
#glabel osViModeMpalLan1
#  .incbin "system.raw.bin", 0x3D100, 0x50

#glabel D_8003D550
#  .incbin "system.raw.bin", 0x3D150, 0x30
#
#glabel D_8003D580
#  .incbin "system.raw.bin", 0x3D180, 0x30

#glabel __osViCurr
#  /* 3D1B0 03E1B0 8003D5B0 */  .4byte D_8003D550
#
#glabel __osViNext
#  /* 3D1B4 03E1B4 8003D5B4 */  .4byte D_8003D580
#  .incbin "system.raw.bin", 0x3D1B8, 0x8