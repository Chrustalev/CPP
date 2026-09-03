
/**
 * @file logic.c
 * @author Collinna
 * @date Август 2025
 * @brief Исходный файл библиотеки игры Тетрис
 */

#include "logic.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "../common.h"
GameInfo_t updateCurrentState() {
  s21_analyzeState();
  const GameMemory_t* gm = s21_getGameMemory();

  return gm->gameInfo;
}

GameMemory_t* s21_getGameMemory() {
  static GameMemory_t gm;

  return &gm;
}

void s21_freeGameMemory() {
  GameMemory_t* gm = s21_getGameMemory();

  if (gm->gameInfo.field != NULL) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      free(gm->gameInfo.field[i]);
      gm->gameInfo.field[i] = NULL;
    }
    free(gm->gameInfo.field);
    gm->gameInfo.field = NULL;
  }

  if (gm->gameInfo.next != NULL) {
    for (int i = 0; i < TETROMINO_SIZE; i++) {
      free(gm->gameInfo.next[i]);
      gm->gameInfo.next[i] = NULL;
    }

    free(gm->gameInfo.next);
    gm->gameInfo.next = NULL;
  }
}

int s21_updateScore(int lines) {
  int result = 0;
  if (lines == 1)
    result = 100;
  else if (lines == 2)
    result = 300;
  else if (lines == 3)
    result = 700;
  else if (lines == 4)
    result = 1500;
  return result;
}

void s21_clearField() {
  GameMemory_t* gm = s21_getGameMemory();

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) gm->gameInfo.field[i][j] = 0;
}

void s21_initialGame() {
  srand(time(NULL));

  GameMemory_t* gm = s21_getGameMemory();

  if (gm->gameInfo.field == NULL) {
    gm->gameInfo.field = (int**)calloc(sizeof(int*), FIELD_HEIGHT);
    for (int i = 0; i < FIELD_HEIGHT; i++)
      gm->gameInfo.field[i] = (int*)calloc(sizeof(int), FIELD_WIDTH);
  }

  if (gm->gameInfo.next == NULL) {
    gm->gameInfo.next = (int**)calloc(sizeof(int*), TETROMINO_SIZE);
    for (int i = 0; i < TETROMINO_SIZE; i++)
      gm->gameInfo.next[i] = (int*)calloc(sizeof(int), TETROMINO_SIZE);
  }

  s21_clearField();

  gm->gameInfo.score = 0;
  gm->gameInfo.level = 1;
  gm->gameInfo.high_score = s21_readHighScore(hsFileName);
  gm->gameInfo.speed = gm->gameInfo.level;

  gm->nextTetrominoIndex = 1 + (rand() % 7);

  for (int i = 0; i < TETROMINO_SIZE; i++)
    for (int j = 0; j < TETROMINO_SIZE; j++)
      gm->gameInfo.next[i][j] =
          tetrominos[(gm->nextTetrominoIndex - 1) * TETROMINO_SIZE + i][j];

  gm->holdKey = false;
  gm->state = StartState;
}

void s21_createTetromino() {
  TETROMINOS;

  GameMemory_t* gm = s21_getGameMemory();

  gm->tetromino.pos_x = 3;
  gm->tetromino.pos_y = 0;
  gm->tetromino.index = gm->nextTetrominoIndex;
  gm->nextTetrominoIndex = 1 + (rand() % 7);

  for (int i = 0; i < TETROMINO_SIZE; i++)
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      gm->tetromino.matrix[i][j] = gm->gameInfo.next[i][j];
      gm->gameInfo.next[i][j] =
          tetrominos[(gm->nextTetrominoIndex - 1) * TETROMINO_SIZE + i][j];
    }

  gm->time = s21_getTime();

  int collide = s21_checkCollide(gm->tetromino.pos_y, gm->tetromino.pos_x);

  s21_insertTetromino();
  if (collide > 0)
    gm->state = Gameover;

  else
    gm->state = Moving;
}

void s21_dropTetromino() {
  s21_shiftTetromino();

  GameMemory_t* gm = s21_getGameMemory();

  if (gm->state == Moving) gm->state = Drop;
  gm->holdKey = false;
}

void s21_moveTetromino() {
  GameMemory_t* gm = s21_getGameMemory();
  UserAction_t action = gm->userAction;

  if (gm->holdKey == true) {
    switch (action) {
      case Left:
        s21_tryMoveLeft();
        gm->holdKey = false;
        break;
      case Right:
        s21_tryMoveRight();
        gm->holdKey = false;
        break;
      case Down:
        gm->state = Drop;
        break;
      case Action:
        s21_tryRotate();
        gm->holdKey = false;
        break;
      case Pause:
        gm->state = PauseState;
        gm->gameInfo.pause = true;
        gm->holdKey = false;
        break;
      default:
        break;
    }
  }

  long long int now = s21_getTime();
  long long int elapsedTime = now - gm->time;

  if (elapsedTime > (650 - gm->gameInfo.speed * DELAY)) {
    gm->time = now;
    gm->state = Shifting;
    s21_shiftTetromino();
  }
}

void s21_tryMoveLeft() {
  s21_deleteTetromino();

  GameMemory_t* gm = s21_getGameMemory();
  int next_x = gm->tetromino.pos_x - 1;
  int next_y = gm->tetromino.pos_y;
  int collide = s21_checkCollide(next_y, next_x);

  if (collide == 0) gm->tetromino.pos_x = next_x;

  s21_insertTetromino();
}

void s21_tryMoveRight() {
  s21_deleteTetromino();

  GameMemory_t* gm = s21_getGameMemory();
  int next_x = gm->tetromino.pos_x + 1;
  int next_y = gm->tetromino.pos_y;
  int collide = s21_checkCollide(next_y, next_x);

  if (collide == 0) gm->tetromino.pos_x = next_x;

  s21_insertTetromino();
}

void s21_shiftTetromino() {
  s21_deleteTetromino();

  GameMemory_t* gm = s21_getGameMemory();
  int next_x = gm->tetromino.pos_x;
  int next_y = gm->tetromino.pos_y + 1;
  int collide = s21_checkCollide(next_y, next_x);

  if (collide == 0) {
    gm->tetromino.pos_y = next_y;
    gm->state = Moving;
  } else {
    gm->state = Attaching;
  }
  s21_insertTetromino();
}

void s21_tryRotate() {
  s21_deleteTetromino();

  int saveMatrix[TETROMINO_SIZE][TETROMINO_SIZE] = {0};

  GameMemory_t* gm = s21_getGameMemory();

  for (int i = 0; i < TETROMINO_SIZE; i++)
    for (int j = 0; j < TETROMINO_SIZE; j++)
      saveMatrix[i][j] = gm->tetromino.matrix[i][j];

  for (int i = 0; i < TETROMINO_SIZE; i++)
    for (int j = 0; j < TETROMINO_SIZE; j++)
      gm->tetromino.matrix[j][TETROMINO_SIZE - i - 1] = saveMatrix[i][j];

  int collide = s21_checkCollide(gm->tetromino.pos_y, gm->tetromino.pos_x);

  if (collide > 0) {
    for (int i = 0; i < TETROMINO_SIZE; i++)
      for (int j = 0; j < TETROMINO_SIZE; j++)
        gm->tetromino.matrix[i][j] = saveMatrix[i][j];
  }

  s21_insertTetromino();
}

int s21_checkCollide(int tetromino_y, int tetromino_x) {
  GameMemory_t* gm = s21_getGameMemory();
  int result = 0;

  for (int i = 0; i < TETROMINO_SIZE; i++)
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      int pixelTetramino = gm->tetromino.matrix[i][j] > 0;
      int pixelField = 0;
      int pixelFieldY = i + tetromino_y;
      int pixelFieldX = j + tetromino_x;

      if (pixelFieldX < 0)
        pixelField = 1;
      else if (pixelFieldX >= FIELD_WIDTH)
        pixelField = 1;
      else if (pixelFieldY >= FIELD_HEIGHT)
        pixelField = 1;
      else
        pixelField = gm->gameInfo.field[pixelFieldY][pixelFieldX];

      if (pixelTetramino > 0 && pixelField > 0) result++;
    }
  return result;
}

void s21_deleteTetromino() {
  GameMemory_t* gm = s21_getGameMemory();

  for (int i = 0; i < TETROMINO_SIZE; i++)
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      int color = gm->tetromino.matrix[i][j];
      if (color > 0)
        gm->gameInfo.field[i + gm->tetromino.pos_y][j + gm->tetromino.pos_x] =
            0;
    }
}

void s21_insertTetromino() {
  GameMemory_t* gm = s21_getGameMemory();

  int x = gm->tetromino.pos_x;
  int y = gm->tetromino.pos_y;
  for (int i = 0; i < TETROMINO_SIZE; i++)
    for (int j = 0; j < TETROMINO_SIZE; j++) {
      int color = gm->tetromino.matrix[i][j];
      if (color > 0) gm->gameInfo.field[i + y][j + x] = color;
    }
}

void s21_checkFillRow() {
  GameMemory_t* gm = s21_getGameMemory();
  int lines = 0;
  int i = FIELD_HEIGHT - 1;

  while (i >= 1) {
    int fillCount = 0;
    for (int j = 0; j < FIELD_WIDTH; j++)
      if (gm->gameInfo.field[i][j] > 0) fillCount++;
    if (fillCount == FIELD_WIDTH) {
      lines++;
      for (int ii = i - 1; ii >= 0; ii--)
        for (int j = 0; j < FIELD_WIDTH; j++)
          gm->gameInfo.field[ii + 1][j] = gm->gameInfo.field[ii][j];
      i = FIELD_HEIGHT - 1;
    } else
      i--;
  }

  gm->gameInfo.score += s21_updateScore(lines);
  gm->gameInfo.high_score =
      s21_updateHighScore(gm->gameInfo.high_score, gm->gameInfo.score);
  gm->gameInfo.level = s21_updateLevel(gm->gameInfo.score, SCORETOLEVELUP);
  gm->gameInfo.speed = gm->gameInfo.level;

  gm->state = Spawn;
}

void userInput(UserAction_t action, bool hold) {
  GameMemory_t* gm = s21_getGameMemory();
  gm->userAction = action;
  gm->holdKey = hold;
  if (action == Terminate && hold == true) {
    gm->state = Gameover;
  }
}

void s21_analyzeState() {
  const GameMemory_t* gm = s21_getGameMemory();

  State_t state = gm->state;

  switch (state) {
    case Initial:
      s21_initialGame();
      break;
    case StartState:
      s21_startGame();
      break;
    case PauseState:
      s21_pauseGame();
      break;
    case Drop:
      s21_dropTetromino();
      break;
    case Spawn:
      s21_createTetromino();
      break;
    case Moving:
      s21_moveTetromino();
      break;
    case Shifting:
      s21_shiftTetromino();
      break;
    case Attaching:
      s21_checkFillRow();
      break;
    case Gameover:
      s21_finishGame();
      break;
    default:
      break;
  }
}

void s21_startGame() {
  GameMemory_t* gm = s21_getGameMemory();
  if (gm->userAction == Start && gm->holdKey == true) gm->state = Spawn;
}

void s21_pauseGame() {
  GameMemory_t* gm = s21_getGameMemory();
  if (gm->userAction == Pause && gm->holdKey == true) {
    gm->state = Moving;
    gm->gameInfo.pause = false;
    gm->holdKey = false;
  }
}

void s21_finishGame() {
  GameMemory_t* gm = s21_getGameMemory();
  s21_writeHighScore(gm->gameInfo.high_score, hsFileName);
  gm->gameInfo.speed = 0;
}