#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>
#include <game/src/mp/mpcoll.h>
#include <game/src/wp/weaponvars.h>
#include <game/src/gm/gmmisc.h>
#include <game/src/gm/gmsound.h>
#include <game/src/sys/develop.h>
#include <game/src/gm/gmmatch.h>

#define WEAPON_ALLOC_MAX 32                     // Allocate this many weapon user_data structs at once

#define WEAPON_STALE_DEFAULT 1.0F

#define WEAPON_TEAM_DEFAULT 4
#define WEAPON_PORT_DEFAULT GMMATCH_PLAYERS_MAX
#define WEAPON_HANDICAP_DEFAULT 9               // CPU level?

#define WEAPON_FLAG_PROJECT (1 << 31)           // Perform initial collision check when spawning weapon?

#define WEAPON_MASK_SPAWN_FIGHTER 0               // Weapon spawned by fighter
#define WEAPON_MASK_SPAWN_GROUND 1                // Weapon spawned by stage
#define WEAPON_MASK_SPAWN_WEAPON 2                // Weapon spawned by another weapon
#define WEAPON_MASK_SPAWN_ARTICLE 3               // ItWeaponem spawned by Pok�mon / misc entity class(es?)

#define WEAPON_MASK_SPAWN_ALL 0xF                 // Mask all GObj classes that can spawn weapons?

// Universal item hitbox attributes

#define WEAPON_REHIT_TIME_DEFAULT 16            // If the weapon is multihit, its hitbox will refresh per victim after this many frames have passed

#define WEAPON_REFLECT_TIME_DEFAULT 100         // Maximum damage cap for reflected weapons
#define WEAPON_REFLECT_MUL_DEFAULT 1.8F         // Universal reflect damage multiplier
#define WEAPON_REFLECT_ADD_DEFAULT 0.99F        // Added after multiplying weapon's hitbox damage

#define WEAPON_STALE_ADD_DEFAULT 0.999F         // Bonus 1% added after multiplying hitbox damage with staling modifier

#define WEAPON_HOP_ANGLE_DEFAULT F_DEG_TO_RAD(135.0F) // 2.3561945F - Determines whether weapon bounces off a shield

typedef enum Wp_Kind
{
    Wp_Kind_Fireball,
    Wp_Kind_Blaster,
    Wp_Kind_ChargeShot,
    Wp_Kind_SamusBomb,
    Wp_Kind_Cutter,
    Wp_Kind_EggThrow,
    Wp_Kind_YoshiStar,
    Wp_Kind_Boomerang,
    Wp_Kind_SpinAttack,
    Wp_Kind_ThunderJoltAir,
    Wp_Kind_ThunderJoltGround,
    Wp_Kind_ThunderHead,
    Wp_Kind_ThunderTrail,
    Wp_Kind_PKFire,
    Wp_Kind_PKThunderHead,
    Wp_Kind_PKThunderTrail,
    Wp_Kind_YubiBulletSingle,
    Wp_Kind_YubiBulletTriple,
    Wp_Kind_LGunAmmo = 0x14,
    Wp_Kind_FFlowerFlame

} Wp_Kind;

typedef struct wpCreateDesc
{
    u8 unk_0x0;
    s32 wp_kind;
    void **p_item; // Pointer to various item data
    intptr_t offset_wp_hit; // Offset of item hitbox info
    u8 unk_0x10;
    u8 unk_0x11;
    u8 unk_0x12;
    u8 unk_0x13;
    bool32 (*proc_update)(GObj*);
    bool32 (*proc_map)(GObj*);
    bool32 (*proc_hit)(GObj*);
    bool32 (*proc_shield)(GObj*);
    bool32 (*proc_hop)(GObj*);
    bool32 (*proc_setoff)(GObj*);
    bool32 (*proc_reflector)(GObj*);
    bool32 (*proc_absorb)(GObj*);

} wpCreateDesc;

typedef struct wpCommonAttributes // Moreso hitbox stuff
{
    void *unk_0x0;
    void *unk_0x4;
    void *unk_0x8;
    void *unk_0xC;
    Vec3h offset[2];
    s16 objectcoll_top;
    s16 objectcoll_center;
    s16 objectcoll_bottom;
    s16 objectcoll_width;
    u16 size;
    s32 angle : 10;
    u32 knockback_scale : 10;
    u32 damage : 8;
    u32 element : 4;
    u32 knockback_weight : 10;
    s32 shield_damage : 8;
    u32 hitbox_count : 2;
    u32 clang : 1;
    u32 sfx : 10;
    u32 priority : 3;
    u32 can_rehit_item : 1;
    u32 can_rehit_fighter : 1;
    u32 can_hop : 1;
    u32 can_reflect : 1;
    u32 can_absorb : 1;
    u32 can_shield : 1;
    u32 flags_0x2F_b6 : 1;
    u32 flags_0x2F_b7 : 1;
    u32 knockback_base : 10;

} wpCommonAttributes;

typedef struct wpHitPositions
{
    Vec3f pos;
    Vec3f pos_prev;
    s32 unused1;
    u8 filler[0x5C - 0x1C];
    f32 unused2;

} wpHitPositions;

typedef struct _Weapon_Hit
{
    s32 update_state; // 0 = disabled, 1 = new hitbox, 2 and 3 = interpolate/copy current position to previous
    s32 damage; // 0x4
    f32 stale; // Multiplies damage
    s32 element; // 0xC // Placed AFTER offset?
    Vec3f offset[2]; // 0x10 - 0x24
    f32 size;
    s32 angle;
    u32 knockback_scale; // Unconfirmed
    u32 knockback_weight; // Weight-Dependent Set Knockback
    u32 knockback_base; // Base knockback
    s32 shield_damage;
    s32 priority; // Used to determine winner in item hitbox vs item hitbox interaction?
    u8 interact_mask; // Mask of object classes hitbox can interact with; 0x1 = fighters, 0x2 = items, 0x4 = articles
    u16 hit_sfx;
    u32 clang : 1;
    u32 can_rehit_item : 1;
    u32 can_rehit_fighter : 1;
    u32 can_rehit_shield : 1;
    u32 can_hop : 1; // Actually determines whether item's shield deflect routine can run?
    u32 can_reflect : 1;
    u32 can_absorb : 1;
    u32 noheal : 1;
    u32 can_shield : 1;
    u32 attack_id : 6;
    u16 motion_count;
    gmStatFlags stat_flags;
    u16 stat_count;
    s32 hitbox_count;
    wpHitPositions hit_positions[2];
    gmHitCollisionRecord hit_targets[4];

} Weapon_Hit;

typedef struct _Weapon_Struct
{
    void *wp_alloc_next;                // Memory region allocated for next Item_Struct
    GObj *weapon_gobj;                  // Weapon's GObj pointer
    GObj *owner_gobj;                   // Weapon's owner
    s32 wp_kind;                        // Weapon ID
    u8 team;                            // Weapon's team
    u8 port_id;                         // Weapon's port index
    u8 handicap;                        // Weapon's handicap
    s32 player_number;                  // Weapon's player number
    s32 lr;                             // Weapon's facing direction; -1 = LEFT, 0 = CENTER, 1 = RIGHT, 2 = WALL_UP (Thunder Jolt only?), 3 = WALL_DOWN (Thunder Jolt only?)

    struct
    {
        f32 vel_ground;                 // Weapon's ground velocity
        Vec3f vel_air;                  // Weapon's aerial velocity

    } phys_info;

    Coll_Data coll_data;                // Weapon's collision data

    gmCollisionGA ground_or_air;        // Ground or air bool

    Weapon_Hit weapon_hit;              // Weapon's hitbox

    s32 hit_victim_damage;              // Damage applied to entity this weapon has hit
    s32 hit_reflect_damage;             // Damage on reflection?
    s32 hit_attack_damage;              // Damage weapon dealt to other attack
    s32 hit_shield_damage;              // Damage weapon dealt to shield
    f32 shield_collide_angle;           // Angle at which item collided with shield?
    Vec3f shield_collide_vec;           // Position of shield this item collided with?
    GObj *reflect_gobj;                 // GObj that reflected this weapon
    gmStatFlags reflect_stat_flags;     // Status flags of GObj reflecting this item (e.g. is_smash_attack, is_ground_or_air, is_special_attack, etc.)
    u16 reflect_stat_count;             // Status update count at the time the item is reflected?
    GObj *absorb_gobj;                  // GObj that absorbed this item

    u32 is_hitlag_victim : 1;           // Weapon can deal hitlag to target
    u32 is_hitlag_item : 1;             // Weapon is in hitlag

    u32 group_id;                       // Weapon's group, identical group IDs => hitbox victim records across are linked?

    s32 lifetime;                       // Weapon's duration in frames

    u32 is_camera_follow : 1;           // Camera will attempt to follow the weapon
    u32 is_static_damage : 1;           // Ignore reflect multiplier if TRUE

    gmSoundEffect *p_sfx;               // Pointer to weapon's current ongoing sound effect
    u16 sfx_id;                         // ID of sound effect this weapon is supposed to play? (This gets checked against gmSoundEffect's ID when despawning)

    bool32 (*proc_update)(GObj*);       // Update general weapon information
    bool32 (*proc_map)(GObj*);          // Update weapon's map collision
    bool32 (*proc_hit)(GObj*);          // Runs when weapon collides with a hurtbox
    bool32 (*proc_shield)(GObj*);       // Runs when weapon collides with a shield
    bool32 (*proc_hop)(GObj*);          // Runs when weapon bounces off a shield
    bool32 (*proc_setoff)(GObj*);       // Runs when weapon's hitbox collides with another hitbox
    bool32 (*proc_reflector)(GObj*);    // Runs when weapon is reflected
    bool32 (*proc_absorb)(GObj*);       // Runs when weapon takes damage
    bool32 (*proc_dead)(GObj*);         // Runs when weapon is in a blast zone

    union weapon_vars                   // Weapon-specific state variables
    {
        wpMario_WeaponVars_Fireball fireball;
        wpSamus_WeaponVars_ChargeShot charge_shot;
        wpSamus_WeaponVars_Bomb samus_bomb;
        wpPikachu_WeaponVars_ThunderJolt thunder_jolt;
        wpPikachu_WeaponVars_Thunder thunder;
        wpNess_WeaponVars_PKThunder pkthunder;
        wpNess_WeaponVars_PKThunderTrail pkthunder_trail;
        wpYoshi_WeaponVars_EggThrow egg_throw;
        wpLink_WeaponVars_SpinAttack spin_attack; // Link's Up Special
        wpLink_WeaponVars_Boomerang boomerang;
        wpStarRod_WeaponVars_Star star;
        wpIwark_WeaponVars_Rock rock; // Onix's Rock Slide
        wpNyars_WeaponVars_Coin coin;
        wpKamex_WeaponVars_Hydro hydro;
        wpDogas_WeaponVars_Smog smog;

    } weapon_vars;

    s32 display_state;                  // Weapon's display mode: 0 = normal, 1 = hit collisions, 2 = opaque hurtboxes + outlined attack hitboxes, 3 = map collisions

} Weapon_Struct;

#define wpGetStruct(weapon_gobj) \
((Weapon_Struct*) (weapon_gobj)->user_data) \

#endif