#include "graph.h"

#include "../constants.h"
#include "ui_graph.h"

namespace s21 {
Graph::Graph(QWidget *parent) : QWidget(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
}

Graph::~Graph() { delete ui; }

void Graph::onclicked() {
  this->close();
  emit GraphWindow();
}

void Graph::Plot(int max_x, int max_y, int min_x, int min_y,
                 const std::vector<double> &y_coordinates) noexcept {
  ui->widget->clearGraphs();
  QPen pen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
  QVector<double> x, y;
  double step_x = (abs(max_x) + abs(min_x)) / static_cast<double>(kNumOfSteps);
  double start_x = min_x;
  double interval_y = (abs(max_y) + abs(min_y)) / 2.;
  int graph_counter = 0;
  ui->widget->xAxis->setRange(min_x, max_x);
  ui->widget->yAxis->setRange(min_y, max_y);
  for (int i = 0; i < kNumOfSteps; ++i) {
    x.push_back(start_x);
    start_x += step_x;
    y.push_back(y_coordinates[i]);
    if (NeedBreakGraph(i, y_coordinates, interval_y)) {
      ui->widget->addGraph()->setPen(pen);
      ui->widget->graph(graph_counter)->setData(x, y);
      ++graph_counter;
      x.clear();
      y.clear();
    }
  }
  ui->widget->addGraph()->setPen(pen);
  ui->widget->graph(graph_counter)->setData(x, y);
  ui->widget->setBackground(QColor(235, 234, 230));
  ui->widget->replot();
}

bool Graph::NeedBreakGraph(int i, const std::vector<double> &y_coordinates,
                           double interval_y) {
  return i < kNumOfSteps - 1 &&
         abs(y_coordinates[i] - y_coordinates[i + 1]) > interval_y;
}
}  // namespace s21
