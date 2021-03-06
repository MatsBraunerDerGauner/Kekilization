#ifndef OBJECT_H
#define OBJECT_H

#include"config.h"
#include<SFML/Graphics.h>

// Sprites
// Sprite for Humen Object
sfSprite *humenSprite;
#define humenScale 0.5 

// Sprite for Tree Object
sfSprite *treeSprite;
#define treeScale 1

// Types of Objects
typedef enum { defType, humenType, treeType } objectType;

typedef struct {
    int x, y;
} position_t;

typedef struct OBJECT_STRUCT {
    objectType type;
    position_t position;
    bool selected;

    sfSprite *objectSprite;
    void (*setPosition)(struct OBJECT_STRUCT *object, int x, int y);
} object_t;

object_t *objectList[10000];

int objectListCount;

void object_Init();

object_t *object_constructor(object_t *object, sfSprite *objectSprite, objectType type);

void setPosition(object_t *object, int x, int y); 

void updatePosition(object_t *object);

#endif
