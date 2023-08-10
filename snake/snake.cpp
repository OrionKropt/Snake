#include <iostream>
#include <conio.h>
#include <ctime>
#include "TConsole.h"
#include "Shapes.h"



#define DEBUG

#define PLAY 0
#define LEVELS 1
#define EXIT 2
using namespace std;






bool gameOver, mainMenu;
bool click_enter; // Functions Menu

const int width = 20; 
const int height = 20;


int x, y, fruitX, fruitY, score; // the coordinates of the snake's head and the fruit



int tailX[100], tailY[100]; // Arrays for coordinates of tail
int nTail;
int  MainMenuDir; // main menu cursor
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN}; // move snake

eDirection dir; // corrent move

TConsole Console;





class map
{
private:
    char MapDesign[width][height];
   
public:
#ifdef DEBUG
    map()
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (i == 0 || j == 0 || i == width - 1 || j == height - 1) MapDesign[i][j] = '#';
                else MapDesign[i][j] = ' ';
            }
        }
    }
#endif // DEBUG

   

    void SetMapDesign(int i, int j, char object)
    {
        MapDesign[i][j] = object;
    }

    void SetFruit(int x, int y)
    {
        
            MapDesign[y][x] = '$';
    }

    void ClearFruit(int x, int y)
    {
        MapDesign[y][x] = ' ';
    }

    bool CheckFruit(int x, int y)
    {
        if (MapDesign[y][x] == ' ') return true;
     
        else return false;
    }

    void DrowMap()
    {
        system("cls");
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == y && j == x)
                {
                    MapDesign[i][j] = '0';
                }
                else if (i == 0 || j == 0 || i == width - 1 || j == height - 1) MapDesign[i][j] = '#';
                else
                {
                    bool print = false;
                    for (int k = 0; k < nTail; k++)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            MapDesign[i][j] = 'o';
                            print = true;
                        }
                    }
                    if (!print && MapDesign[i][j] != '$' && MapDesign[i][j] != '#')
                    {
                        MapDesign[i][j] = ' ';
                    }
                }
                cout << MapDesign[i][j];
            }
            cout << endl;
        }
        cout << endl;
        cout << "Score " << score << endl;
    }

};

map Level_1, Level_2, Level_3;



void Setup(map& Level) // function Setting
{
    gameOver = true;
    mainMenu = false;
    click_enter = false;
    dir = STOP;
    MainMenuDir = 0;
    x = width / 2;
    y = height / 2;
    Level.ClearFruit(fruitX, fruitY);
    do
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
        
    } while (!Level.CheckFruit(fruitX, fruitY));

    Level.SetFruit(fruitX, fruitY);

    for (int i = 0; i < 100; i++)
    {
        tailX[i] = 0;
        tailY[i] = 0;
    }
    nTail = 0;
    score = 0;
}




void CreateLevels()
{
    // Level_2
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            
        }
    }

    

}

void DrowMenu()
{
    system("cls");
    if (MainMenuDir == PLAY) Console.TextColor(COLOR_GREEN);
    Console.GotoXY(60, 14);
    cout << "PLAY";
    Console.TextColor(COLOR_WHITE);
    if (MainMenuDir == LEVELS) Console.TextColor(COLOR_GREEN);
    Console.GotoXY(60, 15);
    cout << "LEVELS";
    Console.TextColor(COLOR_WHITE);
    if (MainMenuDir == EXIT) Console.TextColor(COLOR_GREEN);
    Console.GotoXY(60, 16);
    cout << "EXIT";
    Console.TextColor(COLOR_WHITE);
}

void MoveMenu()
{
    int key = _getch();
    
    switch (key)
    {
    case 'w':
        (MainMenuDir == 0) ? (MainMenuDir = 2) : (MainMenuDir--);
        break;
    case 's':
        (MainMenuDir == 2) ? (MainMenuDir = 0) : (MainMenuDir++);
        break;
    case 13: // Enter
        click_enter = true;
        break;
    default:
        break;
    }
}

void exit()
{
    if (MainMenuDir == EXIT && click_enter) mainMenu = true;
}

void Play()
{
    if (MainMenuDir == PLAY && click_enter) gameOver = false;
}

//void Draw() // Object drawing function
//{
//    system("cls"); 
//    
//    for (int i = 0; i <= width; i++)
//    {
//        cout << "#";
//    }
//    cout << endl;
//
//    for (int i = 0; i < height; i++)
//    {
//        for (int j = 0; j < width; j++)
//        {
//            if (j == 0 || j == width-1)
//            {
//                cout << "#";
//            }
//            
//            if (i == y && j == x)
//            {
//                cout << "0";
//            }
//            else if (i == fruitY && j == fruitX)
//            {
//                cout << "$";
//            }
//            else
//            {
//                bool print = false;
//                for (int k = 0; k < nTail; k++)
//                {
//                    if (tailX[k] == j && tailY[k] == i)
//                    {
//                        cout << "o";
//                        print = true;
//                    }
//                }
//                if (!print)
//                {
//                    cout << " ";
//                }
//                    
//
//            }
//        }
//        cout << endl;
//        
//    }
//    
//    for (int i = 0; i <= width; i++)
//    {
//        cout << "#";
//    }
//    cout << endl;
//    cout << "Score " << score << endl;
//}

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

void Logic(map& Level) // Games's logic
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
    if (x >= width-1) x = 2;
    else if (x < 1) x = width - 2;
    else if (y < 1) y = height - 2;
    else if (y == height-1) y = 1;
    
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }
    
    

    if (x == fruitX && y == fruitY)
    {
        do
        {
            fruitX = rand() % width;
            fruitY = rand() % height;
        } while (!Level.CheckFruit(fruitX, fruitY));

        Level.SetFruit(fruitX, fruitY);
       
        /*fruitX = rand() % width;
        fruitY = rand() % height;*/
        score += 10;
        nTail++;
    }
}

void gameover()
{
    system("cls");
    Console.GotoXY(60, 14);
    cout << "GAME OVER";
    Console.GotoXY(57, 16);
    cout << "Please, click space" << endl;
    Console.GotoXY(57, 18);
    cout << "Score: " << score;
    while (_getch() != ' ');
}

void main()
{
    Shapes ReadyShapes;
    
    //Setup(Level_1);
    //while (!mainMenu)
    //{
    //    DrowMenu();
    //    MoveMenu();
    //    exit();
    //    Play();
    //    click_enter = false;
    //    while (!gameOver)
    //    {
    //        //Draw();
    //        Input();
    //        Logic(Level_1);
    //        Level_1.DrowMap();
    //        if (gameOver)
    //        {
    //            gameover();
    //            Setup(Level_1);

    //        }
    //    }

    //}
    ReadyShapes.RedyShapes();
    ReadyShapes.Get_coordinates_Right_angle_small();
    ReadyShapes.Add_to_map_Right_angle_small(Level_2.SetMapDesign);

}
