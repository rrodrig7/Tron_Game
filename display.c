/* display.c */

/* Preprocessor directives */
#include<ncurses.h>
#include "display.h"
#include "init.h"
#include <stdlib.h>

void set_terminal_title(const char* title) {
    printf("\033]0;%s\007", title);
}

void welcome(void) {
    
    //SET SCREEN TITLE
    set_terminal_title("TRON");
    
    //initializes cbreak
    cbreak();
    
    //find midpoint
    getmaxyx(stdscr,row,col);
    
    //Center Screen Title Print and print in color
    
    attron(COLOR_PAIR(2));
    mvprintw((row/2)-1,(col-15)/2, "WELCOME TO TRON");
    attroff(COLOR_PAIR(2));
    
    attron(COLOR_PAIR(3));
    mvprintw((row/2)+3,(col-28)/2, "Press any Button to Continue");
    attroff(COLOR_PAIR(3));
    
    //getch to initialize screen changing
    getch();
    
    //clear welcome screen
    wclear(stdscr);
    
}

void win(void) {
    nodelay(stdscr, TRUE);
    
    //clear game screen
    wclear(stdscr);
    
    //print messages
    attron(COLOR_PAIR(2));
    mvprintw((row/2),(col/2)-6, "YOU WIN, USER");
    attroff(COLOR_PAIR(2));
}

void loss(void) {
    nodelay(stdscr, TRUE);
    
    //clear game screen
    wclear(stdscr);
    
    //print messages
    attron(COLOR_PAIR(4));
    mvprintw((row/2)-3,(col/2)-4, "GAME OVER");
    mvprintw((row/2),(col/2)-7, "YOU LOSE, USER");
    attroff(COLOR_PAIR(4));
}
