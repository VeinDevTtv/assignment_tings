#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver;
bool gameWin;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
    gameOver = false;
    gameWin = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
}

void Draw()
{
    // Move cursor to top-left to avoid flickering
    COORD cursorPosition;	
    cursorPosition.X = 0;	
    cursorPosition.Y = 0;	
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#"; // Left wall
                
            if (i == y && j == x)
                cout << "O"; // Snake head
            else if (i == fruitY && j == fruitX)
                cout << "F"; // Fruit
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // Snake body
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#"; // Right wall
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << " (Reach 100 to win!)" << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
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
    default:
        break;
    }
    
    // Check collision with walls
    if (x >= width || x < 0 || y >= height || y < 0) {
        gameOver = true;
    }

    // Check collision with its own tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // Check if snake eats the fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
        
        // Win condition
        if (score >= 100) {
            gameWin = true;
            gameOver = true;
        }
    }
}

int main()
{
    Setup();
    system("cls");

    // Hide the console cursor for better rendering
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100); // Control the speed of the game
    }
    
    system("cls"); // Clear the screen at the end to display message
    
    if (gameWin) {
        cout << "\n\n\t============================\n";
        cout << "\t  LFASSI ZAML 7WAY LBRAML\n";
        cout << "\t============================\n\n";
    } else {
        cout << "\n\n\t============================\n";
        cout << "\t          MOK 97BA\n";
        cout << "\t============================\n\n";
    }
    
    cout << "\tFinal Score: " << score << "\n\n";
    
    // Reset cursor visibility before exiting
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
    
    return 0;
}
