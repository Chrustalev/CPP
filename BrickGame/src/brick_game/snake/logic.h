/**
 * @file logic.h
 * @author Collinna
 * @date Февраль 2026
 * @brief Описание логики игры Змейка.
 */

#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

#include "../common.h"

#define SCORETOLEVELUP 5
///< Количество очков для повышения уровня

#define WINSCORE 200
///< Количество очков для победы в игре

/** Перечисление направлений движения змейки */
typedef enum {
  DirectUp = 0,
  ///< Движение вверх
  DirectRight,
  ///< Движение вправо
  DirectDown,
  ///< Движение вниз
  DirectLeft
  ///< Движение влево
} Directoin_t;

namespace s21 {

const char hsFileName[] = "/snakeHighScore.txt";
///< Имя файла для хранения максимального счета игры

/**
 * @class Point
 * @brief Определение координат точки
 * @details Этот класс определяет координаты точки на игровом поле
 */
class Point {
 public:
  int y;
  ///< Номер строки на игровом поле
  int x;
  ///< Номер столбца на игровом поле

  /*! \fn Point()
   * \brief Конструктор по-умолчанию
   */
  Point();

  /*! \fn Point(int py, int px)
   * \brief Конструктор с параметрами
   * \param py Номер столбца на игровом поле
   * \param px Номер строки на игровом поле
   */
  Point(int py, int px);

  /*! \fn bool operator==(const Point p2) const
   * \brief Определение равенства координат двух точек
   * \param p2 Координаты второй точки
   * \return Результат сравнения координат двух точек
   */
  bool operator==(const Point p2) const;
};

/**
 * @class SnakeLogic
 * @brief Реализация логики игры Змейка
 * @details Этот класс реализует логику игры Змейка, хранит данные игры
 */
class SnakeLogic {
 public:
  /*! \fn void ~SnakeLogic()
   * \brief Деструктор класса, освобождение динамической памяти
   */
  ~SnakeLogic();

  /*! \fn void AnalyzeState()
   * \brief Выбор действий в зависимости от состояния игры
   */
  void AnalyzeState();

  /*! \fn void PutAppleOnField()
   * \brief Размещение яблока на игровом поле
   */
  void PutAppleOnField();

  /*! \fn void PutBodyOnField()
   * \brief Размещение змейки на игровом поле
   */
  void PutBodyOnField();

  /*! \fn void InitialGame()
   * \brief Инициализация игры (состояние игры Initial)
   */
  void InitialGame();

  /*! \fn void StartGame()
   * \brief Старт игры (состояние игры StartState)
   */
  void StartGame();

  /*! \fn void PauseGame()
   * \brief Пауза в игре (состояние игры PauseState)
   */
  void PauseGame();

  /*! \fn void CreateApple()
   * \brief Создание яблока (состояние игры Spawn)
   */
  void CreateApple();

  /*! \fn void MoveBody()
   * \brief Движение змейки (состояние игры Moving)
   */
  void MoveBody();

  /*! \fn void ShiftBody()
   * \brief Сдвиг змейки вперед по истечению таймера (состояние игры Shifting)
   */
  void ShiftBody();

  /*! \fn void FinishGame()
   * \brief Завершение игры (состояние игры Gameover)
   */
  void FinishGame();

  /*! \fn void ClearField()
   * \brief Очистка игрового поля
   */
  void ClearField();

  /*! \fn void FreeGameMemory
   * \brief Очистка динамической памяти
   */
  void FreeGameMemory();

  /*! \fn bool IsCollideWall(const Point nextHeadPos) const
   * \brief Определение столкновения головы змейки со стеной
   * \param nextHeadPos Новые координаты головы змейки
   * \return Результат проверки столкновения головы со стеной
   */
  static bool IsCollideWall(const Point nextHeadPos);

  /*! \fn bool IsCollideBody(const Point nextHeadPos) const
   * \brief Определение столкновения головы змейки с самой собой
   * \param nextHeadPos Новые координаты головы змейки
   * \return Результат проверки столкновения головы с самой собой
   */
  bool IsCollideBody(const Point nextHeadPos) const;

  /*! \fn bool IsCollideApple(const Point nextHeadPos) const
   * \brief Определение столкновения головы змейки с яблоком
   * \param nextHeadPos Новые координаты головы змейки
   * \return Результат проверки столкновения головы с яблоком
   */
  bool IsCollideApple(const Point nextHeadPos) const;

  /*! \fn GameInfo_t GetGameInfo()
   * \brief Возвращает данные игры
   * \return Текущие данные игры
   */
  GameInfo_t GetGameInfo() const;

  /*! \fn Point GetApple()
   * \brief Возвращает данные о созданном яблоке
   * \return Текущие координаты яблока
   */
  Point GetApple() const;

  /*! \fn State_t GetState()
   * \brief Возвращает текущий статус игры
   * \return Текущий статус игры
   */
  State_t GetState() const;

  /*! \fn Directoin_t GetDirection()
   * \brief Возвращает текущее направление головы
   * \return Текущее направление головы
   */
  Directoin_t GetDirection() const;

  /*! \fn UserAction_t GetUserAction()
   * \brief Возвращает текущее действие пользователя
   * \return Текущее действие пользователя
   */
  UserAction_t GetUserAction() const;

  /*! \fn SnakeLogic* GetInstance()
   * \brief Создание единственного экземпляра объекта SnakeLogic (паттерн
   * синглтон)
   * \return Указатель на единственный объект класса
   */
  static SnakeLogic* GetInstance();

  /*! \fn void SetState(State_t newState)
   * \brief Изменение состояния игры
   * \param newState Новое состояние игры
   */
  void SetState(State_t newState);

  /*! \fn void SetDirection(Directoin_t newDirection)
   * \brief Изменение направления движения головы
   * \param newDirection Новое направление движения головы
   */
  void SetDirection(Directoin_t newDirection);

  /*! \fn void SetUserAction(UserAction_t newAction)
   * \brief Изменение текущего действия пользователя
   * \param newAction Новое действие пользователя
   */
  void SetUserAction(UserAction_t newAction);

  /*! \fn void SetHold(bool newHold)
   * \brief Изменение статуса удержания клавиши
   * \param newHold Новый статус удержания клавиши
   */
  void SetHold(bool newHold);

 private:
  static SnakeLogic* instance;

  /*! \fn SnakeLogic()
   * \brief Конструктор по-умолчанию
   */
  SnakeLogic();

  /*! \fn SnakeLogic(const SnakeLogic&)
   * \brief Удаление конструктора с параметрами
   */
  SnakeLogic(const SnakeLogic&) = delete;

  /*! \fn SnakeLogic& operator=(const SnakeLogic&)
   * \brief Удаление конструктора копирования
   */
  SnakeLogic& operator=(const SnakeLogic&) = delete;

 private:
  std::vector<Point> body_;
  ///< Вектор координат частей змейки
  std::vector<Point> emptyField_;
  ///< Вектор координат свободного места игрового поля (для размещения яблок)
  State_t state_;
  ///< Текущий статус игры
  Directoin_t direction_;
  ///< Текущий направление движения змейки
  Point pointApple_;
  ///< Текущий координаты яблока
  GameInfo_t gameInfo_;
  ///< Текущее состояние игры
  long long int itTime_;
  ///< Сохраненное время для отсчета времени для сдвига змейки
  bool holdKey_ = false;
  ///< Статус удержания клавиши
  UserAction_t userAction_;
  ///< Действие пользователя
};
}  // namespace s21
