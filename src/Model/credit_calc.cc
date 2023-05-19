#include "credit_calc.h"

#include <cmath>

namespace s21 {
credit_info CreditCalc::CreditAnn(const double &sum, int sum_month,
                                  const double &percent) noexcept {
  result.payment = round(100 * sum * percent * pow((1 + percent), sum_month) /
                         (pow((1 + percent), sum_month) - 1)) /
                   100;
  result.sum = result.payment * sum_month;
  result.overpayment = result.sum - sum;
  return result;
}

credit_info CreditCalc::CreditDiff(const double &sum, int sum_month,
                                   const double &percent) noexcept {
  double fixed = sum / sum_month;
  double first = sum * percent;
  double amount_of_payments = 1;
  double payment = 0;
  double total = first + fixed;
  while (sum_month > 1) {
    payment = (sum - fixed * amount_of_payments) * percent;
    ++amount_of_payments;
    total = total + fixed + payment;
    --sum_month;
  }
  result.payment = fixed + first;
  result.payment_last = payment + fixed;
  result.sum = total;
  result.overpayment = total - sum;
  return result;
}
}  // namespace s21
