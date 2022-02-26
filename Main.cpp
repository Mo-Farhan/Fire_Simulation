#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<conio.h>
#include<windows.h>
#include "Cell.h"
#include "Grid.h"

using namespace std;

int main()
{
    Cell forest[21][21];
    Grid grid;
    int windDirection, weather, groundMoisture = 0;
    int windSpeed;
    Grid newState;
    bool Notdone = true;
    forest[10][10].setStateValue(2);
    Grid::Map[10][10] = 'x';
    srand((unsigned)time(NULL));

    weather = rand() % 2;     // 0 : Normal, 1 : Windy

    windDirection = rand() % 4;     // 0 : East, 1 : West, 2 : South, 3 : North

    windSpeed = (rand() % 20 ) + 10;        //wind speed can vary from 10mph to 30mph

    do
    {
        system("CLS");
        grid.Info(weather,windDirection,windSpeed,groundMoisture);
        grid.DrawGrid(forest);
        fflush(stdin);

        cout << endl << "To Start: Press any key" << endl;
        cout << "To Exit: Press 9\n ";

        // break the simulation when user presses the key "9"
        Notdone = grid.IsAnyCellOnFire(forest);
        if(!Notdone)
        {
            cout << "No cell is on fire\n";
             break;
        }
        else
        {
            Grid::applySpread(forest, weather, windDirection, windSpeed, groundMoisture);
            grid.Regrowth(forest);
        }
    }while(_getch() != '9');

    return 0;
    system("pause");
}


