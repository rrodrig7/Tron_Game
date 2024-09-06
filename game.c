/* game.c */

#include <unistd.h>
#include <ncurses.h>
#include "game.h"
#include "display.h"

#define TRAIL_LENGTH 100 // Desired length of the trail

// Helper function to add a new trail segment
void add_trail_segment(struct tron *tron_player, char grid[row][col], int pgrid[row][col], int *trail_x, int *trail_y, int *trail_index, int *trail_count) {
    int x = tron_player->xpos;
    int y = tron_player->ypos;

    // Add new segment to the circular buffer
    trail_x[*trail_index] = x;
    trail_y[*trail_index] = y;

    // Update index and trail count
    *trail_index = (*trail_index + 1) % TRAIL_LENGTH;
    if (*trail_count < TRAIL_LENGTH) {
        (*trail_count)++;
    }

    // Mark the grid and pgrid
    grid[y][x] = 'P';
    pgrid[y][x] = tron_player->light_pos++;
}

// Helper function to remove the oldest trail segment
void remove_oldest_trail_segment(char grid[row][col], int pgrid[row][col], int *trail_x, int *trail_y, int *trail_index, int *trail_count) {
    if (*trail_count == 0) return; // Nothing to remove if trail is empty

    // Calculate the index of the oldest trail segment
    int oldest_index = (*trail_index - *trail_count + TRAIL_LENGTH) % TRAIL_LENGTH;
    int x = trail_x[oldest_index];
    int y = trail_y[oldest_index];

    // Remove the segment from grid and pgrid
    grid[y][x] = ' ';
    pgrid[y][x] = 0;
    mvaddch(y, x, ' ');
    trail_count--;
}

// Function to move player
void move_player(struct tron *tron_player, char grid[row][col], int pgrid[row][col]) {
    int key;
    static int trail_x[TRAIL_LENGTH]; // Circular buffer for x positions
    static int trail_y[TRAIL_LENGTH]; // Circular buffer for y positions
    static int trail_index = 0;       // Index for circular buffer
    static int trail_count = 0;       // Number of segments in the trail

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
        add_trail_segment(tron_player, grid, pgrid, trail_x, trail_y, &trail_index, &trail_count);
        if (trail_count == TRAIL_LENGTH) {
            remove_oldest_trail_segment(grid, pgrid, trail_x, trail_y, &trail_index, &trail_count);
        }
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
