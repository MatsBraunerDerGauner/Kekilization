#include"Include/object.h"
#include"Include/map.h"
#include"Include/vector.h"

void object_Init() {
    humenSprite = sfSprite_create();
    sfSprite_setTexture(humenSprite, sfTexture_createFromFile("Images/player_II.png", 0), 0);
    sfSprite_setScale(humenSprite, vector2f(humenScale, humenScale));
    sfSprite_setOrigin(humenSprite, vector2f(-25, 45));
}

object_t *object_constructor(object_t *object, sfSprite *objectSprite, objectType type) {
    object->objectSprite = objectSprite;
    object->setPosition = setPosition;
    object->type = type;


    return object;
}

void setPosition(object_t *object, int x, int y) {
    object->position.x = x;
    object->position.y = y;
}

void updatePosition(object_t *object) {
    sfSprite_setPosition(object->objectSprite, vector2f(nullPoint.x + scale * (object->position.x * tileWidth + object->position.y % 2 * h_tileWidth), nullPoint.y + scale * (object->position.y * h_tileHeight)));
}
