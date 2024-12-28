#include "ball.h"
#include <raylib.h>

Ball::Ball(int x, int y) 
    : x(x)
    , y(y)
    , speedX(5)
    , speedY(5)
    , radius(15) 
{
}

void Ball::Update() 
{
    x += speedX;
    y += speedY;
    
    const int screenHeight = GetScreenHeight();
}

void Ball::Draw() const
{
    DrawCircle(x, y, radius, WHITE);
}

void Ball::CollisionMonitor(std::vector<std::unique_ptr<Paddle>>& paddles)
{

    for (const auto& paddle : paddles) {
        if (paddle) {
           const FPaddleInfo paddleInfo =  paddle->getPaddleInfo();

           Rectangle rectangleCollisionBox = Rectangle{(float)paddleInfo.x, (float)paddleInfo.y, paddleInfo.isVertical? (float)paddleInfo.width : (float)paddleInfo.height, paddleInfo.isVertical? (float)paddleInfo.height : (float)paddleInfo.width};

            if (CheckCollisionCircleRec(Vector2{(float)x, (float)y}, radius, rectangleCollisionBox))
            {
                if (paddleInfo.isVertical)
                {
                    speedX *= -1;
                }
                else
                {
                    speedY *= -1;
                }
            }
        }
    }
   
}

void Ball::ResetBall()
{
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speed_choices[2] = {-1, 1};

    speedX *= speed_choices[GetRandomValue(0,1)];
    speedY *= speed_choices[GetRandomValue(0,1)];
}
