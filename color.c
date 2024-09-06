#include "color.h"


void initialize_color(void) {
    
    /*******************COLORS*******************/
    //initialize start colors
    start_color();
    
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    /********************************************/
    
    return;
}
