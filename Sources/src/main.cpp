#include "raylib.h"
#include "Player.h"
#include "World.h"
#include "Enemy.h"
#include <algorithm>

int main()
{
    // 게임 창 만들기
    InitWindow(960, 540, "CPP2409-P");

    // 목표 FPS 설정
    SetTargetFPS(60);

    // Player 클래스로 실제 캐릭터 객체 생성
    // 게임 루프 밖에서 생성하여 위치와 상태를 계속 유지
    Player player;
    World world;
    // 몬스터 4마리 생성
    Enemy enemies[] = {
        {650.0f, 390.0f, 600.0f, 660.0f},
        {950.0f, 390.0f, 850.0f, 980.0f},
        {1550.0f, 390.0f, 1450.0f, 1600.0f},
        {1800.0f, 390.0f, 1680.0f, 1860.0f}
    };
    const int enemyCount = 4 ; 

    Camera2D camera{};
    camera.zoom = 1.0f;

    // 게임 루프 -> 창이 닫히기 전까지 계속 반복
    while (!WindowShouldClose())
    {
        // 이전 프레임부터 지난 시간 (단위 : 초)
        float deltaTime = GetFrameTime();

        // 몬스터 움직임
        for (int i = 0 ; i < enemyCount; i++){
            enemies[i].Update(deltaTime);

            if(CheckCollisionRecs(player.GetBounds(), enemies[i].GetBounds())){
                player.TakeDamage(10);
            }
        }

        // 캐릭터의 키 입력, 이동, 점프 처리
        player.Update(deltaTime, world);
        // 캐릭터의 가운데를 따라가되, 맵 양 끝에서 멈춘다.
        const float screenWidth = static_cast<float>(GetScreenWidth());
        camera.target.x = std::clamp(
            player.GetX() + 20.0f - screenWidth / 2.0f,
            0.0f,
            world.GetWidth() - screenWidth);
        // 화면 그리기 시작
        BeginDrawing();

        // 이전 화면을 지우고 배경색 설정
        ClearBackground(SKYBLUE);

        BeginMode2D(camera);
        // 바닥
        // 변수 : x좌표, y좌표, 너비, 높이, 색상);
        world.Draw();
        // 갱신된 위치에 캐릭터 그리기
        player.Draw();
        // 몬스터 그리기
        for(int i = 0 ; i < enemyCount ; i++){
            enemies[i].Draw();
        }
        EndMode2D();

        // 제목 표시
        DrawText("Side-scroller Game", 30, 30, 30, DARKGRAY);

        // 체력 표시
        DrawText(TextFormat("HP: %d", player.GetHP()), 30, 70, 24, DARKGRAY);

        // 화면 그리기 끝
        EndDrawing();
    }

    // 게임 창과 관련 자원 정리
    CloseWindow();

    // 프로그램 정상 종료
    return 0;
}