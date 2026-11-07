#ifndef WORLD_H
#define WORLD_H

class World
{
public:
    // 바닥, 발판, 장애물을 화면에 그리는 함수
    void Draw() const;

    // 장애물 옆면에 막히면 이동할 x좌표 조정
    float ResolvePlayerX(float oldX, float newX, float y, float width, float height) const;



    // 캐릭터의 착지 판정 함수
    // left : 캐릭터 왼쪽 끝 x좌표 , right ; 캐릭터 오른쪽 끝 x좌표
    // oldFeetY : 이동하기 전 발밑의 y좌표, newFeetY : 이동한 후 발밑의 y좌표
    // landingY : 착지한 y좌표를 반환하는 참조형 매개변수
    // 착지하지 못하면 false, 착지하면 true 반환
    bool FindLandingY(float left, float right, float oldFeetY, float newFeetY, float& landingY) const;
};

#endif