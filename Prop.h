#include<raylib.h>

class Prop
{
    public:
    Prop();

    private:
    Texture2D prop_texture = LoadTexture("");
    Vector2 prop_worldPos{};
    float prop_scale;
};