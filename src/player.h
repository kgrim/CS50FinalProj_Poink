#pragma once

#include <memory>
#include <raylib.h>
#include <vector>
#include "paddle.h"

class Player
{
public:
    // Default constructor
    Player();

    // Parameterized constructor
    Player( Color initialColor, bool isAI, bool isVertical);

    void UpdateAndDraw(int x, int y);

    void setScore(int inScore);
    int getScore();
    Color getColor();

    bool isAI;
    std::vector<std::unique_ptr<Paddle>> paddles;

private:
    int score;
    Color color;
};
