
#include "raylib.h"


typedef struct {
    Vector2 position;
    Texture2D texture;
} Dragon;

 void UpdateDragon(Dragon* dragon)
 {
    dragon->position.x += .5f;
    dragon->position.y += .5f;
 }


int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");

    Texture2D texture = LoadTexture("assets/bad-turky-leg.png");
    Texture2D texture1 = LoadTexture("assets/bad-turky-leg.png");
    Texture2D texture2 = LoadTexture("assets/bad-turky-leg.png");

    Dragon davy = {{50,50}, LoadTexture("assets/sleeping-dragon.png") };

    if (texture.id == 0)
    {
        CloseWindow();
        printf("Failed to load texture!\n");
        return -1;
    }

    Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};

    // Vector2 mousePos =  GetMousePosition();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))
            davy.position.x += 2.0f;
        if (IsKeyDown(KEY_LEFT))
            davy.position.x -= 2.0f;
        if (IsKeyDown(KEY_UP))
           davy.position.y -= 2.0f;
        if (IsKeyDown(KEY_DOWN))
            davy.position.y += 2.0f;

        Vector2 mousePos = GetMousePosition();

        UpdateDragon(&davy);

        BeginDrawing();

        ClearBackground(BLACK);


        DrawTexture(texture, mousePos.x, mousePos.y, GRAY);
        DrawTexture(texture1, 50, 50, GRAY);
        DrawTexture(texture2, 100, 100, GRAY);
        DrawTexture(davy.texture, davy.position.x, davy.position.y, GRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}