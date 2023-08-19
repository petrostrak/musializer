#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <raylib.h>

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])

uint32_t global_frames[1024];
size_t global_frames_count = 0;

void callback(void *bufferData, unsigned int frames)
{
    if (frames > ARRAY_LEN(global_frames))
    {
        frames = ARRAY_LEN(global_frames);
    }
    
    memcpy(global_frames, bufferData, sizeof(uint32_t)*frames);
    global_frames_count = frames;
}

int main(void) 
{
    InitWindow(800, 600, "Musializer");
    SetTargetFPS(60);

    InitAudioDevice();

    Music music = LoadMusicStream("supersonic.ogg");
    PlayMusicStream(music);

    AttachAudioStreamProcessor(music.stream, callback);

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);

        if (IsKeyPressed(KEY_SPACE))
        {   
            if (IsMusicStreamPlaying(music))
            {
                PauseMusicStream(music);
            } else {
                ResumeMusicStream(music);
            }
            
        }
        
        
        BeginDrawing();
        ClearBackground(CLITERAL(Color) {0x18, 0x18, 0x18, 0xFF});
        float cell_width = (float)GetRenderWidth()/global_frames_count;
        for (size_t i = 0; i < global_frames_count; i++)
        {
            int16_t sample = *(int16_t*)&global_frames[i];
            printf("%d\n", sample);
        }
        // if (global_frames_count > 0) exit(1);s
        EndDrawing();
    }
    
    return 0;
}