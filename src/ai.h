#pragma once

#include <iostream>
#include "paddle.h"

class PaddleAI : public Paddle
{
    public:
        PaddleAI(int initX, int initY, int initSpeed, bool movesVertical, Color color);
        void Update(int x, int y);
};