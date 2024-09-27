#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}
void BaseCharacter::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    

    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        // update animation frame

        if (frame > maxFrames)
            frame = 0; // this frame tells us which animation from the sp we choose
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPos + direction
        // direction = scaling the normalized direction vector by speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; // ternary operator = if else with one condition
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // Draw Character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}