#include "move.h"

#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#include "dungeon.h"
#include "heap.h"
#include "move.h"
#include "npc.h"
#include "pc.h"
#include "character.h"
#include "utils.h"
#include "path.h"
#include "io.h"

void do_combat(dungeon_t *d, character *atk, character *def)
{
  // int can_see_atk, can_see_def;
  // const char *organs[] = {
  //   "liver",                   /*  0 */
  //   "pancreas",                /*  1 */
  //   "heart",                   /*  2 */
  //   "eye",                     /*  3 */
  //   "arm",                     /*  4 */
  //   "leg",                     /*  5 */
  //   "intestines",              /*  6 */
  //   "gall bladder",            /*  7 */
  //   "lungs",                   /*  8 */
  //   "hand",                    /*  9 */
  //   "foot",                    /* 10 */
  //   "spinal cord",             /* 11 */
  //   "pituitary gland",         /* 12 */
  //   "thyroid",                 /* 13 */
  //   "tongue",                  /* 14 */
  //   "bladder",                 /* 15 */
  //   "diaphram",                /* 16 */
  //   "stomach",                 /* 17 */
  //   "pharynx",                 /* 18 */
  //   "esophagus",               /* 19 */
  //   "trachea",                 /* 20 */
  //   "urethra",                 /* 21 */
  //   "spleen",                  /* 22 */
  //   "ganglia",                 /* 23 */
  //   "ear",                     /* 24 */
  //   "subcutaneous tissue"      /* 25 */
  //   "cerebellum",              /* 26 */ /* Brain parts begin here */
  //   "hippocampus",             /* 27 */
  //   "frontal lobe",            /* 28 */
  //   "brain",                   /* 29 */
  // };
  // int part;
  //
  // if (def->alive) {
  //   def->alive = 0;
  //   charpair(def->position) = NULL;
  //
  //   if (def != d->PC) {
  //     d->num_monsters--;
  //   } else {
  //     if ((part = rand() % (sizeof (organs) / sizeof (organs[0]))) < 26) {
  //       io_queue_message("As the %c eats your %s, "
  //                        "you wonder if there is an afterlife.",
  //                        atk->symbol, organs[part]);
  //     } else {
  //       io_queue_message("Your last thoughts fade away as "
  //                        "the %c eats your %s...",
  //                        atk->symbol, organs[part]);
  //     }
  //     /* Queue an empty message, otherwise the game will not pause for *
  //      * player to see above.                                          */
  //     io_queue_message("");
  //   }
  //   atk->kills[kill_direct]++;
  //   atk->kills[kill_avenged] += (def->kills[kill_direct] +
  //                                 def->kills[kill_avenged]);
  // }
  //
  // if (atk == d->PC) {
  //   io_queue_message("You smite the %c!", def->symbol);
  // }
  //
  // can_see_atk = can_see(d, character_get_pos(d->PC),
  //                       character_get_pos(atk), 1, 0);
  // can_see_def = can_see(d, character_get_pos(d->PC),
  //                       character_get_pos(def), 1, 0);
  //
  // if (atk != d->PC && def != d->PC) {
  //   if (can_see_atk && !can_see_def) {
  //     io_queue_message("The %c callously murders some poor, "
  //                      "defenseless creature.", atk->symbol);
  //   }
  //   if (can_see_def && !can_see_atk) {
  //     io_queue_message("Something kills the helpless %c.", def->symbol);
  //   }
  //   if (can_see_atk && can_see_def) {
  //     io_queue_message("You watch in abject horror as the %c "
  //                      "gruesomely murders the %c!", atk->symbol, def->symbol);
  //   }
  // }

  character_die(def);
  if (def != d->pc) {
    d->num_monsters--;
  }
}

void move_character(dungeon_t *d, character *c, pair_t next)
{
  if (charpair(next) &&
      ((next[dim_y] != character_get_y(c)) ||
       (next[dim_x] != character_get_x(c)))) {
    do_combat(d, c, charpair(next));
  }
  /* No character in new position. */

  d->charmap[character_get_y(c)][character_get_x(c)] = NULL;
  character_set_y(c, next[dim_y]);
  character_set_x(c, next[dim_x]);
  d->charmap[character_get_y(c)][character_get_x(c)] = c;

  if (c == d->pc) {
    pc_reset_visibility(c);
    pc_observe_terrain(c, d);
  }
}

void do_moves(dungeon_t *d)
{
  pair_t next;
  character *c;
  //event_t *e;

  /* Remove the PC when it is PC turn.  Replace on next call.  This allows *
   * use to completely uninit the heap when generating a new level without *
   * worrying about deleting the PC.                                       */

  if (pc_is_alive(d)) {
    heap_insert(&d->next_turn, d->pc);
  }

  while (pc_is_alive(d) &&
        ((c = ((character *) heap_remove_min(&d->next_turn))) != d->pc)) {
    if (!character_is_alive(c)) {
      if (d->charmap[character_get_y(c)][character_get_x(c)] == c) {
        d->charmap[character_get_y(c)][character_get_x(c)] = NULL;
      }
      if (c != d->pc) {
        character_delete(c);
      }
      continue;
    }

    character_next_turn(c);
    npc_next_pos(d, c, next);
    move_character(d, c, next);
    heap_insert(&d->next_turn, c);
  }
  io_display_no_fog(d);
  if (pc_is_alive(d) && c == d->pc) {
    character_next_turn(c);
    io_handle_input(d);
  }
}

void dir_nearest_wall(dungeon_t *d, character *c, pair_t dir)
{
  dir[dim_x] = dir[dim_y] = 0;

  if (character_get_x(c) != 1 && character_get_x(c) != DUNGEON_X - 2) {
    dir[dim_x] = (character_get_x(c) > DUNGEON_X - character_get_x(c) ? 1 : -1);
  }
  if (character_get_y(c) != 1 && character_get_y(c) != DUNGEON_Y - 2) {
    dir[dim_y] = (character_get_y(c) > DUNGEON_Y - character_get_y(c) ? 1 : -1);
  }
}

uint32_t in_corner(dungeon_t *d, character *c)
{
  uint32_t num_immutable;

  num_immutable = 0;

  num_immutable += (mapxy(character_get_x(c) - 1,
                          character_get_y(c)    ) == ter_wall_immutable);
  num_immutable += (mapxy(character_get_x(c) + 1,
                          character_get_y(c)    ) == ter_wall_immutable);
  num_immutable += (mapxy(character_get_x(c)    ,
                          character_get_y(c) - 1) == ter_wall_immutable);
  num_immutable += (mapxy(character_get_x(c)    ,
                          character_get_y(c) + 1) == ter_wall_immutable);

  return num_immutable > 1;
}

static void new_dungeon_level(dungeon_t *d, uint32_t dir)
{
  /* Eventually up and down will be independantly meaningful. *
   * For now, simply generate a new dungeon.                  */

  switch (dir) {
  case '<':
  case '>':
    new_dungeon(d);
    break;
  default:
    break;
  }
}


uint32_t move_pc(dungeon_t *d, uint32_t dir)
{
  pair_t next;
  uint32_t was_stairs = 0;

  next[dim_y] = character_get_y(d->pc);
  next[dim_x] = character_get_x(d->pc);

  switch (dir) {
  case 1:
  case 2:
  case 3:
    next[dim_y]++;
    break;
  case 4:
  case 5:
  case 6:
    break;
  case 7:
  case 8:
  case 9:
    next[dim_y]--;
    break;
  }
  switch (dir) {
  case 1:
  case 4:
  case 7:
    next[dim_x]--;
    break;
  case 2:
  case 5:
  case 8:
    break;
  case 3:
  case 6:
  case 9:
    next[dim_x]++;
    break;
  case '<':
    if (mappair(character_get_pos(d->pc)) == ter_stairs_up) {
      was_stairs = 1;
      new_dungeon_level(d, '<');
    }
    break;
  case '>':
    if (mappair(character_get_pos(d->pc)) == ter_stairs_down) {
      was_stairs = 1;
      new_dungeon_level(d, '>');
    }
    break;
  }

  if (was_stairs) {
    return 0;
  }

  if ((dir != '>') && (dir != '<') && (mappair(next) >= ter_floor)) {
    move_character(d, d->pc, next);
    dijkstra(d);
    dijkstra_tunnel(d);

    return 0;
  }

  return 1;
}
