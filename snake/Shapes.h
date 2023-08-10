#include <iostream>

#define DEBUG

using namespace std;

#pragma once
class Shapes
{
private:
    int x;
    int y;
    int shape[50][2];
    int count;
    int Right_angle_small[3][2];
          
   
public:
    Shapes()
    {
        x = 0;
        y = 0;
        count = 0;
     
        // Shapes
        // Right_angle_small
       

        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                shape[i][j] = 0;
            }
        }
    }

    void RedyShapes()
    {
        Right_angle_small[0][0] = 3;
        Right_angle_small[0][1] = 3;
        Right_angle_small[1][0] = 3;
        Right_angle_small[1][1] = 2;
        Right_angle_small[2][0] = 4;
        Right_angle_small[2][1] = 2;
    }

    void SetXY(int setX, int setY)
    {
        shape[y][x] = x;
        shape[y][x + 1] = y;
        y++;
        count++;
    }

    void DelXY(int setX, int setY)
    {
        shape[y][x] = 0;
        shape[y][x] = 0;
        y--;
        count--;
    }

#ifdef DEBUG

    void PrintShape()
    {
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                cout << shape[i][j];
            }
            cout << endl;
        }
        if (count == 0)
        {
            cout << "coordinates are not set" << endl;
        }
    }
#endif // DEBUG

    void Get_coordinates_Right_angle_small()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                cout << Right_angle_small[i][j];
            }
            cout << endl;
        }
    }

    void Add_to_map_Right_angle_small(void (*map)(int x, int y, char object))
    {
        for (int i = 0; i < 3; i++)
        {
            map(Right_angle_small[i][0], Right_angle_small[i][1], '#');
        }
    }

};

