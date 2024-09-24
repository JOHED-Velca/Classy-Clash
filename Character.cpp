#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight)
{
    width = texture.width/maxFrames;
    height = texture.height;
    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scale * (0.5f * width), // f=to make it a float
        static_cast<float>(winHeight) / 2.0f - scale * (0.9f * height) // (float) = C cast style
    };
}

void Character::tick(float deltaTime)
{
    BaseCharacter::tick(deltaTime);
    //-------------------------Child Stuff-------------------------
    worldPosLastFrame = worldPos;
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction
        // direction = scaling the normalized direction vector by speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; // ternary operator = if else with one condition
        texture = run;
    }
    else
    {
        texture = idle;
    }
}