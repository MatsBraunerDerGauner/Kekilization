#ifndef CONFIG_H
#define CONFIG_H

// Bool type
typedef enum { false, true } bool;

// Window size
#define WINDOW_WIDTH 2000
#define WINDOW_HEIGHT 1000

typedef struct VECTOR2I_STRUCT {
    int x, y;
} vec2i_t;

#endif
