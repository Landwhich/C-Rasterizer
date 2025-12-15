# 3D Rasterizer written in C
glorified cube spinner

## Dependecies:
- [raylib](https://github.com/raysan5/raylib) (included in libs/folder)
- using `make` to build
- using `ffmpeg -i image(%03d).bmp -r 30 output.mp4` to stitch images to animations 

## Installation
- `git clone` in your root folder
- run `make` to build and run with `./rasterizer`

## features
- Using .bmp to render images may move to .ppm and plan to move to live rendering in raylib soon
- .obj parsing and loading. able to parse normals and textures, but no lighting or texture mapping implemented as of yet
- Rotation of 3D objects

https://github.com/user-attachments/assets/de00242a-de1c-457d-a0d0-3d6289f5c2ae

