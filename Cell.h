#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

class Cell
{
    int state; // state of the cell; 0: Empty, 1: Tree, 2: Burning tree 
public:
    Cell();
    int getStateValue();
    void setStateValue(int stat);
};

#endif // CELL_H_INCLUDED
