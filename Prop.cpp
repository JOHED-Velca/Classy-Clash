#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex):prop_worldPos(pos), prop_texture(tex)
{
}

void Prop::Render(Vector2 knightPos)
{
    Vector2 screenPos{ Vector2Subtract(prop_worldPos, knightPos)};
    DrawTextureEx(prop_texture, screenPos, 0.f, prop_scale, WHITE);
}