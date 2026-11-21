#include "Player.h"
#include "raylib.h"
#include "World.h"
#include <algorithm>

// Player::Update : Player 클래스에 속한 Update 함수
void Player::Update(float deltaTime, const World &world)
{
    invincibleTime = std::max(0.0f, invincibleTime - deltaTime); // 남은 무적 시간을 줄이되 0 아래로 내려가지 않도록 한다
    const float oldX = playerX;                                  // 방향키 처리 전의 x좌표

    // 키 입력에 따른 위치 변경과 방향 전환
    // IsKeyDown : 키를 누르고 있는 동안 계속 true 반환
    if (IsKeyDown(KEY_RIGHT))
    {
        // 프레임 시간이 달라져도 이동 속도를 일정하게 유지하도록
        // 초당 이동 거리에 deltaTime을 곱한다
        playerX += playerSpeed * deltaTime;
        facingRight = true;
    }

    if (IsKeyDown(KEY_LEFT))
    {
        playerX -= playerSpeed * deltaTime;
        facingRight = false;
    }

    // 캐릭터가 화면 밖으로 나가지 않도록 제한
    if (playerX < 0.0f)
    {
        playerX = 0.0f;
    }

    // 맵의 오른쪽 끝에서 캐릭터 너비만큼 뺀 위치가 이동 한계다.
    const float maxX = world.GetWidth() - playerWidth;
    if (playerX > maxX)
    {
        playerX = maxX;
    }
    // 장애물 충돌
    playerX = world.ResolvePlayerX(oldX, playerX, playerY, playerWidth, playerHeight);

    // 점프 구현
    // 바닥에 있을 때 Space를 누르면 점프
    // IsKeyPressed : 키를 누른 순간만 true 반환
    // && : 두 조건이 모두 참일 때만 실행
    if (IsKeyPressed(KEY_SPACE) && onGround)
    {
        velocityY = jumpSpeed;
        onGround = false;
    }

    // 세로 이동 전의 머리와 발 위치를 기록한다.
    float oldHeadY = playerY;
    float oldFeetY = playerY + playerHeight;

    // 중력을 적용하고 세로 위치를 변경한다.
    velocityY += gravity * deltaTime;
    playerY += velocityY * deltaTime;

    onGround = false;

    if (velocityY < 0.0f)
    {
        // 위로 움직일 때는 머리와 지형 밑면의 충돌을 검사한다.
        float ceilingY = 0.0f;

        if (world.FindCeilingY(
                playerX, playerX + playerWidth,
                oldHeadY, playerY, ceilingY))
        {
            playerY = ceilingY;
            velocityY = 0.0f;
        }
    }
    else
    {
        // 내려올 때는 발과 지형 윗면의 충돌을 검사한다.
        float newFeetY = playerY + playerHeight;
        float landingY = 0.0f;

        if (world.FindLandingY(
                playerX, playerX + playerWidth,
                oldFeetY, newFeetY, landingY))
        {
            playerY = landingY - playerHeight;
            velocityY = 0.0f;
            onGround = true;
        }
    }
}

void Player::Draw() const
{
    // 캐릭터
    // DrawRectangle : 사각형을 그리는 함수
    // 인자 순서 : x좌표, y좌표, 너비, 높이, 색상
    // static_cast<int> : float형 위치 값을 int형으로 변환
    DrawRectangle(
        static_cast<int>(playerX),
        static_cast<int>(playerY),
        static_cast<int>(playerWidth),
        static_cast<int>(playerHeight),
        BLUE);

    // 캐릭터가 바라보는 방향 쪽에 눈 표시
    // 조건 ? 값1 : 값2
    // facingRight가 true면 28, false면 4를 선택
    int eyeX = static_cast<int>(playerX) + (facingRight ? 28 : 4);

    DrawRectangle(eyeX, static_cast<int>(playerY) + 12, 8, 8, WHITE);
}

int Player::GetHP() const
{
    return hp;
}

void Player::TakeDamage(int amount)
{
    // 무적 시간이거나 체력이 0이면 추가 피해를 받지 않는다.
    if (amount <= 0 || invincibleTime > 0.0f || hp <= 0)
    {
        return;
    }

    hp = std::max(0, hp - amount);
    invincibleTime = 1.0f;
}

// 플레이어의 현재 위치와 크기를 사각형으로 묶어 돌려주는 역할
Rectangle Player::GetBounds() const
{
    return {playerX, playerY, playerWidth, playerHeight};
}