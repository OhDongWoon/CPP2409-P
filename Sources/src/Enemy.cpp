#include "Enemy.h"
#include "raylib.h"

Enemy::Enemy(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Enemy::Draw() const
{
    DrawRectangle(
        static_cast<int>(x),
        static_cast<int>(y),
        40,
        50,
        RED
    );
}