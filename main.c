#include <stdio.h>
#include <unistd.h>

#include <raylib.h>

int main(void) 
{
    InitAudioDevice();
    Sound sound = LoadSound("supersonic.ogg");
    // Music music = LoadMusicStream("supersonic.ogg");
    PlaySound(sound);
    sleep(211);
    
    return 0;
}