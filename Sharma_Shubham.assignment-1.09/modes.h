#ifndef MODES_H
# define MODES_H

#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>

#include "io.h"
#include "move.h"
#include "path.h"
#include "pc.h"
#include "utils.h"
#include "dungeon.h"
#include "object.h"
#include "npc.h"
#include "io.h"

void wear_item_mode(dungeon_t *d);
void take_off_item_mode(dungeon_t *d);
void drop_item_mode(dungeon_t *d);
void expunge_item_mode(dungeon_t *d);
void list_inventory_mode(dungeon_t *d);
void list_equipment_mode(dungeon_t *d);
void inspect_item_mode(dungeon_t *d);
void look_monster_mode(dungeon_t *d);
void display_monster_list(dungeon_t *d);


#endif
