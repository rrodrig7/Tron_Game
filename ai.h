
#ifndef AI_H
#define	AI_H

#include "init.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
    //FUNCTION PROTOTYPES-----------------------------------------------------

    typedef struct Node {
        int x, y;
        int g, h, f;
        struct Node *parent;
    } Node;

    // void move_opponent(struct tron *tron_opponent, char grid[row][col], \
    //         int ogrid[row][col]);
    //void move_opponent(struct tron *tron_opponent, char grid[row][col], int ogrid[row][col], int player_xpos, int player_ypos);

    void move_opponent(struct tron *tron_opponent, char grid[row][col], int ogrid[row][col], int pgrid[row][col]);
    //------------------------------------------------------------------------
#ifdef	__cplusplus
}
#endif

#endif	/* AI_H */

