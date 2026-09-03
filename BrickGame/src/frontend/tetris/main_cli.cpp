/**
 * @file main_cli.cpp
 * @author Collinna
 * @date Февраль 2026
 * @brief Исполняемый файл консольной версии игры Тетрис
 */

#include "../../brick_game/tetris/logic.h"
#include "../../gui/cli/cli.h"

/*! \fn void s21_tetrisLoop()
 * \brief Игровой цикл консольной версии игры Тетрис
 */
void s21_tetrisLoop() {
  WINDOW *main_win = newwin(LINES - 5, COLS - 35, 0, 0);

  s21_Intro(startTetrisIntro, main_win);

  GameInfo_t gi;

  do {
    int ch = getch();
    bool hold = (ch != KEY_ESC);
    UserAction_t userAction = s21_getAction(ch);

    userInput(userAction, hold);
    gi = updateCurrentState();
    s21_draw(main_win, gi);

  } while (gi.speed != 0);

  s21_Intro(finishIntro, main_win);
  s21_freeGameMemory();
  delwin(main_win);
}

/*! Главная функция десктопной версии игры Тетрис
 * \return Код завершения работы программы
 */
int main() {
  s21_winInit(50);
  s21_startColor();
  s21_tetrisLoop();
  endwin();
  return 0;
}
