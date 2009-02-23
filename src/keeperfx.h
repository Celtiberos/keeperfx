/******************************************************************************/
// keeperfx.h - Dungeon Keeper fan extension.
/******************************************************************************/
// Author:   Tomasz Lis
// Created:  27 May 2008

// Purpose:
//   Header file. Defines exported routines from keeperfx.dll

// Comment:
//   None.

//Copying and copyrights:
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
/******************************************************************************/

#ifndef DK_KEEPERFX_H
#define DK_KEEPERFX_H

#include <windows.h>

#include "globals.h"
#include "bflib_video.h"
#include "packets.h"
#include "thing_list.h"

#define LEGAL_WIDTH  640
#define LEGAL_HEIGHT 480
#define PALETTE_SIZE 768

#define DUNGEONS_COUNT    5
#define PLAYERS_COUNT     5
#define NET_PLAYERS_COUNT 4
#define PACKETS_COUNT     5
#define THINGS_COUNT      2048
#define COLUMNS_COUNT     2048
#define EVENTS_COUNT      100
#define ROOMS_COUNT       150
#define CREATURES_COUNT   256
#define SAVE_SLOTS_COUNT  8
#define MESSAGE_QUEUE_COUNT 4
#define GUI_MESSAGES_COUNT 3
#define CREATURE_PARTYS_COUNT 16
#define WIN_CONDITIONS_COUNT 4
#define CREATURE_MAX_LEVEL 10
#define THING_CLASSES_COUNT  10
// Static textures
#define TEXTURE_BLOCKS_STAT_COUNT   544
// Animated textures
#define TEXTURE_BLOCKS_ANIM_COUNT   48
#define TEXTURE_BLOCKS_COUNT TEXTURE_BLOCKS_STAT_COUNT+TEXTURE_BLOCKS_ANIM_COUNT
// Types of objects
#define CREATURE_TYPES_COUNT  32
#define SPELL_TYPES_COUNT     20
#define TRAP_TYPES_COUNT      11
#define DOOR_TYPES_COUNT      8
#define ROOM_TYPES_COUNT      17
#define OBJECT_TYPES_COUNT   136
#define ACTN_POINTS_COUNT 32
// Camera constants; max zoom is when everything is large
#define CAMERA_ZOOM_MIN 4100
#define CAMERA_ZOOM_MAX 12000

#define SIZEOF_TDDrawSdk 408

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)

// Temporary
typedef struct SSurface {
       char a;
       } TSurface;

enum TbErrorCode {
        Lb_OK      =  0,
        Lb_FAIL    = -1,
};

typedef int TbError;


//This seems to be array of functions in __thiscall convention
// they are all methods for class TDDrawBase and its derivants
// Note: May be incorrectly named - the Beta version was used to get them!
// The inplementation as class is made in "bflib_drawcls.h"
typedef struct {
    void __fastcall (*dt)(void *ths); // +0 virtual ~TDDrawSdk(void);
    long __fastcall (*setup_window)(void *ths); // +4 virtual int setup_window(void);
    long CALLBACK (*WindowProc)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // +8 virtual unsigned int WindowProc(void *,unsigned int,unsigned int,long);
    void __fastcall (*find_video_modes)(void *ths); // +12 virtual void find_video_modes(void);
    int (*get_palette)(void *,unsigned long,unsigned long); // +16 virtual int get_palette(void *,unsigned long,unsigned long);
    int (*set_palette)(void *,unsigned long,unsigned long); // +20 virtual int set_palette(void *,unsigned long,unsigned long);
    int (*setup_screen)(TbScreenMode); // +24 virtual int setup_screen(TbScreenMode);
    long __fastcall (*lock_screen)(void *ths); // +28 virtual long lock_screen(void);
    long __fastcall (*unlock_screen)(void *ths); // +32 virtual long unlock_screen(void);
    long (*clear_screen)(unsigned long); // +36 virtual long clear_screen(unsigned long);
    long (*clear_window)(long,long,unsigned long,unsigned long,unsigned long); // +40 virtual long clear_window(long,long,unsigned long,unsigned long,unsigned long);
    int __fastcall (*swap_screen)(void *ths); //+44 virtual int swap_screen(void);
    int __fastcall (*reset_screen)(void *ths); // +48 virtual int reset_screen(void);
    long __fastcall (*restore_surfaces)(void *ths); // +52 virtual long restore_surfaces(void);
    void __fastcall (*wait_vbi)(void *ths); // +56 virtual void wait_vbi(void);
    long (*swap_box)(tagPOINT,tagRECT &); // +60 virtual long swap_box(tagPOINT,tagRECT &);
    long (*create_surface)(TSurface *,unsigned long,unsigned long); // +64 virtual long create_surface(_TSurface *,unsigned long,unsigned long);
    long (*release_surface)(TSurface *); // +68 virtual long release_surface(_TSurface *);
    long (*blt_surface)(TSurface *,unsigned long,unsigned long,tagRECT *,unsigned long); // +72 virtual long blt_surface(_TSurface *,unsigned long,unsigned long,tagRECT *,unsigned long);
    long (*lock_surface)(TSurface *); // +76 virtual long lock_surface(_TSurface *);
    long (*unlock_surface)(TSurface *); // +80 virtual long unlock_surface(_TSurface *);
    void (*LoresEmulation)(int); // +84 virtual void LoresEmulation(int);
    void *unkn[4];
       } TDDrawBaseVTable;

typedef struct DDrawBaseClass {
       TDDrawBaseVTable *vtable;
       unsigned int unkvar4;
       char *textn2;
       char *textname;
       unsigned int flags;
       unsigned int numfield_14;
       unsigned int numfield_18;
       unsigned int numfield_1C;
       } TDDrawBaseClass;

typedef struct DDrawSdk {
       TDDrawBaseVTable *vtable;
       // From base class
       unsigned int unkvar4;
       char *textn2;
       char *textname;
       unsigned int flags;
       unsigned int numfield_14;
       unsigned int numfield_18;
       unsigned int numfield_1C;
       // The rest
       char unkn[376];
       } TDDrawSdk;

// Windows-standard structure
/*struct _GUID {
     unsigned long Data1;
     unsigned short Data2;
     unsigned short Data3;
     unsigned char Data4[8];
};*/

struct NetMessage {
unsigned char field_0;
char field_1[64];
};

struct GuiMessage { // sizeof = 0x45 (69)
    char text[64];
unsigned char field_40;
unsigned long field_41;
};

struct MessageQueueEntry { // sizeof = 9
     unsigned char field_0;
     unsigned long field_1;
     unsigned long field_5;
};

struct CreatureParty { // sizeof = 208
  char prtname[100];
  unsigned char field_64;
  unsigned char field_65;
  unsigned char field_66;
  unsigned char field_67;
  unsigned long field_68;
  unsigned char field_6C;
  unsigned short field_6D;
  unsigned short field_6F;
  unsigned char field_71[91];
  unsigned long field_CC;
};

//I'm not sure about size of this structure
struct Camera {
    struct Coord3d mappos;
    unsigned char field_6;
    int orient_a;
    int orient_b;
    int orient_c;
    int field_13;
    int field_17;
    int field_1B;
    unsigned char field_1F[9];
    short field_28;
    short field_2A;
    short field_2C;
    short field_2E;
    short field_30;
    short field_32;
    unsigned char field_34;
    int field_35;
    int field_39;
    int field_3D;
    int field_41;
    unsigned char field_45[19];
    short field_58;
    short field_5A;
    short field_5C;
    unsigned char field_5E;
    unsigned char field_5F[12];
    int field_6B;
    unsigned char field_6F[19];
    short field_82;
    short field_84;
    short field_86;
    unsigned char field_88;
    unsigned char field_89[12];
    int field_95;
    int field_99;
};

struct TurnTimer { // sizeof = 5
  unsigned long count;
  unsigned char state;
};

struct InitLight { // sizeof=0x14
short field_0;
unsigned char field_2;
unsigned char field_3;
unsigned char field_4[13];
unsigned char field_11;
unsigned char field_12[2];
};

struct Column { // sizeof=0x18
    short use;
    unsigned char bitfileds;
    unsigned short solidmask;
    unsigned short baseblock;
    unsigned char orient;
    unsigned short cubes[8];
};

struct SpecialDesc {
long field_0;
long field_4;
long field_8;
};

struct UnkStruc5 { // sizeof=0x12
int field_0;
char field_4[4];
short field_8[5];
};

struct ObjectConfig { // sizeof=0x1D
int field_0;
char field_4;
char field_5;
char field_6;
char field_7;
char field_8;
short field_9;
char field_B;
char field_C[14];
char field_1A[3];
};

struct SpellConfig { // sizeof=0x8
int field_0;
int field_4;
};

struct ManfctrConfig { // sizeof=0x14
int field_0;
int field_4;
int field_8;
int field_C;
int field_10;
};

struct Room {
    long field_0;
    short field_4;
    short field_6;
    unsigned char field_8;
    unsigned char field_9;
    short field_A;
    unsigned char field_C[6];
    unsigned char field_12;
    unsigned char field_13[4];
    short field_17;
    unsigned char field_19[30];
    short field_37;
    unsigned char field_39[12];
};

struct Objects {
    unsigned char field_0;
    unsigned char field_1;
    unsigned char field_2;
    unsigned char field_3;
    unsigned char field_4;
    short field_5;
    short field_7;
    short field_9;
    short field_B;
    short field_D;
    unsigned char field_F;
    unsigned char field_10;
    unsigned char field_11;
    unsigned char field_12;
    unsigned char field_13;
    unsigned char field_14;
    unsigned char field_15;
};

struct TrapData {
      long field_0;
      long field_4;
      short field_8;
      short field_A;
      short field_C;
      short field_E;
};

struct RoomData {
      unsigned char numfield_0;
      short numfield_1;
      long ofsfield_3;
      long ofsfield_7;
      long offfield_B;
      unsigned char field_F;
      unsigned char field_10;
      short field_11;
      short field_13;
      short field_15;
};

struct SpellData {
      long field_0;
      long field_4;
      unsigned char field_8;
      short field_9;
      short field_B;
      short field_D;
      unsigned char field_F[2];
      short field_11;
      short field_13;
      long field_15;
      unsigned char field_19;
      unsigned char field_1A;
};

struct CreatureData {
      unsigned char field_0;
      short field_1;
      short field_3;
};

struct SlabMap {
      unsigned char field_0;
      short field_1;
      unsigned char field_3;
      unsigned char field_4;
      unsigned char field_5;
};

struct SlabAttr {
      short field_0;
      short field_2;
      short field_4;
      long field_6;
      long field_A;
      unsigned char field_E;
      unsigned char field_F;
      unsigned char field_10;
      unsigned char field_11;
      unsigned char field_12;
      unsigned char field_13;
      unsigned char field_14;
      unsigned char field_15;
};

struct Event { // sizeof=0x15
unsigned char field_0;
unsigned char field_1;
unsigned long field_2;
unsigned long field_6;
unsigned char field_A;
unsigned char field_B;
unsigned long field_C;
unsigned long field_10;
unsigned char field_14;
};

struct ActnPoint {
    unsigned char flags;
char field_1[8];
char field_9;
};

struct Creatures { // sizeof = 16
  unsigned short numfield_0;
  unsigned short numfield_2;
  unsigned char field_4[2];
  unsigned char field_6;
  unsigned char field_7;
  unsigned char field_8;
  unsigned char field_9[3];
  unsigned char field_C[4];
};

struct CreatureControl {
    unsigned short field_0;
    unsigned char field_2;
char field_3[28];
    unsigned short thing_idx;
unsigned char field_21[77];
    short field_6E;
unsigned char field_70[10];
    unsigned short field_7A;
unsigned char field_7C[15];
    unsigned char field_8B;
unsigned char field_8C[31];
    unsigned char field_AB;
unsigned char field_AC;
    unsigned char field_AD;
unsigned char field_AE[3];
    unsigned char field_B1;
unsigned char field_B2[7];
unsigned short field_B9;
    CoordDelta3d pos_BB;
    unsigned char bloody_footsteps_turns;
unsigned char field_C2[6];
    short field_C8;
    short field_CA;
unsigned char field_CC[2];
    unsigned long field_CE;
unsigned char field_D2[204];
    char instances[256];
unsigned char field_29E[18];
    unsigned char field_2B0;
unsigned char field_2B1[62];
    unsigned long field_2EF;
unsigned char field_2F3[11];
    unsigned long field_2FE;
    unsigned char field_302;
unsigned char field_303[3];
unsigned char field_306[2];
};

struct CreatureStats {
long field_0;
short field_4;
char field_6;
short field_7;
char field_9;
char field_A;
char field_B;
char field_C;
char field_D;
char field_E;
char field_F;
char field_10;
char field_11;
short field_12;
char field_14;
short field_15;
char field_17;
char field_18;
char field_19;
char field_1A;
short field_1B;
short field_1D;
short field_1F;
short field_21;
short field_23;
char field_25;
long field_26[10];
char field_4E;
short field_4F;
char field_51;
char field_52;
short field_53;
short field_55[18];
short field_79;
char field_7B;
char field_7C;
char field_7D;
short field_7E;
char field_80[10];
char field_8A[10];
char field_94;
char field_95;
char field_96;
char field_97;
short field_98;
char field_9A;
char field_9B;
char field_9C[6];
char field_A2;
char field_A3[3];
short field_A6;
short field_A8;
short field_AA;
short field_AC;
short field_AE;
short field_B0;
short field_B2;
short field_B4;
short field_B6;
short field_B8;
short field_BA;
short field_BC;
short field_BE[4];
short field_C6;
short field_C8;
char field_CA[2];
short field_CC;
char field_CE[2];
short field_D0;
char field_D2[5];
char field_D7;
char field_D8;
char field_D9;
char field_DA;
char field_DB;
char field_DC[4];
short field_E0;
short field_E2;
short field_E4;
};

struct MagicStats {  // sizeof=0x4C
long field_0;
long field_4[8];
long field_24;
long field_28[8];
long field_48;
};

struct TrapStats {  // sizeof=54
unsigned long field_0;
unsigned long field_4;
unsigned long field_8;
unsigned char field_C[6];
  unsigned char field_12;
unsigned char field_13[7];
unsigned char field_1A[6];
unsigned char field_20[8];
unsigned char field_28[8];
unsigned char field_30[6];
};

struct BBlock {
      char field_0;
      short field_1;
      short field_3;
};

struct GameSettings {
    unsigned char field_0;
    unsigned char video_shadows;
    unsigned char view_distance;
    unsigned char field_3;
    unsigned char video_textures;
    unsigned char video_cluedo_mode;
    unsigned char sound_volume;
    unsigned char redbook_volume;
    unsigned char field_8;
    unsigned short gamma_correction;
    int field_B;
    unsigned char field_F[8];
    unsigned char field_17[8];
    unsigned char field_1F[8];
    unsigned char field_27[8];
    unsigned char field_2F[8];
    unsigned char field_37[8];
    unsigned char field_3F[8];
    unsigned char field_47[8];
    unsigned char tooltips_on;
    unsigned char field_50;
    unsigned char field_51;
    };

struct PacketSaveHead { // sizeof=0xF
unsigned int field_0;
unsigned int field_4;
unsigned int field_8;
    unsigned char field_C;
unsigned char field_D;
unsigned char field_E;
    };


struct Wander {
unsigned char field_0[424];
    };

struct CatalogueEntry {
    char used;
    char  numfield_1;
    char textname[15];
};

#define SIZEOF_PlayerInfo 0x4EF
struct PlayerInfo {
    unsigned char field_0;
    unsigned char field_1;
    unsigned char field_2; //seems to be never used
    unsigned char field_3;
    unsigned char field_4;
    unsigned char field_5;
    unsigned char field_6;
    unsigned int field_7;
    unsigned char field_B;
unsigned char field_C[4];
unsigned int field_10;
unsigned char field_14;
    char field_15[20]; //size may be shorter
    unsigned char field_29;
    unsigned char field_2A;
    unsigned char field_2B;
    unsigned char field_2C;
    unsigned char field_2D[2];
    short field_2F;
    long field_31;
    short field_35;
    unsigned char field_37;
    struct Camera *camera;
    struct Coord3d cam_mappos;
//    struct Camera camera2;
    unsigned char field_42;
    long field_43;
    unsigned char field_47[31];
    unsigned char field_66[42];
    unsigned short field_90;
    unsigned short field_92;
    unsigned char field_94[3];
    long field_97;
    unsigned char field_9B[31];
    unsigned short field_BA;
    unsigned short field_BC;
    unsigned char field_BE[3];
    long field_C1;
    unsigned char field_C5[16];
    unsigned char field_D5[4];
// end of potential Camera struct
    unsigned char field_D9[11];
    unsigned short field_E4;
    unsigned short field_E6;
char field_E8[2];
    struct Wander wandr1;
    struct Wander wandr2;
    short field_43A;
char field_43C[2];
    short field_43E;
    long field_440;
    short field_444;
    short field_446;
    short field_448;
    short field_44A;
    short mouse_x;
    short mouse_y;
    unsigned short minimap_zoom;
    unsigned char field_452;
    unsigned char field_453;
    unsigned char field_454;
char field_455;
    unsigned char field_456;
char field_457[8];
char field_45F;
short field_460;
char field_462;
    char strfield_463[64];
    char field_4A3[2];
    char field_4A5;
    char field_4A6;
    char field_4A7[9];
    unsigned char field_4B0;
    unsigned long field_4B1;
    char field_4B5;
    char field_4B6[7];
    long field_4BD;
    long field_4C1;
    long field_4C5;
    unsigned char *field_4C9;
    long field_4CD;
    char field_4D1;
    long field_4D2;
    char field_4D6[4];
    char field_4DA;
    char field_4DB[8];
    long field_4E3;
    long field_4E7;
    long field_4EB;
    };

#define SIZEOF_Dungeon 0x1508
struct Dungeon {
    short field_0;
    struct Coord3d mappos;
    unsigned char field_8;
    unsigned char field_9;
    unsigned char computer_enabled;
    int field_B;
    short field_F;
    short field_11;
    short field_13;
    int field_15;
    short field_19;
    short field_1B;
    short field_1D;
    short field_1F;
    short field_21;
    short field_23;
    short field_25;
    short field_27;
    int field_29;
    short field_2D;
    short field_2F;
    short field_31;
    unsigned int field_33;  // originally short, but with 2b padding
    int field_37;
    int field_3B;
    int field_3F;
    short field_43;
    int field_45;
    int field_49;
    int field_4D;
    short field_51;
    short field_53;
    int field_55;
    int field_59;
    int field_5D;
    short field_61;
    unsigned char field_63;
    short field_64[480];
    unsigned short field_424[CREATURE_TYPES_COUNT][3];
    unsigned short field_4E4[CREATURE_TYPES_COUNT][3];
    short field_5A4[15];
    int field_5C2[4];
    short field_5D2;
    int field_5D4;
    short field_5D8;
    unsigned char field_5DA[679];
    unsigned char field_881;
    unsigned char field_882;
    unsigned char field_883;
    int field_884;
    int field_888;
    int field_88C[10];
    int field_8B4[8];
    unsigned char field_8D4;
    unsigned char field_8D5;
    unsigned char field_8D6[23];
    unsigned char field_8ED[43];
    unsigned char field_918;
    unsigned char field_919;
    unsigned char field_91A[32];
    unsigned char field_93A;
    short field_93B;
    short field_93D;
    short field_93F;
    int field_941;
    int field_945;
    short field_949;
    short field_94B[32];
    short field_98B;
    short field_98D[97];
    int field_A4F[32];
    short field_ACF;
    short field_AD1;
    short field_AD3;
    short field_AD5;
    short field_AD7;
    short field_AD9;
    short field_ADB;
    int field_ADD;
    int field_AE1;
    int field_AE5[4];
    short field_AF5;
    short field_AF7;
    int field_AF9;
    int field_AFD;
    short field_B01[DUNGEONS_COUNT];
    int field_B0B[225];
    int field_E8F[4];
    unsigned char field_E9F;
    int field_EA0;
    int field_EA4;
    int field_EA8[52];
    int field_F78;
    unsigned char field_F7C;
    unsigned char field_F7D;
    unsigned char field_F7E;
    unsigned char field_F7F;
    unsigned char field_F80;
    unsigned char field_F81;
    unsigned char field_F82[112];
unsigned char field_FF2;
unsigned char field_FF3[19];
unsigned char field_1006;
unsigned char field_1007[37];
    struct TurnTimer turn_timers[8];
unsigned long field_1054;
unsigned long field_1058;
    long field_105C;
    unsigned char field_1060[34];
    unsigned char field_1082[241];
    unsigned char field_1173;
    unsigned char field_1174;
    unsigned char field_1175;
    unsigned char field_1176;
    short field_1177;
    long field_1179;
    long field_117D;
long field_1181;
long field_1185;
    unsigned char field_1189;
unsigned char field_118A;
long field_118B;
long field_118F;
long field_1193;
long field_1197;
long field_119B;
unsigned char field_119F[99];
unsigned char field_1202[41];
    unsigned long field_122B;
    unsigned long field_122F;
    unsigned long field_1233;
    long time1;
    long time2;
    int field_123F;
    int field_1243;
    int field_1247;
    int field_124B;
    int field_124F;
    int field_1253;
    int field_1257;
    int field_125B;
    int field_125F;
    unsigned char field_1263[31];
    unsigned char field_1282[128];
    unsigned char field_1302[5];
    int allow_save_score;
    unsigned long player_score;
unsigned char field_130F[19];
unsigned char field_1322[36];
unsigned char field_1346[60];
unsigned char field_1382[29];
int field_139F;
int field_13A3;
unsigned char field_13A7[121];
unsigned short field_1420[32];
unsigned char field_1460[41];
unsigned char field_1489[32];
int field_14A9;
unsigned char field_14AD;
int field_14AE;
unsigned char field_14B2[2];
int field_14B4;
int field_14B8;
unsigned char field_14BC[6];
unsigned short field_14C2[32];
    short field_1502;
    int field_1504;
    };

#define SIZEOF_Game 1382437

// only one such struct exists at .data:005F0310
// it ends at 00741B35
struct Game { // (sizeof=0x151825)
char numfield_0;
int version_major;
int version_minor;
unsigned char continue_level;
unsigned char numfield_A;
char align_B;
    unsigned char numfield_C;
char numfield_D;
    unsigned char flags_font;
char one_player;
    char eastegg01_cntr;
char flags_cd;
    char eastegg02_cntr;
char audiotrack;
char numfield_14;
char numfield_15;
int numfield_16;
char numfield_1A;
char numfield_1B;
    struct PlayerInfo players[PLAYERS_COUNT];
struct Column columns[COLUMNS_COUNT];
struct UnkStruc5 struc_D8C7[512];
struct ObjectConfig objects_config[239];
char field_117DA[14];
struct ManfctrConfig traps_config[7];
struct ManfctrConfig doors_config[5];
struct SpellConfig spells_config[15];
    struct Thing *things_lookup[THINGS_COUNT];
long fieldCC157_ptr;
    struct CreatureControl *creature_control_lookup[CREATURES_COUNT];
struct Thing *things_ptr2;
void *field18c7_lookup[2048];
long field_15D58;
char field_15D5C[41674];
char field_20026[65536];
char field_30026[90403];
long field_46149;
char field_4614D;
char field_4614E;
int field_4614F;
int field_46153;
int field_46157[128];
short field_46357;
short field_46359[33502];
char field_56915[38673];
char field_60026[24881];
    struct CreatureControl creature_control_data[CREATURES_COUNT];
    struct Thing things_data[THINGS_COUNT];
char field_CC157 [64251];
struct BBlock bblocks[257];
struct BBlock map[65536];
char computer_task[14800];
char computer[18239];
char field_134266[4096];
char field_135266[4096];
char field_136266[128];
char field_1362E6[51];
    struct SlabMap slabmap[85*85];
    struct Room rooms[ROOMS_COUNT];
    struct Dungeon dungeon[DUNGEONS_COUNT];
char field_149E05;
    struct StructureList thing_lists[11];
unsigned int field_149E5E;
unsigned int field_149E62;
unsigned int field_149E66;
unsigned int field_149E6A;
unsigned int field_149E6E;
char field_149E72[5];
unsigned int field_149E77;
unsigned char field_149E7B;
unsigned int field_149E7C;
unsigned char field_149E80;
unsigned char field_149E81;
    char packet_fname[150];
    char packet_fopened;
    TbFileHandle packet_save_fp;
unsigned int field_149F1D;
    struct PacketSaveHead packet_save_head;
unsigned int field_149F30;
unsigned int turns_fastforward;
unsigned char numfield_149F38;
    unsigned char packet_checksum;
unsigned int numfield_149F3A;
unsigned int numfield_149F3E;
    int numfield_149F42;
unsigned char numfield_149F46;
unsigned char numfield_149F47;
    struct CatalogueEntry save_catalogue[SAVE_SLOTS_COUNT];
    struct Event event[EVENTS_COUNT];
unsigned long field_14A804;
unsigned long field_14A808;
unsigned long field_14A80C;
unsigned long field_14A810;
unsigned long field_14A814;
char field_14A818[14];
char field_14A826[16];
char field_14A836[7];
    unsigned char numfield_14A83D;
    unsigned char level_number; // change it to long ASAP
short texture_animation[8*TEXTURE_BLOCKS_ANIM_COUNT];
short field_14AB3F;
    unsigned char texture_id;
short freethings[287];
char field_14AD80[1254];
char field_14B266[2048];
char field_14BA66[128];
char field_14BAE6[64];
char field_14BB26[28];
    unsigned long seedchk_random_used;
    unsigned long gameturn;
    unsigned long field_14BB4A;
    unsigned long field_14BB4E;
short field_14BB52;
unsigned char field_14BB54;
int field_14BB55;
int field_14BB59;
int field_14BB5D;
    unsigned long time_delta;
short field_14BB65[592];
char field_14C005[5];
short field_14C00A;
    struct Packet packets[PACKETS_COUNT];
    struct CreatureStats creature_stats[CREATURE_TYPES_COUNT];
short field_14DD21[34];
struct MagicStats magic_stats[SPELL_TYPES_COUNT];
struct ActnPoint action_points[ACTN_POINTS_COUNT];
char field_14E495;
    unsigned char field_14E496;
char field_14E497;
int field_14E498;
short field_14E49C;
short field_14E49E;
int field_14E4A0;
short field_14E4A4;
int gold_lookup;
unsigned char field_14E4AA[2];
unsigned short field_14E4AC;
unsigned short field_14E4AE;
unsigned short field_14E4B0;
unsigned short field_14E4B2;
unsigned short field_14E4B4;
unsigned long field_14E4B6;
unsigned char field_14E4BA[1100];
unsigned short field_14E906;
unsigned short field_14E908;
unsigned short field_14E90A;
unsigned char field_14E90C[10];
unsigned long field_14E916;
unsigned short field_14E91A;
unsigned short field_14E91C;
unsigned short field_14E91E;
unsigned short field_14E920;
unsigned short field_14E922;
unsigned short field_14E924;
char field_14E926[14];
long field_14E934;
unsigned short field_14E938;
unsigned short field_14E93A;
unsigned short field_14E93C;
unsigned short field_14E93E;
unsigned short field_14E940;
unsigned short field_14E942;
unsigned short field_14E944;
unsigned short field_14E946;
unsigned short field_14E948;
unsigned short field_14E94A;
unsigned short field_14E94C;
unsigned short field_14E94E;
unsigned short field_14E950;
unsigned short field_14E952;
unsigned short field_14E954;
unsigned short field_14E956[8];
char field_14E966[128];
char field_14E9E6[64];
char field_14EA26[32];
short field_14EA46;
short field_14EA48;
char flagfield_14EA4A;
char field_14EA4B;
char field_14EA4C[320];
unsigned long field_14EB8C;
unsigned long field_14EB90;
unsigned long field_14EB94;
unsigned short field_14EB98;
unsigned short field_14EB9A;
unsigned short field_14EB9C;
unsigned short field_14EB9E;
unsigned char field_14EBA0;
unsigned short field_14EBA1;
unsigned short field_14EBA3;
unsigned char field_14EBA5;
unsigned long field_14EBA6;
unsigned char field_14EBAA[700];
char field_14EE66[1024];
unsigned char field_14F266[800];
    CreatureParty creature_partys[16];
    unsigned long creature_partys_num;
    unsigned short win_conditions[WIN_CONDITIONS_COUNT];
    unsigned long win_conditions_num;
    unsigned short lose_conditions[WIN_CONDITIONS_COUNT];
    unsigned long lose_conditions_num;
unsigned char field_1502A2[2];
unsigned char field_1502A4[13];
    unsigned long creature_pool[CREATURE_TYPES_COUNT];
    char creature_pool_empty;
    long timingvar1;
int field_150336;
int field_15033A;
int field_15033E;
    char no_intro;
int numfield_150343;
int numfield_150347;
int field_15034B;
int field_15034F;
char field_150353;
char field_150354;
char field_150355;
int field_150356;
int field_15035A;
char field_15035E;
int field_15035F;
int field_150363;
char field_150367[15];
char field_150376[28];
    int num_fps;
int numfield_150396;
int numfield_15039A;
int numfield_15039E;
char numfield_1503A2;
char numfield_1503A3;
long field_1503A4;
char field_1503A8[9];
unsigned short field_1503B1;
unsigned short field_1503B3;
char field_1503B5[527];
char field_1505C4[273];
long field_1506D5;
char field_1506D9[1024];
    char field_150AD9[1024];
    char text_info[1024];
int field_1512D9;
char field_1512DD;
int field_1512DE;
int field_1512E2;
char field_1512E6[624];
char field_151556[128];
char field_1515D6[256];
char field_1516D6[29];
int field_1516F3;
int field_1516F7;
int field_1516FB;
char field_1516FF;
int field_151700;
int field_151704;
int field_151708;
    struct GuiMessage messages[GUI_MESSAGES_COUNT];
    unsigned char active_messages_count;
    unsigned char bonus_levels[5];
    unsigned char is_full_moon;
int field_1517E2;
    unsigned char field_1517E6;
    unsigned char field_1517E7;
    int armageddon;
int field_1517EC;
    struct Coord3d pos_1517F0;
char field_1517F6;
char field_1517F7;
char field_1517F8;
char field_1517F9;
char field_1517FA;
char field_1517FB;
char field_1517FC;
short field_1517FD;
short field_1517FF;
int field_151801;
int field_151805;
int field_151809;
    int chosen_spell_type;
    int chosen_spell_look;
    int chosen_spell_tooltip;
int numfield_151819;
int numfield_15181D;
int numfield_151821;
};

struct CPU_INFO {
int field_0;
int field_4;
int field_8;
int field_C;
int field_10;
int field_14;
char *field_18;
};

struct TbNetworkPlayerInfo {
char field_0[32];
long field_20;
};

struct TbNetworkCallbackData {
char field_0[20];
};

struct SerialInitData {
long field_0;
    long numfield_4;
    long field_8;
long field_C;
    char *str_phone;
    char *str_dial;
    char *str_hang;
    char *str_answr;
};

struct ClientDataEntry {
long field_0;
long field_4;
long field_8;
long field_C;
char field_10[28];
};

struct ReceiveCallbacks {
       void (*add_msg)(unsigned long, char *, void *);
       void (*delete_msg)(unsigned long, void *);
       void (*host_msg)(unsigned long, void *);
       void *unkn1;
       void * __stdcall (*multi_player)(unsigned long, unsigned long, unsigned long, void *);
       void __stdcall (*mp_req_exdata_msg)(unsigned long, unsigned long, void *);
       void (*req_compos_exchngdat_msg)(unsigned long, unsigned long, void *);
       void * (*unidirectional_msg)(unsigned long, unsigned long, void *);
       void (*sys_user_msg)(unsigned long, void *, unsigned long, void *);
};

struct TbLoadFiles {
        char FName[28];
        unsigned char **Start;
        unsigned char **SEnd;
        unsigned long SLength;
        unsigned short Flags;
        unsigned short Spare;
};

typedef char * (*ModDL_Fname_Func)(struct TbLoadFiles *);
typedef long (*Thing_Class_Func)(struct Thing *);


// Variables inside the main module
extern TbClockMSec last_loop_time;
extern int map_subtiles_x;
extern int map_subtiles_y;
extern int map_tiles_x;
extern int map_tiles_y;
extern struct GuiBox *gui_box;
extern struct GuiBox *gui_cheat_box;
extern const struct CommandDesc command_desc[];

// Global variables migration between DLL and the program

DLLIMPORT extern HINSTANCE _DK_hInstance;
DLLIMPORT extern TDDrawBaseClass *_DK_lpDDC;
#define lpDDC _DK_lpDDC
DLLIMPORT extern struct Game _DK_game;
#define game _DK_game
DLLIMPORT extern char _DK_my_player_number;
#define my_player_number _DK_my_player_number
DLLIMPORT extern float _DK_phase_of_moon;
#define phase_of_moon _DK_phase_of_moon
DLLIMPORT extern unsigned char *_DK_palette;
DLLIMPORT extern unsigned char *_DK_scratch;
#define scratch _DK_scratch
DLLIMPORT extern struct TbLoadFiles _DK_game_load_files[];
#define game_load_files _DK_game_load_files
DLLIMPORT extern struct GameSettings _DK_settings;
#define settings _DK_settings
DLLIMPORT extern unsigned char _DK_exit_keeper;
#define exit_keeper _DK_exit_keeper
DLLIMPORT extern unsigned char _DK_quit_game;
#define quit_game _DK_quit_game
DLLIMPORT extern struct CatalogueEntry _DK_save_game_catalogue[8];
#define save_game_catalogue _DK_save_game_catalogue
DLLIMPORT extern int _DK_number_of_saved_games;
#define number_of_saved_games _DK_number_of_saved_games
DLLIMPORT extern int _DK_lbUseSdk;
DLLIMPORT extern unsigned char _DK_frontend_palette[768];
#define frontend_palette _DK_frontend_palette
DLLIMPORT extern int _DK_continue_game_option_available;
#define continue_game_option_available _DK_continue_game_option_available
DLLIMPORT extern long _DK_last_mouse_x;
#define last_mouse_x _DK_last_mouse_x
DLLIMPORT extern long _DK_last_mouse_y;
#define last_mouse_y _DK_last_mouse_y
DLLIMPORT extern int _DK_credits_end;
#define credits_end _DK_credits_end
DLLIMPORT extern struct TbSprite *_DK_frontstory_font;
#define frontstory_font _DK_frontstory_font
DLLIMPORT extern struct TbSprite *_DK_winfont;
#define winfont _DK_winfont
DLLIMPORT extern long _DK_frontstory_text_no;
#define frontstory_text_no _DK_frontstory_text_no
DLLIMPORT extern int _DK_FatalError;
#define FatalError _DK_FatalError
DLLIMPORT extern int _DK_net_service_index_selected;
#define net_service_index_selected _DK_net_service_index_selected
DLLIMPORT extern unsigned char _DK_fade_palette_in;
#define fade_palette_in _DK_fade_palette_in
DLLIMPORT extern long _DK_old_mouse_over_button;
#define old_mouse_over_button _DK_old_mouse_over_button
DLLIMPORT extern long _DK_frontend_mouse_over_button;
#define frontend_mouse_over_button _DK_frontend_mouse_over_button
DLLIMPORT extern struct TbLoadFiles _DK_frontstory_load_files[4];
#define frontstory_load_files _DK_frontstory_load_files
DLLIMPORT extern struct TbLoadFiles _DK_netmap_flag_load_files[7];
#define netmap_flag_load_files _DK_netmap_flag_load_files
DLLIMPORT extern int _DK_fe_high_score_table_from_main_menu;
#define fe_high_score_table_from_main_menu _DK_fe_high_score_table_from_main_menu
DLLIMPORT extern long _DK_define_key_scroll_offset;
#define define_key_scroll_offset _DK_define_key_scroll_offset
DLLIMPORT extern ModDL_Fname_Func _DK_modify_data_load_filename_function;
#define modify_data_load_filename_function _DK_modify_data_load_filename_function
DLLIMPORT extern struct TbSetupSprite _DK_frontstory_setup_sprites[2];
#define frontstory_setup_sprites _DK_frontstory_setup_sprites
DLLIMPORT extern unsigned long _DK_time_last_played_demo;
#define time_last_played_demo _DK_time_last_played_demo
DLLIMPORT extern char _DK_lbfade_open;
#define lbfade_open _DK_lbfade_open
DLLIMPORT extern unsigned short _DK_battle_creature_over;
#define battle_creature_over _DK_battle_creature_over
DLLIMPORT extern char _DK_gui_room_type_highlighted;
#define gui_room_type_highlighted _DK_gui_room_type_highlighted
DLLIMPORT extern char _DK_gui_door_type_highlighted;
#define gui_door_type_highlighted _DK_gui_door_type_highlighted
DLLIMPORT extern char _DK_gui_trap_type_highlighted;
#define gui_trap_type_highlighted _DK_gui_trap_type_highlighted
DLLIMPORT extern char _DK_gui_creature_type_highlighted;
#define gui_creature_type_highlighted _DK_gui_creature_type_highlighted
DLLIMPORT extern short _DK_drag_menu_x;
#define drag_menu_x _DK_drag_menu_x
DLLIMPORT extern short _DK_drag_menu_y;
#define drag_menu_y _DK_drag_menu_y
DLLIMPORT extern char _DK_busy_doing_gui;
#define busy_doing_gui _DK_busy_doing_gui
DLLIMPORT extern unsigned short _DK_tool_tip_time;
#define tool_tip_time _DK_tool_tip_time
DLLIMPORT extern unsigned short _DK_help_tip_time;
#define help_tip_time _DK_help_tip_time
DLLIMPORT extern long _DK_gui_last_left_button_pressed_id;
#define gui_last_left_button_pressed_id _DK_gui_last_left_button_pressed_id
DLLIMPORT extern long _DK_gui_last_right_button_pressed_id;
#define gui_last_right_button_pressed_id _DK_gui_last_right_button_pressed_id
DLLIMPORT extern long _DK_tooltip_scroll_offset;
#define tooltip_scroll_offset _DK_tooltip_scroll_offset
DLLIMPORT extern long _DK_tooltip_scroll_timer;
#define tooltip_scroll_timer _DK_tooltip_scroll_timer
DLLIMPORT extern long _DK_map_to_slab[256];
#define map_to_slab _DK_map_to_slab
DLLIMPORT extern struct TrapData _DK_trap_data[TRAP_TYPES_COUNT];
#define trap_data _DK_trap_data
DLLIMPORT extern struct RoomData _DK_room_data[ROOM_TYPES_COUNT];
#define room_data _DK_room_data
DLLIMPORT extern struct SpellData _DK_spell_data[SPELL_TYPES_COUNT+1];
#define spell_data _DK_spell_data
DLLIMPORT extern struct SlabAttr _DK_slab_attrs[58];
DLLIMPORT extern unsigned char _DK_object_to_special[OBJECT_TYPES_COUNT];
#define object_to_special _DK_object_to_special
DLLIMPORT extern unsigned char _DK_object_to_magic[OBJECT_TYPES_COUNT];
#define object_to_magic _DK_object_to_magic
DLLIMPORT extern unsigned char _DK_workshop_object_class[OBJECT_TYPES_COUNT];
#define workshop_object_class _DK_workshop_object_class
DLLIMPORT extern unsigned char _DK_object_to_door_or_trap[OBJECT_TYPES_COUNT];
#define object_to_door_or_trap _DK_object_to_door_or_trap
DLLIMPORT extern unsigned char _DK_magic_to_object[24];
#define magic_to_object _DK_magic_to_object
DLLIMPORT extern unsigned char _DK_trap_to_object[8];
#define trap_to_object _DK_trap_to_object
DLLIMPORT extern unsigned char _DK_door_to_object[DOOR_TYPES_COUNT];
#define door_to_object _DK_door_to_object
DLLIMPORT extern unsigned short _DK_specials_text[10];
#define specials_text _DK_specials_text
DLLIMPORT extern unsigned short _DK_door_names[DOOR_TYPES_COUNT];
#define door_names _DK_door_names
DLLIMPORT extern struct CreatureData _DK_creature_data[CREATURE_TYPES_COUNT];
#define creature_data _DK_creature_data
DLLIMPORT extern struct Objects _DK_objects[135];
DLLIMPORT extern int _DK_eastegg03_cntr;
#define eastegg03_cntr _DK_eastegg03_cntr
DLLIMPORT extern long _DK_pointer_x;
#define pointer_x _DK_pointer_x
DLLIMPORT extern long _DK_pointer_y;
#define pointer_y _DK_pointer_y
DLLIMPORT extern long _DK_block_pointed_at_x;
#define block_pointed_at_x _DK_block_pointed_at_x
DLLIMPORT extern long _DK_block_pointed_at_y;
#define block_pointed_at_y _DK_block_pointed_at_y
DLLIMPORT extern long _DK_pointed_at_frac_x;
#define pointed_at_frac_x _DK_pointed_at_frac_x
DLLIMPORT extern long _DK_pointed_at_frac_y;
#define pointed_at_frac_y _DK_pointed_at_frac_y
DLLIMPORT extern long _DK_top_pointed_at_x;
#define top_pointed_at_x _DK_top_pointed_at_x
DLLIMPORT extern long _DK_top_pointed_at_y;
#define top_pointed_at_y _DK_top_pointed_at_y
DLLIMPORT extern long _DK_top_pointed_at_frac_x;
#define top_pointed_at_frac_x _DK_top_pointed_at_frac_x
DLLIMPORT extern long _DK_top_pointed_at_frac_y;
#define top_pointed_at_frac_y _DK_top_pointed_at_frac_y
DLLIMPORT struct ScreenPacket _DK_net_screen_packet;
#define net_screen_packet _DK_net_screen_packet
DLLIMPORT struct _GUID _DK_net_guid;
#define net_guid _DK_net_guid
DLLIMPORT struct TbNetworkPlayerInfo _DK_net_player_info[NET_PLAYERS_COUNT];
#define net_player_info _DK_net_player_info
DLLIMPORT struct TbNetworkCallbackData _DK_enum_players_callback[NET_PLAYERS_COUNT];
#define enum_players_callback _DK_enum_players_callback
DLLIMPORT struct SerialInitData _DK_net_serial_data;
#define net_serial_data _DK_net_serial_data
DLLIMPORT struct SerialInitData _DK_net_modem_data;
#define net_modem_data _DK_net_modem_data
DLLIMPORT char _DK_tmp_net_player_name[24];
#define tmp_net_player_name _DK_tmp_net_player_name
DLLIMPORT char _DK_tmp_net_phone_number[24];
#define tmp_net_phone_number _DK_tmp_net_phone_number
DLLIMPORT char _DK_tmp_net_modem_init[20];
#define tmp_net_modem_init _DK_tmp_net_modem_init
DLLIMPORT char _DK_tmp_net_modem_dial[20];
#define tmp_net_modem_dial _DK_tmp_net_modem_dial
DLLIMPORT char _DK_tmp_net_modem_hangup[20];
#define tmp_net_modem_hangup _DK_tmp_net_modem_hangup
DLLIMPORT char _DK_tmp_net_modem_answer[20];
#define tmp_net_modem_answer _DK_tmp_net_modem_answer
DLLIMPORT int _DK_fe_network_active;
#define fe_network_active _DK_fe_network_active
DLLIMPORT char _DK_video_shadows;
#define video_shadows _DK_video_shadows
DLLIMPORT char _DK_video_view_distance_level;
#define video_view_distance_level _DK_video_view_distance_level
DLLIMPORT char _DK_video_cluedo_mode;
DLLIMPORT char _DK_video_gamma_correction;
#define video_gamma_correction _DK_video_gamma_correction
DLLIMPORT long _DK_sound_level;
#define sound_level _DK_sound_level
DLLIMPORT long _DK_music_level;
#define music_level _DK_music_level
DLLIMPORT long _DK_fe_mouse_sensitivity;
#define fe_mouse_sensitivity _DK_fe_mouse_sensitivity
DLLIMPORT long _DK_activity_list[24];
#define activity_list _DK_activity_list
DLLIMPORT char _DK_net_service[16][64];
#define net_service _DK_net_service
DLLIMPORT void *_DK_exchangeBuffer;
#define exchangeBuffer _DK_exchangeBuffer
DLLIMPORT long _DK_exchangeSize;
#define exchangeSize _DK_exchangeSize
DLLIMPORT int _DK_maximumPlayers;
#define maximumPlayers _DK_maximumPlayers
DLLIMPORT struct TbNetworkPlayerInfo *_DK_localPlayerInfoPtr;
#define localPlayerInfoPtr _DK_localPlayerInfoPtr
DLLIMPORT void *_DK_localDataPtr;
#define localDataPtr _DK_localDataPtr
DLLIMPORT void *_DK_compositeBuffer;
#define compositeBuffer _DK_compositeBuffer
DLLIMPORT long _DK_sequenceNumber;
#define sequenceNumber _DK_sequenceNumber
DLLIMPORT long _DK_timeCount;
#define timeCount _DK_timeCount
DLLIMPORT long _DK_maxTime;
#define maxTime _DK_maxTime
DLLIMPORT int _DK_runningTwoPlayerModel;
#define runningTwoPlayerModel _DK_runningTwoPlayerModel
DLLIMPORT int _DK_waitingForPlayerMapResponse;
#define waitingForPlayerMapResponse _DK_waitingForPlayerMapResponse
DLLIMPORT long _DK_compositeBufferSize;
#define compositeBufferSize _DK_compositeBufferSize
DLLIMPORT long _DK_basicTimeout;
#define basicTimeout _DK_basicTimeout
DLLIMPORT int _DK_noOfEnumeratedDPlayServices;
#define noOfEnumeratedDPlayServices _DK_noOfEnumeratedDPlayServices
DLLIMPORT struct ClientDataEntry _DK_clientDataTable[32];
#define clientDataTable _DK_clientDataTable
DLLIMPORT struct ReceiveCallbacks _DK_receiveCallbacks;
#define receiveCallbacks _DK_receiveCallbacks
DLLIMPORT unsigned long _DK_hostId;
#define hostId _DK_hostId
DLLIMPORT unsigned long _DK_localPlayerId;
#define localPlayerId _DK_localPlayerId
DLLIMPORT int _DK_gotCompositeData;
#define gotCompositeData _DK_gotCompositeData
DLLIMPORT struct _GUID _DK_clientGuidTable[];
#define clientGuidTable _DK_clientGuidTable
DLLIMPORT long _DK_anim_counter;
#define anim_counter _DK_anim_counter
DLLIMPORT long _DK_block_ptrs[592];
#define block_ptrs _DK_block_ptrs
DLLIMPORT unsigned char _DK_colours[16][16][16];
#define colours _DK_colours
DLLIMPORT long _DK_frame_number;
#define frame_number _DK_frame_number
DLLIMPORT char _DK_grabbed_small_map;
#define grabbed_small_map _DK_grabbed_small_map
DLLIMPORT long _DK_draw_spell_cost;
#define draw_spell_cost _DK_draw_spell_cost
DLLIMPORT int _DK_lbCosTable[2048];
#define lbCosTable _DK_lbCosTable
DLLIMPORT int _DK_lbSinTable[2048];
#define lbSinTable _DK_lbSinTable
DLLIMPORT int _DK_parchment_loaded;
#define parchment_loaded _DK_parchment_loaded
DLLIMPORT char _DK_level_name[88];
#define level_name _DK_level_name
DLLIMPORT unsigned char _DK_poly_pool[0x40000];
#define poly_pool _DK_poly_pool
DLLIMPORT unsigned char *_DK_hires_parchment;
#define hires_parchment _DK_hires_parchment
DLLIMPORT struct NetMessage _DK_net_message[8];
#define net_message _DK_net_message
DLLIMPORT int _DK_fe_computer_players;
#define fe_computer_players _DK_fe_computer_players
DLLIMPORT long _DK_resurrect_creature_scroll_offset;
#define resurrect_creature_scroll_offset _DK_resurrect_creature_scroll_offset
DLLIMPORT unsigned short _DK_dungeon_special_selected;
#define dungeon_special_selected _DK_dungeon_special_selected
DLLIMPORT long _DK_transfer_creature_scroll_offset;
#define transfer_creature_scroll_offset _DK_transfer_creature_scroll_offset
DLLIMPORT struct SpecialDesc _DK_special_desc[8];
#define special_desc _DK_special_desc
DLLIMPORT unsigned char *_DK_block_mem;
#define block_mem _DK_block_mem
DLLIMPORT struct Room *_DK_start_rooms;
#define start_rooms _DK_start_rooms
DLLIMPORT struct Room *_DK_end_rooms;
#define end_rooms _DK_end_rooms
DLLIMPORT unsigned char _DK_smooth_on;
#define smooth_on _DK_smooth_on
DLLIMPORT struct BigSprite _DK_status_panel;
#define status_panel _DK_status_panel
DLLIMPORT struct TbSprite *_DK_gui_panel_sprites;
#define gui_panel_sprites _DK_gui_panel_sprites
DLLIMPORT struct TbSprite *_DK_end_gui_panel_sprites;
#define end_gui_panel_sprites _DK_end_gui_panel_sprites
DLLIMPORT unsigned char _DK_ghost[256*16];
#define ghost _DK_ghost
DLLIMPORT unsigned char _DK_fade_tables[256*64];
#define fade_tables _DK_fade_tables
DLLIMPORT unsigned short _DK_breed_activities[CREATURE_TYPES_COUNT];
#define breed_activities _DK_breed_activities
DLLIMPORT char _DK_top_of_breed_list;
#define top_of_breed_list _DK_top_of_breed_list
DLLIMPORT long _DK_optimised_lights;
#define optimised_lights _DK_optimised_lights
DLLIMPORT long _DK_total_lights;
#define total_lights _DK_total_lights
DLLIMPORT unsigned char _DK_do_lights;
#define do_lights _DK_do_lights
DLLIMPORT struct MessageQueueEntry _DK_message_queue[MESSAGE_QUEUE_COUNT];
#define message_queue _DK_message_queue

DLLIMPORT struct TbSprite *_DK_edit_icon_sprites[];
#define edit_icon_sprites _DK_edit_icon_sprites
DLLIMPORT struct TrapStats _DK_trap_stats[7]; //not sure - maybe it's 8?
#define trap_stats _DK_trap_stats
//DLLIMPORT Thing_Class_Func _DK_class_functions[14];
//#define class_functions _DK_class_functions
DLLIMPORT long _DK_imp_spangle_effects[];
#define imp_spangle_effects _DK_imp_spangle_effects
DLLIMPORT struct Creatures _DK_creatures[32];
#define creatures _DK_creatures

#pragma pack()

//Functions - exported by the DLL

DLLIMPORT int __stdcall _DK_WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
DLLIMPORT int __stdcall _DK_LbBullfrogMain(unsigned short argc,char **argv);
DLLIMPORT int __stdcall _DK_setup_game(void);
DLLIMPORT int __stdcall _DK_game_loop(void);
DLLIMPORT int __stdcall _DK_init_sound(void);
DLLIMPORT int __stdcall _DK_LbErrorLogSetup(char *directory, char *filename, unsigned char flag);
DLLIMPORT void __fastcall _DK_get_cpu_info(struct CPU_INFO *cpu_info);
DLLIMPORT int __stdcall _DK_SyncLog(char *Format, ...);
DLLIMPORT int __cdecl _DK_LbDataLoadAll(struct TbLoadFiles *load_files);
DLLIMPORT void __cdecl _DK_set_cpu_mode(int mode);
DLLIMPORT void __cdecl _DK_display_loading_screen(void);
DLLIMPORT int __cdecl _DK_initial_setup(void);
DLLIMPORT int __cdecl _DK_setup_game_sound_heap(void);
DLLIMPORT int __cdecl _DK_load_settings(void);
DLLIMPORT void __cdecl _DK_init_creature_scores(void);
DLLIMPORT void __cdecl _DK_setup_3d(void);
DLLIMPORT void __cdecl _DK_setup_stuff(void);
DLLIMPORT void __cdecl _DK_input_eastegg(void);
DLLIMPORT void __cdecl _DK_update(void);
DLLIMPORT void __cdecl _DK_wait_at_frontend(void);
DLLIMPORT void __cdecl _DK_clear_mapwho(void);
DLLIMPORT void __cdecl _DK_delete_all_structures(void);
DLLIMPORT void __cdecl _DK_PaletteSetPlayerPalette(struct PlayerInfo *player, unsigned char *palette);
DLLIMPORT void __cdecl _DK_initialise_eye_lenses(void);
DLLIMPORT void __cdecl _DK_setup_eye_lens(long);

DLLIMPORT void __stdcall _DK_IsRunningMark(void);
DLLIMPORT void __stdcall _DK_IsRunningUnmark(void);
DLLIMPORT int __stdcall _DK_LbMouseSuspend(void);
DLLIMPORT int __stdcall _DK_LbDataFreeAll(struct TbLoadFiles *load_files);
DLLIMPORT int __stdcall _DK_LbMemoryFree(void *buffer);
DLLIMPORT int __stdcall _DK_LbMemoryReset(void);
DLLIMPORT int __stdcall _DK_play_smk_(char *fname, int smkflags, int plyflags);
DLLIMPORT int __fastcall _DK_LbFileClose(TbFileHandle handle);
DLLIMPORT int __cdecl _DK_process_sound_heap(void);
DLLIMPORT void __cdecl _DK_setup_engine_window(long, long, long, long);
DLLIMPORT void __cdecl _DK_redraw_display(void);
DLLIMPORT void __cdecl _DK_cumulative_screen_shot(void);
DLLIMPORT long __cdecl _DK_anim_record_frame(unsigned char *screenbuf, unsigned char *palette);
DLLIMPORT int __stdcall _DK_LbIsActive(void);
DLLIMPORT void __cdecl _DK_load_game_save_catalogue(CatalogueEntry *catalg);
DLLIMPORT void __cdecl _DK_frontend_set_state(long);
DLLIMPORT void __cdecl _DK_frontnet_service_update(void);
DLLIMPORT void __cdecl _DK_frontnet_session_update(void);
DLLIMPORT void __cdecl _DK_frontnet_start_update(void);
DLLIMPORT void __cdecl _DK_frontnet_modem_update(void);
DLLIMPORT void __cdecl _DK_frontnet_serial_update(void);
//DLLIMPORT void * __cdecl _DK_frontnet_session_join(GuiButton); (may be incorrect)
DLLIMPORT int __cdecl _DK_get_gui_inputs(int);
DLLIMPORT void __cdecl _DK_demo(void);
DLLIMPORT void __cdecl _DK_draw_gui(void);
DLLIMPORT void __cdecl _DK_save_settings(void);
DLLIMPORT void __cdecl _DK_startup_saved_packet_game(void);
DLLIMPORT int __cdecl _DK_setup_network_service(int srvidx);
DLLIMPORT int __cdecl _DK_process_3d_sounds(void);
DLLIMPORT char *_DK_mdlf_for_cd(struct TbLoadFiles *);
DLLIMPORT char *_DK_mdlf_default(TbLoadFiles *);
DLLIMPORT int _DK_LbSpriteSetupAll(struct TbSetupSprite t_setup[]);
DLLIMPORT void _DK_update_breed_activities(void);
DLLIMPORT void _DK_maintain_my_battle_list(void);
DLLIMPORT char _DK_mouse_is_over_small_map(int, int);
DLLIMPORT long _DK_screen_to_map(struct Camera *camera, long scrpos_x, long scrpos_y, struct Coord3d *mappos);
DLLIMPORT struct Thing *_DK_get_special_at_position(long x, long y);
DLLIMPORT struct Thing *_DK_get_spellbook_at_position(long x, long y);
DLLIMPORT struct Thing *_DK_get_crate_at_position(long x, long y);
DLLIMPORT struct Thing *_DK_get_nearest_object_at_position(long x, long y);
DLLIMPORT int _DK_is_game_key_pressed(long, long *, int);
DLLIMPORT long _DK_get_inputs(void);
DLLIMPORT void _DK_load_packets_for_turn(long gameturn);
DLLIMPORT TbError _DK_LbNetwork_Stop(void);
DLLIMPORT TbError _DK_LbNetwork_ChangeExchangeBuffer(void *, unsigned long);
DLLIMPORT void _DK_get_level_lost_inputs(void);
DLLIMPORT long _DK_get_global_inputs(void);
DLLIMPORT long _DK_get_dungeon_control_action_inputs(void);
DLLIMPORT void _DK_get_dungeon_control_nonaction_inputs(void);
DLLIMPORT void _DK_get_packet_control_mouse_clicks(void);
DLLIMPORT void _DK_get_creature_control_nonaction_inputs(void);
DLLIMPORT void _DK_get_map_nonaction_inputs(void);
DLLIMPORT long _DK_get_bookmark_inputs(void);
DLLIMPORT long _DK_get_small_map_inputs(long x, long y, long);
DLLIMPORT void _DK_turn_off_menu(char mnu_idx);
DLLIMPORT void _DK_fake_button_click(long btn_idx);
DLLIMPORT void _DK_turn_off_roaming_menus(void);
DLLIMPORT void _DK_turn_off_all_panel_menus(void);
DLLIMPORT void _DK_initialise_tab_tags_and_menu(long);
DLLIMPORT void _DK_process_network_error(long);
DLLIMPORT int _DK_play_smk_via_buffer(char *fname, int smkflags, int plyflags);
DLLIMPORT int _DK_play_smk_direct(char *fname, int smkflags, int plyflags);
DLLIMPORT TbError _DK_LbNetwork_Init(unsigned long,struct _GUID guid, unsigned long, void *, unsigned long, struct TbNetworkPlayerInfo *netplayr, void *);
DLLIMPORT void _DK_process_rooms(void);
DLLIMPORT void _DK_process_dungeons(void);
DLLIMPORT void _DK_process_messages(void);
DLLIMPORT void _DK_find_nearest_rooms_for_ambient_sound(void);
DLLIMPORT void __cdecl _DK_light_render_area(int startx, int starty, int endx, int endy);
DLLIMPORT void _DK_process_player_research(int plr_idx);
DLLIMPORT long _DK_process_player_manufacturing(int plr_idx);
DLLIMPORT void _DK_event_process_events(void);
DLLIMPORT void _DK_update_all_events(void);
DLLIMPORT void _DK_process_level_script(void);
DLLIMPORT void _DK_process_computer_players2(void);
DLLIMPORT long _DK_process_action_points(void);
DLLIMPORT long _DK_PaletteFadePlayer(struct PlayerInfo *player);
DLLIMPORT void _DK_message_update(void);
DLLIMPORT void __cdecl _DK_process_player_instance(struct PlayerInfo *player);
DLLIMPORT void _DK_process_player_instances(void);
DLLIMPORT long _DK_wander_point_update(struct Wander *wandr);
DLLIMPORT void __cdecl _DK_update_player_camera(struct PlayerInfo *player);
DLLIMPORT void _DK_set_level_objective(char *msg_text);
DLLIMPORT void _DK_update_flames_nearest_camera(struct Camera *camera);
DLLIMPORT void _DK_update_footsteps_nearest_camera(struct Camera *camera);
DLLIMPORT void _DK_process_player_states(void);
DLLIMPORT void _DK_process_armageddon(void);  //not sure about the name!
DLLIMPORT void _DK_set_mouse_light(struct PlayerInfo *player);
DLLIMPORT void _DK_process_pointer_graphic(void);
DLLIMPORT void _DK_message_draw(void);
DLLIMPORT void _DK_draw_slab64k(long pos_x, long pos_y, long width, long height);
DLLIMPORT void _DK_redraw_creature_view(void);
DLLIMPORT void _DK_redraw_isometric_view(void);
DLLIMPORT void _DK_redraw_frontview(void);
DLLIMPORT void _DK_draw_tooltip(void);
DLLIMPORT long _DK_map_fade_in(long a);
DLLIMPORT long _DK_map_fade_out(long a);
DLLIMPORT void _DK_draw_map_parchment(void);
DLLIMPORT void _DK_draw_2d_map(void);
DLLIMPORT void _DK_draw_gui(void);
DLLIMPORT void _DK_draw_zoom_box(void);
DLLIMPORT void _DK_light_stat_light_map_clear_area(long x1, long y1, long x2, long y2);
DLLIMPORT void _DK_light_signal_stat_light_update_in_area(long x1, long y1, long x2, long y2);
DLLIMPORT void _DK_turn_off_query(char a);
DLLIMPORT void _DK_open_packet_file_for_load(char *fname);
DLLIMPORT void _DK_post_init_level(void);
DLLIMPORT void _DK_post_init_players(void);
DLLIMPORT void _DK_init_level(void);
DLLIMPORT void _DK_init_player(struct PlayerInfo *player, int a2);
DLLIMPORT int _DK_frontend_is_player_allied(long plyr1, long plyr2);

#ifdef __cplusplus
}
#endif

//Functions - reworked
short setup_game(void);
void game_loop(void);
short reset_game(void);
void update(void);

short copy_raw8_image_to_screen_center(const unsigned char *buf,const int img_width,const int img_height);
short copy_raw8_image_buffer(unsigned char *dst_buf,const int scanline,const int nlines,const int spx,const int spy,const unsigned char *src_buf,const int src_width,const int src_height,const int m);

short setup_network_service(int srvidx);
DLLIMPORT extern unsigned char *_DK_blue_palette;
#define blue_palette _DK_blue_palette
TbError LbNetwork_Init(unsigned long,struct _GUID guid, unsigned long, void *, unsigned long, struct TbNetworkPlayerInfo *netplayr, void *);
short wait_for_cd_to_be_available(void);
void ProperFadePalette(unsigned char *pal, long n, TbPaletteFadeFlag flg);
short continue_game_available();
short get_gui_inputs(short gameplay_on);
void intro(void);
void outro(void);
void load_level_file(long lvnum);
void load_map_file(long lvidx);

void reveal_whole_map(struct PlayerInfo *player);
void increase_level(struct PlayerInfo *player);
void multiply_creatures(struct PlayerInfo *player);
struct Thing *create_creature(struct Coord3d *pos, unsigned short a1, unsigned short a2);
void set_creature_level(struct Thing *thing, long nlvl);
short thing_is_special(struct Thing *thing);
#define is_dungeon_special thing_is_special
void activate_dungeon_special(struct Thing *thing, struct PlayerInfo *player);
void resurrect_creature(struct Thing *thing, unsigned char a2, unsigned char a3, unsigned char a4);
void transfer_creature(struct Thing *tng1, struct Thing *tng2, unsigned char a3);
void creature_increase_level(struct Thing *thing);
void remove_events_thing_is_attached_to(struct Thing *thing);
unsigned long steal_hero(struct PlayerInfo *player, struct Coord3d *pos);
void make_safe(struct PlayerInfo *player);
short activate_bonus_level(struct PlayerInfo *player);
void delete_thing_structure(struct Thing *thing, long a2);
long creature_instance_is_available(struct Thing *thing, long inum);
short load_texture_map_file(long tmapidx, unsigned char a2);
short init_animating_texture_maps(void);
void reset_gui_based_on_player_mode(void);
void reinit_tagged_blocks_for_player(unsigned char idx);
void restore_computer_player_after_load(void);
void sound_reinit_after_load(void);
void draw_power_hand(void);
void draw_bonus_timer(void);
void zoom_from_map(void);
void toggle_tooltips(void);
void toggle_main_cheat_menu(void);

int setup_old_network_service(void);
short toggle_computer_player(int idx);
void save_settings(void);
void setup_engine_window(long x1, long y1, long x2, long y2);
short show_onscreen_msg(int nturns, const char *fmt_str, ...);
int LoadMcgaData(void);
void PaletteSetPlayerPalette(struct PlayerInfo *player, unsigned char *pal);
void set_engine_view(struct PlayerInfo *player, long val);
unsigned char find_first_battle_of_mine(unsigned char idx);
unsigned long scale_camera_zoom_to_screen(unsigned long zoom_lvl);
void set_player_instance(struct PlayerInfo *player, long a2, int a3);
void init_good_player_as(long plr_idx);

void check_players_won(void);
void check_players_lost(void);
void process_dungeon_power_magic(void);
void process_dungeon_devastation_effects(void);
void process_entrance_generation(void);
void process_things_in_dungeon_hand(void);
void process_payday(void);
void init_keepers_map_exploration(void);
void init_dungeons_research(void);
void clear_creature_pool(void);
void open_new_packet_file_for_save(void);
long load_stats_files(void);
void check_and_auto_fix_stats(void);
long update_dungeon_scores(void);
long update_dungeon_generation_speeds(void);
void calculate_dungeon_area_scores(void);
void setup_computer_players2(void);
long get_next_research_item(struct Dungeon *dungeon);
void init_creature_level(struct Thing *thing, long nlev);
short send_creature_to_room(struct Thing *thing, struct Room *room);
struct Room *get_room_thing_is_on(struct Thing *thing);
short set_start_state(struct Thing *thing);
void init_creature_state(struct Thing *thing);
void gui_set_button_flashing(long a1, long a2);
struct Thing *get_trap_for_position(long x, long y);
long light_is_light_allocated(long lgt_id);
void light_set_light_position(long lgt_id, struct Coord3d *pos);

void initialise_eye_lenses(void);
void setup_eye_lens(long nlens);
void reinitialise_eye_lens(long nlens);
void reset_eye_lenses(void);
void view_set_camera_y_inertia(struct Camera *cam, long a2, long a3);
void view_set_camera_x_inertia(struct Camera *cam, long a2, long a3);
void view_set_camera_rotation_inertia(struct Camera *cam, long a2, long a3);
void view_zoom_camera_in(struct Camera *cam, long a2, long a3);
void set_camera_zoom(struct Camera *cam, long val);
void view_zoom_camera_out(struct Camera *cam, long a2, long a3);
long get_camera_zoom(struct Camera *camera);
void update_camera_zoom_bounds(struct Camera *cam,unsigned long zoom_max,unsigned long zoom_min);
void keep_local_camera_zoom_level(unsigned long prev_units_per_pixel_size);
void set_mouse_light(struct PlayerInfo *player);
void start_resurrect_creature(struct PlayerInfo *player, struct Thing *thing);
void start_transfer_creature(struct PlayerInfo *player, struct Thing *thing);
void magic_use_power_hold_audience(unsigned char idx);
void clear_slab_dig(long a1, long a2, char a3);
void light_initialise(void);
void delete_all_structures(void);
void clear_mapwho(void);
void clear_game(void);
void clear_game_for_save(void);
long init_navigation(void);
void update_explored_flags_for_power_sight(struct PlayerInfo *player);
void engine(struct Camera *cam);
void smooth_screen_area(unsigned char *a1, long a2, long a3, long a4, long a5, long a6);
void remove_explored_flags_for_power_sight(struct PlayerInfo *player);
void DrawBigSprite(long x, long y, struct BigSprite *bigspr, struct TbSprite *sprite);
void draw_gold_total(unsigned char a1, long a2, long a3, long a4);
void pannel_map_draw(long x, long y, long zoom);
void draw_overlay_things(long zoom);
void draw_overlay_compass(long a1, long a2);

unsigned long seed_check_random(unsigned long range, unsigned long *seed, const char *func_name, unsigned long place);
void setup_heap_manager(void);
int setup_heap_memory(void);
void reset_heap_manager(void);
void reset_heap_memory(void);
long light_create_light(struct InitLight *ilght);
void light_set_light_never_cache(long idx);
void reset_player_mode(struct PlayerInfo *player, unsigned char a2);
void init_keeper_map_exploration(struct PlayerInfo *player);
void init_player_cameras(struct PlayerInfo *player);
void init_lookups(void);
void pannel_map_update(long x, long y, long w, long h);
short play_smacker_file(char *filename, int nstate);
struct Thing *create_effect(struct Coord3d *pos, unsigned short a2, unsigned char a3);
void turn_off_query(short a);
void free_swipe_graphic(void);
void complete_level(struct PlayerInfo *player);
short set_gamma(char corrlvl, short do_set);
void resync_game(void);
void level_lost_go_first_person(long plridx);
long battle_move_player_towards_battle(struct PlayerInfo *player, long var);
void  toggle_ally_with_player(long plyridx, unsigned int allyidx);
void magic_use_power_armageddon(unsigned int plridx);
void lose_level(struct PlayerInfo *player);
void directly_cast_spell_on_thing(long plridx, unsigned char a2, unsigned short a3, long a4);
void output_message(long idx, long a, long b);
void go_on_then_activate_the_event_box(long plridx, long evidx);
void turn_off_sight_of_evil(long plridx);
short dump_held_things_on_map(unsigned int plyridx, long a2, long a3, short a4);
void set_player_mode(struct PlayerInfo *player, long val);
long set_autopilot_type(unsigned int plridx, long aptype);
void event_delete_event(long plridx, long num);
void set_player_state(struct PlayerInfo *player, short a1, long a2);
short magic_use_power_obey(unsigned short plridx);
long place_thing_in_power_hand(struct Thing *thing, long var);
void turn_off_call_to_arms(long a);
long event_move_player_towards_event(struct PlayerInfo *player, long var);
void toggle_creature_tendencies(struct PlayerInfo *player, short val);
void centre_engine_window(void);
void change_engine_window_relative_size(long w_delta, long h_delta);
void light_set_lights_on(char state);
void message_add(char c);
void init_messages(void);
void battle_initialise(void);
void event_initialise_all(void);
void add_thing_to_list(struct Thing *thing, struct StructureList *list);
struct Thing *allocate_free_thing_structure(unsigned char a1);
unsigned char i_can_allocate_free_thing_structure(unsigned char a1);
struct Thing *create_ambient_sound(struct Coord3d *pos, unsigned short a2, unsigned short owner);
void update_thing_animation(struct Thing *thing);
long update_thing(struct Thing *thing);
long get_thing_checksum(struct Thing *thing);
long update_thing_sound(struct Thing *thing);
long update_cave_in(struct Thing *thing);
void move_thing_in_map(struct Thing *thing, struct Coord3d *pos);
void process_creature_instance(struct Thing *thing);
void update_creature_count(struct Thing *thing);
long process_creature_state(struct Thing *thing);
long get_floor_height_under_thing_at(struct Thing *thing, struct Coord3d *pos);
long move_creature(struct Thing *thing);
void process_spells_affected_by_effect_elements(struct Thing *thing);
long get_top_cube_at_pos(long mpos);
void apply_damage_to_thing_and_display_health(struct Thing *thing, long a1, char a2);
long get_foot_creature_has_down(struct Thing *thing);
void process_disease(struct Thing *thing);
void set_creature_graphic(struct Thing *thing);
void process_keeper_spell_effect(struct Thing *thing);
long creature_is_group_leader(struct Thing *thing);
void leader_find_positions_for_followers(struct Thing *thing);
long update_creature_levels(struct Thing *thing);
long process_creature_self_spell_casting(struct Thing *thing);
void process_thing_spell_effects(struct Thing *thing);
short kill_creature(struct Thing *thing, struct Thing *tngrp, char a1, unsigned char a2, unsigned char a3, unsigned char a4);
struct Thing *create_thing(struct Coord3d *pos, unsigned short a1, unsigned short a2, unsigned short a3, long a4);
void process_creature_standing_on_corpses_at(struct Thing *thing, struct Coord3d *pos);
long cleanup_current_thing_state(struct Thing *thing);
unsigned long setup_move_off_lava(struct Thing *thing);
struct Room *player_has_room_of_type(long plr_idx, long roomkind);
struct Room *find_room_with_spare_room_item_capacity(unsigned char a1, signed char a2);
long create_workshop_object_in_workshop_room(long a1, long a2, long a3);
long get_next_manufacture(struct Dungeon *dungeon);
void remove_thing_from_mapwho(struct Thing *thing);
void place_thing_in_mapwho(struct Thing *thing);
long get_thing_height_at(struct Thing *thing, struct Coord3d *pos);

long update_object(struct Thing *thing);
long update_shot(struct Thing *thing);
long update_effect_element(struct Thing *thing);
long update_dead_creature(struct Thing *thing);
long update_creature(struct Thing *thing);
long update_effect(struct Thing *thing);
long process_effect_generator(struct Thing *thing);
long update_trap(struct Thing *thing);
long process_door(struct Thing *thing);

int LbNetwork_Exchange(struct Packet *pckt);
void startup_network_game(void);

short gui_box_is_not_valid(struct GuiBox *gbox);
struct GuiBox *gui_create_box(long x, long y, struct GuiBoxOption *optn_list);
void gui_delete_box(struct GuiBox *gbox);

//Functions - internal

//Functions - inline

void inline fade_in(void)
{
  ProperFadePalette(_DK_frontend_palette, 8, Lb_PALETTE_FADE_OPEN);
}

void inline fade_out(void)
{
  ProperFadePalette(0, 8, Lb_PALETTE_FADE_CLOSED);
  LbScreenClear(0);
}

// Variables - no longer imported

#endif // DK_KEEPERFX_H
