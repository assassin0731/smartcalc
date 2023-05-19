#ifndef CPP3_SMARTCALC_V2_0_CONTROLLER_CONTROLLER_H_
#define CPP3_SMARTCALC_V2_0_CONTROLLER_CONTROLLER_H_

#include "../Model/calculator.h"
#include "../Model/credit_calc.h"

namespace s21 {

class Controller {
 public:
  Controller(Calculator *model, CreditCalc *credit)
      : model(model), credit(credit){};
  std::vector<double> CalculationGraph(const std::string &string, int max_x,
                                       int min_x, std::string &error_message);
  std::string CalculationAnswer(const std::string &string, double x);
  credit_info CreditAnn(const double &sum, int kol_month,
                        const double &percent);
  credit_info CreditDiff(const double &sum, int kol_month,
                         const double &percent);

 private:
  Calculator *model;
  CreditCalc *credit;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_CONTROLLER_CONTROLLER_H_
