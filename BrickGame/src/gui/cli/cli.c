/**
 * @file cli.c
 * @author Collinna
 * @date Август 2025
 * @brief Реализация консольного интерфейса игр BrickGame
 */

#include "cli.h"

#include <ncurses.h>
#include <stdlib.h>

void s21_winInit(int time) {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(time);
}

void s21_startColor() {
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_RED);
  init_pair(2, COLOR_BLACK, 202);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);
  init_pair(4, COLOR_BLACK, 210);
  init_pair(5, COLOR_BLACK, COLOR_GREEN);
  init_pair(6, COLOR_BLACK, COLOR_BLUE);
  init_pair(7, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(8, COLOR_BLACK, COLOR_WHITE);
  init_pair(9, COLOR_BLACK, 250);
}

void s21_drawField(WINDOW *win, int **field) {
  if (field == NULL) return;

  for (int i = 0; i < FIELD_HEIGHT; i++) {
    mvwaddch(win, i + 1, 1, ' ' | COLOR_PAIR(8));
    mvwaddch(win, i + 1, 2, ' ' | COLOR_PAIR(8));
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int color = field[i][j];
      int c1 = ' ';
      int c2 = ' ';

      if (color > 0) {
        c1 = '[';
        c2 = ']';
      }
      mvwaddch(win, i + 1, 3 + (j * ZOOM_X), c1 | COLOR_PAIR(color));
      mvwaddch(win, i + 1, 3 + (j * ZOOM_X + 1), c2 | COLOR_PAIR(color));
    }
    mvwaddch(win, i + 1, 23, ' ' | COLOR_PAIR(8));
    mvwaddch(win, i + 1, 24, ' ' | COLOR_PAIR(8));
  }

  for (int j = 0; j < (FIELD_WIDTH + 2) * ZOOM_X; j++)
    mvwaddch(win, 21, j + 1, ' ' | COLOR_PAIR(8));
}

int s21_fieldEmpty(int **field) {
  if (field == NULL) return 1;

  int cnt = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int color = field[i][j];
      if (color > 0) cnt++;
    }

  return cnt == 0;
}

void s21_drawStatistics(WINDOW *win, int level, int score, int high_score,
                        int speed) {
  mvwprintw(win, 10, 30, "Level     : %i", level);
  mvwprintw(win, 11, 30, "Score     : %i", score);
  mvwprintw(win, 12, 30, "High score: %i", high_score);
  mvwprintw(win, 13, 30, "Speed     : %i", speed);
}

void s21_drawNextTetramino(WINDOW *win, int **next) {
  if (next == NULL) return;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      int c1 = ' ';
      int c2 = ' ';

      int color = next[i][j];

      if (color > 0) {
        c1 = '[';
        c2 = ']';
      }
      mvwaddch(win, OFFSET_PREVIEW_Y + i, OFFSET_PREVIEW_X + (j * ZOOM_X),
               c1 | COLOR_PAIR(color));
      mvwaddch(win, OFFSET_PREVIEW_Y + i, OFFSET_PREVIEW_X + (j * ZOOM_X + 1),
               c2 | COLOR_PAIR(color));
    }
}

void s21_draw(WINDOW *win, GameInfo_t gi) {
  wclear(win);

  s21_drawField(win, gi.field);

  if (s21_fieldEmpty(gi.field)) {
    mvwprintw(win, 15, 30, " -= PRESS S TO START =- ");
  } else {
    s21_drawStatistics(win, gi.level, gi.score, gi.high_score, gi.speed);
    s21_drawNextTetramino(win, gi.next);
  }

  if (gi.pause == 1) mvwprintw(win, 15, 30, " -= PAUSED =- ");

  wrefresh(win);
}

void s21_drawIntro(const int intro[INTRO_ROWS][INTRO_COLS], WINDOW *win,
                   int y) {
  for (int i = 0; i < INTRO_ROWS; i++)
    for (int j = 0; j < INTRO_COLS; j++) {
      int color = intro[i][j];
      char c1 = ' ';
      char c2 = ' ';
      if (color > 0) {
        c1 = '[';
        c2 = ']';
      }

      mvwaddch(win, i + y, 1 + (j * 2), c1 | COLOR_PAIR(color));
      mvwaddch(win, i + y, 1 + (j * 2 + 1), c2 | COLOR_PAIR(color));
    }
}

void s21_Intro(const int intro[INTRO_ROWS][INTRO_COLS], WINDOW *win) {
  int y = -5;

  while (y < 10) {
    refresh();
    wclear(win);
    s21_drawIntro(intro, win, y);
    wrefresh(win);
    napms(100);
    y++;
  }

  napms(3000);
}
