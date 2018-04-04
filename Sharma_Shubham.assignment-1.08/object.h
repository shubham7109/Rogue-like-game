#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include "descriptions.h"
#include "dims.h"

class object 
{
  private:
    const std::string &name;
    const std::string &description;
    object_type_t type;
    uint32_t color;
    pair_t position;
    const dice &damage;
    int32_t hit, dodge, defence, weight, speed, attribute, value;
    uint32_t rarity;
    bool artifact;
    bool seen;
    object *next;
    
  public:
  object(const object_description &o, pair_t p, object *next);
  ~object();
  
  int32_t get_damage_base() const
  {
    return damage.get_base();
  }
  
  int32_t get_damage_number() const
  {
    return damage.get_number();
  }
  
  int32_t get_damage_sides() const
  {
    return damage.get_sides();
  }
  
  char get_symbol()
  {
    return next ? '&' : object_symbol[type];
  }
  
  uint32_t get_color()
  {
    return color;
  }
  
  const char *get_name()
  {
    return name.c_str();
  }
  
  int32_t get_speed()
  {
    return speed;
  }
  
  int32_t roll_dice()
  {
    return damage.roll();
  }
  
  int32_t get_type()
  {
    return type;
  }
  
  uint32_t get_rarity()
  {
    return rarity;
  }
  
  bool get_artifact()
  {
    return artifact;
  }
  
  bool have_seen() 
  { 
    return seen; 
  }
  
  void has_been_seen() 
  { 
    seen = true; 
  }
};

void generate_objects(dungeon_t *d);
char object_get_symbol(object *o);
void destroy_objects(dungeon_t *d);

#endif
