#include "Player.h"
#include "raylib.h"

// Player::Update : Player 클래스에 속한 Update 함수
void Player::Update(float deltaTime)
{
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

    if (playerX > 920.0f)
    {
        // 화면 너비 = 960, 캐릭터 너비 = 40
        // 따라서 가장 오른쪽 x좌표는 960 - 40 = 920
        playerX = 920.0f;
    }

    // 점프 구현
    // 바닥에 있을 때 Space를 누르면 점프
    // IsKeyPressed : 키를 누른 순간만 true 반환
    // && : 두 조건이 모두 참일 때만 실행
    if (IsKeyPressed(KEY_SPACE) && onGround)
    {
        velocityY = jumpSpeed;
        onGround = false;
    }

    // 중력으로 속도를 바꾸고, 속도로 위치를 바꿈
    // 화면 좌표에서는 아래쪽이 +이므로 중력을 더한다
    velocityY += gravity * deltaTime;
    playerY += velocityY * deltaTime;

    // 발이 바닥에 닿으면 착지
    // 바닥 y좌표 440 - 캐릭터 높이 60 = 380
    if (playerY >= 380.0f)
    {
        playerY = 380.0f;
        velocityY = 0.0f;
        onGround = true;
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
        40,
        60,
        BLUE
    );

    // 캐릭터가 바라보는 방향 쪽에 눈 표시
    // 조건 ? 값1 : 값2
    // facingRight가 true면 28, false면 4를 선택
    int eyeX = static_cast<int>(playerX)
               + (facingRight ? 28 : 4);

    DrawRectangle(eyeX, static_cast<int>(playerY) + 12, 8, 8, WHITE);
}