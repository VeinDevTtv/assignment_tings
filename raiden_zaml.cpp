#define NOMINMAX
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

using namespace std;

const int kConsoleWidth = 79;
const int kConsoleHeight = 24;
const int kGroundY = 20;

bool g_useAnsi = false;

const string kReset = "\x1b[0m";
const string kGreen = "\x1b[92m";
const string kYellow = "\x1b[93m";
const string kMagenta = "\x1b[95m";
const string kCyan = "\x1b[96m";
const string kWhite = "\x1b[97m";
const string kRed = "\x1b[91m";

const vector<string> playerSprite = {
    "  _  ",
    " | | ",
    "(_O_)"
};

const vector<string> ananasSprite = {
    " \\|/ ",
    " (X) ",
    " /_\\ "
};

bool enableAnsiColors(HANDLE consoleHandle) {
    DWORD mode = 0;
    if (!GetConsoleMode(consoleHandle, &mode)) return false;
    return SetConsoleMode(consoleHandle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
}

void hideCursor(HANDLE consoleHandle) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void setCursorPosition(HANDLE consoleHandle, int x, int y) {
    COORD coord = { static_cast<short>(x), static_cast<short>(y) };
    SetConsoleCursorPosition(consoleHandle, coord);
}

struct Obstacle {
    int x;
};

struct GameState {
    float playerY;
    float playerVelocity;
    bool isJumping;
    int score;
    vector<Obstacle> obstacles;
    bool gameOver;
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    g_useAnsi = enableAnsiColors(consoleHandle);
    hideCursor(consoleHandle);
    SetConsoleTitleA("Cyborg Zaml Game");

    string groundLine(kConsoleWidth, '-');

    while (true) {
        GameState state;
        state.playerY = kGroundY - playerSprite.size() + 1;
        state.playerVelocity = 0;
        state.isJumping = false;
        state.score = 0;
        state.gameOver = false;

        system("cls");
        cout << (g_useAnsi ? kCyan : "") << "\n Cyborg Zaml Game\n" << (g_useAnsi ? kReset : "");
        cout << " Press Space/Up to jump, Q to quit. Dodge the Ananases!\n";
        cout << " Press any key to start...\n";
        _getch();

        system("cls");

        auto lastTime = chrono::high_resolution_clock::now();
        float obstacleTimer = 0.0f;
        
        while (!state.gameOver) {
            auto currentTime = chrono::high_resolution_clock::now();
            float dt = chrono::duration<float, milli>(currentTime - lastTime).count();
            if (dt < 30.0f) {
                this_thread::sleep_for(chrono::milliseconds(1));
                continue;
            }
            lastTime = currentTime;

            bool jumpPressed = false;
            while (_kbhit()) {
                int key = _getch();
                if (key == 0 || key == 224) { 
                    key = _getch();
                    if (key == 72) jumpPressed = true; 
                } else if (key == ' ' || key == 'w' || key == 'W') {
                    jumpPressed = true;
                } else if (key == 'q' || key == 'Q' || key == 27) {
                    exit(0);
                }
            }

            if (jumpPressed && !state.isJumping) {
                state.playerVelocity = -2.3f; 
                state.isJumping = true;
            }

            state.playerVelocity += 0.22f; 
            state.playerY += state.playerVelocity;

            float groundLimit = kGroundY - playerSprite.size() + 1;
            if (state.playerY >= groundLimit) {
                state.playerY = groundLimit;
                state.playerVelocity = 0;
                state.isJumping = false;
            }

            for (auto& obs : state.obstacles) {
                obs.x -= 2; 
            }

            if (!state.obstacles.empty() && state.obstacles.front().x < -10) {
                state.obstacles.erase(state.obstacles.begin());
            }

            obstacleTimer += dt;
            int speedUp = state.score / 500;
            float spawnThreshold = max(400.0f, 900.0f - (speedUp * 50.0f));

            if (obstacleTimer > spawnThreshold) { 
                if (state.obstacles.empty() || (kConsoleWidth - state.obstacles.back().x) > 25) {
                    if (rand() % 100 < 50) { 
                        state.obstacles.push_back({kConsoleWidth});
                        obstacleTimer = 0.0f;
                    }
                }
            }

            state.score++;

            int playerLeft = 5;
            int playerRight = playerLeft + static_cast<int>(playerSprite[0].size()) - 3;
            int playerTop = static_cast<int>(state.playerY);
            int playerBottom = playerTop + static_cast<int>(playerSprite.size()) - 1;

            for (const auto& obs : state.obstacles) {
                int obsLeft = obs.x + 1;
                int obsRight = obs.x + static_cast<int>(ananasSprite[0].size()) - 2;
                int obsTop = kGroundY - static_cast<int>(ananasSprite.size()) + 1;
                int obsBottom = kGroundY;

                if (playerRight >= obsLeft && playerLeft <= obsRight &&
                    playerBottom >= obsTop && playerTop <= obsBottom) {
                    state.gameOver = true;
                }
            }

            vector<string> screen(kConsoleHeight, string(kConsoleWidth, ' '));
            screen[kGroundY + 1] = groundLine;

            string scoreStr = "Score: " + to_string(state.score / 10);
            for (size_t i = 0; i < scoreStr.length() && (kConsoleWidth - 20 + i) < kConsoleWidth; ++i) {
                screen[2][kConsoleWidth - 20 + i] = scoreStr[i];
            }

            for (const auto& obs : state.obstacles) {
                int oX = obs.x;
                int oY = kGroundY - static_cast<int>(ananasSprite.size()) + 1;
                for (size_t i = 0; i < ananasSprite.size(); ++i) {
                    int drawY = oY + i;
                    if (drawY >= 0 && drawY < kConsoleHeight) {
                        for (size_t j = 0; j < ananasSprite[i].size(); ++j) {
                            if (oX + j >= 0 && oX + j < kConsoleWidth) {
                                screen[drawY][oX + j] = ananasSprite[i][j];
                            }
                        }
                    }
                }
            }

            int pX = playerLeft;
            int pY = static_cast<int>(state.playerY);
            for (size_t i = 0; i < playerSprite.size(); ++i) {
                int drawY = pY + i;
                if (drawY >= 0 && drawY < kConsoleHeight) {
                    for (size_t j = 0; j < playerSprite[i].size(); ++j) {
                        if (pX + j >= 0 && pX + j < kConsoleWidth) {
                            screen[drawY][pX + j] = playerSprite[i][j];
                        }
                    }
                }
            }

            setCursorPosition(consoleHandle, 0, 0);
            string outputBuffer;
            outputBuffer.reserve(kConsoleWidth * kConsoleHeight + kConsoleHeight);
            for (int i = 0; i < kConsoleHeight; ++i) {
                outputBuffer += screen[i];
                if (i < kConsoleHeight - 1) outputBuffer += "\n";
            }
            cout << outputBuffer;
        }

        setCursorPosition(consoleHandle, kConsoleWidth / 2 - 5, kConsoleHeight / 2);
        cout << (g_useAnsi ? kRed : "") << "GAME OVER!" << (g_useAnsi ? kReset : "");
        setCursorPosition(consoleHandle, kConsoleWidth / 2 - 15, kConsoleHeight / 2 + 1);
        cout << "Final Score: " << state.score / 10;
        setCursorPosition(consoleHandle, kConsoleWidth / 2 - 17, kConsoleHeight / 2 + 2);
        cout << "Press R to Retry or Q to Quit.";

        while (true) {
            int key = _getch();
            if (key == 'r' || key == 'R') break;
            if (key == 'q' || key == 'Q' || key == 27) return 0;
        }
    }

    return 0;
}