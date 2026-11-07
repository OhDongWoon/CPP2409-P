#include "World.h"
#include "raylib.h"

namespace // namespace{} : 이 안에서 만든 이름은 .cpp 파일 전용으로 쓰겠다는 의미
{
    // x좌표, y좌표, 너비, 높이
    const Rectangle surfaces[] = {
        {220, 370, 150, 18}, // 첫 번째 발판
        {420, 310, 150, 18}, // 두 번째 발판
        {0, 440, 960, 100},  // 바닥
        {700, 380, 50, 60} // 장애물
    };
}

void World::Draw() const
{
    DrawRectangleRec(surfaces[2], DARKGREEN); // 바닥
    DrawRectangleRec(surfaces[0], BROWN);     // 첫 번째 발판
    DrawRectangleRec(surfaces[1], BROWN);     // 두 번째 발판
    DrawRectangleRec(surfaces[3], DARKGRAY); // 장애물
}

bool World::FindLandingY(float left, float right,
                         float oldFeetY, float newFeetY,
                         float& landingY) const
{
    bool found = false;

    for (const Rectangle& surface : surfaces)
    {
        // 캐릭터와 지형이 가로로 겹치는지 확인
        bool overlapsX = right > surface.x && left < surface.x + surface.width;

        // 발이 이번 프레임에 지형의 윗면에 닿거나 지나갔는지 확인
        bool crossesTop = oldFeetY <= surface.y && newFeetY >= surface.y;

        // 여러 지형을 지나쳤다면 먼저 닿는 위쪽 지형을 선택
        if (overlapsX && crossesTop && (!found || surface.y < landingY)) {
            landingY = surface.y;
            found = true;
        }
    }
    return found;
}

// 옆면 충돌 함수
float World::ResolvePlayerX(float oldX, float newX, float y,
                            float width, float height) const
{
    const Rectangle& obstacle = surfaces[3];
    const float obstacleRight = obstacle.x + obstacle.width;
    const float obstacleBottom = obstacle.y + obstacle.height;

    // 캐릭터가 장애물보다 위나 아래에 있으면 가로 이동을 허용한다.
    if (y + height <= obstacle.y || y >= obstacleBottom)
    {
        return newX;
    }

    // 오른쪽으로 이동하다 장애물 왼쪽 면을 넘으려는 경우
    if (oldX + width <= obstacle.x && newX + width > obstacle.x)
    {
        return obstacle.x - width;
    }

    // 왼쪽으로 이동하다 장애물 오른쪽 면을 넘으려는 경우
    if (oldX >= obstacleRight && newX < obstacleRight)
    {
        return obstacleRight;
    }

    return newX;
}