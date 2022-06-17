//
// Created by r3mm1 on 15.06.2022.
//

#ifndef PROJECT___BATTLE_H
#define PROJECT___BATTLE_H

#include "Hero.h"

class Battle {

    Hero hero;
    Enemy enemy;
    std::vector<Creature> ActiveCreatures;
    std::vector<Creature> AllCreatures;
    bool battleend;
    bool continueBattle;
    double diff;
    int id;

public:

    Battle(const Hero &hero, const Enemy &enemy, int id);

    void start();

    void resetAllCreatures();

    double factorTypes(Creature c1, Creature c2);

    void saveProgress();

    void PlayerTurn();

    void replaceCreature(Creature &creature);

    void evoCreature(Creature &creature);

    void CreatureChoose(Creature &creature);

    void attackCreature(Creature &creature);

    void normalAttack(Creature &myCreature, Creature &enemyCreature);

    void superPowerAttack(Creature &creature, Creature &enemyCreature);

    void EnemyTurn();

    void evoEnemy(Creature &creature);

    void superAttackEnemy(std::vector<Creature> &vec, int poz, int cel);

    const Hero &getHero() const;

    double getDiff() const;

    bool isContinueBattle() const;

    bool isBattleend() const;
    void setBattleend(bool battleend);

};


#endif //PROJECT___BATTLE_H
