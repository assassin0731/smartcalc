#ifndef CPP3_SMARTCALC_V2_0_MODEL_CALCULATOR_H_
#define CPP3_SMARTCALC_V2_0_MODEL_CALCULATOR_H_

#include <cmath>
#include <map>
#include <stack>
#include <string>
#include <vector>

#include "../constants.h"
#include "errors.h"

namespace s21 {
class Calculator {
 public:
  std::vector<double> CalculateForGraph(const std::string &string, int max_x,
                                        int min_x);
  std::string CalculateOneAnswer(const std::string &string, double x);
  int get_error() const noexcept;

 private:
  void FromStrToPolish(const std::string &string);
  bool IsInteger(double answer) const noexcept;
  bool NeedConvertNumToExpForm(double answer) const noexcept;
  void DoubleToExpFormString(std::string &answer_for_return, double answer);
  void DoubleToString(std::string &answer_for_return, double answer);

  void CheckStringForErrors();
  bool PrevSignCurrentSign(char prev_elem, char current_elem) const noexcept;
  bool PrevLeftBracketCurrentSign(char prev_elem,
                                  char current_elem) const noexcept;
  bool PrevRightBracketCurrentNotSign(char prev_elem,
                                      char current_elem) const noexcept;
  bool PrevNumberCurrentBracket(char prev_elem,
                                char current_elem) const noexcept;
  bool PrevNumberCurrentTrigOper(char prev_elem,
                                 char current_elem) const noexcept;
  bool PrevXCurrentNumber(char prev_elem, char current_elem) const noexcept;
  bool PrevNotNumberCurrentExp(char prev_elem,
                               char current_elem) const noexcept;
  bool PrevExpCurrentNotNumber(char prev_elem,
                               char current_elem) const noexcept;
  bool PrevTrigOperCurrentBracket(int i, char prev_elem,
                                  char current_elem) const noexcept;
  bool DotBetweenNumbers(int i, char prev_elem,
                         char current_elem) const noexcept;
  bool FirstElemIsSign(int i, char current_elem) const noexcept;
  bool CountLeftRightBrackets(char current_elem,
                              int &left_bracket_counter) const noexcept;
  bool LastElemIsNotNumOrBracket(int i, char current_elem) const noexcept;

  void ConvertToVectorOfString();
  bool CheckIfNumber(char current_elem) const noexcept;
  bool CheckIfSinCosAbsLog(char current_elem, int j) const noexcept;
  bool CheckIfTgLn(char current_elem) const noexcept;
  bool CheckIfAsinAcosAtanSqrt(char current_elem) const noexcept;
  bool CheckIfUnaryMinus(char current_elem, char prev_elem) const noexcept;
  bool CheckIfUnaryPlus(char current_elem, char prev_elem) const noexcept;
  void MakeExpNumber(int &j);
  void MakeNumber(int &j);
  void MakeString(int k, int &j);

  void ConvertToPolishNotation();
  void GetOperationsFromStack(
      std::stack<std::pair<std::string, int>> &oper_stack,
      const std::string &current_symbol,
      const std::map<std::string, int> &oper_with_prior);

  std::vector<double> GetCoordinatesY();
  double GetAnswer();
  void CountForGraph(std::vector<double> &y_coordinates);
  double CountAnswer(double x);
  bool IsNumber(const std::string &current_string) const noexcept;
  bool IsTrigOperation(const std::string &current_string) const noexcept;
  bool IsOtherOperation(const std::string &current_string) const noexcept;
  void CountTrigOperations(double &answer, std::stack<double> &counter, int i);
  void CountOtherOperations(double &answer, std::stack<double> &counter, int i);
  void PopPush(std::stack<double> &counter, double answer);

  void Clear();

  std::string string_;
  bool find_x_ = false;
  double x_ = NAN;
  int max_x_ = 0;
  int min_x_ = 0;
  std::vector<std::string> vector_of_str_;
  std::vector<std::string> polish_;
  int error_ = kNoError;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_MODEL_CALCULATOR_H_
