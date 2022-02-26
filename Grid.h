#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

class Grid
{
    public:

    Grid();

    static char Map[21][21]; // Grid 

    static int spread(int c, int e , int w , int n , int s, int windSpeed, int prob);   //take all current states and return new state

    static void applySpread(Cell forest[21][21], int weather, int windDirection, int windSpeed, int groundMoisture); // method to 

    bool IsAnyCellOnFire(Cell forest[21][21]); // method to check if a cell is on fire 

    void DrawGrid(Cell forest[21][21]); // method that draws the grid on the screen

    void Regrowth(Cell forest[21][21]); // New tree growth 

    void Info(int weather, int windDirection, int windSpeed, int groundMoisture); // Enchancements to be displyed on the screen 

};

#endif // GRID_H_INCLUDED
