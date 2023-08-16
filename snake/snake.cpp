#include <iostream>
#include <conio.h>
#include <ctime>
#include "TConsole.h"


using namespace std;

#define DEBUG

#define PLAY 0
#define LEVELS 1
#define EXIT 2
#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3








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
    int GetSizeMapDesign()
    {
        return size(MapDesign);
    }
    char GetMapDesign(int i, int j)
    {
        return MapDesign[i][j];
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

map& Selected_Level = Level_1;



void Setup() // function Setting
{
    gameOver = true;
    mainMenu = false;
    click_enter = false;
    dir = STOP;
    MainMenuDir = 0;
    x = width / 2;
    y = height / 2;
    Selected_Level.ClearFruit(fruitX, fruitY);
    do
    {
        fruitX = rand() % width;
        fruitY = rand() % height;
        
    } while (!Selected_Level.CheckFruit(fruitX, fruitY));

    Selected_Level.SetFruit(fruitX, fruitY);
    
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

    class Box_5x5
    {
    private:
        int Box[20][2];
        int x;
        int y;
        int DoorX;
        int DoorY;
    public:
        Box_5x5()
        {
            x = 0;
            y = 0;
            DoorX = -1;
            DoorY = -1;
        }

        bool CheckDoor()
        {
            return DoorX >= 0 && DoorY >= 0;
      }

        void SetDoorX(int valueDoorX)
        {
            DoorX = valueDoorX;
        }
        void SetDoorY(int valueDoorY)
        {
            DoorY = valueDoorY;
        }
        int GetDoorX()
        {
            return DoorX;
        }
        int GetDoorY()
        {
            return DoorY;
        }
        int GetBoxSize()
        {
            return size(Box);
        }
        int GetBox(int i, int j)
        {
            return Box[i][j];
        }

        void CreateBox(int valueX, int valueY)
        {
            for (int i = 0; i < size(Box); i++)
            {
                if (i < 5)
                {
                    Box[i][0] = valueX;
                    Box[i][1] = valueY;
                    valueY++;
                }
                else if (i >= 5 && i < 10)
                {
                    Box[i][0] = valueX;
                    Box[i][1] = valueY;
                    valueX++;
                }
                else if (i >= 10 && i < 15)
                {
                    Box[i][0] = valueX;
                    Box[i][1] = valueY;
                    valueY--;
                }
                else
                {
                    Box[i][0] = valueX;
                    Box[i][1] = valueY;
                    valueX--;
                }

            }
            
            
        }
    };


    // Level_2
   
    int Right_Angle_Left_Up[5][2] = { {5, 2}, {3, 2}, {3, 4}, {3, 3}, {4, 2} };
    int Right_Angle_Right_Up[5][2] = { {14, 2}, {15, 2}, {16, 2}, {16, 3}, {16, 4} };
    int Right_Angle_Left_Down[5][2] = { {3, 15}, {3, 16}, {3, 17}, {4, 17}, {5, 17} };
    int Right_Angle_Right_Down[5][2] = { {14, 17}, {15, 17}, {16, 17}, {16, 16}, {16, 15} };

    for (int i = 0; i < size(Right_Angle_Left_Up); i++)
    {
        Level_2.SetMapDesign(Right_Angle_Left_Up[i][1], Right_Angle_Left_Up[i][0], '#');
        Level_2.SetMapDesign(Right_Angle_Right_Up[i][1], Right_Angle_Right_Up[i][0], '#');
        Level_2.SetMapDesign(Right_Angle_Left_Down[i][1], Right_Angle_Left_Down[i][0], '#');
        Level_2.SetMapDesign(Right_Angle_Right_Down[i][1], Right_Angle_Right_Down[i][0], '#');
    }
    
    // Level_3
    Box_5x5 Box_Left_Up, Box_Right_Up, Box_Left_Down, Box_Right_Down;
    int x = 3;
    int y = 2;
    int DoorX = 8;
    int DoorY = 4;
    
    Box_Left_Up.SetDoorX(DoorX);
    Box_Left_Up.SetDoorY(DoorY);
    Box_Left_Up.CreateBox(x, y);

    y = 12;
    DoorY = 14;

    Box_Left_Down.SetDoorX(DoorX);
    Box_Left_Down.SetDoorY(DoorY);
    Box_Left_Down.CreateBox(x, y);

    y = 2;
    x = 12;
    DoorX = 12;
    DoorY = 6;

    Box_Right_Up.SetDoorX(DoorX);
    Box_Right_Up.SetDoorY(DoorY);
    Box_Right_Up.CreateBox(x, y);
    
    DoorX = 12;
    DoorY = 14;
    y = 12;
   
    Box_Right_Down.SetDoorX(DoorX);
    Box_Right_Down.SetDoorY(DoorY);
    Box_Right_Down.CreateBox(x, y);

    for (int i = 0; i < Box_Left_Up.GetBoxSize(); i++)
    {
        Level_3.SetMapDesign(Box_Left_Up.GetBox(i, 1), Box_Left_Up.GetBox(i, 0), '#');
        Level_3.SetMapDesign(Box_Right_Up.GetBox(i, 1), Box_Right_Up.GetBox(i, 0), '#');
        Level_3.SetMapDesign(Box_Left_Down.GetBox(i, 1), Box_Left_Down.GetBox(i, 0), '#');
        Level_3.SetMapDesign(Box_Right_Down.GetBox(i, 1), Box_Right_Down.GetBox(i, 0), '#');
    }

    if (Box_Left_Up.CheckDoor()) Level_3.SetMapDesign(Box_Left_Up.GetDoorY(), Box_Left_Up.GetDoorX(), ' ');
    if (Box_Right_Up.CheckDoor()) Level_3.SetMapDesign(Box_Right_Up.GetDoorY(), Box_Right_Up.GetDoorX(), ' ');
    if (Box_Left_Down.CheckDoor()) Level_3.SetMapDesign(Box_Left_Down.GetDoorY(), Box_Left_Down.GetDoorX(), ' ');
    if (Box_Right_Down.CheckDoor()) Level_3.SetMapDesign(Box_Right_Down.GetDoorY(), Box_Right_Down.GetDoorX(), ' ');
}

void DrowMenu()
{
    system("cls");


    Console.TextColor(COLOR_GREEN);
    cout << "\n\n";
    cout << "\t\t\t   &&&&&         NNN         NN             &             NN      NN   &&&&&&&&&&" <<  endl;
    cout << "\t\t\t &&&    &&&      NN NN       NN            &&&            NN    NN     &&P       " << endl;
    cout << "\t\t\t&&&       &&&    NN  N       NN           &   &           NN   NN      &&" << endl;
    cout << "\t\t\t  &&&            NN   NN     NN          &&   &&          NN  NN       &&" << endl;
    cout << "\t\t\t   &&&           NN    N     NN         &       &         NN NN        &&L       " << endl;
    cout << "\t\t\t     &&&         NN     NN   NN        &&&&&&&&&&&        NNN          &&&&&&&&&&" << endl;
    cout << "\t\t\t       &&&       NN      N   NN       &           &       NN NN        &&P" << endl;
    cout << "\t\t\t         &&&     NN       NN NN      &&           &&      NN   NN      &&" << endl;
    cout << "\t\t\t &&&    &&&      NN        N NN     &               &     NN    NN     &&L       " << endl;
    cout << "\t\t\t    &&&&&        NN         NNN    &&               &&    NN     NN    &&&&&&&&&&" << endl;
  
    Console.TextColor(COLOR_WHITE);
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

void Selecting_levels()
{
    if (MainMenuDir == LEVELS && click_enter)
    {
        bool Selecting = true;
        int Dir_Selecting_levels = LEVEL_1;
        char key;
        while (Selecting)
        {
            

            if (Dir_Selecting_levels == LEVEL_1)
            {
                Level_1.DrowMap();
                cout << "\n\nClick on 'A' and 'D' to move through menu";
                cout << "\n\nClick on 'Enter' to set up the level\n";
                Console.GotoXY(32, 10);
                Console.TextColor(COLOR_GREEN);
                cout << "LEVEL 1";
                Console.TextColor(COLOR_WHITE);
                Console.GotoXY(27, 11);
                cout << "----------------";
                Console.GotoXY(27, 12);
                cout << "Difficult - Easy";
            }
            else if (Dir_Selecting_levels == LEVEL_2)
            {
                Level_2.DrowMap();
                cout << "\n\nClick on 'A' and 'D' to move through menu";
                cout << "\n\nClick on 'Enter' to set up the level\n";
                Console.GotoXY(32, 10);
                Console.TextColor(COLOR_GREEN);
                cout << "LEVEL 2";
                Console.TextColor(COLOR_WHITE);
                Console.GotoXY(27, 11);
                cout << "----------------";
                Console.GotoXY(27, 12);
                cout << "Difficult - Normal";
            }
            else
            {
                Level_3.DrowMap();
                cout << "\n\nClick on 'A' and 'D' to move through menu";
                cout << "\n\nClick on 'Enter' to set up the level\n";
                Console.GotoXY(32, 10);
                Console.TextColor(COLOR_GREEN);
                cout << "LEVEL 3";
                Console.TextColor(COLOR_WHITE);
                Console.GotoXY(27, 11);
                cout << "----------------";
                Console.GotoXY(27, 12);
                cout << "Difficult - Hard";
            }

            key = _getch();
            switch (key)
            {
            case 'a':
                (Dir_Selecting_levels == LEVEL_1) ? (Dir_Selecting_levels = LEVEL_3) : (Dir_Selecting_levels--);
                break;
            case 'd':
                (Dir_Selecting_levels == LEVEL_3) ? (Dir_Selecting_levels = LEVEL_1) : (Dir_Selecting_levels++);
                break;
            case 13:    // Enter
                
                if (Dir_Selecting_levels == LEVEL_1) Selected_Level = Level_1;
                else if (Dir_Selecting_levels == LEVEL_2) Selected_Level = Level_2;
                else Selected_Level = Level_3;
                Setup();
            case 27:    // Esc
                Selecting = false;
                break;
            default:
                break;

                
            }
        }
    }

   
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
    if (x >= width-1) x = 2;
    else if (x < 1) x = width - 2;
    else if (y < 1) y = height - 2;
    else if (y == height-1) y = 1;
    
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }
    
    
    
    if (Selected_Level.GetMapDesign(y, x) == '#') gameOver = true;
    

    if (x == fruitX && y == fruitY)
    {
        
        fruitX = rand() % width;
        fruitY = rand() % height;
        while (!Selected_Level.CheckFruit(fruitX, fruitY))
        {
            
            Selected_Level.SetMapDesign(fruitY, fruitX, '#');
            fruitX = rand() % width;
            fruitY = rand() % height;
            
        }

        Selected_Level.SetFruit(fruitX, fruitY);
       
        
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
    
    CreateLevels();
    Setup();
    while (!mainMenu)
    {
        DrowMenu();
        MoveMenu();
        exit();
        Play();
        Selecting_levels();
        
        click_enter = false;
        while (!gameOver)
        {
            
            Input();
            Logic();
            Selected_Level.DrowMap();
            if (gameOver)
            {
                gameover();
                Setup();
                CreateLevels();

            }
        }
        
    }
    
   


}
