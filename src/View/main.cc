#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Calculator model;
  s21::CreditCalc credit;
  s21::Controller controller(&model, &credit);
  s21::MainWindow w;
  w.SetController(&controller);
  w.show();
  return a.exec();
}
