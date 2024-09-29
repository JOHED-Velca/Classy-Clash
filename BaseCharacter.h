#ifndef BASECHARACTER_H
#define BASECHARACTER_H
#include "raylib.h"

class BaseCharacter
{
public:
    BaseCharacter();
    virtual void tick(float deltaTime);
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual Vector2 getScreenPos() = 0; //pure virtual function (because it equals 0)
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }
protected:
    float width{};
    float height{};
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1: Facing right, -1: facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.0f};
    float scale{4.0f};
    Vector2 velocity{};
private:
    bool alive{true};
};
#endif