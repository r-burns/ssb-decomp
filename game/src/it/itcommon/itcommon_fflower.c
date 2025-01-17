#include "item.h"
#include "weapon.h"
#include "fighter.h"

itCreateDesc itCommon_FFlower_ItemDesc = 
{
    It_Kind_FFlower,                        // Item Kind
    &gItemFileData,                         // Pointer to item file data?
    0x2E4,                                  // Offset of item attributes in file?
    0x1B,                                   // ???
    0,                                      // ???
    0,                                      // ???
    gmHitCollision_UpdateState_Disable,     // Hitbox Update State
    itFFlower_AFall_ProcUpdate,             // Proc Update
    itFFlower_AFall_ProcMap,                // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

itStatusDesc itCommon_FFlower_StatusDesc[5] =
{
    // Status 0 (Ground Wait)
    {
        NULL,                               // Proc Update
        itFFlower_GWait_ProcMap,            // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 1 (Air Wait Fall)
    {
        itFFlower_AFall_ProcUpdate,         // Proc Update
        itFFlower_AFall_ProcMap,            // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 2 (Fighter Hold)
    {
        NULL,                               // Proc Update
        NULL,                               // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        NULL                                // Proc Damage
    },

    // Status 3 (Fighter Throw)
    {
        itFFlower_AFall_ProcUpdate,         // Proc Update
        itFFlower_AThrow_ProcMap,           // Proc Map
        itFFlower_SDefault_ProcHit,         // Proc Hit
        itFFlower_SDefault_ProcHit,         // Proc Shield
        itCommon_SDefault_ProcHop,          // Proc Hop
        itFFlower_SDefault_ProcHit,         // Proc Set-Off
        itCommon_SDefault_ProcReflector,    // Proc Reflector
        itFFlower_SDefault_ProcHit          // Proc Damage
    },

    // Status 4 (Fighter Drop)
    {
        itFFlower_AFall_ProcUpdate,         // Proc Update
        itFFlower_ADrop_ProcMap,            // Proc Map
        itFFlower_SDefault_ProcHit,         // Proc Hit
        itFFlower_SDefault_ProcHit,         // Proc Shield
        itCommon_SDefault_ProcHop,          // Proc Hop
        itFFlower_SDefault_ProcHit,         // Proc Set-Off
        itCommon_SDefault_ProcReflector,    // Proc Reflector
        itFFlower_SDefault_ProcHit          // Proc Damage
    }
};

wpCreateDesc wpFFlower_Flame_WeaponDesc =
{
    0,                                      // Render flags?
    Wp_Kind_FFlowerFlame,                   // Weapon Kind
    &gItemFileData,                         // Pointer to character's loaded files?
    0x32C,                                  // Offset of weapon attributes in loaded files
    0x1C,                                   // ???
    0,                                      // ???
    0,                                      // ???
    0,                                      // ???
    wpFFlower_Flame_ProcUpdate,             // Proc Update
    wpFFlower_Flame_ProcMap,                // Proc Map
    wpFFlower_Flame_ProcHit,                // Proc Hit
    wpFFlower_Flame_ProcHit,                // Proc Shield
    NULL,                                   // Proc Hop
    wpFFlower_Flame_ProcHit,                // Proc Set-Off
    wpFFlower_Flame_ProcReflector,          // Proc Reflector
    NULL                                    // Proc Absorb
};

typedef enum itFFlowerStatus
{
    itStatus_FFlower_GWait,
    itStatus_FFlower_AFall,
    itStatus_FFlower_FHold,
    itStatus_FFlower_AThrow,
    itStatus_FFlower_ADrop

} itFFlowerStatus;

// 0x80175B20
bool32 itFFlower_AFall_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATFFLOWER_GRAVITY, ATFFLOWER_T_VEL);
    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

// 0x80175B5C
bool32 itFFlower_GWait_ProcMap(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, itFFlower_AFall_SetStatus);

    return FALSE;
}

// 0x80175B84
bool32 itFFlower_AFall_ProcMap(GObj *item_gobj)
{
    return func_ovl3_80173B24(item_gobj, 0.0F, 0.5F, itFFlower_GWait_SetStatus);
}

extern itStatusDesc itCommon_FFlower_StatusDesc[];

// 0x80175BB0
void itFFlower_GWait_SetStatus(GObj *item_gobj)
{
    func_ovl3_80172E74(item_gobj);
    itMain_SetItemStatus(item_gobj, itCommon_FFlower_StatusDesc, itStatus_FFlower_GWait);
}

// 0x80175BE4
void itFFlower_AFall_SetStatus(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ip);
    itMain_SetItemStatus(item_gobj, itCommon_FFlower_StatusDesc, itStatus_FFlower_AFall);
}

// 0x80175C28
void itFFlower_FHold_SetStatus(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, itCommon_FFlower_StatusDesc, itStatus_FFlower_FHold);
}

// 0x80175C50
bool32 itFFlower_AThrow_ProcMap(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->it_multi == 0)
    {
        return func_ovl3_80173DF4(item_gobj, 0.0F);
    }
    else return func_ovl3_80173B24(item_gobj, 0.0F, 0.5F, itFFlower_GWait_SetStatus);
}

// 0x80175C9C
bool32 itFFlower_SDefault_ProcHit(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

// 0x80175CC4
void itFFlower_AThrow_SetStatus(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, itCommon_FFlower_StatusDesc, itStatus_FFlower_AThrow);
}

// 0x80175CEC
bool32 itFFlower_ADrop_ProcMap(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->it_multi == 0)
    {
        return func_ovl3_80173DF4(item_gobj, 0.0F);
    }
    else return func_ovl3_80173B24(item_gobj, 0.0F, 0.5F, itFFlower_GWait_SetStatus);
}

// 0x80175D38
void itFFlower_ADrop_SetStatus(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, itCommon_FFlower_StatusDesc, itStatus_FFlower_ADrop);
}

extern itCreateDesc itCommon_FFlower_ItemDesc;

// 0x80175D60
GObj* itCommon_FFlower_CreateItem(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &itCommon_FFlower_ItemDesc, pos, vel, flags);

    if (item_gobj != NULL)
    {
        Item_Struct *ip = itGetStruct(item_gobj);

        ip->it_multi = ATFFLOWER_AMMO_MAX;

        ip->is_unused_item_bool = TRUE;

        ip->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ip);
    }
    return item_gobj;
}

// 0x80175DDC
bool32 wpFFlower_Flame_ProcUpdate(GObj *weapon_gobj)
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);

    if (wpMain_DecLifeCheckExpire(wp) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

// 0x801750E8
bool32 wpFFlower_Flame_ProcMap(GObj *weapon_gobj)
{
    if (func_ovl3_80167C04(weapon_gobj) != FALSE)
    {
        func_ovl2_800FF648(&DObjGetStruct(weapon_gobj)->translate, 1.0F);

        return TRUE;
    }
    else return FALSE;
}

// 0x80175E4C
bool32 wpFFlower_Flame_ProcHit(GObj *weapon_gobj)
{
    func_800269C0(0U);
    func_ovl2_80100480(&DObjGetStruct(weapon_gobj)->translate);

    return FALSE;
}

extern s32 D_ovl3_8018D044; // Something to do with GFX IDs; static (.bss)

// 0x80175E84
bool32 wpFFlower_Flame_ProcReflector(GObj *weapon_gobj)
{
    Weapon_Struct *wp = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(wp->owner_gobj);
    Vec3f *translate;

    wp->lifetime = ATFFLOWER_AMMO_LIFETIME;

    wpMain_ReflectorInvertLR(wp, fp);

    translate = &DObjGetStruct(weapon_gobj)->translate;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, translate->x, translate->y, 0.0F, wp->phys_info.vel_air.x, wp->phys_info.vel_air.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, translate->x, translate->y, 0.0F, wp->phys_info.vel_air.x, wp->phys_info.vel_air.y, 0.0F);

    return FALSE;
}

// 0x80175F48
GObj* wpFFlower_Flame_CreateWeapon(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *weapon_gobj = wpManager_CreateWeapon(fighter_gobj, &wpFFlower_Flame_WeaponDesc, pos, (WEAPON_FLAG_PROJECT | WEAPON_MASK_SPAWN_FIGHTER));
    Weapon_Struct *wp;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    wp = wpGetStruct(weapon_gobj);

    wp->phys_info.vel_air.x = vel->x * wp->lr;
    wp->phys_info.vel_air.y = vel->y;
    wp->phys_info.vel_air.z = vel->z;

    wp->lifetime = ATFFLOWER_AMMO_LIFETIME;

    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 2, pos->x, pos->y, 0.0F, wp->phys_info.vel_air.x, wp->phys_info.vel_air.y, 0.0F);
    func_ovl0_800CE8C0(D_ovl3_8018D044 | 8, 0, pos->x, pos->y, 0.0F, wp->phys_info.vel_air.x, wp->phys_info.vel_air.y, 0.0F);

    return weapon_gobj;
}

extern intptr_t D_NF_00000360;

// 0x8017604C
void ftCommon_FireFlowerShoot_CreateFlame(GObj *fighter_gobj, Vec3f *pos, s32 index, s32 ammo_sub)
{
    Item_Struct *ip = itGetStruct(ftGetStruct(fighter_gobj)->item_hold);
    Vec3f vel;
    f32 *flame_vel = (f32*) ((uintptr_t)*itCommon_FFlower_ItemDesc.p_file + (intptr_t)&D_NF_00000360); // Linker thing

    vel.x = cosf(flame_vel[index]) * ATFFLOWER_AMMO_VEL;
    vel.y = __sinf(flame_vel[index]) * ATFFLOWER_AMMO_VEL;
    vel.z = 0.0F;

    wpFFlower_Flame_CreateWeapon(fighter_gobj, pos, &vel);

    ip->it_multi -= ammo_sub;
}