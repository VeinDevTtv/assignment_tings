#include <iostream>
#include <vector>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

struct Point {
    int x;
    int y;
};

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

const int kBoardWidth = 20;
const int kBoardHeight = 12;
const int kWinScore = 10;
const DWORD kFrameDelayMs = 120;

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool isOpposite(Direction current, Direction candidate) {
    return (current == Direction::Up && candidate == Direction::Down) ||
           (current == Direction::Down && candidate == Direction::Up) ||
           (current == Direction::Left && candidate == Direction::Right) ||
           (current == Direction::Right && candidate == Direction::Left);
}

bool isInsideBoard(const Point& point) {
    return point.x >= 0 && point.x < kBoardWidth &&
           point.y >= 0 && point.y < kBoardHeight;
}

bool isOnSnake(const deque<Point>& snake, const Point& point) {
    for (const Point& segment : snake) {
        if (segment == point) {
            return true;
        }
    }
    return false;
}

bool hitsSnake(const deque<Point>& snake, const Point& point, bool ignoreTail) {
    size_t lastIndex = snake.empty() ? 0 : snake.size() - 1;

    for (size_t i = 0; i < snake.size(); ++i) {
        if (ignoreTail && i == lastIndex) {
            continue;
        }
        if (snake[i] == point) {
            return true;
        }
    }

    return false;
}

Point movePoint(const Point& point, Direction direction) {
    Point next = point;

    if (direction == Direction::Up) {
        next.y--;
    } else if (direction == Direction::Down) {
        next.y++;
    } else if (direction == Direction::Left) {
        next.x--;
    } else {
        next.x++;
    }

    return next;
}

Direction readDirection(Direction currentDirection) {
    Direction updatedDirection = currentDirection;

    while (_kbhit()) {
        int key = _getch();
        Direction candidate = updatedDirection;
        bool recognized = true;

        if (key == 0 || key == 224) {
            int arrow = _getch();
            if (arrow == 72) {
                candidate = Direction::Up;
            } else if (arrow == 80) {
                candidate = Direction::Down;
            } else if (arrow == 75) {
                candidate = Direction::Left;
            } else if (arrow == 77) {
                candidate = Direction::Right;
            } else {
                recognized = false;
            }
        } else if (key == 'w' || key == 'W') {
            candidate = Direction::Up;
        } else if (key == 's' || key == 'S') {
            candidate = Direction::Down;
        } else if (key == 'a' || key == 'A') {
            candidate = Direction::Left;
        } else if (key == 'd' || key == 'D') {
            candidate = Direction::Right;
        } else {
            recognized = false;
        }

        if (recognized && !isOpposite(updatedDirection, candidate)) {
            updatedDirection = candidate;
        }
    }

    return updatedDirection;
}

Point spawnFood(const deque<Point>& snake) {
    vector<Point> freeCells;

    for (int y = 0; y < kBoardHeight; ++y) {
        for (int x = 0; x < kBoardWidth; ++x) {
            Point candidate = {x, y};
            if (!isOnSnake(snake, candidate)) {
                freeCells.push_back(candidate);
            }
        }
    }

    if (freeCells.empty()) {
        return {-1, -1};
    }

    int index = rand() % static_cast<int>(freeCells.size());
    return freeCells[index];
}

void clearConsole(HANDLE consoleHandle) {
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo);

    DWORD cellCount = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;
    DWORD charsWritten = 0;
    COORD home = {0, 0};

    FillConsoleOutputCharacterA(consoleHandle, ' ', cellCount, home, &charsWritten);
    FillConsoleOutputAttribute(consoleHandle, bufferInfo.wAttributes, cellCount, home, &charsWritten);
    SetConsoleCursorPosition(consoleHandle, home);
}

void hideCursor(HANDLE consoleHandle) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void showStartScreen(HANDLE consoleHandle) {
    clearConsole(consoleHandle);
    cout << "====================\n";
    cout << "  NOKIA SNAKE CLONE \n";
    cout << "====================\n\n";
    cout << "Controls: WASD or Arrow Keys\n";
    cout << "Goal: Reach Score " << kWinScore << "\n\n";
    cout << "Press any key to start...";
    _getch();
    clearConsole(consoleHandle);
}

void renderGame(HANDLE consoleHandle, const deque<Point>& snake, const Point& food, int score) {
    vector<string> board(kBoardHeight, string(kBoardWidth, ' '));

    for (size_t i = 0; i < snake.size(); ++i) {
        board[snake[i].y][snake[i].x] = (i == 0) ? 'O' : 'o';
    }

    if (isInsideBoard(food)) {
        board[food.y][food.x] = '*';
    }

    COORD home = {0, 0};
    SetConsoleCursorPosition(consoleHandle, home);

    cout << "Score: " << score << "/" << kWinScore << "\n";
    cout << "Controls: WASD or Arrow Keys\n";
    cout << '+';
    for (int x = 0; x < kBoardWidth; ++x) {
        cout << '-';
    }
    cout << "+\n";

    for (int y = 0; y < kBoardHeight; ++y) {
        cout << '|';
        for (int x = 0; x < kBoardWidth; ++x) {
            cout << board[y][x];
        }
        cout << "|\n";
    }

    cout << '+';
    for (int x = 0; x < kBoardWidth; ++x) {
        cout << '-';
    }
    cout << "+\n";
}

void showEndScreen(HANDLE consoleHandle, const string& message) {
    clearConsole(consoleHandle);
    cout << message << "\n\n";
    cout << "Press any key to exit...";
    _getch();
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor(consoleHandle);
    SetConsoleTitleA("Raiden Zaml Snake");

    deque<Point> snake;
    snake.push_back({10, 6});
    snake.push_back({9, 6});
    snake.push_back({8, 6});

    Direction direction = Direction::Right;
    Point food = spawnFood(snake);
    int score = 0;
    bool gameOver = false;
    bool gameWon = false;

    showStartScreen(consoleHandle);

    while (!gameOver && !gameWon) {
        direction = readDirection(direction);

        Point nextHead = movePoint(snake.front(), direction);
        bool willGrow = (nextHead == food);
        bool ignoreTail = !willGrow;

        if (!isInsideBoard(nextHead) || hitsSnake(snake, nextHead, ignoreTail)) {
            gameOver = true;
        } else {
            snake.push_front(nextHead);

            if (willGrow) {
                score++;
                if (score >= kWinScore) {
                    gameWon = true;
                } else {
                    food = spawnFood(snake);
                }
            } else {
                snake.pop_back();
            }
        }

        renderGame(consoleHandle, snake, food, score);
        Sleep(kFrameDelayMs);
    }

    if (gameWon) {
        showEndScreen(consoleHandle, "LFASSI ZAML 7WAY LBRAML");
    } else {
        showEndScreen(consoleHandle, "MOK 97BA");
    }

    return 0;
}
