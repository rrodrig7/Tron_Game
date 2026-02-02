/* game.c */

#include <unistd.h>
#include <ncurses.h>
#include "game.h"
#include "display.h"

#define TRAIL_LENGTH 100 // Desired length of the trail

// Helper function to add a new trail segment
void add_trail_segment(struct tron *tron_player, char grid[row][col], int pgrid[row][col]) {
    int x = tron_player->xpos;
    int y = tron_player->ypos;

    // Mark the grid and pgrid
    grid[y][x] = 'P';
    pgrid[y][x] = ++tron_player->light_pos;
}

// Helper function to remove the oldest trail segment by light index
void remove_oldest_trail_segment(struct tron *tron_player, char grid[row][col], int pgrid[row][col]) {
    if ((tron_player->light_pos - TRAIL_LENGTH) <= 0) return;

    int target = tron_player->light_pos - TRAIL_LENGTH;
    for (int y = 0; y < row; y++) {
        for (int x = 0; x < col; x++) {
            if (pgrid[y][x] == target) {
                pgrid[y][x] = 0;
                grid[y][x] = ' ';
                mvaddch(y, x, ' ');
                return;
            }
        }
    }
}

// Function to move player
void move_player(struct tron *tron_player, char grid[row][col], int pgrid[row][col]) {
    int key;
    // Add block for player
    attron(tron_player->color);
    mvaddch(tron_player->ypos, tron_player->xpos, ACS_DIAMOND);

    // Initialize nodelay
    nodelay(stdscr, TRUE);
    // Refresh screen to show last block before game terminates
    refresh();

    // Sleep to slow down the game
    usleep(tron_player->speed);

    // Get new key for new move
    key = getch();

    // Update direction based on key press
    switch(key) {
        case KEY_UP:
            if(tron_player->direction != KEY_DOWN) tron_player->direction = KEY_UP;
            break;
        case KEY_DOWN:
            if(tron_player->direction != KEY_UP) tron_player->direction = KEY_DOWN;
            break;
        case KEY_RIGHT:
            if(tron_player->direction != KEY_LEFT) tron_player->direction = KEY_RIGHT;
            break;
        case KEY_LEFT:
            if(tron_player->direction != KEY_RIGHT) tron_player->direction = KEY_LEFT;
            break;
        default:
            // No change in direction
            break;
    }

    // Move player
    if (tron_player->direction == KEY_UP) tron_player->ypos--;
    else if (tron_player->direction == KEY_DOWN) tron_player->ypos++;
    else if (tron_player->direction == KEY_RIGHT) tron_player->xpos++;
    else if (tron_player->direction == KEY_LEFT) tron_player->xpos--;

    // Check boundaries
    if (tron_player->ypos < 0 || tron_player->ypos >= row || tron_player->xpos < 0 || tron_player->xpos >= col) {
        tron_player->lose = TRUE;
    }

    // Check if the current position collides with the trail or grid
    if (grid[tron_player->ypos][tron_player->xpos] != ' ') {
        tron_player->lose = TRUE;
    }

    // Manage the trail
    if (grid[tron_player->ypos][tron_player->xpos] == ' ') {
        add_trail_segment(tron_player, grid, pgrid);
        remove_oldest_trail_segment(tron_player, grid, pgrid);
    }


    // Refresh the screen
    refresh();
}

void test_winorloss(struct tron *tron_player, struct tron *tron_opponent) {
    //Call functions to open win or loss screen
    if(tron_player -> lose == TRUE)             //
        loss();                                 //
    else                                        //
        win();                                  //
    //-----------------------------------------

    //getch to open and keep win or loss screen before termination
    getch();

    // set timer for automatic win/loss screen termination
    usleep(2000000);

    //end the window
    endwin();
}
