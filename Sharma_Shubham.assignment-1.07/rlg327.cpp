#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
using namespace std;

class MonsterDefinitions
{

    public:
    string NAME;
    string DESC;
    string COLOR;
    string SPEED;
    string ABIL;
    string HP;
    string DAM;
    string RRTY;
    bool begin = false;
    bool end = false;

    // Constructor to set up instance variables
    MonsterDefinitions(){

      char *path = strcat(getenv("HOME"), "/.rlg327/monster_desc.txt");;
      string metadata;
      ifstream monster_desc (path);
      if (monster_desc.is_open())
      {
        metadata = "";
        getline (monster_desc,metadata);
        if(metadata != "RLG327 MONSTER DESCRIPTION 1"){
          std::cout << metadata << "\n";
          std::cout << "Line 1 is incorrect!" << "\n";
          exit(0); // exits the program
        }
      }
      else{
        std::cout << "File not found!" << "\n";
        exit(0);
      }

      string line;
      int flag = 0;
      while(getline(monster_desc, line)){
        std::cout << line << "\n";
        if(line == "" || line == "BEGIN MONSTER"){
          continue;
        }
        if(line ==  "END"){

          if(NAME.length() == 0 ||
          RRTY.length() == 0 ||
          COLOR.length() == 0 ||
    	    SPEED.length() == 0 ||
          DAM.length() == 0 ||
          HP.length() == 0 ||
    	    ABIL.length() == 0 ||
          DESC.length() == 0 ||
          flag == 1){
             flag = 0;
          }
          else{
    	//monster has everything, print to console
    	cout << "Name: " << NAME << "\n";
    	cout << "Rarity: " << RRTY << "\n";
    	cout << "Color: " << COLOR << "\n";
    	cout << "Speed: " << SPEED << "\n";
    	cout << "Damage: " << DAM << "\n";
    	cout << "Hit points: " << HP << "\n";
    	cout << "Abillities: " << ABIL << "\n";
    	cout << "Description: " << DESC << "\n";;
    	cout << "\n" << "\n";
    	NAME = RRTY = COLOR = SPEED = DAM = HP = ABIL = DESC = "";
          }
        }
        else if(line.substr(0, 4) == "NAME"){
          if(NAME != ""){
            std::cout << "SETTING FLAG TO 1" << "\n";
    	       flag = 1;
          }
          NAME = line.substr(5, line.length());
        }
        else if(line.substr(0, 4) == "RRTY"){
          if(RRTY != ""){
            std::cout << "SETTING FLAG TO 1" << "\n";
    	flag = 1;
          }
          RRTY = line.substr(5, line.length());
        }
        else if(line.substr(0, 5) == "COLOR"){
          if(COLOR != ""){
            std::cout << "SETTING FLAG TO 1" << "\n";
    	flag = 1;
          }
          COLOR = line.substr(5, line.length());
        }
        else if(line.substr(0, 5) == "SPEED"){
          if(SPEED != ""){
            std::cout << "SETTING FLAG TO 1" << "\n";
    	flag = 1;
          }
          SPEED = line.substr(6, line.length());
        }
        else if(line.substr(0, 3) == "DAM"){
          if(DAM != ""){
            std::cout << "SETTING FLAG TO 1" << "\n";
    	flag = 1;
          }
          DAM = line.substr(4, line.length());
        }
        else if(line.substr(0, 2) == "HP"){
          if(HP != ""){
            std::cout << "SETTING FLAG TO 1" << "\n";
    	flag = 1;
          }
          HP = line.substr(3, line.length());
        }
        else if(line.substr(0, 4) == "ABIL"){
          if(ABIL != ""){
            std::cout << "SETTING FLAG TO 1" << "\n";
    	flag = 1;
          }
          ABIL = line.substr(5, line.length());
        }
        else if(line.substr(0, 4) == "DESC"){
          if(DESC != ""){
            std::cout << "SETTING FLAG TO 1" << "\n";
    	flag = 1;
          }
          while(getline(monster_desc, line)){
    	if(line == "."){
    	  break;
    	}
    	if(line == "DESC"){
    	  continue;
    	}
    	else if(DESC == ""){
    	  if(line.length() > 77){
          std::cout << "SETTING FLAG TO 1" << "\n";
    	    flag = 1;
    	  }
    	  DESC = line + "\n";
    	}
    	else{
    	  if(line.length() > 77){
          std::cout << "SETTING FLAG TO 1" << "\n";
    	    flag = 1;
    	  }
    	  DESC = DESC + line + "\n";
    	}
          }
        }
        else{
            continue;
        }
      }
      monster_desc.close();

    }

    // Member Functions()
    void printMonster()
    {
       std::cout << "Print monster" << std::endl;;
    }

    void resetMonster(){
      std::cout << "Reset monster" << std::endl;
    }
};


int main(int argc, char *argv[])
{

  // Calls Constructor
  MonsterDefinitions monsterObj;

  return 0;
}
