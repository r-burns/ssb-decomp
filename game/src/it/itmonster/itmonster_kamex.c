#include "item.h"
#include "weapon.h"
#include "fighter.h"

void func_ovl3_80180630(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if (ap->item_vars.kamex.hydro_spawn_wait <= 0)
    {
        Vec3f pos = joint->translate;

        if (ap->it_kind == It_Kind_Kamex)
        {
            pos.x += ATKAMEX_KAMEX_HYDRO_SPAWN_OFF_X * ap->lr;
            pos.y += ATKAMEX_KAMEX_HYDRO_SPAWN_OFF_Y;
        }
        else pos.x += ATKAMEX_OTHER_HYDRO_SPAWN_OFF_X * ap->lr;

        func_ovl3_80180F9C(item_gobj, &pos);
        func_ovl2_801001A8(&pos, ap->lr);
        func_800269C0(0x87U);

        ap->item_vars.kamex.hydro_spawn_wait = rand_u16_range(ATKAMEX_HYDRO_SPAWN_WAIT_RANDOM) + ATKAMEX_HYDRO_SPAWN_WAIT_CONST;

        pos = joint->translate;

        pos.y += ap->attributes->objectcoll_bottom;

        if (ap->it_kind == It_Kind_Kamex)
        {
            pos.x += (ap->attributes->objectcoll_width + ATKAMEX_DUST_SPAWN_OFF_X) * -ap->lr;
        }
        ap->item_vars.kamex.is_apply_push = TRUE;

        ap->phys_info.vel_air.x = -ap->lr * ATKAMEX_CONST_VEL_X;

        func_ovl2_800FF278(&pos, -ap->lr);
    }
}

bool32 jtgt_ovl3_801807DC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATKAMEX_GRAVITY, ATKAMEX_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_80180808(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_801737B8(item_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_RWALL | MPCOLL_MASK_LWALL));

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        func_ovl3_80180A58(item_gobj, TRUE);
        func_ovl3_80180AF4(item_gobj);
    }
    return FALSE;
}

void func_ovl3_80180860(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80173F78(ap);

    ap->phys_info.vel_air.y = 0.0F;
    ap->phys_info.vel_air.x = 0.0F;

    ap->is_allow_pickup = FALSE;

    ap->item_vars.kamex.hydro_push_vel_x = 0.0F;
}

extern itStatusDesc Article_Kamex_Status[];

void func_ovl3_801808A4(GObj *item_gobj)
{
    func_ovl3_80180860(item_gobj);
    itMain_SetItemStatus(item_gobj, Article_Kamex_Status, 0);
}

bool32 jtgt_ovl3_801808D8(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_80172558(ap, ATKAMEX_GRAVITY, ATKAMEX_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_80180904(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    func_ovl3_801737B8(item_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_RWALL | MPCOLL_MASK_LWALL));

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        ap->phys_info.vel_air.y = 0.0F;

        func_ovl3_80180A58(item_gobj, FALSE);
        func_ovl3_80180AF4(item_gobj);
    }
    return FALSE;
}

void func_ovl3_80180964(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    ap->it_multi = ATKAMEX_LIFETIME;

    if (ap->it_kind == It_Kind_Kamex)
    {
        func_800269C0(0x139U);
    }
    itMain_SetItemStatus(item_gobj, Article_Kamex_Status, 1);
}

bool32 jtgt_ovl3_801809BC(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->it_multi == 0)
    {
        return TRUE;
    }
    func_ovl3_80180630(item_gobj);

    if (ap->item_vars.kamex.is_apply_push != FALSE)
    {
        ap->phys_info.vel_air.x += ap->item_vars.kamex.hydro_push_vel_x;
    }
    ap->item_vars.kamex.hydro_spawn_wait--;

    ap->it_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80180A30(GObj *item_gobj)
{
    func_ovl3_801735A0(item_gobj, func_ovl3_801808A4);

    return FALSE;
}

extern intptr_t D_NF_0000EA60;
extern intptr_t D_NF_0000ED60;

void func_ovl3_80180A58(GObj *item_gobj, bool32 is_setup_vars)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    if (is_setup_vars == FALSE)
    {
        ap->it_multi = ATKAMEX_LIFETIME;

        if (ap->it_kind == It_Kind_Kamex)
        {
            void *dl = itGetPData(ap, D_NF_0000EA60, D_NF_0000ED60); // Linker thing

            joint->display_list = dl;

            ap->coll_data.object_coll.top = ATKAMEX_COLL_SIZE;
            ap->coll_data.object_coll.center = 0.0F;
            ap->coll_data.object_coll.bottom = -ATKAMEX_COLL_SIZE;
            ap->coll_data.object_coll.width = ATKAMEX_COLL_SIZE;
        }
    }
    ap->phys_info.vel_air.y = 0;
    ap->phys_info.vel_air.x = 0;

    ap->item_vars.kamex.hydro_push_vel_x = ap->lr * ATKAMEX_PUSH_VEL_X;
    ap->item_vars.kamex.hydro_spawn_wait = 0;
    ap->item_vars.kamex.is_apply_push = FALSE;
}

void func_ovl3_80180AF4(GObj *item_gobj)
{
    itMain_SetItemStatus(item_gobj, Article_Kamex_Status, 2);
}

bool32 jtgt_ovl3_80180B1C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (ap->it_multi == 0)
    {
        ap->phys_info.vel_air.y = 0.0F;

        func_ovl3_80180964(item_gobj);
    }
    ap->it_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80180B6C(GObj *item_gobj)
{
    Item_Struct *ap = itGetStruct(item_gobj);

    if (func_ovl3_801737B8(item_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel_air.y = 0.0F;
    }
    return FALSE;
}

void func_ovl3_80180BAC(GObj *item_gobj)
{
    GObj *fighter_gobj = gOMObjCommonLinks[gOMObjLinkIndexFighter];
    s32 unused1;
    GObj *victim_gobj;
    s32 unused2[3];
    Item_Struct *ap = itGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);
    f32 dist_xy;
    f32 dist_x;
    Vec3f dist;
    f32 square_xy;
    s32 ft_count = 0;

    if (fighter_gobj != NULL)
    {
        do
        {
            Fighter_Struct *fp = ftGetStruct(fighter_gobj);

            if ((fighter_gobj != ap->owner_gobj) && (fp->team != ap->team))
            {
                vec3f_sub(&dist, &DObjGetStruct(fighter_gobj)->translate, &joint->translate);

                if (ft_count == 0)
                {
                    dist_xy = SQUARE(dist.x) + SQUARE(dist.y);
                }
                ft_count++;

                square_xy = SQUARE(dist.x) + SQUARE(dist.y);

                if (square_xy <= dist_xy)
                {
                    dist_xy = square_xy;

                    victim_gobj = fighter_gobj;
                }
            }
            fighter_gobj = fighter_gobj->group_gobj_next;
        } 
        while (fighter_gobj != NULL);
    }
    dist_x = DObjGetStruct(victim_gobj)->translate.x - joint->translate.x;

    ap->lr = (dist_x < 0.0F) ? LEFT : RIGHT;
}

extern intptr_t D_NF_00013624;
extern itCreateDesc Article_Kamex_Data;

GObj *jtgt_ovl3_80180CDC(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *item_gobj = itManager_CreateItem(spawn_gobj, &Article_Kamex_Data, pos, vel, flags);
    DObj *joint;
    Item_Struct *kamex_ap;
    Item_Struct *m_ball_ap;

    if (item_gobj != NULL)
    {
        joint = DObjGetStruct(item_gobj);

        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = *pos;

        kamex_ap = itGetStruct(item_gobj);

        kamex_ap->it_multi = ATMONSTER_RISE_STOP_WAIT;

        kamex_ap->phys_info.vel_air.z = 0.0F;
        kamex_ap->phys_info.vel_air.x = 0.0F;
        kamex_ap->phys_info.vel_air.y = ATMONSTER_RISE_VEL_Y;

        m_ball_ap = itGetStruct(spawn_gobj);

        kamex_ap->owner_gobj = m_ball_ap->owner_gobj;
        kamex_ap->team = m_ball_ap->team;

        func_ovl3_80180BAC(item_gobj);

        if (kamex_ap->lr == LEFT)
        {
            joint->rotate.y = PI32;
        }
        joint->translate.y -= kamex_ap->attributes->objectcoll_bottom;

        func_8000BD1C(joint, itGetPData(kamex_ap, D_NF_0000EA60, D_NF_00013624), 0.0F); // Linker thing
    }
    return item_gobj;
}

bool32 func_ovl3_80180E10(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    DObj *joint = DObjGetStruct(weapon_gobj);

    ip->weapon_hit.offset[0].x = joint->next->translate.x * ip->lr;

    if (wpMain_DecLifeCheckExpire(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80180E60(GObj *weapon_gobj)
{
    return FALSE;
}

bool32 jtgt_ovl3_80180E6C(GObj *weapon_gobj)
{
    Weapon_Struct *ip = wpGetStruct(weapon_gobj);
    Fighter_Struct *fp = ftGetStruct(ip->owner_gobj);

    wpMain_ReflectorInvertLR(ip, fp);

    DObjGetStruct(weapon_gobj)->rotate.z = atan2f(ip->phys_info.vel_air.y, ip->phys_info.vel_air.x);
    DObjGetStruct(weapon_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern wpCreateDesc Item_Hydro_Data;

GObj *func_ovl3_80180EDC(GObj *item_gobj, Vec3f *pos)
{
    Item_Struct *ap = itGetStruct(item_gobj);
    GObj *weapon_gobj = wpManager_CreateWeapon(item_gobj, &Item_Hydro_Data, pos, WEAPON_MASK_SPAWN_ARTICLE);
    DObj *joint;
    s32 unused;
    Weapon_Struct *ip;
    Vec3f translate;

    if (weapon_gobj == NULL)
    {
        return NULL;
    }
    ip = wpGetStruct(weapon_gobj);

    ip->lr = ap->lr;

    joint = DObjGetStruct(weapon_gobj);

    translate = joint->translate;

    func_ovl2_8010066C(&translate, 1.0F);

    if (ip->lr == LEFT)
    {
        joint->rotate.y = PI32;
    }
    ip->weapon_vars.hydro.unk_0x0 = 0; // Set but never used?
    ip->weapon_vars.hydro.unk_0x4 = 0; // Set but never used?

    ip->lifetime = ATKAMEX_HYDRO_LIFETIME;

    return weapon_gobj;
}

void func_ovl3_80180F9C(GObj *item_gobj, Vec3f *pos)
{
    func_ovl3_80180EDC(item_gobj, pos);
}