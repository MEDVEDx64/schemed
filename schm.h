/*
 *  ===============================================
 *
 *	schm.h
 *
 *	Header file of Worms Armageddon
 *	game scheme file format library
 *
 *	This file IS NOT a part of original
 *	Worms Armageddon source code, this is
 *	an attempt to represent the scheme system
 *	of W:A. This library can be redistributed
 *	under the terms of GNU General Public License.
 *
 *	(C) MEDVEDx64, 2012,
 *	documentation (C) worms2d.info.
 *	http://worms2d.info/Game_scheme_file
 *
 *	- Last updated: 2012.08.28 -
 *
 *  ===============================================
 */

#ifndef SCHM_H
#define SCHM_H

#include <stdio.h>
#include <malloc.h>

/** Versioning **/
#define SCHM_VERSION_MAJOR 0
#define SCHM_VERSION_MINOR 2
#define SCHM_VERSION_MICRO 1

/*
 The W:A scheme file format contains game settings,
 which define which weapons will be available,
 various game options such as turn time and weapon
 strength, as well as many other settings.
*/

/** Weapons definitions **/
#define WEAPON_BAZOOKA			0
#define WEAPON_HOMING_MISSILE		1
#define WEAPON_MORTAR			2
#define WEAPON_GRENADE			3
#define WEAPON_CLUSTER_BOMB		4
#define WEAPON_SKUNK			5
#define WEAPON_PETROL_BOMB		6
#define WEAPON_BANANA_BOMB		7
#define WEAPON_HANDGUN			8
#define WEAPON_SHOTGUN			9
#define WEAPON_UZI			10
#define WEAPON_MINIGUN			11
#define WEAPON_LONGBOW			12
#define WEAPON_AIRSTRIKE		13
#define WEAPON_NAPALM_STRIKE		14
#define WEAPON_MINE			15
#define WEAPON_FIRE_PUNCH		16
#define WEAPON_DRAGON_BALL		17
#define WEAPON_KAMIKAZE			18
#define WEAPON_PROD			19
#define WEAPON_BATTLE_AXE		20
#define WEAPON_BLOWTORCH		21
#define WEAPON_PNEUMATIC_DRILL		22
#define WEAPON_GIRDER			23
#define WEAPON_NINJA_ROPE		24
#define WEAPON_PARACHUTE		25
#define WEAPON_BUNGEE			26
#define WEAPON_TELEPORT			27
#define WEAPON_DYNAMITE			28
#define WEAPON_SHEEP			29
#define WEAPON_BASEBALL_BAT		30
#define WEAPON_FLAME_THROWER		31
#define WEAPON_HOMING_PIGEON		32
#define WEAPON_MAD_COW			33
#define WEAPON_HOLY_HAND_GRENADE	34
#define WEAPON_OLD_WOMAN		35
#define WEAPON_SHEEP_LAUNCHER		36
#define WEAPON_SUPER_SHEEP		37
#define WEAPON_MOLE_BOMB		38
#define WEAPON_JET_PACK			39
#define WEAPON_LOW_GRAVITY		40
#define WEAPON_LASER_SIGHT		41
#define WEAPON_FAST_WALK		42
#define WEAPON_INVISIBILITY		43
#define WEAPON_DAMAGE_X2		44

/** Super weapons definitions **/
#define WEAPON_FREEZE			45
#define WEAPON_SUPER_BANANA_BOMB		46
#define WEAPON_MINE_STRIKE		47
#define WEAPON_GIRDER_STARTER_PACK	48
#define WEAPON_EARTHQUAKE		49
#define WEAPON_SCALES_OF_JUSTICE		50
#define WEAPON_MING_VASE			51
#define WEAPON_MIKES_CARPET_BOMB		52
#define WEAPON_PATSYS_MAGIC_BULLET	53
#define WEAPON_INDIAN_NUCLEAR_TEST	54
#define WEAPON_SELECT_WORM		55
#define WEAPON_SALVATION_ARMY		56
#define WEAPON_MOLE_SQUADRON		57
#define WEAPON_MB_BOMB			58
#define WEAPON_CONCRETE_DONKEY		59
#define WEAPON_SUICIDE_BOMBER		60
#define WEAPON_SHEEP_STRIKE		61
#define WEAPON_MAIL_STRIKE		62
#define WEAPON_ARMAGEDDON		63

/** Weapon settings structure **/
typedef struct
{
	unsigned char ammo;
	unsigned char power;
	unsigned char delay;
	unsigned char crate_probability;
}
T_WEAPON_SETTINGS;

/** Fields count **/
#define SCHM_FIELDS 38

/** T_WEAPON_SETTINGS fields count **/
#define SCHM_WEAPONS_SETTINGS_FIELDS 4

/** Weapon records count **/
#define WEAPONS 64
#define WEAPONS_OLD_FORMAT 45

/** Scheme file length **/
#define SCHM_LENGTH SCHM_FIELDS + 3\
 + SCHM_WEAPONS_SETTINGS_FIELDS * WEAPONS

 #define SCHM_LENGTH_OLD_FORMAT SCHM_FIELDS + 3\
 + SCHM_WEAPONS_SETTINGS_FIELDS * WEAPONS_OLD_FORMAT

/** File signature definition **/
#define SCHM_SIGNATURE 0x4D484353

/** File version definition **/
 #define SCHM_FILE_VERSION 2
 #define SCHM_FILE_VERSION_OLD 1

/** File format **/
typedef struct
{
	/* Signature. The magic number used to identify
	the WSC file. ASCII: "SCHM" */
	int			signature;

	/* Version. Represents the WSC file version.
	Values: 0x01=Standard Scheme, 0x02=Extended Scheme */
	unsigned char		version;

	/* Hot-Seat Delay. The extra time added between turns,
	used to switch seats and/or plan your turn.
	Values: represent seconds */
	unsigned char		hotseat_delay;

	/* Retreat Time. The time available after using
	a weapon while grounded, used to move to a better
	place before your turn ends. Values: represent seconds */
	unsigned char		retreat_time;

	/* Rope Retreat Time. The time available after
	using a weapon while roping, used to move to
	a better place before your turn ends.
	Values: represent seconds */
	unsigned char		rope_retreat_time;

	/* Display Total Round Time. When enabled,
	the total round time is displayed along with
	the turn time. Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		display_total_round_time;

	/* Automatic Replays. When enabled, the game will
	automatically replay the ending of a significant turn.
	Does not apply to online games. Values: 0x00=Off?,
	0x01=On?, Other=? */
	unsigned char		automatic_replays;

	/* Fall Damage. The amount of damage caused to a worm
	for hitting the ground at a critical velocity.
	Values: see http://worms2d.info/Fall_Damage */
	unsigned char		fall_damage;

	/* Artillery Mode. Known also as, anchored worms.
	When enabled, worms are unable to move around
	by means of walking or jumping.
	Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		artillery_mode;

	/* Bounty Mode. This setting presumably was for
	a planned feature that never got implemented.
	The byte is unused by the game. A suggested use
	for this byte is for scheme editors to save a
	selected Magic Number to distinguish which scheme
	editor was used to encode a scheme.
	Values: 0x00=Unset, 0x89=SchemeEddy */
	unsigned char		bounty_mode;

	/* Stockpiling Mode Determines what happens to
	unused weapons between rounds. This setting only
	matters in matches where more than 1 round is
	meant to be played. Values: 0x00=Off (replenishing),
	0x01=On (accumulating), 0x02=Anti (reducing), Other=? */
	unsigned char		stockpiling_mode;

	/* Worm Select. The method for choosing which worm on
	the team plays the turn. Values: 0x00=Ordered? (off),
	0x01=Optional? (on), 0x02=Random?, Other=? */
	unsigned char		worm_select;

	/* Sudden Death Event. An event that gets triggered
	after the remaining round time reaches zero.
	Values: 0x00=Round Ends (strongest team wins),
	0x01=Nuclear Strike, 0x02=HP Drops to 1,
	0x03=Nothing Happens, Other=? */
	unsigned char		sudden_death_event;

	/* Water Rise Rate. The rate that the water
	rises after each turn during sudden death.
	Values: see http://worms2d.info/Sudden_Death */
	char			water_rise_rate;

	/* Weapon Crate Probability. The relative chance
	that a crate drop will contain weapons.
	Values: see http://worms2d.info/Crate_probability */
	char			weapon_crate_probability;

	/* Donor Cards. When enabled, teams will drop
	a collectible donor card at their defeat.
	Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		donor_cards;

	/* Health Crate Probability. The relative chance
	that crate drop will contain energy.
	Values: see http://worms2d.info/Crate_probability */
	char			health_crate_probability;

	/* Health Crate Energy. The amount of energy gained
	for collecting a health crate drop.
	Values: represent energy amount */
	unsigned char		health_crate_energy;

	/* Utility Crate Probability. The relative chance
	that a crate drop will contain a utility.
	Values: see http://worms2d.info/Crate_probability */
	char			utility_crate_probability;

	/* Hazardous Object Types. Sets what hazards should
	appear on the landscape (and how many for new W:A schemes).
	Values: see http://worms2d.info/Hazardous_Objects */
	unsigned char		hazardous_object_types;

	/* Mine Delay. The amount of time between activating
	a mine and it exploding. Values: 0x04 & 0x80 to 0xFF=Random
	(between 0 & 3 seconds), Other=represents seconds */
	unsigned char		mine_delay;

	/* Dud Mines. When enabled, some landscape mines will
	be triggered as duds. Values: 0x00=Off?,
	0x01=On?, Other=? */
	unsigned char		dud_mines;

	/* Worm Placement. The method in which worms are placed
	onto the landscape at the beginning of the round.
	Values: 0x00=Automatic?, 0x01=Manual?, Other=? */
	unsigned char		worm_placement;

	/* Initial Worm Energy. The amount of energy a worm
	begins a round with. Values: 0x00=game crashes,
	Other=represent energy amount */
	unsigned char		initial_worm_energy;

	/* Turn Time. The amount of time you get to make
	your move. Values: 0x00 to 0x7F=represent seconds,
	0x80 to 0xFF=timer counts up */
	char			turn_time;

	/* Round Time. The amount of time before sudden death
	is triggered. Values: A negative value will result in
	sudden death triggering on the first turn. A value
	above 127 will result in round times that last for
	a specific number of seconds. As this value increase,
	the number of seconds increases by 1, starting with 1
	second for value 128. */
	char			round_time;

	/* Number of Rounds. The number of round wins required
	to win the match. Values: 0x00=1, Other=represent
	number of rounds */
	unsigned char		number_of_rounds;

	/* Blood. When enabled, damaging a worm causes red
	particles to be drawn instead of pink. Values: 0x00=Off?,
	0x01=On?, Other=? */
	unsigned char		blood;

	/* Aqua Sheep. When enabled, super sheep are converted
	to aqua sheep, which can swim under the water.
	Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		aqua_sheep;

	/* Sheep Heaven. When enabled, exploding sheep will
	jump out of destroyed weapon crates. Values: 0x00=Off?,
	0x01=On?, Other=? */
	unsigned char		sheep_heaven;

	/* God Worms. When enabled, all worms have infinite
	health and can only be destroyed by drowning them.
	Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		god_worms;

	/* Indestructible Land. When enabled, the landscape can
	not be destroyed, except by rising water.
	Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		indestructible_land;

	/* Upgraded Grenade. When enabled, grenades are
	more powerful. Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		upgraded_grenade;

	/* Upgraded Shotgun. When enabled, the shotgun
	shoots 2 consecutive shots, giving it 4 shots total.
	Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		upgraded_shotgun;

	/* Upgraded Clusters. When enabled, cluster weapons
	contain even more clusters. Values: 0x00=Off?,
	0x01=On?, Other=? */
	unsigned char		upgraded_clusters;

	/* Upgraded Longbow. When enabled, longbows are
	more powerful. Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		upgraded_longbow;

	/* Team Weapons. When enabled, teams will start the
	match with their preselected team weapon. The team weapon
	setting will override the Ammo, Power, Delay, and Crate
	settings for the 8 team weapons in the scheme (see
	http://worms2d.info/Team_weapons). Values: 0x00=Off?,
	0x01=On?, Other=? */
	unsigned char		team_weapons;

	/* Super Weapons. When enabled, super weapons may appear
	in weapon crate drops (see http://worms2d.info/Crate_probability).
	Values: 0x00=Off?, 0x01=On?, Other=? */
	unsigned char		super_weapons;

	/* Weapon Settings. Individual weapon settings follow. Each
	weapon uses 4 unsigned bytes in the scheme file for weapon
	Ammo, Power, Delay, and Crate Probability settings respectively. */
	T_WEAPON_SETTINGS	weapon_settings[WEAPONS];
}
SCHM_FILE;

/** Funcs **/

/*!
\brief		- Creates and returns a blank (empty) scheme.
*/
SCHM_FILE	schm_blank ();

/*!
\brief		- Loads a scheme file.
\param fname	- File name.
\returns	- Loaded scheme. If the loading has failed, this
			func will return a blank SCHM_FILE with
			error code in the signature field,
			where 1 means that the file has failed
			to open; 2 - the file have invalid
			length; 3 - the file have wrong signature.
*/
SCHM_FILE	schm_load ( const char* fname );

/*!
\brief		- Writes a scheme to file.
\param fname	- File name.
\param scheme	- Scheme structure, which will be saved.
\returns	- 0 on success, 1 on failure.
*/
int		schm_save ( const char* fname, SCHM_FILE scheme );

#endif /* SCHM_H */
