#include<SFML/Graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*-------------------------------------------------------------------------------------*\
|----------<- ToDo ->-------------------------------------------------------------------|
|   1 random map with height meter over meer                                            |
|   2 select tile                                                                       |
|   3 larger zoom in and zoom out                                                       |
|   4 performenc                                                                        |
|                                                                                       |
\*-------------------------------------------------------------------------------------*/

typedef enum { false, true } bool;

// Typ's of Grafics (Suface)
typedef enum { _grass, _water } surfaceTyp;

// Windows Size
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 700

sfRenderWindow *window;
sfSprite *grassSprite;
sfSprite *grassSprite2;

// Tile Size
#define tileWidth 40
#define tileHeight 20

// Tile scale
int scale = 1;

// Tile half of Size
int h_tileWidth = tileWidth / 2;
int h_tileHeight = tileHeight / 2;


struct point_t {
    int x, y;
    surfaceTyp type;
} list[10000];

int listCount = 0;


struct point_t nullPoint = { WINDOW_WIDTH/2, WINDOW_HEIGHT/2 };




void addPointToList(int x, int y, surfaceTyp type) {
    list[listCount].x = x;
    list[listCount].y = y;
    list[listCount].type = type;
    listCount++;
}

struct point_t *getListItem(int x, int y) {
    for (int i = 0; i < listCount; i++) {
        if (list[i].x == x && list[i].y == y)
            return &list[i];
    }
    return NULL;
}


    // random islands
void createIsland(int size, int islandPoint) {

    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {

            int chance;
            int probability=rand()%size*size;
            if(probability<=size*size) {
                chance=0;
            }else{
                chance=1;
            }

            list[islandPoint+i].type = chance;

        }
        islandPoint += 30;
    }

}

bool prozent(int prozent) {
    int random = rand() % 101;
    
    if (random <= prozent)
        return true;

    return false;
}

int randomHeightBetween(int min, int max) {
   int zahl;

   zahl = rand() % ((max - min) + 1);

   zahl += min;

   return zahl;
}

bool inHand = false;
struct point_t mousePosBackup = { 0, 0 };

int main(void) {

    srand(time(NULL));


    // window
    sfVideoMode mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
    window = sfRenderWindow_create(mode, "Kekcivilisation", sfDefaultStyle, NULL);

    // gras
    grassSprite = sfSprite_create();
    sfSprite_setTexture(grassSprite, sfTexture_createFromFile("Images/tiles.png", 0), 0);

    // Random Map
    // addPointToList(int x, int y, int choose) => x = j, y = i
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {

            addPointToList(j, i, 1);
        }
    }

    for (int i = 0; i < 20; i++) {

        int size;

        int islandPoint = rand()%900;
        islandPoint -= 1;


        int islandSize = rand()%3;

        if (islandSize < 2) {
            size = 3;
            createIsland(size, islandPoint);
        }
        if (islandSize == 2) {
            size = 5;
            createIsland(size, islandPoint);
        }
        if (islandSize > 2) {
            size = 7;
            createIsland(size, islandPoint);
        }

    }


    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            switch (event.type) {
                case sfEvtClosed:
                    sfRenderWindow_close(window);
                    break;
                case sfEvtMouseButtonPressed:
                    inHand = true;
                    break;
                case sfEvtMouseButtonReleased:
                    inHand = false;
            }
            if (event.type == sfEvtMouseMoved) {
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
        sfRenderWindow_clear(window, sfTransparent);
        for (int i=0; i<listCount; i++) {
            sfVector2f vec = { (nullPoint.x-scale*h_tileWidth) + (list[i].x-list[i].y)*scale*h_tileWidth, nullPoint.y + (list[i].x+list[i].y)*scale*h_tileHeight };

            sfIntRect rect = { list[i].type * tileWidth, 0, tileWidth, tileHeight };
            sfSprite_setTextureRect(grassSprite, rect);

            sfVector2f scaleS = { scale, scale };
            sfSprite_setScale(grassSprite, scaleS);

            sfSprite_setPosition(grassSprite, vec);
            sfRenderWindow_drawSprite(window, grassSprite, NULL);
        }





        sfRenderWindow_display(window);

    }
}

