#ifndef CONFIG_H
#define CONFIG_H
/*
This file stores constants that are used throughout the program.
*/

//map dimensions
constexpr int MAPHEIGHT = 30;
constexpr int MAPWIDTH = MAPHEIGHT * 2; //mulitply width of the map by 2 because ascii char are rectangular

//round limit
constexpr int ROUND_LIMIT = 50;

//default stats
constexpr int DEFAULT_HP = 100; //starting, maximum HP
constexpr int DEFAULT_ATTACK_DAMAGE = 5; //damage of the default attack
constexpr int DEFAULT_ATTACK_RANGE = 1; //range of the default attack
constexpr int DEFAULT_ATTACK_ENERGY_COST = 1; //energy cost of the default attack
constexpr int DEFAULT_ENERGY = 10; //default energy
constexpr int DEFAULT_CURRENCY = 1000; //starting money
constexpr int PASSIVE_INCOME = 500; //income gained after every turn

//game map characters
constexpr char BLANK = '.';
constexpr char TREE[3] = "##";
constexpr char SWAMP[3] = "##";
constexpr char CLIFF[3] = "##";
constexpr char BUSH[3] = "##";

#endif
