#ifndef CONFIG_H
#define CONFIG_H
/*
This file stores constants that are used throughout the program,
it is designed specifically to prevent circular includes and compilation errors
*/


constexpr int MAPHEIGHT = 30; //constant size of the map
constexpr int MAPWIDTH = MAPHEIGHT * 2;//mulitply size of the map by 2 because ascii char are rectangular

#endif
