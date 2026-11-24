#ifndef ENEMY_H // ENEMY_H가 아직 정의되지 않았다면
#define ENEMY_H // 이 헤더를 읽었다는 표시를 남긴다
#include "raylib.h"

class Enemy
{
public:
    // 몬스터를 생성할 때 시작 위치
    Enemy(float x, float y, float left, float right , bool strong); // strong : 강화 몬스터

    // 현재 위치에 몬스터를 그리기
    void Draw() const;

    // 몬스터가 움직이기 위해 시간에 따라 위치가 바뀌게 하는 함수
    void Update(float deltaTime);
    
    // 몬스터 충돌 판정용 사각형 반환
    Rectangle GetBounds() const;
private:
    // 위치 변수
    float x;
    float y;
    // 몬스터 움직임 변수
    float moveSpeed = 100.0f ; // 초당 이동 거리
    // 몬스터가 왔다갔다 하는 위치의 범위
    float patrolLeft ;
    float patrolRight ;
    bool movingRight = true ; // true이면 오른쪽으로 이동
    // 몬스터의 너비와 높이
    const float enemyWidth = 40.0f;
    const float enemyHeight = 50.0f;
    // 강화 몬스터
    bool strong ; 
};  

#endif // 조건의 끝