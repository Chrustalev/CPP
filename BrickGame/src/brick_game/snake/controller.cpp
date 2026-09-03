/**
 * @file controller.cpp
 * @author Collinna
 * @date Февраль 2026
 * @brief Реализация контроллера игры Змейка
 */

#include "../common.h"
#include "logic.h"

GameInfo_t updateCurrentState() {
  s21::SnakeLogic* sing = s21::SnakeLogic::GetInstance();

  sing->ClearField();
  sing->PutBodyOnField();
  sing->PutAppleOnField();
  sing->AnalyzeState();

  return sing->GetGameInfo();
}

void userInput(UserAction_t action, bool hold) {
  s21::SnakeLogic* sing = s21::SnakeLogic::GetInstance();

  sing->SetUserAction(action);
  sing->SetHold(hold);

  if (action == Terminate && hold == true) {
    sing->SetState(Gameover);
  }
}
