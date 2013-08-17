#ifndef __LOGIC_PROFESSION_H__
#define __LOGIC_PROFESSION_H__
#include <string>

#include "Logic/Attributes.h"
#include "Logic/Stats.h"

class Profession {
  public:
    static Profession byName(std::string name);

    void initializeStats(Stats& stats) const;
    void initializeAttributes(Attributes& attributes) const;
  private:
    Profession(std::string professionName, const Attributes& attributes, const Stats &stats) : name(professionName), initialAttributes(attributes), initialStats(stats) {}
    std::string name;

    Attributes initialAttributes;
    Stats initialStats;  
};
#endif //__LOGIC_PROFESSION_H__
