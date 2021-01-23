// GB SCREEN : (0,0) to (19,17)

#include <stdio.h>
#include <stdlib.h> // rand

#include <gb/gb.h>
#include <gb/console.h>

#include "tools.h"
#include "gameboard.h"
#include "render.h"

// Prints the key pressed
const char* print_key(UINT8 keys) {
    if (keys & J_UP) return "UP";
    if (keys & J_DOWN) return "DOWN";
    if (keys & J_LEFT) return "LEFT";
    if (keys & J_RIGHT) return "RIGHT";
    if (keys & J_SELECT) return "SELECT";
    if (keys & J_START) return "START";
    if (keys & J_A) return "A";
    if (keys & J_B) return "B";
    return "NONE";
}

UINT8 blocking_input(UINT8 mask) {
    UINT8 key = waitpad(mask);
    waitpadup();
    return key;
}

void human_turn(GameBoard *game_board) {
    UINT8 key;
    UINT8 cursor_moved = 0;

    key = blocking_input(J_UP | J_DOWN | J_LEFT | J_RIGHT | J_A);

    if (key & J_UP && game_board->cursor_y > 0) {
        cursor_moved = 1;
        game_board->cursor_y--;
    }

    else if (key & J_DOWN && game_board->cursor_y < 2) {
        cursor_moved = 1;
        game_board->cursor_y++;
    }

    else if (key & J_LEFT && game_board->cursor_x > 0) {
        cursor_moved = 1;
        game_board->cursor_x--;
    }

    else if (key & J_RIGHT && game_board->cursor_x < 2) {
        cursor_moved = 1;
        game_board->cursor_x++;
    }

    else if (key & J_A && game_board->game_board_state[game_board->cursor_idx] == EMPTY_CELL) {
        game_board->game_board_state[game_board->cursor_idx] = O_CELL;
        draw_marks(game_board);
    }

    if (cursor_moved) {
        clear_cursor(game_board->cursor_idx);
        game_board->cursor_idx = xy_to_idx(game_board->cursor_x, game_board->cursor_y);
        draw_cursor(game_board->cursor_idx);
    }
}

void computer_turn(GameBoard *game_board) {
    // 9 = number of cells
    
    UINT8 rand_idx = (UINT8)(rand() / (double)RAND_MAX * (9 - 1));

    while(game_board->game_board_state[rand_idx] != EMPTY_CELL)
        rand_idx = (UINT8)(rand() / (double)RAND_MAX * (9 - 1));

    game_board->game_board_state[rand_idx] = X_CELL;
    draw_marks(game_board);
}

void play(GameBoard *game_board) {
    UINT8 human_score = 0;
    UINT8 cmp_score = 0;

    game_init(game_board);
    render_all(game_board, human_score, cmp_score);

    while(1) {
        human_turn(game_board);
        computer_turn(game_board);
        //render_all(game_board, human_score, cmp_score);
    }
}

int main(void) {
    srand(42); // 42 for debug purpose

    UINT8 keys = 0;
    UINT8 prev_keys = 0;

    GameBoard game_board;

    printf("Hello world!");
    blocking_input(J_START);

    draw_home_screen();
    blocking_input(J_START);

    play(&game_board);

    clear_screen();
    gotoxy(0, 0);
    printf("Good! See you around.\n");
    return 0;
}

    /*while (1) {
        keys = joypad();

        if (keys == prev_keys) {
            continue;
        }

        if (keys > 0) {
            printf(print_key(keys));
            printf("\n");
            waitpadup();
        }

        prev_keys = keys;
    }*/