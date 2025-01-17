#include "item.h"
#include "fighter.h"

extern intptr_t Article_Link_Bomb_Scale;
extern itCreateDesc Article_Link_Bomb_Data;

void func_ovl3_801859C0(GObj *item_gobj)
{
    DObj *joint = DObjGetStruct(item_gobj);
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->item_vars.link_bomb.scale_int == 0)
    {
        f32 *p_scale = (f32*) ((uintptr_t)*Article_Link_Bomb_Data.p_file + (intptr_t)&Article_Link_Bomb_Scale); // Linker thing

        s32 index = (ap->item_vars.link_bomb.scale_index >= ATLINKBOMB_SCALE_INDEX_REWIND) ? ATLINKBOMB_SCALE_INDEX_MAX - ap->item_vars.link_bomb.scale_index : ap->item_vars.link_bomb.scale_index;

        if (ap->is_hold)
        {
            joint->next->scale.x = joint->next->scale.y = p_scale[index];
        }
        else
        {
            joint->scale.x = joint->scale.y = p_scale[index];
        }
        ap->item_vars.link_bomb.scale_int = ATLINKBOMB_SCALE_INT;

        if (ap->item_vars.link_bomb.scale_index >= ATLINKBOMB_SCALE_INDEX_MAX)
        {
            ap->item_vars.link_bomb.scale_index = 0;
        }
        else ap->item_vars.link_bomb.scale_index += 1; // Doesn't match with "++" lol
    }
    ap->item_vars.link_bomb.scale_int--;
}

void func_ovl3_80185A80(GObj *item_gobj)
{
    s32 unused;
    DObj *joint = DObjGetStruct(item_gobj);
    Item_Struct *ap = itGetStruct(item_gobj);
    Effect_Unk *ep;

    func_ovl3_80185CE4(item_gobj);

    ep = func_ovl2_801005C8(&joint->translate);

    if (ep != NULL)
    {
        ep->effect_info->scale.x = ATLINKBOMB_EXPLODE_GFX_SCALE;
        ep->effect_info->scale.y = ATLINKBOMB_EXPLODE_GFX_SCALE;
        ep->effect_info->scale.z = ATLINKBOMB_EXPLODE_GFX_SCALE;
    }
    func_ovl2_801008F4(1);

    DObjGetStruct(item_gobj)->unk_0x54 = 2;

    ap->item_hit.hit_sfx = 1;

    func_ovl3_8017275C(item_gobj);
    func_ovl3_8018656C(item_gobj);
}

void func_ovl3_80185B18(GObj *item_gobj)
{
    s32 unused[5];
    Item_Struct *ap = itGetStruct(item_gobj);
    itCommonAttributes *attributes = ap->attributes;
    DObj *joint = DObjGetStruct(item_gobj);
    Vec3f pos = joint->translate;

    pos.y += attributes->objectcoll_bottom;

    func_ovl2_800FF3F4(&pos, ap->lr, 1.0F);
}

bool32 func_ovl3_80185B84(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->damage_taken_recent >= ATLINKBOMB_HEALTH)
    {
        func_ovl3_80186368(item_gobj);
    }
    else
    {
        ap->lr = -ap->lr_damage;

        ap->phys_info.vel_air.x = -ap->lr_damage * ATLINKBOMB_DAMAGE_RECOIL_VEL_X;
        ap->phys_info.vel_air.y = -ap->lr_damage * ATLINKBOMB_DAMAGE_RECOIL_VEL_Y;
    }
    return FALSE;
}

bool32 func_ovl3_80185BFC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if ((ABSF(ap->phys_info.vel_air.x) > ATLINKBOMB_EXPLODE_THRESHOLD_VEL_X) || (ABSF(ap->phys_info.vel_air.y) > ATLINKBOMB_EXPLODE_THRESHOLD_VEL_Y))
    {
        func_ovl3_80186368(item_gobj);
    }
    else
    {
        ap->lr = -ap->lr_attack;

        ap->phys_info.vel_air.x = -ap->lr_attack * ATLINKBOMB_HIT_RECOIL_VEL_X;
        ap->phys_info.vel_air.y = ATLINKBOMB_HIT_RECOIL_VEL_Y;

        func_ovl3_80185FD8(item_gobj);
    }
    return FALSE;
}

void func_ovl3_80185CD4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_Normal;
}

void func_ovl3_80185CD4(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hurt.hitstatus = gmHitCollision_HitStatus_None;
}

bool32 func_ovl3_80185CF0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATLINKBOMB_GRAVITY, ATLINKBOMB_T_VEL);

    if (ap->lifetime == 0)
    {
        func_ovl3_80186368(item_gobj);
    }
    if (ap->lifetime == ATLINKBOMB_BLOAT_BEGIN)
    {
        itMain_CheckSetColAnimIndex(item_gobj, ATLINKBOMB_BLOAT_COLANIM_ID, ATLINKBOMB_BLOAT_COLANIM_LENGTH);

        ap->item_vars.link_bomb.scale_index = 1;
    }
    if (ap->lifetime < ATLINKBOMB_BLOAT_BEGIN)
    {
        func_ovl3_801859C0(item_gobj);
    }
    ap->lifetime--;

    func_ovl3_801713F4(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_80185DCC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->phys_info.vel_air.x != 0.0F)
    {
        ap->phys_info.vel_air.x += (-1.0F) * ap->lr;
    }
    if (ABSF(ap->phys_info.vel_air.x) < 1.0F)
    {
        ap->phys_info.vel_air.x = 0;
    }
    if (ap->lifetime == 0)
    {
        func_ovl3_80186368(item_gobj);
    }
    if (ap->lifetime == ATLINKBOMB_BLOAT_BEGIN)
    {
        itMain_CheckSetColAnimIndex(item_gobj, ATLINKBOMB_BLOAT_COLANIM_ID, ATLINKBOMB_BLOAT_COLANIM_LENGTH);

        ap->item_vars.link_bomb.scale_index = 1;
    }
    if (ap->lifetime < ATLINKBOMB_BLOAT_BEGIN)
    {
        func_ovl3_801859C0(item_gobj);
    }
    ap->lifetime--;

    return FALSE;
}

bool32 jtgt_ovl3_80185F10(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_80185FD8);

    return FALSE;
}

bool32 jtgt_ovl3_80185F38(GObj *item_gobj)
{
    func_ovl3_80173B24(item_gobj, 0.4F, 0.3F, func_ovl3_80185F70);

    return FALSE;
}

extern itStatusDesc Article_Link_Bomb_Status[];

void func_ovl3_80185F70(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->item_hit.update_state = gmHitCollision_UpdateState_Disable;

    ap->is_allow_pickup = TRUE;

    ap->times_landed = 0;

    ap->phys_info.vel_air.z = 0.0F;
    ap->phys_info.vel_air.y = 0.0F;
    ap->phys_info.vel_air.x = 0.0F;

    func_ovl3_80173F54(ap);
    func_ovl3_80185CD4(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 0);
}

void func_ovl3_80185FD8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->is_allow_pickup = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80185CD4(item_gobj);
    itMain_SetItemStatus(item_gobj, &Article_Link_Bomb_Status, 1);
}

bool32 func_ovl3_80186024(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    Fighter_Struct *fp = ftGetStruct(ap->owner_gobj);

    if (fp->status_info.status_id == ftStatus_Common_DokanWait) // Odd but go off
    {
        return FALSE;
    }
    else
    {
        if (ap->lifetime == 0)
        {
            func_ovl3_80172984(item_gobj, &ap->phys_info.vel, 1.0F); // Ok, WHAT? This function takes 5 arguments, but it doesn't match otherwise???
                                                                        // Did they actually redefine this? Passes pointer in a3 instead of u16...
                                                                        // Do we leave this out of the header and declare it separately to match?
                                                                        // Update 3/23/2023: matches as variadic. No comment.
            func_ovl3_8017279C(item_gobj);
            func_ovl3_80186368(item_gobj);
        }
        if (ap->lifetime == ATLINKBOMB_BLOAT_BEGIN)
        {
            itMain_CheckSetColAnimIndex(item_gobj, ATLINKBOMB_BLOAT_COLANIM_ID, ATLINKBOMB_BLOAT_COLANIM_LENGTH);

            ap->item_vars.link_bomb.scale_index = 1;
        }
        if (ap->lifetime < ATLINKBOMB_BLOAT_BEGIN)
        {
            func_ovl3_801859C0(item_gobj);
        }
        ap->lifetime--;

        return FALSE;
    }
}

void func_ovl3_8018611C(GObj *item_gobj)
{
    func_ovl3_80185CE4(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 2);
}

bool32 jtgt_ovl3_80186150(GObj *item_gobj)
{
    s32 unused;
    Item_Struct *ap = itGetStruct(item_gobj);
    Vec3f vel = ap->phys_info.vel;

    if (func_ovl3_80173D24(item_gobj, 0.4F, 0.3F, &func_ovl3_80185FD8) != FALSE)
    {
        if ((ABSF(vel.x) > ATLINKBOMB_EXPLODE_THRESHOLD_VEL_X) || (ABSF(vel.y) > ATLINKBOMB_EXPLODE_THRESHOLD_VEL_Y))
        {
            func_ovl3_80186368(item_gobj);
        }
    }
    return FALSE;
}

void jtgt_ovl3_80186224(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80185CD4(item_gobj);

    ap->is_damage_all = TRUE;

    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 3);
}

bool32 jtgt_ovl3_80186270(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->item_vars.link_bomb.unk_0x2 != 0)
    {
        ap->item_vars.link_bomb.unk_0x2--;
    }
    else func_ovl3_80185CF0(item_gobj);

    return FALSE;
}

bool32 jtgt_ovl3_801862AC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->item_vars.link_bomb.unk_0x2 == 0)
    {
        func_ovl3_80185BFC(item_gobj);
    }
    return FALSE;
}

bool32 jtgt_ovl3_801862E0(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->item_vars.link_bomb.unk_0x2 == 0)
    {
        func_ovl3_80185B84(item_gobj);
    }
    return FALSE;
}

void jtgt_ovl3_80186314(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80185CD4(item_gobj);

    ap->item_vars.link_bomb.unk_0x2 = 10;

    ap->is_damage_all = TRUE;

    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 4);
}

void func_ovl3_80186368(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->phys_info.vel_air.z = 0.0F;
    ap->phys_info.vel_air.y = 0.0F;
    ap->phys_info.vel_air.x = 0.0F;

    func_ovl3_8017279C(item_gobj);
    func_ovl3_80185A80(item_gobj);
    func_800269C0(1U);
}

extern intptr_t Link_Bomb_Event;

void func_ovl3_801863AC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    itHitEvent *ev = (itHitEvent *)((uintptr_t)*Article_Link_Bomb_Data.p_file + (intptr_t)&Link_Bomb_Event); // Linker thing

    if (ap->it_multi == ev[ap->item_event_index].timer)
    {
        ap->item_hit.angle = ev[ap->item_event_index].angle;
        ap->item_hit.damage = ev[ap->item_event_index].damage;
        ap->item_hit.size = ev[ap->item_event_index].size;

        ap->item_hit.can_rehit_item = TRUE;
        ap->item_hit.can_hop = FALSE;
        ap->item_hit.can_reflect = FALSE;
        ap->item_hit.clang = FALSE;

        ap->item_hit.element = gmHitCollision_Element_Fire;

        ap->item_event_index++;

        if (ap->item_event_index == 4)
        {
            ap->item_event_index = 3;
        }
    }
}

bool32 jtgt_ovl3_80186498(GObj *item_gobj)
{
    func_ovl3_80172FE0(item_gobj);

    return FALSE;
}

bool32 func_ovl3_801864BC(GObj *item_gobj) // Unused
{
    func_ovl3_80185B18(item_gobj);
    func_ovl3_80186368(item_gobj);

    return FALSE;
}

void func_ovl3_801864E8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi = 0;
    ap->item_event_index = 0;

    ap->item_hit.stale = ITEM_STALE_DEFAULT;

    func_ovl3_801863AC(item_gobj);
}

bool32 jtgt_ovl3_80186524(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_801863AC(item_gobj);

    ap->it_multi++;

    if (ap->it_multi == ATLINKBOMB_EXPLODE_LIFETIME)
    {
        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8018656C(GObj *item_gobj)
{
    func_ovl3_801864E8(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Link_Bomb_Status, 5);
}

GObj* func_ovl3_801865A0(GObj *fighter_gobj, Vec3f *pos, Vec3f *vel)
{
    GObj *item_gobj = itManager_CreateItem(fighter_gobj, &Article_Link_Bomb_Data, pos, vel, 0);
    DObj *joint;
    Item_Struct *ap;

    if (item_gobj != NULL)
    {
        ap = itGetStruct(item_gobj);
        joint = DObjGetStruct(item_gobj);

        func_80008CC0(joint, 0x2EU, 0U);
        func_80008CC0(joint->next, 0x2EU, 0U);

        ap->it_multi = 0;

        ap->lifetime = ATLINKBOMB_LIFETIME;

        ap->item_vars.link_bomb.scale_index = 0;
        ap->item_vars.link_bomb.scale_int = ATLINKBOMB_SCALE_INT;

        ap->item_hit.can_rehit_shield = TRUE;

        ap->phys_info.vel_air.z = 0.0F;
        ap->phys_info.vel_air.y = 0.0F;
        ap->phys_info.vel_air.x = 0.0F;

        itMain_PickupSetHoldFighter(item_gobj, fighter_gobj);
    }
    return item_gobj;
}