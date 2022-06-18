#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

#include "Creature.h"
#include "Hero.h"
#include "Enemy.h"
#include "Battle.h"


std::vector<Creature> PullOfCreatures;
Hero MainHero;
static int battlecounter = 0;


void HeroCreateChoseCreatures(std::vector<Creature>&);

/**
 * Ta metoda wyświetla informacje o wybranym stworzeniu i pozwala wybrać następną akcję z tym stworem.
 * @param creature Wybrane stworzenie
 * @param HerosCreatures wektor, w który należy zapisać to stworzenie
 */
void chosenCreature(Creature &creature, std::vector<Creature> &HerosCreatures){
    creature.info();
    std::cout << "1)Add to Hero" << std::endl;
    std::cout << "2)Return" << std::endl;
    int in;
    std::cin >> in;
    switch (in) {
        case 1:
            HerosCreatures.push_back(creature);
            std::for_each(PullOfCreatures.begin(), PullOfCreatures.end(), [&creature](Creature &cr){
                if(creature.getName() == cr.getName())
                    cr.setChosen(true);
            });
            std::cout << "Successfully added!" << std::endl;
            break;
        case 2:
            HeroCreateChoseCreatures(HerosCreatures);
            break;
        default:
            std::cout << "There is no such option!" << std::endl;
            chosenCreature(creature, HerosCreatures);
            break;
    }
}


/**
 * Ta metoda resetuje wszystkie wybrane stworzenia w głównym Pull'ie stworzeń
 * Jest to potrzebne do generowania przeciwników.
 */
void resetPull(){
    std::for_each(PullOfCreatures.begin(), PullOfCreatures.end(), [](Creature &creature){
        if(creature.isChosen())
            creature.setChosen(false);
    });
}


/**
 * Ta metoda wyświetla listę wszystkich stworzeń dostępnych do wyboru w drużynie gracza.
 * @param HerosCreatures wektor gracza, który jest przekazany dalej
 */
void HeroCreateChoseCreatures(std::vector<Creature> &HerosCreatures){
    std::vector<Creature> AvCreatures;
    int c = 1;
    std::for_each(PullOfCreatures.begin(), PullOfCreatures.end(), [&AvCreatures](Creature creature) {
       if(!creature.isChosen())
           AvCreatures.push_back(creature);
    });
    std::for_each(AvCreatures.begin(), AvCreatures.end(), [&c](Creature creature){
        std::cout << c << ")" << creature.getName() << std::endl;
            c++;
    });
    int in;
    std::cin >> in;
    if(in > c-1 || in < 1){
        std::cout << "There is no such option!" << std::endl;
        HeroCreateChoseCreatures(HerosCreatures);
        return;
    } else{
        chosenCreature(AvCreatures.at(in-1),HerosCreatures);
        return;
    }
}


/**
 * Ta metoda generuje wektor z wrogimi stworzeniami.
 * Powtórzenia stworzeń są dozwolone.
 * @return zwraca zgenerowany wektor
 */
std::vector<Creature> generateEnemyPull(){
    std::vector<Creature> pull;
    for(int i = 0; i < 4; i++)
        pull.push_back(PullOfCreatures.at(rand() % 14));
    return pull;
}


/**
 * Ta metoda odpowiada za stworzenie gracza, jeśli została wybrana opcja nowej gry.
 * @return zwara nowego gracza
 */
Hero CreateHero(){
    std::string HeroName;
    std::vector<Creature> HerosCreatures;
    int diff;
    std::cout << "Enter your Hero name" << std::endl;
    std::cin >> HeroName;
    for(int i = 1; i < 7; i++){
        std::cout << "Choose yours creatures (" << i << "/6)" <<std::endl;
        HeroCreateChoseCreatures(HerosCreatures);
    }
    resetPull();
    std::cout << "Choose game difficulty" << std::endl;
    std::cout << "1 - Easy" << std::endl;
    std::cout << "2 - Middle" << std::endl;
    std::cout << "3 - Hard" << std::endl;
    std::cin >> diff;
    std::vector<Enemy> Enemys;
    Enemys.emplace_back(generateEnemyPull());
    Enemys.emplace_back(generateEnemyPull());
    Enemys.emplace_back(generateEnemyPull());
    Enemys.emplace_back(generateEnemyPull());
    Hero hero = Hero(HeroName,HerosCreatures,Enemys,diff);
    return hero;
}


/**
 * Ta metoda odpowiada za odczytanie pliku zapisu, który został zapisany w określonym formacie.
 */
void readSave(){
    std::cout << "Enter save name" << std::endl;
    std::string saveName;
    std::cin >> saveName;
    std::fstream fileIn;
    fileIn.open(saveName+".txt",std::ios::in);
    if(fileIn.is_open()){
        std::string HeroName;
        std::vector<Creature> creatures;
        std::vector<Enemy> Enemys;
        int diff;
        fileIn >> HeroName >> diff >> battlecounter;
        for(int i = 0; i < 6; i++){
            std::string CreatureName;
            int lvl, exp, hp, damage, agil;
            fileIn >> CreatureName >> lvl >> exp >> hp >> damage >> agil;
            for(int j = 0; j < PullOfCreatures.size(); j++){
                if(PullOfCreatures.at(j).getName() == CreatureName){
                    Creature newCr = PullOfCreatures.at(j);
                    newCr.setLvl(lvl);
                    newCr.setExp(exp);
                    newCr.setMaxhp(hp);
                    newCr.setMaxDamage(damage);
                    newCr.setMaxAbility(agil);
                    newCr.setHp(newCr.getMaxhp());
                    newCr.setDamage(newCr.getMaxDamage());
                    newCr.setAgility(newCr.getMaxAbility());
                    creatures.push_back(newCr);
                    break;
                }
            }
        }
        std::vector<Creature> pull1, pull2, pull3, pull4;
        for(int i = 0; i < 4; i++){
            std::string CreatureName;
            fileIn >> CreatureName;
            for(int j = 0; j < PullOfCreatures.size(); j++){
                if(PullOfCreatures.at(j).getName() == CreatureName){
                    pull1.push_back(PullOfCreatures.at(j));
                    break;
                }
            }
        }
        for(int i = 0; i < 4; i++){
            std::string CreatureName;
            fileIn >> CreatureName;
            for(int j = 0; j < PullOfCreatures.size(); j++){
                if(PullOfCreatures.at(j).getName() == CreatureName){
                    pull2.push_back(PullOfCreatures.at(j));
                    break;
                }
            }
        }
        for(int i = 0; i < 4; i++){
            std::string CreatureName;
            fileIn >> CreatureName;
            for(int j = 0; j < PullOfCreatures.size(); j++){
                if(PullOfCreatures.at(j).getName() == CreatureName){
                    pull3.push_back(PullOfCreatures.at(j));
                    break;
                }
            }
        }
        for(int i = 0; i < 4; i++){
            std::string CreatureName;
            fileIn >> CreatureName;
            for(int j = 0; j < PullOfCreatures.size(); j++){
                if(PullOfCreatures.at(j).getName() == CreatureName){
                    pull4.push_back(PullOfCreatures.at(j));
                    break;
                }
            }
        }
        Enemys.emplace_back(pull1);
        Enemys.emplace_back(pull2);
        Enemys.emplace_back(pull3);
        Enemys.emplace_back(pull4);
        MainHero = Hero(HeroName,creatures,Enemys,diff);
        fileIn.close();
    } else {
        std::cout << "The file with this name was not found!" << std::endl;
        readSave();
        return;
    }
    std::cout << "Save was successful readed!" << std::endl;
}


/**
 * Metoda ta odpowiada za wyświetlenie krótkiego opisu gry przed jej rozpoczęciem.
 */
void gameRules(){
    std::cout << "Welcome to the CreaturesWorld!" << std::endl;
    std::cout << "This is a turn based combat game. Your task is to defeat enemy creatures with your brave team of creatures!" << std::endl;
    std::cout << "To do this, you need to pump and pay attention to the events of the battle." << std::endl;
    std::cout << "Each of the creatures has certain characteristics, such as agility, health, damage, and more." << std::endl;
    std::cout << "Creatures also have different elements, such as water, fire, earth, air, ice and steel." << std::endl;
    std::cout << "Each of these elements in one way or another acts on other elements, both to the best and to the worst." << std::endl;
    std::cout << "Battles take place in a 4v4 format, where your creatures must defeat the enemy! There are 4 total rounds in the game." << std::endl;
    std::cout << "A creature can evolve after reaching EXP 100" << std::endl;
    std::cout << "As a player, you can have 6 different creatures with completely different stats, it's all up to you!" << std::endl;
    std::cout << "Beat, upgrade, change, evolve, have fun!" << std::endl;
}


/**
 * Główna metoda odpowiadająca za rozpoczęcie i zakończenie gry.
 */
void startGame(){
    std::cout << "Welcome to the CreaturesWorld!" << std::endl;
    std::cout << "Choose action:" << std::endl;
    std::cout << "1)Load game" << std::endl;
    std::cout << "2)New game" << std::endl;
    int input;
    std::cin >> input;
    switch (input) {
        case 1:
            readSave();
            for(int i = 0; i < 4; i++){
                if(battlecounter == i){
                    Battle battle = Battle(MainHero,MainHero.getEnemys().at(i), battlecounter+1);
                    battle.start();
                    MainHero = battle.getHero();
                    if(!battle.isContinueBattle())
                        break;
                    battlecounter++;
                }
            }
            std::cout << "You have completed the whole game, you have won!" << std::endl;
            std::cout << "Congratulations!!!" << std::endl;
            break;
        case 2:
            MainHero = CreateHero();
            gameRules();
            for(int i = 0; i < 4; i++){
                battlecounter++;
                Battle battle = Battle(MainHero,MainHero.getEnemys().at(i), battlecounter);
                battle.start();
                MainHero = battle.getHero();
                if(!battle.isContinueBattle())
                    break;
            }
            std::cout << "You have completed the whole game, you have won!" << std::endl;
            std::cout << "Congratulations!!!" << std::endl;
            break;
        default:
            std::cout << "Bad option!" << std::endl;
            startGame();
            break;
    }
}

int main() {
    std::rand();
    srand(time(NULL));

    PullOfCreatures.emplace_back(2,"Buldyga","Creature living in caves, completely covered with cobblestones on the outside",
                                       200,20,10, true,"Can summon a cobblestone wall");
    PullOfCreatures.emplace_back(1,"Soml","The creature lives in coastal areas, a distinctive feature is a transparent bag of water in the belly area",
                                       100,30,40, false,"Spitting high pressure hot water");
    PullOfCreatures.emplace_back(6,"Weld","The creature lives near iron mines, outwardly looks like a metal box.",
                                       200,40,0, false,"Can collect metal from the ground and turning into metal spears to dream them into an enemy");
    PullOfCreatures.emplace_back(4,"Flame","The creature appears in places of large fires, looks like a cat, but with burning ears and a tail, leaves burning traces in the form of a cat's paw.",
                                       100,25,80, true,"Creates a wall of high-temperature fire, impervious to attacks");
    PullOfCreatures.emplace_back(3,"Golubs","A creature that lives in the upper atmosphere, looks like a large hawk, but the color of the plumage is white and blue",
                                       200,35,70, false,"Begins to fly around the enemy creating a zone of low pressure");
    PullOfCreatures.emplace_back(5,"Blibles","A creature that lives in the Arctic Circle, covered in razor-sharp pieces of ice",
                                       100,35,50, false,"Shoots solid and hard spikes of ice from the ground");
    PullOfCreatures.emplace_back(2,"Skwork","A creature that lives in swampy areas, completely covered in mud",
                                       150,20,10, true,"Creates a swamp under the enemy's feet (with a radius of 2m), thereby immobilizing the enemy");
    PullOfCreatures.emplace_back(2,"Bit","A creature that lives near oil refineries, looks like a drop",
                                       200,40,0, false,"Creates a bitumen barrier around the enemy, inside of which there are sharp spikes");
    PullOfCreatures.emplace_back(4,"Torch","It picks up near coal mines, a distinctive feature is a light on its head",
                                       100,10,80, true,"Kindles a light on the head, thereby blinding the enemy");
    PullOfCreatures.emplace_back(3,"Albatr","It lives near mountain peaks, a distinctive feature is small and completely black",
                                       100,35,80, false,"Lightning attacks the enemy in the air, inflicting a large number of air cuts.");
    PullOfCreatures.emplace_back(3,"Pulast","It lives in urban areas, a medium-sized bird with a strong beak",
                                       150,30,70, false,"Hits the enemy at high speed causing internal damage");
    PullOfCreatures.emplace_back(5,"Icetle","It lives in areas of low temperatures, it looks like a blue beetle",
                                       150,30,20, true,"Spreading its wings creates a wall of ice out of them");
    PullOfCreatures.emplace_back(6,"Kvarbos","Inhabits areas of magnetic ore formations, nondescript dark gray in appearance",
                                       200,10,35, true,"Creates magnetic waves suppressing the opponent's brain activity");
    PullOfCreatures.emplace_back(4,"Magnis","Feeds in areas of active volcanoes, looks like a lizard covered in stone with magma flows between stones",
                                       150,40,50, false,"Spews a stream of magma, causing burns to the enemy");
    PullOfCreatures.emplace_back(2,"Sands","Lives in desert areas, similar to coyote covered with sandy deposits",
                                       150,35,50, true,"Summons a whirlwind of sand");

    startGame();
}