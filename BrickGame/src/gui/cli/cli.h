/**
 * @file cli.h
 * @author Collinna
 * @date Август 2025
 * @brief Описание макросов, констант и функций, используемых при реализации
 консольного интерфейса с использованием ncurses.
 */
#ifndef DRAW_H
#define DRAW_H

#include <ncurses.h>

#include "../../brick_game/common.h"

#define ZOOM_X 2
///< Коэффициент масштаба по оси X
#define OFFSET_PREVIEW_X 32
///< Координата X для отображения следующего тетромино
#define OFFSET_PREVIEW_Y 5
///< Координата Y для отображения следующего тетромино

/*! \fn s21_winInit(int time)
 * \brief Инициализация терминального интерфейса
 * \param time Задержка ожидания нажатия клавиши
 */
void s21_winInit(int time);

/*! \fn void s21_startColor()
 * \brief Инициализация цвета и цветовых пар
 */
void s21_startColor();

/*! \fn s21_fieldEmpty(int **field)
 * \brief Проверка пустоты игрового поля
 * \param field Указатель на поле
 * \return 0 - Поле не пустое, 1 - Поле пустое
 */
int s21_fieldEmpty(int **field);

/*! \fn void s21_drawField(WINDOW *win, int **field)
 * \brief Отрисовка игрового поля
 * \param win Окно для отрисовки
 * \param field Указатель на поле
 */
void s21_drawField(WINDOW *win, int **field);

/*! \fn void s21_drawStatistics(WINDOW *win, int level, int score,
  int high_score, int speed)
 * \brief Отрисовка игровой статистики
 * \param win Окно для отрисовки
 * \param level Уровень игры
 * \param score Заработанные очки
 * \param high_score Рекорд (максимальные очки)
 * \param speed Скорость игры
 */
void s21_drawStatistics(WINDOW *win, int level, int score, int high_score,
                        int speed);

/*! \fn void s21_draw(WINDOW *win, GameInfo_t gi)
 * \brief Основная функция отрисовки игры
 * \param win Окно для отрисовки
 * \param gi Текущее состояние игры
 */
void s21_draw(WINDOW *win, GameInfo_t gi);

/*! \fn void s21_drawIntro(const int intro[INTRO_ROWS][INTRO_COLS], WINDOW *win,
 * int y)
 * \brief Вывод заставки intro в заданных координатах
 * \param intro Указатель на заставку
 * \param win Окно для отрисовки
 * \param y Координата заставки
 */
void s21_drawIntro(const int intro[INTRO_ROWS][INTRO_COLS], WINDOW *win, int y);

/*! \fn void s21_Intro(const int intro[INTRO_ROWS][INTRO_COLS],WINDOW *win)
 * \brief Показ заставки
 * \param intro Указатель на заставку
 * \param win Окно для отрисовки
 */
void s21_Intro(const int intro[INTRO_ROWS][INTRO_COLS], WINDOW *win);

/*! \fn void s21_drawNextTetramino(WINDOW *win, int **next)
 * \brief Отрисовка в окне следующего тетрамино
 * \param win Окно для отрисовки
 * \param next Указатель на тетрамино
 */
void s21_drawNextTetramino(WINDOW *win, int **next);
#endif