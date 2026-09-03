/**
 * @file mainwindow.cpp
 * @author Collinna
 * @date Февраль 2026
 * @brief Реализация десктопного интерфейса игр BrickGame
 */

#include "mainwindow.h"

#include <QCoreApplication>
#include <QThread>

#include "../../brick_game/common.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
  resize(600, 480);
  field_label_ = new QLabel("Fiels", this);

  QHBoxLayout *hBox = new QHBoxLayout();
  hBox->addWidget(field_label_);

  setLayout(hBox);

  startColor();
  setStyleSheet("color: black; background: black;");

  game_timer_ = new QTimer(this);
  connect(game_timer_, &QTimer::timeout, this, &MainWindow::render);
  game_timer_->start(50);
}

MainWindow::~MainWindow() {}

void MainWindow::startColor() {
  brushes[0] = QBrush(Qt::black, Qt::SolidPattern);
  brushes[1] = QBrush(Qt::red, Qt::SolidPattern);
  brushes[2] = QBrush(QColor(255, 69, 0), Qt::SolidPattern);
  brushes[3] = QBrush(Qt::yellow, Qt::SolidPattern);

  brushes[4] = QBrush(QColor(255, 143, 171), Qt::SolidPattern);
  brushes[5] = QBrush(Qt::green, Qt::SolidPattern);
  brushes[6] = QBrush(Qt::blue, Qt::SolidPattern);
  brushes[7] = QBrush(Qt::magenta, Qt::SolidPattern);
  brushes[8] = QBrush(Qt::white, Qt::SolidPattern);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
  int keyCode = event->key();

  UserAction_t userAction;
  bool hold;

  switch (keyCode) {
    case Qt::Key_S:
      userAction = Start;
      hold = true;
      break;
    case Qt::Key_P:
      userAction = Pause;
      hold = true;
      break;
    case Qt::Key_Q:
      userAction = Terminate;
      hold = true;
      break;
    case Qt::Key_Left:
      userAction = Left;
      hold = true;
      break;
    case Qt::Key_Right:
      userAction = Right;
      hold = true;
      break;
    case Qt::Key_Up:
      userAction = Up;
      hold = true;
      break;
    case Qt::Key_Down:
      userAction = Down;
      hold = true;
      break;
    case Qt::Key_Space:
      userAction = Action;
      hold = true;
      break;
    default:
      userAction = Default;
      hold = false;
      break;
  }

  userInput(userAction, hold);
}

bool MainWindow::isFieldEmpty(int **field) {
  if (field == NULL) return 1;

  int cnt = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++)
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int color = field[i][j];
      if (color > 0) cnt++;
    }

  return cnt == 0;
}

void MainWindow::render() {
  QPainter painter;
  QPicture pic;

  GameInfo_t gi = updateCurrentState();

  painter.begin(&pic);
  draw(&painter, gi);
  painter.end();
  field_label_->setPicture(pic);
  repaint();
  QCoreApplication::processEvents();
  if (gi.speed == 0) {
    game_timer_->stop();
    QThread::msleep(3000);
    close();
  }
}

void MainWindow::drawField(QPainter *qp, int **field) {
  if (field == NULL) return;

  for (int i = 0; i < 20; i++) {
    qp->setBrush(brushes[8]);
    qp->drawRect(0, (i + 1) * 20, 20, 20);
    qp->drawRect((FIELD_WIDTH + 1) * 20, (i + 1) * 20, 20, 20);

    for (int j = 0; j < 10; j++) {
      int color = field[i][j];
      qp->setBrush(brushes[color]);
      qp->drawRect((j + 1) * 20, (i + 1) * 20, 20, 20);
    }
  }

  qp->setBrush(brushes[8]);
  for (int j = 0; j < (FIELD_WIDTH + 2); j++) {
    qp->drawRect(j * 20, 0, 20, 20);
    qp->drawRect(j * 20, 21 * 20, 20, 20);
  }
}

void MainWindow::drawStatistics(QPainter *qp, int level, int score,
                                int high_score, int speed) {
  qp->setPen(Qt::white);
  qp->drawText(300, 150, "Level: " + QString::number(level));
  qp->drawText(300, 180, "Score: " + QString::number(score));
  qp->drawText(300, 210, "High score: " + QString::number(high_score));
  qp->drawText(300, 240, "Speed: " + QString::number(speed));
}

void MainWindow::drawNextTetramino(QPainter *qp, int **next) {
  if (next == NULL) return;

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      int color = next[i][j];
      qp->setBrush(brushes[color]);
      qp->drawRect(j * 20 + 300, i * 20, 20, 20);
    }
}

void MainWindow::draw(QPainter *qp, GameInfo_t gi) {
  drawField(qp, gi.field);

  qp->setPen(Qt::white);
  if (isFieldEmpty(gi.field)) {
    qp->drawText(300, 300, " -= PRESS S TO START =- ");
  } else {
    drawStatistics(qp, gi.level, gi.score, gi.high_score, gi.speed);
    drawNextTetramino(qp, gi.next);
  }

  if (gi.pause == 1) qp->drawText(300, 300, " -= PAUSED =- ");
  if (gi.speed == 0) {
    if (gi.level > MAX_LEVEL)
      qp->drawText(300, 300, " -= YOU WIN =- ");
    else
      qp->drawText(300, 300, " -= YOU LOSE =- ");
  }
}