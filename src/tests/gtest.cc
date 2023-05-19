#include <gtest/gtest.h>

#include <cmath>
#include <iostream>
#include <string>

#include "../Model/calculator.h"
#include "../Model/errors.h"

constexpr double kEps = 0.000001;

TEST(Test, test_1) {
  s21::Calculator model;
  std::string string = "sin(10)";
  double real_result = sin(10);
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_EQ("", s21::ErrorType(model.get_error()));
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_2) {
  s21::Calculator model;
  std::string string = "sin(10)+1-2/3+tg(100)";
  double real_result = sin(10) + 1 - 2. / 3 + tan(100);
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_EQ("", s21::ErrorType(model.get_error()));
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_3) {
  s21::Calculator model;
  std::string string = "abs(cos(10)-12^3+25)+asin(0.5)+10%3";
  double real_result = fabs(cos(10) - pow(12, 3) + 25) + asin(0.5) + 10 % 3;
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_EQ(s21::kNoError, model.get_error());
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_4) {
  s21::Calculator model;
  std::string string = "10--20";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
}

TEST(Test, test_5) {
  s21::Calculator model;
  std::string string = "(123-10)/sin(0)";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kZeroDiv, model.get_error());
}

TEST(Test, test_6) {
  s21::Calculator model;
  std::string string = "sin(123)-.123+12";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
}

TEST(Test, test_7) {
  s21::Calculator model;
  std::string string = "512-asin(0.12.1)";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
}

TEST(Test, test_8) {
  s21::Calculator model;
  std::string string = "512-asin(0.121)+25-100*(10/2))";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
}

TEST(Test, test_9) {
  s21::Calculator model;
  std::string string = "sqrt(-1)";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kMinusSqrt, model.get_error());
}

TEST(Test, test_10) {
  s21::Calculator model;
  std::string string = "1+3/2+ln(-20)";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kLogError, model.get_error());
}

TEST(Test, test_11) {
  s21::Calculator model;
  std::string string = "1+3/2+log(-20)";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kLogError, model.get_error());
}

TEST(Test, test_12) {
  s21::Calculator model;
  std::string string = "asin(0.2)+acos(-0.1)/ln(10)+tg(1.2^3+log(25))";
  double real_result =
      asin(0.2) + acos(-0.1) / log(10) + tan(pow(1.2, 3) + log10(25));
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_13) {
  s21::Calculator model;
  std::string string = "x+2*x-3/2";
  double max_x = 10;
  double min_x = -10;
  double x = 2 * 10. / kNumOfSteps;
  std::vector<double> real_result;
  double start_x = min_x;
  for (int i = 0; i < kNumOfSteps; ++i) {
    real_result.push_back(start_x + 2 * start_x - 3. / 2);
    start_x += x;
  }
  std::vector<double> my_result = model.CalculateForGraph(string, max_x, min_x);
  for (int i = 0; i < kNumOfSteps; ++i) {
    EXPECT_NEAR(real_result[i], my_result[i], kEps);
  }
}

TEST(Test, test_14) {
  s21::Calculator model;
  std::string string = "(25*12-(12/3-(12*3))";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
}

TEST(Test, test_15) {
  s21::Calculator model;
  std::string string = "sin(x)/cos(x)";
  double real_result = sin(0.3) / cos(0.3);
  std::string my_result_str = model.CalculateOneAnswer(string, 0.3);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_16) {
  s21::Calculator model;
  std::string string = "sqrt(125*3/2^1.2)";
  double real_result = sqrt(125 * 3 / pow(2, 1.2));
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_17) {
  s21::Calculator model;
  std::string string = "atan(sqrt(ln(asin(0.5)+5)))";
  double real_result = atan(sqrt(log(asin(0.5) + 5)));
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_18) {
  s21::Calculator model;
  std::string string = "(123-10)%sin(0)";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kZeroDiv, model.get_error());
}

TEST(Test, test_19) {
  s21::Calculator model;
  std::string string = "sqrt(abs(20-sin(25)+10*2-asin(0.1)))";
  double real_result = sqrt(fabs(20 - sin(25) + 10 * 2 - asin(0.1)));
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_20) {
  s21::Calculator model;
  std::string string = "sin(cos(sin(cos(sqrt(abs(1.4+12.3%2.1))))))";
  double real_result = sin(cos(sin(cos(sqrt(fabs(1.4 + fmod(12.3, 2.1)))))));
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_21) {
  s21::Calculator model;
  std::string string = "10/9/8/7/6/5/4+12*2-3*tg(125+cos(123))";
  double real_result = 180.8743346;
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_22) {
  s21::Calculator model;
  std::string string = "+12351*2+2153443-345324+2342+3452-34523*12";
  double real_result = 12351 * 2 + 2153443 - 345324 + 2342 + 3452 - 34523 * 12;
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_23) {
  s21::Calculator model;
  std::string string = "+12*10-3*cos(123)e5+123/12-25^2+12%(10-1/2)";
  double real_result = 12 * 10 - 3 * cos(123) * pow(10, 5) + 123. / 12 -
                       pow(25, 2) + fmod(12, (10 - 1. / 2));
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_24) {
  s21::Calculator model;
  std::string string = "-12e-3+(-25/12)*cos(-2e+2)";
  double real_result = -12 * 0.001 + (-25. / 12) * cos(-2 * 100);
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, kEps);
}

TEST(Test, test_25) {
  s21::Calculator model;
  std::string string = "";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kEmpty, model.get_error());
}

TEST(Test, test_26) {
  s21::Calculator model;
  std::string string;
  for (int i = 0; i < 20; i++) {
    string += "-12e-3+(-25/12)*cos(-2e+2)";
  }
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kTooLong, model.get_error());
}

TEST(Test, test_27) {
  s21::Calculator model;
  std::string string = "-1e+100";
  double real_result = -1 * pow(10, 100);
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  double my_result = stod(my_result_str);
  EXPECT_NEAR(real_result, my_result, 0.1);
}

TEST(Test, test_28) {
  s21::Calculator model;
  std::string string = "sin10";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  string = "cos10";
  my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
  string = "tg10";
  my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
  string = "ln10";
  my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
  string = "log10";
  my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
  string = "sqrt10";
  my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
  string = "atan10";
  my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
  string = "abs10";
  my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
}

TEST(Test, test_29) {
  s21::Calculator model;
  std::string string = "10e-20.15*20";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kStringError, model.get_error());
}

TEST(Test, test_30) {
  s21::Calculator model;
  std::string string = "25/100-10e-400";
  std::string my_result_str = model.CalculateOneAnswer(string, NAN);
  EXPECT_EQ(s21::kExpError, model.get_error());
}

TEST(Test, test_31) {
  s21::Calculator model;
  std::string string = "25/100-10e-40";
  std::vector<double> my_result = model.CalculateForGraph(string, -10, 10);
  EXPECT_EQ("Отсутствует 'x' для построения графика",
            s21::ErrorType(model.get_error()));
}
TEST(Test, test_32) {
  s21::Calculator model;
  std::string string = "25/100-10e-40*x-sqrt(-1)";
  std::vector<double> my_result = model.CalculateForGraph(string, -10, 10);
  EXPECT_EQ(s21::kCantPrintGraph, model.get_error());
  EXPECT_EQ("Невозможно построить график", s21::ErrorType(model.get_error()));
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
