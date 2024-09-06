#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "init.h"
#include "color.h"

void init_curses(void) {

    //initialize the screen
    initscr();

    //enable keypad use in window
    keypad(stdscr, TRUE);

    //cursor set so no cursor is printed
    curs_set(0);  

    //noecho so program does not wait on input
    noecho();

    //initialize start colors
    initialize_color();

    //Initializes cbreak
    cbreak();
    //start randomizer for rest of function
    init_rand();
}

void init_rand(void) {
    //randomizes by computer time
    srand(time(NULL));
    return;
}


void init_player(struct tron *tron_player) {
    //ASSIGN VALUES TO THE STRUCTURE ELEMENTS 

    tron_player -> color         = COLOR_PAIR(6);
    tron_player -> light         = TRUE;
    tron_player -> xpos          = 10;
    tron_player -> ypos          = row/2;
    tron_player -> direction     = KEY_RIGHT;
    tron_player -> speed         = 50000;

    tron_player -> light_length  = 100;
    tron_player -> light_pos     = 0;
    tron_player -> lose           = FALSE;
}

void init_opponent(struct tron *tron_opponent) {
    //ASSIGN VALUES TO THE STRUCTURE ELEMENTS 

    tron_opponent -> color         = COLOR_PAIR(1);
    tron_opponent -> light         = TRUE;
    tron_opponent -> xpos          = col - 10;
    tron_opponent -> ypos          = row/2;
    tron_opponent -> direction     = KEY_LEFT;
    tron_opponent -> speed         = 50000;
    tron_opponent -> light_length  = 100; 
    tron_opponent -> light_pos     = 0;
    tron_opponent -> lose           = FALSE;
}

void init_grid(struct tron *tron_player, struct tron *tron_opponent, \
               char grid[row][col], int pgrid[row][col], int ogrid[row][col]) {
    //initialize grid with for loop
    for(int y = 0 ; y <= row-1 ; y++ ) {
        for(int x = 0 ; x <= col-1 ; x++ ){
            grid[y][x]= ' ';
        }
    }

    //set the starting positions by occupying a space with P or O
    grid[tron_player -> ypos][tron_player ->xpos] = 'P';  
    grid[tron_opponent -> ypos][tron_opponent ->xpos] = 'O';

    //INITIALIZE THE PGRID=======================================

    //for loop to initialize the PGRID
    for(int y = 0 ; y <= row-1 ; y++ ) {
        for(int x = 0 ; x <= col-1 ; x++ ){
            pgrid[y][x]= 0;
        }
    }
    //assign value to starting point
    pgrid[tron_player -> ypos][tron_player ->xpos] = 1;

    //INITIALIZE THE OGRID=======================================

    //for loop to initialize the OGRID
    for(int y = 0 ; y <= row-1 ; y++ ) {
        for(int x = 0 ; x <= col-1 ; x++ ){
            ogrid[y][x]= 0;
        }
    }
    //assign value to starting point
    ogrid[tron_opponent -> ypos][tron_opponent ->xpos] = 1;

    //===========================================================
}
