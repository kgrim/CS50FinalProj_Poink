#include <array>
#include <iostream>
#include <raylib.h>
#include <vector>
#include "ai.h"
#include "ball.h"
#include "paddle.h"
#include "player.h"

// Screen constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

// Enum for game pages
enum ESGamePage {
    Menu,
    Game,
    GameOver
};

struct FGlobalState {
    int selectedItem = 0;
    bool is2Players = true;
    std::array<Player, 2> players;
    ESGamePage gamePage = ESGamePage::Menu;

    // Update player types based on selected menu item
    void UpdatePlayers() {
        is2Players = selectedItem == 1;
        players[0] = Player(BLUE, false, true); // Player 1
        players[1] = Player(RED, !is2Players, false); // Player 2
    }
};

// Game state struct
struct FGameState {
    Ball ball;
    std::array<Player, 2> players;

    FGameState() : ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2) {}

    // Reset the ball and players
    void Reset(bool is2Players) {
        ball.ResetBall();
        players[0] = Player(BLUE, false, true);
        players[1] = Player(RED, !is2Players, false);
    }
};

// Global State Declaration
FGlobalState globalState;

// Function prototypes
void GameMenu();
void GamePlay(FGameState& currentState);
void GameOverScreen();

// Main Game Loop
int main() {
    std::cout << "Starting Game" << std::endl;

    FGameState gameState;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Poink!");
    SetTargetFPS(60);

    // Game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Game state handling
        switch (globalState.gamePage) {
            case ESGamePage::Menu:
                GameMenu();
                break;
            case ESGamePage::Game:
                GamePlay(gameState);  // Pass by reference
                break;
            case ESGamePage::GameOver:
                GameOverScreen();
                break;
            default:
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// Game Menu Function
void GameMenu() {
    // Menu items
    std::vector<std::string> menuItems = {"1 Player Game", "2 Player Game", "Exit"};

    // Menu navigation
    if (IsKeyPressed(KEY_DOWN)) {
        globalState.selectedItem = (globalState.selectedItem + 1) % menuItems.size();
    }
    if (IsKeyPressed(KEY_UP)) {
        globalState.selectedItem = (globalState.selectedItem - 1 + menuItems.size()) % menuItems.size();
    }

    // Menu selection
    if (IsKeyPressed(KEY_ENTER)) {
        globalState.UpdatePlayers();
        switch (globalState.selectedItem) {
            case 0:
            case 1:
                globalState.gamePage = ESGamePage::Game;
                break;
            case 2:
                CloseWindow();  // Exit the game
                break;
        }
    }

    // Calculate total menu height and vertical positioning
    int totalMenuHeight = menuItems.size() * 40 + 40;
    int startY = (SCREEN_HEIGHT - totalMenuHeight) / 2;

    // Draw the main menu title
    const char* menuTitle = "POINK! Main Menu";
    DrawText(menuTitle, SCREEN_WIDTH / 2 - MeasureText(menuTitle, 60) / 2, SCREEN_HEIGHT / 4, 60, WHITE);

    // Draw the menu items
    for (int i = 0; i < menuItems.size(); i++) {
        Color textColor = (i == globalState.selectedItem) ? RED : DARKGRAY;

        // Center the menu items horizontally
        int textWidth = MeasureText(menuItems[i].c_str(), 40);
        int xPosition = (SCREEN_WIDTH - textWidth) / 2;

        // Draw each menu item
        DrawText(menuItems[i].c_str(), xPosition, startY + i * 50, 40, textColor);
    }
}

// Game Play Function
void GamePlay(FGameState& currentState) {
    // Update the ball and paddles
    currentState.ball.Update();

    const int ballX = currentState.ball.x;
    const int ballY = currentState.ball.y;

    // Check for scoring
    auto checkScoring = [&]() {
        if (ballX >= SCREEN_WIDTH || ballX < 0) {
            int scoringPlayer = (ballX >= SCREEN_WIDTH) ? 1 : 0;
            globalState.players[scoringPlayer].setScore(globalState.players[scoringPlayer].getScore() + 1);
            currentState.ball.ResetBall();

            if (globalState.players[scoringPlayer].getScore() >= 10) {
                globalState.gamePage = ESGamePage::GameOver;
            }
        }
    };
    
    checkScoring();

    // Draw the game elements (lines, ball, paddles)
    DrawLine(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, 3 * SCREEN_HEIGHT / 4, WHITE);
    DrawLine(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 3 * SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, WHITE);
    currentState.ball.Draw();

    // Draw player scores
    for (int i = 0; i < globalState.players.size(); i++) {
        globalState.players[i].UpdateAndDraw(ballX, ballY);
        currentState.ball.CollisionMonitor(globalState.players[i].paddles);

        DrawText(TextFormat("%s%i: %i", globalState.players[i].isAI ? "AI" : "P", i + 1, globalState.players[i].getScore()), 
                 (i == 0) ? SCREEN_WIDTH / 2 - 100 : SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - 50, 20, 
                 globalState.players[i].getColor());
    }
}

// Game Over Screen with Retry Option
void GameOverScreen() {
    const char* title = "Game Over!";
    const char* retryText = "Press R to Retry";
    const char* exitText = "Press ESC to Exit";

    int titleWidth = MeasureText(title, 40);
    int retryWidth = MeasureText(retryText, 20);
    int exitWidth = MeasureText(exitText, 20);
    const char* score1Text = TextFormat("Score P1: %i", globalState.players[0].getScore());
    const char* score2Text = TextFormat("Score P2: %i", globalState.players[1].getScore());

    int score1Width = MeasureText(score1Text, 20);
    int score2Width = MeasureText(score2Text, 20);

    // Center the game over screen elements
    DrawText(title, SCREEN_WIDTH / 2 - titleWidth / 2, SCREEN_HEIGHT / 3, 40, WHITE);
    DrawText(score1Text, SCREEN_WIDTH / 2 - score1Width / 2, SCREEN_HEIGHT / 3 + 50, 20, globalState.players[0].getColor());
    DrawText(score2Text, SCREEN_WIDTH / 2 - score2Width / 2, SCREEN_HEIGHT / 3 + 80, 20, globalState.players[1].getColor());

    DrawText(retryText, SCREEN_WIDTH / 2 - retryWidth / 2, SCREEN_HEIGHT / 2, 20, WHITE);
    DrawText(exitText, SCREEN_WIDTH / 2 - exitWidth / 2, SCREEN_HEIGHT / 2 + 40, 20, WHITE);

    // Handle user input for retry or exit
    if (IsKeyPressed(KEY_R)) {
        globalState.players[0].setScore(0);
        globalState.players[1].setScore(0);
        globalState.gamePage = ESGamePage::Game;
    }
}
