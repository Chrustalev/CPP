#include <gtest/gtest.h>

#include "../brick_game/common.h"
#include "../brick_game/tetris/logic.h"

#define KEY_LEFT 260
#define KEY_RIGHT 261
#define KEY_DOWN 258
#define KEY_UP 259
#define KEY_SPACE 32

TEST(Tetris, userAction) {
  UserAction_t ua;
  ua = s21_getAction('s');
  EXPECT_EQ(ua, Start);

  ua = s21_getAction('S');
  EXPECT_EQ(ua, Start);

  ua = s21_getAction('p');
  EXPECT_EQ(ua, Pause);

  ua = s21_getAction('P');
  EXPECT_EQ(ua, Pause);

  ua = s21_getAction('q');
  EXPECT_EQ(ua, Terminate);

  ua = s21_getAction('Q');
  EXPECT_EQ(ua, Terminate);

  ua = s21_getAction(KEY_LEFT);
  EXPECT_EQ(ua, Left);

  ua = s21_getAction(KEY_RIGHT);
  EXPECT_EQ(ua, Right);

  ua = s21_getAction(KEY_DOWN);
  EXPECT_EQ(ua, Down);

  ua = s21_getAction(KEY_UP);
  EXPECT_EQ(ua, Up);

  ua = s21_getAction(KEY_SPACE);
  EXPECT_EQ(ua, Action);

  ua = s21_getAction(255);
}

TEST(Tetris, userInputTest) {
  UserAction_t ua = Left;

  userInput(ua, true);
  GameMemory_t *gm = s21_getGameMemory();
  EXPECT_EQ(gm->userAction, Left);
  EXPECT_EQ(gm->holdKey, 1);
};

TEST(Tetris, userInputTerm) {
  UserAction_t ua = Terminate;

  userInput(ua, false);
  GameMemory_t *gm = s21_getGameMemory();
  EXPECT_NE(gm->state, Gameover);

  userInput(ua, true);

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, Gameover);
};

TEST(Tetris, updateScore) {
  int score = 100;

  score += s21_updateScore(1);
  EXPECT_EQ(score, 200);

  score += s21_updateScore(2);
  EXPECT_EQ(score, 500);

  score += s21_updateScore(3);
  EXPECT_EQ(score, 1200);

  score += s21_updateScore(4);
  EXPECT_EQ(score, 2700);
};

TEST(Tetris, updateLevel) {
  int level = s21_updateLevel(100, SCORETOLEVELUP);
  EXPECT_EQ(level, 1);

  level = s21_updateLevel(600, SCORETOLEVELUP);
  EXPECT_EQ(level, 2);

  level = s21_updateLevel(6600, SCORETOLEVELUP);
  EXPECT_EQ(level, 10);
};

TEST(Tetris, updateHighScore) {
  int score = 300;
  int highScore = 100;

  highScore = s21_updateHighScore(highScore, score);
  EXPECT_EQ(highScore, 300);

  score = 200;
  highScore = s21_updateHighScore(highScore, score);
  EXPECT_EQ(highScore, 300);
};

TEST(Common, readHighScore) {
  int highScore = s21_readHighScore("./,sadvlk");
  EXPECT_EQ(highScore, 0);
};

TEST(Common, writeHighScore) {
  int highScore = s21_readHighScore("tetrisHighScore.txt");
  s21_writeHighScore(1000, "./asdfjigjr/.m,.m#");
  int score = s21_readHighScore("tetrisHighScore.txt");
  EXPECT_EQ(highScore, score);
};

TEST(Tetris, initGame) {
  s21_initialGame();
  GameMemory_t *gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.level, 1);
  EXPECT_EQ(gm->state, StartState);
};

TEST(Tetris, initGameAgain) {
  s21_initialGame();
  GameMemory_t *gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.level, 1);
  EXPECT_EQ(gm->state, StartState);
};

TEST(Tetris, startGame) {
  GameMemory_t *gm = s21_getGameMemory();
  gm->userAction = Start;
  gm->holdKey = true;
  s21_startGame();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, Spawn);
};

TEST(Tetris, finishGame) {
  s21_finishGame();

  GameMemory_t *gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.speed, 0);
};

TEST(Tetris, createTeromino) {
  GameMemory_t *gm = s21_getGameMemory();
  int nextTetrominoIndex = gm->nextTetrominoIndex;

  s21_createTetromino();

  gm = s21_getGameMemory();

  EXPECT_EQ(gm->tetromino.index, nextTetrominoIndex);
  EXPECT_EQ(gm->state, Moving);
};

TEST(Tetris, updateState) {
  GameInfo_t gi = updateCurrentState();
  GameMemory_t *gm = s21_getGameMemory();

  EXPECT_EQ(gi.score, gm->gameInfo.score);
  EXPECT_EQ(gi.level, gm->gameInfo.level);
};

TEST(Tetris, moveLeft) {
  GameMemory_t *gm = s21_getGameMemory();

  gm->userAction = Left;
  gm->holdKey = true;

  s21_moveTetromino();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->tetromino.pos_x, 2);
};

TEST(Tetris, moveRight) {
  GameMemory_t *gm = s21_getGameMemory();

  gm->userAction = Right;
  gm->holdKey = true;

  s21_moveTetromino();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->tetromino.pos_x, 3);
};

TEST(Tetris, moveDown) {
  GameMemory_t *gm;

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->tetromino.pos_y, 0);

  s21_shiftTetromino();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->tetromino.pos_y, 1);
};

TEST(Tetris, drop) {
  GameMemory_t *gm = s21_getGameMemory();

  gm->userAction = Down;
  gm->holdKey = true;

  s21_moveTetromino();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, Drop);
};

TEST(Tetris, rotate) {
  GameMemory_t *gm = s21_getGameMemory();

  gm->userAction = Action;
  gm->holdKey = true;

  s21_moveTetromino();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->tetromino.pos_x, 3);
};

TEST(Tetris, holdFalse) {
  GameMemory_t *gm = s21_getGameMemory();

  int pos_x = gm->tetromino.pos_x;

  gm->userAction = Left;
  gm->holdKey = false;

  s21_moveTetromino();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->tetromino.pos_x, pos_x);
};

TEST(Tetris, actionNull) {
  GameMemory_t *gm = s21_getGameMemory();

  int pos_x = gm->tetromino.pos_x;
  int pos_y = gm->tetromino.pos_y;

  gm->userAction = Default;
  gm->holdKey = true;

  s21_moveTetromino();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->tetromino.pos_x, pos_x);
  EXPECT_EQ(gm->tetromino.pos_y, pos_y);
};

TEST(Tetris, checkFill) {
  GameMemory_t *gm = s21_getGameMemory();
  int score = gm->gameInfo.score;

  s21_checkFillRow();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.score, score);
};

TEST(Tetris, enterPause) {
  GameMemory_t *gm = s21_getGameMemory();

  gm->userAction = Pause;
  gm->holdKey = true;

  s21_moveTetromino();

  gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.pause, 1);
  EXPECT_EQ(gm->state, PauseState);
};

TEST(Tetris, exitPause){};

TEST(Tetris, freeMemory) {
  s21_freeGameMemory();
  GameMemory_t *gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.field, nullptr);
  EXPECT_EQ(gm->gameInfo.next, nullptr);
};

TEST(Tetris, freeMemoryAgain) {
  s21_freeGameMemory();
  GameMemory_t *gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.field, nullptr);
  EXPECT_EQ(gm->gameInfo.next, nullptr);
};

TEST(Tetris, analyzeState) {
  GameMemory_t *gm = s21_getGameMemory();
  gm->state = Initial;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, StartState);

  gm->state = StartState;
  gm->userAction = Start;
  gm->holdKey = false;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, StartState);

  gm->state = StartState;
  gm->userAction = Start;
  gm->holdKey = true;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, Spawn);

  gm->state = PauseState;
  gm->userAction = Pause;
  gm->holdKey = false;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, PauseState);

  gm->state = PauseState;
  gm->userAction = Start;
  gm->holdKey = true;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, PauseState);

  gm->state = PauseState;
  gm->userAction = Pause;
  gm->holdKey = true;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.pause, 0);

  gm->state = Drop;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, Drop);

  gm->state = Spawn;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, Moving);

  gm->state = Moving;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, Moving);

  // gm->state = Shifting;
  // s21_analyzeState();
  // gm = s21_getGameMemory();
  // EXPECT_EQ(gm->state, Moving);

  int score = gm->gameInfo.score;
  gm->state = Attaching;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->gameInfo.score, score);

  gm->state = Gameover;
  s21_analyzeState();
  gm = s21_getGameMemory();
  EXPECT_EQ(gm->state, Gameover);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
