#include<SFML/Graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Include/vector.h"
#include"Include/config.h"
#include"Include/map.h"
#include"Include/object.h"
#include"Include/humen.h"
#include"Include/tree.h"
#include"Include/button.h"

#define p_float(x) printf("%f\n", x);
#define p_int(x) printf("%d\n", x);

/*-------------------------------------------------------------------------------------*\
|----------<- ToDo ->-------------------------------------------------------------------|
|   3 Player bewegen können                                                             |
|                                                                                       |
|                                                                                       |
\*-------------------------------------------------------------------------------------*/





sfRenderWindow *window;

// mouse
bool inHand = false;
struct point_t mousePosBackup = { 0, 0 };
struct point_t selectedTile = { 0, 0 };
bool action = false;

int main(void) {


    // Textanzeige
    sfText *cellXText = sfText_create();
    sfText_setColor(cellXText, sfBlack);
    sfText_setFont(cellXText, sfFont_createFromFile("Fonts/arial.ttf"  ));
    sfText_setCharacterSize(cellXText, 20);

    sfText *cellYText = sfText_create();
    sfText_setColor(cellYText, sfBlack);
    sfText_setFont(cellYText, sfFont_createFromFile("Fonts/arial.ttf"  ));
    sfText_setCharacterSize(cellYText, 20);
    sfVector2f poss = { 0, 50 };
    sfText_setPosition(cellYText, poss);






    // window
    sfVideoMode mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
    window = sfRenderWindow_create(mode, "Kekcivilisation", sfDefaultStyle, NULL);
    


    // selectet
    selected = sfSprite_create();
    sfSprite_setTexture(selected, sfTexture_createFromFile("Images/selected.png", 0), 0);

    // Menu
    button_t *btn = button_create("Start_Game");



    bool menu_IsOpen = true;
    while (sfRenderWindow_isOpen(window) && menu_IsOpen) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyA) {
                    menu_IsOpen = false;
                }
            }
        }
        sfRenderWindow_clear(window, sfWhite);
        drawButton(window, btn);
        sfRenderWindow_display(window);
    }

    map_Init();
    object_Init();

    humen_create("Matthias", 0, 0);
    tree_create(5, 10);


    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            switch (event.type) {
                case sfEvtClosed:
                    sfRenderWindow_close(window);
                    break;
                case sfEvtMouseButtonPressed:
                    inHand = true;
                    if (event.mouseButton.button == sfMouseLeft) {
                        for (int i = 0; i < objectListCount; i++) {
                            if (action == true) {
                                if (!(objectList[i]->selected == true))
                                    continue;
                                switch (objectList[i]->type) {
                                    case humenType:
                                        if (getSurfaceType(selectedTile.x, selectedTile.y) == _water)
                                            break;
                                        objectList[i]->setPosition(objectList[i], selectedTile.x, selectedTile.y);
                                        break;
                                    case treeType:
                                        // tree
                                        break;
                                    case defType:
                                        break;
                                }

                                action = false;
                                objectList[i]->selected = false;
                                break;
                            }
                            if (objectList[i]->position.x == selectedTile.x && objectList[i]->position.y == selectedTile.y) {
                                objectList[i]->selected = true;
                                action = true;
                                break;
                            }
                        }
                    }
                    break;
                case sfEvtMouseButtonReleased:
                    inHand = false;
                    break;
            }
            if (event.type == sfEvtMouseMoved) {
                // move the world
                int posX = event.mouseMove.x;
                int posY = event.mouseMove.y;
                if (inHand == true) {
                    int diffX = posX-mousePosBackup.x;
                    int diffY = posY-mousePosBackup.y;
                    nullPoint.x = nullPoint.x + diffX;
                    nullPoint.y = nullPoint.y + diffY;
                }
                mousePosBackup.x = posX;
                mousePosBackup.y = posY;
                        


                // select
                int offsetX = 0, offsetY = 0;

                int temp_tileWidth = tileWidth * scale / 10;
                int temp_h_tileWidth = h_tileWidth * scale / 10;
                int temp_h_tileHeight = h_tileHeight * scale / 10;
                

                selectedTile.x = (posX - nullPoint.x) / temp_tileWidth;
                selectedTile.y = (posY - nullPoint.y) / temp_h_tileHeight;

                offsetX = (posX - nullPoint.x) % temp_tileWidth;
                offsetY = (posY - nullPoint.y) % temp_h_tileHeight;

                switch (selectedTile.y % 2) {
                    case 0:
                        if (offsetX <= (offsetY - temp_h_tileHeight) / -0.5) {
                            selectedTile.x--;
                            selectedTile.y--;
                        } 
                        if (offsetX - temp_h_tileWidth >= offsetY / 0.5) {
                            selectedTile.y--;
                        }
                        break;
                    case 1:
                        switch (offsetX / temp_h_tileWidth) {
                            int eins, zwei;
                            case 0:
                                if (offsetX <= offsetY / 0.5)
                                    selectedTile.x--;
                                if (offsetX >= offsetY / 0.5)
                                    selectedTile.y--;
                                break;
                            case 1:
                                eins = offsetX - temp_h_tileWidth;
                                zwei = (offsetY - temp_h_tileHeight) / -0.5;

                                if (offsetX - temp_h_tileWidth <= (offsetY - temp_h_tileHeight) / -0.5) {
                                    selectedTile.y--;
                                }
                                if (offsetX - temp_h_tileWidth >= (offsetY - temp_h_tileHeight) / -0.5) {
                                }
                                break;
                        } 
                        break;
                }


                char cellX_Text[25];
                char cellY_Text[25];

                sprintf(cellX_Text, "CellX: %d OffsetX: %d", selectedTile.x, offsetX); 
                sprintf(cellY_Text, "CellY: %d OffsetY: %d", selectedTile.y, offsetY); 

                sfText_setString(cellXText, cellX_Text);
                sfText_setString(cellYText, cellY_Text);


            }

            if (event.type == sfEvtMouseWheelMoved) {

                int mouse_x = event.mouseWheel.x;
                int mouse_y = event.mouseWheel.y;

                int delta = event.mouseWheel.delta;
                if (scale == 1 && delta == -1) {
                    continue;
                }
                scale += delta;


                switch (delta) {
                    case 1:
                        nullPoint.x -= ((mouse_x - nullPoint.x) * scale) / (scale - 1) - (mouse_x - nullPoint.x);
                        nullPoint.y -= ((mouse_y - nullPoint.y) * scale) / (scale - 1) - (mouse_y - nullPoint.y);
                        break;
                    case -1:
                        nullPoint.x -= ((mouse_x - nullPoint.x) * scale) / (scale + 1) - (mouse_x - nullPoint.x);
                        nullPoint.y -= ((mouse_y - nullPoint.y) * scale) / (scale + 1) - (mouse_y - nullPoint.y);
                        break;
                }
            }
        }

        sfRenderWindow_clear(window, sfWhite);
        // draw Tiles
        for (int i = 0; i < listCount; i++) {
            sfVector2f vec = { nullPoint.x + scale / 10 * (list[i].x * tileWidth + list[i].y % 2 * h_tileWidth), nullPoint.y + scale / 10 * (list[i].y * h_tileHeight) };
            sfIntRect rect = { list[i].type * tileWidth, 0, tileWidth, tileHeight };
            sfSprite_setTextureRect(tileSprite, rect);

            sfVector2f scaleS = { scale / 10, scale / 10 };
            sfSprite_setScale(tileSprite, scaleS);

            sfSprite_setPosition(tileSprite, vec);
            sfRenderWindow_drawSprite(window, tileSprite, NULL);
        }

        // selected
        sfVector2f vecSel = { nullPoint.x + scale / 10 * (selectedTile.x * tileWidth + selectedTile.y % 2 * h_tileWidth), nullPoint.y + scale / 10 * (selectedTile.y * h_tileHeight) };
        sfVector2f scaleSelected = { scale / 10, scale / 10 };
        sfIntRect rectS = { 0 * tileWidth, 0, tileWidth, tileHeight };
        sfSprite_setScale(selected, scaleSelected);
        sfSprite_setPosition(selected, vecSel);
        sfSprite_setTextureRect(selected, rectS);
        sfRenderWindow_drawSprite(window, selected, NULL);

        // selected test yellow
        for (int i = 0; i < objectListCount; i++) {
            if (objectList[i]->selected == true) {
                sfVector2f vec = { nullPoint.x + scale / 10 * (objectList[i]->position.x * tileWidth + objectList[i]->position.y % 2 * h_tileWidth), nullPoint.y + scale / 10 * (objectList[i]->position.y * h_tileHeight) };
                sfVector2f scaleSelected = { scale / 10, scale / 10 };
                sfIntRect rectS = { 1 * tileWidth, 0, tileWidth, tileHeight };
                sfSprite_setScale(selected, scaleSelected);
                sfSprite_setPosition(selected, vec);
                sfSprite_setTextureRect(selected, rectS);
                sfRenderWindow_drawSprite(window, selected, NULL);
            }
        }
                

       
        // select Rect Text
        sfRenderWindow_drawText(window, cellXText, NULL);
        sfRenderWindow_drawText(window, cellYText, NULL);

        // Humen§
        for (int i = 0; i < objectListCount; i++) {
            sfSprite_setScale(objectList[i]->objectSprite, vector2f(scale * humenScale, scale * humenScale));
            updatePosition(objectList[i]);
            sfRenderWindow_drawSprite(window, objectList[i]->objectSprite, NULL);
        }


        sfRenderWindow_display(window);
    }
}

