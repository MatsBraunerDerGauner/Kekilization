#include"Include/human.h"
#include<stdlib.h>


humen_t *humen_create(char *name, int posX, int posY) {
    humen_t *humen = calloc(1, sizeof(struct HUMEN_STRUCT));
    object_t *object = object_constructor((object_t*)humen, humenSprite, humenType);

    object->selected = false; 

    humen->setPosition = object->setPosition;

    humen->name = name;
    humen->setPosition((object_t*)humen, posX, posY);

    objectList[objectListCount] = (object_t*)humen;
    objectListCount++;

    return humen;
}



