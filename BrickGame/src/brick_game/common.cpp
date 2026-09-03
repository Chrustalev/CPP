/**
 * @file common.cpp
 * @author Collinna
 * @date Февраль 2026
 * @brief Реализация общих функций игр BrickGame
 */

#include "common.h"

#include <ncurses.h>
#include <string.h>
#include <sys/time.h>

#include <cstdlib>
#include <ctime>

UserAction_t s21_getAction(int key) {
  UserAction_t action;
  switch (key) {
    case 's':
    case 'S':
      action = Start;
      break;
    case 'p':
    case 'P':
      action = Pause;
      break;
    case 'q':
    case 'Q':
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case KEY_UP:
      action = Up;
      break;
    case KEY_SPACE:
      action = Action;
      break;
    default:
      action = Default;
      break;
  }
  return action;
}

long long int s21_getTime() {
  struct timeval current_time;

  gettimeofday(&current_time, NULL);
  return (long long int)current_time.tv_sec * 1000 +
         current_time.tv_usec / 1000;
}

int s21_updateHighScore(int highScore, int score) {
  int result = highScore;
  if (score > highScore) result = score;
  return result;
}

int s21_updateLevel(int score, int scoreToLevelUp) {
  int result = score / scoreToLevelUp + 1;
  if (result > MAX_LEVEL) result = MAX_LEVEL;
  return result;
}

int s21_readHighScore(const char* fn) {
  int high_score = 0;

  char filename[255] = {0};
  strcat(filename, getenv("HOME"));
  strcat(filename, fn);

  FILE* file = fopen(filename, "r");
  if (file) {
    int r = fscanf(file, "%d", &high_score);
    if (r != 1) high_score = 0;
    fclose(file);
  }
  return high_score;
}

void s21_writeHighScore(int high_score, const char* fn) {
  char filename[255] = {0};
  strcat(filename, getenv("HOME"));
  strcat(filename, fn);

  FILE* file = fopen(filename, "w");
  if (file) {
    fprintf(file, "%d", high_score);
    fclose(file);
  }
}