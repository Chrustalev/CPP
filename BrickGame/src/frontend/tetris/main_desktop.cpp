/**
 * @file main_desktop.cpp
 * @author Collinna
 * @date Февраль 2026
 * @brief Исполняемый файл десктопной версии игры Тетрис
 */
#include <QApplication>
#include <QPushButton>

#include "../../gui/desktop/mainwindow.h"

/*! Главная функция программы
 * \param argc Количество аргументов командной строки
 * \param argv[] Список аргументов
 * \return Код завершения работы программы
 */
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle(" -= Тетрис =- ");
  w.show();
  return a.exec();
}
