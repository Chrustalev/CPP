/**
 * @file mainwindow.h
 * @author Collinna
 * @date Февраль 2026
 * @brief Описание класса главного окна, используемого при реализации
 * десктопного интерфейса с использованием Qt.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QShowEvent>
#include <QTimer>

#include "../../brick_game/common.h"

/**
 * @class MainWindow
 * @brief Реализация десктопного интерфейса
 * @details Этот класс реализует десктопный интерфейс игр Brickgame с
 * использованием библиотеки Qt6
 */
class MainWindow : public QWidget {
  Q_OBJECT

 public:
  /*! \fn MainWindow(QWidget *parent = nullptr)
   * \brief Конструктор главного окна
   */
  explicit MainWindow(QWidget *parent = nullptr);

  /*! \fn void startColor()
   * \brief Инициализация цветовой схемы
   */
  void startColor();

  /*! \fn bool isFieldEmpty(int **field)
   * \brief Определение
   * \param field Указатель на игровое поле
   * \return
   */
  bool isFieldEmpty(int **field);

  /*! \fn void draw(QPainter *qp, GameInfo_t gi)
   * \brief Отрисовка кадра игры
   * \param qp Указатель на объект для рисования
   * \param gi Информация о состоянии игры (поле, статистика и т.д.)
   */
  void draw(QPainter *qp, GameInfo_t gi);

  /*! \fn void drawField(QPainter *qp, int **field)
   * \brief Отрисовка игрового поля
   * \param qp Указатель на объект для рисования
   * \param field Указатель на игровое поле
   */
  void drawField(QPainter *qp, int **field);

  /*! \fn void drawNextTetramino(QPainter *qp, int **next)
   * \brief Отрисовка следующей фигуры тетрамино
   * \param qp Указатель на объект для рисования
   * \param next Указатель на следующее тетрамино
   */
  void drawNextTetramino(QPainter *qp, int **next);

  /*! \fn void drawStatistics(QPainter *qp, int level, int score, int
   high_score, int speed)
   * \brief Отрисовка игровой статистики
   * \param qp Указатель на объект для рисования
   * \param level Текущий уровень игры
   * \param score Текущий счет игры
   * \param high_score Максимальный счет игры
   * \param speed Текущая скорость игры
   */
  void drawStatistics(QPainter *qp, int level, int score, int high_score,
                      int speed);

  /*! \fn void render()
   * \brief Рендеринг кадра игры
   */
  void render();

  /*! \fn ~MainWindow()
   * \brief Деструктор главного окна
   */
  ~MainWindow();

 protected:
  /*! \fn void keyPressEvent(QKeyEvent *event)
   * \brief Переопределение метода обработки событий от клавиатуры
   * \param event Событие от клавиатуры
   */
  void keyPressEvent(QKeyEvent *event) override;

 private:
  QLabel *field_label_;
  ///< Виджет для отрисовки кадра игры
  QTimer *game_timer_;
  ///< Игровой таймер (задержка для отрисовки следующего кадра)
  QBrush brushes[9]{};
  ///< Матрица цветовой схемы
};
#endif  // MAINWINDOW_H
