/***
*
*	Copyright (c) 1996-2001, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
#ifndef WEAPONS_H
#define WEAPONS_H

#include <cassert> //solokiller

#include "effects.h"
#include "weaponinfo.h"

class CBasePlayer;
class CBasePlayerWeapon;
extern int gmsgWeapPickup;

void DeactivateSatchels(CBasePlayer* pOwner);

// Contact Grenade / Timed grenade / Satchel Charge
class CGrenade : public CBaseMonster
{
public:
    void Spawn(void) override;

    using SATCHELCODE = enum { SATCHEL_DETONATE = 0, SATCHEL_RELEASE };

    static CGrenade* ShootTimed(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity, float time);
    static CGrenade* ShootContact(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity);
    static CGrenade* ShootSatchelCharge(entvars_t* pevOwner, Vector vecStart, Vector vecVelocity);
    static void UseSatchelCharges(entvars_t* pevOwner, SATCHELCODE code);

    void Explode(Vector vecSrc, Vector vecAim);
    void Explode(TraceResult* pTrace, int bitsDamageType);
    void EXPORT Smoke(void);

    void EXPORT BounceTouch(CBaseEntity* pOther);
    void EXPORT SlideTouch(CBaseEntity* pOther);
    void EXPORT ExplodeTouch(CBaseEntity* pOther);
    void EXPORT DangerSoundThink(void);
    void EXPORT PreDetonate(void);
    void EXPORT Detonate(void);
    void EXPORT DetonateUse(CBaseEntity* pActivator, CBaseEntity* pCaller, USE_TYPE useType, float value);
    void EXPORT TumbleThink(void);

    virtual void BounceSound(void);
    int BloodColor(void) override { return DONT_BLEED; }
    void Killed(entvars_t* pevAttacker, int iGib) override;

    BOOL m_fRegisteredSound; // whether or not this grenade has issued its DANGER sound to the world sound list yet.
};


// constant items
#define ITEM_HEALTHKIT		1
#define ITEM_ANTIDOTE		2
#define ITEM_SECURITY		3
#define ITEM_BATTERY		4

#define WEAPON_NONE				0
#define WEAPON_CROWBAR			1
#define	WEAPON_GLOCK			2
#define WEAPON_PYTHON			3
#define WEAPON_MP5				4
#define WEAPON_CHAINGUN			5
#define WEAPON_CROSSBOW			6
#define WEAPON_SHOTGUN			7
#define WEAPON_RPG				8
#define WEAPON_GAUSS			9
#define WEAPON_EGON				10
#define WEAPON_HORNETGUN		11
#define WEAPON_HANDGRENADE		12
#define WEAPON_TRIPMINE			13
#define	WEAPON_SATCHEL			14
#define	WEAPON_SNARK			15

#define WEAPON_ALLWEAPONS		(~(1<<WEAPON_SUIT))

#define WEAPON_SUIT				31	// ?????

#define MAX_WEAPONS			32


#define MAX_NORMAL_BATTERY	100


// weapon weight factors (for auto-switching)   (-1 = noswitch)
#define CROWBAR_WEIGHT		0
#define GLOCK_WEIGHT		10
#define PYTHON_WEIGHT		15
#define MP5_WEIGHT			15
#define SHOTGUN_WEIGHT		15
#define CROSSBOW_WEIGHT		10
#define RPG_WEIGHT			20
#define GAUSS_WEIGHT		20
#define EGON_WEIGHT			20
#define HORNETGUN_WEIGHT	10
#define HANDGRENADE_WEIGHT	5
#define SNARK_WEIGHT		5
#define SATCHEL_WEIGHT		-10
#define TRIPMINE_WEIGHT		-10


// weapon clip/carry ammo capacities
#define URANIUM_MAX_CARRY		100
#define	_9MM_MAX_CARRY			250
#define _357_MAX_CARRY			36
#define BUCKSHOT_MAX_CARRY		125
#define BOLT_MAX_CARRY			50
#define ROCKET_MAX_CARRY		5
#define HANDGRENADE_MAX_CARRY	10
#define SATCHEL_MAX_CARRY		5
#define TRIPMINE_MAX_CARRY		5
#define SNARK_MAX_CARRY			15
#define HORNET_MAX_CARRY		8
#define M203_GRENADE_MAX_CARRY	10

// the maximum amount of ammo each weapon's clip can hold
#define WEAPON_NOCLIP			-1

//#define CROWBAR_MAX_CLIP		WEAPON_NOCLIP
#define GLOCK_MAX_CLIP			17
#define PYTHON_MAX_CLIP			6
#define MP5_MAX_CLIP			50
#define MP5_DEFAULT_AMMO		25
#define SHOTGUN_MAX_CLIP		8
#define CROSSBOW_MAX_CLIP		5
#define RPG_MAX_CLIP			1
#define GAUSS_MAX_CLIP			WEAPON_NOCLIP
#define EGON_MAX_CLIP			WEAPON_NOCLIP
#define HORNETGUN_MAX_CLIP		WEAPON_NOCLIP
#define HANDGRENADE_MAX_CLIP	WEAPON_NOCLIP
#define SATCHEL_MAX_CLIP		WEAPON_NOCLIP
#define TRIPMINE_MAX_CLIP		WEAPON_NOCLIP
#define SNARK_MAX_CLIP			WEAPON_NOCLIP


// the default amount of ammo that comes with each gun when it spawns
#define GLOCK_DEFAULT_GIVE			17
#define PYTHON_DEFAULT_GIVE			6
#define MP5_DEFAULT_GIVE			25
#define MP5_DEFAULT_AMMO			25
#define MP5_M203_DEFAULT_GIVE		0
#define SHOTGUN_DEFAULT_GIVE		12
#define CROSSBOW_DEFAULT_GIVE		5
#define RPG_DEFAULT_GIVE			1
#define GAUSS_DEFAULT_GIVE			20
#define EGON_DEFAULT_GIVE			20
#define HANDGRENADE_DEFAULT_GIVE	5
#define SATCHEL_DEFAULT_GIVE		1
#define TRIPMINE_DEFAULT_GIVE		1
#define SNARK_DEFAULT_GIVE			5
#define HIVEHAND_DEFAULT_GIVE		8

// The amount of ammo given to a player by an ammo item.
#define AMMO_URANIUMBOX_GIVE	20
#define AMMO_GLOCKCLIP_GIVE		GLOCK_MAX_CLIP
#define AMMO_357BOX_GIVE		PYTHON_MAX_CLIP
#define AMMO_MP5CLIP_GIVE		MP5_MAX_CLIP
#define AMMO_CHAINBOX_GIVE		200
#define AMMO_M203BOX_GIVE		2
#define AMMO_BUCKSHOTBOX_GIVE	12
#define AMMO_CROSSBOWCLIP_GIVE	CROSSBOW_MAX_CLIP
#define AMMO_RPGCLIP_GIVE		RPG_MAX_CLIP
#define AMMO_URANIUMBOX_GIVE	20
#define AMMO_SNARKBOX_GIVE		5

// bullet types
using Bullet = enum
{
    BULLET_NONE = 0,
    BULLET_PLAYER_9MM,
    // glock
    BULLET_PLAYER_MP5,
    // mp5
    BULLET_PLAYER_357,
    // python
    BULLET_PLAYER_BUCKSHOT,
    // shotgun
    BULLET_PLAYER_CROWBAR,
    // crowbar swipe

    BULLET_MONSTER_9MM,
    BULLET_MONSTER_MP5,
    BULLET_MONSTER_12MM,
};


#define ITEM_FLAG_SELECTONEMPTY		1
#define ITEM_FLAG_NOAUTORELOAD		2
#define ITEM_FLAG_NOAUTOSWITCHEMPTY	4
#define ITEM_FLAG_LIMITINWORLD		8
#define ITEM_FLAG_EXHAUSTIBLE		16 // A player can totally exhaust their ammo supply and lose this weapon

#define WEAPON_IS_ONTARGET 0x40

using ItemInfo = struct
{
    int iSlot;
    int iPosition;
    const char* pszAmmo1; // ammo 1 type
    int iMaxAmmo1; // max ammo 1
    const char* pszAmmo2; // ammo 2 type
    int iMaxAmmo2; // max ammo 2
    const char* pszName;
    int iMaxClip;
    int iId;
    int iFlags;
    int iWeight; // this value used to determine this weapon's importance in autoselection.
};

using AmmoInfo = struct
{
    const char* pszName;
    int iId;
};

// Items that the player has in their inventory that they can use
class CBasePlayerItem : public CBaseAnimating
{
public:
    void SetObjectCollisionBox(void) override;

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    static TYPEDESCRIPTION m_SaveData[];

    virtual int AddToPlayer(CBasePlayer* pPlayer);
    // return TRUE if the item you want the item added to the player inventory
    virtual int AddDuplicate(CBasePlayerItem* pItem) { return FALSE; }
    // return TRUE if you want your duplicate removed from world
    void EXPORT DestroyItem(void);
    void EXPORT DefaultTouch(CBaseEntity* pOther); // default weapon touch
    void EXPORT FallThink(void);
    // when an item is first spawned, this think is run to determine when the object has hit the ground.
    void EXPORT Materialize(void); // make a weapon visible and tangible
    void EXPORT AttemptToMaterialize(void);
    // the weapon desires to become visible and tangible, if the game rules allow for it
    CBaseEntity* Respawn(void) override; // copy a weapon
    void FallInit(void);
    void CheckRespawn(void);
    virtual int GetItemInfo(ItemInfo* p) { return 0; }; // returns 0 if struct not filled out
    virtual BOOL CanDeploy(void) { return TRUE; };

    virtual BOOL Deploy() // returns is deploy was successful
    {
        return TRUE;
    };

    virtual BOOL CanHolster(void) { return TRUE; }; // can this weapon be put away right now?
    virtual void Holster(int skiplocal = 0);
    virtual void UpdateItemInfo(void) { return; };

    virtual void ItemPreFrame(void) { return; } // called each frame by the player PreThink
    virtual void ItemPostFrame(void) { return; } // called each frame by the player PostThink

    virtual void Drop(void);
    virtual void Kill(void);
    virtual void AttachToPlayer(CBasePlayer* pPlayer);

    virtual int PrimaryAmmoIndex() { return -1; };
    virtual int SecondaryAmmoIndex() { return -1; };

    virtual int UpdateClientData(CBasePlayer* pPlayer) { return 0; }

    virtual CBasePlayerWeapon* GetWeaponPtr(void) { return NULL; }

    virtual void GetWeaponData(weapon_data_t& data)
    {
    }

    virtual void SetWeaponData(const weapon_data_t& data)
    {
    }

    virtual void DecrementTimers()
    {
    }

    static ItemInfo ItemInfoArray[MAX_WEAPONS];
    static AmmoInfo AmmoInfoArray[MAX_AMMO_SLOTS];

    CBasePlayer* m_pPlayer;
    CBasePlayerItem* m_pNext;
    int m_iId; // WEAPON_???

    virtual int iItemSlot(void) { return 0; } // return 0 to MAX_ITEMS_SLOTS, used in hud

    int iItemPosition(void) { return ItemInfoArray[m_iId].iPosition; }
    const char* pszAmmo1(void) { return ItemInfoArray[m_iId].pszAmmo1; }
    int iMaxAmmo1(void) { return ItemInfoArray[m_iId].iMaxAmmo1; }
    const char* pszAmmo2(void) { return ItemInfoArray[m_iId].pszAmmo2; }
    int iMaxAmmo2(void) { return ItemInfoArray[m_iId].iMaxAmmo2; }
    const char* pszName(void) { return ItemInfoArray[m_iId].pszName; }
    int iMaxClip(void) { return ItemInfoArray[m_iId].iMaxClip; }
    int iWeight(void) { return ItemInfoArray[m_iId].iWeight; }
    int iFlags(void) { return ItemInfoArray[m_iId].iFlags; }

    // int		m_iIdPrimary;										// Unique Id for primary ammo
    // int		m_iIdSecondary;										// Unique Id for secondary ammo

    //Hack so deploy animations work when weapon prediction is enabled.
    bool m_ForceSendAnimations = false;
};


// inventory items that 
class CBasePlayerWeapon : public CBasePlayerItem
{
public:
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;

    static TYPEDESCRIPTION m_SaveData[];

    void SetNextThink(float delay) override; //LRC

    // generic weapon versions of CBasePlayerItem calls
    int AddToPlayer(CBasePlayer* pPlayer) override;
    int AddDuplicate(CBasePlayerItem* pItem) override;

    virtual int ExtractAmmo(CBasePlayerWeapon* pWeapon);
    //{ return TRUE; };			// Return TRUE if you can add ammo to yourself when picked up
    virtual int ExtractClipAmmo(CBasePlayerWeapon* pWeapon);
    // { return TRUE; };			// Return TRUE if you can add ammo to yourself when picked up

    // generic "shared" ammo handlers
    BOOL AddPrimaryAmmo(CBasePlayerWeapon* origin, int iCount, char* szName, int iMaxClip, int iMaxCarry);
    BOOL AddSecondaryAmmo(int iCount, char* szName, int iMaxCarry);

    void UpdateItemInfo(void) override
    {
    }; // updates HUD state

    int m_iPlayEmptySound;
    int m_fFireOnEmpty; // True when the gun is empty and the player is still holding down the
    // attack key(s)
    virtual BOOL PlayEmptySound(void);
    virtual void ResetEmptySound(void);

    virtual void SendWeaponAnim(int iAnim, int skiplocal = 1, int body = 0);
    // skiplocal is 1 if client is predicting weapon animations

    BOOL CanDeploy(void) override;
    virtual BOOL IsUseable(void);
    BOOL DefaultDeploy(const char* szViewModel, const char* szWeaponModel, int iAnim, const char* szAnimExt,
                       int skiplocal = 0, int body = 0);
    int DefaultReload(int iClipSize, int iAnim, float fDelay, int body = 0);

    void ItemPostFrame(void) override; // called each frame by the player PostThink
    // called by CBasePlayerWeapons ItemPostFrame()
    virtual void PrimaryAttack(void) { return; } // do "+ATTACK"
    virtual void SecondaryAttack(void) { return; } // do "+ATTACK2"
    virtual void Reload(void) { return; } // do "+RELOAD"
    virtual void WeaponIdle(void) { return; } // called when no buttons pressed
    int UpdateClientData(CBasePlayer* pPlayer) override; // sends hud info to client dll, if things have changed
    void RetireWeapon();

    // Can't use virtual functions as think functions so this wrapper is needed.
    void EXPORT CallDoRetireWeapon()
    {
        DoRetireWeapon();
    }

    virtual void DoRetireWeapon();
    virtual BOOL ShouldWeaponIdle(void) { return FALSE; };
    void Holster(int skiplocal = 0) override;
    virtual BOOL UseDecrement(void) { return FALSE; };

    //LRC - used by weaponstrip
    void DrainClip(CBasePlayer* pPlayer, BOOL keep, int i9mm, int i357, int iBuck, int iBolt, int iARGren, int iRock,
                   int iUranium, int iSatchel, int iSnark, int iTrip, int iGren);

    int PrimaryAmmoIndex() override;
    int SecondaryAmmoIndex() override;

    void PrintState(void);

    CBasePlayerWeapon* GetWeaponPtr() override { return this; }
    float GetNextAttackDelay(float delay);

    float m_flPumpTime;
    int m_fInSpecialReload; // Are we in the middle of a reload for the shotguns
    float m_flNextPrimaryAttack; // soonest time ItemPostFrame will call PrimaryAttack
    float m_flNextSecondaryAttack; // soonest time ItemPostFrame will call SecondaryAttack
    float m_flTimeWeaponIdle; // soonest time ItemPostFrame will call WeaponIdle
    int m_iPrimaryAmmoType; // "primary" ammo index into players m_rgAmmo[]
    int m_iSecondaryAmmoType; // "secondary" ammo index into players m_rgAmmo[]
    int m_iClip; // number of shots left in the primary weapon clip, -1 it not used
    int m_iClientClip; // the last version of m_iClip sent to hud dll
    int m_iClientWeaponState; // the last version of the weapon state sent to hud dll (is current weapon, is on target)
    int m_fInReload; // Are we in the middle of a reload;

    int m_iDefaultAmmo; // how much ammo you get when you pick up this weapon as placed by a level designer.

    // hle time creep vars
    float m_flPrevPrimaryAttack;
    float m_flLastFireTime;
};


class CBasePlayerAmmo : public CBaseEntity
{
public:
    void Spawn(void) override;
    void EXPORT DefaultTouch(CBaseEntity* pOther); // default weapon touch
    virtual BOOL AddAmmo(CBaseEntity* pOther) { return TRUE; };

    CBaseEntity* Respawn(void) override;
    void EXPORT Materialize(void);
};


extern DLL_GLOBAL short g_sModelIndexLaser; // holds the index for the laser beam
extern DLL_GLOBAL const char* g_pModelNameLaser;

extern DLL_GLOBAL short g_sModelIndexLaserDot; // holds the index for the laser beam dot
extern DLL_GLOBAL short g_sModelIndexFireball; // holds the index for the fireball
extern DLL_GLOBAL short g_sModelIndexSmoke; // holds the index for the smoke cloud
extern DLL_GLOBAL short g_sModelIndexWExplosion; // holds the index for the underwater explosion
extern DLL_GLOBAL short g_sModelIndexBubbles; // holds the index for the bubbles model
extern DLL_GLOBAL short g_sModelIndexBloodDrop; // holds the sprite index for blood drops
extern DLL_GLOBAL short g_sModelIndexBloodSpray; // holds the sprite index for blood spray (bigger)

extern void ClearMultiDamage(void);
extern void ApplyMultiDamage(entvars_t* pevInflictor, entvars_t* pevAttacker);
extern void AddMultiDamage(entvars_t* pevInflictor, CBaseEntity* pEntity, float flDamage, int bitsDamageType);

extern void DecalGunshot(TraceResult* pTrace, int iBulletType);
extern void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage);
extern int DamageDecal(CBaseEntity* pEntity, int bitsDamageType);
extern void RadiusDamage(Vector vecSrc, entvars_t* pevInflictor, entvars_t* pevAttacker, float flDamage, float flRadius,
                         int iClassIgnore, int bitsDamageType);

using MULTIDAMAGE = struct
{
    CBaseEntity* pEntity;
    float amount;
    int type;
};

extern MULTIDAMAGE gMultiDamage;

class CWeaponRegistry //solokiller
{
public:
    using FactoryFn = CBasePlayerWeapon * (*)(entvars_t* pev);

public:
    CWeaponRegistry(const char* pszMapName, const char* pszDLLClassName, FactoryFn pFactoryFn)
        : m_pszMapName(pszMapName)
          , m_pszDLLClassName(pszDLLClassName)
          , m_pFactoryFn(pFactoryFn)
    {
        //Don't register multiple weapons with the same underlying class
        for (CWeaponRegistry* pReg = m_pHead; pReg; pReg = pReg->GetNext())
        {
            if (!strcmp(pszDLLClassName, pReg->GetDLLClassName()))
            {
                //The problem in question is the wrong name being used to look up HUD sprites and selecting weapons
                //Only use LINK_WEAPON_TO_CLASS for the name used for sprites, and the name the classname is set to in Spawn()
                assert(!"Registering multiple names for the same weapon will cause problems");
                return;
            }
        }

        m_pNext = m_pHead;
        m_pHead = this;
    }

    const char* GetMapName() const { return m_pszMapName; }

    const char* GetDLLClassName() const { return m_pszDLLClassName; }

    FactoryFn GetFactory() const { return m_pFactoryFn; }

    static CWeaponRegistry* GetHead() { return m_pHead; }

    CWeaponRegistry* GetNext() const { return m_pNext; }

private:
    const char* const m_pszMapName;
    const char* const m_pszDLLClassName;
    const FactoryFn m_pFactoryFn;

    static CWeaponRegistry* m_pHead;

    CWeaponRegistry* m_pNext;

private:
    //No copying
    CWeaponRegistry(const CWeaponRegistry&);
    CWeaponRegistry& operator=(const CWeaponRegistry&);
};

#define LINK_WEAPON_TO_CLASS( mapClassName, DLLClassName )															\
static CBasePlayerWeapon* __Create##mapClassName( entvars_t* pev )													\
{																													\
	return static_cast<CBasePlayerWeapon*>( new ( pev ) DLLClassName );												\
}																													\
static CWeaponRegistry __g_##mapClassName##WeaponRegistry( #mapClassName, #DLLClassName, &__Create##mapClassName );	\
LINK_ENTITY_TO_CLASS( mapClassName, DLLClassName )


#define LOUD_GUN_VOLUME			1000
#define NORMAL_GUN_VOLUME		600
#define QUIET_GUN_VOLUME		200

#define	BRIGHT_GUN_FLASH		512
#define NORMAL_GUN_FLASH		256
#define	DIM_GUN_FLASH			128

#define BIG_EXPLOSION_VOLUME	2048
#define NORMAL_EXPLOSION_VOLUME	1024
#define SMALL_EXPLOSION_VOLUME	512

#define	WEAPON_ACTIVITY_VOLUME	64

#define VECTOR_CONE_1DEGREES	Vector( 0.00873, 0.00873, 0.00873 )
#define VECTOR_CONE_2DEGREES	Vector( 0.01745, 0.01745, 0.01745 )
#define VECTOR_CONE_3DEGREES	Vector( 0.02618, 0.02618, 0.02618 )
#define VECTOR_CONE_4DEGREES	Vector( 0.03490, 0.03490, 0.03490 )
#define VECTOR_CONE_5DEGREES	Vector( 0.04362, 0.04362, 0.04362 )
#define VECTOR_CONE_6DEGREES	Vector( 0.05234, 0.05234, 0.05234 )
#define VECTOR_CONE_7DEGREES	Vector( 0.06105, 0.06105, 0.06105 )
#define VECTOR_CONE_8DEGREES	Vector( 0.06976, 0.06976, 0.06976 )
#define VECTOR_CONE_9DEGREES	Vector( 0.07846, 0.07846, 0.07846 )
#define VECTOR_CONE_10DEGREES	Vector( 0.08716, 0.08716, 0.08716 )
#define VECTOR_CONE_15DEGREES	Vector( 0.13053, 0.13053, 0.13053 )
#define VECTOR_CONE_20DEGREES	Vector( 0.17365, 0.17365, 0.17365 )

//=========================================================
// CWeaponBox - a single entity that can store weapons
// and ammo. 
//=========================================================
class CWeaponBox : public CBaseEntity
{
    void Precache(void) override;
    void Spawn(void) override;
    void Touch(CBaseEntity* pOther) override;
    void KeyValue(KeyValueData* pkvd) override;
    BOOL IsEmpty(void);
    int GiveAmmo(int iCount, const char* szName, int iMax, int* pIndex = NULL);
    void SetObjectCollisionBox(void) override;

public:
    void EXPORT Kill(void);
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];

    BOOL HasWeapon(CBasePlayerItem* pCheckItem);
    BOOL PackWeapon(CBasePlayerItem* pWeapon);
    BOOL PackAmmo(int iszName, int iCount);

    CBasePlayerItem* m_rgpPlayerItems[MAX_ITEM_TYPES]; // one slot for each 

    int m_rgiszAmmo[MAX_AMMO_SLOTS]; // ammo names
    int m_rgAmmo[MAX_AMMO_SLOTS]; // ammo quantities

    int m_cAmmoTypes; // how many ammo types packed into this box (if packed by a level designer)
};

#ifdef CLIENT_DLL
bool bIsMultiplayer ( void );
void LoadVModel ( const char *szViewModel, CBasePlayer *m_pPlayer );
#endif

class CGlock : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 2; }
    int GetItemInfo(ItemInfo* p) override;

    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    void GlockFire(float flSpread, float flCycleTime, BOOL fUseAutoAim);
    BOOL Deploy(void) override;
    void Reload(void) override;
    void WeaponIdle(void) override;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    int m_iShell;


    unsigned short m_usFireGlock1;
    unsigned short m_usFireGlock2;
};


class CCrowbar : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 1; }
    void EXPORT SwingAgain(void);
    void EXPORT Smack(void);
    int GetItemInfo(ItemInfo* p) override;

    void PrimaryAttack(void) override;
    int Swing(int fFirst);
    BOOL Deploy(void) override;
    void Holster(int skiplocal = 0) override;
    int m_iSwing;
    TraceResult m_trHit;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usCrowbar;
};

class CPython : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 2; }
    int GetItemInfo(ItemInfo* p) override;
    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    BOOL Deploy(void) override;
    void Holster(int skiplocal = 0) override;
    void Reload(void) override;
    void WeaponIdle(void) override;
    float m_flSoundDelay;

    BOOL m_fInZoom; // don't save this. 

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usFirePython;
};

class CMP5 : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 3; }
    int GetItemInfo(ItemInfo* p) override;

    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    BOOL Deploy(void) override;
    void Reload(void) override;
    void WeaponIdle(void) override;

    BOOL IsUseable() override;

    float m_flNextAnimTime;
    int m_iShell;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usMP5;
    unsigned short m_usMP52;
};

class CCrossbow : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot() override { return 3; }
    int GetItemInfo(ItemInfo* p) override;

    void FireBolt(void);
    void FireSniperBolt(void);
    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    BOOL Deploy() override;
    void Holster(int skiplocal = 0) override;
    void Reload(void) override;
    void WeaponIdle(void) override;

    int m_fInZoom; // don't save this

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usCrossbow;
    unsigned short m_usCrossbow2;
};

class CShotgun : public CBasePlayerWeapon
{
public:
#ifndef CLIENT_DLL
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
#endif


    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot() override { return 3; }
    int GetItemInfo(ItemInfo* p) override;

    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    BOOL Deploy() override;
    void Reload(void) override;
    void WeaponIdle(void) override;
    void ItemPostFrame() override;

    int m_fInReload;
    float m_flNextReload;
    int m_iShell;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usDoubleFire;
    unsigned short m_usSingleFire;
};

class CLaserSpot : public CBaseEntity
{
    void Spawn(void) override;
    void Precache(void) override;

    int ObjectCaps(void) override { return FCAP_DONT_SAVE; }

public:
    void Suspend(float flSuspendTime);
    void EXPORT Revive(void);

    static CLaserSpot* CreateSpot(void);
    static CLaserSpot* CreateSpot(const char* spritename);
};

class CRpg : public CBasePlayerWeapon
{
public:
#ifndef CLIENT_DLL
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
#endif

    void Spawn(void) override;
    void Precache(void) override;
    void Reload(void) override;
    int iItemSlot(void) override { return 4; }
    int GetItemInfo(ItemInfo* p) override;

    BOOL Deploy(void) override;
    BOOL CanHolster(void) override;
    void Holster(int skiplocal = 0) override;

    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    void WeaponIdle(void) override;

    void UpdateSpot(void);
    BOOL ShouldWeaponIdle(void) override { return TRUE; }
    BOOL IsUseable() override;

    CLaserSpot* m_pSpot;
    int m_fSpotActive;
    int m_cActiveRockets; // how many missiles in flight from this launcher right now?

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usRpg;
};

class CRpgRocket : public CGrenade
{
public:
    ~CRpgRocket() override;

    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
    void Spawn(void) override;
    void Precache(void) override;
    void EXPORT FollowThink(void);
    void EXPORT IgniteThink(void);
    void EXPORT RocketTouch(CBaseEntity* pOther);
    static CRpgRocket* CreateRpgRocket(Vector vecOrigin, Vector vecAngles, CBaseEntity* pOwner, CRpg* pLauncher);

    int m_iTrail;
    float m_flIgniteTime;
    EHANDLE m_hLauncher; // handle back to the launcher that fired me. 
};

class CGauss : public CBasePlayerWeapon
{
public:
#ifndef CLIENT_DLL
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
#endif

    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 4; }
    int GetItemInfo(ItemInfo* p) override;

    BOOL Deploy(void) override;
    void Holster(int skiplocal = 0) override;

    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    void WeaponIdle(void) override;

    void StartFire(void);
    void Fire(Vector vecOrigSrc, Vector vecDirShooting, float flDamage);
    float GetFullChargeTime(void);

    int m_iBalls;
    int m_iGlow;
    int m_iBeam;
    int m_iSoundState; // don't save this

    // was this weapon just fired primary or secondary?
    // we need to know so we can pick the right set of effects. 
    BOOL m_fPrimaryFire;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    void SendStopEvent(bool sendToHost) const;
    unsigned short m_usGaussFire = 0;
    unsigned short m_usGaussSpin = 0;
};

class CEgon : public CBasePlayerWeapon
{
public:
#ifndef CLIENT_DLL
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
#endif

    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 4; }
    int GetItemInfo(ItemInfo* p) override;

    BOOL Deploy(void) override;
    void Holster(int skiplocal = 0) override;

    void UpdateEffect(const Vector& startPoint, const Vector& endPoint, float timeBlend);

    void CreateEffect(void);
    void DestroyEffect(void);

    void EndAttack(void);
    void Attack(void);
    void PrimaryAttack(void) override;
    BOOL ShouldWeaponIdle() override { return TRUE; }
    void WeaponIdle(void) override;

    float m_flAmmoUseTime; // since we use < 1 point of ammo per update, we subtract ammo on a timer.

    float GetPulseInterval(void);
    float GetDischargeInterval(void);

    void Fire(const Vector& vecOrigSrc, const Vector& vecDir);

    BOOL HasAmmo(void);

    void UseAmmo(int count);

    enum EGON_FIREMODE { FIRE_NARROW, FIRE_WIDE };

    CBeam* m_pBeam;
    CBeam* m_pNoise;
    CSprite* m_pSprite;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

    unsigned short m_usEgonStop;

private:
    float m_shootTime;
    EGON_FIREMODE m_fireMode;
    float m_shakeTime;
    BOOL m_deployed;

    unsigned short m_usEgonFire;
};

class CHgun : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 4; }
    int GetItemInfo(ItemInfo* p) override;
    int AddToPlayer(CBasePlayer* pPlayer) override;

#ifndef CLIENT_DLL
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
#endif

    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    BOOL Deploy(void) override;
    BOOL IsUseable(void) override;
    void Holster(int skiplocal = 0) override;
    void Reload(void) override;
    void WeaponIdle(void) override;
    float m_flNextAnimTime;

    float m_flRechargeTime;

    int m_iFirePhase; // don't save me.

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usHornetFire;
};


class CHandGrenade : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 5; }
    int GetItemInfo(ItemInfo* p) override;

    void PrimaryAttack(void) override;
    BOOL Deploy(void) override;
    BOOL CanHolster(void) override;
    void Holster(int skiplocal = 0) override;
    void WeaponIdle(void) override;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }
};

class CSatchel : public CBasePlayerWeapon
{
public:
#ifndef CLIENT_DLL
    int Save(CSave& save) override;
    int Restore(CRestore& restore) override;
    static TYPEDESCRIPTION m_SaveData[];
#endif

    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 5; }
    int GetItemInfo(ItemInfo* p) override;
    int AddToPlayer(CBasePlayer* pPlayer) override;
    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    int AddDuplicate(CBasePlayerItem* pOriginal) override;
    BOOL CanDeploy(void) override;
    BOOL Deploy(void) override;
    BOOL IsUseable(void) override;

    void Holster(int skiplocal = 0) override;
    void WeaponIdle(void) override;
    void Throw(void);

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }
};


class CTripmine : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 5; }
    int GetItemInfo(ItemInfo* p) override;

    void SetObjectCollisionBox(void) override
    {
        //!!!BUGBUG - fix the model!
        pev->absmin = pev->origin + Vector(-16, -16, -5);
        pev->absmax = pev->origin + Vector(16, 16, 28);
    }

    void PrimaryAttack(void) override;
    BOOL Deploy(void) override;
    void Holster(int skiplocal = 0) override;
    void WeaponIdle(void) override;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usTripFire;
};

class CSqueak : public CBasePlayerWeapon
{
public:
    void Spawn(void) override;
    void Precache(void) override;
    int iItemSlot(void) override { return 5; }
    int GetItemInfo(ItemInfo* p) override;

    void PrimaryAttack(void) override;
    void SecondaryAttack(void) override;
    BOOL Deploy(void) override;
    void Holster(int skiplocal = 0) override;
    void WeaponIdle(void) override;
    int m_fJustThrown;

    BOOL UseDecrement(void) override
    {
#if defined( CLIENT_WEAPONS )
        return TRUE;
#else
		return FALSE;
#endif
    }

private:
    unsigned short m_usSnarkFire;
};


#endif // WEAPONS_H
