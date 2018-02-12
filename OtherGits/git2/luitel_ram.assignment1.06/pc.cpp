#include <stdlib.h>

#include "string.h"

#include "dungeon.h"
#include "pc.h"
#include "utils.h"
#include "move.h"
#include "path.h"
#include "io.h"


/**void pc_delete(pc_t *pc)
{
  if (pc) {
    free(pc);
  }
}
*/

uint32_t pc_is_alive(dungeon_t *d)
{
  return d->thepc->alive;
}

void place_pc(dungeon_t *d)
{
  d->thepc->position[dim_y] = rand_range(d->rooms->position[dim_y],
                                     (d->rooms->position[dim_y] +
                                      d->rooms->size[dim_y] - 1));
  d->thepc->position[dim_x] = rand_range(d->rooms->position[dim_x],
                                     (d->rooms->position[dim_x] +
                                      d->rooms->size[dim_x] - 1));
   
  pc_inititial_terrain(d->thepc);
  notice_pc_terrain(d->thepc, d);
  
}

void config_pc(dungeon_t *d)
{
  d->thepc = new pc;

  d->thepc->symbol = '@';

  place_pc(d);

 d->thepc->speed = PC_SPEED;
  d->thepc->alive = 1;
  d->thepc->sequence_number = 0;

  d->character_map[d->thepc->position[dim_y]][d->thepc->position[dim_x]] = d->thepc;

  dijkstra(d);
  dijkstra_tunnel(d);
}

uint32_t pc_next_pos(dungeon_t *d, pair_t dir)
{

  dir[dim_y] = dir[dim_x] = 0;

  if (in_corner(d, d->thepc)) {
   	dir[dim_y] = (mapxy(d->thepc->position[dim_x],
                        d->thepc->position[dim_y] - 1) ==
                  ter_wall_immutable) ? 1 : -1;
  	} else {
   		 dir_nearest_wall(d, d->thepc, dir);
  	}

  	return 0;
}


void pc_learn_terrain(pc *p, pair_t pos, terrain_type_t ter)
{
  p->known_terrain[pos[dim_y]][pos[dim_x]] = ter;
  p->visible[pos[dim_y]][pos[dim_x]] = 1;
}

void reset_pc_visibility(pc *p)
{
  uint32_t y, x;

  for (y = 0; y < DUNGEON_Y; y++) {
    for (x = 0; x < DUNGEON_X; x++) {
      p->visible[y][x] = 0;
    }
  }
}

terrain_type_t pc_learned_terrain(pc *p, int8_t y, int8_t x)
{
  return p->known_terrain[y][x];
}

void pc_inititial_terrain(pc *p)
{
  uint32_t y, x;

  for (y = 0; y < DUNGEON_Y; y++) {
    for (x = 0; x < DUNGEON_X; x++) {
      p->known_terrain[y][x] = ter_unknown;
      p->visible[y][x] = 0;
    }
  }
}

void notice_pc_terrain(pc *p, dungeon_t *d)
{
  pair_t where;
  int8_t y_min, y_max, x_min, x_max;

  y_min = p->position[dim_y] - PC_VISUAL_RANGE;
  if (y_min < 0) {
    y_min = 0;
  }
  y_max = p->position[dim_y] + PC_VISUAL_RANGE;
  if (y_max > DUNGEON_Y - 1) {
    y_max = DUNGEON_Y - 1;
  }
  x_min = p->position[dim_x] - PC_VISUAL_RANGE;
  if (x_min < 0) {
    x_min = 0;
  }
  x_max = p->position[dim_x] + PC_VISUAL_RANGE;
  if (x_max > DUNGEON_X - 1) {
    x_max = DUNGEON_X - 1;
  }

  for (where[dim_y] = y_min; where[dim_y] <= y_max; where[dim_y]++) {
    where[dim_x] = x_min;
    can_see(d, p->position, where, 1);
    where[dim_x] = x_max;
    can_see(d, p->position, where, 1);
  }
 
  for (where[dim_x] = x_min - 1; where[dim_x] <= x_max - 1; where[dim_x]++) {
    where[dim_y] = y_min;
    can_see(d, p->position, where, 1);
    where[dim_y] = y_max;
    can_see(d, p->position, where, 1);
  }       
}

int32_t pc_is_illuminated(pc *p, int8_t y, int8_t x)
{
  return p->visible[y][x];
}



uint32_t pc_in_room(dungeon_t *d, uint32_t room)
{
  if ((room < d->num_rooms)                                     &&
      (d->thepc->position[dim_x] >= d->rooms[room].position[dim_x]) &&
      (d->thepc->position[dim_x] < (d->rooms[room].position[dim_x] +
                                d->rooms[room].size[dim_x]))    &&
      (d->thepc->position[dim_y] >= d->rooms[room].position[dim_y]) &&
      (d->thepc->position[dim_y] < (d->rooms[room].position[dim_y] +
                               d->rooms[room].size[dim_y]))) {
    return 1;
  }

  return 0;
}





