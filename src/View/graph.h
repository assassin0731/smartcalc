#ifndef CPP3_SMARTCALC_V2_0_VIEW_GRAPH_H_
#define CPP3_SMARTCALC_V2_0_VIEW_GRAPH_H_

#include <QVector>
#include <QWidget>

namespace Ui {
class Graph;
}

namespace s21 {
class Graph : public QWidget {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  void Plot(int max_x, int max_y, int min_x, int min_y,
            const std::vector<double> &y_coordinates) noexcept;
  ~Graph();

 signals:
  void GraphWindow();

 private slots:
  void onclicked();

 private:
  Ui::Graph *ui;
  bool NeedBreakGraph(int i, const std::vector<double> &y_coordinates,
                      double interval_y);
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_VIEW_GRAPH_H_
