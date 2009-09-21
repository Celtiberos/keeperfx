/******************************************************************************/
// Free implementation of Bullfrog's Dungeon Keeper strategy game.
/******************************************************************************/
/** @file front_landview.h
 *     Header file for front_landview.c.
 * @par Purpose:
 *     Land view, where the user can select map for campaign or multiplayer.
 * @par Comment:
 *     Just a header file - #defines, typedefs, function prototypes etc.
 * @author   Tomasz Lis
 * @date     16 Mar 2009 - 01 Apr 2009
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/

#ifndef DK_FRONT_LAND_H
#define DK_FRONT_LAND_H

#include "bflib_basics.h"
#include "globals.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/

/******************************************************************************/
#pragma pack(1)

struct TbSprite;

struct MapLevelInfo { // sizeof = 56
  unsigned char field_0;
  unsigned char field_1;
  long fade_step;
  long fade_pos;
  long field_A;
  long field_E;
  long field_12;
  long scrshift_x;
  long scrshift_y;
  long field_1E;
  long field_22;
  long field_26;
  long field_2A;
  long hotspot_x;
  long hotspot_y;
  unsigned char field_36;
  unsigned char field_37;
};

struct ScreenPacket { // sizeof = 12
  unsigned char field_0[4];
  unsigned char field_4;
  char field_5;
  short field_6;
  short field_8;
  char field_A;
  unsigned char field_B;
};

/******************************************************************************/
DLLIMPORT extern TbClockMSec _DK_play_desc_speech_time;
#define play_desc_speech_time _DK_play_desc_speech_time
DLLIMPORT extern unsigned long _DK_played_bad_descriptive_speech;
#define played_bad_descriptive_speech _DK_played_bad_descriptive_speech
DLLIMPORT extern unsigned long _DK_played_good_descriptive_speech;
#define played_good_descriptive_speech _DK_played_good_descriptive_speech
DLLIMPORT extern unsigned long _DK_map_flag_data;
#define map_flag_data _DK_map_flag_data
DLLIMPORT extern unsigned long _DK_end_map_flag_data;
#define end_map_flag_data _DK_end_map_flag_data
DLLIMPORT extern unsigned long _DK_map_font_data;
#define map_font_data _DK_map_font_data
DLLIMPORT extern unsigned long _DK_end_map_font_data;
#define end_map_font_data _DK_end_map_font_data
DLLIMPORT extern unsigned long _DK_map_hand_data;
#define map_hand_data _DK_map_hand_data
DLLIMPORT extern struct TbSetupSprite _DK_netmap_flag_setup_sprites[];
#define netmap_flag_setup_sprites _DK_netmap_flag_setup_sprites
DLLIMPORT extern long _DK_fe_net_level_selected;
#define fe_net_level_selected _DK_fe_net_level_selected
DLLIMPORT extern long _DK_net_map_limp_time;
#define net_map_limp_time _DK_net_map_limp_time
DLLIMPORT extern struct ScreenPacket _DK_net_screen_packet[4];
#define net_screen_packet _DK_net_screen_packet
DLLIMPORT extern long _DK_players_currently_in_session;
#define players_currently_in_session _DK_players_currently_in_session
DLLIMPORT extern unsigned long _DK_end_map_hand_data;
#define end_map_hand_data _DK_end_map_hand_data
DLLIMPORT extern struct TbSprite *_DK_map_flag;
#define map_flag _DK_map_flag
DLLIMPORT extern struct TbSprite *_DK_end_map_flag;
#define end_map_flag _DK_end_map_flag
DLLIMPORT extern struct TbSprite *_DK_map_font;
#define map_font _DK_map_font
DLLIMPORT extern struct TbSprite *_DK_end_map_font;
#define end_map_font _DK_end_map_font
DLLIMPORT extern struct TbSprite *_DK_map_hand;
#define map_hand _DK_map_hand
DLLIMPORT extern struct TbSprite *_DK_end_map_hand;
#define end_map_hand _DK_end_map_hand
DLLIMPORT extern struct MapLevelInfo _DK_map_info;
#define map_info _DK_map_info
DLLIMPORT extern long _DK_map_sound_fade;
#define map_sound_fade _DK_map_sound_fade
DLLIMPORT extern unsigned char *_DK_map_screen;
#define map_screen _DK_map_screen
DLLIMPORT extern long *_DK_window_y_offset;
#define window_y_offset _DK_window_y_offset
DLLIMPORT extern unsigned char *_DK_map_window;
#define map_window _DK_map_window
DLLIMPORT extern struct TbLoadFiles _DK_map_flag_load_files[];
//#define map_flag_load_files _DK_map_flag_load_files
DLLIMPORT extern struct TbSetupSprite _DK_map_flag_setup_sprites[];
#define map_flag_setup_sprites _DK_map_flag_setup_sprites

#pragma pack()
/******************************************************************************/
/******************************************************************************/
void frontnetmap_unload(void);
TbBool frontnetmap_load(void);
void frontnetmap_input(void);
void frontnetmap_draw(void);
long frontnetmap_update(void);
void frontmap_input(void);
void frontmap_draw(void);
TbBool frontmap_load(void);
void frontmap_unload(void);
long frontmap_update(void);
void frontzoom_to_point(long a1, long a2, long a3);
void compressed_window_draw(void);
void frontnet_init_level_descriptions(void);

short play_current_description_speech(short play_good);
short play_description_speech(LevelNumber lvnum, short play_good);
void check_mouse_scroll(void);
void update_velocity(void);
/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
