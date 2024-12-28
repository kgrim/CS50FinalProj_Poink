#include "ai.h"
#include <raylib.h>

PaddleAI::PaddleAI(int initX, int initY, int initSpeed, bool movesVertical, Color color)
    : Paddle(initX, initY, initSpeed, movesVertical, color)
{
}

void PaddleAI::Update(int x, int y)
{
    const FPaddleInfo currentPaddle = getPaddleInfo(); 
    int newSpeed;
    if (currentPaddle.isVertical)
    {
        newSpeed = currentPaddle.y + currentPaddle.height/2 > y ? - currentPaddle.speed : currentPaddle.speed;
    }
    else
    {    
        newSpeed = currentPaddle.x + currentPaddle.width/2 > x ? - currentPaddle.speed : currentPaddle.speed;
    }
    
    UpdateNewValues(newSpeed);
}