#include "raylib.h"
#include "raymath.h"

int main()
{
    //Window Dimensions
    int windowDimensions[2];
    windowDimensions[0] = 384;
    windowDimensions[1] = 384;

    //initialize window
    InitWindow(windowDimensions[0], windowDimensions[1], "Top-Down section");

    //Map Texture
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    float speed{4.0};
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos{
        (float)windowDimensions[0]/2.0f - 4.0f * (0.5 * (float)knight.width/6.0f), //f=to make it a float
        (float)windowDimensions[1]/2.0f - 4.0f * (0.5 * (float)knight.height) // (float) = C cast style
    };

    //1: Facing right, -1: facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        //Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        if(Vector2Length(direction) != 0.0)
        {
            // set mapPos = mapPos - direction
            //direction = scaling the normalized direction vector by speed
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; // ternary operator = if else with one condition
            knight = knight_run;
        }
        else
        {
            knight = knight_idle;
        }

        //Draw Map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        //Update Animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            //update animation frame
            
            if (frame > maxFrames) frame = 0; // this frame tells us which animation from the sp we choose
        }

        //Draw Character
        Rectangle source {frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};
        Rectangle dest {knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);


        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(knight);
    UnloadTexture(knight_idle);
    UnloadTexture(knight_run);
    CloseWindow();
}