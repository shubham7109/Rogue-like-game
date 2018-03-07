#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <ncurses.h>
/* Very slow seed: 686846853 */
#include "path.h"
#include "dungeon.h"
#include "pc.h"
#include "npc.h"
#include "move.h"


const char *victory =
  "\n                                       o\n"
  "                                      $\"\"$o\n"
  "                                     $\"  $$\n"
  "                                      $$$$\n"
  "                                      o \"$o\n"
  "                                     o\"  \"$\n"
  "                oo\"$$$\"  oo$\"$ooo   o$    \"$    ooo\"$oo  $$$\"o\n"
  "   o o o o    oo\"  o\"      \"o    $$o$\"     o o$\"\"  o$      \"$  "
  "\"oo   o o o o\n"
  "   \"$o   \"\"$$$\"   $$         $      \"   o   \"\"    o\"         $"
  "   \"o$$\"    o$$\n"
  "     \"\"o       o  $          $\"       $$$$$       o          $  ooo"
  "     o\"\"\n"
  "        \"o   $$$$o $o       o$        $$$$$\"       $o        \" $$$$"
  "   o\"\n"
  "         \"\"o $$$$o  oo o  o$\"         $$$$$\"        \"o o o o\"  "
  "\"$$$  $\n"
  "           \"\" \"$\"     \"\"\"\"\"            \"\"$\"            \""
  "\"\"      \"\"\" \"\n"
  "            \"oooooooooooooooooooooooooooooooooooooooooooooooooooooo$\n"
  "             \"$$$$\"$$$$\" $$$$$$$\"$$$$$$ \" \"$$$$$\"$$$$$$\"  $$$\""
  "\"$$$$\n"
  "              $$$oo$$$$   $$$$$$o$$$$$$o\" $$$$$$$$$$$$$$ o$$$$o$$$\"\n"
  "              $\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\""
  "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"$\n"
  "              $\"                                                 \"$\n"
  "              $\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\"$\""
  "$\"$\"$\"$\"$\"$\"$\"$\n"
  "                                   You win!\n\n";

const char *tombstone =
  "\n\n                /\"\"\"\"\"/\"\"\"\"\"\"\".\n"
  "               /     /         \\             __\n"
  "              /     /           \\            ||\n"
  "             /____ /   Rest in   \\           ||\n"
  "            |     |    Pieces     |          ||\n"
  "            |     |               |          ||\n"
  "            |     |   A. Luser    |          ||\n"
  "            |     |               |          ||\n"
  "            |     |     * *   * * |         _||_\n"
  "            |     |     *\\/* *\\/* |        | TT |\n"
  "            |     |     *_\\_  /   ...\"\"\"\"\"\"| |"
  "| |.\"\"....\"\"\"\"\"\"\"\".\"\"\n"
  "            |     |         \\/..\"\"\"\"\"...\"\"\""
  "\\ || /.\"\"\".......\"\"\"\"...\n"
  "            |     |....\"\"\"\"\"\"\"........\"\"\"\"\""
  "\"^^^^\".......\"\"\"\"\"\"\"\"..\"\n"
  "            |......\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"......"
  "..\"\"\"\"\"....\"\"\"\"\"..\"\"...\"\"\".\n\n"
  "            You're dead.  Better luck in the next life.\n\n\n";

// Global variables for assignment 1.05
  bool quit = false;
  bool monsterListMode =false;
  bool moveMonsterCheck = true;
  int scrollFactor = 0; //Positive is down / Negative is Up
  WINDOW *my_win;

void usage(char *name)
{
  fprintf(stderr,
          "Usage: %s [-r|--rand <seed>] [-l|--load [<file>]]\n"
          "          [-s|--save [<file>]] [-i|--image <pgm file>]\n"
          "          [-p|--pc <y> <x>] [-n|--nummon <count>]\n",
          name);

          // Ends and clears the dungeon
          clear();
          endwin();
  exit(-1);
}

void render_ncurses_dungeon(dungeon_t *d){

  pair_t p;
  // Clears the dungeon
  for (p[dim_y] = 0; p[dim_y] < DUNGEON_Y; p[dim_y]++) {
    for (p[dim_x] = 0; p[dim_x] < DUNGEON_X; p[dim_x]++) {
      int y, x;            // to store where you are
      getyx(stdscr, y, x); // save current pos
      move(y, 0);          // move to begining of line
      clrtoeol();          // clear line
      move(y, x);          // move back to where you were
    }
  }
  for (p[dim_y] = 0; p[dim_y] < DUNGEON_Y; p[dim_y]++) {
    for (p[dim_x] = 0; p[dim_x] < DUNGEON_X; p[dim_x]++) {
      if (charpair(p)) {
        mvprintw(p[dim_y], p[dim_x],"%c",charpair(p)->symbol);
      } else {
        switch (mappair(p)) {
        case ter_wall:
        case ter_wall_immutable:
          mvprintw(p[dim_y], p[dim_x]," ");
          break;
        case ter_floor:
        case ter_floor_room:
          mvprintw(p[dim_y], p[dim_x],".");
          break;
        case ter_floor_hall:
          mvprintw(p[dim_y], p[dim_x],"#");
          break;
        case ter_down_staircase:
          mvprintw(p[dim_y], p[dim_x],">");
          break;
        case ter_up_staircase:
          mvprintw(p[dim_y], p[dim_x],"<");
          break;
        case ter_debug:
          mvprintw(p[dim_y], p[dim_x],"*");
          //fprintf(stderr, "Debug character at %d, %d\n", p[dim_y], p[dim_x]);
          break;
        }
      }
    }
    mvprintw(p[dim_y], p[dim_x],"\n");
  }
  mvprintw(p[dim_y], p[dim_x],"\n");
}

// Picks a number between the bounds with the bounds included in the range
int pickAnumber(int min, int max){

	// This function was inspired from a code on StackOverflow
	int r;
    int range = 1 + max - min;
	int buckets = RAND_MAX / range;
	int limit = buckets * range;
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}


void gen_staircase(dungeon_t *d){
  int num_stairs = pickAnumber(1,10);
  pair_t pair_stair;
  int i=0;
  // generate upstairs
  for(i=0; i< num_stairs; i++){

    int pickRoom = pickAnumber(1 , (d->num_rooms-1));
    int min_x = d->rooms[pickRoom].position[dim_x];
    int max_x = min_x + d->rooms[pickRoom].size[dim_x] - 1;
    int xpos = pickAnumber(min_x,max_x);

    int min_y = d->rooms[pickRoom].position[dim_y];
    int max_y = min_y + d->rooms[pickRoom].size[dim_y] - 1;
    int ypos = pickAnumber(min_y,max_y);

    pair_stair[dim_x] = xpos;
    pair_stair[dim_y] = ypos;
    mappair(pair_stair) = ter_up_staircase;

  }
  // generate downstairs
  for(i=0; i< num_stairs; i++){

    int pickRoom = pickAnumber(1 , (d->num_rooms-1));
    int min_x = d->rooms[pickRoom].position[dim_x];
    int max_x = min_x + d->rooms[pickRoom].size[dim_x] - 1;
    int xpos = pickAnumber(min_x,max_x);

    int min_y = d->rooms[pickRoom].position[dim_y];
    int max_y = min_y + d->rooms[pickRoom].size[dim_y] - 1;
    int ypos = pickAnumber(min_y,max_y);

    pair_stair[dim_x] = xpos;
    pair_stair[dim_y] = ypos;
    mappair(pair_stair) = ter_down_staircase;

  }

}
void generate_new_dungeon(dungeon_t *d) // Used when going up or down a staircase
{
  delete_dungeon(d);
  init_dungeon(d);
  gen_dungeon(d);
  config_pc(d);
  gen_monsters(d);
  gen_staircase(d);
}
void printMonsters(dungeon_t *d){
  clear();
  pair_t p;
  int count =0;
  int xDisplacement=0;
  int yDisplacement=0;
  wmove(my_win, 0, 0);
  clear();
  for (p[dim_y] = 0; p[dim_y] < DUNGEON_Y; p[dim_y]++) {
    for (p[dim_x] = 0; p[dim_x] < DUNGEON_X; p[dim_x]++) {
      if (charpair(p) && charpair(p)->symbol != '@') {
        yDisplacement = p[dim_y] - d->pc.position[dim_y];
        xDisplacement = p[dim_x] - d->pc.position[dim_x];

        if(yDisplacement>= 0 && xDisplacement >= 0)
          mvprintw(count+scrollFactor, 0," '%c' is %d South and %d East",charpair(p)->symbol,yDisplacement,xDisplacement);

        else if(yDisplacement> 0 && xDisplacement < 0)
          mvprintw(count+scrollFactor, 0," '%c' is %d South and %d West",charpair(p)->symbol,yDisplacement,xDisplacement-xDisplacement-xDisplacement);

        else if(yDisplacement< 0 && xDisplacement > 0)
            mvprintw(count+scrollFactor, 0," '%c' is %d North and %d East",charpair(p)->symbol,yDisplacement-yDisplacement-yDisplacement,xDisplacement);

        else if(yDisplacement< 0 && xDisplacement < 0)
          mvprintw(count+scrollFactor, 0," '%c' is %d North and %d West",charpair(p)->symbol,yDisplacement-yDisplacement-yDisplacement,xDisplacement-xDisplacement-xDisplacement);

        count++;
      }
    }
  }
}
// Displays the list of monsters below the rendered dungeon.
void displayMonstersList(dungeon_t *d){

  printMonsters(d);
  //int mx = 0;
  //int my = 0;
  //getmaxyx(stdscr, mx, my);

  while (1){
    // Escape
    int value = getch();
    if(value == 27){
      monsterListMode =  false;
      moveMonsterCheck = false;
      clear();
      break;
    }
    if(value == 113){
      quit = true;
      //mvprintw(0,0,"Quit the game");
      clear();
      break;
    }
    if(value == KEY_UP){
      if(scrollFactor < 0)
        scrollFactor++;
      printMonsters(d);
    }
    if(value == KEY_DOWN){
      scrollFactor--;
      printMonsters(d);
    }

  }
}

void clearMonsterList(dungeon_t *d){
  int i=0;
  for(i=0; i<(d->num_monsters+5); i++){ // +5 just to be safe
    move(i+21, 0);          // move to begining of line
    clrtoeol();          // clear line
  }
}

void movePC(dungeon_t *d){

  int keyPress;
  bool onPress = false;
  pair_t pos;
  pos[dim_y] = d->pc.position[dim_y];
  pos[dim_x] = d->pc.position[dim_x];
  while(!onPress){
    keyPress = getch();
    switch (keyPress) {
      case 55:
      case 121:
      // Move upper left
      if(!monsterListMode){
        pos[dim_x]--;
    		pos[dim_y]--;
        if(mappair(pos) == ter_wall || mappair(pos) == ter_wall_immutable){
          pos[dim_x]++;
          pos[dim_y]++;
        }
        else
          move_character(d, &d->pc, pos);
      }
      //mvprintw(0,0,"Move Upper left");
      return;
      break;

      case 56:
      case 107:
      // Move up
      //mvprintw(0,0,"Move Up");
      if(!monsterListMode){
        pos[dim_y]--;
        if(mappair(pos) == ter_wall || mappair(pos) == ter_wall_immutable){
          pos[dim_y]++;
        }
        else
          move_character(d, &d->pc, pos);
      }
  		return;
      break;

      case 57:
      case 117:
      // Move upper right
      //mvprintw(0,0,"Move Upper right");
      if(!monsterListMode){
        pos[dim_x]++;
    		pos[dim_y]--;
        if(mappair(pos) == ter_wall || mappair(pos) == ter_wall_immutable){
          pos[dim_x]--;
          pos[dim_y]++;
        }
        else
          move_character(d, &d->pc, pos);
      }
      return;
      break;

      case 54:
      case 108:
      // Move right
      //mvprintw(0,0,"Move right");
      if(!monsterListMode){
          pos[dim_x]++;
          if(mappair(pos) == ter_wall || mappair(pos) == ter_wall_immutable){
            pos[dim_x]--;
          }
          else
            move_character(d, &d->pc, pos);
        }
      return;
      break;

      case 51:
      case 110:
      // Move lower right
      //mvprintw(0,0,"Move lower right");
      if(!monsterListMode){
        pos[dim_x]++;
    		pos[dim_y]++;
        if(mappair(pos) == ter_wall || mappair(pos) == ter_wall_immutable){
          pos[dim_x]--;
          pos[dim_y]--;
        }
        else
          move_character(d, &d->pc, pos);
      }
      return;
      break;

      case 50:
      case 106:
      // Move down
      //mvprintw(0,0,"Move down");
      if(!monsterListMode){
        pos[dim_y]++;
        if(mappair(pos) == ter_wall || mappair(pos) == ter_wall_immutable){
          pos[dim_y]--;
        }
        else
          move_character(d, &d->pc, pos);
      }
  		return;
      break;

      case 49:
      case 98:
      // Move lower left
      //mvprintw(0,0,"Move lower left");
      if(!monsterListMode){
        pos[dim_x]--;
    		pos[dim_y]++;
        if(mappair(pos) == ter_wall || mappair(pos) == ter_wall_immutable){
          pos[dim_x]++;
          pos[dim_y]--;
        }
        else
          move_character(d, &d->pc, pos);
      }
      return;
      break;

      case 52:
      case 104:
      // Move left
      //mvprintw(0,0,"Move left");
      if(!monsterListMode){
        pos[dim_x]--;
        if(mappair(pos) == ter_wall || mappair(pos) == ter_wall_immutable){
          pos[dim_x]++;
        }
        else
          move_character(d, &d->pc, pos);
      }
      return;
      break;

      case 62:
      //mvprintw(0,0,"Move downstairs");
      if(!monsterListMode){
        if(mappair(pos) == ter_down_staircase)
        {
            generate_new_dungeon(d);
            onPress = true;
      }
      }
      break;

      case 60:
      // Move upstairs
      //mvprintw(0,0,"Move upstairs");
      if(!monsterListMode){
        if(mappair(pos) == ter_up_staircase )
        {
            generate_new_dungeon(d);
            onPress = true;
        }
      }
      break;

      case 32:
      case 53:
      // Do nothing
      //mvprintw(0,0,"Do nothing");
      if(!monsterListMode)
        onPress = true;
      return;
      break;

      case 109:
      // Display a list of Monsters
      //mvprintw(0,0,"Display a list of monsters");
      if(!monsterListMode)
      {
        monsterListMode = true;
        moveMonsterCheck = false;
        displayMonstersList(d);
      }
      //onPress = true;
      return;
      break;

/*
      case 27:
      // Escape
      //mvprintw(0,0,"Escape");
      if(monsterListMode){
        monsterListMode =  false;
        moveMonsterCheck = false;
        clearMonsterList(d);
        onPress = true;
        return;
      }
      break;
*/
      case 113:
      // Quit the Game
      quit = true;
      //mvprintw(0,0,"Quit the game");
      clear();
      return; // Exits the loop
      break;

    }
  }
}

// From https://stackoverflow.com/questions/29412315/move-a-cursor-inside-a-window-ncurses
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win = newwin(height, width, starty, startx);
  box(local_win, 0, 0);
  wrefresh(local_win);

  return (local_win);
}

int main(int argc, char *argv[])
{
  dungeon_t d;
  time_t seed;
  struct timeval tv;
  uint32_t i;
  uint32_t do_load, do_save, do_seed, do_image, do_save_seed,
           do_save_image, do_place_pc;
  uint32_t long_arg;
  char *save_file;
  char *load_file;
  char *pgm_file;

  memset(&d, 0, sizeof (d));

  /* Default behavior: Seed with the time, generate a new dungeon, *
   * and don't write to disk.                                      */
  do_load = do_save = do_image = do_save_seed =
    do_save_image = do_place_pc = 0;
  do_seed = 1;
  save_file = load_file = NULL;
  d.max_monsters = MAX_MONSTERS;


  // Sets up the ncurses lib before initialization
  initscr();
  raw();
  noecho();
  keypad(stdscr, TRUE);
  my_win = create_newwin(1000, 1000, 0, 0);
  wmove(my_win, 0, 0);
  wrefresh(my_win);
  ESCDELAY = 1; // REMOVE THE ESCAPE KEY DELAY

  /* The project spec requires '--load' and '--save'.  It's common  *
   * to have short and long forms of most switches (assuming you    *
   * don't run out of letters).  For now, we've got plenty.  Long   *
   * forms use whole words and take two dashes.  Short forms use an *
    * abbreviation after a single dash.  We'll add '--rand' (to     *
   * specify a random seed), which will take an argument of it's    *
   * own, and we'll add short forms for all three commands, '-l',   *
   * '-s', and '-r', respectively.  We're also going to allow an    *
   * optional argument to load to allow us to load non-default save *
   * files.  No means to save to non-default locations, however.    *
   * And the final switch, '--image', allows me to create a dungeon *
   * from a PGM image, so that I was able to create those more      *
   * interesting test dungeons for you.                             */

 if (argc > 1) {
    for (i = 1, long_arg = 0; i < argc; i++, long_arg = 0) {
      if (argv[i][0] == '-') { /* All switches start with a dash */
        if (argv[i][1] == '-') {
          argv[i]++;    /* Make the argument have a single dash so we can */
          long_arg = 1; /* handle long and short args at the same place.  */
        }
        switch (argv[i][1]) {
        case 'r':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-rand")) ||
              argc < ++i + 1 /* No more arguments */ ||
              !sscanf(argv[i], "%lu", &seed) /* Argument is not an integer */) {
            usage(argv[0]);
          }
          do_seed = 0;
          break;
        case 'n':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-nummon")) ||
              argc < ++i + 1 /* No more arguments */ ||
              !sscanf(argv[i], "%hu", &d.max_monsters)) {
            usage(argv[0]);
          }
          break;
        case 'l':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-load"))) {
            usage(argv[0]);
          }
          do_load = 1;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll treat it as a save file and try to load it.    */
            load_file = argv[++i];
          }
          break;
        case 's':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-save"))) {
            usage(argv[0]);
          }
          do_save = 1;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll save to it.  If it is "seed", we'll save to    *
	     * <the current seed>.rlg327.  If it is "image", we'll  *
	     * save to <the current image>.rlg327.                  */
	    if (!strcmp(argv[++i], "seed")) {
	      do_save_seed = 1;
	      do_save_image = 0;
	    } else if (!strcmp(argv[i], "image")) {
	      do_save_image = 1;
	      do_save_seed = 0;
	    } else {
	      save_file = argv[i];
	    }
          }
          break;
        case 'i':
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-image"))) {
            usage(argv[0]);
          }
          do_image = 1;
          if ((argc > i + 1) && argv[i + 1][0] != '-') {
            /* There is another argument, and it's not a switch, so *
             * we'll treat it as a save file and try to load it.    */
            pgm_file = argv[++i];
          }
          break;
        case 'p':
          /* PC placement makes no effort to avoid placing *
           * the PC inside solid rock.                     */
          if ((!long_arg && argv[i][2]) ||
              (long_arg && strcmp(argv[i], "-pc"))) {
            usage(argv[0]);
          }
          if ((d.pc.position[dim_y] = atoi(argv[++i])) < 1 ||
              d.pc.position[dim_y] > DUNGEON_Y - 2         ||
              (d.pc.position[dim_x] = atoi(argv[++i])) < 1 ||
              d.pc.position[dim_x] > DUNGEON_X - 2)         {
            fprintf(stderr, "Invalid PC position.\n");
            usage(argv[0]);
          }
          do_place_pc = 1;
          break;
        default:
          usage(argv[0]);
        }
      } else { /* No dash */
        usage(argv[0]);
      }
    }
  }

  if (do_seed) {
    /* Allows me to generate more than one dungeon *
     * per second, as opposed to time().           */
    gettimeofday(&tv, NULL);
    seed = (tv.tv_usec ^ (tv.tv_sec << 20)) & 0xffffffff;
  }

  if (!do_load && !do_image) {
    printf("Seed is %ld.\n", seed);
  }
  srand(seed);



  init_dungeon(&d);

  if (do_load) {
    read_dungeon(&d, load_file);
  } else if (do_image) {
    read_pgm(&d, pgm_file);
  } else {
    gen_dungeon(&d);

  }

  config_pc(&d);
  gen_monsters(&d);
  gen_staircase(&d);

  while (pc_is_alive(&d) && dungeon_has_npcs(&d) && !quit) {
    moveMonsterCheck = true;
    render_ncurses_dungeon(&d);
    movePC(&d);
    if(!monsterListMode && moveMonsterCheck)
      do_moves(&d);
  }

  // Ends and clears the dungeon
  clear();
  endwin();
  render_dungeon(&d);

  if (do_save) {
    if (do_save_seed) {
       /* 10 bytes for number, please dot, extention and null terminator. */
      save_file = malloc(18);
      sprintf(save_file, "%ld.rlg327", seed);
    }
    if (do_save_image) {
      if (!pgm_file) {
	fprintf(stderr, "No image file was loaded.  Using default.\n");
	do_save_image = 0;
      } else {
	/* Extension of 3 characters longer than image extension + null. */
	save_file = malloc(strlen(pgm_file) + 4);
	strcpy(save_file, pgm_file);
	strcpy(strchr(save_file, '.') + 1, "rlg327");
      }
    }
    write_dungeon(&d, save_file);

    if (do_save_seed || do_save_image) {
      free(save_file);
    }
  }

  if(quit) // If the user quit the game
  {
    printf("You have quit the game\n");
    printf("%s",tombstone);
    printf("You defended your life in the face of %u deadly beasts.\n"
           "You avenged the cruel and untimely murders of %u "
           "peaceful dungeon residents.\n",
           d.pc.kills[kill_direct], d.pc.kills[kill_avenged]);
  }
  else
  {
    printf("%s", pc_is_alive(&d) ? victory : tombstone);
    printf("You defended your life in the face of %u deadly beasts.\n"
           "You avenged the cruel and untimely murders of %u "
           "peaceful dungeon residents.\n",
           d.pc.kills[kill_direct], d.pc.kills[kill_avenged]);
  }
  pc_delete(d.pc.pc);
  delete_dungeon(&d);

  return 0;
}
