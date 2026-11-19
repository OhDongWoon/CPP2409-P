#include "Enemy.h"
#include "raylib.h"

Enemy::Enemy(float x, float y)
{
    this->x = x;
    this->y = y;
}

// 몬스터가 왼쪽 오른쪽으로 왔다갔다 움직임
void Enemy::Update(float deltaTime)
{
    if (movingRight == true)
    {
        x = x + moveSpeed * deltaTime;
        if (x >= patroRight)
        {
            x = patroRight;
            movingRight = false;
        }
    }
    else { // movingRight == flase
        x = x - moveSpeed * deltaTime;
        
        if (x <= patroLeft){
            x = patroLeft;
            movingRight = true;
        }
    }
}

void Enemy::Draw() const
{
    DrawRectangle(
        static_cast<int>(x),
        static_cast<int>(y),
        40,
        50,
        RED);
}

Rectangle Enemy::GetBounds() const
{
    return {x, y, 40.0f, 50.0f};
}