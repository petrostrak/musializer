#include <stdio.h>
#include <unistd.h>

#include <raylib.h>

int main(void) 
{
    InitWindow(800, 600, "Musializer");
    SetTargetFPS(60);

    InitAudioDevice();

    Music music = LoadMusicStream("supersonic.ogg");
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);
        
        BeginDrawing();
        ClearBackground(RED);
        EndDrawing();
    }
    
    return 0;
}