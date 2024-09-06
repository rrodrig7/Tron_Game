#include <ncurses.h>
#include <stdlib.h>
#include "ai.h"
#include "init.h"

// Helper function to determine if a move is valid
int is_valid_move(int x, int y, char grid[row][col], int ogrid[row][col], int pgrid[row][col]) {
    // Check boundaries
    if (x < 0 || x >= col || y < 0 || y >= row) {
        return 0;
    }
    // Check if move collides with trail or walls
    if (grid[y][x] != ' ' || ogrid[y][x] != 0 || pgrid[y][x] != 0) {
        return 0;
    }
    return 1;
}

// Function to move opponent
void move_opponent(struct tron *tron_opponent, char grid[row][col], int ogrid[row][col], int pgrid[row][col]) {
    // Define possible moves and their corresponding directions
    int possible_moves[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; // Up, Down, Left, Right
    int direction_keys[4] = { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT };
    int valid_moves[4]; // Array to store indices of valid moves
    int move_count = 0;
    int next_x, next_y;

    // Check if the current direction is valid
    next_x = tron_opponent->xpos + possible_moves[tron_opponent->direction - KEY_UP][1];
    next_y = tron_opponent->ypos + possible_moves[tron_opponent->direction - KEY_UP][0];
    
    // Determine if the move in the current direction is valid
    if (is_valid_move(next_x, next_y, grid, ogrid, pgrid)) {
        tron_opponent->xpos = next_x;
        tron_opponent->ypos = next_y;
    } else {
        // Check all possible moves
        for (int i = 0; i < 4; i++) {
            next_x = tron_opponent->xpos + possible_moves[i][1];
            next_y = tron_opponent->ypos + possible_moves[i][0];
            if (is_valid_move(next_x, next_y, grid, ogrid, pgrid) && direction_keys[i] != -tron_opponent->direction) {
                valid_moves[move_count++] = i;
            }
        }

        // If there are valid moves, choose one randomly
        if (move_count > 0) {
            int chosen_move = valid_moves[rand() % move_count];
            tron_opponent->direction = direction_keys[chosen_move];
            next_x = tron_opponent->xpos + possible_moves[chosen_move][1];
            next_y = tron_opponent->ypos + possible_moves[chosen_move][0];
            tron_opponent->xpos = next_x;
            tron_opponent->ypos = next_y;
        } else {
            // No valid moves, opponent loses
            tron_opponent->lose = TRUE;
        }
    }

    // Draw the block for the opponent's new position
    attron(tron_opponent->color);
    mvaddch(tron_opponent->ypos, tron_opponent->xpos, ACS_DIAMOND);
    grid[tron_opponent->ypos][tron_opponent->xpos] = 'O';
    ogrid[tron_opponent->ypos][tron_opponent->xpos] = tron_opponent->light_pos++;

    // Cleanup old light trail
    if ((tron_opponent->light_pos - 100) >= 0) {
        for (int y = 0; y < row; y++) {
            for (int x = 0; x < col; x++) {
                if (ogrid[y][x] == tron_opponent->light_pos - 100) {
                    ogrid[y][x] = 0;
                    grid[y][x] = ' ';
                    mvaddch(y, x, ' ');
                }
            }
        }
    }

    // Refresh the screen
    refresh();
}
