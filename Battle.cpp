//
// Created by r3mm1 on 15.06.2022.
//

#include "Battle.h"
#include <iostream>
#include <fstream>
#include <ctime>


Battle::Battle(const Hero &hero, const Enemy &enemy, int id) : hero(hero), enemy(enemy) {
    Battle::id = id;
    Battle::battleend = false;
    Battle::continueBattle = false;
    Battle::diff = hero.getDifficulty();
    if(hero.getDifficulty() == 1)
        Battle::diff = 0.8;
    if(hero.getDifficulty() == 2)
        Battle::diff = 1;
    if(hero.getDifficulty() == 3)
        Battle::diff = 1.2;
    std::cout << "=======================================" << std::endl;
    std::cout << "Battle " << id << std::endl;
    AllCreatures = hero.getCreatures();
    for(int i = 0; i < 4; i++) {
        ActiveCreatures.push_back(AllCreatures.at(i));
        AllCreatures.at(i).setChosen(true);
    }
    ConfigEnemy();
}

void Battle::start() {
    while (true) {
        bool alive = false;
        for(int i = 0; i < AllCreatures.size(); i++){
            if(AllCreatures.at(i).isAlive()) {
                alive = true;
                break;
            }
        }
        if(!alive || isBattleend())
            break;
        for(int i = 0; i < 2; i++){
            if(i == 0)
                PlayerTurn();
            if(i == 1)
                EnemyTurn();
        }
    }
    std::cout << "The battle is over!" << std::endl;
    if(isBattleend()){
        //player win
        resetAllCreatures();
        std::cout << "You win Battle!" << std::endl;
        std::cout << "You want to save game and exit or continue game?" << std::endl;
        std::cout << "1)Save and exit" << std::endl;
        std::cout << "2)Continue playing" << std::endl;
        int input;
        std::cin >> input;
        switch (input) {
            case 1:
                saveProgress();
                break;
            case 2:
                continueBattle = true;
                break;
            default:
                continueBattle = true;
                break;
        }
    } else {
        //player lose
        resetAllCreatures();
        std::cout << "You lose Battle! :(" << std::endl;
        std::cout << "You want to save game and exit or continue game?" << std::endl;
        std::cout << "1)Save and exit" << std::endl;
        std::cout << "2)Restart battle" << std::endl;
        int input;
        std::cin >> input;
        switch (input) {
            case 1:
                id--;
                saveProgress();
                break;
            case 2:
                start();
                break;
            default:
                start();
                break;
        }
    }
}

void Battle::PlayerTurn() {
    std::cout << std::endl;
    std::cout << "Your enemy: ";
    std::for_each(enemy.getCreatures().begin(), enemy.getCreatures().end(), [](Creature creature) {
        if (creature.isAlive())
            std::cout << creature.getName() << "(lvl " << creature.getLvl() << ") HP - " << creature.getHp()
                      << "; ";
    });
    std::cout << std::endl;
    std::cout << "Choose your creature" << std::endl;
    int c = 1;
    std::for_each(ActiveCreatures.begin(), ActiveCreatures.end(), [&c](Creature creature) {
        std::string inf;
        std::string update;
        if (creature.isAlive())
            inf = "Alive";
        else
            inf = "Unconscious";
        if (creature.getExp() >= 100)
            update = "LVL UP AVAILABLE!";
        else
            update = "";
        std::cout << c << ")" << creature.getName() << "(lvl " << creature.getLvl() << ")" << " - " << inf << " "
                  << update << std::endl;
        c++;
    });
    int input;
    std::cin >> input;
    switch (input) {
        case 1:
            CreatureChoose(ActiveCreatures.at(input - 1));
            break;
        case 2:
            CreatureChoose(ActiveCreatures.at(input - 1));
            break;
        case 3:
            CreatureChoose(ActiveCreatures.at(input - 1));
            break;
        case 4:
            CreatureChoose(ActiveCreatures.at(input - 1));
            break;
        default:
            std::cout << "There is no such option!" << std::endl;
            start();
            break;
    }
}

void Battle::CreatureChoose(Creature &creature) {
    std::cout << std::endl;
    creature.infoBattle();
    std::cout << "LVL - " << creature.getLvl() << std::endl;
    std::cout << "EXP - " << creature.getExp() << std::endl;
    if(!creature.isAlive()){
        std::cout << "Your creature is not conscious!" << std::endl;
        std::cout << "1)Replace Creature" << std::endl;
        std::cout << "2)Return" << std::endl;
        int input;
        std::cin >> input;
        switch (input) {
            case 1:
                replaceCreature(creature);
                break;
            case 2:
                PlayerTurn();
                break;
            default:
                std::cout << "There is no such option!" << std::endl;
                CreatureChoose(creature);
                break;
        }
        return;
    }
    std::string evo;
    if(creature.getExp() >= 100)
        evo = "Available";
    else
        evo = "Not available";
    std::cout << "1)Attack" << std::endl;
    std::cout << "2)Replace Creature" << std::endl;
    std::cout << "3)Evolution(" << evo << ")" << std::endl;
    std::cout << "4)Return" << std::endl;
    int input;
    std::cin >> input;
    switch (input) {
        case 1:
            attackCreature(creature);
            break;
        case 2:
            replaceCreature(creature);
            break;
        case 3:
            if(evo == "Not available"){
                std::cout << "This option is not available!" << std::endl;
                CreatureChoose(creature);
                break;
            }
            evoCreature(creature);
            break;
        case 4:
            PlayerTurn();
            break;
        default:
            std::cout << "There is no such option!" << std::endl;
            CreatureChoose(creature);
            break;
    }
}

void Battle::evoCreature(Creature &creature) {
    std::cout << std::endl;
    std::cout << "Chose stats (2) that you want to upgrade: " << std::endl;
    std::cout << "1)HP" << std::endl;
    std::cout << "2)Damage" << std::endl;
    std::cout << "3)Agility" << std::endl;
    int input;
    std::cin >> input;
    switch (input) {
        case 1:
            creature.setLvl(creature.getLvl() + 1);
            creature.setExp(creature.getExp() - 100);
            creature.setMaxhp(creature.getMaxhp() + 15);
            std::cout << "Chose stat that you want to upgrade: " << std::endl;
            std::cout << "1)Damage" << std::endl;
            std::cout << "2)Agility" << std::endl;
            int input2;
            std::cin >> input2;
            switch (input2) {
                case 1:
                    creature.setMaxDamage(creature.getMaxDamage() + 10);
                    creature.setDamage(creature.getMaxDamage());
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
                case 2:
                    creature.setMaxAbility(creature.getMaxAbility() + 10);
                    creature.setAgility(creature.getMaxAbility());
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
                default:
                    creature.setMaxAbility(creature.getMaxAbility() + 10);
                    creature.setAgility(creature.getMaxAbility());
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
            }
            break;
        case 2:
            creature.setLvl(creature.getLvl() + 1);
            creature.setExp(creature.getExp() - 100);
            creature.setMaxDamage(creature.getMaxDamage() + 10);
            creature.setDamage(creature.getMaxDamage());
            std::cout << "Chose stat that you want to upgrade: " << std::endl;
            std::cout << "1)HP" << std::endl;
            std::cout << "2)Agility" << std::endl;
            int input3;
            std::cin >> input3;
            switch (input3) {
                case 1:
                    creature.setMaxhp(creature.getMaxhp() + 15);
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
                case 2:
                    creature.setMaxAbility(creature.getMaxAbility() + 10);
                    creature.setAgility(creature.getMaxAbility());
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
                default:
                    creature.setMaxAbility(creature.getMaxAbility() + 10);
                    creature.setAgility(creature.getMaxAbility());
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
            }
            break;
        case 3:
            creature.setLvl(creature.getLvl() + 1);
            creature.setExp(creature.getExp() - 100);
            creature.setMaxAbility(creature.getMaxAbility() + 10);
            creature.setAgility(creature.getMaxAbility());
            std::cout << "Chose stat that you want to upgrade: " << std::endl;
            std::cout << "1)Damage" << std::endl;
            std::cout << "2)HP" << std::endl;
            int input4;
            std::cin >> input4;
            switch (input4) {
                case 1:
                    creature.setMaxDamage(creature.getMaxDamage() + 10);
                    creature.setDamage(creature.getMaxDamage());
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
                case 2:
                    creature.setMaxhp(creature.getMaxhp() + 15);
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
                default:
                    creature.setMaxhp(creature.getMaxhp() + 15);
                    std::cout << creature.getName() << " was successfully evoluted!" << std::endl;
                    break;
            }
            break;
        default:
            std::cout << "There is no such option!" << std::endl;
            evoCreature(creature);
            break;
    }
}

void Battle::replaceCreature(Creature &creature) {
    std::cout << std::endl;
    std::cout << "Choose which creature you want to replace " << creature.getName() << " with?" << std::endl;
    int c = 1;
    std::for_each(AllCreatures.begin(), AllCreatures.end(), [&c](Creature freeCreature){
       if(!freeCreature.isChosen()){
           std::cout << c << ")" << freeCreature.getName() << "(lvl " << freeCreature.getLvl() << "), hp = " << freeCreature.getHp() << std::endl;
           c++;
       }
    });
    int input;
    std::cin >> input;
    if(input > c-1 || input < 1){
        std::cout << "There is no such option!" << std::endl;
        replaceCreature(creature);
        return;
    }
    for(int i = 0; i < ActiveCreatures.size(); i++){
        if(&ActiveCreatures.at(i) == &creature){
            Creature tmp = creature;
            ActiveCreatures.at(i) = AllCreatures.at(input + 3);
            AllCreatures.at(input+3) = tmp;
            std::cout << tmp.getName() << " was replaced with " << ActiveCreatures.at(i).getName() << std::endl;
            break;
        }
    }
}

void Battle::attackCreature(Creature &creature) {
    std::cout << std::endl;
    std::cout << "Choose your enemy: " << std::endl;
    int c = 1;
    std::for_each(enemy.getCreatures().begin(), enemy.getCreatures().end(), [&c](Creature enCreature){
        if(enCreature.isAlive()){
            std::cout << c << ")" << enCreature.getName() << "(lvl " << enCreature.getLvl() << ") HP - " << enCreature.getHp() << std::endl;
            c++;
        }
    });
    int input;
    std::cin >> input;
    if(input > c-1 || input < 1){
        std::cout << "There is no such option!" << std::endl;
        attackCreature(creature);
        return;
    }
    std::cout << "1)Normal attack" << std::endl;
    std::cout << "2)Use super power(" << creature.getUsesOfSPower() << " left)" << std::endl;
    int att;
    std::cin >> att;
    switch (att) {
        case 1:
            normalAttack(creature, const_cast<Creature &>(enemy.getCreatures().at(input - 1)));
            break;
        case 2:
            if(creature.getUsesOfSPower() <= 0){
                std::cout << "The creature has 0 super attacks left!" << std::endl;
                attackCreature(creature);
                break;
            }
            superPowerAttack(creature, const_cast<Creature &>(enemy.getCreatures().at(input - 1)));
            break;
        default:
            std::cout << "There is no such option!" << std::endl;
            attackCreature(creature);
            break;
    }
}

void Battle::normalAttack(Creature &myCreature, Creature &en) {
    std::cout << std::endl;
    std::rand();
    srand(time(NULL));

    int random = rand() % 100;

    if(en.getAgility() <= 20){
        if(random <= 10){
            std::cout << "The enemy dodged the attack!" << std::endl;
            return;
        }
    }
    if(en.getAgility() > 20 && en.getAgility() <= 40){
        if(random <= 20){
            std::cout << "The enemy dodged the attack!" << std::endl;
            return;
        }
    }
    if(en.getAgility() > 40 && en.getAgility() <= 60){
        if(random <= 30){
            std::cout << "The enemy dodged the attack!" << std::endl;
            return;
        }
    }
    if(en.getAgility() > 60){
        if(random <= 50){
            std::cout << "The enemy dodged the attack!" << std::endl;
            return;
        }
    }
    en.setHp(en.getHp() - myCreature.getDamage() * factorTypes(myCreature,en));
    myCreature.setExp(myCreature.getExp() + 50);
    std::cout << "Successful attack!" << std::endl;
    std::cout << "Your " << myCreature.getName() << " received 50 EXP" << std::endl;
    std::cout << "Enemy " << en.getName() << " took "<< myCreature.getDamage() * factorTypes(myCreature,en) << " damage" << std::endl;
    if(en.getHp() <= 0){
        std::vector<Creature> vector;
        std::cout << "Enemy " << en.getName() << " loses consciousness! "<< std::endl;
        if(enemy.getCreatures().size() == 1){
            setBattleend(true);
            return;
        }
        for(int i = 0; i < enemy.getCreatures().size(); i++){
            if(&enemy.getCreatures().at(i) != &en){
                vector.push_back(enemy.getCreatures().at(i));
            }
        }
        enemy.setCreatures(vector);
    }
}

void Battle::superPowerAttack(Creature &creature, Creature &en) {
    std::cout << std::endl;
    if(creature.isPowerDefend()){
        creature.setAgility(creature.getAgility() + 10);
        std::cout << "Agility of your creature has been increased by 10!" << std::endl;
    } else {
        std::rand();
        srand(time(NULL));

        int random = rand() % 100;

        if (en.getAgility() <= 20) {
            if (random <= 10) {
                std::cout << "The enemy dodged the attack!" << std::endl;
                return;
            }
        }
        if (en.getAgility() > 20 && en.getAgility() <= 40) {
            if (random <= 20) {
                std::cout << "The enemy dodged the attack!" << std::endl;
                return;
            }
        }
        if (en.getAgility() > 40 && en.getAgility() <= 60) {
            if (random <= 30) {
                std::cout << "The enemy dodged the attack!" << std::endl;
                return;
            }
        }
        if (en.getAgility() > 60) {
            if (random <= 50) {
                std::cout << "The enemy dodged the attack!" << std::endl;
                return;
            }
        }
        en.setHp(en.getHp() - (creature.getDamage()*creature.getMnsPower()*factorTypes(creature,en)));
        creature.setExp(creature.getExp() + 100);
        creature.setUsesOfSPower(creature.getUsesOfSPower() - 1);
        std::cout << "Successful attack!" << std::endl;
        std::cout << "Your " << creature.getName() << " received 100 EXP" << std::endl;
        std::cout << "Enemy " << en.getName() << " took "<< creature.getDamage()*creature.getMnsPower()*factorTypes(creature,en) << " damage" << std::endl;
        std::cout << "Your " << creature.getName() << " has " << creature.getUsesOfSPower() << " super attacks left." << std::endl;
        if(en.getHp() <= 0){
            std::vector<Creature> vector;
            std::cout << "Enemy " << en.getName() << " loses consciousness! "<< std::endl;
            if(enemy.getCreatures().size() == 1){
                setBattleend(true);
                return;
            }
            for(int i = 0; i < enemy.getCreatures().size(); i++){
                if(&enemy.getCreatures().at(i) != &en){
                    vector.push_back(enemy.getCreatures().at(i));
                }
            }
            enemy.setCreatures(vector);
        }
    }
}

double Battle::factorTypes(Creature c1, Creature c2) {
    if(c1.getType() == 1){
        if(c2.getType() == 1)
            return 0.7;
        if(c2.getType() == 2)
            return 1.3;
        if(c2.getType() == 3)
            return 1;
        if(c2.getType() == 4)
            return 1.3;
        if(c2.getType() == 5)
            return 1;
        if(c2.getType() == 6)
            return 1;
    }
    if(c1.getType() == 2){
        if(c2.getType() == 1)
            return 1;
        if(c2.getType() == 2)
            return 1;
        if(c2.getType() == 3)
            return 0.7;
        if(c2.getType() == 4)
            return 1.3;
        if(c2.getType() == 5)
            return 1.3;
        if(c2.getType() == 6)
            return 1.3;
    }
    if(c1.getType() == 3){
        if(c2.getType() == 1)
            return 1;
        if(c2.getType() == 2)
            return 0.7;
        if(c2.getType() == 3)
            return 1;
        if(c2.getType() == 4)
            return 1;
        if(c2.getType() == 5)
            return 1.3;
        if(c2.getType() == 6)
            return 0.7;
    }
    if(c1.getType() == 4){
        if(c2.getType() == 1)
            return 0.7;
        if(c2.getType() == 2)
            return 0.7;
        if(c2.getType() == 3)
            return 1;
        if(c2.getType() == 4)
            return 1;
        if(c2.getType() == 5)
            return 1.3;
        if(c2.getType() == 6)
            return 1.3;
    }
    if(c1.getType() == 5){
        if(c2.getType() == 1)
            return 0.7;
        if(c2.getType() == 2)
            return 1.3;
        if(c2.getType() == 3)
            return 1;
        if(c2.getType() == 4)
            return 0.7;
        if(c2.getType() == 5)
            return 0.7;
        if(c2.getType() == 6)
            return 1;
    }
    if(c1.getType() == 6){
        if(c2.getType() == 1)
            return 1.3;
        if(c2.getType() == 2)
            return 1;
        if(c2.getType() == 3)
            return 1.3;
        if(c2.getType() == 4)
            return 0.7;
        if(c2.getType() == 5)
            return 1;
        if(c2.getType() == 6)
            return 0.7;
    }
    return 1;
}

void Battle::EnemyTurn() {
    std::cout << std::endl;
    std::cout << "====================" << std::endl;
    std::rand();
    srand(time(NULL));
    int creature = rand() % enemy.getCreatures().size();
    int count_action;
    if(enemy.getCreatures().at(creature).getExp() >= 100)
        count_action = 2;
    else count_action = 1;
    int action = rand() % count_action;
    if(action == 1){
        evoEnemy(const_cast<Creature &>(enemy.getCreatures().at(creature)));
    }
    if(action == 0){
        int atCreat = rand() % 4;
        int shave;
        if(enemy.getCreatures().at(creature).getUsesOfSPower() > 0)
            shave = 2;
        else shave = 1;
        int typAtaki = rand() % shave;
        if(typAtaki == 0){
            int random = rand() % 100;
            if(ActiveCreatures.at(atCreat).getAgility() <= 20){
                if(random <= 10){
                    std::cout << "Your creature dodged the enemy attack!" << std::endl;
                    std::cout << "====================" << std::endl;
                    return;
                }
            }
            if(ActiveCreatures.at(atCreat).getAgility() > 20 && ActiveCreatures.at(atCreat).getAgility() <= 40){
                if(random <= 20){
                    std::cout << "Your creature dodged the enemy attack!" << std::endl;
                    std::cout << "====================" << std::endl;
                    return;
                }
            }
            if(ActiveCreatures.at(atCreat).getAgility() > 40 && ActiveCreatures.at(atCreat).getAgility() <= 60){
                if(random <= 30){
                    std::cout << "Your creature dodged the enemy attack!" << std::endl;
                    std::cout << "====================" << std::endl;
                    return;
                }
            }
            if(ActiveCreatures.at(atCreat).getAgility() > 60){
                if(random <= 50){
                    std::cout << "Your creature dodged the enemy attack!" << std::endl;
                    std::cout << "====================" << std::endl;
                    return;
                }
            }
            ActiveCreatures.at(atCreat).setHp(ActiveCreatures.at(atCreat).getHp() - enemy.getCreatures().at(creature).getDamage() * getDiff() * factorTypes(enemy.getCreatures().at(creature),ActiveCreatures.at(atCreat)));
            std::cout << "Your " << ActiveCreatures.at(atCreat).getName() <<" was attacked!" << std::endl;
            std::cout << ActiveCreatures.at(atCreat).getName() << " taked "<< enemy.getCreatures().at(creature).getDamage() * getDiff() *
                                                                              factorTypes(enemy.getCreatures().at(creature),ActiveCreatures.at(atCreat)) << " damage!" << std::endl;
            if(ActiveCreatures.at(atCreat).getHp() <= 0){
                ActiveCreatures.at(atCreat).setAlive(false);
                std::cout << "Your " << ActiveCreatures.at(atCreat).getName() <<" loses consciousness!" << std::endl;
            }
            std::cout << "====================" << std::endl;
            return;
        }
        if(typAtaki == 1){
            superAttackEnemy(const_cast<std::vector<Creature> &>(enemy.getCreatures()), creature,atCreat);
        }
    }
    std::cout << "====================" << std::endl;
}

void Battle::evoEnemy(Creature &creature) {
        creature.setDamage(creature.getDamage() + 10);
        creature.setAgility(creature.getAgility() + 10);
        creature.setExp(creature.getExp() - 100);
        creature.setLvl(creature.getLvl() + 1);
}

void Battle::superAttackEnemy(std::vector<Creature> &vec, int poz, int cel) {
    if(vec.at(poz).isPowerDefend()){
        vec.at(poz).setAgility(vec.at(poz).getAgility() + 10);
        vec.at(poz).setUsesOfSPower(vec.at(poz).getUsesOfSPower() - 1);
        std::cout << "Enemy " << vec.at(poz).getName() << " used super power Defend!" << std::endl;
    } else{
        int random = rand() % 100;
        if(ActiveCreatures.at(cel).getAgility() <= 20){
            if(random <= 10){
                std::cout << "Your creature dodged the enemy attack!" << std::endl;
                return;
            }
        }
        if(ActiveCreatures.at(cel).getAgility() > 20 && ActiveCreatures.at(cel).getAgility() <= 40){
            if(random <= 20){
                std::cout << "Your creature dodged the enemy attack!" << std::endl;
                return;
            }
        }
        if(ActiveCreatures.at(cel).getAgility() > 40 && ActiveCreatures.at(cel).getAgility() <= 60){
            if(random <= 30){
                std::cout << "Your creature dodged the enemy attack!" << std::endl;
                return;
            }
        }
        if(ActiveCreatures.at(cel).getAgility() > 60){
            if(random <= 50){
                std::cout << "Your creature dodged the enemy attack!" << std::endl;
                return;
            }
        }
        vec.at(poz).setUsesOfSPower(vec.at(poz).getUsesOfSPower() - 1);
        ActiveCreatures.at(cel).setHp(ActiveCreatures.at(cel).getHp() - vec.at(poz).getDamage() * vec.at(poz).getMnsPower() * getDiff() * factorTypes(vec.at(poz),ActiveCreatures.at(cel)));
        std::cout << "Your " << ActiveCreatures.at(cel).getName() <<" was super attacked!" << std::endl;
        std::cout << ActiveCreatures.at(cel).getName() << " taked "<< vec.at(poz).getDamage() * getDiff() *
                                                                          factorTypes(vec.at(poz),ActiveCreatures.at(cel)) * vec.at(poz).getMnsPower() << " damage!" << std::endl;
        if(ActiveCreatures.at(cel).getHp() <= 0){
            ActiveCreatures.at(cel).setAlive(false);
            std::cout << "Your " << ActiveCreatures.at(cel).getName() <<" loses consciousness!" << std::endl;
        }
    }
}

bool Battle::isBattleend() const {
    return battleend;
}

void Battle::setBattleend(bool battleend) {
    Battle::battleend = battleend;
}

double Battle::getDiff() const {
    return diff;
}

void Battle::resetAllCreatures() {
    std::for_each(ActiveCreatures.begin(), ActiveCreatures.end(), [](Creature &creature){
        creature.setHp(creature.getMaxhp());
        creature.setAgility(creature.getMaxAbility());
        creature.setDamage(creature.getMaxDamage());
        creature.setUsesOfSPower(2);
        creature.setAlive(true);
    });
    std::for_each(AllCreatures.begin(), AllCreatures.end(), [](Creature &creature){
        creature.setHp(creature.getMaxhp());
        creature.setAgility(creature.getMaxAbility());
        creature.setDamage(creature.getMaxDamage());
        creature.setUsesOfSPower(2);
        creature.setAlive(true);
    });
    for(int i = 0; i < AllCreatures.size(); i++){
        for(int j = 0; j < ActiveCreatures.size(); j++){
            if(AllCreatures.at(i).getName() == ActiveCreatures.at(j).getName()){
                AllCreatures.at(i) = ActiveCreatures.at(j);
                break;
            }
        }
    }
    hero.setCreatures(AllCreatures);
}

void Battle::saveProgress() {
    std::fstream fileOut;
    fileOut.open(hero.getName()+".txt",std::ios::out);
    if(fileOut.is_open()){
        fileOut << hero.getName() << " " << hero.getDifficulty() << " " << id << '\n';
        for(int i = 0; i < hero.getCreatures().size(); i++) {
            fileOut << hero.getCreatures().at(i).getName() << " " << hero.getCreatures().at(i).getLvl() << " "
                    << hero.getCreatures().at(i).getExp() << " " << hero.getCreatures().at(i).getMaxhp() << " "
                    << hero.getCreatures().at(i).getMaxDamage() << " " << hero.getCreatures().at(i).getMaxAbility()
                    << '\n';
        }
        for(int i = 0; i < hero.getEnemys().size(); i++){
            for(int j = 0; j < hero.getEnemys().at(i).getCreatures().size(); j++){
                fileOut << hero.getEnemys().at(i).getCreatures().at(j).getName() << '\n';
            }
        }
        fileOut.close();
    }
}

bool Battle::isContinueBattle() const {
    return continueBattle;
}

const Hero &Battle::getHero() const {
    return hero;
}

void Battle::ConfigEnemy() {
    if(id == 2){
        std::vector<Creature> crs;
        std::for_each(enemy.getCreatures().begin(), enemy.getCreatures().end(), [&crs](Creature creature){
            crs.push_back(creature);
        });
        std::for_each(crs.begin(), crs.end(), [this](Creature &creature){
            for(int i = 0; i < 2; i++)
                evoEnemy(creature);
        });
        enemy.setCreatures(crs);
    }
    if(id == 3){
        std::vector<Creature> crs;
        std::for_each(enemy.getCreatures().begin(), enemy.getCreatures().end(), [&crs](Creature creature){
            crs.push_back(creature);
        });
        std::for_each(crs.begin(), crs.end(), [this](Creature &creature){
            for(int i = 0; i < 4; i++)
                evoEnemy(creature);
        });
        enemy.setCreatures(crs);
    }
    if(id == 4){
        std::vector<Creature> crs;
        std::for_each(enemy.getCreatures().begin(), enemy.getCreatures().end(), [&crs](Creature creature){
            crs.push_back(creature);
        });
        std::for_each(crs.begin(), crs.end(), [this](Creature &creature){
            for(int i = 0; i < 6; i++)
                evoEnemy(creature);
        });
        enemy.setCreatures(crs);
    }
}
