#ifndef _ITEMVARS_H_
#define _ITEMVARS_H_

#include <game/include/ssb_types.h>
#include <game/include/PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef struct Thunder_ItemVars // Pikachu's Thunder
{
    s32 thunder_state;

} Thunder_ItemVars;

typedef struct _PK_Thunder_ItemVars
{
    s32 x0;
    f32 x4;
    GObj *x8; // Original owner?
    GObj *xC[5];

} PK_Thunder_ItemVars;

typedef struct _PK_Thunder_Trail_ItemVars
{
    s32 x0;
    s32 x4;
    GObj *x8; // Original owner?
    GObj *xC[5];

} PK_Thunder_Trail_ItemVars;

typedef struct Charge_Shot_ItemVars
{
    s32 x0;
    s32 x4;
    s32 charge_size;
    s32 xC;

} Charge_Shot_ItemVars;

typedef struct Spin_Attack_ItemVars
{
    s16 pos_x[4];
    s16 pos_y[4];
    u8 filler_0x10[0x18 - 0x10];
    u8 unk_0x18;
    s8 pos_index;

} Spin_Attack_ItemVars;

typedef struct Egg_Throw_ItemVars
{
    u8 unk_0x0;
    u8 is_throw;
    Vec2b trajectory;
    s16 throw_force;

} Egg_Throw_ItemVars;

#endif