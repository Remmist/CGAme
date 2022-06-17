//
// Created by r3mm1 on 13.06.2022.
//

#ifndef PROJECT___CREATURE_H
#define PROJECT___CREATURE_H

#include <string>

class Creature {
    /*
     * 1-вода
     * 2-земля
     * 3-воздух
     * 4-огонь
     * 5-лед
     * 6-сталь
     */

    int type;
    std::string name;
    std::string desc;

    int MAXHP;
    int MAXAbility;
    int MAXDamage;
    int HP;
    int damage;
    int agility;
    bool PowerDefend;
    std::string descOfSPower;
    double MNSPower;
    bool chosen;
    int lvl;
    int EXP;
    int usesOfSPower;
    bool alive;

public:

    Creature(int type, const std::string &name, const std::string &desc, int hp, int damage, int agility,
             bool powerDefend, const std::string &descOfSPower);


    int getType() const;

    int getHp() const;
    void setHp(int hp);

    int getDamage() const;
    void setDamage(int damage);

    int getAgility() const;
    void setAgility(int agility);

    bool isChosen() const;
    void setChosen(bool chosen);

    double getMnsPower() const;

    bool isPowerDefend() const;

    int getExp() const;
    void setExp(int exp);

    bool isAlive() const;
    void setAlive(bool alive);

    int getUsesOfSPower() const;
    void setUsesOfSPower(int usesOfSPower);

    int getLvl() const;
    void setLvl(int lvl);

    int getMaxhp() const;
    void setMaxhp(int maxhp);

    int getMaxAbility() const;
    void setMaxAbility(int maxAbility);

    int getMaxDamage() const;
    void setMaxDamage(int maxDamage);

    const std::string &getName() const;

    void info();
    void infoBattle();

};


#endif //PROJECT___CREATURE_H
