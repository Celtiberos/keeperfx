/******************************************************************************/
// Free implementation of Bullfrog's Dungeon Keeper strategy game.
/******************************************************************************/
/** @file game_saves.c
 *     Saved games maintain functions.
 * @par Purpose:
 *     For opening, writing, listing saved games.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     27 Jan 2009 - 25 Mar 2009
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "game_saves.h"

#include "globals.h"
#include "bflib_basics.h"
#include "bflib_memory.h"
#include "bflib_fileio.h"
#include "bflib_dernc.h"
#include "bflib_bufrw.h"

#include "config.h"
#include "config_campaigns.h"
#include "front_simple.h"
#include "frontend.h"
#include "front_landview.h"
#include "keeperfx.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/******************************************************************************/
DLLIMPORT long _DK_save_game_save_catalogue(struct CatalogueEntry *game_catalg);
DLLIMPORT void _DK_load_game_save_catalogue(struct CatalogueEntry *game_catalg);
DLLIMPORT long _DK_load_game(long);
/******************************************************************************/
long const VersionMajor = 1;
long const VersionMinor = 12;

const char *continue_game_filename="fx1contn.sav";
const char *saved_game_filename="fx1g%04d.sav";
const char *save_catalogue_filename="fx1save.cat";
const char *packet_filename="fx1rp%04d.pck";

/******************************************************************************/

short save_version_compatible(long filesize,struct Game *header)
{
  // Native version
  if ((filesize == sizeof(struct Game)) &&
    (header->version_major == VersionMajor) &&
    (header->version_minor == VersionMinor))
    return true;
  // Compatibility list
  if ((filesize == sizeof(struct Game)) &&
    (header->version_major == VersionMajor) &&
    (header->version_minor <= 8) &&
    (VersionMinor == 10))
    return true;
  if ((filesize == sizeof(struct Game)) &&
    (header->version_major == VersionMajor) &&
    (header->version_minor <= 10) &&
    (VersionMinor == 12))
    return true;
  return false;
}

short save_game(long slot_idx)
{
  char *fname;
  if (!save_game_save_catalogue())
    return false;
  game.version_major = VersionMajor;
  game.version_minor = VersionMinor;
  game.load_restart_level = get_loaded_level_number();
  fname = prepare_file_fmtpath(FGrp_Save, saved_game_filename, slot_idx);
  if (LbFileSaveAt(fname, &game, sizeof(struct Game)) == -1)
    return false;
  return true;
}

short is_save_game_loadable(long num)
{
  TbFileHandle fh;
  unsigned char buf[14];
  char *fname;
  // Prepare filename and open the file
  fname = prepare_file_fmtpath(FGrp_Save,saved_game_filename,num);
  fh = LbFileOpen(fname, Lb_FILE_MODE_READ_ONLY);
  if (fh != -1)
  {
    // Let's try to read the file, just to be sure
    if (LbFileRead(fh, &buf, 14) == 14)
    {
      LbFileClose(fh);
      return true;
    }
    LbFileClose(fh);
  }
  return false;
}

short load_game(long slot_num)
{
  static const char *func_name="load_game";
  //return _DK_load_game(slot_num);
  char *fname;
  TbFileHandle handle;
  struct PlayerInfo *player;
  struct Dungeon *dungeon;
  unsigned char buf[14];
  char cmpgn_fname[CAMPAIGN_FNAME_LEN];
#if (BFDEBUG_LEVEL > 6)
    LbSyncLog("%s: Starting\n",func_name);
#endif
  reset_eye_lenses();
  fname = prepare_file_fmtpath(FGrp_Save,saved_game_filename,slot_num);
  if (!wait_for_cd_to_be_available())
    return 0;
  handle = LbFileOpen(fname,Lb_FILE_MODE_READ_ONLY);
  if (handle == -1)
  {
    LbWarnLog("Cannot open saved game file \"%s\".\n",fname);
    save_catalogue_slot_disable(slot_num);
    return 0;
  }
  if (LbFileRead(handle, buf, 14) != 14)
  {
    LbFileClose(handle);
    save_catalogue_slot_disable(slot_num);
    return 0;
  }
  LbFileSeek(handle, (char *)&game.campaign_fname[0] - (char *)&game.load_restart_level, Lb_FILE_SEEK_BEGINNING);
  LbFileRead(handle, cmpgn_fname, CAMPAIGN_FNAME_LEN);
  cmpgn_fname[CAMPAIGN_FNAME_LEN-1] = '\0';
  LbFileClose(handle);
  if (!change_campaign(cmpgn_fname))
  {
    error(func_name, 867, "Unable to load campaign associated with saved game");
    return 0;
  }
  if (!save_version_compatible(LbFileLength(fname),(struct Game *)buf))
  {
    LbWarnLog("Saved game file \"%s\" has incompatible version; restarting level.\n",fname);
    player = &(game.players[my_player_number%PLAYERS_COUNT]);
    player->field_7 = 0;
    my_player_number = default_loc_player;
    player = &(game.players[my_player_number%PLAYERS_COUNT]);
    game.flagfield_14EA4A = 2;
    set_flag_byte(&game.numfield_A,0x01,false);
    player->field_2C = 1;
    set_selected_level_number(((struct Game *)buf)->load_restart_level);
    set_continue_level_number(((struct Game *)buf)->continue_level_number);
    startup_network_game();
    return 1;
  }
  if (LbFileLoadAt(fname, &game) != sizeof(struct Game))
  {
    LbWarnLog("Couldn't correctly load saved game \"%s\".\n",fname);
    return 0;
  }
  LbStringCopy(game.campaign_fname,campaign.fname,sizeof(game.campaign_fname));
  init_lookups();
  reinit_level_after_load();
  output_message(102, 0, 1);
  pannel_map_update(0, 0, map_subtiles_x+1, map_subtiles_y+1);
  calculate_moon_phase(false,false);
  update_extra_levels_visibility();
  player = &(game.players[my_player_number%PLAYERS_COUNT]);
  set_flag_byte(&player->field_3,0x08,false);
  set_flag_byte(&player->field_3,0x04,false);
  player->field_4C1 = 0;
  player->field_4C5 = 0;
  player->field_7 = 0;
  PaletteSetPlayerPalette(player, _DK_palette);
  reinitialise_eye_lens(game.numfield_1B);
  if (player->victory_state != VicS_Undecided)
  {
    frontstats_initialise();
    dungeon = &(game.dungeon[my_player_number%DUNGEONS_COUNT]);
    dungeon->lvstats.player_score = 0;
    dungeon->lvstats.allow_save_score = 1;
  }
  game.field_1516FF = 0;
  return 1;
}

int count_valid_saved_games(void)
{
  struct CatalogueEntry *centry;
  int i;
  number_of_saved_games = 0;
  for (i=0; i < SAVE_SLOTS_COUNT; i++)
  {
    centry = &save_game_catalogue[i];
    if (centry->used)
      number_of_saved_games++;
  }
  return number_of_saved_games;
}

short game_save_catalogue(struct CatalogueEntry *game_catalg,int nentries)
{
  char *fname;
  //return _DK_save_game_save_catalogue(game_catalg);
  fname = prepare_file_path(FGrp_Save,save_catalogue_filename);
  return (LbFileSaveAt(fname, game_catalg, nentries*sizeof(struct CatalogueEntry)) != -1);
}

short game_catalogue_slot_disable(struct CatalogueEntry *game_catalg,unsigned int slot_idx)
{
  char *fname;
  if (slot_idx >= SAVE_SLOTS_COUNT)
    return false;
  game_catalg[slot_idx].used = false;
  game_save_catalogue(game_catalg,SAVE_SLOTS_COUNT);
  return true;
}

short save_catalogue_slot_disable(unsigned int slot_idx)
{
  return game_catalogue_slot_disable(save_game_catalogue,slot_idx);
}

short save_game_save_catalogue(void)
{
  return game_save_catalogue(save_game_catalogue,SAVE_SLOTS_COUNT);
}

short load_game_catalogue(struct CatalogueEntry *game_catalg)
{
  char *fname;
  //_DK_load_game_save_catalogue(game_catalg); return;
  fname = prepare_file_path(FGrp_Save,save_catalogue_filename);
  if (LbFileLoadAt(fname, game_catalg) == -1)
  {
    memset(game_catalg, 0, SAVE_SLOTS_COUNT*sizeof(struct CatalogueEntry));
    return false;
  }
  return true;
}

short load_game_save_catalogue(void)
{
  return load_game_catalogue(save_game_catalogue);
}

short initialise_load_game_slots(void)
{
  load_game_save_catalogue();
  return (count_valid_saved_games() > 0);
}

short save_continue_game(LevelNumber lvnum)
{
  static const char *func_name="save_continue_game";
  LevelNumber bkp_lvnum;
  char *fname;
  long fsize;
  // Update continue level number
  bkp_lvnum = get_continue_level_number();
  if (is_singleplayer_like_level(lvnum))
    set_continue_level_number(lvnum);
#if (BFDEBUG_LEVEL > 6)
    LbSyncLog("%s: Continue set to level %d (loaded is %d)\n",func_name,(int)get_continue_level_number(),(int)get_loaded_level_number());
#endif
  fname = prepare_file_path(FGrp_Save,continue_game_filename);
  fsize = LbFileSaveAt(fname, &game, sizeof(struct Game));
  // Reset original continue level number
  if (is_singleplayer_like_level(lvnum))
    set_continue_level_number(bkp_lvnum);
  return (fsize == sizeof(struct Game));
}

short read_continue_game_part(unsigned char *buf,long pos,long buf_len)
{
  static const char *func_name="read_continue_game_part";
  TbFileHandle fh;
  short result;
  char *fname;
  fname = prepare_file_path(FGrp_Save,continue_game_filename);
  if (LbFileLength(fname) != sizeof(struct Game))
  {
  #if (BFDEBUG_LEVEL > 7)
    LbSyncLog("%s: No correct .SAV file; there's no continue\n",func_name);
  #endif
    return false;
  }
  fh = LbFileOpen(fname,Lb_FILE_MODE_READ_ONLY);
  if (fh == -1)
  {
  #if (BFDEBUG_LEVEL > 7)
    LbSyncLog("%s: Can't open .SAV file; there's no continue\n",func_name);
  #endif
    return false;
  }
  LbFileSeek(fh, pos, Lb_FILE_SEEK_BEGINNING);
  result = (LbFileRead(fh, buf, buf_len) == buf_len);
  LbFileClose(fh);
  return result;
}

short continue_game_available(void)
{
  static const char *func_name="continue_game_available";
  unsigned char buf[14];
  char cmpgn_fname[CAMPAIGN_FNAME_LEN];
  long lvnum;
  long i;
//  static short continue_needs_checking_file = 1;
#if (BFDEBUG_LEVEL > 6)
    LbSyncLog("%s: Starting\n",func_name);
#endif
//  if (continue_needs_checking_file)
  {
    if (!read_continue_game_part(buf,0,14))
    {
      return false;
    }
    i = (char *)&game.campaign_fname[0] - (char *)&game.load_restart_level;
    read_continue_game_part((unsigned char *)cmpgn_fname,i,CAMPAIGN_FNAME_LEN);
    cmpgn_fname[CAMPAIGN_FNAME_LEN-1] = '\0';
    lvnum = ((struct Game *)buf)->continue_level_number;
    if (!change_campaign(cmpgn_fname))
    {
      error(func_name, 701, "Unable to load campaign");
      return false;
    }
    if (is_singleplayer_like_level(lvnum))
      set_continue_level_number(lvnum);
//    continue_needs_checking_file = 0;
  }
  lvnum = get_continue_level_number();
  if (is_singleplayer_like_level(lvnum))
  {
  #if (BFDEBUG_LEVEL > 7)
    LbSyncLog("%s: Continue to level %d is available\n",func_name,(int)lvnum);
  #endif
    return true;
  } else
  {
  #if (BFDEBUG_LEVEL > 7)
    LbSyncLog("%s: Level %d from continue file is not single player\n",func_name,(int)lvnum);
  #endif
    return false;
  }
}

short load_continue_game(void)
{
  static const char *func_name="load_continue_game";
  unsigned char buf[14];
  unsigned char bonus[12];
  char cmpgn_fname[CAMPAIGN_FNAME_LEN];
  long lvnum;
  long i;

  if (!read_continue_game_part(buf,0,14))
  {
    LbWarnLog("%s: Can't read continue game file head\n",func_name);
    return false;
  }
  i = (char *)&game.campaign_fname[0] - (char *)&game.load_restart_level;
  read_continue_game_part((unsigned char *)cmpgn_fname,i,CAMPAIGN_FNAME_LEN);
  cmpgn_fname[CAMPAIGN_FNAME_LEN-1] = '\0';
  if (!change_campaign(cmpgn_fname))
  {
    error(func_name, 731, "Unable to load campaign");
    return false;
  }
  lvnum = ((struct Game *)buf)->continue_level_number;
  if (!is_singleplayer_like_level(lvnum))
  {
    LbWarnLog("%s: Level number in continue file is incorrect\n",func_name);
    return false;
  }
  set_continue_level_number(lvnum);
  LbMemorySet(bonus,0,12);
  i = (char *)&game.bonuses_found[0] - (char *)&game.load_restart_level;
  read_continue_game_part(bonus,i,10);
  game.load_restart_level = ((struct Game *)buf)->load_restart_level;
  game.version_major = ((struct Game *)buf)->version_major;
  game.version_minor = ((struct Game *)buf)->version_minor;
  for (i=0; i < BONUS_LEVEL_STORAGE_COUNT; i++)
    game.bonuses_found[i] = bonus[i];
  LbStringCopy(game.campaign_fname,campaign.fname,sizeof(game.campaign_fname));
  update_extra_levels_visibility();
  i = (char *)&game.transfered_creature - (char *)&game.bonuses_found[0];
  game.transfered_creature.model = bonus[i];
  game.transfered_creature.explevel = bonus[i+1];
  return true;
}


/******************************************************************************/
#ifdef __cplusplus
}
#endif
