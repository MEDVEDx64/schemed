/*
 *  schemed.c - W:A scheme file editor
 *  (C) MEDVEDx64, 13-17.5.2012, 27-28.8.2012, 28.10.2012
 */

#include <stdlib.h>
#include <string.h>
#include "schm.h"

#define SCHEMED_VERSION "0.2.3 beta"
#define SCHEMED_DATE "2012.10.28" /* last updated */
#define DEF_FNAME "out.wsc"
#define ARG_IS_INCOMP "%cIgnoring incompleted argument: %s\n"

#define _RW_RUBBER WEAPON_ARMAGEDDON
#define _RW_GRAVITY WEAPON_MAIL_STRIKE
#define _RW_VISC WEAPON_CONCRETE_DONKEY
#define _RW_WIND WEAPON_SUICIDE_BOMBER
#define _RW_ANTISINK WEAPON_SHEEP_STRIKE
#define _RW_FRICTION WEAPON_SALVATION_ARMY
#define _RB_SDET 0
#define _RW_SDET WEAPON_MOLE_SQUADRON
#define _RB_LDET 1
#define _RW_LDET WEAPON_MOLE_SQUADRON
#define _RB_FDPT 2
#define _RW_FDPT WEAPON_MOLE_SQUADRON
#define _RB_IR 3
#define _RW_IR WEAPON_MOLE_SQUADRON
#define _RB_CRATESHOWER 4
#define _RW_CRATESHOWER WEAPON_MOLE_SQUADRON
#define _RW_VERSION WEAPON_SELECT_WORM
#define _RW_CRATERATE WEAPON_INDIAN_NUCLEAR_TEST
#define _RW_CRATELIMIT WEAPON_PATSYS_MAGIC_BULLET
#define _RW_KNOCK WEAPON_SUPER_BANANA_BOMB

#define _RB_WDCA 6
#define _RW_WDCA WEAPON_MOLE_SQUADRON
#define _RB_OPE 5
#define _RW_OPE WEAPON_MOLE_SQUADRON
#define _RW_FLAMES WEAPON_SCALES_OF_JUSTICE
#define _R__KAOSMOD0 0
#define _R__KAOSMOD1 16
#define _R__KAOSMOD2 48
#define _R__KAOSMOD3 80
#define _R__KAOSMOD4 112
#define _R__KAOSMOD5 144
#define _RW_KAOSMOD WEAPON_EARTHQUAKE
//#define _R__SPEED 16
//#define _R__SPEED_TS 32
//#define _R__SPEED_NOLIM 255
#define _RW_SPEED WEAPON_MINE_STRIKE
#define _R__TS8 164
#define _RW_TS8 WEAPON_SELECT_WORM
#define _RB_FUSEEX 7
#define _RW_FUSEEX WEAPON_MOLE_SQUADRON
#define _R__SWAT 1
#define _RW_SWAT WEAPON_MB_BOMB
#define _RB_REAIM 0
#define _RW_REAIM WEAPON_EARTHQUAKE
#define _RB_CIRA 1
#define _RW_CIRA WEAPON_EARTHQUAKE
#define _RB_ALP 2
#define _RW_ALP WEAPON_EARTHQUAKE
#define _RB_USW 3
#define _RW_USW WEAPON_EARTHQUAKE

#define _R__GLUE 0
#define _R__ICE 99
#define _R__DEFG 0

unsigned char
bitmod              /* Thanks to A.A.C. */
(unsigned char in, unsigned char bitnum, unsigned char target)
{
    unsigned char out = 0;
    if (target)
        out = in | (1 << bitnum);
    else
        out = in & ~(1 << bitnum);
    return out;
}

void
schmprint(SCHM_FILE _scheme)
{
    printf("Signature: 0x%x\n", _scheme.signature);
    printf("Verion: %d\n", _scheme.version);
	printf("Hot-seat delay: %d\n", _scheme.hotseat_delay);
	printf("Retreat time: %d\n", _scheme.retreat_time);
	printf("Rope retreat time: %d\n", _scheme.rope_retreat_time);
	printf("Display total round time: %d\n", _scheme.display_total_round_time);
	printf("Automatic replays: %d\n", _scheme.automatic_replays);
	printf("Fall damage: %d\n", _scheme.fall_damage);
	printf("Artillery mode: %d\n", _scheme.artillery_mode);
	printf("Bounty mode: %d\n", _scheme.bounty_mode);
	printf("Stockpiling mode: %d\n", _scheme.stockpiling_mode);
	printf("Worm select: %d\n", _scheme.worm_select);
	printf("Sudden death event: %d\n", _scheme.sudden_death_event);
	printf("Water rise rate: %d\n", _scheme.water_rise_rate);
	printf("Weapon crate probability: %d\n", _scheme.weapon_crate_probability);
	printf("Donor cards: %d\n", _scheme.donor_cards);
	printf("Health crate probability: %d\n", _scheme.health_crate_probability);
	printf("Health crate energy: %d\n", _scheme.health_crate_energy);
	printf("Utility crate probability: %d\n", _scheme.utility_crate_probability);
	printf("Hazardous object types: %d\n", _scheme.hazardous_object_types);
	printf("Mine delay: %d\n", _scheme.mine_delay);
	printf("Dud mines: %d\n", _scheme.dud_mines);
	printf("Worm placement: %d\n", _scheme.worm_placement);
	printf("Initial worm energy: %d\n", _scheme.initial_worm_energy);
	printf("Turn time: %d\n", _scheme.turn_time);
	printf("Round time: %d\n", _scheme.round_time);
	printf("Number of rounds: %d\n", _scheme.number_of_rounds);
	printf("Blood: %d\n", _scheme.blood);
	printf("Aqua sheep: %d\n", _scheme.aqua_sheep);
	printf("Sheep Heaven: %d\n", _scheme.sheep_heaven);
	printf("God worms: %d\n", _scheme.god_worms);
	printf("Indestructible land: %d\n", _scheme.indestructible_land);
	printf("Upgraded grenades: %d\n", _scheme.upgraded_grenade);
	printf("Upgraded shotgun: %d\n", _scheme.upgraded_shotgun);
	printf("Upgraded clusters: %d\n", _scheme.upgraded_clusters);
	printf("Upgraded longbow: %d\n", _scheme.upgraded_longbow);
	printf("Team weapons: %d\n", _scheme.team_weapons);
	printf("Super weapons: %d\n", _scheme.super_weapons);

    printf("\n");
    printf("Weapons tab:\n");

	unsigned char idx = 0;
	while ( idx < WEAPONS )
	{
		printf("%d:%c%d%c%d%c%d%c%d\n",
        idx, 9,
        _scheme.weapon_settings[idx].ammo, 9,
		_scheme.weapon_settings[idx].power + 1, 9,
		_scheme.weapon_settings[idx].delay, 9,
		_scheme.weapon_settings[idx].crate_probability);
		idx ++ ;
	}
}

int main(int argc, char *argv[])
{
    char ifname[0x2000];
    char ofname[0x2000];
    SCHM_FILE scheme;
    int is_ifname = 0;
    int is_ofname = 0;
    int is_nowrite = 0;
    int is_print = 0;

    int z;
    for(z = 1; z < argc; z++)
    {
        if(!strcmp(argv[z], "-h") ||
            !strcmp(argv[z], "--help"))
            {
                printf(
                       "Usage: %s [arguments]\n\
\n\
Short list of the basic args:\n\
-a, --about%c%c%cDisplay the About message and exit\n\
-h, --help%c%c%cDisplay this Help message and exit\n\
-i [FILE], --input [FILE]%cInput file name\n\
-o [FILE], --output [FILE]%cOutput file name\n\
-n, --no-write%c%c%cForbids any writing operations\n\
-p, --print%c%c%cPrint the containment of the input file,\n\
        or output, if the output file is specified\n\
\n\
There's too many available options, so i can only\n\
present an usage example here, which adds an unlimited\n\
and full-powered Ninja Rope to the scheme:\n\
%s -i scheme.wsc -wnr0 10 -wnr1 5\n\
or\n\
%s --input scheme.wsc --ninja-rope-ammo 10 --ninja-rope-power 5\n",
                       argv[0],9,9,9,9,9,9,9,9,9,9,9,9,9,9,argv[0],argv[0]);
                return 0;
            }
        if(!strcmp(argv[z], "-a") ||
            !strcmp(argv[z], "--about"))
            {
                printf(
                       "schemed - terminal W:A scheme file editor\n\
version "SCHEMED_VERSION" (MEDVEDx64, "SCHEMED_DATE")\n");
                return 0;
            }
    }

    int i;
    for(i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], "-i") ||
            !strcmp(argv[i], "--input") ||
            !strcmp(argv[i], "--input-file"))
            {
                if(i<argc-1)
                {
                    strcpy(ifname, argv[i+1]);
                    is_ifname = 1;
                }
                else printf(ARG_IS_INCOMP, 9, argv[i]);
            }
        if(!strcmp(argv[i], "-o") ||
            !strcmp(argv[i], "--output") ||
            !strcmp(argv[i], "--output-file"))
            {
                if(i<argc-1)
                {
                    strcpy(ofname, argv[i+1]);
                    is_ofname = 1;
                }
                else printf(ARG_IS_INCOMP, 9, argv[i]);
            }
        if(!strcmp(argv[i], "-n") ||
            !strcmp(argv[i], "--no-write")) is_nowrite = 1;
        if(!strcmp(argv[i], "-p") ||
            !strcmp(argv[i], "--print")) is_print = 1;
    }

    if(is_ifname) scheme = schm_load(ifname);
    else scheme = schm_blank();

    if(scheme.signature != SCHM_SIGNATURE && is_ifname)
    {
        if(scheme.signature == 1)
        {
            printf("Unable to open the file: %s\n", ifname);
            return 2;
        }
        if(scheme.signature == 2)
        {
            printf("The file have invalid length: %s\n", ifname);
            return 3;
        }
        if(scheme.signature == 3)
        {
            printf("The file have wrong signature: %s\n", ifname);
            return 4;
        }
        else
        {
            printf("An unknown error happened while opening the file: %s.\n", ifname);
            return -1;
        }
    }

    if(is_nowrite)
    {
        if(is_print) schmprint(scheme);
        return 0;
    }

    int y;
    for(y = 1; y < argc; y++)
    {
        if(!strcmp(argv[y], "-rkaosmod") && y<argc-1)
        {
            switch(atoi(argv[y+1]))
            {
                case 1:
                scheme.weapon_settings[_RW_KAOSMOD].crate_probability = _R__KAOSMOD1; break;
                case 2:
                scheme.weapon_settings[_RW_KAOSMOD].crate_probability = _R__KAOSMOD2; break;
                case 3:
                scheme.weapon_settings[_RW_KAOSMOD].crate_probability = _R__KAOSMOD3; break;
                case 4:
                scheme.weapon_settings[_RW_KAOSMOD].crate_probability = _R__KAOSMOD4; break;
                case 5:
                scheme.weapon_settings[_RW_KAOSMOD].crate_probability = _R__KAOSMOD5; break;
                default:
                scheme.weapon_settings[_RW_KAOSMOD].crate_probability = _R__KAOSMOD0; break;
            }
        }
    }

    int x;
    for(x = 1; x < argc; x++)
    {
        if(!strcmp(argv[x], "-a") || !strcmp(argv[x], "--about"));
        else if(!strcmp(argv[x], "-h") || !strcmp(argv[x], "--help"));
        else if(!strcmp(argv[x], "-i") || !strcmp(argv[x], "--input") ||
            !strcmp(argv[x], "--input-file"));
        else if(!strcmp(argv[x], "-o") || !strcmp(argv[x], "--output") ||
            !strcmp(argv[x], "--output-file"));
        else if(!strcmp(argv[x], "-n") ||
            !strcmp(argv[x], "--no-write"));
        else if(!strcmp(argv[x], "-p") || !strcmp(argv[x], "--print"));
        else if(!strcmp(argv[x], "-rkaosmod"));

        /* ========================================================================================================= */
        /* Game params */
        /* ========================================================================================================= */

        else if(!strcmp(argv[x], "--version") || !strcmp(argv[x], "-fv")) {
            if(x<argc-1) scheme.version = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--hotseat-delay") || !strcmp(argv[x], "-fhd")) {
            if(x<argc-1) scheme.hotseat_delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--retreat-time") || !strcmp(argv[x], "-fret")) {
            if(x<argc-1) scheme.retreat_time = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--rope-retreat-time") || !strcmp(argv[x], "-frrt")) {
            if(x<argc-1) scheme.rope_retreat_time = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--display-total-round-time") || !strcmp(argv[x], "-fdtrt")) {
            if(x<argc-1) scheme.display_total_round_time = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--automatic-replays") || !strcmp(argv[x], "-far")) {
            if(x<argc-1) scheme.automatic_replays = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--fall-damage") || !strcmp(argv[x], "-ffd")) {
            if(x<argc-1) scheme.fall_damage = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--artillery-mode") || !strcmp(argv[x], "-fam")) {
            if(x<argc-1) scheme.artillery_mode = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--bounty-mode") || !strcmp(argv[x], "-fbm")) {
            if(x<argc-1) scheme.bounty_mode = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--stockpiling-mode") || !strcmp(argv[x], "-fsm")) {
            if(x<argc-1) scheme.stockpiling_mode = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--worm-select") || !strcmp(argv[x], "-fws")) {
            if(x<argc-1) scheme.worm_select = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--sudden-death-event") || !strcmp(argv[x], "-fsde")) {
            if(x<argc-1) scheme.sudden_death_event = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--water-rise-rate") || !strcmp(argv[x], "-fwrr")) {
            if(x<argc-1) scheme.water_rise_rate = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--weapon-crate-probability") || !strcmp(argv[x], "-fwcp")) {
            if(x<argc-1) scheme.weapon_crate_probability = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--donor-cards") || !strcmp(argv[x], "-fdc")) {
            if(x<argc-1) scheme.donor_cards = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--health-crate-probability") || !strcmp(argv[x], "-fhcp")) {
            if(x<argc-1) scheme.health_crate_probability = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--health-crate-energy") || !strcmp(argv[x], "-fhce")) {
            if(x<argc-1) scheme.health_crate_energy = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--utility-crate-probability") || !strcmp(argv[x], "-fucp")) {
            if(x<argc-1) scheme.utility_crate_probability = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--hazardous-object-types") || !strcmp(argv[x], "-fhot")) {
            if(x<argc-1) scheme.hazardous_object_types = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mine-delay") || !strcmp(argv[x], "-fmd")) {
            if(x<argc-1) scheme.mine_delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--dud-mines") || !strcmp(argv[x], "-fdm")) {
            if(x<argc-1) scheme.dud_mines = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--worm-placement") || !strcmp(argv[x], "-fwp")) {
            if(x<argc-1) scheme.worm_placement = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--initial-worm-energy") || !strcmp(argv[x], "-fiwe")) {
            if(x<argc-1) scheme.initial_worm_energy = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--turn-time") || !strcmp(argv[x], "-ftt")) {
            if(x<argc-1) scheme.turn_time = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--round-time") || !strcmp(argv[x], "-frot")) {
            if(x<argc-1) scheme.round_time = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--number-of-rounds") || !strcmp(argv[x], "-fnor")) {
            if(x<argc-1) scheme.number_of_rounds = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--blood") || !strcmp(argv[x], "-fb")) {
            if(x<argc-1) scheme.blood = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--aqua-sheep") || !strcmp(argv[x], "-fas")) {
            if(x<argc-1) scheme.aqua_sheep = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--sheep-heaven") || !strcmp(argv[x], "-fsh")) {
            if(x<argc-1) scheme.sheep_heaven = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--god-worms") || !strcmp(argv[x], "-fgw")) {
            if(x<argc-1) scheme.god_worms = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--indestructible-land") || !strcmp(argv[x], "-fil")) {
            if(x<argc-1) scheme.indestructible_land = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--upgraded-grenade") || !strcmp(argv[x], "-fug")) {
            if(x<argc-1) scheme.upgraded_grenade = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--upgraded-shotgun") || !strcmp(argv[x], "-fus")) {
            if(x<argc-1) scheme.upgraded_shotgun = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--upgraded-clusters") || !strcmp(argv[x], "-fuc")) {
            if(x<argc-1) scheme.upgraded_clusters = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--upgraded-longbow") || !strcmp(argv[x], "-ful")) {
            if(x<argc-1) scheme.upgraded_longbow = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--team-weapons") || !strcmp(argv[x], "-ftw")) {
            if(x<argc-1) scheme.team_weapons = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--super-weapons") || !strcmp(argv[x], "-fsw")) {
            if(x<argc-1) scheme.super_weapons = atoi(argv[x+1]); }

        /* ========================================================================================================= */
        /* Std. Weapons */
        /* ========================================================================================================= */

        else if(!strcmp(argv[x], "--bazooka-ammo") || !strcmp(argv[x], "-wba0") || !strcmp(argv[x], "-w000")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BAZOOKA].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--bazooka-power") || !strcmp(argv[x], "-wba1") || !strcmp(argv[x], "-w001")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BAZOOKA].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--bazooka-delay") || !strcmp(argv[x], "-wba2") || !strcmp(argv[x], "-w002")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BAZOOKA].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--bazooka-crate-probability") || !strcmp(argv[x], "-wba3") || !strcmp(argv[x], "-w003")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BAZOOKA].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--homing-missle-ammo") || !strcmp(argv[x], "-whm0") || !strcmp(argv[x], "-w010")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOMING_MISSILE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--homing-missle-power") || !strcmp(argv[x], "-whm1") || !strcmp(argv[x], "-w011")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOMING_MISSILE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--homing-missle-delay") || !strcmp(argv[x], "-whm2") || !strcmp(argv[x], "-w012")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOMING_MISSILE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--homing-missle-crate-probability") || !strcmp(argv[x], "-whm3") || !strcmp(argv[x], "-w013")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOMING_MISSILE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mortar-ammo") || !strcmp(argv[x], "-wmo0") || !strcmp(argv[x], "-w020")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MORTAR].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mortar-power") || !strcmp(argv[x], "-wmo1") || !strcmp(argv[x], "-w021")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MORTAR].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mortar-delay") || !strcmp(argv[x], "-wmo2") || !strcmp(argv[x], "-w022")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MORTAR].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mortar-crate-probability") || !strcmp(argv[x], "-wmo3") || !strcmp(argv[x], "-w023")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MORTAR].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--grenade-ammo") || !strcmp(argv[x], "-wgr0") || !strcmp(argv[x], "-w030")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GRENADE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--grenade-power") || !strcmp(argv[x], "-wgr1") || !strcmp(argv[x], "-w031")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GRENADE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--grenade-delay") || !strcmp(argv[x], "-wgr2") || !strcmp(argv[x], "-w032")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GRENADE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--grenade-crate-probability") || !strcmp(argv[x], "-wgr3") || !strcmp(argv[x], "-w033")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GRENADE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--cluster-bomb-ammo") || !strcmp(argv[x], "-wcb0") || !strcmp(argv[x], "-w040")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_CLUSTER_BOMB].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--cluster-bomb-power") || !strcmp(argv[x], "-wcb1") || !strcmp(argv[x], "-w041")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_CLUSTER_BOMB].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--cluster-bomb-delay") || !strcmp(argv[x], "-wcb2") || !strcmp(argv[x], "-w042")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_CLUSTER_BOMB].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--cluster-bomb-crate-probability") || !strcmp(argv[x], "-wcb3") || !strcmp(argv[x], "-w043")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_CLUSTER_BOMB].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--skunk-ammo") || !strcmp(argv[x], "-wsk0") || !strcmp(argv[x], "-w050")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SKUNK].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--skunk-power") || !strcmp(argv[x], "-wsk1") || !strcmp(argv[x], "-w051")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SKUNK].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--skunk-delay") || !strcmp(argv[x], "-wsk2") || !strcmp(argv[x], "-w052")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SKUNK].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--skunk-crate-probability") || !strcmp(argv[x], "-wsk3") || !strcmp(argv[x], "-w053")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SKUNK].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--petrol-bomb-ammo") || !strcmp(argv[x], "-wpb0") || !strcmp(argv[x], "-w060")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PETROL_BOMB].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--petrol-bomb-power") || !strcmp(argv[x], "-wpb1") || !strcmp(argv[x], "-w061")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PETROL_BOMB].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--petrol-bomb-delay") || !strcmp(argv[x], "-wpb2") || !strcmp(argv[x], "-w062")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PETROL_BOMB].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--petrol-bomb-crate-probability") || !strcmp(argv[x], "-wpb3") || !strcmp(argv[x], "-w063")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PETROL_BOMB].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--banana-bomb-ammo") || !strcmp(argv[x], "-wbbo0") || !strcmp(argv[x], "-w070")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BANANA_BOMB].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--banana-bomb-power") || !strcmp(argv[x], "-wbbo1") || !strcmp(argv[x], "-w071")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BANANA_BOMB].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--banana-bomb-delay") || !strcmp(argv[x], "-wbbo2") || !strcmp(argv[x], "-w072")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BANANA_BOMB].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--banana-bomb-crate-probability") || !strcmp(argv[x], "-wbbo3") || !strcmp(argv[x], "-w073")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BANANA_BOMB].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--handgun-ammo") || !strcmp(argv[x], "-wh0") || !strcmp(argv[x], "-w080")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HANDGUN].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--handgun-power") || !strcmp(argv[x], "-wh1") || !strcmp(argv[x], "-w081")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HANDGUN].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--handgun-delay") || !strcmp(argv[x], "-wh2") || !strcmp(argv[x], "-w082")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HANDGUN].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--handgun-crate-probability") || !strcmp(argv[x], "-wh3") || !strcmp(argv[x], "-w083")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HANDGUN].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--shotgun-ammo") || !strcmp(argv[x], "-wsho0") || !strcmp(argv[x], "-w090")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHOTGUN].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--shotgun-power") || !strcmp(argv[x], "-wsho1") || !strcmp(argv[x], "-w091")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHOTGUN].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--shotgun-delay") || !strcmp(argv[x], "-wsho2") || !strcmp(argv[x], "-w092")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHOTGUN].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--shotgun-crate-probability") || !strcmp(argv[x], "-wsho3") || !strcmp(argv[x], "-w093")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHOTGUN].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--uzi-ammo") || !strcmp(argv[x], "-wu0") || !strcmp(argv[x], "-w100")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_UZI].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--uzi-power") || !strcmp(argv[x], "-wu1") || !strcmp(argv[x], "-w101")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_UZI].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--uzi-delay") || !strcmp(argv[x], "-wu2") || !strcmp(argv[x], "-w102")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_UZI].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--uzi-crate-probability") || !strcmp(argv[x], "-wu3") || !strcmp(argv[x], "-w103")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_UZI].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--minigun-ammo") || !strcmp(argv[x], "-wmini0") || !strcmp(argv[x], "-w110")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINIGUN].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--minigun-power") || !strcmp(argv[x], "-wmini1") || !strcmp(argv[x], "-w111")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINIGUN].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--minigun-delay") || !strcmp(argv[x], "-wmini2") || !strcmp(argv[x], "-w112")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINIGUN].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--minigun-crate-probability") || !strcmp(argv[x], "-wmini3") || !strcmp(argv[x], "-w113")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINIGUN].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--longbow-ammo") || !strcmp(argv[x], "-wl0") || !strcmp(argv[x], "-w120")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LONGBOW].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--longbow-power") || !strcmp(argv[x], "-wl1") || !strcmp(argv[x], "-w121")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LONGBOW].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--longbow-delay") || !strcmp(argv[x], "-wl2") || !strcmp(argv[x], "-w122")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LONGBOW].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--longbow-crate-probability") || !strcmp(argv[x], "-wl3") || !strcmp(argv[x], "-w123")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LONGBOW].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--airstrike-ammo") || !strcmp(argv[x], "-wai0") || !strcmp(argv[x], "-w130")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_AIRSTRIKE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--airstrike-power") || !strcmp(argv[x], "-wai1") || !strcmp(argv[x], "-w131")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_AIRSTRIKE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--airstrike-delay") || !strcmp(argv[x], "-wai2") || !strcmp(argv[x], "-w132")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_AIRSTRIKE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--airstrike-crate-probability") || !strcmp(argv[x], "-wai3") || !strcmp(argv[x], "-w133")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_AIRSTRIKE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--napalm-strike-ammo") || !strcmp(argv[x], "-wns0") || !strcmp(argv[x], "-w140")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_NAPALM_STRIKE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--napalm-strike-power") || !strcmp(argv[x], "-wns1") || !strcmp(argv[x], "-w141")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_NAPALM_STRIKE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--napalm-strike-delay") || !strcmp(argv[x], "-wns2") || !strcmp(argv[x], "-w142")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_NAPALM_STRIKE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--napalm-strike-crate-probability") || !strcmp(argv[x], "-wns3") || !strcmp(argv[x], "-w143")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_NAPALM_STRIKE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mine-ammo") || !strcmp(argv[x], "-wmine0") || !strcmp(argv[x], "-w150")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mine-power") || !strcmp(argv[x], "-wmine1") || !strcmp(argv[x], "-w151")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mine-delay") || !strcmp(argv[x], "-wmine2") || !strcmp(argv[x], "-w152")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mine-crate-probability") || !strcmp(argv[x], "-wmine3") || !strcmp(argv[x], "-w153")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--fire-punch-ammo") || !strcmp(argv[x], "-wfp0") || !strcmp(argv[x], "-w160")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FIRE_PUNCH].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--fire-punch-power") || !strcmp(argv[x], "-wfp1") || !strcmp(argv[x], "-w161")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FIRE_PUNCH].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--fire-punch-delay") || !strcmp(argv[x], "-wfp2") || !strcmp(argv[x], "-w162")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FIRE_PUNCH].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--fire-punch-crate-probability") || !strcmp(argv[x], "-wfp3") || !strcmp(argv[x], "-w163")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FIRE_PUNCH].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--dragon-ball-ammo") || !strcmp(argv[x], "-wdb0") || !strcmp(argv[x], "-w170")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DRAGON_BALL].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--dragon-ball-power") || !strcmp(argv[x], "-wdb1") || !strcmp(argv[x], "-w171")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DRAGON_BALL].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--dragon-ball-delay") || !strcmp(argv[x], "-wdb2") || !strcmp(argv[x], "-w172")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DRAGON_BALL].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--dragon-ball-crate-probability") || !strcmp(argv[x], "-wdb3") || !strcmp(argv[x], "-w173")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DRAGON_BALL].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--kamikaze-ammo") || !strcmp(argv[x], "-wk0") || !strcmp(argv[x], "-w180")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_KAMIKAZE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--kamikaze-power") || !strcmp(argv[x], "-wk1") || !strcmp(argv[x], "-w181")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_KAMIKAZE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--kamikaze-delay") || !strcmp(argv[x], "-wk2") || !strcmp(argv[x], "-w182")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_KAMIKAZE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--kamikaze-crate-probability") || !strcmp(argv[x], "-wk3") || !strcmp(argv[x], "-w183")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_KAMIKAZE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--prod-ammo") || !strcmp(argv[x], "-wpr0") || !strcmp(argv[x], "-w190")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PROD].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--prod-power") || !strcmp(argv[x], "-wpr1") || !strcmp(argv[x], "-w191")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PROD].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--prod-delay") || !strcmp(argv[x], "-wpr2") || !strcmp(argv[x], "-w192")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PROD].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--prod-crate-probability") || !strcmp(argv[x], "-wpr3") || !strcmp(argv[x], "-w193")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PROD].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--battle-axe-ammo") || !strcmp(argv[x], "-waxe0") || !strcmp(argv[x], "-w200")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BATTLE_AXE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--battle-axe-power") || !strcmp(argv[x], "-waxe1") || !strcmp(argv[x], "-w201")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BATTLE_AXE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--battle-axe-delay") || !strcmp(argv[x], "-waxe2") || !strcmp(argv[x], "-w202")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BATTLE_AXE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--battle-axe-crate-probability") || !strcmp(argv[x], "-waxe3") || !strcmp(argv[x], "-w203")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BATTLE_AXE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--blowtorch-ammo") || !strcmp(argv[x], "-wbl0") || !strcmp(argv[x], "-w210")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BLOWTORCH].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--blowtorch-power") || !strcmp(argv[x], "-wbl1") || !strcmp(argv[x], "-w211")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BLOWTORCH].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--blowtorch-delay") || !strcmp(argv[x], "-wbl2") || !strcmp(argv[x], "-w212")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BLOWTORCH].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--blowtorch-crate-probability") || !strcmp(argv[x], "-wbl3") || !strcmp(argv[x], "-w213")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BLOWTORCH].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--pneumatic-drill-ammo") || !strcmp(argv[x], "-wpd0") || !strcmp(argv[x], "-w220")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PNEUMATIC_DRILL].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--pneumatic-drill-power") || !strcmp(argv[x], "-wpd1") || !strcmp(argv[x], "-w221")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PNEUMATIC_DRILL].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--pneumatic-drill-delay") || !strcmp(argv[x], "-wpd2") || !strcmp(argv[x], "-w222")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PNEUMATIC_DRILL].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--pneumatic-drill-crate-probability") || !strcmp(argv[x], "-wpd3") || !strcmp(argv[x], "-w223")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PNEUMATIC_DRILL].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--girder-ammo") || !strcmp(argv[x], "-wgi0") || !strcmp(argv[x], "-w230")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GIRDER].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--girder-power") || !strcmp(argv[x], "-wgi1") || !strcmp(argv[x], "-w231")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GIRDER].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--girder-delay") || !strcmp(argv[x], "-wgi2") || !strcmp(argv[x], "-w232")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GIRDER].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--girder-crate-probability") || !strcmp(argv[x], "-wgi3") || !strcmp(argv[x], "-w233")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GIRDER].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--ninja-rope-ammo") || !strcmp(argv[x], "-wnr0") || !strcmp(argv[x], "-w240")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_NINJA_ROPE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--ninja-rope-power") || !strcmp(argv[x], "-wnr1") || !strcmp(argv[x], "-w241")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_NINJA_ROPE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--ninja-rope-delay") || !strcmp(argv[x], "-wnr2") || !strcmp(argv[x], "-w242")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_NINJA_ROPE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--ninja-rope-crate-probability") || !strcmp(argv[x], "-wnr3") || !strcmp(argv[x], "-w243")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_NINJA_ROPE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--parachute-ammo") || !strcmp(argv[x], "--chute-ammo") ||
                !strcmp(argv[x], "-wpa0") || !strcmp(argv[x], "-w250")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PARACHUTE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--parachute-power") || !strcmp(argv[x], "--chute-power") ||
                !strcmp(argv[x], "-wpa1") || !strcmp(argv[x], "-w251")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PARACHUTE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--parachute-delay") || !strcmp(argv[x], "--chute-delay") ||
                !strcmp(argv[x], "-wpa2") || !strcmp(argv[x], "-w252")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PARACHUTE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--parachute-crate-probability") || !strcmp(argv[x], "--chute-crate-probability") ||
                !strcmp(argv[x], "-wpa3") || !strcmp(argv[x], "-w253")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PARACHUTE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--bungee-ammo") || !strcmp(argv[x], "-wbu0") || !strcmp(argv[x], "-w260")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BUNGEE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--bungee-power") || !strcmp(argv[x], "-wbu1") || !strcmp(argv[x], "-w261")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BUNGEE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--bungee-delay") || !strcmp(argv[x], "-wbu2") || !strcmp(argv[x], "-w262")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BUNGEE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--bungee-crate-probability") || !strcmp(argv[x], "-wbu3") || !strcmp(argv[x], "-w263")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BUNGEE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--teleport-ammo") || !strcmp(argv[x], "-wt0") || !strcmp(argv[x], "-w270")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_TELEPORT].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--teleport-power") || !strcmp(argv[x], "-wt1") || !strcmp(argv[x], "-w271")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_TELEPORT].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--teleport-delay") || !strcmp(argv[x], "-wt2") || !strcmp(argv[x], "-w272")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_TELEPORT].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--teleport-crate-probability") || !strcmp(argv[x], "-wt3") || !strcmp(argv[x], "-w273")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_TELEPORT].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--dynamite-ammo") || !strcmp(argv[x], "-wd0") || !strcmp(argv[x], "-w280")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DYNAMITE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--dynamite-power") || !strcmp(argv[x], "-wd1") || !strcmp(argv[x], "-w281")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DYNAMITE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--dynamite-delay") || !strcmp(argv[x], "-wd2") || !strcmp(argv[x], "-w282")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DYNAMITE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--dynamite-crate-probability") || !strcmp(argv[x], "-wd3") || !strcmp(argv[x], "-w283")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DYNAMITE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--sheep-ammo") || !strcmp(argv[x], "-wsh0") || !strcmp(argv[x], "-w290")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--sheep-power") || !strcmp(argv[x], "-wsh1") || !strcmp(argv[x], "-w291")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--sheep-delay") || !strcmp(argv[x], "-wsh2") || !strcmp(argv[x], "-w292")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--sheep-crate-probability") || !strcmp(argv[x], "-wsh3") || !strcmp(argv[x], "-w293")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--baseball-bat-ammo") || !strcmp(argv[x], "-wbba0") || !strcmp(argv[x], "-w300")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BASEBALL_BAT].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--baseball-bat-power") || !strcmp(argv[x], "-wbba1") || !strcmp(argv[x], "-w301")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BASEBALL_BAT].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--baseball-bat-delay") || !strcmp(argv[x], "-wbba2") || !strcmp(argv[x], "-w302")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BASEBALL_BAT].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--baseball-bat-crate-probability") || !strcmp(argv[x], "-wbba3") || !strcmp(argv[x], "-w303")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_BASEBALL_BAT].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--flame-thrower-ammo") || !strcmp(argv[x], "-wft0") || !strcmp(argv[x], "-w310")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FLAME_THROWER].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--flame-thrower-power") || !strcmp(argv[x], "-wft1") || !strcmp(argv[x], "-w311")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FLAME_THROWER].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--flame-thrower-delay") || !strcmp(argv[x], "-wft2") || !strcmp(argv[x], "-w312")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FLAME_THROWER].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--flame-thrower-crate-probability") || !strcmp(argv[x], "-wft3") || !strcmp(argv[x], "-w313")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FLAME_THROWER].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--homing-pigeon-ammo") || !strcmp(argv[x], "-whp0") || !strcmp(argv[x], "-w320")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOMING_PIGEON].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--homing-pigeon-power") || !strcmp(argv[x], "-whp1") || !strcmp(argv[x], "-w321")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOMING_PIGEON].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--homing-pigeon-delay") || !strcmp(argv[x], "-whp2") || !strcmp(argv[x], "-w322")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOMING_PIGEON].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--homing-pigeon-crate-probability") || !strcmp(argv[x], "-whp3") || !strcmp(argv[x], "-w323")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOMING_PIGEON].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mad-cow-ammo") || !strcmp(argv[x], "-wmc0") || !strcmp(argv[x], "-w330")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MAD_COW].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mad-cow-power") || !strcmp(argv[x], "-wmc1") || !strcmp(argv[x], "-w331")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MAD_COW].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mad-cow-delay") || !strcmp(argv[x], "-wmc2") || !strcmp(argv[x], "-w332")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MAD_COW].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mad-cow-crate-probability") || !strcmp(argv[x], "-wmc3") || !strcmp(argv[x], "-w333")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MAD_COW].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--holy-hand-grenade-ammo") || !strcmp(argv[x], "-whhg0") || !strcmp(argv[x], "-w340")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOLY_HAND_GRENADE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--holy-hand-grenade-power") || !strcmp(argv[x], "-whhg1") || !strcmp(argv[x], "-w341")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOLY_HAND_GRENADE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--holy-hand-grenade-delay") || !strcmp(argv[x], "-whhg2") || !strcmp(argv[x], "-w342")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOLY_HAND_GRENADE].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--holy-hand-grenade-crate-probability") || !strcmp(argv[x], "-whhg3") || !strcmp(argv[x], "-w343")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_HOLY_HAND_GRENADE].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--old-woman-ammo") || !strcmp(argv[x], "-wow0") || !strcmp(argv[x], "-w350")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_OLD_WOMAN].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--old-woman-power") || !strcmp(argv[x], "-wow1") || !strcmp(argv[x], "-w351")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_OLD_WOMAN].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--old-woman-delay") || !strcmp(argv[x], "-wow2") || !strcmp(argv[x], "-w352")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_OLD_WOMAN].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--old-woman-crate-probability") || !strcmp(argv[x], "-wow3") || !strcmp(argv[x], "-w353")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_OLD_WOMAN].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--sheep-launcher-ammo") || !strcmp(argv[x], "-wsl0") || !strcmp(argv[x], "-w360")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP_LAUNCHER].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--sheep-launcher-power") || !strcmp(argv[x], "-wsl1") || !strcmp(argv[x], "-w361")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP_LAUNCHER].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--sheep-launcher-delay") || !strcmp(argv[x], "-wsl2") || !strcmp(argv[x], "-w362")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP_LAUNCHER].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--sheep-launcher-crate-probability") || !strcmp(argv[x], "-wsl3") || !strcmp(argv[x], "-w363")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP_LAUNCHER].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--super-sheep-ammo") || !strcmp(argv[x], "-wssh0") || !strcmp(argv[x], "-w370")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUPER_SHEEP].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--super-sheep-power") || !strcmp(argv[x], "-wssh1") || !strcmp(argv[x], "-w371")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUPER_SHEEP].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--super-sheep-delay") || !strcmp(argv[x], "-wssh2") || !strcmp(argv[x], "-w372")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUPER_SHEEP].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--super-sheep-crate-probability") || !strcmp(argv[x], "-wssh3") || !strcmp(argv[x], "-w373")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUPER_SHEEP].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mole-bomb-ammo") || !strcmp(argv[x], "-wmb0") || !strcmp(argv[x], "-w380")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MOLE_BOMB].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mole-bomb-power") || !strcmp(argv[x], "-wmb1") || !strcmp(argv[x], "-w381")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MOLE_BOMB].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mole-bomb-delay") || !strcmp(argv[x], "-wmb2") || !strcmp(argv[x], "-w382")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MOLE_BOMB].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mole-bomb-crate-probability") || !strcmp(argv[x], "-wmb3") || !strcmp(argv[x], "-w383")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MOLE_BOMB].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--jet-pack-ammo") || !strcmp(argv[x], "-wjp0") || !strcmp(argv[x], "-w390")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_JET_PACK].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--jet-pack-power") || !strcmp(argv[x], "-wjp1") || !strcmp(argv[x], "-w391")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_JET_PACK].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--jet-pack-delay") || !strcmp(argv[x], "-wjp2") || !strcmp(argv[x], "-w392")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_JET_PACK].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--jet-pack-crate-probability") || !strcmp(argv[x], "-wjp3") || !strcmp(argv[x], "-w393")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_JET_PACK].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--low-gravity-ammo") || !strcmp(argv[x], "-wlg0") || !strcmp(argv[x], "-w400")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LOW_GRAVITY].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--low-gravity-power") || !strcmp(argv[x], "-wlg1") || !strcmp(argv[x], "-w401")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LOW_GRAVITY].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--low-gravity-delay") || !strcmp(argv[x], "-wlg2") || !strcmp(argv[x], "-w402")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LOW_GRAVITY].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--low-gravity-crate-probability") || !strcmp(argv[x], "-wlg3") || !strcmp(argv[x], "-w403")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LOW_GRAVITY].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--laser-sight-ammo") || !strcmp(argv[x], "-wls0") || !strcmp(argv[x], "-w410")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LASER_SIGHT].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--laser-sight-power") || !strcmp(argv[x], "-wls1") || !strcmp(argv[x], "-w411")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LASER_SIGHT].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--laser-sight-delay") || !strcmp(argv[x], "-wls2") || !strcmp(argv[x], "-w412")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LASER_SIGHT].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--laser-sight-crate-probability") || !strcmp(argv[x], "-wls3") || !strcmp(argv[x], "-w413")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_LASER_SIGHT].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--fast-walk-ammo") || !strcmp(argv[x], "-wfw0") || !strcmp(argv[x], "-w420")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FAST_WALK].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--fast-walk-power") || !strcmp(argv[x], "-wfw1") || !strcmp(argv[x], "-w421")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FAST_WALK].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--fast-walk-delay") || !strcmp(argv[x], "-wfw2") || !strcmp(argv[x], "-w422")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FAST_WALK].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--fast-walk-crate-probability") || !strcmp(argv[x], "-wfw3") || !strcmp(argv[x], "-w423")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FAST_WALK].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--invisibility-ammo") || !strcmp(argv[x], "-wi0") || !strcmp(argv[x], "-w430")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_INVISIBILITY].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--invisibility-power") || !strcmp(argv[x], "-wi1") || !strcmp(argv[x], "-w431")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_INVISIBILITY].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--invisibility-delay") || !strcmp(argv[x], "-wi2") || !strcmp(argv[x], "-w432")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_INVISIBILITY].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--invisibility-crate-probability") || !strcmp(argv[x], "-wi3") || !strcmp(argv[x], "-w433")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_INVISIBILITY].crate_probability = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--damage-x2-ammo") || !strcmp(argv[x], "-wdd0") || !strcmp(argv[x], "-w440")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DAMAGE_X2].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--damage-x2-power") || !strcmp(argv[x], "-wdd1") || !strcmp(argv[x], "-w441")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DAMAGE_X2].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--damage-x2-delay") || !strcmp(argv[x], "-wdd2") || !strcmp(argv[x], "-w442")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DAMAGE_X2].delay = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--damage-x2-crate-probability") || !strcmp(argv[x], "-wdd3") || !strcmp(argv[x], "-w443")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_DAMAGE_X2].crate_probability = atoi(argv[x+1]); }

        /* ========================================================================================================= */
        /* Super Weapons */
        /* ========================================================================================================= */

        else if(!strcmp(argv[x], "--freeze-ammo") || !strcmp(argv[x], "-wf0") || !strcmp(argv[x], "-w450")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FREEZE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--freeze-power") || !strcmp(argv[x], "-wf1") || !strcmp(argv[x], "-w451")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FREEZE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--freeze-delay") || !strcmp(argv[x], "-wf2") || !strcmp(argv[x], "-w452")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_FREEZE].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--super-banana-bomb-ammo") || !strcmp(argv[x], "-wsbb0") || !strcmp(argv[x], "-w460")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUPER_BANANA_BOMB].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--super-banana-bomb-power") || !strcmp(argv[x], "-wsbb1") || !strcmp(argv[x], "-w461")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUPER_BANANA_BOMB].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--super-banana-bomb-delay") || !strcmp(argv[x], "-wsbb2") || !strcmp(argv[x], "-w462")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUPER_BANANA_BOMB].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mine-strike-ammo") || !strcmp(argv[x], "-wmist0") || !strcmp(argv[x], "-w470")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINE_STRIKE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mine-strike-power") || !strcmp(argv[x], "-wmist1") || !strcmp(argv[x], "-w471")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINE_STRIKE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mine-strike-delay") || !strcmp(argv[x], "-wmist2") || !strcmp(argv[x], "-w472")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MINE_STRIKE].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--girder-starter-pack-ammo") || !strcmp(argv[x], "-wgsp0") || !strcmp(argv[x], "-w480")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GIRDER_STARTER_PACK].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--girder-starter-pack-power") || !strcmp(argv[x], "-wgsp1") || !strcmp(argv[x], "-w481")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GIRDER_STARTER_PACK].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--girder-starter-pack-delay") || !strcmp(argv[x], "-wgsp2") || !strcmp(argv[x], "-w482")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_GIRDER_STARTER_PACK].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--earthquake-ammo") || !strcmp(argv[x], "-we0") || !strcmp(argv[x], "-w490")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_EARTHQUAKE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--earthquake-power") || !strcmp(argv[x], "-we1") || !strcmp(argv[x], "-w491")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_EARTHQUAKE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--earthquake-delay") || !strcmp(argv[x], "-we2") || !strcmp(argv[x], "-w492")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_EARTHQUAKE].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--scales-of-justice-ammo") || !strcmp(argv[x], "-wsoj0") || !strcmp(argv[x], "-w500")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SCALES_OF_JUSTICE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--scales-of-justice-power") || !strcmp(argv[x], "-wsoj1") || !strcmp(argv[x], "-w501")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SCALES_OF_JUSTICE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--scales-of-justice-delay") || !strcmp(argv[x], "-wsoj2") || !strcmp(argv[x], "-w502")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SCALES_OF_JUSTICE].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--ming-vase-ammo") || !strcmp(argv[x], "-wmv0") || !strcmp(argv[x], "-w510")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MING_VASE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--ming-vase-power") || !strcmp(argv[x], "-wmv1") || !strcmp(argv[x], "-w511")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MING_VASE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--ming-vase-delay") || !strcmp(argv[x], "-wmv2") || !strcmp(argv[x], "-w512")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MING_VASE].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mikes-carpet-bomb-ammo") || !strcmp(argv[x], "-wmcb0") || !strcmp(argv[x], "-w520")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MIKES_CARPET_BOMB].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mikes-carpet-bomb-power") || !strcmp(argv[x], "-wmcb1") || !strcmp(argv[x], "-w521")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MIKES_CARPET_BOMB].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mikes-carpet-bomb-delay") || !strcmp(argv[x], "-wmcb2") || !strcmp(argv[x], "-w522")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MIKES_CARPET_BOMB].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--patsys-magic-bullet-ammo") || !strcmp(argv[x], "-wpmb0") || !strcmp(argv[x], "-w530")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PATSYS_MAGIC_BULLET].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--patsys-magic-bullet-power") || !strcmp(argv[x], "-wpmb1") || !strcmp(argv[x], "-w531")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PATSYS_MAGIC_BULLET].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--patsys-magic-bullet-delay") || !strcmp(argv[x], "-wpmb2") || !strcmp(argv[x], "-w532")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_PATSYS_MAGIC_BULLET].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--indian-nuclear-test-ammo") || !strcmp(argv[x], "-wint0") || !strcmp(argv[x], "-w540")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_INDIAN_NUCLEAR_TEST].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--indian-nuclear-test-power") || !strcmp(argv[x], "-wint1") || !strcmp(argv[x], "-w541")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_INDIAN_NUCLEAR_TEST].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--indian-nuclear-test-delay") || !strcmp(argv[x], "-wint2") || !strcmp(argv[x], "-w542")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_INDIAN_NUCLEAR_TEST].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--select-worm-ammo") || !strcmp(argv[x], "-wsw0") || !strcmp(argv[x], "-w550")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SELECT_WORM].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--select-worm-power") || !strcmp(argv[x], "-wsw1") || !strcmp(argv[x], "-w551")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SELECT_WORM].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--select-worm-delay") || !strcmp(argv[x], "-wsw2") || !strcmp(argv[x], "-w552")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SELECT_WORM].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--salvation-army-ammo") || !strcmp(argv[x], "-wsa0") || !strcmp(argv[x], "-w560")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SALVATION_ARMY].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--salvation-army-power") || !strcmp(argv[x], "-wsa1") || !strcmp(argv[x], "-w561")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SALVATION_ARMY].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--salvation-army-delay") || !strcmp(argv[x], "-wsa2") || !strcmp(argv[x], "-w562")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SALVATION_ARMY].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mole-squadron-ammo") || !strcmp(argv[x], "-wmsq0") || !strcmp(argv[x], "-w570")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MOLE_SQUADRON].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mole-squadron-power") || !strcmp(argv[x], "-wmsq1") || !strcmp(argv[x], "-w571")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MOLE_SQUADRON].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mole-squadron-delay") || !strcmp(argv[x], "-wmsq2") || !strcmp(argv[x], "-w572")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MOLE_SQUADRON].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mb-bomb-ammo") || !strcmp(argv[x], "-wmbb0") || !strcmp(argv[x], "-w580")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MB_BOMB].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mb-bomb-power") || !strcmp(argv[x], "-wmbb1") || !strcmp(argv[x], "-w581")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MB_BOMB].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mb-bomb-delay") || !strcmp(argv[x], "-wmbb2") || !strcmp(argv[x], "-w582")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MB_BOMB].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--concrete-donkey-ammo") || !strcmp(argv[x], "-wcd0") || !strcmp(argv[x], "-w590")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_CONCRETE_DONKEY].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--concrete-donkey-power") || !strcmp(argv[x], "-wcd1") || !strcmp(argv[x], "-w591")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_CONCRETE_DONKEY].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--concrete-donkey-delay") || !strcmp(argv[x], "-wcd2") || !strcmp(argv[x], "-w592")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_CONCRETE_DONKEY].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--suicide-bomber-ammo") || !strcmp(argv[x], "-wsb0") || !strcmp(argv[x], "-w600")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUICIDE_BOMBER].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--suicide-bomber-power") || !strcmp(argv[x], "-wsb1") || !strcmp(argv[x], "-w601")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUICIDE_BOMBER].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--suicide-bomber-delay") || !strcmp(argv[x], "-wsb2") || !strcmp(argv[x], "-w602")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SUICIDE_BOMBER].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--sheep-strike-ammo") || !strcmp(argv[x], "-wsst0") || !strcmp(argv[x], "-w610")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP_STRIKE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--sheep-strike-power") || !strcmp(argv[x], "-wsst1") || !strcmp(argv[x], "-w611")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP_STRIKE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--sheep-strike-delay") || !strcmp(argv[x], "-wsst2") || !strcmp(argv[x], "-w612")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_SHEEP_STRIKE].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--mail-strike-ammo") || !strcmp(argv[x], "-wmast0") || !strcmp(argv[x], "-w620")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MAIL_STRIKE].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--mail-strike-power") || !strcmp(argv[x], "-wmast1") || !strcmp(argv[x], "-w621")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MAIL_STRIKE].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--mail-strike-delay") || !strcmp(argv[x], "-wmast2") || !strcmp(argv[x], "-w622")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_MAIL_STRIKE].delay = atoi(argv[x+1]); }

        else if(!strcmp(argv[x], "--armageddon-ammo") || !strcmp(argv[x], "-war0") || !strcmp(argv[x], "-w630")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_ARMAGEDDON].ammo = atoi(argv[x+1]); }
        else if(!strcmp(argv[x], "--armageddon-power") || !strcmp(argv[x], "-war1") || !strcmp(argv[x], "-w631")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_ARMAGEDDON].power = atoi(argv[x+1])-1; }
        else if(!strcmp(argv[x], "--armageddon-delay") || !strcmp(argv[x], "-war2") || !strcmp(argv[x], "-w632")) {
            if(x<argc-1) scheme.weapon_settings[WEAPON_ARMAGEDDON].delay = atoi(argv[x+1]); }

        /* ========================================================================================================= */
        /* RubberWorm features */
        /* ========================================================================================================= */

        else if(!strcmp(argv[x], "-rrubber") && x<argc-1)
            scheme.weapon_settings[_RW_RUBBER].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rversion") && x<argc-1)
            scheme.weapon_settings[_RW_VERSION].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rantisink") && x<argc-1)
            scheme.weapon_settings[_RW_ANTISINK].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rvisc") && x<argc-1)
            scheme.weapon_settings[_RW_VISC].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rwind") && x<argc-1)
            scheme.weapon_settings[_RW_WIND].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rfriction") && x<argc-1)
            scheme.weapon_settings[_RW_FRICTION].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rglue"))
            scheme.weapon_settings[_RW_FRICTION].crate_probability = _R__GLUE;
        else if(!strcmp(argv[x], "-rice"))
            scheme.weapon_settings[_RW_FRICTION].crate_probability = _R__ICE;
        else if(!strcmp(argv[x], "-rgravity") && x<argc-1)
            scheme.weapon_settings[_RW_GRAVITY].crate_probability = atoi(argv[x+1]);
        //else if(!strcmp(argv[x], "-rdefg"))
        //    scheme.weapon_settings[_RW_FRICTION].crate_probability = _RC_DEFG;
        else if(!strcmp(argv[x], "-rcraterate") && x<argc-1)
            scheme.weapon_settings[_RW_CRATERATE].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rcratelimit") && x<argc-1)
            scheme.weapon_settings[_RW_CRATELIMIT].crate_probability = atoi(argv[x+1]);

        else if(!strcmp(argv[x], "-rflames") && x<argc-1)
            scheme.weapon_settings[_RW_FLAMES].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rspeed") && x<argc-1)
            scheme.weapon_settings[_RW_SPEED].crate_probability = atoi(argv[x+1]);
	else if(!strcmp(argv[x], "-rknock") && x<argc-1)
            scheme.weapon_settings[_RW_KNOCK].crate_probability = atoi(argv[x+1]);
        else if(!strcmp(argv[x], "-rts8") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_SPEED].crate_probability = _R__TS8;
            else scheme.weapon_settings[_RW_SPEED].crate_probability = 0;
        }

        else if(!strcmp(argv[x], "-rsdet") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_SDET].crate_probability
                = bitmod(scheme.weapon_settings[_RW_SDET].crate_probability, _RB_SDET, 1);
            else scheme.weapon_settings[_RW_SDET].crate_probability
                = bitmod(scheme.weapon_settings[_RW_SDET].crate_probability, _RB_SDET, 0);
        }
        else if(!strcmp(argv[x], "-rldet") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_LDET].crate_probability
                = bitmod(scheme.weapon_settings[_RW_LDET].crate_probability, _RB_LDET, 1);
            else scheme.weapon_settings[_RW_LDET].crate_probability
                = bitmod(scheme.weapon_settings[_RW_LDET].crate_probability, _RB_LDET, 0);
        }
        else if(!strcmp(argv[x], "-rfdpt") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_FDPT].crate_probability
                = bitmod(scheme.weapon_settings[_RW_FDPT].crate_probability, _RB_FDPT, 1);
            else scheme.weapon_settings[_RW_FDPT].crate_probability
                = bitmod(scheme.weapon_settings[_RW_FDPT].crate_probability, _RB_FDPT, 0);
        }
        else if(!strcmp(argv[x], "-rir") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_IR].crate_probability
                = bitmod(scheme.weapon_settings[_RW_IR].crate_probability, _RB_IR, 1);
            else scheme.weapon_settings[_RW_IR].crate_probability
                = bitmod(scheme.weapon_settings[_RW_IR].crate_probability, _RB_IR, 0);
        }
        else if(!strcmp(argv[x], "-rcrateshower") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_CRATESHOWER].crate_probability
                = bitmod(scheme.weapon_settings[_RW_CRATESHOWER].crate_probability, _RB_CRATESHOWER, 1);
            else scheme.weapon_settings[_RW_CRATESHOWER].crate_probability
                = bitmod(scheme.weapon_settings[_RW_CRATESHOWER].crate_probability, _RB_CRATESHOWER, 0);
        }
        else if(!strcmp(argv[x], "-rwdca") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_WDCA].crate_probability
                = bitmod(scheme.weapon_settings[_RW_WDCA].crate_probability, _RB_WDCA, 1);
            else scheme.weapon_settings[_RW_WDCA].crate_probability
                = bitmod(scheme.weapon_settings[_RW_WDCA].crate_probability, _RB_WDCA, 0);
        }
        else if(!strcmp(argv[x], "-rope") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_OPE].crate_probability
                = bitmod(scheme.weapon_settings[_RW_OPE].crate_probability, _RB_OPE, 1);
            else scheme.weapon_settings[_RW_OPE].crate_probability
                = bitmod(scheme.weapon_settings[_RW_OPE].crate_probability, _RB_OPE, 0);
        }
        else if(!strcmp(argv[x], "-rfuseex") && x<argc-1)
        {
            if(atoi(argv[x+1])) scheme.weapon_settings[_RW_FUSEEX].crate_probability
                = bitmod(scheme.weapon_settings[_RW_FUSEEX].crate_probability, _RB_FUSEEX, 1);
            else scheme.weapon_settings[_RW_FUSEEX].crate_probability
                = bitmod(scheme.weapon_settings[_RW_FUSEEX].crate_probability, _RB_FUSEEX, 0);
        }

        else if(argv[x][0] == '-') printf("%cIgnoring unknown or incompleted argument: %s\n", 9, argv[x]);
    }

    if(is_ifname)
    {
        if(is_ofname)
        {
            if(schm_save(ofname, scheme))
            {
                printf("Unable to write the file: %s\n", ofname);
                return 5;
            }
        }
        else
        {
            if(schm_save(ifname, scheme))
            {
                printf("Unable to write the file: %s\n", ifname);
                return 6;
            }
        }
    }
    else
    {
        if(is_ofname)
        {
            if(schm_save(ofname, scheme))
            {
                printf("Unable to write the file: %s\n", ofname);
                return 7;
            }
        }
        else
        {
            if(schm_save(DEF_FNAME, scheme))
            {
                printf("Unable to write the file: %s\n", DEF_FNAME);
                return 8;
            }
        }
    }

    if(is_print)
        schmprint(scheme);
    return 0;
}
