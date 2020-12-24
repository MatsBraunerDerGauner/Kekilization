#ifndef MAP_H
#define MAP_H

#include<SFML/Graphics.h>

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

// Sprite for Tile
sfSprite *tileSprite;
sfSprite *selected;

// Typ's of Grafics (Suface)
typedef enum { _grass, _water } surfaceTyp;

// Tile Size
#define tileWidth 400
#define tileHeight 200

// Tile scale
float scale;

// Tile half of Size
int h_tileWidth;
int h_tileHeight;

// Perlin Noise
void perlinNoise2D(int width, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput);

// PerlinNoise
float *fNoiseSeed2D;
float *fPerlinNoise2D;

struct point_t {
    int x, y;
    surfaceTyp type;
} list[MAP_WIDTH * MAP_HEIGHT];

int listCount;

struct point_t nullPoint;

void addPointToList(int x, int y, surfaceTyp type);

void map_Init();


#endif
