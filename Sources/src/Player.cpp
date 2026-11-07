#include "Player.h"
#include "raylib.h"
#include "World.h"
#include <algorithm>

// Player::Update : Player 클래스에 속한 Update 함수
void Player::Update(float deltaTime, const World& world)
{
    const float playerWidth = 40.0f;
    const float playerHeight = 60.0f;
    const float oldX = playerX; // 방향키 처리 전의 x좌표

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
    

    // 이동하기 전의 발 위치를 기록한다.
    float oldFeetY = playerY + playerHeight;

    // 중력을 적용하고 이번 프레임의 위치를 계산한다.
    velocityY += gravity * deltaTime;
    playerY += velocityY * deltaTime;

    float newFeetY = playerY + playerHeight;
    float landingY = 0.0f;
    onGround = false;

    // 아래로 움직일 때만 착지를 검사한다.
    if (velocityY >= 0.0f && world.FindLandingY(playerX, playerX + playerWidth, oldFeetY, newFeetY, landingY)) {
    // 캐릭터의 발이 지형 윗면에 딱 맞도록 위치를 조정한다.
    playerY = landingY - playerHeight;
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
    DrawRectangle( static_cast<int>(playerX), static_cast<int>(playerY), 40, 60, BLUE);

    // 캐릭터가 바라보는 방향 쪽에 눈 표시
    // 조건 ? 값1 : 값2
    // facingRight가 true면 28, false면 4를 선택
    int eyeX = static_cast<int>(playerX)
               + (facingRight ? 28 : 4);

    DrawRectangle(eyeX, static_cast<int>(playerY) + 12, 8, 8, WHITE);
}

int Player::GetHP() const
{
    return hp;
}

void Player::TakeDamage(int amount){
    if(amount <= 0) {
        return ; // 피해량이 0 이하이면 무시
    }

    // 체력이 0 이하로 떨어지면 0 , 그렇지 않으면 hp = hp - amount
    hp = std::max(0, hp - amount); 
}