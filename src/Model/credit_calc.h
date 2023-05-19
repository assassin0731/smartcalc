#ifndef CPP3_SMARTCALC_V2_0_MODEL_CREDIT_CALC_H_
#define CPP3_SMARTCALC_V2_0_MODEL_CREDIT_CALC_H_

#include <string>
#include <vector>

namespace s21 {
struct credit_info {
  double payment_last;
  double payment;
  double sum;
  double overpayment;
};
class CreditCalc {
 public:
  credit_info CreditAnn(const double &sum, int sum_month,
                        const double &percent) noexcept;
  credit_info CreditDiff(const double &sum, int sum_month,
                         const double &percent) noexcept;

 private:
  credit_info result = {0, 0, 0, 0};
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_MODEL_CREDIT_CALC_H_
