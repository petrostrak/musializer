## Music visualizer in C
A music visualizer written in C

On linux the following env variables must be exported:
```bash
export PKG_CONFIG_PATH="$HOME/opt/raylib/lib/pkgconfig/:$PKG_CONFIG_PATH"
export LD_LIBRARY_PATH="$HOME/opt/raylib/lib/:$LD_LIBRARY_PATH"
#export LD_LIBRARY_PATH=/usr/local/lib64
```

To run
```bash
./build.sh && ./musializer <path-to-audio>
```

<img src="https://github.com/petrostrak/musializer/blob/main/musializer.png" width="250" height="250" />
