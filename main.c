#include <stdio.h>

#include <raylib.h>

int main(void) 
{
    InitAudioDevice();
    Sound sound = LoadSound("supersonic.ogg");
    
    return 0;
}