#include "player.h"

#include "ai.h"
#include <raylib.h>

// Default constructor
Player::Player()
    : score(0), color(WHITE), isAI(false) {
        paddles.push_back(std::make_unique<Paddle>());
        paddles.push_back(std::make_unique<Paddle>());
      } // Initialize paddles in the default constructor

// Parameterized constructor
Player::Player(Color initialColor, bool isAI, bool isVertical)
    : score(0), color(initialColor), isAI(isAI) {

        int newX = isVertical? GetScreenWidth() - 25 : GetScreenWidth() / 2 - 120 / 2;
        int newY = isVertical? GetScreenHeight() / 2 - 120 / 2 : GetScreenHeight() - 25;
        int padding = 10;
        int speed = 5;

    if (isAI) {
        // Initialize AIPaddle if the player is AI
        paddles.push_back(std::make_unique<PaddleAI>(newX, padding, speed, false, color));
        paddles.push_back(std::make_unique<PaddleAI>(newX, newY - padding, speed, false, color));
    } else {
        if (isVertical)
        {
            paddles.push_back(std::make_unique<Paddle>(padding, newY, speed, isVertical, color));
            paddles.push_back(std::make_unique<Paddle>(newX - padding, newY, speed, isVertical, color));
        }
        else
        {
            paddles.push_back(std::make_unique<Paddle>(newX, padding, speed, isVertical, color));
            paddles.push_back(std::make_unique<Paddle>(newX, newY - padding, speed, isVertical, color));
        }

    }

} // Initialize paddles with provided color

void Player::UpdateAndDraw(int x, int y)
{
    for (const auto& paddle : paddles)
    {
        paddle->Update(x, y);
        paddle->Draw();
    }
}

// Member function implementations
void Player::setScore(int inScore) {
    score = inScore;
}

int Player::getScore() {
    return score;
}

Color Player::getColor() {
    return color;
}
