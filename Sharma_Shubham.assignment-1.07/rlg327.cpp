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

    public: // Everything is set to public
      // File params
    string name;
    string description;
    string symb;
    string color;
    string speed;
    string abilities;
    string hitpoints;
    string damage;
    string rarity;

    string line; // Reads
    bool fillAll = true; // Checker to see if all fields are given
    bool justEnded = false;


    void printMonsterDef(){


      cout << name << "\n";
      cout << description;
      cout << symb << "\n";
      cout << color << "\n";
      cout << speed << "\n";
      cout << abilities << "\n";
      cout << hitpoints << "\n";
      cout << damage << "\n";
      cout << rarity << "\n";





      cout << '\n';
      writeMonsterDef();
      resetMonsters();
    }

    void writeMonsterDef(){

      // This is optional

/*      char *path = strcat(getenv("HOME"), "/.rlg327/object desc.txt");;
      std::cout << path << '\n';
      ofstream outfile (path);
      if (outfile.is_open())
      {
        outfile << "Name: " << name << "\n";
        outfile << "Rarity: " << rarity << "\n";
        outfile << "Color: " << color << "\n";
        outfile << "Speed: " << speed << "\n";
        outfile << "Damage: " << damage << "\n";
        outfile << "Hit points: " << hitpoints << "\n";
        outfile << "Abillities: " << abilities << "\n";
        outfile << "Description: " << description << "\n";
        myfile.close();
      }
      else cout << "Unable to open file";
*/
    }

    // Constructor to set up instance variables
    MonsterDefinitions(){
      char *path = strcat(getenv("HOME"), "/.rlg327/monster_desc.txt");;
      ifstream inFile (path);
      if (inFile.is_open())
      {
        line = "";
        getline (inFile,line);
        if(line != "RLG327 MONSTER DESCRIPTION 1"){
          std::cout << "Line 1 is incorrect!" << "\n";
          exit(0); // exits the program
        }
      }
      else{
        std::cout << "File not found!" << "\n";
        exit(0);
      }
      description = "";

      // Reads till eof
      while(getline(inFile, line)){
        if(justEnded && line != "BEGIN MONSTER" && line != "" ){
          std::cout << "check BEGIN MONSTER / END line" << '\n';
          exit(0);
        }
        if(justEnded && line == "BEGIN MONSTER"){
          justEnded = false;
        }

        if(line ==  "END"){
          justEnded = true;
          if(fillAll == false){
             fillAll = true;
          }
          else{
            printMonsterDef();
          }
        }


        if(line.substr(0, 4) == "NAME"){
          if(name != ""){
            //std::cout << "SETTING FLAG TO 1" << "\n";
    	       fillAll = false;
          }
          name = line.substr(5, line.length());
        }


        if(line.substr(0, 4) == "DESC"){
          if(description != ""){
            //std::cout << "SETTING FLAG TO 1" << "\n";
            fillAll = false;
          }// Gets all the description lines
          while(getline(inFile, line)){
            if(line == "."){
              break;
            }
            if(line == "DESC"){
              continue;
            }
            else{
              if(line.length() > 77){
                //std::cout << "SETTING FLAG TO 1" << "\n";
                fillAll = false;
              }
              description = description + line + "\n";
            }
          }
        }


        if(line.substr(0, 4) == "SYMB"){
          if(symb != ""){
            //std::cout << "SETTING FLAG TO 1" << "\n";
             fillAll = false;
           }
           symb = line.substr(5, line.length());
         }


        if(line.substr(0, 5) == "COLOR"){
          if(color != ""){
            //std::cout << "SETTING FLAG TO 1" << "\n";
             fillAll = false;
           }
           color = line.substr(6, line.length());
         }


         if(line.substr(0, 5) == "SPEED"){
           if(speed != ""){
             //std::cout << "SETTING FLAG TO 1" << "\n";
             fillAll = false;
            }
            speed = line.substr(6, line.length());
          }


         if(line.substr(0, 4) == "ABIL"){
           if(abilities != ""){
             //std::cout << "SETTING FLAG TO 1" << "\n";
             fillAll = false;
            }
            abilities = line.substr(5, line.length());
          }


          if(line.substr(0, 2) == "HP"){
            if(hitpoints != ""){
              //::cout << "SETTING FLAG TO 1" << "\n";
               fillAll = false;
             }
             hitpoints = line.substr(3, line.length());
           }


         if(line.substr(0, 3) == "DAM"){
           if(damage != ""){
             //std::cout << "SETTING FLAG TO 1" << "\n";
	            fillAll = false;
            }
            damage = line.substr(4, line.length());
          }


          if(line.substr(0, 4) == "RRTY"){
          if(rarity != ""){
            //  std::cout << "SETTING FLAG TO 1" << "\n";
  	         fillAll = false;
           }
           rarity = line.substr(5, line.length());
         }
       }

      inFile.close();

    }
    void resetMonsters(){
      name = rarity = color = symb = speed = damage = hitpoints = abilities = description = "";
    }
};


int main(int argc, char *argv[])
{

  // Calls Constructor
  MonsterDefinitions monsterObj;
  // This should basically handle eveything


  return 0;
}
