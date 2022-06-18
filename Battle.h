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

    /**
     * Konstruktor ten przechodzi bezpośrednio do tworzenia i głównej konfiguracji całej bitwy.
     * Tutaj stwory gracza są rozdzielane na określone komórki,
     * a także resetuje wszystkie statystyki stworzeń do standardu, a także konfigurację trudności.
     * @param hero Bohater, który będzie walczył.
     * @param enemy Wróg, z którym bohater będzie walczył
     * @param id numer bitwy
     */
    Battle(const Hero &hero, const Enemy &enemy, int id);


    /**
     * Ta metoda odpowiada za przebieg ruchów gracza i przeciwnika,
     * a także za zakończenie tej samej bitwy, niezależnie od tego,
     * czy jest to porażka, czy zwycięstwo gracza.
     */
    void start();


    /**
     * Ta metoda jest odpowiedzialna za resetowanie wszystkich cech stworzeń
     * do ich standardów, zgodnie z poziomem i cechami,
     * które gracz pompował podczas gry.
     */
    void resetAllCreatures();


    /**
     *Ta metoda jest tabelką oddziaływań.
     * Na podstawie dwóch stworzeń, gdzie pierwsza jest atakującym,
     * a druga obrońcą, obliczany jest double, który później będzie mnożnikiem obrażeń.
     * @param c1 Stworzenie atakujące
     * @param c2 Stworzenie obrońca
     * @return double mnożnik obrażeń
     */
    double factorTypes(Creature c1, Creature c2);


    /**
     * Ta metoda odpowiada za zapisywanie postępów gracza.
     * Możesz zapisać grę dopiero po zakończeniu bitwy, a liczba bitew, które gracz już ukończył, jest zapisywana w postępach gracza.
     * Wszystkie cechy stworzeń gracza i wszyscy przeciwnicy gracza są również zapisywane.
     * Zapisy później mają nazwę gracza (bohatera), którą gracz nadał mu w momencie jego tworzenia.
     */
    void saveProgress();


    /**
     *Ta metoda odpowiada za rozpoczęcie tury gracza,
     * gdzie graczowi wyświetlane są informacje o swoich przeciwnikach
     * oraz lista jego aktywnych stworzeń w bitwie.
     */
    void PlayerTurn();


    /**
     * Ta metoda jest odpowiedzialna za zastąpienie aktywnego stwora w bitwie innym z listy gracza,
     * którą gracz stworzył podczas tworzenia bohatera.
     * Na tej liście podświetlone są tylko te stworzenia, które nie biorą udziału w bitwie.
     * @param creature Stworzenie do zastąpienia.
     */
    void replaceCreature(Creature &creature);


    /**
     * Ta metoda odpowiada za ewolucję stwora gracza,
     * gdzie gracz może wybrać, które cechy zostaną ulepszone z stwora.
     * @param creature Stworzenie, które będzie ewoluować.
     */
    void evoCreature(Creature &creature);


    /**
     * Ta metoda odpowiada za wyświetlanie wszystkich aktywnych informacji o stworzeniu,
     * a także wybór kolejnych akcji gracza z tym stworem.
     * @param creature Stworzenie, którego informacje zostaną wyświetlone i jakie czynności zostaną z nim wykonane w następnej kolejności.
     */
    void CreatureChoose(Creature &creature);


    /**
     *Ta metoda odpowiada za wybór wrogiego stwora, który ma zostać zaatakowany,
     * a także wybór ataku, który zostanie użyty.
     * @param creature Stworzenie, które zaatakuje.
     */
    void attackCreature(Creature &creature);


    /**
     * Ta metoda odpowiada za atak typu normalnego.
     * @param myCreature Stwór gracza do zaatakowania
     * @param enemyCreature Wrogie stworzenie, które otrzyma atak
     */
    void normalAttack(Creature &myCreature, Creature &enemyCreature);


    /**
     * Ta metoda odpowiada za atak supertypu, który każde stworzenie posiada w ograniczonej ilości (2)
     * @param creature Stwór gracza do zaatakowania
     * @param enemyCreature Wrogie stworzenie, które otrzyma atak
     */
    void superPowerAttack(Creature &creature, Creature &enemyCreature);


    /**
     * Ta metoda odpowiada za ruch przeciwnika.
     * Generuje działanie wroga na gracza całkowicie losowo.
     */
    void EnemyTurn();


    /**
     * Ta metoda odpowiada za konfigurowanie wrogich stworów na podstawie postępów gracza.
     * Dla wroga ustawione są pewne poziomy stworzeń i ulepszone cechy.
     */
    void ConfigEnemy();


    /**
     * Ta metoda odpowiada za ewolucję stwora przeciwnika.
     * Ewolucja wroga obejmuje poprawę obrażeń i zręczności stworzenia.
     * Ilość zdrowia wroga nie ulega ewolucji, ponieważ zgodnie z logiką rozgrywki istoty nie mogą regenerować swojego zdrowia podczas bitwy,
     * co oznacza, że ewolucja zdrowia jest w większości bezużyteczne dla wroga.
     * @param creature Stworzenie, które będzie ewoluować.
     */
    void evoEnemy(Creature &creature);


    /**
     * Ta metoda odpowiada za atak wroga supertypu, który każde stworzenie posiada w ograniczonej ilości (2)
     * Ta metoda nie jest zbyt wygodna, ale można ją wygodniej przepisać.
     * @param vec Wektor stworzeń wroga
     * @param poz Pozycja w wektorze stworzenia
     * @param cel Pozycja stwora, który ma zostać zaatakowany
     */
    void superAttackEnemy(std::vector<Creature> &vec, int poz, int cel);


    /**
     * Zwykły getter, który zwraca Gracza(Bohatera)
     * @return zwraca bohatera
     */
    const Hero &getHero() const;


    /**
     * Zwykły getter, który zwraca poziom trudności bitwy
     * @return poziom trudności bitwy
     */
    double getDiff() const;


    /**
     * Getter, który odpowiada za zwracenie bool,
     * który w głównej klasie zadecyduje, czy kontynuować grę dalej, czy nie.
     * @return kontynuuj czy nie
     */
    bool isContinueBattle() const;


    /**
     * Logika, która mówi, czy bitwa się skończyła,
     * czy nie, zmienia swoje znaczenie dopiero wtedy,
     * gdy przeciwnik zostanie pokonany.
     * @return true or false
     */
    bool isBattleend() const;


    /**
     * Logika opisana powyżej, tutaj jest zmiana jej
     * @param battleend true or false
     */
    void setBattleend(bool battleend);

};


#endif //PROJECT___BATTLE_H
