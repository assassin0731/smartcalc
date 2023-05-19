#include "calculator.h"

#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

#include "errors.h"

namespace s21 {
std::vector<double> Calculator::CalculateForGraph(const std::string &string,
                                                  int max_x, int min_x) {
  FromStrToPolish(string);
  max_x_ = max_x;
  min_x_ = min_x;
  return GetCoordinatesY();
}

std::string Calculator::CalculateOneAnswer(const std::string &string,
                                           double x) {
  FromStrToPolish(string);
  x_ = x;
  double answer = GetAnswer();
  std::string answer_for_return;
  if (error_ != kNoError) {
    answer_for_return = ErrorType(error_);
  } else if (IsInteger(answer)) {
    answer_for_return = std::to_string(static_cast<int>(answer));
  } else if (NeedConvertNumToExpForm(answer)) {
    DoubleToExpFormString(answer_for_return, answer);
  } else {
    DoubleToString(answer_for_return, answer);
  }
  return answer_for_return;
}

void Calculator::FromStrToPolish(const std::string &string) {
  Clear();
  string_ = string;
  CheckStringForErrors();
  if (error_ == kNoError) {
    ConvertToVectorOfString();
  }
  if (error_ == kNoError) {
    ConvertToPolishNotation();
  }
}

bool Calculator::IsInteger(double answer) const noexcept {
  return answer == static_cast<int>(answer);
}

bool Calculator::NeedConvertNumToExpForm(double answer) const noexcept {
  double max_num = 1e+12;
  double min_num = 1e-7;
  return fabs(answer) > max_num || fabs(answer) < min_num;
}

void Calculator::DoubleToExpFormString(std::string &answer_for_return,
                                       double answer) {
  std::ostringstream converter_to_exp;
  converter_to_exp << answer;
  answer_for_return = converter_to_exp.str();
}

void Calculator::DoubleToString(std::string &answer_for_return, double answer) {
  std::ostringstream converter_to_double;
  converter_to_double << std::fixed;
  converter_to_double << std::setprecision(7);
  converter_to_double << answer;
  answer_for_return = converter_to_double.str();
  while (answer_for_return.back() == '0') {
    answer_for_return.pop_back();
  }
}

void Calculator::CheckStringForErrors() {
  char prev_elem = 'q';
  int left_bracket_counter = 0;
  int string_size = static_cast<int>(string_.size());
  if (string_size == 0) {
    error_ = kEmpty;
  } else if (string_size > 255) {
    error_ = kTooLong;
  }
  for (int i = 0; i < string_size && error_ == kNoError; ++i) {
    char current_elem = string_[i];
    if (PrevSignCurrentSign(prev_elem, current_elem) ||
        PrevLeftBracketCurrentSign(prev_elem, current_elem) ||
        PrevRightBracketCurrentNotSign(prev_elem, current_elem) ||
        PrevNumberCurrentBracket(prev_elem, current_elem) ||
        PrevNumberCurrentTrigOper(prev_elem, current_elem) ||
        PrevXCurrentNumber(prev_elem, current_elem) ||
        PrevNotNumberCurrentExp(prev_elem, current_elem) ||
        PrevExpCurrentNotNumber(prev_elem, current_elem) ||
        FirstElemIsSign(i, current_elem) ||
        LastElemIsNotNumOrBracket(i, current_elem) ||
        DotBetweenNumbers(i, prev_elem, current_elem) ||
        CountLeftRightBrackets(current_elem, left_bracket_counter) ||
        PrevTrigOperCurrentBracket(i, prev_elem, current_elem)) {
      error_ = kStringError;
    }
    prev_elem = string_[i];
  }
  if (left_bracket_counter > 0) {
    error_ = kStringError;
  }
}

bool Calculator::PrevSignCurrentSign(char prev_elem,
                                     char current_elem) const noexcept {
  return strchr("-+^/*%", prev_elem) && strchr("-+^/*%", current_elem);
}

bool Calculator::PrevLeftBracketCurrentSign(char prev_elem,
                                            char current_elem) const noexcept {
  return prev_elem == '(' && strchr("+^/*%", current_elem);
}

bool Calculator::PrevRightBracketCurrentNotSign(
    char prev_elem, char current_elem) const noexcept {
  return prev_elem == ')' && !strchr(")*-+/^%e", current_elem);
}

bool Calculator::PrevNumberCurrentBracket(char prev_elem,
                                          char current_elem) const noexcept {
  return strchr("0123456789x", prev_elem) && current_elem == '(';
}

bool Calculator::PrevNumberCurrentTrigOper(char prev_elem,
                                           char current_elem) const noexcept {
  return strchr("0123456789x", prev_elem) && strchr("xcstal", current_elem);
}

bool Calculator::PrevXCurrentNumber(char prev_elem,
                                    char current_elem) const noexcept {
  return prev_elem == 'x' && strchr("0123456789x", current_elem);
}

bool Calculator::PrevNotNumberCurrentExp(char prev_elem,
                                         char current_elem) const noexcept {
  return !(strchr("0123456789x)", prev_elem)) && current_elem == 'e';
}

bool Calculator::PrevExpCurrentNotNumber(char prev_elem,
                                         char current_elem) const noexcept {
  return prev_elem == 'e' && !strchr("0123456789-+", current_elem);
}

bool Calculator::FirstElemIsSign(int i, char current_elem) const noexcept {
  return i == 0 && strchr("^/*%.", current_elem);
}

bool Calculator::LastElemIsNotNumOrBracket(int i,
                                           char current_elem) const noexcept {
  return !strchr("0123456789x)", current_elem) &&
         i == static_cast<int>(string_.size()) - 1;
}

bool Calculator::DotBetweenNumbers(int i, char prev_elem,
                                   char current_elem) const noexcept {
  bool error = false;
  if (i < static_cast<int>(string_.size()) - 1) {
    char next_elem = string_[i + 1];
    if (strchr(".", current_elem) &&
        !(strchr("0123456789", prev_elem) && strchr("0123456789", next_elem))) {
      error = true;
    }
  }
  return error;
}

bool Calculator::CountLeftRightBrackets(
    char current_elem, int &left_bracket_counter) const noexcept {
  if (current_elem == '(') {
    ++left_bracket_counter;
  } else if (current_elem == ')') {
    --left_bracket_counter;
  }
  return left_bracket_counter < 0;
}

bool Calculator::PrevTrigOperCurrentBracket(int i, char prev_elem,
                                            char current_elem) const noexcept {
  bool error = false;
  if (i < static_cast<int>(string_.size()) - 1) {
    char next_elem = string_[i + 1];
    if (current_elem == 'n' && prev_elem == 'i' && next_elem != '(') {
      error = true;
    } else if (current_elem == 'g' && prev_elem == 't' && next_elem != '(') {
      error = true;
    } else if (current_elem == 's' && prev_elem == 'o' && next_elem != '(') {
      error = true;
    } else if (current_elem == 's' && prev_elem == 'b' && next_elem != '(') {
      error = true;
    } else if (current_elem == 'n' && prev_elem == 'l' && next_elem != '(') {
      error = true;
    } else if (current_elem == 'g' && prev_elem == 'o' && next_elem != '(') {
      error = true;
    } else if (current_elem == 't' && prev_elem == 'r' && next_elem != '(') {
      error = true;
    } else if (current_elem == 'n' && prev_elem == 'a' && next_elem != '(') {
      error = true;
    }
  }
  return error;
}

void Calculator::ConvertToVectorOfString() {
  int j = 0;
  if (string_[0] == '-') {
    ++j;
    vector_of_str_.push_back("~");
  } else if (string_[0] == '+') {
    ++j;
  }
  while (j < static_cast<int>(string_.size()) && error_ == kNoError) {
    if (string_[j] == 'e') {
      MakeExpNumber(j);
    } else if (CheckIfNumber(string_[j])) {
      MakeNumber(j);
    } else if (CheckIfSinCosAbsLog(string_[j], j)) {
      MakeString(3, j);
    } else if (CheckIfTgLn(string_[j])) {
      MakeString(2, j);
    } else if (CheckIfAsinAcosAtanSqrt(string_[j])) {
      MakeString(4, j);
    } else if (CheckIfUnaryMinus(string_[j], string_[j - 1])) {
      string_[j] = '~';
      MakeString(1, j);
    } else {
      if (!CheckIfUnaryPlus(string_[j], string_[j - 1])) {
        MakeString(1, j);
      }
    }
  }
}

bool Calculator::CheckIfNumber(char current_elem) const noexcept {
  return current_elem >= '0' && current_elem <= '9';
}

bool Calculator::CheckIfSinCosAbsLog(char current_elem, int j) const noexcept {
  bool checked = false;
  if (j < static_cast<int>(string_.size()) - 1) {
    char next_elem = string_[j + 1];
    if ((current_elem == 'a' && next_elem == 'b') || current_elem == 'c' ||
        (current_elem == 's' && next_elem == 'i') ||
        (current_elem == 'l' && next_elem == 'o')) {
      checked = true;
    }
  }
  return checked;
}

bool Calculator::CheckIfTgLn(char current_elem) const noexcept {
  return current_elem == 't' || current_elem == 'l';
}

bool Calculator::CheckIfAsinAcosAtanSqrt(char current_elem) const noexcept {
  return current_elem == 's' || current_elem == 'a';
}

bool Calculator::CheckIfUnaryMinus(char current_elem,
                                   char prev_elem) const noexcept {
  return current_elem == '-' && prev_elem == '(';
}

bool Calculator::CheckIfUnaryPlus(char current_elem,
                                  char prev_elem) const noexcept {
  return current_elem == '+' && prev_elem == '(';
}

void Calculator::MakeNumber(int &j) {
  bool check_dot = false;
  int num_counter = 0;
  while (CheckIfNumber(string_[j])) {
    ++num_counter;
    ++j;
    if (string_[j] == '.' && !check_dot) {
      check_dot = true;
      ++num_counter;
      ++j;
    } else if (string_[j] == '.' && check_dot) {
      error_ = kStringError;
      break;
    }
  }
  j -= num_counter;
  MakeString(num_counter, j);
}

void Calculator::MakeExpNumber(int &j) {
  ++j;
  bool minus = false;
  double max_double = 300;
  if (string_[j] == '-') {
    minus = true;
    ++j;
  } else if (string_[j] == '+') {
    ++j;
  }
  std::string degree_string{};
  while (CheckIfNumber(string_[j])) {
    degree_string += string_[j];
    ++j;
  }
  if (string_[j] == '.') {
    error_ = kStringError;
  } else if (stod(degree_string) > max_double) {
    error_ = kExpError;
  } else {
    double degree = pow(10, stod(degree_string));
    if (minus) {
      vector_of_str_.push_back("/^");
    } else {
      vector_of_str_.push_back("*^");
    }
    vector_of_str_.push_back(std::to_string(degree));
  }
}

void Calculator::MakeString(int k, int &j) {
  std::string new_string{};
  for (int l = 0; l < k; ++l) {
    new_string += string_[j];
    ++j;
  }
  vector_of_str_.push_back(new_string);
}

void Calculator::ConvertToPolishNotation() {
  std::map<std::string, int> oper_with_prior = {
      {"-", 1},    {"+", 1},    {"*", 2},    {"/", 2},  {"%", 2},
      {"~", 3},    {"^", 4},    {"*^", 5},   {"/^", 5}, {"cos", 6},
      {"sin", 6},  {"tg", 6},   {"abs", 6},  {"ln", 6}, {"sqrt", 6},
      {"acos", 6}, {"asin", 6}, {"atan", 6}, {"log", 6}};
  std::stack<std::pair<std::string, int>> oper_stack;
  for (int i = 0; i < static_cast<int>(vector_of_str_.size()); ++i) {
    if (!find_x_ && vector_of_str_[i].compare("x") == 0) {
      find_x_ = true;
    }
    if (CheckIfNumber(vector_of_str_[i][0]) || vector_of_str_[i][0] == 'x') {
      polish_.push_back(vector_of_str_[i]);
    } else if (vector_of_str_[i].compare("(") == 0) {
      oper_stack.push({vector_of_str_[i], 0});
    } else if (vector_of_str_[i].compare(")") == 0) {
      while (oper_stack.top().first.compare("(")) {
        polish_.push_back(oper_stack.top().first);
        oper_stack.pop();
      }
      oper_stack.pop();
    } else {
      GetOperationsFromStack(oper_stack, vector_of_str_[i], oper_with_prior);
    }
  }
  while (oper_stack.size()) {
    polish_.push_back(oper_stack.top().first);
    oper_stack.pop();
  }
}

void Calculator::GetOperationsFromStack(
    std::stack<std::pair<std::string, int>> &oper_stack,
    const std::string &current_symbol,
    const std::map<std::string, int> &oper_with_prior) {
  auto item = oper_with_prior.find(current_symbol);
  std::string operation = item->first;
  int priority = item->second;
  while (oper_stack.size() && oper_stack.top().second >= priority &&
         !(item->second == 4 && oper_stack.top().second == 4)) {
    polish_.push_back(oper_stack.top().first);
    oper_stack.pop();
  }
  oper_stack.push({operation, priority});
}

double Calculator::GetAnswer() { return CountAnswer(NAN); }

std::vector<double> Calculator::GetCoordinatesY() {
  std::vector<double> y_coordinates;
  if (find_x_ && error_ == kNoError) {
    CountForGraph(y_coordinates);
  } else if (error_ == kNoError) {
    error_ = kNoXInString;
  }
  return y_coordinates;
}

void Calculator::CountForGraph(std::vector<double> &y_coordinates) {
  double x = min_x_;
  double nan_inf_counter = 0;
  double x_step =
      (abs(min_x_) + abs(max_x_)) / static_cast<double>(kNumOfSteps);
  for (int j = 0; j < kNumOfSteps; ++j) {
    y_coordinates.push_back(CountAnswer(x));
    error_ = kNoError;
    x = x + x_step;
    if (!std::isnormal(y_coordinates.back())) {
      ++nan_inf_counter;
    }
  }
  if (nan_inf_counter == static_cast<int>(y_coordinates.size())) {
    error_ = kCantPrintGraph;
  }
}

double Calculator::CountAnswer(double x) {
  double answer = 0;
  std::stack<double> counter;
  for (int i = 0; i < static_cast<int>(polish_.size()) && error_ == kNoError;
       ++i) {
    if (IsNumber(polish_[i])) {
      if (polish_[i].compare("x") == 0 && !std::isnan(x_)) {
        answer = x_;
      } else if (polish_[i].compare("x") == 0) {
        answer = x;
      } else {
        answer = stod(polish_[i]);
      }
      counter.push(answer);
    } else if (IsTrigOperation(polish_[i])) {
      CountTrigOperations(answer, counter, i);
    } else {
      CountOtherOperations(answer, counter, i);
    }
  }
  return answer;
}

bool Calculator::IsNumber(const std::string &current_string) const noexcept {
  return !IsTrigOperation(current_string) && !IsOtherOperation(current_string);
}

bool Calculator::IsTrigOperation(
    const std::string &current_string) const noexcept {
  return strpbrk(current_string.c_str(), "tgabssincoslnlogsqrt");
}

bool Calculator::IsOtherOperation(
    const std::string &current_string) const noexcept {
  return strpbrk(current_string.c_str(), "%*^/-+~");
}

void Calculator::CountTrigOperations(double &answer,
                                     std::stack<double> &counter, int i) {
  answer = counter.top();
  counter.pop();
  if (polish_[i].compare("cos") == 0) {
    answer = cos(answer);
    counter.push(answer);
  } else if (polish_[i].compare("sin") == 0) {
    answer = sin(answer);
    counter.push(answer);
  } else if (polish_[i].compare("tg") == 0) {
    answer = tan(answer);
    counter.push(answer);
  } else if (polish_[i].compare("abs") == 0) {
    answer = fabs(answer);
    counter.push(answer);
  } else if (polish_[i].compare("ln") == 0) {
    if (answer <= 0) {
      error_ = kLogError;
    }
    answer = log(answer);
    counter.push(answer);
  } else if (polish_[i].compare("sqrt") == 0) {
    if (answer < 0) {
      error_ = kMinusSqrt;
    }
    answer = sqrt(answer);
    counter.push(answer);
  } else if (polish_[i].compare("asin") == 0) {
    answer = asin(answer);
    counter.push(answer);
  } else if (polish_[i].compare("acos") == 0) {
    answer = acos(answer);
    counter.push(answer);
  } else if (polish_[i].compare("atan") == 0) {
    answer = atan(answer);
    counter.push(answer);
  } else if (polish_[i].compare("log") == 0) {
    if (answer <= 0) {
      error_ = kLogError;
    }
    answer = log10(answer);
    counter.push(answer);
  }
}

void Calculator::CountOtherOperations(double &answer,
                                      std::stack<double> &counter, int i) {
  answer = counter.top();
  counter.pop();
  double eps = 0.0000001;
  if (polish_[i].compare("-") == 0) {
    answer = counter.top() - answer;
    PopPush(counter, answer);
  } else if (polish_[i].compare("+") == 0) {
    answer = counter.top() + answer;
    PopPush(counter, answer);
  } else if (polish_[i].compare("/") == 0 || polish_[i].compare("/^") == 0) {
    if (answer <= eps && answer >= -eps) {
      error_ = kZeroDiv;
    } else {
      answer = counter.top() / answer;
      PopPush(counter, answer);
    }
  } else if (polish_[i].compare("*") == 0 || polish_[i].compare("*^") == 0) {
    answer = counter.top() * answer;
    PopPush(counter, answer);
  } else if (polish_[i].compare("^") == 0) {
    answer = pow(counter.top(), answer);
    PopPush(counter, answer);
  } else if (polish_[i].compare("~") == 0) {
    answer = 0 - answer;
    counter.push(answer);
  } else if (polish_[i].compare("%") == 0) {
    if (answer <= eps && answer >= -eps) {
      error_ = kZeroDiv;
    } else {
      answer = fmod(counter.top(), answer);
      PopPush(counter, answer);
    }
  }
}

void Calculator::PopPush(std::stack<double> &counter, double answer) {
  counter.pop();
  counter.push(answer);
}

int Calculator::get_error() const noexcept { return error_; }

void Calculator::Clear() {
  vector_of_str_.clear();
  polish_.clear();
  find_x_ = false;
  x_ = NAN;
  error_ = kNoError;
}
}  // namespace s21
