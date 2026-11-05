#include "raylib.h"

int main()
{
    // 게임 창 만들기
    InitWindow(960, 540, "CPP2409-P");
    // 목표 FPS 설정 -> 1초에 화면을 60번 갱신 (프레임)
    SetTargetFPS(60);

    // 캐릭터 위치와 속도
    float playerX = 100.0f; // playerX : 캐릭터의 x좌표
    const float playerSpeed = 300.0f; // playerSpeed : 1초에 이동할 캐릭터의 거리
    
    // 점프에 필요한 변수
    float playerY = 380.0f; // 캐릭터 세로 위치
    float velocityY = 0.0f; // 현재 세로의 속도
    const float gravity = 1200.0f; // 아래로 속도를 증가시키는 중력
    const float jumpSpeed = -500.0f; // 점프할 때의 초기 속도
    bool onGround = true; // 바닥에 있는지 여부


    // 게임루프 -> 창이 닫히기 전까지 계속 반복
    while (!WindowShouldClose())
    {
        // 키 입력에 따른 위치 변경
        float deltaTime = GetFrameTime();

        if (IsKeyDown(KEY_RIGHT))
        {
            playerX += playerSpeed * deltaTime; // 프레임이 느려도 캐릭터가 일정한 속도로 움직이도록 하기 위해 deltaTime을 곱한다
        }

        if (IsKeyDown(KEY_LEFT))
        {
            playerX -= playerSpeed * deltaTime;
        }

        // 캐릭터가 화면 밖으로 나가지 않도록 제한
        if (playerX < 0.0f)
        {
            playerX = 0.0f;
        }
        if (playerX > 920.0f)
        {
            playerX = 920.0f; // 화면 너비 = 960, 캐릭터 너비 = 40 이므로 960-40 = 920
        }
        
        // 점프 구현
        // 바닥에 있을 때 Space를 누르면 점프
        if (IsKeyPressed(KEY_SPACE) && onGround) // IsKeyPressed : 키를 누른 순간만 true 반환, IsKeyDown : 키를 누르고 있는 동안 계속 true 반환
        {
            velocityY = jumpSpeed;
            onGround = false;
        }

        // 중력으로 속도를 바꾸고, 속도로 위치를 바꿈
        velocityY += gravity * deltaTime;
        playerY += velocityY * deltaTime;

        // 발이 바닥에 닿으면 착지
        if (playerY >= 380.0f)
        {
            playerY = 380.0f;
            velocityY = 0.0f;
            onGround = true;
        }

        // 화면 그리기
        BeginDrawing();

        ClearBackground(SKYBLUE);

    // 바닥: x좌표, y좌표, 너비, 높이, 색상 -> DrawRectangle : 사각형 그리는 함수
    DrawRectangle(0, 440, 960, 100, DARKGREEN);

    // 캐릭터
    // static_cast<int>(playerX) : float형 playerX를 int형으로 변환
    DrawRectangle(static_cast<int>(playerX), static_cast<int>(playerY), 40, 60, BLUE);

    DrawText("My action game", 30, 30, 30, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}