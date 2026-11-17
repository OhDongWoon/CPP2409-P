#ifndef ENEMY_H // ENEMY_H가 아직 정의되지 않았다면
#define ENEMY_H // 이 헤더를 읽었다는 표시를 남긴다

class Enemy
{
public:
    // 몬스터를 생성할 때 시작 위치
    Enemy(float x, float y);

    // 현재 위치에 몬스터를 그리기
    void Draw() const;

private:
    float x;
    float y;
};

#endif // 조건의 끝