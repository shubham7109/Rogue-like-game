#ifndef monster_H
# define monster_H

class monster 
{
  private: 
  int color; 
  std::string rarity; 
  std::string name; 
  std::string description; 
  char symbol; 
  std::vector<int>  abilities; 
  dice  damage; 
  dice  hitpoints; 
  dice  speed; 

  public:
  monster() : color(), rarity(), name(), description(), symbol(), abilities(), damage(), hitpoints(), speed(){}
  
  monster(int color, std::string rarity, std::string name, std::string description, char symbol, std::vector<int> abilities, dice damage, dice hitpoints, dice speed) : color(color), rarity(rarity), name(name), description(description), symbol(symbol), abilities(abilities), damage(damage), hitpoints(hitpoints), speed(speed){}
  
  void set_monster(int color, std::string rarity, std::string name, std::string description, char symbol, std::vector<int> &abilities, dice &damage, dice &hitpoints, dice &speed)
  {

    this->color = color;
    this->rarity = rarity;
    this->name = name;
    this->description = description;
    this->symbol = symbol;
    this->abilities = abilities;
    this->damage = damage;
    this->hitpoints = hitpoints;
    this->speed = speed; 
  
  }
  std::string get_rarity()
  {
    return rarity;
  }
  
  int get_color() 
  {
    return color; 
  }
  
  std::string get_name() 
  {
    return name; 
  }
  
  std::string get_description() 
  {
    return description;   
  }
  
  char get_symbol() 
  {
    return symbol; 
  }
  
  std::vector<int> &get_abilities() 
  {
    return abilities; 
  }
  
  dice &get_damage() 
  {
    return damage; 
  }
  
  dice &get_hitpoints()  
  {
    return hitpoints; 
  }
  
  dice &get_speed() 
  {
    return speed; 
  }
};
#endif