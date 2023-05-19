UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lgtest -lsubunit -lrt -lm -lpthread
	LEAK=valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lgtest
	LEAK=leaks -quiet -atExit --
endif
CCFLAGS=-std=c++17 -Wall -Werror -Wextra 
GFLAGS=-g -O0 -Wall -fprofile-arcs -ftest-coverage
SOURCES=Model/calculator.cc

all: clean style leaks gcov_report dist dvi clean

style:
	clang-format -n -style=Google -verbose Model/*.cc Model/*.h Controller/*.cc Controller/*.h View/*.cc View/*.h tests/*.cc *.h

style_force:
	clang-format -i -style=Google Model/*.cc Model/*.h Controller/*.cc Controller/*.h View/*.cc View/*.h tests/*.cc *.h

s21_calc: clean
	g++ $(CCFLAGS) -c $(SOURCES)
	ar rc s21_calc.a *.o
	ranlib s21_calc.a
	rm -f *.o

build: clean
	mkdir ../build/
	cp Calcul.pro ../build/
	cd ../build/; qmake Calcul.pro
	make -C ../build/

install: build
	mkdir SmartCalc
	cp -rf ../build/Calcul.app SmartCalc
	cp document1.pdf SmartCalc
	make clean

uninstall:
	rm -rf SmartCalc

dvi:
	texi2dvi dociment.tex
	dvipdfmx dociment.dvi

dist: uninstall install
	tar -zcvf Calc_Archive.tar SmartCalc

gcov_report: clean
	g++ $(GFLAGS) $(CCFLAGS) $(SOURCES) tests/gtest.cc $(LFLAGS) -o test
	./test
	lcov -no-external -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	
tests: s21_calc
	g++ $(CCFLAGS) tests/gtest.cc s21_calc.a -L. $(LFLAGS) -o test
	./test

leaks: tests
	CK_FORK=no $(LEAK) ./test > leak.log
	bash test_leak.sh

clean:
	rm -f test s21_calcul.a *.gc* test.info log.xml test.log leak.log s21_calc.a 
	rm -f -rf report test.dSYM
	rm -f dociment.aux dociment.log dociment.pdf dociment.out dociment.dvi
	rm -rf ../build
