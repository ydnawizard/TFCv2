//Standard Library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <time.h>

//NCURSES
#include <curses.h>

//Data Structures
#include "game/data/card.c"
#include "game/data/deck.c"
#include "game/data/gameRules.c"
#include "game/data/gameState.c"

//Utilities
#include "game/util/bool.c"
#include "game/util/input.c"
#include "game/util/time.c"

//File Read Utilities
#include "game/util/read/readDirectory.c"
#include "game/util/read/readTXT.c"
#include "game/util/read/readDecks.c"
#include "game/util/read/readDeck.c"

//Game Loop
#include "game/main/cardStackHandler.c"
#include "game/main/clockHandler.c"
#include "game/main/game.c"

//Menu Handling

//Play Menu & its submenus
#include "game/menu/deckMenu.c"
#include "game/menu/timerMenu.c"
#include "game/menu/playMenu.c"


//Main Menu
#include "game/menu/mainMenu.c"
