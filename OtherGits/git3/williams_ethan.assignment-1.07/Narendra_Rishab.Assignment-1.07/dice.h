#ifndef dice_H
# define dice_H

class dice
{
  private: 
   int base;
   int number;
   int sides;
	  
  public:
    dice() : base(0), number(0), sides(0){}

    dice(int base, int number, int sides) : base(base), number(number), sides(sides){}

    void setDice(int base, int number, int sides)
    {
      this->base = base; 
      this->number = number; 
      this->sides = sides; 
    }
    
    int getBase()
    {
      return base; 
    }
    int getSides()
    {
      return sides; 
    }
    int getNumber()
    {
      return number; 
    }
};
#endif