#include"Include/button.h"
#include"stdlib.h"
#include"Include/vector.h"

button_t *button_create(char *str) {
    button_t *btn = calloc(1, sizeof(struct BUTTON_STRUCT)); 

    sfSprite *back = sfSprite_create();
    sfSprite_setTexture(back, sfTexture_createFromFile("Images/button.png", 0), 0);

    sfText *tempText = sfText_create();
    sfText_setFont(tempText, sfFont_createFromFile("Fonts/arial.ttf"));
    sfText_setColor(tempText, sfBlack);
    sfText_setCharacterSize(tempText, 20);
    sfText_setString(tempText, str);
    sfText_setPosition(tempText, vector2f(0, 0)); 

    btn->text = tempText;
    btn->background = back;

    // Methodes
    btn->click = click;

    return btn;
}

void click() {

}

void drawButton(sfRenderWindow *window, button_t *button) {
    sfRenderWindow_drawSprite(window, button->background, NULL);
    sfRenderWindow_drawText(window, button->text, NULL);
}
