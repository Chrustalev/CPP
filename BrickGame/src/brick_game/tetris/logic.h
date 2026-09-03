/**
 * @file logic.h
 * @author Collinna
 * @date Август 2025
 * @brief Описание макросов, перечислений,  структур и функций,
  используемых при реализации библиотеки игры Тетрис.
 */

#include <stdbool.h>

#include "../common.h"

#ifndef TETRIS_H
#define TETRIS_H

#define TETROMINO_SIZE 4
///< Размер тетромино

#define SCORETOLEVELUP 600
///< Количество очков для повышения уровня

#define TETROMINOS
///< Матричное описание тетромино
static const int tetrominos[28][TETROMINO_SIZE] = {
    {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    {0, 2, 0, 0}, {0, 2, 2, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 3},
    {0, 3, 3, 3}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 4, 4, 0}, {0, 4, 4, 0},
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 5, 5}, {0, 5, 5, 0}, {0, 0, 0, 0},
    {0, 0, 0, 0}, {0, 6, 6, 0}, {0, 0, 6, 6}, {0, 0, 0, 0}, {0, 0, 0, 0},
    {0, 0, 7, 0}, {0, 7, 7, 7}, {0, 0, 0, 0}};

const char hsFileName[] = "/tetrisHighScore.txt";
///< Имя файла для хранения максимального счета игры

/*! \struct Tetromino_t
 * Объект тетромино
 */
typedef struct {
  int matrix[TETROMINO_SIZE][TETROMINO_SIZE];
  ///< Матричное описание тетромино
  int pos_x;
  ///< Позиция x на игровом поле
  int pos_y;
  ///< Позиция y на игровом поле
  int index;
  ///< Индекс тетромино
} Tetromino_t;

/*! \struct GameMemory_t
 * Текущее состояние игры
 */
typedef struct {
  GameInfo_t gameInfo;
  ///< Текущее состояние игрового поля
  Tetromino_t tetromino;
  ///< Текущее тетромино
  UserAction_t userAction;
  ///< Действие пользователя
  bool holdKey;
  ///< Флаг нажатой кнопки
  State_t state;
  ///< Текущее состояние игры
  int nextTetrominoIndex;
  ///< Индекс следующего тетромино
  long long int time;
  ///< Сохраненное время
} GameMemory_t;

/*! \fn GameMemory_t *s21_getGameMemory()
 * \brief Получение данных об игре
 */
GameMemory_t *s21_getGameMemory();

/*! \fn void s21_freeGameMemory()
 * \brief Освобождение динамической памяти игры
 */
void s21_freeGameMemory();

/*! \fn int s21_updateScore(int lines)
 * \brief Обновление счета игры в зависимости от количества заполненных линий
 * \param lines Количество заполненных линий
 * \return Значение прироста счета игры
 */
int s21_updateScore(int lines);

/*! \fn int s21_updateHighScore(int highScore, int score);
 * \brief Обновление рекорда (максимального счета игры)
 * \param highScore Текущий рекорд
 * \param score Текущий счет
 * \return Новый рекорд
 */
int s21_updateHighScore(int highScore, int score);

/*! \fn int s21_updateLevel(int score)
 * \brief Обновление уровня игры в зависимости от счета игры
 * \param score Текущий счет
 * \return Новый уровень игры
 */
int s21_updateLevel(int score);

/*! \fn void s21_clearField()
 * \brief Очистка игрового поля
 */
void s21_clearField();

/*! \fn void s21_initialGame()
 * \brief Инициализация игры
 */
void s21_initialGame();

/*! \fn void s21_createTetromino()
 * \brief Создание тетромино (состояние игры Spawn)
 */
void s21_createTetromino();

/*! \fn void s21_dropTetromino()
 * \brief Ускорение падения тетромино (состояние игры Drop)
 */
void s21_dropTetromino();

/*! \fn void s21_moveTetromino()
 * \brief Перемещение тетромино (состояние игры Moving)
 */
void s21_moveTetromino();

/*! \fn void s21_shiftTetromino()
 * \brief Сдвиг тетромино вниз (состояние игры Shifting)
 */
void s21_shiftTetromino();

/*! \fn void s21_tryMoveLeft()
 * \brief Перемещение тетромино влево
 */
void s21_tryMoveLeft();

/*! \fn void s21_tryMoveRight()
 * \brief Перемещение тетромино вправо
 */
void s21_tryMoveRight();

/*! \fn void s21_tryRotate()
 * \brief Вращение тетромино
 */
void s21_tryRotate();

/*! \fn void s21_insertTetromino()
 * \brief Размещение тетромино на игровом поле
 */
void s21_insertTetromino();

/*! \fn void s21_deleteTetromino()
 * \brief Удаление тетромино с игрового поля
 */
void s21_deleteTetromino();

/*! \fn void s21_checkFillRow()
 * \brief Проверка заполненных линий на поле
 */
void s21_checkFillRow();

/*! \fn void s21_startGame()
 * \brief Старт игры
 */
void s21_startGame();

/*! \fn void s21_pauseGame()
 * \brief Пауза игры
 */
void s21_pauseGame();

/*! \fn void s21_finishGame()
 * \brief Завершение игры
 */
void s21_finishGame();

/*! \fn int s21_checkCollide(int tetromino_y, int tetromino_x)
 * \brief Проверка столкновения тетромино с границами поля или другими тетромино
 * на поле
 * \param tetromino_y Позиция y тетромино
 * \param tetromino_x Позиция x тетромино
 * \return Статус столкновения (0 - нет столкновения, 1 и более - есть
 * столкновение)
 */
int s21_checkCollide(int tetromino_y, int tetromino_x);

/*! \fn void s21_writeHighScore(int high_score)
 * \brief Запись в файл рекорда игры
 */
void s21_writeHighScore(int high_score);

/*! \fn void s21_readHighScore()
 * \brief Чтение из файла рекорда игры
 */
int s21_readHighScore();

/*! \fn void s21_analyzeState()
 * \brief Выбор действий в зависимости от состояния игры
 */
void s21_analyzeState();

#endif