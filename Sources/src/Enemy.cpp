#include "Enemy.h"
#include "raylib.h"

Enemy::Enemy(float x, float y, float left, float right, bool strong)
{
    this->x = x;
    this->y = y;

    patrolLeft = left;
    patrolRight = right;

    this->strong = strong;
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
    else
    { // movingRight == false

        x -= moveSpeed * deltaTime;

        if (x <= patrolLeft)
        {
            x = patrolLeft;
            movingRight = true;
        }
    }
}

void Enemy::Draw() const
{
    Color bodyColor = RED ; 

    if(strong) {
        bodyColor = PURPLE ; 
    }

    Rectangle body = {x, y, enemyWidth, enemyHeight};
    DrawRectangleRec(body, bodyColor);
}

Rectangle Enemy::GetBounds() const
{
    return {x, y, enemyWidth, enemyHeight};
}

int Enemy::GetContactDamage() const {
    if (strong) {
        return 20 ; 
    }
    return 10 ; 
}