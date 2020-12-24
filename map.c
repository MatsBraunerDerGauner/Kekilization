#include"Include/map.h"
#include"Include/config.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Perlin Noise
void perlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput) {
    // Used 1D Perlin Noise
    for (int x = 0; x < nWidth; x++) {
        for (int y = 0; y < nHeight; y++) {
            float fNoise = 0.0f;
            float fScaleAcc = 0.0f;
            float fScale = 1.0f;

            for (int o = 0; o < nOctaves; o++) {
                int nPitch = nWidth >> o;
                int nSampleX1 = (x / nPitch) * nPitch;
                int nSampleY1 = (y / nPitch) * nPitch;
                
                int nSampleX2 = (nSampleX1 + nPitch) % nWidth;					
                int nSampleY2 = (nSampleY1 + nPitch) % nWidth;

                float fBlendX = (float)(x - nSampleX1) / (float)nPitch;
                float fBlendY = (float)(y - nSampleY1) / (float)nPitch;

                float fSampleT = (1.0f - fBlendX) * fSeed[nSampleY1 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY1 * nWidth + nSampleX2];
                float fSampleB = (1.0f - fBlendX) * fSeed[nSampleY2 * nWidth + nSampleX1] + fBlendX * fSeed[nSampleY2 * nWidth + nSampleX2];

                fScaleAcc += fScale;
                fNoise += (fBlendY * (fSampleB - fSampleT) + fSampleT) * fScale;
                fScale = fScale / fBias;
            }
        // Scale to seed range
        fOutput[y * nWidth + x] = fNoise / fScaleAcc;
        }
    }
}

void addPointToList(int x, int y, surfaceTyp type) {
    list[listCount].x = x;
    list[listCount].y = y;
    list[listCount].type = type;
    listCount++;
}

void map_Init() {

    // tiles
    tileSprite = sfSprite_create();
    sfSprite_setTexture(tileSprite, sfTexture_createFromFile("Images/tiles_II.png", 0), 0);

    scale = 1.0f;

    h_tileWidth = tileWidth / 2;
    h_tileHeight = tileHeight / 2;

    listCount = 0;
    nullPoint.x = WINDOW_WIDTH / 2;
    nullPoint.y = WINDOW_HEIGHT / 2;

    fNoiseSeed2D = NULL;
    fPerlinNoise2D = NULL;

    fNoiseSeed2D = calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(float));
    fPerlinNoise2D = calloc(MAP_WIDTH * MAP_HEIGHT, sizeof(float));
    // Random Map with simple noise
    srand(time(NULL)); 


    for (int i = 0; i < MAP_WIDTH * MAP_HEIGHT; i++) {
        fNoiseSeed2D[i] = (float)rand() / (float)RAND_MAX;
    }

    perlinNoise2D(MAP_WIDTH, MAP_HEIGHT, fNoiseSeed2D, 5, 0.3f, fPerlinNoise2D);

    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            float perlinNoise = fPerlinNoise2D[y * MAP_WIDTH + x];

            surfaceTyp type; 

            if (perlinNoise >= 0.55f)
                type = _grass;
            else
                type = _water;

            addPointToList(x, y, type);
        }
    }
}
