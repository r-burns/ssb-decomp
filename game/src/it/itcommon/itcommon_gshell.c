#include "item.h"

itCreateDesc itCommon_GShell_ItemDesc =
{
    It_Kind_GShell,                         // Item Kind
    &gItemFileData,                         // Pointer to item file data?
    0x53C,                                  // Offset of item attributes in file?
    0,                                      // ???
    0,                                      // ???
    0,                                      // ???
    gmHitCollision_UpdateState_Disable,     // Hitbox Update State
    itGShell_AFall_ProcUpdate,              // Proc Update
    itGShell_AFall_ProcMap,                 // Proc Map
    NULL,                                   // Proc Hit
    NULL,                                   // Proc Shield
    NULL,                                   // Proc Hop
    NULL,                                   // Proc Set-Off
    NULL,                                   // Proc Reflector
    NULL                                    // Proc Damage
};

itStatusDesc itCommon_GShell_StatusDesc[7] =
{
    // Status 0 (Ground Wait)
    {
        NULL,                               // Proc Update
        itGShell_GWait_ProcMap,             // Proc Map
        NULL,                               // Proc Hit
        NULL,                               // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        NULL,                               // Proc Reflector
        itGShell_SDefault_ProcDamage        // Proc Damage
    },

    // Status 1 (Air Wait Fall)
    {
        itGShell_AFall_ProcUpdate,          // Proc Update
        itGShell_AFall_ProcMap,             // Proc Map
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
        itGShell_AThrow_ProcUpdate,         // Proc Update
        itGShell_AThrow_ProcMap,            // Proc Map
        itGShell_SDefault_ProcHit,          // Proc Hit
        itGShell_SDefault_ProcShield,       // Proc Shield
        itCommon_SDefault_ProcHop,          // Proc Hop
        itGShell_SDefault_ProcShield,       // Proc Set-Off
        itCommon_SDefault_ProcReflector,    // Proc Reflector
        itGShell_SDefault_ProcDamage        // Proc Damage
    },

    // Status 4 (Fighter Drop)
    {
        itGShell_AFall_ProcUpdate,          // Proc Update
        itGShell_AThrow_ProcMap,            // Proc Map
        itGShell_SDefault_ProcHit,          // Proc Hit
        itGShell_SDefault_ProcShield,       // Proc Shield
        itCommon_SDefault_ProcHop,          // Proc Hop
        itGShell_SDefault_ProcShield,       // Proc Set-Off
        itCommon_SDefault_ProcReflector,    // Proc Reflector
        itGShell_SDefault_ProcDamage        // Proc Damage
    },

    // Status 5 (Ground Spin)
    {
        itGShell_GSpin_ProcUpdate,          // Proc Update
        itGShell_GSpin_ProcMap,             // Proc Map
        itGShell_SDefault_ProcHit,          // Proc Hit
        itGShell_SDefault_ProcHit,          // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        itCommon_SDefault_ProcReflector,    // Proc Reflector
        itGShell_GASpin_ProcDamage          // Proc Damage
    },

    // Status 6 (Air Spin)
    {
        itGShell_AFall_ProcUpdate,          // Proc Update
        itGShell_AThrow_ProcMap,            // Proc Map
        itGShell_SDefault_ProcHit,          // Proc Hit
        itGShell_SDefault_ProcHit,          // Proc Shield
        NULL,                               // Proc Hop
        NULL,                               // Proc Set-Off
        itCommon_SDefault_ProcReflector,    // Proc Reflector
        itGShell_GASpin_ProcDamage          // Proc Damage
    }
};

typedef enum itGShellStatus
{
    itStatus_GShell_GWait,
    itStatus_GShell_AFall,
    itStatus_GShell_FHold,
    itStatus_GShell_AThrow,
    itStatus_GShell_ADrop,
    itStatus_GShell_GSpin,
    itStatus_GShell_ASpin

} itGShellStatus;

// 0x801785E0
void itGShell_GSpin_UpdateGFX(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos;

    if (ip->item_vars.shell.dust_gfx_int == 0)
    {
        pos = joint->translate;

        pos.y += ip->attributes->objectcoll_bottom;

        func_ovl2_800FF048(&pos, ip->lr, 1.0F);

        ip->item_vars.shell.dust_gfx_int = ATGSHELL_GFX_SPAWN_INT;
    }
    ip->item_vars.shell.dust_gfx_int--;
}

extern intptr_t D_NF_00005F88;
extern intptr_t D_NF_00006018;
extern intptr_t D_NF_00006048;

// 0x80178670
void func_ovl3_80178670(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    s32 unused[2];

    func_8000BD1C(joint, itGetPData(ip, D_NF_00005F88, D_NF_00006018), 0.0F); // Linker thing
    func_8000BD54(joint->mobj, itGetPData(ip, D_NF_00005F88, D_NF_00006048), 0.0F); // Linker thing
    func_8000DF34(item_gobj);
}

// 0x80178704
void func_ovl3_80178704(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->mobj->unk_mobj_0x94 = 0;
    DObjGetStruct(item_gobj)->unk_dobj_0x70 = 0;
}

// 0x8017871C
bool32 itGShell_AFall_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATGSHELL_GRAVITY, ATGSHELL_T_VEL);

    return FALSE;
}

// 0x8017874C
bool32 itGShell_GWait_ProcMap(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, itGShell_AFall_SetStatus);

    return FALSE;
}

// 0x80178774
bool32 itGShell_AFall_ProcMap(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->item_vars.shell.health == 0)
    {
        return func_ovl3_80173DF4(item_gobj, 0.2F);
    }
    else func_ovl3_80173B24(item_gobj, 0.2F, 0.5F, itGShell_GWait_SetStatus);

    return FALSE;
}

extern itStatusDesc itCommon_GShell_StatusDesc[];

// 0x801787CC
void itGShell_GWait_InitItemVars(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_80173F54(ip);

    if (ABSF(ip->phys_info.vel_air.x) < ATGSHELL_STOP_VEL_X)
    {
        func_ovl3_80172E74(item_gobj);

        ip->item_vars.shell.is_damage = FALSE;

        ip->is_damage_all = TRUE;

        ip->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
        ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

        ip->phys_info.vel_air.x = 0.0F;

        func_ovl3_80178704(item_gobj);
        itMain_SetItemStatus(item_gobj, itCommon_GShell_StatusDesc, itStatus_GShell_GWait);
    }
    else if (ip->item_vars.shell.is_damage != FALSE)
    {
        ip->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);
        itGShell_GSpin_SetStatus(item_gobj);
    }
    else
    {
        func_ovl3_80172E74(item_gobj);

        ip->is_damage_all = TRUE;

        ip->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
        ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

        ip->phys_info.vel_air.x = 0.0F;

        func_ovl3_80178704(item_gobj);
        itMain_SetItemStatus(item_gobj, itCommon_GShell_StatusDesc, itStatus_GShell_GWait);
    }
}

// 0x80178910
void itGShell_GWait_SetStatus(GObj *item_gobj)
{
    itGShell_GWait_InitItemVars(item_gobj);
}

// 0x80178930
void itGShell_AFall_SetStatus(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

    ip->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ip->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ip);
    itMain_SetItemStatus(item_gobj, itCommon_GShell_StatusDesc, itStatus_GShell_AFall);
}

// 0x8017897C
bool32 itGShell_SDefault_ProcDamage(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->phys_info.vel_air.x = ip->damage_taken_recent * ATGSHELL_DAMAGE_MUL_NORMAL * (-ip->lr_damage);

    if (ABSF(ip->phys_info.vel_air.x) > ATGSHELL_STOP_VEL_X)
    {
        ip->item_vars.shell.is_damage = TRUE;

        ip->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);

        ip->item_hurt.hitstatus = gmHitCollision_HitStatus_None;

        func_ovl3_801727BC(item_gobj);

        if (ip->ground_or_air != GA_Ground)
        {
            itGShell_ASpin_SetStatus(item_gobj);
        }
        else itGShell_GSpin_SetStatus(item_gobj);

    }
    else
    {
        ip->phys_info.vel_air.x = 0.0F;

        if (ip->ground_or_air != GA_Ground)
        {
            itGShell_AFall_SetStatus(item_gobj);
        }
        else itGShell_GWait_SetStatus(item_gobj);
    }
    return FALSE;
}

// 0x80178A90
void itGShell_FHold_SetStatus(GObj *item_gobj)
{
    DObjGetStruct(item_gobj)->rotate.y = 0.0F;

    itMain_SetItemStatus(item_gobj, itCommon_GShell_StatusDesc, itStatus_GShell_FHold);
}

// 0x80178AC4
bool32 itGShell_AThrow_ProcMap(GObj *item_gobj)
{
    func_ovl3_80173C68(item_gobj, 0.2F, 0.5F, itGShell_GWait_SetStatus);

    return FALSE;
}

// 0x80178AF8
bool32 itGShell_AThrow_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    func_ovl3_80172558(ip, ATGSHELL_GRAVITY, ATGSHELL_T_VEL);

    return FALSE;
}

// 0x80178B28
void itGShell_AThrow_SetStatus(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_vars.shell.health = 1;
    ip->item_vars.shell.is_damage = TRUE;

    itMain_SetItemStatus(item_gobj, itCommon_GShell_StatusDesc, itStatus_GShell_AThrow);
}

// 0x80178B60
void itGShell_ADrop_SetStatus(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_vars.shell.health = 1;
    ip->item_vars.shell.is_damage = TRUE;

    itMain_SetItemStatus(item_gobj, itCommon_GShell_StatusDesc, itStatus_GShell_ADrop);
}

// 0x80178B98
bool32 itGShell_GSpin_ProcUpdate(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    itGShell_GSpin_UpdateGFX(item_gobj);

    if (!(ip->item_vars.shell.damage_all_delay))
    {
        ip->is_damage_all = TRUE;

        ip->item_vars.shell.damage_all_delay = -1;
    }

    if (ip->item_vars.shell.damage_all_delay != -1)
    {
        ip->item_vars.shell.damage_all_delay--;
    }

    if (ip->lifetime == 0)
    {
        return TRUE;
    }
    else ip->lifetime--;

    return FALSE;
}

// 0x80178C10
bool32 itGShell_GSpin_ProcMap(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, itGShell_AFall_SetStatus);

    if (itMap_CheckCollideAllModifiyVel(item_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_RWALL | MPCOLL_MASK_LWALL), 0.2F, NULL) != FALSE)
    {
        func_ovl3_80172508(item_gobj);
        func_ovl3_8017279C(item_gobj);
    }
    return FALSE;
}

// 0x80178C6C
bool32 itGShell_SDefault_ProcHit(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;

    ip->item_vars.shell.health = rand_u16_range(ATGSHELL_HEALTH_MAX);

    ip->phys_info.vel_air.y = ATGSHELL_REBOUND_VEL_Y;

    ip->phys_info.vel_air.x = rand_f32() * (-ip->phys_info.vel_air.x * ATGSHELL_REBOUND_MUL_X);

    func_ovl3_8017279C(item_gobj);
    func_ovl3_80178704(item_gobj);
    itGShell_AFall_SetStatus(item_gobj);

    return FALSE;
}

// 0x80178CF8
bool32 itGShell_GASpin_ProcDamage(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->phys_info.vel_air.x += (ip->damage_taken_recent * ATGSHELL_DAMAGE_MUL_ADD * -ip->lr_damage);

    if (ABSF(ip->phys_info.vel_air.x) > ATGSHELL_STOP_VEL_X)
    {
        ip->item_hit.update_state = gmHitCollision_UpdateState_New;

        itManager_UpdateHitPositions(item_gobj);
        func_ovl3_801727BC(item_gobj);

        if (ip->ground_or_air != FALSE)
        {
            itGShell_ASpin_SetStatus(item_gobj);
        }
        else itGShell_GSpin_SetStatus(item_gobj);
    }
    else
    {
        ip->phys_info.vel_air.x = 0.0F;

        if (ip->ground_or_air != GA_Ground)
        {
            itGShell_AFall_SetStatus(item_gobj);
        }
        else itGShell_GWait_SetStatus(item_gobj);
    }
    return FALSE;
}

// 0x80178E04
void itGShell_GSpin_InitItemVars(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    ip->is_allow_pickup = FALSE;

    ip->pickup_wait = ITEM_PICKUP_WAIT_DEFAULT;

    if (ip->phys_info.vel_air.x > ATGSHELL_CLAMP_VEL_X)
    {
        ip->phys_info.vel_air.x = ATGSHELL_CLAMP_VEL_X;
    }
    if (ip->phys_info.vel_air.x < -ATGSHELL_CLAMP_VEL_X)
    {
        ip->phys_info.vel_air.x = -ATGSHELL_CLAMP_VEL_X;
    }
    ip->phys_info.vel_air.y = 0.0F;

    if (ip->phys_info.vel_air.x < 0.0F)
    {
        ip->lr = LEFT;
    }
    else ip->lr = RIGHT;

    ip->item_vars.shell.dust_gfx_int = ATGSHELL_GFX_SPAWN_INT;
    ip->item_vars.shell.damage_all_delay = ATGSHELL_DAMAGE_ALL_WAIT;

    func_ovl3_80178670(item_gobj);

    ip->is_damage_all = FALSE;

    func_ovl3_8017275C(item_gobj);
    func_800269C0(0x37);
}

// 0x80178EDC
void itGShell_GSpin_SetStatus(GObj *item_gobj)
{
    itGShell_GSpin_InitItemVars(item_gobj);
    itMain_SetItemStatus(item_gobj, itCommon_GShell_StatusDesc, itStatus_GShell_GSpin);
}

// 0x80178F10
void itGShell_ASpin_InitItemVars(GObj *item_gobj)
{
    Item_Struct *ip = itGetStruct(item_gobj);

    if (ip->phys_info.vel_air.x > ATGSHELL_CLAMP_VEL_X)
    {
        ip->phys_info.vel_air.x = ATGSHELL_CLAMP_VEL_X;
    }
    if (ip->phys_info.vel_air.x < -ATGSHELL_CLAMP_VEL_X)
    {
        ip->phys_info.vel_air.x = -ATGSHELL_CLAMP_VEL_X;
    }
    if (ip->phys_info.vel_air.x < 0.0F)
    {
        ip->lr = LEFT;
    }
    else ip->lr = RIGHT;

    ip->is_damage_all = FALSE;

    func_ovl3_8017275C(item_gobj);
}

// 0x80178FA8
void itGShell_ASpin_SetStatus(GObj *item_gobj)
{
    itGShell_ASpin_InitItemVars(item_gobj);
    itMain_SetItemStatus(item_gobj, itCommon_GShell_StatusDesc, itStatus_GShell_ASpin);
}

// 0x80178FDC
GObj* itCommon_GShell_CreateItem(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &itCommon_GShell_ItemDesc, pos, vel, flags);

    if (item_gobj != NULL)
    {
        DObj *joint = DObjGetStruct(item_gobj);
        Item_Struct *ip;
        Vec3f translate = joint->translate;

        joint->rotate.y = HALF_PI32;

        func_80008CC0(joint, 0x1BU, 0U);
        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = translate;

        joint->mobj->anim_frame = 1.0F;

        ip = itGetStruct(item_gobj);

        ip->item_hit.can_rehit_shield = TRUE;

        ip->item_vars.shell.health = 1;
        ip->item_vars.shell.is_damage = FALSE;

        ip->is_unused_item_bool = TRUE;

        ip->indicator_gobj = ifManager_ItemIndicator_CreateInterface(ip);

        ip->lifetime = ATGSHELL_LIFETIME;
    }
    return item_gobj;
}

// 0x801790F4
bool32 itGShell_SDefault_ProcShield(GObj *item_gobj)
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}