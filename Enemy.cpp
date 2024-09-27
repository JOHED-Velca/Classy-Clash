#include "Enemy.h"
#include "raymath.h"
#include "Character.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width/maxFrames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float deltaTime)
{
    // Get the toTarget vector
    Vector2 toTarget = Vector2Subtract(target->getScreenPos(), screenPos);

    // Normalize the toTarget vector
    toTarget = Vector2Normalize(toTarget);

    // Multiply the toTarget vector by speed
    toTarget = Vector2Scale(toTarget, speed);

    // Move the Enemy (set worldPos)
    worldPos = Vector2Add(worldPos, toTarget);

    screenPos = Vector2Subtract(worldPos, target->getWorldPos());
    BaseCharacter::tick(deltaTime);
}