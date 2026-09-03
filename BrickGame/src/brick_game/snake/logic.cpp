/**
 * @file logic.cpp
 * @author Collinna
 * @date Февраль 2026
 * @brief Реализация библиотеки игры Змейка
 */

#include "logic.h"

#include <ncurses.h>

#include <algorithm>
#include <vector>

#include "../common.h"

namespace s21 {

SnakeLogic* SnakeLogic::instance = nullptr;

Point::Point() : y(0), x(0){};
Point::Point(int py, int px) : y(py), x(px){};
bool Point::operator==(const Point p2) const { return y == p2.y && x == p2.x; }

SnakeLogic::SnakeLogic() {
  gameInfo_.field = new int* [FIELD_HEIGHT] {};
  for (int i = 0; i < FIELD_HEIGHT; i++)
    gameInfo_.field[i] = new int[FIELD_WIDTH]{};
  gameInfo_.next = nullptr;

  srand(time(0));

  state_ = Initial;

  direction_ = DirectUp;

  gameInfo_.speed = 1;
  gameInfo_.level = 1;
  gameInfo_.high_score = s21_readHighScore(hsFileName);
  gameInfo_.score = 0;
  gameInfo_.pause = false;

  pointApple_.x = -1;
  pointApple_.y = -1;

  itTime_ = s21_getTime();
  userAction_ = Default;
}

SnakeLogic::~SnakeLogic() { FreeGameMemory(); }

SnakeLogic* SnakeLogic::GetInstance() {
  if (instance == nullptr) instance = new SnakeLogic();
  return instance;
}

GameInfo_t SnakeLogic::GetGameInfo() const { return gameInfo_; }

Directoin_t SnakeLogic::GetDirection() const { return direction_; }

UserAction_t SnakeLogic::GetUserAction() const { return userAction_; }

Point SnakeLogic::GetApple() const { return pointApple_; }

State_t SnakeLogic::GetState() const { return state_; }

void SnakeLogic::SetState(State_t newState) { state_ = newState; };

void SnakeLogic::SetDirection(Directoin_t newDirection) {
  direction_ = newDirection;
};

void SnakeLogic::SetUserAction(UserAction_t newAction) {
  userAction_ = newAction;
};

void SnakeLogic::SetHold(bool newHold) { holdKey_ = newHold; };

void SnakeLogic::ClearField() {
  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) gameInfo_.field[i][j] = 0;
}

void SnakeLogic::FreeGameMemory() {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    delete[] gameInfo_.field[i];
    gameInfo_.field[i] = nullptr;
  }
  delete[] gameInfo_.field;
  gameInfo_.field = nullptr;
  body_.clear();
  emptyField_.clear();
}

void SnakeLogic::InitialGame() {
  body_.clear();
  emptyField_.clear();

  int centerWidth = FIELD_WIDTH / 2;
  int centerHeight = FIELD_HEIGHT / 2;

  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) emptyField_.push_back(Point{i, j});

  body_.push_back(Point{centerHeight, centerWidth});
  std::erase(emptyField_, Point{centerHeight, centerWidth});

  body_.push_back(Point{centerHeight + 1, centerWidth});
  std::erase(emptyField_, Point{centerHeight + 1, centerWidth});

  body_.push_back(Point{centerHeight + 2, centerWidth});
  std::erase(emptyField_, Point{centerHeight + 2, centerWidth});

  body_.push_back(Point{centerHeight + 3, centerWidth});
  std::erase(emptyField_, Point{centerHeight + 3, centerWidth});

  state_ = StartState;
};

void SnakeLogic::StartGame() {
  if (userAction_ == Start && holdKey_ == true) state_ = Spawn;
};

void SnakeLogic::PauseGame() {
  if (userAction_ == Pause && holdKey_ == true) {
    state_ = Moving;
    gameInfo_.pause = false;
    holdKey_ = false;
  }
};

void SnakeLogic::CreateApple() {
  int index = rand() % (emptyField_.size());
  pointApple_.x = emptyField_[index].x;
  pointApple_.y = emptyField_[index].y;

  state_ = Moving;
};

void SnakeLogic::MoveBody() {
  if (holdKey_ == true) {
    switch (userAction_) {
      case Left:
        if (direction_ == DirectUp || direction_ == DirectDown) {
          direction_ = DirectLeft;
          state_ = Shifting;
        }
        break;
      case Right:
        if (direction_ == DirectUp || direction_ == DirectDown) {
          direction_ = DirectRight;
          state_ = Shifting;
        }
        break;
      case Down:
        if (direction_ == DirectLeft || direction_ == DirectRight) {
          direction_ = DirectDown;
          state_ = Shifting;
        }
        break;
      case Up:
        if (direction_ == DirectLeft || direction_ == DirectRight) {
          direction_ = DirectUp;
          state_ = Shifting;
        }
        break;
      case Action:
        state_ = Shifting;
        holdKey_ = false;
        break;
      case Pause:
        state_ = PauseState;
        gameInfo_.pause = true;
        holdKey_ = false;
        break;
      default:
        break;
    }
  }

  long long int now = s21_getTime();
  long long int elapsedTime = now - itTime_;

  if (elapsedTime > (650 - gameInfo_.speed * DELAY)) {
    state_ = Shifting;
  }
};

void SnakeLogic::ShiftBody() {
  int headX = body_[0].x;
  int headY = body_[0].y;

  itTime_ = s21_getTime();

  switch (direction_) {
    case DirectUp:
      headY--;
      break;
    case DirectRight:
      headX++;
      break;
    case DirectDown:
      headY++;
      break;
    case DirectLeft:
      headX--;
      break;
    default:
      break;
  }

  if (IsCollideWall(Point{headY, headX})) {
    body_.insert(body_.begin(), Point{headY, headX});
    body_.pop_back();
    state_ = Gameover;
  } else if (IsCollideBody(Point{headY, headX})) {
    body_.insert(body_.begin(), Point{headY, headX});
    state_ = Gameover;
  } else {
    body_.insert(body_.begin(), Point{headY, headX});
    std::erase(emptyField_, Point{headY, headX});

    if (IsCollideApple(Point{headY, headX})) {
      gameInfo_.score++;

      gameInfo_.high_score =
          s21_updateHighScore(gameInfo_.high_score, gameInfo_.score);

      gameInfo_.level = s21_updateLevel(gameInfo_.score, SCORETOLEVELUP);
      gameInfo_.speed = gameInfo_.level;

      state_ = Spawn;
    } else {
      Point p = body_.back();
      body_.pop_back();
      emptyField_.push_back(p);
      state_ = Moving;
    }
  };

  if (gameInfo_.score == WINSCORE) state_ = Gameover;
}

bool SnakeLogic::IsCollideWall(const Point nextHeadPos) {
  int headX = nextHeadPos.x;
  int headY = nextHeadPos.y;

  return (headX < 0 || headX >= FIELD_WIDTH || headY < 0 ||
          headY >= FIELD_HEIGHT);
}

bool SnakeLogic::IsCollideApple(const Point nextHeadPos) const {
  int headX = nextHeadPos.x;
  int headY = nextHeadPos.y;

  return headX == pointApple_.x && headY == pointApple_.y;
}

bool SnakeLogic::IsCollideBody(const Point nextHeadPos) const {
  int headX = nextHeadPos.x;
  int headY = nextHeadPos.y;

  auto it = std::find(body_.begin(), body_.end(), Point{headY, headX});

  return it != body_.end();
}
void SnakeLogic::FinishGame() {
  s21_writeHighScore(gameInfo_.high_score, hsFileName);
  gameInfo_.speed = 0;
  if (gameInfo_.score >= WINSCORE) gameInfo_.level = MAX_LEVEL + 1;
};

void SnakeLogic::PutBodyOnField() {
  if (state_ == Initial || state_ == StartState) return;

  int x;
  int y;
  for (int i = 1; i < (int)body_.size(); i++) {
    x = body_[i].x;
    y = body_[i].y;
    gameInfo_.field[y][x] = 3;
  }

  x = body_[0].x;
  y = body_[0].y;

  if (x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
    gameInfo_.field[y][x] = 2;
  }
}

void SnakeLogic::PutAppleOnField() {
  if (state_ == Initial || state_ == StartState || pointApple_.x < 0) return;

  int x = pointApple_.x;
  int y = pointApple_.y;
  gameInfo_.field[y][x] = 1;
}

void SnakeLogic::AnalyzeState() {
  switch (state_) {
    case Initial:
      InitialGame();
      break;
    case StartState:
      StartGame();
      break;
    case PauseState:
      PauseGame();
      break;
    case Spawn:
      CreateApple();
      break;
    case Moving:
      MoveBody();
      break;
    case Shifting:
      ShiftBody();
      break;
    case Gameover:
      FinishGame();
      break;
    default:
      break;
  }
}

}  // namespace s21