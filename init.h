/* 
 * File:   init.h
 *
 * Created on December 9, 2013, 6:55 PM
 */

#ifndef INIT_H
#define	INIT_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    extern int row, col;
    
    struct tron {
        int color;
        bool light;
        bool missiles;
        int xpos;
        int ypos;
        int direction;
        int speed;
        int light_length;
        bool disc_attack;
        int disk_position;
        int light_pos;
        bool lose;
    };
    //FUNCTION PROTOTYPES---------------------------------------------------
    
    void init_curses(void);
    
    //starts randomizer
    void init_rand(void);
    
    //initializes grid
    void init_grid(struct tron *tron_player, struct tron *tron_opponent, \
              char grid[row][col], int pgrid[row][col], int ogrid[row][col]);
    
    //initializes the tron_player structure
    void init_player(struct tron *tron_player);
    
    //initializes the tron_opponent structure
    void init_opponent(struct tron *tron_opponent);

    //----------------------------------------------------------------------
#ifdef	__cplusplus
}
#endif

#endif	/* INIT_H */
