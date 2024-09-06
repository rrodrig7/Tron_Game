#ifndef GAME_H
#define	GAME_H

#include "init.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    //FUNCTION PROTOTYPES-----------------------------------------------------
    
    //accepts commands and moves player
    void move_player(struct tron *tron_player, char grid[row][col], \
            int pgrid[row][col]);
    void test_winorloss(struct tron *tron_player, struct tron *tron_opponent);
    
    //------------------------------------------------------------------------

   


#ifdef	__cplusplus
}
#endif

#endif	/* GAME_H */

