#ifndef __RENDER__
#define __RENDER__

const UINT8 SCREEN_W = 20;
const UINT8 SCREEN_H = 18;

// Clears the screen
void clear_screen() {
    for (UINT8 i = 0; i < SCREEN_H; i++) {
        for (UINT8 j = 0; j < SCREEN_W; j++) {
            gotoxy(j, i);
            setchar(' ');
        }
    }
}

// Go to next line with an offset of x
void goto_nl(UINT8 x) {
    gotoxy(x, posy() + 1);
}

void setchar_at(UINT8 chr, UINT8 x, UINT8 y) {
    gotoxy(x, y);
    setchar(chr);
}

void draw_home_screen() {
    clear_screen();
    gotoxy(4, 2);
    printf("TIC TAC TOE");
    gotoxy(4, 17);
    printf("PRESS START");
}

void draw_game_board() {
    clear_screen();

    gotoxy(1, 1);
    printf("   |   |");
    goto_nl(1);
    printf("   |   |");
    goto_nl(1);
    printf("   |   |");
    goto_nl(1);
    printf("---+---+---");
    goto_nl(1);
    printf("   |   |");
    goto_nl(1);
    printf("   |   |");
    goto_nl(1);
    printf("   |   |");
    goto_nl(1);
    printf("---+---+---");
    goto_nl(1);
    printf("   |   |");
    goto_nl(1);
    printf("   |   |");
    goto_nl(1);
    printf("   |   |");
    goto_nl(1);
}

void draw_marks(GameBoard *game_board) {
    UINT8 x, y;

    for (UINT8 i = 0; i < 9; i++) {
        x = x_coord_cell(i);
        y = y_coord_cell(i);
        gotoxy(x, y);
        setchar(game_board->game_board_state[i]);
    }
}

void draw_game_score(UINT8 human, UINT8 cmp) {
    gotoxy(13, 1);
    printf("HMN: %d", human);
    gotoxy(13, 3);
    printf("CMP: %d", cmp);
}

void draw_help() {
    gotoxy(1, SCREEN_H - 2);
    printf("You: O - Cmp: X");
}

void draw_cursor(UINT8 idx) {
    UINT8 x = x_coord_cell(idx);
    UINT8 y = y_coord_cell(idx);

    setchar_at('/', x - 1, y - 1);
    setchar_at('/', x    , y - 1);
    setchar_at('/', x + 1, y - 1);

    setchar_at('/', x - 1, y);
    setchar_at('/', x + 1, y);

    setchar_at('/', x - 1, y + 1);
    setchar_at('/', x,     y + 1);
    setchar_at('/', x + 1, y + 1);
}

void clear_cursor(UINT8 idx) {
    UINT8 x = x_coord_cell(idx);
    UINT8 y = y_coord_cell(idx);

    setchar_at(' ', x - 1, y - 1);
    setchar_at(' ', x    , y - 1);
    setchar_at(' ', x + 1, y - 1);

    setchar_at(' ', x - 1, y);
    setchar_at(' ', x + 1, y);

    setchar_at(' ', x - 1, y + 1);
    setchar_at(' ', x,     y + 1);
    setchar_at(' ', x + 1, y + 1);
}

void render_all(GameBoard *game_board, UINT8 human_score, UINT8 cmp_score) {
    draw_game_board();
    draw_marks(game_board);
    draw_cursor(game_board->cursor_idx);
    draw_game_score(human_score, cmp_score);
    draw_help();
}

#endif