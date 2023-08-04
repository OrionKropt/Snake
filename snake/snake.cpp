﻿#include <iostream>
#include <conio.h>
#include "TConsole.h"
using namespace std;

bool gameOver, mainMenu; 

const int width = 20; 
const int height = 20;

int x, y, fruitX, fruitY, score; // the coordinates of the snake's head and the fruit

int tailX[100], tailY[100]; // Arrays for coordinates of tail
int nTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN}; // move snake

eDirection dir; // corrent move

TConsole Console;

void Setup() // function Setting
{
    gameOver = false;
    mainMenu = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}

void DrowMenu()
{
    Console.GotoXY(60, 14);
    cout << "PLAY";
    Console.GotoXY(60, 15);
    cout << "LEVELS";
    Console.GotoXY(60, 16);
    cout << "EXIT";
    Console.GotoXY(60, 14);
}

void MoveMenu()
{

}

void Draw() // Object drawing function
{
    system("cls"); 
    
    for (int i = 0; i <= width; i++)
    {
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0 || j == width-1)
            {
                cout << "#";
            }
            
            if (i == y && j == x)
            {
                cout << "0";
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "$";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
                    

            }
        }
        cout << endl;
        
    }
    
    for (int i = 0; i <= width; i++)
    {
        cout << "#";
    }
    cout << endl;
    cout << "Score " << score << endl;
}

void Input() // Function that reads keystrokes
{
    if (_kbhit())
    {
        int key = _getch();
       
        switch (key)
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 27:    // Esc
            gameOver = true;
            break;
       
        }
   }
}

void Logic() // Games's logic
{

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    
    }
    if (x >= width-1) x = 1;
    else if (x == 0) x = width - 2;
    else if (y < 0) y = height - 1;
    else if (y == height) y = 0;
    
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }
    
    

    if (x == fruitX && y == fruitY)
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
        score += 10;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!mainMenu)
    {
        DrowMenu();
        MoveMenu();
    }
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
    }
}
