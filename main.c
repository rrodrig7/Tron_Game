/* 
 * File:   main.c
 *
 */

//include directives
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "init.h"
#include "ai.h"
#include "display.h"
#include "game.h"

//initialize row and columns to be used in main
int row, col;

// Function to check for collisions
void check_collisions(struct tron *tron_player, struct tron *tron_opponent, char grid[row][col], int pgrid[row][col], int ogrid[row][col]) {
    // Check if player collides with opponent or opponent's tail
    if (tron_player->xpos == tron_opponent->xpos && tron_player->ypos == tron_opponent->ypos) {
        tron_player->lose = TRUE;
    }
    if (ogrid[tron_player->ypos][tron_player->xpos] != 0) {
        tron_player->lose = TRUE;
    }

    // Check if opponent collides with player or player's tail
    if (tron_opponent->xpos == tron_player->xpos && tron_opponent->ypos == tron_player->ypos) {
        tron_opponent->lose = TRUE;
    }
    if (pgrid[tron_opponent->ypos][tron_opponent->xpos] != 0) {
        tron_opponent->lose = TRUE;
    }
}

void run_game(void) {
    // Find rows and columns
    getmaxyx(stdscr, row, col);

    // Declare player structures AND GRID
    struct tron player;
    struct tron opponent;
    char grid[row][col];
    int pgrid[row][col];
    int ogrid[row][col];

    // Hook up pointers to player structures
    struct tron *tron_player = &player;
    struct tron *tron_opponent = &opponent;

    // Initialize player structure
    init_player(tron_player);
    // Initialize opponent structure
    init_opponent(tron_opponent);
    // Initialize the grid
    init_grid(tron_player, tron_opponent, grid, pgrid, ogrid);

    // Print the screen
    welcome();

    // set nodelay mode to false
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    // Run game loop
    while(tron_player->lose == FALSE && tron_opponent->lose == FALSE) {
        // Move the player
        move_player(tron_player, grid, pgrid);
        // Refresh screen after player moves
        refresh();

        // Move the opponent
        move_opponent(tron_opponent, grid, ogrid, pgrid);
        // Refresh screen after opponent moves
        refresh();

        // Check for collisions
        check_collisions(tron_player, tron_opponent, grid, pgrid, ogrid);
    }

    // Test win or loss
    test_winorloss(tron_player, tron_opponent);
}

int prompt_replay(void) {
    clear();
    nodelay(stdscr, FALSE); // Make getch() blocking
    int ch;
    while (1) {
        attron(COLOR_PAIR(3));
        mvprintw(row / 2, col / 2 - 10, "Play again? (y/n): ");
        refresh();
        ch = getch();
        if (ch == 'y' || ch == 'Y') {
            nodelay(stdscr, TRUE); // Restore non-blocking mode
            return 1;
        } else if (ch == 'n' || ch == 'N') {
            nodelay(stdscr, TRUE); // Restore non-blocking mode
            return 0;
        }
    }
}


//CALL MAIN FUNCTION
int main(void) {  
    //initialize curses functions etc.
    init_curses();

    int replay = 1;
    while (replay) {
        run_game();
        refresh();
        replay = prompt_replay();
        clear(); // Clear the screen for a new game
    }
    attron(COLOR_PAIR(3));
    mvprintw(row / 2, col / 2 - 5, "GOODBYE");
    refresh();
    usleep(1000000);

    // End curses mode
    endwin();
    // fclose(log_file);

    //end program
    return (EXIT_SUCCESS);
}
