//
// Created by r3mm1 on 15.06.2022.
//

#include "Enemy.h"

Enemy::Enemy(const std::vector<Creature> &creatures) : creatures(creatures) {}

const std::vector<Creature> &Enemy::getCreatures() const {
    return creatures;
}

void Enemy::setCreatures(const std::vector<Creature> &creatures) {
    Enemy::creatures = creatures;
}
