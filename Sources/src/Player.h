#ifndef PLAYER_H
#define PLAYER_H

// 같은 헤더 파일이 중복으로 포함되는 것을 방지

class Player
{
public:
    // 키 입력, 이동, 점프 등 캐릭터 상태 갱신
    void Update(float deltaTime);

    // 캐릭터 그리기
    // const : 이 함수에서는 캐릭터의 데이터를 변경하지 않음
    void Draw() const;

private:
    // 캐릭터 위치와 속도
    float playerX = 100.0f; // 캐릭터의 x좌표
    const float playerSpeed = 300.0f; // 1초에 이동할 캐릭터의 거리

    // 점프에 필요한 변수
    float playerY = 380.0f; // 캐릭터 세로 위치
    float velocityY = 0.0f; // 현재 세로 속도
    const float gravity = 1200.0f; // 아래로 속도를 증가시키는 중력
    const float jumpSpeed = -500.0f; // 점프할 때의 초기 속도
    bool onGround = true; // 바닥에 있는지 여부

    // true : 오른쪽, false : 왼쪽을 바라봄
    bool facingRight = true;
};

#endif