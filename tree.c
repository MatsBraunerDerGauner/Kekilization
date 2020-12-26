#include"Include/tree.h"
#include<stdlib.h>


tree_t *tree_create(int posX, int posY) {
    // init a new Tree 
    tree_t *tree = calloc(1, sizeof(struct TREE_STRUCT));
    object_t *object = object_constructor((object_t*)tree, treeSprite, treeType);

    object->selected = false; 

    tree->setPosition = object->setPosition;

    tree->setPosition((object_t*)tree, posX, posY);

    objectList[objectListCount] = (object_t*)tree;
    objectListCount++;

    return tree;
}




