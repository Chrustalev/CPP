#include <gtest/gtest.h>
#include <ncurses.h>

#include "../brick_game/common.h"
#include "../brick_game/snake/logic.h"

static s21::SnakeLogic* sing = s21::SnakeLogic::GetInstance();

TEST(Common, userAction) {
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

TEST(Common, updateLevel) {
  int level = s21_updateLevel(6, SCORETOLEVELUP);
  EXPECT_EQ(level, 2);

  level = s21_updateLevel(11, SCORETOLEVELUP);
  EXPECT_EQ(level, 3);

  level = s21_updateLevel(61, SCORETOLEVELUP);
  EXPECT_EQ(level, 10);
};

TEST(Common, updateHighScore) {
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
  int highScore = s21_readHighScore("snakeHighScore.txt");
  s21_writeHighScore(1000, "./asdfjigjr/.m,.m#");
  int score = s21_readHighScore("snakeHighScore.txt");
  EXPECT_EQ(highScore, score);
};

TEST(Control, updateCurrentState) {
  GameInfo_t gi = updateCurrentState();
  EXPECT_NE(gi.field, nullptr);
};

TEST(Control, userAction) {
  userInput(Start, true);
  EXPECT_EQ(sing->GetUserAction(), Start);

  userInput(Terminate, true);
  EXPECT_EQ(sing->GetState(), Gameover);
}

TEST(Point, PointDefault) {
  s21::Point pointDefault;
  EXPECT_EQ(pointDefault.x, 0);
  EXPECT_EQ(pointDefault.y, 0);
}

TEST(Point, PointParam) {
  s21::Point pointParam(-5, 10);
  EXPECT_EQ(pointParam.y, -5);
  EXPECT_EQ(pointParam.x, 10);
}

TEST(Point, PointEQ) {
  s21::Point point1(3, 5);
  s21::Point point2(3, 5);
  s21::Point point3(3, -5);
  s21::Point point4(-3, 5);
  s21::Point point5(-3, -5);
  EXPECT_EQ(point1, point2);
  EXPECT_NE(point1, point3);
  EXPECT_NE(point1, point4);
  EXPECT_NE(point1, point5);
}

TEST(Snake, Constructor) {
  sing->InitialGame();
  EXPECT_NE(sing, nullptr);
}

TEST(Snake, ClearField) {
  sing->ClearField();
  int cnt = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      cnt += sing->GetGameInfo().field[i][j];
  EXPECT_EQ(cnt, 0);
}

TEST(Snake, IsCollideWall) {
  // s21::SnakeLogic* sing = s21::SnakeLogic::GetInstance();
  s21::Point head1(1, 1);
  s21::Point head2(1, -1);
  s21::Point head3(1, FIELD_WIDTH);
  s21::Point head4(-1, 1);
  s21::Point head5(FIELD_HEIGHT, 1);
  EXPECT_EQ(sing->IsCollideWall(head1), false);
  EXPECT_EQ(sing->IsCollideWall(head2), true);
  EXPECT_EQ(sing->IsCollideWall(head3), true);
  EXPECT_EQ(sing->IsCollideWall(head4), true);
  EXPECT_EQ(sing->IsCollideWall(head5), true);
}

TEST(Snake, IsCollideApple) {
  sing->CreateApple();
  s21::Point apple = sing->GetApple();
  s21::Point head1(apple.y, apple.x);
  s21::Point head2(apple.y, -10);
  s21::Point head3(-10, apple.x);
  EXPECT_EQ(sing->IsCollideApple(head1), true);
  EXPECT_NE(sing->IsCollideApple(head2), true);
  EXPECT_NE(sing->IsCollideApple(head3), true);
}

TEST(Snake, AnalyzeState) {
  sing->SetState(Initial);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), StartState);

  sing->SetHold(false);
  sing->SetUserAction(Start);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), StartState);

  sing->SetHold(true);
  sing->SetUserAction(Start);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), Spawn);

  sing->SetState(StartState);
  sing->SetUserAction(Terminate);
  sing->SetHold(false);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), StartState);

  sing->SetState(Spawn);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), Moving);

  sing->SetState(PauseState);
  sing->SetHold(false);
  sing->SetUserAction(Terminate);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), PauseState);

  sing->SetState(PauseState);
  sing->SetHold(false);
  sing->SetUserAction(Pause);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), PauseState);

  sing->SetState(PauseState);
  sing->SetHold(true);
  sing->SetUserAction(Pause);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), Moving);

  sing->SetState(Shifting);
  sing->SetDirection(DirectUp);
  sing->AnalyzeState();

  sing->SetState(Shifting);
  sing->SetDirection(DirectDown);
  sing->AnalyzeState();

  sing->SetState(Shifting);
  sing->SetDirection(DirectLeft);
  sing->AnalyzeState();

  sing->SetState(Shifting);
  sing->SetDirection(DirectRight);
  sing->AnalyzeState();

  sing->SetState(Drop);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), Drop);

  sing->SetState(Gameover);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetGameInfo().speed, 0);
}

TEST(Snake, MoveBody) {
  sing->SetState(Moving);
  sing->SetDirection(DirectUp);
  sing->SetHold(false);
  sing->SetUserAction(Left);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectUp);

  sing->SetState(Moving);
  sing->SetDirection(DirectUp);
  sing->SetHold(true);
  sing->SetUserAction(Terminate);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), Moving);

  // попытки поворота налево
  sing->SetState(Moving);
  sing->SetDirection(DirectUp);
  sing->SetHold(true);
  sing->SetUserAction(Left);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectLeft);

  sing->SetState(Moving);
  sing->SetDirection(DirectDown);
  sing->SetHold(true);
  sing->SetUserAction(Left);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectLeft);

  sing->SetState(Moving);
  sing->SetDirection(DirectRight);
  sing->SetHold(true);
  sing->SetUserAction(Left);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectRight);

  // попытки поворота направо
  sing->SetState(Moving);
  sing->SetDirection(DirectUp);
  sing->SetHold(true);
  sing->SetUserAction(Right);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectRight);

  sing->SetState(Moving);
  sing->SetDirection(DirectDown);
  sing->SetHold(true);
  sing->SetUserAction(Right);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectRight);

  sing->SetState(Moving);
  sing->SetDirection(DirectLeft);
  sing->SetHold(true);
  sing->SetUserAction(Right);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectLeft);

  // попытка поворота вниз
  sing->SetState(Moving);
  sing->SetDirection(DirectLeft);
  sing->SetHold(true);
  sing->SetUserAction(Down);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectDown);

  sing->SetState(Moving);
  sing->SetDirection(DirectRight);
  sing->SetHold(true);
  sing->SetUserAction(Down);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectDown);

  sing->SetState(Moving);
  sing->SetDirection(DirectUp);
  sing->SetHold(true);
  sing->SetUserAction(Down);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectUp);

  // попытка поворота вверх
  sing->SetState(Moving);
  sing->SetDirection(DirectLeft);
  sing->SetHold(true);
  sing->SetUserAction(Up);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectUp);

  sing->SetState(Moving);
  sing->SetDirection(DirectRight);
  sing->SetHold(true);
  sing->SetUserAction(Up);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectUp);

  sing->SetState(Moving);
  sing->SetDirection(DirectDown);
  sing->SetHold(true);
  sing->SetUserAction(Up);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetDirection(), DirectDown);

  sing->SetState(Moving);
  sing->SetHold(true);
  sing->SetUserAction(Action);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), Shifting);

  sing->SetState(Moving);
  sing->SetHold(true);
  sing->SetUserAction(Pause);
  sing->AnalyzeState();
  EXPECT_EQ(sing->GetState(), PauseState);
}

TEST(Snake, putApple) {
  sing->SetState(Moving);
  sing->PutAppleOnField();
  s21::Point apple = sing->GetApple();
  EXPECT_EQ(sing->GetGameInfo().field[apple.y][apple.x], 1);
}

TEST(Snake, putBody) {
  sing->SetState(Moving);
  sing->PutBodyOnField();
  GameInfo_t gi = sing->GetGameInfo();

  int bodyCnt = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++)
      if ((gi.field[i][j] == 2) || (gi.field[i][j] == 3)) bodyCnt++;

  EXPECT_EQ(bodyCnt, 4);
}

TEST(Snake, FreeGameMemory) {
  sing->FreeGameMemory();
  EXPECT_EQ(sing->GetGameInfo().field, nullptr);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
