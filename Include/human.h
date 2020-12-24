#ifndef HUMEN_H
#define HUMEN_H
#include"object.h"

#include<SFML/Graphics.h>

typedef enum { guard } humenTyp;

typedef struct HUMEN_STRUCT {
    object_t base;
    char *name;
    void (*setPosition)(struct OBJECT_STRUCT *object, int x, int y);
} humen_t;

humen_t *humen_create(char *name, int posX, int posY);



#endif 
