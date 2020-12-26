#ifndef TREE_H
#define TREE_H
#include"object.h"

#include<SFML/Graphics.h>

typedef struct TREE_STRUCT {
    object_t base;
    void (*setPosition)(struct OBJECT_STRUCT *object, int x, int y);
} tree_t;

tree_t *tree_create(int posX, int posY);



#endif 
