#ifndef BUTTON_H
#define BUTTON_H

#include<SFML/Graphics.h>
#include"object.h"

typedef struct BUTTON_STRUCT {
    sfText *text;
    sfSprite *background;
    char *str;
    vec2i_t position;
    vec2i_t width;
    vec2i_t height;
    void (*click)();
} button_t;

button_t *button_create(char *str);

void click();

void drawButton(sfRenderWindow *window, button_t *button);

#endif
