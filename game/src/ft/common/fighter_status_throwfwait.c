#include "ftdonkey.h"

// Donkey Kong's Cargo Wait

#define ftStatus_CheckInteruptThrowFWait(fighter_gobj) \
(                                                      \
    (func_ovl3_80146BE0(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014DFA8(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014D9B8(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014DC08(fighter_gobj) != FALSE) ||     \
    (func_ovl3_8014D810(fighter_gobj) != FALSE)        \
)                                                      \

void func_ovl3_8014D400(GObj *fighter_gobj)
{
    if (!ftStatus_CheckInteruptThrowFWait(fighter_gobj))
    {
        func_ovl3_8014D6F8(fighter_gobj);
    }
}

void func_ovl3_8014D478(GObj *fighter_gobj)
{
    func_ovl2_800DDDDC(fighter_gobj, func_ovl3_8014DA98);
}

void func_ovl3_8014D49C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (fp->ground_or_air == air)
    {
        ftCollision_SetGround(fp);
    }
    ftStatus_Update(fighter_gobj, ftStatus_Donkey_ThrowFWait, 0.0F, 1.0F, 0U);
}

bool32 func_ovl3_8014D4EC(GObj *fighter_gobj)
{
    if (func_ovl3_8013E258(fighter_gobj) != FALSE)
    {
        func_ovl3_8014D49C(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}