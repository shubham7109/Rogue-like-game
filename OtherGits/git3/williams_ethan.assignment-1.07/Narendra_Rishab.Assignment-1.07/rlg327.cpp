#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector> 
#include <ctype.h>
#include "dungeon.h"
#include "pc.h"
#include "npc.h"
#include "move.h"
#include "io.h"
#include "dice.h"
#include "monster.h" 

std::vector<int> colors;
std::vector<monster> monsters; 

class splitstring : public std::string 
{
  std::vector<std::string> flds;
  
  public:
    splitstring(char *s) : std::string(s) { };
    std::vector<std::string>& split(char delim, int rep=0);
};

std::vector<std::string>& splitstring::split(char delim, int rep) 
{
    if (!flds.empty()) flds.clear();  
    std::string work = data();
    std::string buf = "";
    int i = 0;
    while ((size_t)i < work.length()) 
    {
        if (work[i] != delim)
            buf += work[i];
        else if (rep == 1) 
	{
            flds.push_back(buf);
            buf = "";
        }
        else if (buf.length() > 0) 
	{
            flds.push_back(buf);
            buf = "";
        }
        i++;
    }
    if (!buf.empty())
        flds.push_back(buf);
    return flds;
}

std::string trim(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && isspace(*it))
        it++;

    std::string::const_reverse_iterator rit = s.rbegin();
    while (rit.base() != it && isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

void parse(std::ifstream& fileRead){

  bool is_monster = false;

  std::string color, name, description, rarity, abilities, damage, speed, hitpoints; 
  char symbol;
  std::vector<int> abil; 
  dice hp, sp, dam;
  monster list; 

  int parameters = 0; 
  
  std::string line = ""; 
  getline(fileRead, line); 
 	
  if(line != "RLG327 MONSTER DESCRIPTION 1")
  {
     std::cout << "First line should be RLG327 MONSTER DESCRIPTION 1 \n "; 
     return; 
  }

  while(!fileRead.eof())
  {
    std::string keyword;
    fileRead  >> keyword;
    keyword = trim(keyword);

    bool present = false; 
    while (!present) 
    {
      if(isblank(fileRead.peek()))
      {
	fileRead.get();
      }   
      else
      {
	break; 
      }
    } 

    std::getline(fileRead, line); 
    line = trim(line);

    if(keyword + " " + line  == "BEGIN MONSTER")
    {
      std::cout << "\n";
      color = name = description = abilities = damage = hitpoints = speed = rarity = ""; 
      symbol = ' ';
      abil.clear();   
      parameters = 0; 
      is_monster = true;
    }

    if(is_monster)
    {
      if(keyword == "NAME")
      {
	name = line;
	parameters++; 
      }

      if(keyword == "SYMB")
      {  
	symbol = line.at(0);
	parameters++;
      }

      if(keyword == "COLOR")
      {    
	if(line == "BLACK")
	{
	  colors.push_back(COLOR_BLACK); 
	  color = line;
	  parameters++;
	}
	
	else if(line == "WHITE")
	{
	  colors.push_back(COLOR_WHITE);
	  color = line;
	  parameters++;
	}
	
	else if(line == "BLUE")
	{
	  colors.push_back(COLOR_BLUE); 
	  color = line;
	  parameters++;
	}
	
	else if(line == "GREEN")
	{
	  colors.push_back(COLOR_GREEN);
	  color = line;
	  parameters++;
	}	
	
	else if(line == "RED")
	{
	  colors.push_back(COLOR_RED);
	  color = line;
	  parameters++;
	}
	
	else if(line == "CYAN")
	{
	  colors.push_back(COLOR_CYAN);
	  color = line;
	  parameters++;
	}
	
	else if(line == "YELLOW")
	{
	  colors.push_back(COLOR_YELLOW);
	  color = line;
	  parameters++;
	}
	
	else if(line == "MAGENTA")
	{
	  colors.push_back(COLOR_MAGENTA); 
	  color = line;
	  parameters++;
	}

	else if(line.empty() == false)
	{
	  color = line;
	  parameters++;
	}
      }

      if(keyword == "DESC")
      {  
	getline(fileRead, line);
	description += line + "\n";

	while(!fileRead.eof())
	{
	  getline(fileRead, line); 
	  line = trim(line);

	  if(line == ".")
	  {
	    break; 
	  }
	  description += line + "\n" ;
	}
	description.erase(description.length()-1); 

	if(line.length() < 77)
	{
	  if(line == ".")
	  {
	    parameters++;
	  }
	}
      }

      if(keyword == "SPEED")
      { 
	int base, number, sides;

	if(sscanf(line.c_str(), "%d+%ud%u", &base, &number, &sides) == 3)
	{
	  sp.setDice(base, number, sides); 
	  speed = line; 
	  parameters++;
	}
      }

      if(keyword == "DAM")
      {   
	int base, number, sides;
	
	if(sscanf(line.c_str(), "%d+%ud%u", &base, &number, &sides) == 3)
	{
	  dam.setDice(base, number, sides); 
	  damage = line;
	  parameters++;
	} 
      }

      if(keyword == "HP")
      {
	int base, number, sides;
	
	if(sscanf(line.c_str(), "%d+%ud%u", &base, &number, &sides) == 3)
	{
	  hp.setDice(base, number, sides); 
	  hitpoints = line; 
	  parameters++;
	}
      }

      if(keyword == "RRTY")
      {
	rarity = line;
	parameters++;
      }
      
      if(keyword == "ABIL")
      { 
	splitstring s((char*)line.c_str());

	std::vector<std::string> flds = s.split(' ');
	for (int i = 0; (size_t)i < flds.size(); i++)
	{
	  if(flds[i] == "SMART")
	  {
	    abil.push_back(0); 
	  }
	  else if(flds[i] == "TELE")
	  {
	    abil.push_back(1); 
	  }
	  else if(flds[i] == "TUNNEL")
	  {
	    abil.push_back(2); 
	  }
	  else if(flds[i] == "ERRATIC")
	  {
	    abil.push_back(3); 
	  }
	  else if(flds[i] == "PASS")
	  {
	    abil.push_back(4); 
	  }
	}
	abilities = line; 
	parameters++;
	
      }
    }

    if(keyword == "END" && parameters == 9)
    { 
      std::cout << name + "\n";
      std::cout << description + "\n";
      std::cout << symbol << "\n";
      std::cout << color + "\n"; 
      std::cout << rarity + "\n";
      std::cout << speed  + "\n"; 
      std::cout << abilities  + "\n"; 
      std::cout << hitpoints  + "\n";
      std::cout << damage  + "\n";

      int currentColor = colors[colors.size() -1]; 

      list.set_monster(currentColor, rarity, name, description, symbol, abil, dam, hp, sp );
      monsters.push_back(list);  
    }    	
 } 
} 

int main(int argc, char *argv[])
{
  std::string file; 
  std::ifstream fileRead; 
  file = getenv("HOME"); 
  file += std::string("/") + ".rlg327" + "/" + "monster_desc.txt";
  fileRead.open(file.c_str()); 
  parse(fileRead);
  return 0;
}
