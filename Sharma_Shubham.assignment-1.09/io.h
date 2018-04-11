#ifndef IO_H
# define IO_H

#include "io.h"
#include "move.h"
#include "path.h"
#include "pc.h"
#include "utils.h"
#include "dungeon.h"
#include "object.h"
#include "npc.h"
#include "modes.h"
#include "character.h"

typedef struct dungeon dungeon_t;

void io_init_terminal(void);
void io_reset_terminal(void);
void io_display(dungeon_t *d);
void io_display_no_fog(dungeon *d);
void io_redisplay_non_terrain(dungeon *d, pair_t cursor);
void io_handle_input(dungeon_t *d);
void io_queue_message(const char *format, ...);

#endif
