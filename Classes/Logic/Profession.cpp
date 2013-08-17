#include "Logic/Profession.h"

#include "Logic/Attributes.h"
#include "Logic/Stats.h"

void Profession::initializeStats(Stats& stats) const {
  stats = initialStats;
}

void Profession::initializeAttributes(Attributes& attributes) const {
  attributes = initialAttributes;
} 

Profession Profession::byName(std::string name) {
  if(name == "Student") {
    return Profession("Student", Attributes(10, 10, 10), Stats(0, 0, 1500));
  }
  
  throw std::string("Not such profession exists");
}
