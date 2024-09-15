#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width/maxFrames;
    height = texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width), // f=to make it a float
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)       // (float) = C cast style
    };
}

void Character::tick(float deltaTime)
{
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

    // Update Animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        // update animation frame

        if (frame > maxFrames)
            frame = 0; // this frame tells us which animation from the sp we choose
    }

    // Draw Character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}