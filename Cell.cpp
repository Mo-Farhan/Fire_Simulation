
#include<iostream>
#include "Cell.h"

using namespace std;

    Cell::Cell()
    {
        state = 1; // state of the cell is 1 (tree)
    }
    int Cell::getStateValue() // get the current state of the cell
    {
        return state;
    }
    void Cell::setStateValue(int stat) // set the state of the cell
    {
        state = stat;
    }
