#ifndef CELL_H
#define CELL_H

// cell_t is a cell
typedef struct
{
    enum {
        stateEmpty,
        stateAnt,
        stateAnthill,
        stateFood,
        stateWater
    } state; // State of the cell
    
    union {
        ant_t* ant;
        hill_t* hill;
        food_t* food;
    } content;

    unsigned short lastSeen; // Turn in which this cell was last seen. Can be useful for strategy
} cell_t;

// cell_t methods
cell_t *newCell();      
void clearCell(cell_t* c);                    
void destroyCell(cell_t *c);

#endif