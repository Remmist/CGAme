//
// Created by r3mm1 on 13.06.2022.
//

#ifndef PROJECT___CREATURE_H
#define PROJECT___CREATURE_H

#include <string>

class Creature {
    /*
     * 1-woda
     * 2-ziemia
     * 3-powietrze
     * 4-ogień
     * 5-lód
     * 6-stal
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

    /**
     * Konstruktor ten jest odpowiedzialny za stworzenie stwora ze wszystkimi zdefiniowanymi polami,
     * które stwór musi mieć.
     * @param type typ stworzenia, typy są opisane powyżej
     * @param name imie stworzenia
     * @param desc krótki opis stworzenia
     * @param hp ilość zdrowia stworzenia
     * @param damage obrażenia stworzenia
     * @param agility na jego podstawie obliczona zostanie zręczność stworzenia, na podstawie której obliczona zostanie szansa na uniknięcie ataku wroga
     * @param powerDefend czy super moc stworzenia jest atakująca czy dla obrony
     * @param descOfSPower krótki opis super mocy strworzenia
     */
    Creature(int type, const std::string &name, const std::string &desc, int hp, int damage, int agility,
             bool powerDefend, const std::string &descOfSPower);



    /*
     * ============================================================================
     * Tutaj jest ogromny zestaw różnego rodzaju getterów i setterów,
     * nie sądzę, aby dokumentowanie każdego z nich miało sens,
     * ponieważ nazwy metod mówią same za siebie.
     * ============================================================================
     */
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


    /**
     * Ta metoda wyświetla informacje o stworzeniu podczas wybierania stworzeń dla bohatera.
     */
    void info();

    /**
     * Ta metoda wyświetla informacje o stworzeniu podczas walki z rozszerzonymi informacjami o cechach stwora.
     */
    void infoBattle();

};


#endif //PROJECT___CREATURE_H
