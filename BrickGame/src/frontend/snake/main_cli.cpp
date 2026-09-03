/**
 * @file main_cli.cpp
 * @author Collinna
 * @date Февраль 2026
 * @brief Исполняемый файл консольной версии игры Змейка
 */

#include "../../brick_game/snake/logic.h"
#include "../../gui/cli/cli.h"

/*! \fn void s21_snakeLoop()
 * \brief Игровой цикл консольной версии игры Змейка
 */
void s21_snakeLoop() {
  WINDOW *main_win = newwin(LINES - 5, COLS - 35, 0, 0);

  s21_Intro(startSnakeIntro, main_win);

  GameInfo_t gi;

  do {
    int ch = getch();
    bool hold = (ch != KEY_ESC);

    UserAction_t userAction = s21_getAction(ch);

    userInput(userAction, hold);
    gi = updateCurrentState();
    s21_draw(main_win, gi);

  } while (gi.speed != 0);

  napms(2000);

  if (gi.score == WINSCORE)
    s21_Intro(winIntro, main_win);
  else
    s21_Intro(finishIntro, main_win);

  delwin(main_win);
}

/*! \fn int main()
 * \brief Главная функция программы
 * \return Код завершения работы программы
 */
int main() {
  s21_winInit(50);
  s21_startColor();
  s21_snakeLoop();
  endwin();
  return 0;
}
