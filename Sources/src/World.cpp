#include "World.h"
#include "raylib.h"

namespace // namespace{} : 이 안에서 만든 이름은 .cpp 파일 전용으로 쓰겠다는 의미
{
    // x좌표, y좌표, 너비, 높이
    const Rectangle surfaces[] = {
        {220, 340, 150, 18}, // 첫 번째 발판
        {420, 310, 150, 18}, // 두 번째 발판
        {0, 440, World::width, 100}, // 바닥 (맵 크기를 확장하기 위함)
        {700, 380, 50, 60}, // 회색 장애물
        {1050, 345, 150, 18}, // 오른쪽 구간 첫 번째 발판
        {1300, 345, 150, 18}, // 오른쪽 구간 두 번째 발판 : 처음에 1240이었는데 캐릭터와 겹쳐 떨어지지 않는 문제 발생 -> 1300으로 수정
    };
}

void World::Draw() const
{
    DrawRectangleRec(surfaces[2], DARKGREEN); // 바닥
    DrawRectangleRec(surfaces[0], BROWN);     // 첫 번째 발판
    DrawRectangleRec(surfaces[1], BROWN);     // 두 번째 발판
    DrawRectangleRec(surfaces[4], BROWN);     // 오른쪽 구간 첫 번째 발판
    DrawRectangleRec(surfaces[5], BROWN);     // 오른쪽 구간 두 번째 발판
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

// 바닥, 발판, 장애물의 옆면 충돌 처리
float World::ResolvePlayerX(float oldX, float newX, float y,
                            float width, float height) const
{
    float resolvedX = newX;

    for (const Rectangle& surface : surfaces)
    {
        const float surfaceRight = surface.x + surface.width;
        const float surfaceBottom = surface.y + surface.height;

        // 세로로 겹치지 않으면 이 지형의 옆면에는 부딪히지 않는다.
        if (y + height <= surface.y || y >= surfaceBottom)
        {
            continue;
        }

        // 오른쪽으로 이동하다 지형의 왼쪽 면을 넘는 경우
        if (oldX + width <= surface.x &&
            resolvedX + width > surface.x)
        {
            resolvedX = surface.x - width;
        }

        // 왼쪽으로 이동하다 지형의 오른쪽 면을 넘는 경우
        if (oldX >= surfaceRight && resolvedX < surfaceRight)
        {
            resolvedX = surfaceRight;
        }
    }

    return resolvedX;
}


// 밑면 충돌 함수
bool World::FindCeilingY(float left, float right,
                         float oldHeadY, float newHeadY,
                         float& ceilingY) const
{
    bool found = false;

    for (const Rectangle& surface : surfaces)
    {
        const float surfaceBottom = surface.y + surface.height;

        bool overlapsX = right > surface.x &&
                         left < surface.x + surface.width;

        // 위로 이동하는 머리가 지형의 밑면에 닿거나 지나갔는지 검사
        bool crossesBottom = oldHeadY >= surfaceBottom &&
                             newHeadY <= surfaceBottom;

        // 위로 가면서 가장 먼저 만나는 밑면을 선택
        if (overlapsX && crossesBottom &&
            (!found || surfaceBottom > ceilingY))
        {
            ceilingY = surfaceBottom;
            found = true;
        }
    }

    return found;
}