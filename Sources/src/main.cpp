#include "raylib.h"
#include "Player.h"

int main()
{
    // 게임 창 만들기
    InitWindow(960, 540, "CPP2409-P");

    // 목표 FPS 설정 -> 1초에 화면을 60번 갱신하는 것을 목표로 함
    SetTargetFPS(60);

    // Player 클래스로 실제 캐릭터 객체 생성
    // 게임 루프 밖에서 생성하여 위치와 상태를 계속 유지
    Player player;

    // 게임 루프 -> 창이 닫히기 전까지 계속 반복
    while (!WindowShouldClose())
    {
        // 이전 프레임부터 지난 시간 (단위 : 초)
        float deltaTime = GetFrameTime();

        // 캐릭터의 키 입력, 이동, 점프 처리
        player.Update(deltaTime);

        // 화면 그리기 시작
        BeginDrawing();

        // 이전 화면을 지우고 배경색 설정
        ClearBackground(SKYBLUE);

        // 바닥
        // 인자 순서 : x좌표, y좌표, 너비, 높이, 색상
        DrawRectangle(0, 440, 960, 100, DARKGREEN);

        // 갱신된 위치에 캐릭터 그리기
        player.Draw();

        // 제목 표시
        DrawText("My action game", 30, 30, 30, DARKGRAY);

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