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
    /**
     * Ten konstruktor pozwala bezpośrednio stworzyć samego gracza,
     * który będzie zawierał imię bohatera, wektor stworzeń gracza, wektor przeciwników,
     * z którymi gracz będzie walczył przez całą grę,
     * a także złożoność samej gry, którą gracz wybrał.
     * @param name imie bohatera
     * @param creatures wektor stworzeń gracza
     * @param enemys wektor wrogów
     * @param difficulty złożoność gry
     */
    Hero(const std::string &name, const std::vector<Creature> &creatures, const std::vector<Enemy> &enemys,
         int difficulty);

    /**
     * Zwykły pusty konstruktor, jest to wymagane dla statycznego MainHero dla całej głównej klasy.
     */
    Hero();


    /*
     * Zwykły zestaw getterów i setterów.
     */
    const std::string &getName() const;

    const std::vector<Creature> getCreatures() const;

    void setCreatures(const std::vector<Creature> &creatures);

    int getDifficulty() const;

    const std::vector<Enemy> &getEnemys() const;

};


#endif //PROJECT___HERO_H
