#include "mainwindow.h"

#include "ui_mainwindow.h"
namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  graph_window_ = new Graph();
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(GetTextFromButton()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_tg, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_ctg, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_atg, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_left, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_right, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_min, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this,
          SLOT(GetTextFromButton()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(Clear()));
  connect(ui->pushButton_del, SIGNAL(clicked()), this, SLOT(DelLast()));
  connect(ui->pushButton_equal, SIGNAL(clicked()), this,
          SLOT(PrintAnswerOrGraph()));

  connect(ui->max_x, SIGNAL(valueChanged(int)), this, SLOT(IfChangedMaxX()));
  connect(ui->max_y, SIGNAL(valueChanged(int)), this, SLOT(IfChangedMaxY()));
  connect(ui->min_x, SIGNAL(valueChanged(int)), this, SLOT(IfChangedMinX()));
  connect(ui->min_y, SIGNAL(valueChanged(int)), this, SLOT(IfChangedMinY()));

  connect(ui->calculate, SIGNAL(clicked()), this, SLOT(CalculateCredit()));
  ui->month->addItem("1 месяц", QVariant(1));
  ui->month->addItem("3 месяца", QVariant(3));
  ui->month->addItem("6 месяцев", QVariant(6));
  ui->month->addItem("9 месяцев", QVariant(9));
  ui->month->addItem("1 год", QVariant(12));
  ui->month->addItem("2 года", QVariant(24));
  ui->month->addItem("3 года", QVariant(36));
  ui->month->addItem("4 года", QVariant(48));
  ui->month->addItem("5 лет", QVariant(60));
  ui->month->addItem("6 лет", QVariant(72));
  ui->month->addItem("7 лет", QVariant(84));
  ui->month->addItem("10 лет", QVariant(120));
  ui->month->addItem("15 лет", QVariant(180));
  ui->month->addItem("20 лет", QVariant(240));
  ui->month->addItem("25 лет", QVariant(300));
  ui->month->addItem("30 лет", QVariant(360));
}

MainWindow::~MainWindow() {
  delete graph_window_;
  delete ui;
}

void MainWindow::GetTextFromButton() {
  QPushButton *button = qobject_cast<QPushButton *>(sender());
  length_of_text_.push_back(button->text().size());
  ui->enter_window->setText(ui->enter_window->text() + button->text());
}

void MainWindow::Clear() {
  ui->result_window->clear();
  ui->enter_window->clear();
}

void MainWindow::DelLast() {
  if (ui->enter_window->text().length() > 0) {
    std::string delete_last = ui->enter_window->text().toStdString();
    for (int i = 0; i < length_of_text_.back(); ++i) {
      delete_last.pop_back();
    }
    length_of_text_.pop_back();
    ui->enter_window->setText(QString::fromStdString(delete_last));
  }
}

void MainWindow::PrintAnswerOrGraph() {
  if (ui->count->isChecked()) {
    ui->result_window->setText(
        QString::fromStdString(control->CalculationAnswer(
            ui->enter_window->text().toStdString(), ui->x->value())));
  } else {
    std::string error_message;
    std::vector<double> y_coordinates(control->CalculationGraph(
        ui->enter_window->text().toStdString(), ui->max_x->value(),
        ui->min_x->value(), error_message));
    if (error_message.empty()) {
      connect(graph_window_, &Graph::GraphWindow, this, &MainWindow::show);
      graph_window_->Plot(ui->max_x->value(), ui->max_y->value(),
                          ui->min_x->value(), ui->min_y->value(),
                          y_coordinates);
      graph_window_->show();
      ui->result_window->clear();
    } else {
      ui->result_window->setText(QString::fromStdString(error_message));
    }
  }
}

void MainWindow::CalculateCredit() {
  if (ui->ann->isChecked()) {
    credit_info result(control->CreditAnn(ui->summ->value(),
                                          ui->month->currentData().toInt(),
                                          ui->percent->value() / 100 / 12));
    ui->payment->setText(QString::number(result.payment, 'f', 2));
    ui->total->setText(QString::number(result.sum, 'f', 2));
    ui->overpayment->setText(QString::number(result.overpayment, 'f', 2));
  } else {
    credit_info result(control->CreditDiff(ui->summ->value(),
                                           ui->month->currentData().toInt(),
                                           ui->percent->value() / 100 / 12));
    ui->payment->setText(QString::number(result.payment, 'f', 2) + "..." +
                         QString::number(result.payment_last, 'f', 2));
    ui->total->setText(QString::number(result.sum, 'f', 2));
    ui->overpayment->setText(QString::number(result.overpayment, 'f', 2));
  }
}

void MainWindow::IfChangedMaxX() {
  ui->min_x->setMaximum(ui->max_x->value() - 1);
}

void MainWindow::IfChangedMinX() {
  ui->max_x->setMinimum(ui->min_x->value() + 1);
}

void MainWindow::IfChangedMaxY() {
  ui->min_y->setMaximum(ui->max_y->value() - 1);
}

void MainWindow::IfChangedMinY() {
  ui->max_y->setMinimum(ui->min_y->value() + 1);
}
}  // namespace s21
