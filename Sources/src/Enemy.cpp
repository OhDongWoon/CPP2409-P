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
    if (movingRight)
    {
        x += moveSpeed * deltaTime;
        
        if (x >= patrolRight)
        {
            x = patrolRight;
            movingRight = false;
        }
    }
    else { // movingRight == flase
        
        x -= moveSpeed * deltaTime;
        
        if (x <= patrolLeft){
            x = patrolLeft;
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