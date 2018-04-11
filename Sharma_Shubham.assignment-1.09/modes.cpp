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

void wear_item_mode(dungeon_t *d)
{
  clear();
  int32_t input_value;
  int i;
  mvprintw(2, 1,  "|::::::::::::::::::::::::Wear Item::::::::::::::::::::::::|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "| %d) %-53s|", i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "| %d) No Item                                              |", i);
  }
  mvprintw(13, 1, "|:::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  mvprintw(14, 1, "|		  Choose an object to wear                 |");
  mvprintw(15, 1, "|		      Press esc to abort                   |");
  mvprintw(16, 1, "|:::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
    else if(input_value != '0' && input_value != '1' && input_value != '2' && input_value != '3' && input_value != '4' && input_value != '5'
      && input_value != '6' && input_value != '7' && input_value != '8' && input_value != '9'){
        mvprintw(17, 1, "|                      Incorrect Input                    |");
	mvprintw(18, 1, "|:::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
        continue;
      }
    else if(d->PC->wear_item(input_value - '0')){
      io_display(d);
      return;
    }
    else{
      io_display(d);
      return;
    }
  }while(1);
}

void take_off_item_mode(dungeon_t *d)
{
  int32_t input_value;
  int i;
  clear();
  mvprintw(2, 1,  "|::::::::::::::::::::::::Take off item:::::::::::::::::::::|");
  for(i = 0; i < 12; i++){
    if(d->PC->equipment_slot[i]){
      switch (i) {
        case 0:
          mvprintw(i + 3, 1, "| a) WEAPON: %-46s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 1:
          mvprintw(i + 3, 1, "| b) OFFHAND: %-45s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 2:
          mvprintw(i + 3, 1, "| c) RANGED: %-46s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 3:
          mvprintw(i + 3, 1, "| d) ARMOR: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 4:
          mvprintw(i + 3, 1, "| e) HELMET: %-46s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 5:
          mvprintw(i + 3, 1, "| f) CLOAK: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 6:
          mvprintw(i + 3, 1, "| g) GLOVES: %-46s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 7:
          mvprintw(i + 3, 1, "| h) BOOTS: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 8:
          mvprintw(i + 3, 1, "| i) AMULET: %-46s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 9:
          mvprintw(i + 3, 1, "| j) LIGHT: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 10:
          mvprintw(i + 3, 1, "| k) RING1: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 11:
          mvprintw(i + 3, 1, "| l) RING2: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
      }
    }
    else {
      switch (i) {
        case 0:
          mvprintw(i + 3, 1, "| a) WEAPON: Empty                                         |");
          break;
        case 1:
          mvprintw(i + 3, 1, "| b) OFFHAND: Empty                                        |");
          break;
        case 2:
          mvprintw(i + 3, 1, "| c) RANGED: Empty                                         |");
          break;
        case 3:
          mvprintw(i + 3, 1, "| d) ARMOR: Empty                                          |");
          break;
        case 4:
          mvprintw(i + 3, 1, "| e) HELMET: Empty                                         |");
          break;
        case 5:
          mvprintw(i + 3, 1, "| f) CLOAK: Empty                                          |");
          break;
        case 6:
          mvprintw(i + 3, 1, "| g) GLOVES: Empty                                         |");
          break;
        case 7:
          mvprintw(i + 3, 1, "| h) BOOTS: Empty                                          |");
          break;
        case 8:
          mvprintw(i + 3, 1, "| i) AMULET: Empty                                         |");
          break;
        case 9:
          mvprintw(i + 3, 1, "| j) LIGHT: Empty                                          |");
          break;
        case 10:
          mvprintw(i + 3, 1, "| k) RING1: Empty                                          |");
          break;
        case 11:
          mvprintw(i + 3, 1, "| l) RING2: Empty                                          |");
          break;
      }
    }
  }
  mvprintw(15, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  mvprintw(16, 1, "|             Choose an object to take off                 |");
  mvprintw(17, 1, "|               Press esc to abort                         |");
  mvprintw(18, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  refresh();
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
    else if(input_value != 'a' && input_value != 'b' && input_value != 'c' && input_value != 'd' && input_value != 'e' && input_value != 'f'
      && input_value != 'g' && input_value != 'h' && input_value != 'i' && input_value != 'j' && input_value != 'k' && input_value != 'l'){
        mvprintw(19, 1, "|                      Incorrect Input                     |");
	      mvprintw(20, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
        continue;
      }
    else if(d->PC->take_off_item(d->PC->equipment_slot[input_value - 'a'])){
      io_display(d);
      return;
    }
    else{
      d->PC->equipment_slot[input_value - 'a'] = NULL;
      io_display(d);
      return;
    }
  }while(1);
}

void drop_item_mode(dungeon_t *d)
{
  int32_t input_value;
  clear();
  int i;
  mvprintw(2, 1,  "|:::::::::::::::::::::::::Drop Item::::::::::::::::::::::::|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "| %c) %-54s|", '0' + i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "| %c) Empty                                                 |", '0' + i);
  }
  mvprintw(13, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  mvprintw(14, 1, "|               Choose an object to drop                   |");
  mvprintw(15, 1, "|                  Press esc to abort                      |");
  mvprintw(16, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
    else if(input_value != '0' && input_value != '1' && input_value != '2' && input_value != '3' && input_value != '4' && input_value != '5'
      && input_value != '6' && input_value != '7' && input_value != '8' && input_value != '9'){
        mvprintw(17, 1, "|                      Incorrect Input                     |");
	      mvprintw(18, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
        continue;
      }
    else if(d->PC->drop_item(d, d->PC->carry_slot[input_value - '0'])){
      io_display(d);
      return;
    }
    else{
      d->PC->carry_slot[input_value - '0'] = NULL;
      io_display(d);
      return;
    }
  }while(1);
}

void expunge_item_mode(dungeon_t *d)
{
  clear();
  int32_t input_value;
  int i;
  mvprintw(2, 1,  "|:::::::::::::::::::::::Expunge item:::::::::::::::::::::::|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "| %c) %-54s|", '0' + i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "| %c) Empty                                                 |", '0' + i);
  }
  mvprintw(13, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  mvprintw(14, 1, "|              Choose an object to expunge                 |");
  mvprintw(15, 1, "|                 Press esc to abort                       |");
  mvprintw(16, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  refresh();
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
    else if(input_value != '0' && input_value != '1' && input_value != '2' && input_value != '3' && input_value != '4' && input_value != '5'
      && input_value != '6' && input_value != '7' && input_value != '8' && input_value != '9'){
        mvprintw(17, 1, "|                      Incorrect Input                     |");
        mvprintw(18, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
        continue;
      }
    else if(d->PC->expunge_item(d->PC->carry_slot[input_value - '0'])){
      io_display(d);
      return;
    }
    else{
      d->PC->carry_slot[input_value - '0'] = NULL;
      io_display(d);
      return;
    }
  }while(1);
}

void list_inventory_mode(dungeon_t *d)
{
  clear();
  int32_t input_value;
  int i;
  mvprintw(2, 1,  "|::::::::::::::::::::::Item Inventory::::::::::::::::::::::|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "| %c) %-54s|", '0' + i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "| %c) Empty                                                 |", '0' + i);
  }
  mvprintw(13, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  mvprintw(14, 1, "|                 Press esc to abort                       |");
  mvprintw(15, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  refresh();
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
  }while(1);
}

void list_equipment_mode(dungeon_t *d)
{
  clear();
  int32_t input_value;
  int i;
  mvprintw(2, 1,  "|::::::::::::::::::::::List Equipments:::::::::::::::::::::|");
  for(i = 0; i < 12; i++){
    if(d->PC->equipment_slot[i]){
      switch (i) {
          case 0:
            mvprintw(i + 3, 1, "| a) WEAPON: %-46s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 1:
            mvprintw(i + 3, 1, "| b) OFFHAND: %-45s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 2:
            mvprintw(i + 3, 1, "| c) RANGED: %-46s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 3:
            mvprintw(i + 3, 1, "| d) ARMOR: %-47s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 4:
            mvprintw(i + 3, 1, "| e) HELMET: %-46s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 5:
            mvprintw(i + 3, 1, "| f) CLOAK: %-47s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 6:
            mvprintw(i + 3, 1, "| g) GLOVES: %-46s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 7:
            mvprintw(i + 3, 1, "| h) BOOTS: %-47s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 8:
            mvprintw(i + 3, 1, "| i) AMULET: %-46s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 9:
            mvprintw(i + 3, 1, "| j) LIGHT: %-47s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 10:
            mvprintw(i + 3, 1, "| k) RING1: %-47s|", d->PC->equipment_slot[i]->get_name());
            break;
          case 11:
            mvprintw(i + 3, 1, "| l) RING2: %-47s|", d->PC->equipment_slot[i]->get_name());
            break;
        }
    }
      else {
        switch (i) {
          case 0:
            mvprintw(i + 3, 1, "| a) WEAPON: Empty                                         |");
            break;
          case 1:
            mvprintw(i + 3, 1, "| b) OFFHAND: Empty                                        |");
            break;
          case 2:
            mvprintw(i + 3, 1, "| c) RANGED: Empty                                         |");
            break;
          case 3:
            mvprintw(i + 3, 1, "| d) ARMOR: Empty                                          |");
            break;
          case 4:
            mvprintw(i + 3, 1, "| e) HELMET: Empty                                         |");
            break;
          case 5:
            mvprintw(i + 3, 1, "| f) CLOAK: Empty                                          |");
            break;
          case 6:
            mvprintw(i + 3, 1, "| g) GLOVES: Empty                                         |");
            break;
          case 7:
            mvprintw(i + 3, 1, "| h) BOOTS: Empty                                          |");
            break;
          case 8:
            mvprintw(i + 3, 1, "| i) AMULET: Empty                                         |");
            break;
          case 9:
            mvprintw(i + 3, 1, "| j) LIGHT: Empty                                          |");
            break;
          case 10:
            mvprintw(i + 3, 1, "| k) RING1: Empty                                          |");
            break;
          case 11:
            mvprintw(i + 3, 1, "| l) RING2: Empty                                          |");
            break;
      }
    }
  }
  mvprintw(15, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  mvprintw(16, 1, "|               Press esc to abort                         |");
  mvprintw(17, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  refresh();
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
  }while(1);
}

void inspect_item_mode(dungeon_t *d)
{
  clear();
  int32_t input_value;
  int i;
  mvprintw(2, 1,  "|::::::::::::::::::::::::Inspect Item::::::::::::::::::::::|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "| %c) %-54s|", '0' + i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "| %c) Empty                                                 |", '0' + i);
  }
  mvprintw(13, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  mvprintw(14, 1, "|              Choose an item to inspect                   |");
  mvprintw(15, 1, "|                Press esc to abort                        |");
  mvprintw(16, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");

  refresh();
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
    else if(input_value != '0' && input_value != '1' && input_value != '2' && input_value != '3' && input_value != '4' && input_value != '5'
      && input_value != '6' && input_value != '7' && input_value != '8' && input_value != '9'){
        mvprintw(17, 1, "|                      Incorrect Input                     |");
        mvprintw(18, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
        continue;
      }
    else if (!d->PC->carry_slot[input_value - '0']) {
      mvprintw(17, 1, "|                     Incorrect Input                      |");
      mvprintw(18, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
      refresh();
      continue;
    }
    else{
      io_queue_message(d->PC->carry_slot[input_value - '0']->get_description());
      io_display(d);
      return;
    }
  }while(1);
}


void look_monster_mode(dungeon_t *d)
{
clear();
  pair_t dest;
  int c;
  fd_set readfs;
  struct timeval tv;

  io_display_no_fog(d);

  mvprintw(0, 0, "Choose a location");

  dest[dim_y] = d->PC->position[dim_y];
  dest[dim_x] = d->PC->position[dim_x];

  mvaddch(dest[dim_y] + 1, dest[dim_x], '*');
  refresh();

  do {
    do{
      FD_ZERO(&readfs);
      FD_SET(STDIN_FILENO, &readfs);

      tv.tv_sec = 0;
      tv.tv_usec = 125000; /* An eigth of a second */

      io_redisplay_non_terrain(d, dest);
    } while (!select(STDIN_FILENO + 1, &readfs, NULL, NULL, &tv));
    /* Can simply draw the terrain when we move the cursor away, *
     * because if it is a character or object, the refresh       *
     * function will fix it for us.                              */
    switch (mappair(dest)) {
    case ter_wall:
    case ter_wall_immutable:
    case ter_unknown:
      mvaddch(dest[dim_y] + 1, dest[dim_x], ' ');
      break;
    case ter_floor:
    case ter_floor_room:
      mvaddch(dest[dim_y] + 1, dest[dim_x], '.');
      break;
    case ter_floor_hall:
      mvaddch(dest[dim_y] + 1, dest[dim_x], '#');
      break;
    case ter_debug:
      mvaddch(dest[dim_y] + 1, dest[dim_x], '*');
      break;
    case ter_stairs_up:
      mvaddch(dest[dim_y] + 1, dest[dim_x], '<');
      break;
    case ter_stairs_down:
      mvaddch(dest[dim_y] + 1, dest[dim_x], '>');
      break;
    default:
 /* Use zero as an error symbol, since it stands out somewhat, and it's *
  * not otherwise used.                                                 */
      mvaddch(dest[dim_y] + 1, dest[dim_x], '0');
    }
    switch ((c = getch())) {
    case '7':
    case 'y':
    case KEY_HOME:
      if (dest[dim_y] != 1) {
        dest[dim_y]--;
      }
      if (dest[dim_x] != 1) {
        dest[dim_x]--;
      }
      break;
    case '8':
    case 'k':
    case KEY_UP:
      if (dest[dim_y] != 1) {
        dest[dim_y]--;
      }
      break;
    case '9':
    case 'u':
    case KEY_PPAGE:
      if (dest[dim_y] != 1) {
        dest[dim_y]--;
      }
      if (dest[dim_x] != DUNGEON_X - 2) {
        dest[dim_x]++;
      }
      break;
    case '6':
    case 'l':
    case KEY_RIGHT:
      if (dest[dim_x] != DUNGEON_X - 2) {
        dest[dim_x]++;
      }
      break;
    case '3':
    case 'n':
    case KEY_NPAGE:
      if (dest[dim_y] != DUNGEON_Y - 2) {
        dest[dim_y]++;
      }
      if (dest[dim_x] != DUNGEON_X - 2) {
        dest[dim_x]++;
      }
      break;
    case '2':
    case 'j':
    case KEY_DOWN:
      if (dest[dim_y] != DUNGEON_Y - 2) {
        dest[dim_y]++;
      }
      break;
    case '1':
    case 'b':
    case KEY_END:
      if (dest[dim_y] != DUNGEON_Y - 2) {
        dest[dim_y]++;
      }
      if (dest[dim_x] != 1) {
        dest[dim_x]--;
      }
      break;
    case '4':
    case 'h':
    case KEY_LEFT:
      if (dest[dim_x] != 1) {
        dest[dim_x]--;
      }
      break;
    }
  } while (c != 'L');
  
  pair_t pair;
  pair[dim_y] = dest[dim_y];
  pair[dim_x] = dest[dim_x];
  
  if(c == 'L' && charpair(pair)->symbol != '@')
  {
    std::string description;
    for(int i = 0; (unsigned)i < d->monster_descriptions.size(); i++)
    {
      if(charpair(pair)->name == d->monster_descriptions[i].name)
      {
	description = d->monster_descriptions[i].get_description();
      }
    }
    clear();
    refresh();
    mvprintw(0, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
    mvprintw(1, 1, "|%-58s|", " Press escape to exit");
    mvprintw(2, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
    mvprintw(3, 1, "|Name: %-52s|", charpair(pair)->name);
    mvprintw(5, 1, "Description:\n %s", description.c_str());
    
    refresh();
    while(getch()!= 27);
  }
  io_display(d);
}
