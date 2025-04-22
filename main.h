//Standard Library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

//NCURSES
#include <curses.h>

//Data Structures
#include "game/data/card.h"
#include "game/data/deck.h"
#include "game/data/gameRules.h"

//File Read Utilities
#include "game/read/readDirectory.h"
#include "game/read/readTXT.h"
#include "game/read/readDecks.h"
#include "game/read/readDeck.h"

//Menu Handling

//Play Menu & its submenus
#include "game/menu/deckMenu.h"
#include "game/menu/playMenu.h"

//Main Menu
#include "game/menu/mainMenu.h"
