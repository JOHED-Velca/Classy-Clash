#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

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
}
void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale
    };
}