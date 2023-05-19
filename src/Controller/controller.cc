#include "controller.h"

#include <string>

namespace s21 {

std::vector<double> Controller::CalculationGraph(const std::string &string,
                                                 int max_x, int min_x,
                                                 std::string &error_message) {
  std::vector<double> y_coordinates =
      model->CalculateForGraph(string, max_x, min_x);
  error_message = ErrorType(model->get_error());
  return y_coordinates;
}

std::string Controller::CalculationAnswer(const std::string &string, double x) {
  return model->CalculateOneAnswer(string, x);
}

credit_info Controller::CreditAnn(const double &sum, int sum_month,
                                  const double &percent) {
  return credit->CreditAnn(sum, sum_month, percent);
}

credit_info Controller::CreditDiff(const double &sum, int sum_month,
                                   const double &percent) {
  return credit->CreditDiff(sum, sum_month, percent);
}
}  // namespace s21
