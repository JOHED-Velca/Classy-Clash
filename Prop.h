#include<raylib.h>

class Prop
{
    public:
    Prop(Vector2 pos, Texture2D tex);
    void Render(Vector2 knightPos);
    Rectangle getCollisionRec(Vector2 knightPos);

    private:
    Texture2D prop_texture{}; //= LoadTexture("");
    Vector2 prop_worldPos{};
    float prop_scale{4.f};
};