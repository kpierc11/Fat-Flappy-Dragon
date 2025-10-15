
#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>
#include <time.h>

#define TURKEY_LEG_AMOUNT 5

typedef struct
{
    Vector2 position;
    Texture2D texture;

} Dragon;

typedef struct
{
    Vector2 position;
    Texture2D texture;
} TurkeyLeg;

void UpdateTurkeyLeg(TurkeyLeg *leg)
{
    leg->position.x -= 3.0f;
}

int main(void)
{

    srand(time(NULL));

    const int screenWidth = 900;
    const int screenHeight = 900;
    float turkeyLegScale = 2.0f;
    float davyScale = 1.0f;

    Vector2 jumpAmount;
    jumpAmount.x = 0.0f;
    jumpAmount.y = -100.0f;

    Vector2 bottomScreen;
    bottomScreen.x = 0;
    bottomScreen.y = screenHeight;

    Color bgColor;
    bgColor.r = 135;
    bgColor.g = 206;
    bgColor.b = 250;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");

    InitAudioDevice();

    // Load Music
    Music fatDragonToons = LoadMusicStream("assets/chill-penguin.ogg");

    if (fatDragonToons.frameCount == 0)
    {
        CloseWindow();
        printf("Failed to load sound!\n");
        return -1;
    }

    // Create Dragon
    Dragon davy = {{100, 50}, LoadTexture("assets/sleeping-dragon.png")};
    davy.texture.height = 100;
    davy.texture.width = 100;

    SetTargetFPS(60);

    // Turkey Legs
    TurkeyLeg legs[TURKEY_LEG_AMOUNT];
    Texture2D legTexture = LoadTexture("assets/bad-turky-leg.png");

    if (legTexture.id == 0)
    {
        CloseWindow();
        printf("Failed to load texture!\n");
        return -1;
    }

    // Fill up the turky leg array
    for (int i = 0; i < TURKEY_LEG_AMOUNT; i++)
    {
        legs[i].position.x = rand() % 901;
        legs[i].position.y = rand() % 901;
        legs[i].texture = legTexture;
    }

    SetMasterVolume(1.0f);
    PlayMusicStream(fatDragonToons);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            davy.position.y += jumpAmount.y;
        }
 
        // Bounding box rectangles for davy and turky legs.
        Rectangle playerRec = {davy.position.x, davy.position.y, davy.texture.width * davyScale, davy.texture.height * davyScale};
        DrawRectangleLinesEx(playerRec, 5, RED);

        UpdateMusicStream(fatDragonToons);

        davy.position = Vector2Lerp(davy.position, bottomScreen, .5f * GetFrameTime());

        BeginDrawing();

        ClearBackground(bgColor);

        // Render all turky legs
        for (int i = 0; i < TURKEY_LEG_AMOUNT; i++)
        {
            UpdateTurkeyLeg(&legs[i]);
            if (legs[i].position.x <= -30)
                legs[i].position.x = 902;

            Rectangle enemyRec = {legs[i].position.x, legs[i].position.y, legs[i].texture.width, legs[i].texture.height};

            bool collision = CheckCollisionRecs(playerRec, enemyRec);
            if (collision)
            {
                DrawText("Turky leg eaten!!!", 50, 50, 20, GRAY);
                davyScale += .02f;
            }

            DrawTextureEx(legs[i].texture, legs[i].position, 0.0f, 2.0f, GRAY);
        }

        DrawTextureEx(davy.texture, davy.position, 0.0f, davyScale, GRAY);

        EndDrawing();
    }

    UnloadMusicStream(fatDragonToons); // Unload sound data

    CloseAudioDevice();

    UnloadTexture(legTexture);
    UnloadTexture(davy.texture);

    CloseWindow();

    return 0;
}