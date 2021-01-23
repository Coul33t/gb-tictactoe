#ifndef __TOOLS__
#define __TOOLS__

typedef struct Coordinates Coordinates;
struct Coordinates {
    UINT8 x;
    UINT8 y;
};

// Transforms 2d coordinates into 1d coordinates
UINT8 xy_to_idx(UINT8 x, UINT8 y) {
    return y * 3 + x;
}

UINT8 x_coord_cell(UINT8 idx) {
    if (idx % 3 == 0)
        return 2;
    else if (idx % 3 == 1)
        return 6;
    else
        return 10;
}

UINT8 y_coord_cell(UINT8 idx) {
    if (idx < 3)
        return 2;
    else if (idx >= 3 && idx < 6)
        return 6;
    else
        return 10;
}

#endif