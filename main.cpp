#include "raylib.h"
#include "raymath.h"

// struct are public but classes can be private
class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPos{};
    Vector2 worldPos{};
    // 1: Facing right, -1: facing left
    float rightLeft{1.f};
    // animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f / 12.f};
    float speed{4.f};
};

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f), // f=to make it a float
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)       // (float) = C cast style
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
    Rectangle source{frame * (float)texture.width / 6.f, 0.f, rightLeft * (float)texture.width / 6.f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

int main()
{
    // Window Dimensions
    const int windowWidth{384};
    const int windowHeight{384};

    // initialize window
    InitWindow(windowWidth, windowHeight, "Top-Down section");

    // Map Texture
    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};

    Character knight;

    knight.setScreenPos(windowWidth, windowHeight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw Map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}