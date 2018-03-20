#ifndef CHARACTER_H
# define CHARACTER_H

# include <stdint.h>

# include "dims.h"

typedef struct dungeon dungeon_t;
typedef struct npc npc_t;
typedef struct pc pc_t;
typedef struct dice_t dice_t;

typedef enum kill_type {
  kill_direct,
  kill_avenged,
  num_kill_types
} kill_type_t;

# ifdef __cplusplus
using namespace std;
class character{
public: // everything is set to public
char symbol;
pair_t position;
int32_t speed;
uint32_t alive;
/* Characters use to have a next_turn for the move queue.  Now that it is *
 * an event queue, there's no need for that here.  Instead it's in the    *
 * event.  Similarly, sequence_number was introduced in order to ensure   *
 * that the queue remains stable.  Also no longer necessary here, but in  *
 * this case, we'll keep it, because it provides a bit of interesting     *
 * metadata: locally, how old is this character; and globally, how many   *
 * characters have been created by the game.                              */
uint32_t sequence_number;
npc_t *npc;
pc_t *pc;
uint32_t kills[num_kill_types];
};

extern "C"{
  #else
  typedef void character;
  #endif

  int32_t compare_characters_by_next_turn(const void *character1,
                                          const void *character2);
  uint32_t can_see(dungeon_t *d, character *voyeur, character *exhibitionist);
  void character_delete(void *c);

  //Accesors and mutators for character class
  uint32_t get_character_yPos(character *c);
  void set_character_yPos(uint32_t newY, character *c);
  uint32_t get_character_xPos(character *c);
  void set_character_xPos(uint32_t newX, character *c);
  uint32_t get_dKills(character *c);
  void set_direct_kills(character *c, int num);
  uint32_t get_aKills(character *c);
  void set_dKills(character *c, int num);
  void delete_character(character *c);
  uint8_t get_character_alive(character *c);
  void set_character_alive(character *c, uint8_t isalive);
  char get_character_symbol(character *c);
  void set_character_symbol(character *c, char desired);
  int32_t get_character_speed(character *c);
  void set_character_speed(character *c, int32_t newspeed);
  void set_seqNumber(character *c, uint32_t num);
  int16_t *get_position(character *c);

  # ifdef __cplusplus
  }
  # endif

  #endif
