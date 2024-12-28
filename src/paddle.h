#pragma once
#include <raylib.h>
#include <iostream>

struct FPaddleInfo 
{
    int x;
    int y;
    int speed;
    int width;
    int height;
    bool isVertical;
    Color color;

    // Default constructor
    FPaddleInfo()
        : x(0), y(0), speed(5), width(25), height(120), isVertical(true), color(WHITE) // Default color set here
    {
    }
};

class Paddle
{
public:

    Paddle(){};

    // Constructor with initialization of paddle info
    Paddle(int initX, int initY, int initSpeed, bool movesVertical, Color color)
    {
        paddleInfo.x = initX;
        paddleInfo.y = initY;
        paddleInfo.speed = initSpeed;
        paddleInfo.isVertical = movesVertical;
        paddleInfo.color = color;
        paddleInfo.width = 25; // Default width, can be overridden
        paddleInfo.height = 120; // Default height, can be overridden
    }

    virtual void Update(int x, int y);
    void Draw() const;

    const FPaddleInfo getPaddleInfo() const { return paddleInfo; }
    void UpdateNewValues(int newSpeed);

private:
    FPaddleInfo paddleInfo;
};
