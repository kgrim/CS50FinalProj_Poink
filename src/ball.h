#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "paddle.h"

class Ball
{
public:
    Ball(int x, int y);
    void Update();
    void Draw() const;
    
    void CollisionMonitor(std::vector<std::unique_ptr<Paddle>>& paddles);
    void ResetBall();

    int x;
    int y;

private:
    int speedX;
    int speedY;
    int radius;
};