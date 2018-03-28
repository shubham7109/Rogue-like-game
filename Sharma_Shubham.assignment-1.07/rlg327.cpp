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
      //char *filePath = strcat(getenv("HOME"), "/.rlg327/monster desc.txt");
      //std::cout << filePath << '\n';

      /*string line;
      ifstream myfile (filePath);
      if (myfile.is_open())
      {
        getline (myfile,line);
        if(line != "RLG327 MONSTER DESCRIPTION 1")
          exit(0); // exits the program

        do{
          getline (myfile,line)
        }while
        while ( getline (myfile,line) )
        {
          cout << line << '\n';

          if(line == "BEGIN MONSTER"){

          }
          else if(line == ""){

          }
        }
      myfile.close();
      }
      else cout << "Unable to open file" << endl;*/


      char *dir = getenv("HOME");
      char *path = strcat(dir, "/.rlg327/");

      //Opens monster description text file
      std::ifstream monster_desc;
      monster_desc.open(strcat(path, "monster desc.txt"));
      std::cout << path << '\n';
      string metadata;
      getline(monster_desc, metadata);
      std::cout << metadata << '\n';
      //If metadata doesn't match, exit program
      if(metadata != "RLG327 MONSTER DESCRIPTION 1"){
        exit(0);
      }

      string tmp;
      int flag = 0;
      while(getline(monster_desc, tmp)){
        std::cout << tmp << '\n';
        if(tmp == "" || tmp == "BEGIN MONSTER"){
          continue;
        }
        if(tmp ==  "END"){
          if(NAME == "" || RRTY == "" || COLOR == "" ||
    	 SPEED == "" || DAM == "" || HP == "" ||
    	 ABIL == "" || DESC == "" || flag == 1){
            NAME = RRTY = COLOR = SPEED = DAM = HP = ABIL = DESC = "";
    	flag = 0;
          }
          else{
    	//monster has everything, print to console
    	cout << "Name: " << NAME << '\n';
    	cout << "Rarity: " << RRTY << '\n';
    	cout << "Color: " << COLOR << '\n';
    	cout << "Speed: " << SPEED << '\n';
    	cout << "Damage: " << DAM << '\n';
    	cout << "Hit points: " << HP << '\n';
    	cout << "Abillities: " << ABIL << '\n';
    	cout << "Description: " << DESC << '\n';;
    	cout << '\n' << '\n';
    	NAME = RRTY = COLOR = SPEED = DAM = HP = ABIL = DESC = "";
          }
        }
        else if(tmp.substr(0, 4) == "NAME"){
          if(NAME != ""){
    	flag = 1;
          }
          NAME = tmp.substr(5, tmp.length());
        }
        else if(tmp.substr(0, 4) == "RRTY"){
          if(RRTY != ""){
    	flag = 1;
          }
          RRTY = tmp.substr(5, tmp.length());
        }
        else if(tmp.substr(0, 5) == "COLOR"){
          if(COLOR != ""){
    	flag = 1;
          }
          COLOR = tmp.substr(5, tmp.length());
        }
        else if(tmp.substr(0, 5) == "SPEED"){
          if(SPEED != ""){
    	flag = 1;
          }
          SPEED = tmp.substr(6, tmp.length());
        }
        else if(tmp.substr(0, 3) == "DAM"){
          if(DAM != ""){
    	flag = 1;
          }
          DAM = tmp.substr(4, tmp.length());
        }
        else if(tmp.substr(0, 2) == "HP"){
          if(HP != ""){
    	flag = 1;
          }
          HP = tmp.substr(3, tmp.length());
        }
        else if(tmp.substr(0, 4) == "ABIL"){
          if(ABIL != ""){
    	flag = 1;
          }
          ABIL = tmp.substr(5, tmp.length());
        }
        else if(tmp.substr(0, 4) == "DESC"){
          if(DESC != ""){
    	flag = 1;
          }
          while(getline(monster_desc, tmp)){
    	if(tmp == "."){
    	  break;
    	}
    	if(tmp == "DESC"){
    	  continue;
    	}
    	else if(DESC == ""){
    	  if(tmp.length() > 77){
    	    flag = 1;
    	  }
    	  DESC = tmp + '\n';
    	}
    	else{
    	  if(tmp.length() > 77){
    	    flag = 1;
    	  }
    	  DESC = DESC + tmp + '\n';
    	}
          }
        }
        else{
          flag = 1;
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
