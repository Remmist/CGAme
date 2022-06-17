//
// Created by r3mm1 on 15.06.2022.
//

#ifndef PROJECT___ENEMY_H
#define PROJECT___ENEMY_H

#include "Creature.h"
#include <vector>

class Enemy {
    std::vector<Creature> creatures;


public:
    Enemy(const std::vector<Creature> &creatures);

    const std::vector<Creature> &getCreatures() const;

    void setCreatures(const std::vector<Creature> &creatures);

};


#endif //PROJECT___ENEMY_H
