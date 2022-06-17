//
// Created by r3mm1 on 14.06.2022.
//

#ifndef PROJECT___HERO_H
#define PROJECT___HERO_H

#include "Creature.h"
#include "Enemy.h"
#include <string>
#include <vector>

class Hero {

    std::string Name;
    std::vector<Creature> creatures;
    std::vector<Enemy> Enemys;
    int difficulty;
    //1 - easy      2 - middle      3 - hard

public:
    Hero(const std::string &name, const std::vector<Creature> &creatures, const std::vector<Enemy> &enemys,
         int difficulty);

    Hero();

    const std::string &getName() const;

    const std::vector<Creature> getCreatures() const;

    void setCreatures(const std::vector<Creature> &creatures);

    int getDifficulty() const;

    const std::vector<Enemy> &getEnemys() const;

};


#endif //PROJECT___HERO_H
