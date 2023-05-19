#ifndef CPP3_SMARTCALC_V2_0_MODEL_ERRORS_H_
#define CPP3_SMARTCALC_V2_0_MODEL_ERRORS_H_
namespace s21 {
enum Errors {
  kNoError,
  kStringError,
  kEmpty,
  kTooLong,
  kZeroDiv,
  kMinusSqrt,
  kLogError,
  kExpError,
  kNoXInString,
  kCantPrintGraph
};

constexpr const char *ErrorType(int e) {
  switch (e) {
    case kStringError:
      return "Ошибка в записи";
    case kEmpty:
      return "Пустая строка";
    case kTooLong:
      return "Больше 255 символов в строке";
    case kZeroDiv:
      return "Деление на 0";
    case kMinusSqrt:
      return "Отрицаиельный корень";
    case kLogError:
      return "Несуществующий логарифм";
    case kExpError:
      return "Слишком большое число число для E";
    case kNoXInString:
      return "Отсутствует 'x' для построения графика";
    case kCantPrintGraph:
      return "Невозможно построить график";
  }
  return "";
}
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_MODEL_ERRORS_H_
