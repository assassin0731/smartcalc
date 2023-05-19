#ifndef CPP3_SMARTCALC_V2_0_VIEW_MAINWINDOW_H_
#define CPP3_SMARTCALC_V2_0_VIEW_MAINWINDOW_H_

#include <QDate>
#include <QMainWindow>

#include "../Controller/controller.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  void SetController(s21::Controller *controller) { control = controller; }
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graph *graph_window_;
  Controller *control;
  std::vector<int> length_of_text_;

 private slots:
  void GetTextFromButton();
  void Clear();
  void DelLast();
  void PrintAnswerOrGraph();
  void CalculateCredit();

  void IfChangedMaxY();
  void IfChangedMaxX();
  void IfChangedMinY();
  void IfChangedMinX();
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_VIEW_MAINWINDOW_H_
