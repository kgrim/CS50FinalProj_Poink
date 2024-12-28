#include "paddle.h"

void Paddle::Update(int x, int y)
{
    const int screenHeight = GetScreenHeight();
    const int screenWidth = GetScreenWidth();

    if (paddleInfo.isVertical)
    {
        if (IsKeyDown(KEY_UP) && paddleInfo.y >= 0)
        {
            paddleInfo.y -= paddleInfo.speed;
        }

        if (IsKeyDown(KEY_DOWN) && paddleInfo.y + paddleInfo.height <= screenHeight)
        {
            paddleInfo.y += paddleInfo.speed;
        }   
    }
    else
    {
        if (IsKeyDown(KEY_LEFT) && paddleInfo.x >= 0)
        {
            paddleInfo.x -= paddleInfo.speed;
        }

        if (IsKeyDown(KEY_RIGHT) && paddleInfo.x + paddleInfo.width <= screenWidth)
        {
            paddleInfo.x += paddleInfo.speed;
        }  
    }
}

void Paddle::Draw() const
{
    DrawRectangle(paddleInfo.x, paddleInfo.y, paddleInfo.isVertical? paddleInfo.width : paddleInfo.height, paddleInfo.isVertical? paddleInfo.height : paddleInfo.width, paddleInfo.color);
}

void Paddle::UpdateNewValues(int newSpeed)
{
    if (paddleInfo.isVertical)
    {
        paddleInfo.y += newSpeed;
    }
    else
    {
        paddleInfo.x += newSpeed;
    }  
}

