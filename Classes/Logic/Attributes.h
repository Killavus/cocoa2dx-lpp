#ifndef __LOGIC_ATTRIBUTES_H__
#define __LOGIC_ATTRIBUTES_H__
class Attributes {
  public:
    Attributes(int smartness, int education, int motivation) : attrSmartness(smartness), attrEducation(education), attrMotivation(motivation) {};

    int smartness() const { return attrSmartness; }
    int education() const { return attrEducation; }
    int motivation() const { return attrMotivation; }

  private:
      int attrSmartness, attrEducation, attrMotivation;
};
#endif //__LOGIC_ATTRIBUTES_H__

