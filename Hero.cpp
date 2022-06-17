//
// Created by r3mm1 on 14.06.2022.
//

#include "Hero.h"

Hero::Hero(const std::string &name, const std::vector<Creature> &creatures, const std::vector<Enemy> &enemys,
           int difficulty) : Name(name), creatures(creatures), Enemys(enemys), difficulty(difficulty) {}

Hero::Hero() {}

const std::string &Hero::getName() const {
    return Name;
}

const std::vector<Creature> Hero::getCreatures() const {
    return creatures;
}

void Hero::setCreatures(const std::vector<Creature> &creatures) {
    Hero::creatures = creatures;
}

int Hero::getDifficulty() const {
    return difficulty;
}

const std::vector<Enemy> &Hero::getEnemys() const {
    return Enemys;
}
