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
  mvprintw(15, 1, "|		      Enter esc to abort                   |");
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
  mvprintw(2, 1,  "|::::::::::::::::::::::::Take off item:::::::::::::::::::::|");
  for(i = 0; i < 12; i++){
    if(d->PC->equipment_slot[i]){
      switch (i) {
        case 0:
          mvprintw(i + 3, 1, "|a) WEAPON: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 1:
          mvprintw(i + 3, 1, "|b) OFFHAND: %-46s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 2:
          mvprintw(i + 3, 1, "|c) RANGED: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 3:
          mvprintw(i + 3, 1, "|d) ARMOR: %-48s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 4:
          mvprintw(i + 3, 1, "|e) HELMET: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 5:
          mvprintw(i + 3, 1, "|f) CLOAK: %-48s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 6:
          mvprintw(i + 3, 1, "|g) GLOVES: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 7:
          mvprintw(i + 3, 1, "|h) BOOTS: %-48s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 8:
          mvprintw(i + 3, 1, "|i) AMULET: %-47s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 9:
          mvprintw(i + 3, 1, "|j) LIGHT: %-48s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 10:
          mvprintw(i + 3, 1, "|k) RING1: %-48s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 11:
          mvprintw(i + 3, 1, "|l RING2: %-48s|", d->PC->equipment_slot[i]->get_name());
          break;
      }
    }
    else {
      switch (i) {
        case 0:
          mvprintw(i + 3, 1, "|a. WEAPON: Empty                                          |");
          break;
        case 1:
          mvprintw(i + 3, 1, "|b. OFFHAND: Empty                                         |");
          break;
        case 2:
          mvprintw(i + 3, 1, "|c. RANGED: Empty                                          |");
          break;
        case 3:
          mvprintw(i + 3, 1, "|d. ARMOR: Empty                                           |");
          break;
        case 4:
          mvprintw(i + 3, 1, "|e. HELMET: Empty                                          |");
          break;
        case 5:
          mvprintw(i + 3, 1, "|f. CLOAK: Empty                                           |");
          break;
        case 6:
          mvprintw(i + 3, 1, "|g. GLOVES: Empty                                          |");
          break;
        case 7:
          mvprintw(i + 3, 1, "|h. BOOTS: Empty                                           |");
          break;
        case 8:
          mvprintw(i + 3, 1, "|i. AMULET: Empty                                          |");
          break;
        case 9:
          mvprintw(i + 3, 1, "|j. LIGHT: Empty                                           |");
          break;
        case 10:
          mvprintw(i + 3, 1, "|k. RING1: Empty                                           |");
          break;
        case 11:
          mvprintw(i + 3, 1, "|l. RING2: Empty                                           |");
          break;
      }
    }
  }
  mvprintw(15, 1, "|::::::::::::::::::::::::::::::::::::::::::::::::::::::::::|");
  mvprintw(16, 1, "|             Choose an object to take off                 |");
  mvprintw(17, 1, "|               Enter esc to abort                         |");
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
  int i;
  mvprintw(2, 1,  "|-------------------Drop Mode--------------------|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "|%c. %-45s|", '0' + i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "|%c. Empty                                        |", '0' + i);
  }
  mvprintw(13, 1, "|------------------------------------------------|");
  mvprintw(14, 1, "|------------------------------------------------|");
  mvprintw(15, 1, "|Choose an object to drop                        |");
  mvprintw(16, 1, "|Enter esc to abort                              |");
  mvprintw(17, 1, "|------------------------------------------------|");
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
    else if(input_value != '0' && input_value != '1' && input_value != '2' && input_value != '3' && input_value != '4' && input_value != '5'
      && input_value != '6' && input_value != '7' && input_value != '8' && input_value != '9'){
        mvprintw(18, 1, "Wrong number!");
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
  int32_t input_value;
  int i;
  mvprintw(2, 1,  "|------------------Expunge Mode------------------|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "|%c. %-45s|", '0' + i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "|%c. Empty                                        |", '0' + i);
  }
  mvprintw(13, 1, "|------------------------------------------------|");
  mvprintw(14, 1, "|------------------------------------------------|");
  mvprintw(15, 1, "|Choose an object to expunge                     |");
  mvprintw(16, 1, "|Enter esc to abort                              |");
  mvprintw(17, 1, "|------------------------------------------------|");
  refresh();
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
    else if(input_value != '0' && input_value != '1' && input_value != '2' && input_value != '3' && input_value != '4' && input_value != '5'
      && input_value != '6' && input_value != '7' && input_value != '8' && input_value != '9'){
        mvprintw(18, 1, "Wrong number!");
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
  int32_t input_value;
  int i;
  mvprintw(2, 1,  "|-----------------Inventory Mode-----------------|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "|%c. %-45s|", '0' + i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "|%c. Empty                                        |", '0' + i);
  }
  mvprintw(13, 1, "|------------------------------------------------|");
  mvprintw(14, 1, "|------------------------------------------------|");
  mvprintw(15, 1, "|------------------------------------------------|");
  mvprintw(16, 1, "|Enter esc to abort                              |");
  mvprintw(17, 1, "|------------------------------------------------|");
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
  int32_t input_value;
  int i;
  mvprintw(2, 1, "|-----------------Equipment Mode-----------------|");
  for(i = 0; i < 12; i++){
    if(d->PC->equipment_slot[i]){
      switch (i) {
        case 0:
          mvprintw(i + 3, 1, "|a. WEAPON: %-37s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 1:
          mvprintw(i + 3, 1, "|b. OFFHAND: %-36s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 2:
          mvprintw(i + 3, 1, "|c. RANGED: %-37s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 3:
          mvprintw(i + 3, 1, "|d. ARMOR: %-38s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 4:
          mvprintw(i + 3, 1, "|e. HELMET: %-37s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 5:
          mvprintw(i + 3, 1, "|f. CLOAK: %-38s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 6:
          mvprintw(i + 3, 1, "|g. GLOVES: %-37s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 7:
          mvprintw(i + 3, 1, "|h. BOOTS: %-38s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 8:
          mvprintw(i + 3, 1, "|i. AMULET: %-37s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 9:
          mvprintw(i + 3, 1, "|j. LIGHT: %-38s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 10:
          mvprintw(i + 3, 1, "|k. RING1: %-38s|", d->PC->equipment_slot[i]->get_name());
          break;
        case 11:
          mvprintw(i + 3, 1, "|l. RING2: %-38s|", d->PC->equipment_slot[i]->get_name());
          break;
      }
    }
    else {
      switch (i) {
        case 0:
          mvprintw(i + 3, 1, "|a. WEAPON: Empty                                |");
          break;
        case 1:
          mvprintw(i + 3, 1, "|b. OFFHAND: Empty                               |");
          break;
        case 2:
          mvprintw(i + 3, 1, "|c. RANGED: Empty                                |");
          break;
        case 3:
          mvprintw(i + 3, 1, "|d. ARMOR: Empty                                 |");
          break;
        case 4:
          mvprintw(i + 3, 1, "|e. HELMET: Empty                                |");
          break;
        case 5:
          mvprintw(i + 3, 1, "|f. CLOAK: Empty                                 |");
          break;
        case 6:
          mvprintw(i + 3, 1, "|g. GLOVES: Empty                                |");
          break;
        case 7:
          mvprintw(i + 3, 1, "|h. BOOTS: Empty                                 |");
          break;
        case 8:
          mvprintw(i + 3, 1, "|i. AMULET: Empty                                |");
          break;
        case 9:
          mvprintw(i + 3, 1, "|j. LIGHT: Empty                                 |");
          break;
        case 10:
          mvprintw(i + 3, 1, "|k. RING1: Empty                                 |");
          break;
        case 11:
          mvprintw(i + 3, 1, "|l. RING2: Empty                                 |");
          break;
      }
    }
  }
  mvprintw(15, 1, "|------------------------------------------------|");
  mvprintw(16, 1, "|------------------------------------------------|");
  mvprintw(17, 1, "|------------------------------------------------|");
  mvprintw(18, 1, "|Enter esc to abort                              |");
  mvprintw(19, 1, "|------------------------------------------------|");
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
  int32_t input_value;
  int i;
  mvprintw(2, 1,  "|------------------Inspect Mode------------------|");
  for(i = 0; i < 10; i++){
    if(d->PC->carry_slot[i]){
      mvprintw(i + 3, 1, "|%c. %-45s|", '0' + i, d->PC->carry_slot[i]->get_name());
    }
    else mvprintw(i + 3, 1, "|%c. Empty                                        |", '0' + i);
  }
  mvprintw(13, 1, "|------------------------------------------------|");
  mvprintw(14, 1, "|------------------------------------------------|");
  mvprintw(15, 1, "|Choose an object to inspect                     |");
  mvprintw(16, 1, "|Enter esc to abort                              |");
  mvprintw(17, 1, "|------------------------------------------------|");
  refresh();
  do {
    if ((input_value = getch()) == 27 /* ESC */) {
      io_display(d);
      return;
    }
    else if(input_value != '0' && input_value != '1' && input_value != '2' && input_value != '3' && input_value != '4' && input_value != '5'
      && input_value != '6' && input_value != '7' && input_value != '8' && input_value != '9'){
        mvprintw(18, 1, "Wrong number!");
        continue;
      }
    else if (!d->PC->carry_slot[input_value - '0']) {
      mvprintw(18, 1, "Empty slot!");
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
  
}

void display_monster_list(dungeon_t *d)
{
  mvprintw(11, 33, " HP:    XXXXX ");
  mvprintw(12, 33, " Speed: XXXXX ");
  mvprintw(14, 27, " Hit any input_value to continue. ");
  refresh();
  getch();
}
