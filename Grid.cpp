#include<iostream>
#include "Cell.h"
#include "Grid.h"
using namespace std;

char Grid::Map[21][21];

Grid::Grid()
{
    // & is drawn on the screen
     for(int i = 0 ; i < 21; i++)
        {
            for(int j = 0; j < 21; j++)
            {
                Map[i][j] = '&';
            }
        }
}
int Grid::spread(int c, int e , int w , int n , int s, int windSpeed, int probability )   //take all current states and return new state
{
    if(c == 0 || c == 2)
        return 0;

    if(c == 1)
    {
        if(e != 2 && w != 2 && n != 2 && s != 2)
            return 1;
        else
        {
            int seconds = 0;
            if(windSpeed < 17)
                seconds = 1000;
            else
                seconds = 500;

            //Sleep(seconds);
            //srand( (unsigned)time( NULL ) );

            int m = 2;
            if(probability == 40 || probability == 80)
                m = 3;
            else if(probability == 50)
                m = 2;

            //choose random number between 0 & 1, 0 for a tree and 1 for a burning tree
            int random = rand() % m;

            if(probability == 40 && (random == 0 || random == 2))
                    return 1;
            else if(probability == 40 && random == 1)
                    return 2;
            else if(probability == 80 && (random == 1 || random == 2))
                    return 2;
            else if(probability == 80 && random == 0)
                    return 1;
            else if(probability == 50 && random == 0)
                    return 1;
            else if(probability == 50 && random == 1)
                    return 2;


        }
    }
    return 9;
}


void Grid::applySpread(Cell forest[21][21], int weather, int windDirection, int windSpeed, int groundMoisture)
{
    int newState,probability = 50;

    // probabilities based on groundMoisture and windDirection

    for(int i = 0 ; i < 21; i++)
        {
            for(int j = 0; j < 21; j++)
            {
                if(weather == 0)
                    probability = 50;
                else
                {
                   switch(windDirection)
                    {
                        case 0 :    //east
                                    if(groundMoisture == windDirection)
                                            probability = 40;
                                    else if(j >= 0 && j <= 10)
                                            probability = 80;
                                    else
                                            probability = 40;
                                    break;
                        case 1 :    //west
                                    if(groundMoisture == windDirection)
                                            probability = 40;
                                    else if(j >= 10 && j < 21)
                                            probability = 80;
                                    else
                                            probability = 50;
                                    break;
                        case 2 :    //south
                                    if(groundMoisture == windDirection)
                                            probability = 40;
                                    else if(i >= 10 && i < 21)
                                            probability = 80;
                                    else
                                            probability = 50;
                                    break;
                        case 3 :    //north
                                    if(groundMoisture == windDirection)
                                            probability = 40;
                                    else if(i >= 0 && i <= 10)
                                            probability = 80;
                                    else
                                            probability = 50;
                                    break;
                    }
                }
                int east, west, south, north;

                //checking for the trees at the edges
                if(i == 0)
                    north = 0;
                else
                    north = forest[i-1][j].getStateValue();
                if(j == 0)
                    east = 0;
                else
                    east = forest[i][j-1].getStateValue();
                if (i == 20)
                    south = 0;
                else
                    south = forest[i+1][j].getStateValue();
                if (j == 20)
                    west = 0;
                else
                    west = forest[i][j+1].getStateValue();


                newState = spread(forest[i][j].getStateValue(), east, west, south, north, windSpeed,  probability);

                //apply new state to the forest;
                forest[i][j].setStateValue(newState);

                //update the Map
                switch(newState)
                {
                    case 0 : Grid::Map[i][j] = ' ';
                                break;
                    case 1 : Grid::Map[i][j] = '&';
                                break;
                    case 2 : Grid::Map[i][j] = 'x';
                                break;
                }
            }
        }
}

bool Grid::IsAnyCellOnFire(Cell forest[21][21])
{
    // To check for the state of the cell and return flag as true if cell is empty or else false
    int i, j;
    bool flag = false;
        for( i = 0 ; i < 21; i++)
        {
            for( j = 0; j < 21; j++)
            {
                if(forest[i][j].getStateValue() == 2)
                {
                    flag = true;
                }
            }
        }
        if(flag)
            return true;
        else
            return false;
}

void Grid::DrawGrid(Cell forest[21][21])
{
    cout << endl << endl;

    // empty state is drwan on the grid " "
    for(int i = 0 ; i < 21; i++)
        {
            for(int j = 0; j < 21; j++)
            {
                cout << Grid::Map[i][j] << " ";
            }
            cout << endl;
        }
}

void Grid:: Regrowth(Cell forest[21][21])
{
    // New tree growth at random
        for(int i = 0 ; i < 21; i++)
        {
            for(int j = 0; j < 21; j++)
            {
                if(forest[i][j].getStateValue() == 0)
                {
                    int random = rand() % 2;

                    //apply new state to the forest
                    forest[i][j].setStateValue(random);

                    //update the Map
                    switch(random)
                    {
                        case 0 : Grid::Map[i][j] = ' ';
                                    break;
                        case 1 : Grid::Map[i][j] = '&';
                                    break;
                    }
                }
            }
        }
}

void Grid::Info(int weather, int windDirection, int windSpeed, int groundMoisture)
{

    // Wether condition to be displayed on the screen 
    cout << endl;
    cout << " Weather conditions :\t";
    switch(weather)
    {
        case 0  :   cout << "Normal" << endl;
        break;
        case 1  :   cout << "Windy" <<  endl;
        break;
    }

    //Wiid Direction to be displayed on the screen
    cout << " Wind Direction :\t" ;
    switch(windDirection)
    {
        case 0  :   cout << "East" << endl;
        break;
        case 1  :   cout << "West" << endl;
        break;
        case 2  :   cout << "South" << endl;
        break;
        case 3  :   cout << "North" << endl;
        break;
    }

    // Wind speed to be displayed on the screen 
    cout << " Wind Speed :\t\t" << windSpeed << "mph (miles per hour)" << endl;

    cout << " Forest damp area :\t";
    switch(groundMoisture)
    {
        case 0  :   cout << "East" << endl;
        break;
        case 1  :   cout << "West" << endl;
        break;
        case 2  :   cout << "South" << endl;
        break;
        case 3  :   cout << "North" << endl;
        break;
    }
}
