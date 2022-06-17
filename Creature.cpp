//
// Created by r3mm1 on 13.06.2022.
//
#include <iostream>
#include "Creature.h"


Creature::Creature(int type, const std::string &name, const std::string &desc, int hp, int damage, int agility,
                   bool powerDefend, const std::string &descOfSPower) : type(type), name(name), desc(desc), MAXHP(hp),
                                                                        MAXDamage(damage), MAXAbility(agility),
                                                                        PowerDefend(powerDefend),
                                                                        descOfSPower(descOfSPower) {
    Creature::HP = hp;
    Creature::damage = damage;
    Creature::agility = agility;
    Creature::lvl = 1;
    Creature::alive = true;
    Creature::usesOfSPower = 2;
    Creature::chosen = false;
    Creature::EXP = 0;
    if(!powerDefend)
        Creature::MNSPower = 1.5;
    else Creature::MNSPower = 1;
}

int Creature::getType() const {
    return type;
}

int Creature::getHp() const {
    return HP;
}

void Creature::setHp(int hp) {
    HP = hp;
}

int Creature::getDamage() const {
    return damage;
}

void Creature::setDamage(int damage) {
    Creature::damage = damage;
}

int Creature::getAgility() const {
    return agility;
}

void Creature::setAgility(int agility) {
    Creature::agility = agility;
}

int Creature::getExp() const {
    return EXP;
}

void Creature::setExp(int exp) {
    EXP = exp;
}

int Creature::getUsesOfSPower() const {
    return usesOfSPower;
}

void Creature::setUsesOfSPower(int usesOfSPower) {
    Creature::usesOfSPower = usesOfSPower;
}

void Creature::info() {
    std::string type;
    switch (Creature::type) {
        case 1:
            type = "Water";
            break;
        case 2:
            type = "Earth";
            break;
        case 3:
            type = "Air";
            break;
        case 4:
            type = "Fire";
            break;
        case 5:
            type = "Ice";
            break;
        case 6:
            type = "Steel";
            break;
    }
    std::cout << Creature::name << std::endl;
    std::cout << "Type of Creature - " << type << std::endl;
    std::cout << Creature::desc << std::endl;
    std::string typeOfPower;
    if(PowerDefend)
        typeOfPower = "Type of Super Power - Defend";
    else
        typeOfPower = "Type of Super Power - Attack";
    std::cout << typeOfPower << std::endl;
    std::cout << "Super power - " << Creature::descOfSPower << std::endl;
    std::cout << "Usage of Super power - " << Creature::usesOfSPower << std::endl;
    std::cout << "HP - " << Creature::MAXHP << std::endl;
    std::cout << "Damage - " << Creature::MAXDamage << std::endl;
    std::cout << "Agility - " << Creature::MAXAbility << std::endl;
}

void Creature::infoBattle() {
    std::string type;
    switch (Creature::type) {
        case 1:
            type = "Water";
            break;
        case 2:
            type = "Earth";
            break;
        case 3:
            type = "Air";
            break;
        case 4:
            type = "Fire";
            break;
        case 5:
            type = "Ice";
            break;
        case 6:
            type = "Steel";
            break;
    }
    std::cout << Creature::name << std::endl;
    std::cout << "Type of Creature - " << type << std::endl;
    std::string typeOfPower;
    if(PowerDefend)
        typeOfPower = "Type of Super Power - Defend";
    else
        typeOfPower = "Type of Super Power - Attack";

    std::cout << typeOfPower << std::endl;
    std::cout << "Super power - " << Creature::descOfSPower << std::endl;
    std::cout << "Usage of Super power - " << Creature::usesOfSPower << std::endl;
    std::cout << "HP - " << Creature::HP << " (Max: " << Creature::MAXHP << ")" << std::endl;
    std::cout << "Damage - " << Creature::damage << " (Max: " << Creature::MAXDamage << ")" << std::endl;
    std::cout << "Agility - " << Creature::agility << " (Max: " << Creature::MAXAbility << ")" << std::endl;
}

int Creature::getLvl() const {
    return lvl;
}

void Creature::setLvl(int lvl) {
    Creature::lvl = lvl;
}

const std::string &Creature::getName() const {
    return name;
}

double Creature::getMnsPower() const {
    return MNSPower;
}

bool Creature::isChosen() const {
    return chosen;
}

void Creature::setChosen(bool chosen){
    Creature::chosen = chosen;
}

bool Creature::isPowerDefend() const {
    return PowerDefend;
}

bool Creature::isAlive() const {
    return alive;
}

void Creature::setAlive(bool alive) {
    Creature::alive = alive;
}

int Creature::getMaxhp() const {
    return MAXHP;
}

void Creature::setMaxhp(int maxhp) {
    MAXHP = maxhp;
}

int Creature::getMaxAbility() const {
    return MAXAbility;
}

void Creature::setMaxAbility(int maxAbility) {
    MAXAbility = maxAbility;
}

int Creature::getMaxDamage() const {
    return MAXDamage;
}

void Creature::setMaxDamage(int maxDamage) {
    MAXDamage = maxDamage;
}
