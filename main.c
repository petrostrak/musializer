#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <complex.h>
#include <assert.h>

#include <raylib.h>

#define ARRAY_LEN(xs) sizeof(xs)/sizeof(xs[0])

typedef struct
{
    float left;
    float right;
} Frame;


Frame global_frames[4080] = {0};
size_t global_frames_count = 0;

void callback(void *bufferData, unsigned int frames)
{
    size_t capacity = ARRAY_LEN(global_frames);
    if (frames <= capacity - global_frames_count)
    {
        memcpy(global_frames + global_frames_count, bufferData, sizeof(Frame)*frames);
        global_frames_count += frames;
    } else if (frames <= capacity)
    {
        memmove(global_frames, global_frames + frames, sizeof(Frame)*(capacity-frames));
        memcpy(global_frames + (capacity - frames), bufferData, sizeof(Frame)*frames);
    } else
    {
        memcpy(global_frames, bufferData, sizeof(Frame)*capacity);
        global_frames_count = capacity;
    }
}

void dft(float in[], float complex out[], size_t n)
{
    for (size_t f = 0; f < n; f++)
    {
        out[f] = 0;
        for (size_t i = 0; i < n; i++)
        {
            float t = (float)i/n;
            out[f] += in[i]*cexp(2*I*PI*f*t);
        }
        
    }
    
}

void fft(float in[], size_t stride, float complex out[], size_t n)
{
    assert(n > 0); 
    if (n == 1) 
    {
        out[0] = in[0];
        return;
    }
    
    fft(in, stride*2, out, n/2);
    fft(in + stride, stride*2, out + n/2, n/2);

    for (size_t k = 0; k < n/2; k++)
    {
        float t = (float)k/n;
        float complex v = cexp(-2*I*PI*t)*out[k+n/2];
        float complex e = out[k];
        out[k] = e + v;
        out[k+n/2] = e - v;
    }
}

int main(void) 
{
    InitWindow(800, 600, "Musializer");
    SetTargetFPS(60);

    InitAudioDevice();

    Music music = LoadMusicStream("supersonic.ogg");
    SetMusicVolume(music, 0.2);
    PlayMusicStream(music);

    AttachAudioStreamProcessor(music.stream, callback);

    while (!WindowShouldClose()) 
    {
        UpdateMusicStream(music);

        if (IsKeyPressed(KEY_SPACE))
        {   
            if (IsMusicStreamPlaying(music))
            {
                PauseMusicStream(music);
            } else 
            {
                ResumeMusicStream(music);
            }
            
        }
        
        int w = GetRenderWidth();
        int h = GetRenderHeight();

        BeginDrawing();
        ClearBackground(CLITERAL(Color) {0x18, 0x18, 0x18, 0xFF});

        float cell_width = (float)w/global_frames_count;
        for (size_t i = 0; i < global_frames_count; i++)
        {
            float t = global_frames[i].left;
            if (t > 0)
            {
                DrawRectangle(i*cell_width, h/2 - h/2*t, 1, h/2*t, RED);
            } else
            {
                DrawRectangle(i*cell_width, h/2, 1, h/2*t, RED);
            }
        }
        
        EndDrawing();
    }
    
    return 0;
}