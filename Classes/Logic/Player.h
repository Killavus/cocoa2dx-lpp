#ifndef __LOGIC_PLAYER_H__
#define __LOGIC_PLAYER_H__
#include <string>

#include "Logic/Profession.h"
#include "Logic/Attributes.h"
#include "Logic/Stats.h"

class Player {
  public:
    Player(std::string playerName, std::string professionName) : name(playerName) {
      profession = Profession::byName(professionName);

      profession->initializeStats(conditions);
      profession->initializeAttributes(attributes);
    }

    const Inventory& inventory() const { return inventory; };
    Inventory& inventory { return inventory; };

    const Stats& conditions() const { return conditions; }
    Stats& conditions { return conditions; }

    const Attributes& attributes() const { return attributes; }
    Attributes& attributes { return attributes; }

    int level() const { return level; }
    int experience() const { return experience; }
  private:
      std::string name;
      Stats conditions;
      Attributes attributes;
      Inventory inventory;
      Profession profession;

      int experience;
      int level;
}; 
#endif //__LOGIC_PLAYER_H__
