#ifndef __GAMEBOARD__
#define __GAMEBOARD__

#define EMPTY_CELL ' '
#define X_CELL 'X'
#define O_CELL 'O'

enum GameState { PLAYING, WON, LOST, DRAW };

typedef struct GameBoard GameBoard;
struct GameBoard {
    UINT8 game_board_state[9];
    UINT8 cursor_x, cursor_y, cursor_idx;
    enum GameState game_state;
};

void game_init(GameBoard *game_board) {
    game_board->cursor_x = 1;
    game_board->cursor_y = 1;

    game_board->cursor_idx = xy_to_idx(1, 1);

    for (UINT8 i = 0; i < 9; i++)
        game_board->game_board_state[i] = EMPTY_CELL;

    game_board->game_state = PLAYING;
}

void compute_game_state(GameBoard * game_board) {
    
}

#endif