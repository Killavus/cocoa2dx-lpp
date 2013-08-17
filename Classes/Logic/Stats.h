#ifndef __LOGIC_STATS_H__
#define __LOGIC_STATS_H__
class Stats {
  public:
    Stats(int _money, int _fatigue, int _hunger) : statMoney(_money), statFatigue(_fatigue), statHunger(_hunger) {};

    int money() const { return statMoney; }
    int hunger() const { return statHunger; }
    int fatigue() const { return statFatigue; }

  private:
      int statMoney, statFatigue, statHunger;
};
#endif //__LOGIC_STATS_H__

